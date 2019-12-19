/*!
  * @file     TEST_WDOG.c
  *
  * @brief    ���Ź�����
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
#include "fsl_wwdt.h"
#include "LQ_WDOG.h"
#include "LQ_LED.h"
#include "TEST_WDog.h"
/*!
  * @brief    ���Կ��Ź�
  *
  * @param    
  *
  * @return   
  *
  * @note     ���Ź���һ�ַ�ֹ�����ܷɵ����� ��Ҫ��ʱι�� �����ι����ᵼ�µ�Ƭ����λ
  *
  * @example      
  *
  * @date     2019/10/31 ������
  */
 void Test_WDOG(void)
 {
     LED_Init();
     WDOG_InitConfig(1, 2);
     
     // ���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
     NVIC_SetPriority(WDT_BOD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
     EnableIRQ(WDT_BOD_IRQn);  //ʹ���ж�
     
     /* ι�� */
     WWDT_Refresh(WWDT);
     
     /* */
     while(1);
     
 }
