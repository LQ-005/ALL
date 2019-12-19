/*!
  * @file     TEST_ICM20602.c
  *
  * @brief    ICM20602 SPI���߲���
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0   2019/11/27  �޸�Ӳ��SPI��ʼ������
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 ������
  */ 
#include "config.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_ICM20602.h"
#include "TEST_ICM20602.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"

/* ����ʹ�õĽ��߷�ʽ��ѡ��ͬͷ�ļ� */
#if (ICM_USE_SELECT == USE_HAL_SPI)
#include "LQ_SPI.h"

#else
#include "LQ_SOFTSPI.h"
#endif


/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


/**
  * @brief    ��ȡICM20602����ICM20602ԭʼ���� ����
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/12 ������
  */
#ifdef TFT1_8
void Test_ICM20602(void)
{
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    
#if (ICM_USE_SELECT == USE_HAL_SPI)
    SPI_MasterInitConfig(SPI3, 3, 10000000);
#else
    SPI_SoftInit(); 
#endif
    
    char  txt[30];
	short aacx,aacy,aacz;	         //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ���� 
    
    TFTSPI_P8X16Str(2,0,"LQ 20602 Test",u16RED,u16BLUE);

    if(ICM20602_Init())
    {
        TFTSPI_P8X16Str(2,0,"ICM Test Fail",u16RED,u16BLUE);
        while(1);   
    }
        
    while(1)
    {
        ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
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
        delayms(500);
        PRINTF("\r\n*********************\r\n");
    }
    
}


#else

void Test_ICM20602(void)
{
    char  txt[30];
	short aacx,aacy,aacz;	         //���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;        //������ԭʼ����
    LCD_Init();                      //LCD��ʼ��
    LCD_CLS();                       //LCD����
#if (ICM_USE_SELECT == USE_HAL_SPI)
    SPI_MasterInitConfig(SPI3, 3, 10000000);
#else 
    SPI_SoftInit(); 
#endif
    
    LCD_P8x16Str(15,0,"LQ 20602 Test"); 
    PRINTF("\r\nLQ ICM20602 Test\n");
    
    if(ICM20602_Init())
    {
    
        LCD_P8x16Str(15,2,"ICM20602 Test Fail");
        while(1);
    }
        
    while(1)
    {
        ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
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
        delayms(500);
        PRINTF("\r\n*********************\r\n");
    }
    
}
#endif



