/*!
  * @file     TEST_ADC.c
  *
  * @brief    �����ļ�
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
  * @date     2019/10/18 ������
  */ 
#include "config.h"
#include "LQ_ADC.h"
#include "LQ_LED.h"
#include "LQ_KEY.h"
#include "LQ_SGP18T.h"
#include "LQ_12864.h"
#include "LQ_UART.h"
#include "TEST_ADC.h"
#include "stdio.h"
/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


#ifdef TFT1_8
/*!
  * @brief    ����ĸ���ϵ�ADC�ӿ�
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example     
  *
  * @date     2019/10/21 ����һ
  */
void TEST_ADC(void)
{
    /* ��ʼ������0 */
    UART_InitConfig(USART0, 115200);
    TFTSPI_Init(1);                 //LCD��ʼ��  0:����  1������
    TFTSPI_CLS(u16BLUE);            //����
    LED_Init();
    
    ADC_InitConfig(ADC0CH0_P0_10, ADC_12bit);
    ADC_InitConfig(ADC0CH3_P0_15, ADC_12bit);
    ADC_InitConfig(ADC0CH4_P0_16, ADC_12bit);   //ע���ռ�ñ�����4�ӿ�
    ADC_InitConfig(ADC0CH5_P0_31, ADC_12bit);
    ADC_InitConfig(ADC0CH6_P1_0,  ADC_12bit);
    ADC_InitConfig(ADC0CH11_P0_23, ADC_12bit);

    TFTSPI_P8X16Str(2,0,"LQ ADC Test",u16RED,u16BLUE);
    
    UART_PutStr(USART0, "\r\nLQ ADC Test");
    
    /* 0.806 = 3.3 / 4095 * 1000    12λAD 4096*/
    uint16_t batv1=(uint16_t)(ADC_Read(ADC0CH4_P0_16)*0.806);  //��ȡADCֵ 
    uint16_t batv2=(uint16_t)(ADC_Read(ADC0CH6_P1_0)*0.806);  //��ȡADCֵ 
    uint16_t batv3=(uint16_t)(ADC_Read(ADC0CH3_P0_15)*0.806);  //��ȡADCֵ
    uint16_t batv4=(uint16_t)(ADC_Read(ADC0CH0_P0_10)*0.806);  //��ȡADCֵ 
    uint16_t batv5=(uint16_t)(ADC_Read(ADC0CH5_P0_31)*0.806);  //��ȡADCֵ 
    uint16_t batv6=(uint16_t)(ADC_Read(ADC0CH11_P0_23)*0.806);  //��ȡADCֵ 
    
    char txt[32];
    while (1)
    {           
        /* �������0.5 ��һ���򵥵ĵ�ͨ�˲� ��ֹ��������̫�� ��Ļ������� */
        batv1 = (uint16_t)(batv1*0.5 + 0.5*ADC_Read(ADC0CH4_P0_16)*0.806);            
        batv2 = (uint16_t)(batv2*0.5 + 0.5*ADC_Read(ADC0CH6_P1_0)*0.806);            
        batv3 = (uint16_t)(batv3*0.5 + 0.5*ADC_Read(ADC0CH3_P0_15)*0.806);            
        batv4 = (uint16_t)(batv4*0.5 + 0.5*ADC_Read(ADC0CH0_P0_10)*0.806);            
        batv5 = (uint16_t)(batv5*0.5 + 0.5*ADC_Read(ADC0CH5_P0_31)*0.806);            
        batv6 = (uint16_t)(batv6*0.5 + 0.5*ADC_Read(ADC0CH11_P0_23)*0.806); 
        
        UART_PutStr(USART0,"\r\n-----------------------------\n");
                                  
        sprintf(txt,"P0_16:%3.2fV ",batv1/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,2,txt,u16RED,u16BLUE);
        
        sprintf(txt,"P1_0 :%3.2fV ",batv2/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
        
        sprintf(txt,"P0_15:%3.2fV ",batv3/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,4,txt,u16RED,u16BLUE);
        
        sprintf(txt,"P0_10:%3.2fV ",batv4/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,5,txt,u16RED,u16BLUE);
        
        sprintf(txt,"P0_31:%3.2fV ",batv5/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,6,txt,u16RED,u16BLUE);
        
        sprintf(txt,"P0_23:%3.2fV ",batv6/1000.0f);
        UART_PutStr(USART0,  txt);
        TFTSPI_P8X16Str(3,7,txt,u16RED,u16BLUE);
        
        LED_ColorReverse(blue);    //����   
        delayms(100);
    }
}

#else
/*!
  * @brief    ����ĸ���ϵ�ADC�ӿ�
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example      
  *
  * @date     2019/10/21 ����һ
  */
void TEST_ADC(void)
{
    /* ��ʼ������0 */
    UART_InitConfig(USART0, 115200);
    LCD_Init();                  //LCD��ʼ��
    LCD_CLS();                   //LCD����
    LED_Init();
    KEY_Init();
    
    ADC_InitConfig(ADC0CH0_P0_10, ADC_12bit);
    ADC_InitConfig(ADC0CH3_P0_15, ADC_12bit);
    ADC_InitConfig(ADC0CH4_P0_16, ADC_12bit);   //ע���ռ�ñ�����4�ӿ�
    ADC_InitConfig(ADC0CH5_P0_31, ADC_12bit);
    ADC_InitConfig(ADC0CH6_P1_0,  ADC_12bit);
    ADC_InitConfig(ADC0CH11_P0_23, ADC_12bit);

    LCD_P8x16Str(4,0,"LQ ADC Test"); 
    
    UART_PutStr(USART0, "\r\nLQ ADC Test");
    
    /* 0.806 = 3.3 / 4095 * 1000    12λAD 4096*/
    uint16_t batv1=(uint16_t)(ADC_Read(ADC0CH4_P0_16)*0.806);  //��ȡADCֵ 
    uint16_t batv2=(uint16_t)(ADC_Read(ADC0CH6_P1_0)*0.806);  //��ȡADCֵ 
    uint16_t batv3=(uint16_t)(ADC_Read(ADC0CH3_P0_15)*0.806);  //��ȡADCֵ
    uint16_t batv4=(uint16_t)(ADC_Read(ADC0CH0_P0_10)*0.806);  //��ȡADCֵ 
    uint16_t batv5=(uint16_t)(ADC_Read(ADC0CH5_P0_31)*0.806);  //��ȡADCֵ 
    uint16_t batv6=(uint16_t)(ADC_Read(ADC0CH11_P0_23)*0.806);  //��ȡADCֵ 
    
    char txt[32];
    uint8_t key = 0;
    while (1)
    {           
        /* �������0.5 ��һ���򵥵ĵ�ͨ�˲� ��ֹ��������̫�� ��Ļ������� */
        batv1 = (uint16_t)(batv1*0.5 + 0.5*ADC_Read(ADC0CH4_P0_16)*0.806);            
        batv2 = (uint16_t)(batv2*0.5 + 0.5*ADC_Read(ADC0CH6_P1_0)*0.806);            
        batv3 = (uint16_t)(batv3*0.5 + 0.5*ADC_Read(ADC0CH3_P0_15)*0.806);            
        batv4 = (uint16_t)(batv4*0.5 + 0.5*ADC_Read(ADC0CH0_P0_10)*0.806);            
        batv5 = (uint16_t)(batv5*0.5 + 0.5*ADC_Read(ADC0CH5_P0_31)*0.806);            
        batv6 = (uint16_t)(batv6*0.5 + 0.5*ADC_Read(ADC0CH11_P0_23)*0.806); 
        
           
        switch(KEY_Read(1))     //�������·�ҳ
        {
            case 1:
                LCD_CLS();          //LCD����
                key = 0;            //K0 ���� ��һҳ
                break;           
            case 2: 
                LCD_CLS();          //LCD����
                key = 1;            //K1 ���� �ڶ�ҳ
                break;
            default:
                
                break;
        }
        UART_PutStr(USART0, "\r\n-----------------------------\n");
        
        if(0 == key)
        {
            LCD_P8x16Str(4,0,"LQ ADC Test"); 
            
            sprintf(txt,"P0_16:%3.2fV ",batv1/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,2,txt);
            
            sprintf(txt,"P1_0 :%3.2fV ",batv2/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,4,txt);
            
            sprintf(txt,"P0_15:%3.2fV ",batv3/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,6,txt);
            
        }
        if(1 == key)
        {            
            sprintf(txt,"P0_10:%3.2fV ",batv4/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,0,txt);
            
            sprintf(txt,"P0_31:%3.2fV ",batv5/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,2,txt);    
            
            sprintf(txt,"P0_23:%3.2fV ",batv6/1000.0f);
            UART_PutStr(USART0, txt);
            LCD_P8x16Str(20,4,txt);
            
        }
   
        LED_ColorReverse(blue);    //����   
        delayms(100);
        
    }
}

#endif

