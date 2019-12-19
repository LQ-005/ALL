/*!
  * @file     TEST_CAMERA.c
  *
  * @brief    摄像头测试
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "TEST_CAMERA.h"
#include "LQ_SCTIME.h"
#include "LQ_DMA.h"
#include "LQ_GPIO.h"
#include "LQ_MT9V034.h"
#include "LQ_UART.h"
#include "LQ_LED.h"
#include "LQ_CAMERA.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_SYSTICK.h"
#include "config.h"




/*!
  * @brief    摄像头测试例程
  *
  * @param    
  *
  * @return   
  *
  * @note     测试MT9V034  注意需要使用  带与非门版（白色）转接座  
  *
  * @example      
  *
  * @date     2019/10/22 星期二
  */
void TEST_CAMERA(void)
{
    /* 关闭所有中断 防止初始化过程中 中断服务函数因操作未初始化外设导致硬件访问中断 */
    DisableInterrupts; 
   
#ifdef OLED
    LCD_Init();
    LCD_CLS();                   //LCD清屏 
#else
    TFTSPI_Init(0);               //TFT1.8初始化 
    TFTSPI_CLS(u16BLUE);          //清屏  
#endif 
    
    /* LED 初始化 */
    LED_Init();
    
    /* 串口初始化 */
    UART_InitConfig(USART0, 115200);
    
    /* 摄像头初始化 */
    CAMERA_Init(50);

    /* 初始化完成 打开中断 */
    EnableInterrupts;

    while(1)
    {
        if(camera_flag)
        {
            /* 串口波特率比较低 上报数据比较慢，为了防止还没上传完毕 就被下一帧数据覆盖 先关掉中断 */
            DisableInterrupts;
            
            /* 清除摄像头采集完成标志位 */
            camera_flag = false;
            
            /* 提取部分使用的数据 */
            Get_Use_Image();

            
#ifdef OLED
            /* 二值化 */
            Get_01_Value(0);

            /* OLED画图 */
            LCD_Road(LCDH, LCDW, (uint8_t *)Pixle);
#else
            TFTSPI_Road(0, 0, LCDH, LCDW, (uint8_t *)Image_Use);

#endif
            /* 上报数据给上位机 串口速度比较慢 注意上位机图像宽高设置为120*188*/
//            CAMERA_Reprot();
			
            /* 打开中断 */
            EnableInterrupts;      

        }
    }
}

