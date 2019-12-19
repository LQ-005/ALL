/*!
  * @file     TEST_ULTRASONIC.h
  *
  * @brief    ����������
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
#ifndef __TEST_ULTRASONIC_H
#define __TEST_ULTRASONIC_H
#include "LQ_GPIO.h"

/*! �������ܽ� */
#define HCSR04_TRIG   P0_7
#define HCSR04_ECHO   P1_13

/**  hc_starttime ��¼���������ECHO �ߵ�ƽ��ʼʱ��  hc_time ��¼ECHO�ߵ�ƽ����ʱ�� */
extern volatile uint32_t hc_starttime; 
extern volatile uint16_t hc_time;

/*!
  * @brief    ���Գ�����ģ��
  *
  * @param    
  *
  * @return   
  *
  * @note     �жϷ�ʽ ������HCSR04_TRIG�ܽ��øߵ�ƽ15us���ң�
  *           ������ģ��ᷢ�䳬���� ͬʱHCSR04_ECHO�ܽ���Ϊ�ߵ�ƽ 
  *           ���յ������������ź�ʱHCSR04_ECHO�ܽű�ɵ͵�ƽ 
  *           ��¼HCSR04_ECHO�ܽŸߵ�ƽʱ�� ͨ�����پͿ��Լ��������
  *
  * @example  Test_HCSR04(); //��ͨ�ȴ���ʽ  ���Ứ�ѱȽϳ���ʱ��
  *
  * @date     2019/10/9 ������
  */
void Test_HCSR04(void);



/*!
  * @brief    ���Գ�����ģ��
  *
  * @param    
  *
  * @return   
  *
  * @note     �жϷ�ʽ ������HCSR04_TRIG�ܽ��øߵ�ƽ15us���ң�
  *           ������ģ��ᷢ�䳬���� ͬʱHCSR04_ECHO�ܽ���Ϊ�ߵ�ƽ 
  *           ���յ������������ź�ʱHCSR04_ECHO�ܽű�ɵ͵�ƽ 
  *           ��¼HCSR04_ECHO�ܽŸߵ�ƽʱ�� ͨ�����پͿ��Լ��������
  *
  * @example  Test_HCSR(); //��irq.c�ж��м�¼ʱ��
  *
  * @date     2019/10/9 ������
  */
void Test_HCSR(void);

#endif
