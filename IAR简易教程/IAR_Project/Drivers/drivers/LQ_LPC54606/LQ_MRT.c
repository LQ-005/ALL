/*!
  * @file     LQ_MRT.c
  *
  * @brief    MRT��ʱ��
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
#include "fsl_clock.h"
#include "LQ_MRT.h"


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
void MRT_InitConfig(mrt_chnl_t channel, uint32_t us)
{
    /* У׼ֵ */
//    us += (us/500)+1;
    
    uint32_t mrt_clock;
    
    /* MRT��ʼ���ṹ�� */
    mrt_config_t mrtConfig;    
    
    /* ��ȡMRTʱ��Ƶ�� */
    mrt_clock =CLOCK_GetFreq(kCLOCK_BusClk);
    
    /* ��ȡMRT��ʼ��Ĭ�ϲ��� */
    MRT_GetDefaultConfig(&mrtConfig);

    static uint8_t count = 0;
    
    /* ��ֹ��γ�ʼ�� */
    if(count == 0)
    {
        count++;
        /* Init mrt module */
        MRT_Init(MRT0, &mrtConfig);
    }
    
    
    /* ����ͨ��ģʽ */
    MRT_SetupChannelMode(MRT0, channel, kMRT_RepeatMode);

    /* ʹ���ж� */
    MRT_EnableInterrupts(MRT0, channel, kMRT_TimerInterruptEnable);
    
    //΢�룬ticksINTVAL���ֵΪ0xFFFFFFU  
    MRT_StartTimer(MRT0, channel, USEC_TO_COUNT(us, mrt_clock));
    //����
    //MRT_StartTimer(MRT0, channel, MSEC_TO_COUNT(250000U, mrt_clock));   
}

