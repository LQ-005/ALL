/*!
  * @file     TEST_SYSTICK.c
  *
  * @brief    systick�����ļ�
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
#include "LQ_LED.h"
#include "LQ_SYSTICK.h"
#include "TEST_SYSTICK.h"

/**
  * @brief    ����systime ��ʱ��
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� LED_R_PIN   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_Systick(void)
{
    LED_Init();                          //LED��ʼ��
    systime.init();                      //����systick��ʱ��
    uint32_t nowtime = 0;
    nowtime = systime.get_time_us();
    while(1)
    {
        
        if(systime.get_time_us() - nowtime >= 1000)
        {
            nowtime = systime.get_time_us();
            
            LED_ColorReverse(red);     //��ת��� ����ָʾ��������
            
        }
    }
    
}


/**
  * @brief    ����systime ��ʱ
  *
  * @param    
  *
  * @return   
  *
  * @note     ʾ���� LED_R_PIN   500Hz��ת
  *
  * @example  
  *
  * @date     2019/6/10 ����һ
  */
void Test_SystickDelay(void)
{
    LED_Init();                          //LED��ʼ��
    systime.init();                      //����systick��ʱ��
    while(1)
    {
        systime.delay_ms(1);
        LED_ColorReverse(red);           //��ת��� ����ָʾ��������
        
    }
    
}



