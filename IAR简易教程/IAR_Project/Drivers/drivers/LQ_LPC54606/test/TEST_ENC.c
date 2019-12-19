/*!
  * @file     TEST_ENC.c
  *
  * @brief    编码器测试例程
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0   2019/11/27  修改硬件SPI初始化函数
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "config.h"
#include "LQ_CTIME.h"
#include "LQ_LED.h"
#include "LQ_UART.h"
#include "LQ_GPIO.h"
#include "TEST_ENC.h"
#include "stdio.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"


/** 声明外部延时函数 */
extern void delayms(uint16_t ms);



/* 注意 LPC54606 只能用带方向编码器 */
#define ENC1_DIR    P1_11          /*!< 编码器1方向 */
#define ENC2_DIR    P1_21          /*!< 编码器2方向 */
#define ENC3_DIR    P1_16          /*!< 编码器3方向 */
#define ENC4_DIR    P1_8           /*!< 编码器4方向 */




/*!
  * @brief    测试带方向编码器
  *
  * @param    
  *
  * @return   
  *
  * @note     LPC54606 只能使用带方向编码器
  *
  * @example      
  *
  * @date     2019/10/21 星期一
  */
void TEST_ENC(void)
{
    LED_Init();
    UART_InitConfig(USART0,115200);
    
#ifdef OLED
    LCD_Init();
    LCD_CLS();                   //LCD清屏
    LCD_P8x16Str(4,0,"LQ ENC PWM");  
#else
    TFTSPI_Init(1);               //TFT1.8初始化 
    TFTSPI_CLS(u16BLUE);          //清屏  
    TFTSPI_P16x16Str(0,0,"北京龙邱智能科技",u16RED,u16BLUE);
#endif 
    
    printf("带方向编码器测试\n");
    printf("编码器1的脉冲接P0_1   方向接P1_11 \n");
    printf("编码器2的脉冲接P0_24  方向接P1_21 \n");
    printf("编码器3的脉冲接P0_4   方向接P1_16 \n");
    printf("编码器4的脉冲接P0_15  方向接P1_8  \n");
    
    CTIMER_InitCapConfig(CTIMER0, CT0Input0_P0_1);          //用CTIMER0 P0_1作为脉冲输入口
    CTIMER_InitCapConfig(CTIMER2, CT2Input0_P0_24);         //用CTIMER2 P0_24作为脉冲输入口
    CTIMER_InitCapConfig(CTIMER3, CT3Input0_P0_4);          //用CTIMER3 P0_4作为脉冲输入口
    CTIMER_InitCapConfig(CTIMER4, CT4Input0_P0_15);         //用CTIMER4 P0_15作为脉冲输入口 注意会少一个ADC口
    
    /* 方向管脚 */
    PIN_InitConfig(ENC1_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC2_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC3_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC4_DIR, PIN_MODE_INPUT_PULLUP, 1);

    char txt[16];
    int speed1, speed2, speed3, speed4;
    while(1)
    {

        /* 获取 编码器计数值 */
        speed1 = CTIMER_GetCounter(CTIMER0, ENC1_DIR);
        
        /* 获取 编码器计数值 */
        speed2 = CTIMER_GetCounter(CTIMER2, ENC2_DIR);
        
        /* 获取 编码器计数值 */
        speed3 = CTIMER_GetCounter(CTIMER3, ENC3_DIR);
          
        /* 获取 编码器计数值 */
        speed4 = CTIMER_GetCounter(CTIMER4, ENC4_DIR);
            
#ifdef OLED
            printf("\r\n/ENC1 %5d \r\n ",speed1);
            sprintf(txt,"enc1:%5d ",speed1);
            LCD_P6x8Str(20,2,txt);
            
            printf("\r\n/ENC2 %5d \r\n ",speed2);
            sprintf(txt,"enc2:%5d ",speed2);
            LCD_P6x8Str(20,3,txt);
            
            printf("\r\n/ENC3 %5d \r\n ",speed3);
            sprintf(txt,"enc3:%5d ",speed3);
            LCD_P6x8Str(20,4,txt);
            
            printf("\r\n/ENC4 %5d \r\n ",speed4);
            sprintf(txt,"enc4:%5d ",speed4);
            LCD_P6x8Str(20,5,txt);
#else
            printf("\r\n/ENC1 %5d \r\n ",speed1);
            sprintf(txt,"enc1:%5d ",speed1);
            TFTSPI_P8X16Str(2, 3, txt, u16RED, u16BLUE);
            
            printf("\r\n/ENC2 %5d \r\n ",speed2);
            sprintf(txt,"enc2:%5d ",speed2);
            TFTSPI_P8X16Str(2, 4, txt, u16RED, u16BLUE);
            
            printf("\r\n/ENC3 %5d \r\n ",speed3);
            sprintf(txt,"enc3:%5d ",speed3);
            TFTSPI_P8X16Str(2, 5, txt, u16RED, u16BLUE);
            
            printf("\r\n/ENC4 %5d \r\n ",speed4);
            sprintf(txt,"enc4:%5d ",speed4);
            TFTSPI_P8X16Str(2, 6, txt, u16RED, u16BLUE);
#endif            
            delayms(100);
            LED_ColorReverse(green);
    }
        
}


