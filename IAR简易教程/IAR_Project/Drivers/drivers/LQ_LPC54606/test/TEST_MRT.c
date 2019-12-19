/*!
  * @file     TEST_MRT.c
  *
  * @brief    MRT��ʱ������
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "LQ_MRT.h"
#include "LQ_LED.h"
#include "TEST_MRT.h"


/*!
  * @brief    ����MRT��ʱ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ʾ�������� P0_26 P1_17 P0_28 P0_27 Ƶ�ʷֱ�500Hz 100Hz 50Hz 10Hz
  *
  * @example      
  *
  * @date     2019/10/31 ������
  */
void Test_MRT(void)
{
    /* ��ʼ�� LED */
    LED_Init();
    
    /* ��ʼ�� IO ���жϷ������з�ת ����۲��Ƿ�����ж� */
    PIN_InitConfig(P0_26, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P1_17, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P0_28, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(P0_27, PIN_MODE_OUTPUT, 0);
    
    /* ����MRT��ʱ��ͨ��0 1000us����һ���ж� */
    MRT_InitConfig(kMRT_Channel_0, 1000);
    
    /* ����MRT��ʱ��ͨ��0 5000us����һ���ж� */
    MRT_InitConfig(kMRT_Channel_1, 5000);
    
    /* ����MRT��ʱ��ͨ��0 10000us����һ���ж� */
    MRT_InitConfig(kMRT_Channel_2, 10000);
    
    /* ����MRT��ʱ��ͨ��0 50000us����һ���ж� */
    MRT_InitConfig(kMRT_Channel_3, 50000);
    
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
    NVIC_SetPriority(MRT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(MRT0_IRQn);  //ʹ���ж�
    
    /* ��irq.c�� ��д�жϷ�����*/
    while(1);

}

