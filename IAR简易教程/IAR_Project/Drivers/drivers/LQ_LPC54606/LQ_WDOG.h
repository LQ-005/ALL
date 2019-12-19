/*!
  * @file     LQ_WDOG.h
  *
  * @brief    ���Ź������ļ�
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
#ifndef __LQ_WDOG_H
#define __LQ_WDOG_H

#include "stdint.h"

/*!
  * @brief    ���Ź���ʼ��
  *
  * @param    min_s    ����������ʱ�� ��λ s
  * @param    max_s    ����������ʱ�� ��λ s
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      WDOG_InitConfig(2, 5); //���ÿ��Ź� ��2-5S��ι��
  * @see      ���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
  * @see      NVIC_SetPriority(WDT_BOD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(WDT_BOD_IRQn);  //ʹ���ж�
  *
  * @date     2019/10/19 ������
  */
void WDOG_InitConfig(uint8_t min_s, uint8_t max_s);





#endif
