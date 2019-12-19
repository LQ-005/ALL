/*!
  * @file     TEST_PWM.h
  *
  * @brief    PWM����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0   2019/11/27  �޸�Ӳ��SPI��ʼ������
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __TEST_PWM_H
#define __TEST_PWM_H
#include "stdint.h"

/**
  * @brief    ���ö��ռ�ձ�
  *
  * @param    duty          ��ռ�ձ�*SCT_PWM_MAX   
  *
  * @return   
  *
  * @note      �����ֵ 1.5ms�ߵ�ƽ��PWM��    �޷��� 1.3 - 1.7ms֮��
  *
  * @example  PWM_SetServoDuty(700);  //����ռ�ձȰٷ�֮  700/SCT_PWM_MAX * 100
  *
  * @date     2019/5/23 ������
  */
void PWM_SetServoDuty(uint16_t duty);


/*!
  * @brief    ���Զ��PWM
  *
  * @param    
  *
  * @return   
  *
  * @note     ����ʹ�ô˺���ʱ�������Ҫװ���̣���ֹ���������������ֵ����װ������������������ֵ
  *
  * @example      
  *
  * @date     2019/10/21 ����һ
  */
void TEST_Servo(void);


/*!
  * @brief    ������ƺ���
  *
  * @param    num�� 1�����1�� ʹ�� P0_26  P1_17   
                    2�����2�� ʹ�� P0_28  P0_27  
                    3�����3�� ʹ�� P0_19  P0_22   
                    4�����4�� ʹ�� P0_18  P0_17
  * @param    duty: ռ�ձ�  ��Χ��-SCT_PWM_MAX  ---  SCT_PWM_MAX   
  *
  * @return   
  *
  * @note     �����������
  *
  * @see      PWM_SetMotorDuty(1, -2000);  //���1 ��ת ����ռ�ձȰٷ�֮ 2000/SCT_PWM_MAX * 100
  *
  * @date     2019/10/31 ������
  */
void PWM_SetMotorDuty(uint8_t num, short duty);



/*!
  * @brief    ���Ե��
  *
  * @param    
  *
  * @return   
  *
  * @note      1�����1�� ʹ�� P0_26  P1_17   
               2�����2�� ʹ�� P0_28  P0_27  
               3�����3�� ʹ�� P0_19  P0_22   
               4�����4�� ʹ�� P0_18  P0_17   
  *
  * @example   ���� K1���� ���ֹͣ  K0��K2���£�����Ӽ���
  *
  * @date     2019/10/31 ������
  */
void TEST_MOTOR(void);



#endif
