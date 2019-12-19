/*!
  * @file     LQ_MRT.h
  *
  * @brief    MRT��ʱ������
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     MRT������ 0XFFFFFF
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_MRT_H
#define __LQ_MRT_H


#include "fsl_mrt.h"

/**
  * @brief    MRT��ʱ�жϳ�ʼ��
  *
  * @param    channel �� MRTͨ�� kMRT_Channel_0 - kMRT_Channel_3
  * @param    us      �� ��ʱ�ж�ʱ��
  *
  * @return   ��
  *
  * @note     MRT��� 0XFFFFFF  ����ʱ90ms   
  *
  * @see      MRT_InitConfig(kMRT_Channel_0, 5000); //5ms����һ��MRT�ж�
  * @see      ���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
  * @see      NVIC_SetPriority(MRT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(MRT0_IRQn);  //ʹ���ж�
  *
  * @date     2019/5/6 ����һ
  */
void MRT_InitConfig(mrt_chnl_t channel, uint32_t us);




#endif
