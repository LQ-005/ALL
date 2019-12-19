/*!
  * @file     TEST_RIT.c
  *
  * @brief    RIT�����ļ�
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
#include "LQ_RIT.h"
#include "LQ_LED.h"
#include "TEST_RIT.h"

/*!
  * @brief    RIT��ʱ������
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ʾ�����۲� P0_26   500Hz
  *
  * @example  Test_RIT();
  *
  * @date     2019/10/31 ������
  */
void Test_RIT(void)
{
    /* ��ʼ�� LED */
    LED_Init();
    
    /* ��ʼ�� IO ���жϷ������з�ת ����۲��Ƿ�����ж� */
    PIN_InitConfig(P0_26, PIN_MODE_OUTPUT, 0);
    
    /* ����RIT��ʱ�� 1000us ����һ���ж� */
    RIT_InitConfig(1000);
    
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
    NVIC_SetPriority(RIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(RIT_IRQn);  //ʹ���ж�
    
    /* ��irq.c�� ��д�жϷ�����*/
    while(1);

}
