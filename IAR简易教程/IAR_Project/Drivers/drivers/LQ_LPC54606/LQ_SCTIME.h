/*!
  * @file     LQ_SCTIME.h
  *
  * @brief    SCT�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1 
  *           �޸ļ�¼   2019/11/13  SCTIMER0 ������ڲ����ṹ��
  *           			 2019/12/11  �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_SCTIME_H
#define __LQ_SCTIME_H

#include "LQ_GPIO.h"


/** 
  * @brief SCT0ģ�� ����7ͨ�� 
  */ 
typedef enum
{
    SctInput0_P0_0 = 0x0000 + 1,  SctInput0_P1_5 = 0x0000 + 2, SctInput0_P0_24= 0x0000 + 3, SctInput0_P0_13= 0x0000 + 4,
    SctInput1_P0_1 = 0x0100 + 1,  SctInput1_P0_14= 0x0100 + 2, SctInput1_P0_25= 0x0100 + 3,
    SctInput2_P0_2 = 0x0200 + 1,  SctInput2_P0_20= 0x0200 + 2,
    SctInput3_P0_3 = 0x0300 + 1,  SctInput3_P0_21= 0x0300 + 2, SctInput3_P1_6 = 0x0300 + 3,
    SctInput4_P0_4 = 0x0400 + 1,  SctInput4_P1_0 = 0x0400 + 2, SctInput4_P1_7 = 0x0400 + 3,
    SctInput5_P0_5 = 0x0500 + 1,  SctInput5_P1_1 = 0x0500 + 2, SctInput5_P1_22= 0x0500 + 3,
    SctInput6_P0_6 = 0x0600 + 1,  SctInput6_P1_29= 0x0600 + 2, SctInput6_P1_2 = 0x0600 + 3,
    SctInput7_P0_17= 0x0700 + 1,  SctInput7_P0_12= 0x0700 + 2, SctInput7_P1_19= 0x0700 + 3, SctInput7_P1_30= 0x0700 + 4,   
}SCT0_InputChannel_t;


 
/** 
  * @brief SCT0ģ�� ���ͨ�� 
  */
typedef enum  
{
    //SCT0ͨ��     �ܽ�  ��ѡ�ܽ� ����2019      
    SctOutPut0_P0_2 = 0x0000 + 1, SctOutPut0_P0_17= 0x0000 + 2, SctOutPut0_P1_4 = 0x0000 + 3, SctOutPut0_P1_23= 0x0000 + 4, 
    SctOutPut1_P0_3 = 0x0100 + 1, SctOutPut1_P0_18= 0x0100 + 2, SctOutPut1_P1_8 = 0x0100 + 3, SctOutPut1_P1_24= 0x0100 + 4, 
    SctOutPut2_P0_15= 0x0200 + 1, SctOutPut2_P0_19= 0x0200 + 2, SctOutPut2_P1_9 = 0x0200 + 3, SctOutPut2_P1_25= 0x0200 + 4, 
    SctOutPut3_P0_22= 0x0300 + 1, SctOutPut3_P0_31= 0x0300 + 2, SctOutPut3_P1_10= 0x0300 + 3, SctOutPut3_P1_26= 0x0300 + 4, 
    SctOutPut4_P0_23= 0x0400 + 1, SctOutPut4_P1_3 = 0x0400 + 2, SctOutPut4_P1_17= 0x0400 + 3, 
    SctOutPut5_P0_26= 0x0500 + 1, SctOutPut5_P1_18= 0x0500 + 2, 
    SctOutPut6_P0_27= 0x0600 + 1, SctOutPut6_P1_31= 0x0600 + 2,
    SctOutPut7_P0_28= 0x0700 + 1, SctOutPut7_P1_19= 0x0700 + 2,
    SctOutPut8_P0_29= 0x0800 + 1, 
    SctOutPut9_P0_30= 0x0900 + 1, 
} SCT0_OutChnannel_t;



#define SCT_PWM_MAX                  10000     /*!< PWMռ�ձ�������ֵ */
#define PWM_SCT_EVENT_PERIOD         9         /*!< ���������¼���һ��10���¼�0-9��,����ȷ�����PWM������ֵ��*/
#define CAMERA_SCT_EVENT_PCLK        8         /*!< ����ͷPCLK�ܴ���DMA���¼���һ��10���¼�0-9�� */


/*!
  * @brief    SCT ���PWM��ʼ��
  *
  * @param    channel    �� SCTͨ��  LQ_SCTIME.h �пɵ�ö����
  * @param    frequency  �� Ƶ��  ע��SCT�����PWMƵ�ʱ���һ��
  * @param    duty       �� ռ�ձȰٷ�֮ duty/SCT_PWM_MAX *100  
  *
  * @return   ��
  *
  * @note     SCT���10���¼�������һ���¼�����PWM���ڣ������Ÿ��¼����Բ���9·Ƶ����ͬ��PWM
  * @note     ��������ͷҲ��Ҫ�õ�SCT���¼������ʹ�����۴�����ŵ�ת��������ɫ������Ҫһ�������¼�������ͷ����ͬ���źŴ���DMA������ֻ�����8·PWM
  * @note     ���ʹ�������ϰ�ת��������OV7725������Ҫ����������¼� ����������8·PWM�ˡ�
  *
  * @see      SCT_InitPwmConfig(SctOutPut0_P0_2, 18000, 500); //����ͨ��0 P0_2���Ƶ�� 18000 ռ�ձȰٷ�֮ 500/SCT_PWM_MAX *100
  *
  * @date     2019/10/21 ����һ
  */
void SCT_InitPwmConfig(SCT0_OutChnannel_t channel, uint32_t frequency, uint32_t duty);



/**
  * @brief    SCT ����PWMռ�ձ�
  *
  * @param    channel    �� SCTͨ��  LQ_SCTIME.h �е�ö����
  * @param    duty       �� ռ�ձȰٷ�֮ duty/SCT_PWM_MAX *100
  *
  * @return   ��
  *
  * @note     ʹ��ǰ��Ҫ��ʼ��
  *
  * @example  SCT_PwmSetDuty(SctOutPut0_P0_2, 500);  //����ͨ��0 P0_2���ռ�ձȰٷ�֮ 500/SCT_PWM_MAX *100
  *
  * @date     2019/5/8 ������
  */
void SCT_PwmSetDuty(SCT0_OutChnannel_t channel, uint32_t duty);




/*!
  * @brief    SCT ����ܽŴ���DMA��ʼ��
  *
  * @param    channel  :  SCT����ͨ��  LQ_SCTIME.h �е�ö����
  *
  * @return   ��
  *
  * @note     SCT���10���¼�������һ���¼�����PWM���ڣ������Ÿ��¼����Բ���9·Ƶ����ͬ��PWM
  * @note     ��������ͷҲ��Ҫ�õ�SCT���¼������ʹ�����۴�����ŵ�ת��������Ҫһ�������¼�������ͷ����ͬ���źŴ���DMA������ֻ�����8·PWM
  * @note     ���ʹ�������ϰ�ת��������OV7725���Ͳ���������8·PWM�ˡ�   
  *
  * @see      SCT_InitCameraConfig(SctInput0_P0_0);  //��������ͨ��0 P0_0��Ϊ����ͷpclk�ӿ�
  *
  * @date     2019/10/22 ���ڶ�
  */
void SCT_InitCameraConfig(SCT0_InputChannel_t channel);


/*!
  * @brief    SCT ������������
  *
  * @param    channel  : SCT����ͨ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      SCT_CapPinInit(SctInput0_P1_5);  //��ʼ��P1_5 ���ܸ���ΪSCT����
  *
  * @date     2019/5/8 ������
  */
void SCT_CapPinInit(SCT0_InputChannel_t channel);


/*!
  * @brief    SCT PWM�����������
  *
  * @param    SCT0_Chn  : PWM���ͨ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      SCT_PwmPinInit(SctOutPut0_P0_2); //��ʼ�� P0_2 ���ܸ���ΪSCT���
  *
  * @date     2019/5/8 ������
  */
void SCT_PwmPinInit(SCT0_OutChnannel_t SCT0_Chn);

#endif
