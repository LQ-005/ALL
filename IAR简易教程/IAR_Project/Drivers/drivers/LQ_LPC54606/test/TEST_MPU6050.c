/*!
  * @file     TEST_MPU6050.c
  *
  * @brief    MPU6050/ICM20602测试文件
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
  * @date     2019/10/19 星期六
  */ 
#include "config.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_MPU6050.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"
#include "TEST_MPU6050.h"
/* 根据使用的接线方式，选择不同头文件 */
#if (IMU_USE_SELECT == USE_HAL_IIC)
#include "LQ_IIC.h"

#else
#include "LQ_SOFTIIC.h"

#endif


/* 声明外部延时函数 */
extern void delayms(uint16_t ms);


/**
  * @brief    读取MPU6050或者ICM20602原始数据 测试
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/12 星期三
  */
#ifdef TFT1_8
void Test_MPU6050(void)
{
    
    TFTSPI_Init(1);                //TFT1.8初始化  
    TFTSPI_CLS(u16BLUE);           //清屏
    
#if (IMU_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#else
    IIC_Init(); 
#endif
    
    char  txt[30];
	short aacx,aacy,aacz;	         //加速度传感器原始数据
	short gyrox,gyroy,gyroz;        //陀螺仪原始数据 
    
    TFTSPI_P8X16Str(2,0,"LQ 6050 Test",u16RED,u16BLUE);

    if(MPU6050_Init())
    {
        TFTSPI_P8X16Str(2,0,"6050 Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据  
        sprintf((char*)txt,"ax:%06d",aacx);
        TFTSPI_P8X16Str(0,1,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"ay:%06d",aacy);
        TFTSPI_P8X16Str(0,2,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"az:%06d",aacz);
        TFTSPI_P8X16Str(0,3,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gx:%06d",gyrox);
        TFTSPI_P8X16Str(0,4,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gy:%06d",gyroy);
        TFTSPI_P8X16Str(0,5,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"gz:%06d",gyroz);
        TFTSPI_P8X16Str(0,6,txt,u16RED,u16BLUE);

        PRINTF("\r\nAX: %d  ",aacx); 
        PRINTF("\r\nAY: %d  ",aacy);
        PRINTF("\r\nAZ: %d  ",aacz); 
        PRINTF("\r\nGX: %d  ",gyrox);
        PRINTF("\r\nGY: %d  ",gyroy); 
        PRINTF("\r\nGZ: %d  ",gyroz);
        delayms(100);
        PRINTF("\r\n*********************\r\n");
    }
    
}


#else

void Test_MPU6050(void)
{
    char  txt[30];
	short aacx,aacy,aacz;	         //加速度传感器原始数据
	short gyrox,gyroy,gyroz;        //陀螺仪原始数据
    LCD_Init();                      //LCD初始化
    LCD_CLS();                       //LCD清屏
    
#if (IMU_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#else
    IIC_Init(); 
#endif
    
    LCD_P8x16Str(15,0,"LQ 6050 Test"); 
    PRINTF("\r\nLQ 6050 Test");
    
    if(MPU6050_Init())
    {
    
        LCD_P8x16Str(15,2,"6050 Test Fail");
        while(1);
    }
        
    while(1)
    {
        MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//得到加速度传感器数据  
        sprintf((char*)txt,"ax:%06d",aacx);
        LCD_P6x8Str(0,2,txt);
        sprintf((char*)txt,"ay:%06d",aacy);
        LCD_P6x8Str(0,3,txt);
        sprintf((char*)txt,"az:%06d",aacz);
        LCD_P6x8Str(0,4,txt);
        sprintf((char*)txt,"gx:%06d",gyrox);
        LCD_P6x8Str(0,5,txt);
        sprintf((char*)txt,"gy:%06d",gyroy);
        LCD_P6x8Str(0,6,txt);
        sprintf((char*)txt,"gz:%06d",gyroz);
        LCD_P6x8Str(0,7,txt);

        PRINTF("\r\nAX: %d  ",aacx); 
        PRINTF("\r\nAY: %d  ",aacy);
        PRINTF("\r\nAZ: %d  ",aacz); 
        PRINTF("\r\nGX: %d  ",gyrox);
        PRINTF("\r\nGY: %d  ",gyroy); 
        PRINTF("\r\nGZ: %d  ",gyroz);
        delayms(100);
        PRINTF("\r\n*********************\r\n");
    }
    
}
#endif







