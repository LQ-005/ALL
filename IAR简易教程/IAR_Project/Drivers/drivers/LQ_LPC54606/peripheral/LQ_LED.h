/*!
  * @file     LQ_LED.h
  *
  * @brief    LED�����ļ�
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
#ifndef __LQ_LED_H
#define __LQ_LED_H

#include "LQ_GPIO.h"

/** 
  * @brief RGB LED��ɫö����
  */ 
typedef enum
{
  white = 0,  /*!<��ɫ */
  black = 1,  /*!<��ɫ */
  red   = 2,  /*!<��   */
  green = 3,  /*!<��   */
  blue  = 4,  /*!<��ɫ */
  yellow= 5,  /*!<��ɫ */
  violet= 6,  /*!<��ɫ */
  cyan  = 7,  /*!<��ɫ */
}LED_t;


/* LED�ܽŶ��� */
#define LED_R_PIN       P0_8            /*!<  @brief    ���İ�RGB�� R�Ƶ�Pin  */
                                        
#define LED_G_PIN       P0_9            /*!<  @brief    ���İ�RGB�� G�Ƶ�Pin  */
                                        
#define LED_B_PIN       P1_12           /*!<  @brief    ���İ�RGB�� B�Ƶ�Pin  */
                                        
#define LED_D0_PIN      P1_15           /*!<  @brief    ĸ��� D0�Ƶ�Pin  */
                                        
#define LED_D1_PIN      P1_4            /*!<  @brief    ĸ��� D1�Ƶ�Pin  */

/**
  * @brief    RGB�����ų�ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     LEDʹ��IO��LQ_LED.h��ͨ���궨��ѡ��
  *
  * @see      LED_Init();  
  *
  * @date     2019/6/4 ���ڶ�
  */
void LED_Init(void);


/**
  * @brief    ָ����ɫ�ĵ���
  *
  * @param    color  �� ö��LED_t�е���ɫ
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ��
  *
  * @see      LED_Color(red);   //�����
  *
  * @date     2019/6/4 ���ڶ�
  */
void LED_Color(LED_t color);




/**
  * @brief    ָ����ɫ��˸
  *
  * @param    color  �� ö��LED_t�е���ɫ
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LED_ColorReverse(red);
  *
  * @date     2019/6/4 ���ڶ�
  */
void LED_ColorReverse(LED_t color);


/**
  * @brief    ����LED��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  * 
  * @see  
  *
  * @date     2019/6/4 ���ڶ�
  */
void Test_LED(void);


#endif
