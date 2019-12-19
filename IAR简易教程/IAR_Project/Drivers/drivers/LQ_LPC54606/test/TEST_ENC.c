/*!
  * @file     TEST_ENC.c
  *
  * @brief    ��������������
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
  * @date     2019/10/18 ������
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


/** �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);



/* ע�� LPC54606 ֻ���ô���������� */
#define ENC1_DIR    P1_11          /*!< ������1���� */
#define ENC2_DIR    P1_21          /*!< ������2���� */
#define ENC3_DIR    P1_16          /*!< ������3���� */
#define ENC4_DIR    P1_8           /*!< ������4���� */




/*!
  * @brief    ���Դ����������
  *
  * @param    
  *
  * @return   
  *
  * @note     LPC54606 ֻ��ʹ�ô����������
  *
  * @example      
  *
  * @date     2019/10/21 ����һ
  */
void TEST_ENC(void)
{
    LED_Init();
    UART_InitConfig(USART0,115200);
    
#ifdef OLED
    LCD_Init();
    LCD_CLS();                   //LCD����
    LCD_P8x16Str(4,0,"LQ ENC PWM");  
#else
    TFTSPI_Init(1);               //TFT1.8��ʼ�� 
    TFTSPI_CLS(u16BLUE);          //����  
    TFTSPI_P16x16Str(0,0,"�����������ܿƼ�",u16RED,u16BLUE);
#endif 
    
    printf("���������������\n");
    printf("������1�������P0_1   �����P1_11 \n");
    printf("������2�������P0_24  �����P1_21 \n");
    printf("������3�������P0_4   �����P1_16 \n");
    printf("������4�������P0_15  �����P1_8  \n");
    
    CTIMER_InitCapConfig(CTIMER0, CT0Input0_P0_1);          //��CTIMER0 P0_1��Ϊ���������
    CTIMER_InitCapConfig(CTIMER2, CT2Input0_P0_24);         //��CTIMER2 P0_24��Ϊ���������
    CTIMER_InitCapConfig(CTIMER3, CT3Input0_P0_4);          //��CTIMER3 P0_4��Ϊ���������
    CTIMER_InitCapConfig(CTIMER4, CT4Input0_P0_15);         //��CTIMER4 P0_15��Ϊ��������� ע�����һ��ADC��
    
    /* ����ܽ� */
    PIN_InitConfig(ENC1_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC2_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC3_DIR, PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(ENC4_DIR, PIN_MODE_INPUT_PULLUP, 1);

    char txt[16];
    int speed1, speed2, speed3, speed4;
    while(1)
    {

        /* ��ȡ ����������ֵ */
        speed1 = CTIMER_GetCounter(CTIMER0, ENC1_DIR);
        
        /* ��ȡ ����������ֵ */
        speed2 = CTIMER_GetCounter(CTIMER2, ENC2_DIR);
        
        /* ��ȡ ����������ֵ */
        speed3 = CTIMER_GetCounter(CTIMER3, ENC3_DIR);
          
        /* ��ȡ ����������ֵ */
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


