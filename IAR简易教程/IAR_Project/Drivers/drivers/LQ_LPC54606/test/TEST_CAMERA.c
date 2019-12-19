/*!
  * @file     TEST_CAMERA.c
  *
  * @brief    ����ͷ����
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
  * @brief    ����ͷ��������
  *
  * @param    
  *
  * @return   
  *
  * @note     ����MT9V034  ע����Ҫʹ��  ������Ű棨��ɫ��ת����  
  *
  * @example      
  *
  * @date     2019/10/22 ���ڶ�
  */
void TEST_CAMERA(void)
{
    /* �ر������ж� ��ֹ��ʼ�������� �жϷ����������δ��ʼ�����赼��Ӳ�������ж� */
    DisableInterrupts; 
   
#ifdef OLED
    LCD_Init();
    LCD_CLS();                   //LCD���� 
#else
    TFTSPI_Init(0);               //TFT1.8��ʼ�� 
    TFTSPI_CLS(u16BLUE);          //����  
#endif 
    
    /* LED ��ʼ�� */
    LED_Init();
    
    /* ���ڳ�ʼ�� */
    UART_InitConfig(USART0, 115200);
    
    /* ����ͷ��ʼ�� */
    CAMERA_Init(50);

    /* ��ʼ����� ���ж� */
    EnableInterrupts;

    while(1)
    {
        if(camera_flag)
        {
            /* ���ڲ����ʱȽϵ� �ϱ����ݱȽ�����Ϊ�˷�ֹ��û�ϴ���� �ͱ���һ֡���ݸ��� �ȹص��ж� */
            DisableInterrupts;
            
            /* �������ͷ�ɼ���ɱ�־λ */
            camera_flag = false;
            
            /* ��ȡ����ʹ�õ����� */
            Get_Use_Image();

            
#ifdef OLED
            /* ��ֵ�� */
            Get_01_Value(0);

            /* OLED��ͼ */
            LCD_Road(LCDH, LCDW, (uint8_t *)Pixle);
#else
            TFTSPI_Road(0, 0, LCDH, LCDW, (uint8_t *)Image_Use);

#endif
            /* �ϱ����ݸ���λ�� �����ٶȱȽ��� ע����λ��ͼ��������Ϊ120*188*/
//            CAMERA_Reprot();
			
            /* ���ж� */
            EnableInterrupts;      

        }
    }
}

