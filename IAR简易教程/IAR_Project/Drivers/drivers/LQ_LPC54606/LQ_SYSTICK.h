/*!
  * @file     LQ_SYSTICK.h
  *
  * @brief    systick�����ļ�
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
#ifndef __LQ_SYSTICK_H
#define __LQ_SYSTICK_H
#include "fsl_common.h"

/** 
  * @brief һ��ϵͳʱ��ṹ��
  */
typedef struct
{	
	void (* init) (void);  
	uint32_t (* get_time_us) (void);
	uint32_t (* get_time_ms) (void);
	void (* delay_us)(uint32_t);
	void (* delay_ms)(uint32_t);
}systime_t;

/** ���� systime */
extern systime_t  systime;



#endif //__LQ_SYSTICK_H




