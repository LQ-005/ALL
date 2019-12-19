/*!
  * @file     TEST_9AX.c
  *
  * @brief    ��������ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 ������
  */ 
#include "include.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_9AX.h"
#include "TEST_9AX.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"
/* ����ʹ�õĽ��߷�ʽ��ѡ��ͬͷ�ļ� */
#if (IMU_USE_SELECT == USE_HAL_IIC)
#include "LQ_IIC.h"

#else
#include "LQ_SOFTIIC.h"

#endif


/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);



/**
  * @brief    �������
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/13 ������
  */
#ifdef TFT1_8
void Test_9AX(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    
#if (IMU_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#elif (IMU_USE_SELECT == USE_SOFT_IIC) 
    IIC_Init(); 
#endif
    
    char  txt[30];
	short aacx,aacy,aacz;	         //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ���� 
    short magx, magy, magz;         //�شż�ԭʼ���� 
    
    TFTSPI_P8X16Str(2,0,"LQ 9AX Test",u16RED,u16BLUE);

    if(LQ9AX_Init())
    {
        TFTSPI_P8X16Str(2,0,"9AX Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        FX_8700_GetACCRaw(&aacx,&aacy,&aacz);	  //�õ����ٶȴ���������  
        FX_8700_GetMAGRaw(&magx, &magy, &magz);
        FX_21002_GetRaw(&gyrox, &gyroy, &gyroz);
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
        sprintf((char*)txt,"MX:%06d ",magx);  
        TFTSPI_P8X16Str(0,7,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"MY:%06d ",magy); 
        TFTSPI_P8X16Str(0,8,txt,u16RED,u16BLUE);
        sprintf((char*)txt,"MZ:%06d ",magz);
        TFTSPI_P8X16Str(0,9,txt,u16RED,u16BLUE);

        PRINTF("\r\nAX: %d  ",aacx); 
        PRINTF("\r\nAY: %d  ",aacy);
        PRINTF("\r\nAZ: %d  ",aacz); 
        PRINTF("\r\nGX: %d  ",gyrox);
        PRINTF("\r\nGY: %d  ",gyroy); 
        PRINTF("\r\nGZ: %d  ",gyroz);
        PRINTF("\r\nMX: %d  ",magx);
        PRINTF("\r\nMY: %d  ",magy); 
        PRINTF("\r\nMZ: %d  ",magz);
        delayms(100);
        PRINTF("\r\n*********************\r\n");
    }
    
}


#else

void Test_9AX(void)
{
    char  txt[30];
	short aacx,aacy,aacz;	         //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ����
    short magx, magy, magz;         //�شż�ԭʼ����
    
    LCD_Init();                      //LCD��ʼ��
    LCD_CLS();                       //LCD����
    
#if (IMU_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#elif (IMU_USE_SELECT == USE_SOFT_IIC) 
    IIC_Init(); 
#endif
    
    LCD_P8x16Str(15,0,"LQ 9AX Test"); 
    PRINTF("\r\nLQ 9AX Test\n");
    
    if(LQ9AX_Init())
    {
    
        LCD_P8x16Str(0,2,"9AX Test Fail");
        while(1);
    }
        
    while(1)
    {
        FX_8700_GetACCRaw(&aacx,&aacy,&aacz);	  //�õ����ٶȴ���������  
        FX_8700_GetMAGRaw(&magx, &magy, &magz);
        FX_21002_GetRaw(&gyrox, &gyroy, &gyroz);
        
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
        sprintf((char*)txt,"MX:%5d ",magx);  
        LCD_P6x8Str(60,5,txt);
        sprintf((char*)txt,"MY:%5d ",magy);
        LCD_P6x8Str(60,6,txt); 
        sprintf((char*)txt,"MZ:%5d ",magz); 
        LCD_P6x8Str(60,7,txt);

        PRINTF("\r\nAX: %d  ",aacx); 
        PRINTF("\r\nAY: %d  ",aacy);
        PRINTF("\r\nAZ: %d  ",aacz); 
        PRINTF("\r\nGX: %d  ",gyrox);
        PRINTF("\r\nGY: %d  ",gyroy); 
        PRINTF("\r\nGZ: %d  ",gyroz);
        PRINTF("\r\nMX: %d  ",magx);
        PRINTF("\r\nMY: %d  ",magy); 
        PRINTF("\r\nMZ: %d  ",magz);
        delayms(100);
        PRINTF("\r\n*********************\r\n");
    }
    
}
#endif


