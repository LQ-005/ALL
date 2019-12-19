/*!
  * @file     LQ_KEY.h
  *
  * @brief    ���������ļ�
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
#ifndef __LQ_KEY_H
#define __LQ_KEY_H

#include "LQ_GPIO.h"

/* �����ܽŶ��� */
#define KEY0_PIN       P0_21         /*!<  @brief    ĸ�尴��KYE0 ��Pin  */
                                     
#define KEY1_PIN       P0_5          /*!<  @brief    ĸ�尴��KYE1 ��Pin  */
                                     
#define KEY2_PIN       P1_14         /*!<  @brief    ĸ�尴��KYE2 ��Pin  */



/**
  * @brief    ��ʼ������ĸ���ϵİ���
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����IO��LQ_KEY.h��ͨ���궨��ѡ��
  *
  * @see      KEY_Init();
  *
  * @date     2019/6/4 ���ڶ�
  */
void KEY_Init(void);


/**
  * @brief    ��ȡ����״̬
  *
  * @param    mode�� 0����֧��������;   1��֧��������;
  *
  * @return   0���ް�������  1��KEY0����  2:KEY1����  3:KEY2����
  *
  * @note     ʹ��ǰ���ȳ�ʼ������
  *
  * @see      uint8_t key_flag = KEY_Read(0);
  *
  * @date     2019/6/4 ���ڶ�
  */
uint8_t KEY_Read(uint8_t mode);


/*!
  * @brief    ����GPIIO�ⲿ�ж�
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����ĸ���ϲ�ͬ�İ��� ��ͬ��ɫ�ĵ���˸
  *
  * @see      Test_ExtiKEY();
  *
  * @date     2019/8/19 ����һ
  */
void Test_ExtiKEY(void);


/**
  * @brief    ���԰���
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      Test_KEY();
  *
  * @date     2019/6/4 ���ڶ�
  */
void Test_KEY(void);


#endif