/*!
  * @file     LQ_SCTIME.c
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
#include "fsl_iocon.h"
#include "fsl_sctimer.h"
#include "fsl_clock.h"
#include "fsl_inputmux.h"
#include "LQ_SCTIME.h"


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
void SCT_InitPwmConfig(SCT0_OutChnannel_t channel, uint32_t frequency, uint32_t duty)
{
    /* �ܽų�ʼ�� */
    SCT_PwmPinInit(channel);
    
	channel = (SCT0_OutChnannel_t)((uint32_t)channel >> 8);
    /* ���÷�Ƶϵ�� */
    uint32_t core_clock = CLOCK_GetFreq(kCLOCK_BusClk);
                           
    uint32_t div = core_clock/(frequency * 0xffff);
    
    if(div > 255)
    {
        assert("����Ƶ�ʹ���");
    }
    
    /* ��ʼ���Ľṹ�� */
    sctimer_config_t config = {
        .enableCounterUnify = false,                   /* SCT������16λ��ʱ�� ���Լ���Ϊ32λ��ʱ�� */
        .clockMode = kSCTIMER_System_ClockMode,         /* SCTʹ���ں�ʱ�� */
        .clockSelect = kSCTIMER_Clock_On_Rise_Input_0,  /* ���ں�ʱ�������ؼ��� */
        .enableBidirection_l = false,                   /* SCT ��16λ������ ���ϼ��� */
        .enableBidirection_h = false,                   /* SCT ��16λ������ ���ϼ��� */
        .prescale_l = div,                               /* SCT ��16λ������ ��Ƶϵ�� */
        .prescale_h = div,                               /* SCT ��16λ������ ��Ƶϵ�� */
        .outInitState = 0U,                              /* SCT ����ܽų�ʼ״̬ */
        .inputsync = 0                                   /* SCT ����ܽų�ʼ״̬ */
    };

    /* ����ʱ�� */
    CLOCK_EnableClock(kCLOCK_Sct0);
    
    /* ���������ʼ���ṹ�����üĴ��� */
    SCT0->CONFIG = SCT_CONFIG_CKSEL(config.clockSelect) | SCT_CONFIG_CLKMODE(config.clockMode) |
                   SCT_CONFIG_UNIFY(config.enableCounterUnify) | SCT_CONFIG_INSYNC(config.inputsync);
    SCT0->CTRL = SCT_CTRL_BIDIR_L(config.enableBidirection_l) | SCT_CTRL_PRE_L(config.prescale_l) |
                 SCT_CTRL_CLRCTR_L_MASK | SCT_CTRL_HALT_L_MASK;
    if (!(config.enableCounterUnify))
    {
        SCT0->CTRL |= SCT_CTRL_BIDIR_H(config.enableBidirection_h) | SCT_CTRL_PRE_H(config.prescale_h) |
                      SCT_CTRL_CLRCTR_H_MASK | SCT_CTRL_HALT_H_MASK;
    }
    
    
    //��ͣSCT �Ա��޸�ĳЩ����Ҫ��ֹͣ״̬�²����޸ĵļĴ���
    SCT0->CTRL |= (SCT_CTRL_HALT_H_MASK | SCT_CTRL_HALT_L_MASK);                  
     
    //PWM��ʼ�� ʹ��ƥ��ģʽ
    SCT0->REGMODE = 0;                                                            

    /* ����ͨ�� SCTһ����ʮ���¼��� һ���¼�����PWM���ڣ����ܲ���PWM
       SCT��16��״̬ ÿ��״̬�¶�����ָ��һЩ�¼����Է�����һЩ�����Է��� */
    /* �κ�״̬�� �����Է��������¼� */
    SCT0->EVENT[PWM_SCT_EVENT_PERIOD].STATE = 0xffff;            
    
    uint32_t period = core_clock/(frequency * (div + 1));                           //���ڼ�������
    uint32_t match_val = (uint32_t)(duty * (double)((double)period / (double)SCT_PWM_MAX));   //����ռ�ձ�ƥ����
    
    /* ���������¼�*/
    SCT0->SCTMATCH[PWM_SCT_EVENT_PERIOD] = period<<SCT_SCTMATCH_MATCHn_H_SHIFT;     //Ϊ ��16λ��ʱ������ ƥ��ֵ 
    SCT0->SCTMATCHREL[PWM_SCT_EVENT_PERIOD] = period<<SCT_SCTMATCH_MATCHn_H_SHIFT;  //Ϊ ��16λ��ʱ������ �Զ�װ��ֵ
    SCT0->EVENT[PWM_SCT_EVENT_PERIOD].CTRL =      SCT_EVENT_CTRL_MATCHSEL(PWM_SCT_EVENT_PERIOD) /* ѡ������¼�������ƥ��Ĵ��� */
                                                | SCT_EVENT_CTRL_HEVENT(1)   /* ��ʹ��State_H״̬�� */
                                                | SCT_EVENT_CTRL_OUTSEL(1)   /* ����Ϊ��� */
                                                | SCT_EVENT_CTRL_IOSEL(PWM_SCT_EVENT_PERIOD) /* ѡ�������ͨ�� */
                                                | SCT_EVENT_CTRL_IOCOND(0)   /* ��Ч����*/
                                                | SCT_EVENT_CTRL_COMBMODE(1) /* ��ʹ��ָ����ƥ����������Ƕ�ʱ��ϵͳ�Ĵ������� */
                                                | SCT_EVENT_CTRL_STATELD(0)  /* ����״̬���ķ�ʽ��ֱ��������ֵ */
                                                | SCT_EVENT_CTRL_STATEV(0)   /* �¼������������µ�״ֵ̬ */
                                                | SCT_EVENT_CTRL_MATCHMEM(0) /* ��������Ч */
                                                | SCT_EVENT_CTRL_DIRECTION(0)/* ��������Ч */
                                                ;
    //�� PWM_SCT_EVENT_PERIOD ���õ����ƼĴ����У���������������PWM_SCT_EVENT_PERIOD��ƥ��ֵʱ������������
    SCT0->LIMIT |= SCT_LIMIT_LIMMSK_H(1U << PWM_SCT_EVENT_PERIOD); 
    
    
    /* �κ�״̬�� �����Է���PWM�¼� */
    SCT0->EVENT[channel].STATE = 0xffff;                                 
    
    /* ����PWMƥ���¼� */
    SCT0->SCTMATCH[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT;                 //channel ͨ�� �ߵ�ƽʱ��
    SCT0->SCTMATCHREL[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT;              //channel ͨ�� ��װ��ֵ
    SCT0->EVENT[channel].CTRL =      SCT_EVENT_CTRL_MATCHSEL(channel) /* ѡ������¼�������ƥ��Ĵ��� */
                                    | SCT_EVENT_CTRL_HEVENT(1)        /* ��ʹ��State_H״̬�� */
                                    | SCT_EVENT_CTRL_OUTSEL(1)        /* ����Ϊ��� */
                                    | SCT_EVENT_CTRL_IOSEL(channel)   /* ѡ�������ͨ�� */
                                    | SCT_EVENT_CTRL_IOCOND(0)        /* ��Ч����*/
                                    | SCT_EVENT_CTRL_COMBMODE(1)      /* ��ʹ��ָ����ƥ����������Ƕ�ʱ��ϵͳ�Ĵ������� */
                                    | SCT_EVENT_CTRL_STATELD(0)       /* ����״̬���ķ�ʽ��ֱ��������ֵ */
                                    | SCT_EVENT_CTRL_STATEV(0)        /* �¼������������µ�״ֵ̬ */
                                    | SCT_EVENT_CTRL_MATCHMEM(0)      /* ��������Ч */
                                    | SCT_EVENT_CTRL_DIRECTION(0)     /* ��������Ч */
                                    ;
    //�����������趨ֵ�� �������� 
    SCT0->OUT[channel].CLR = 1<<channel;                                  
   
    SCT0->RES &= ~((uint32_t)SCT_RES_O0RES_MASK<<(2*channel));                        //��� ͨ��SCT0_Chn��Ӧ�� conflict resolution register
    if(0 == match_val)                                                                 
    {
        SCT0->RES |= 0x2U<<(2*channel);                                               //������ PWM�����¼��������������1��PWMƥ���¼���������������� ͬʱ����Ӧ������
        SCT0->OUT[channel].SET = 1<<channel;                                          //������� 
    }
    else
    {
        SCT0->RES |= 0x1U<<(2*channel);                                               //������� //�������¼�(����ͬһ���¼�)Ҫ��ͬʱ���ú�����������������Ӧ�ò�ȡ�����������
        SCT0->OUT[channel].SET = 1<<PWM_SCT_EVENT_PERIOD;                             //�������
    }

    SCT0->CTRL &= ~(SCT_CTRL_HALT_L_MASK | SCT_CTRL_HALT_H_MASK);      /* ����״̬�� */

}



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
void SCT_PwmSetDuty(SCT0_OutChnannel_t channel, uint32_t duty)
{
    assert(duty<=SCT_PWM_MAX); 
    uint32_t period;                              //���ڼ�������
    uint32_t match_val;                           //ƥ��ֵ
    channel = (SCT0_OutChnannel_t)((uint32_t)channel >> 8); 
    period = SCT0->SCTMATCHREL[PWM_SCT_EVENT_PERIOD]>>SCT_SCTMATCHREL_RELOADn_H_SHIFT;  //ȡ�����ڼ������� ��ʼ��ʱ���ù�
    match_val = duty * period / SCT_PWM_MAX;                                            //����ռ�ձ�ƥ����
                    
    SCT0->RES &= ~((uint32_t)SCT_RES_O0RES_MASK<<(2*channel));           //��� ͨ��SCT0_Chn��Ӧ�� conflict resolution register
    if(0 == match_val)
    {
        SCT0->RES |= 0x2U<<(2*channel);                                  //������ PWM�����¼��������������1��PWMƥ���¼���������������� ͬʱ����Ӧ������
        SCT0->OUT[channel].SET = 1<<channel;                             //������� 
    }                                                                                   
    else                                                                                
    {                                                                                   
        SCT0->RES |= 0x1U<<(2*channel);                                  //�������//�������¼�(����ͬһ���¼�)Ҫ��ͬʱ���ú�����������������Ӧ�ò�ȡ�����������
        SCT0->OUT[channel].SET = 1<<PWM_SCT_EVENT_PERIOD;                //�������
    }

    SCT0->SCTMATCHREL[channel] = match_val<<SCT_SCTMATCH_MATCHn_H_SHIFT; //����ƥ��ֵ
}

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
void SCT_InitCameraConfig(SCT0_InputChannel_t channel)
{

    SCT_CapPinInit(channel);

	channel = (SCT0_InputChannel_t)((uint32_t)channel >> 8);
    /* ��·��������ʼ�� */
    INPUTMUX_Init(INPUTMUX);
    
    /* ���ܽ����ӵ���Ӧ��SCTͨ���� */
    INPUTMUX->SCT0_INMUX[channel] = INPUTMUX_SCT0_INMUX_INP_N(channel);      
    
    /* ��ʼ���Ľṹ�� */
    sctimer_config_t config = {
        .enableCounterUnify = false,                   /* SCT������16λ��ʱ�� ���Լ���Ϊ32λ��ʱ�� */
        .clockMode = kSCTIMER_System_ClockMode,         /* SCTʹ���ں�ʱ�� */
        .clockSelect = kSCTIMER_Clock_On_Rise_Input_0,  /* ���ں�ʱ�������ؼ��� */
        .enableBidirection_l = false,                   /* SCT ��16λ������ ���ϼ��� */
        .enableBidirection_h = false,                   /* SCT ��16λ������ ���ϼ��� */
        .prescale_l = 0,                                /* SCT ��16λ������ ��Ƶϵ�� */
        .prescale_h = 0,                                /* SCT ��16λ������ ��Ƶϵ�� */
        .outInitState = 0U,                              /* SCT ����ܽų�ʼ״̬ */
        .inputsync = (1U << channel)                     /* SCT ����ܽų�ʼ״̬ */
    };
    
    /* ����ʱ�� */
    CLOCK_EnableClock(kCLOCK_Sct0);
    
    /* ���������ʼ���ṹ�����üĴ��� */
    SCT0->CONFIG = SCT_CONFIG_CKSEL(config.clockSelect) | SCT_CONFIG_CLKMODE(config.clockMode) |
                   SCT_CONFIG_UNIFY(config.enableCounterUnify) | SCT_CONFIG_INSYNC(config.inputsync);

    //��ͣSCT �Ա��޸�ĳЩ����Ҫ��ֹͣ״̬�²����޸ĵļĴ���
    SCT0->CTRL |= (SCT_CTRL_HALT_H_MASK | SCT_CTRL_HALT_L_MASK);  
    
    //״̬����
    SCT0->STATE = (SCT0->STATE & SCT_STATE_STATE_H_MASK) | SCT_STATE_STATE_L(0U);   
    
    /* �κ�״̬�� �����Է���PCLK�¼� */
    SCT0->EVENT[CAMERA_SCT_EVENT_PCLK].STATE = 0xffff;                    
    SCT0->EVENT[CAMERA_SCT_EVENT_PCLK].CTRL = ( 0 
                                    | SCT_EVENT_CTRL_HEVENT(0)                      /* ��ʹ��State_L״̬�� */
                                    | SCT_EVENT_CTRL_OUTSEL(0)                      /* �����������ŵĴ��� */
                                    | SCT_EVENT_CTRL_IOSEL(channel)                 /* ����PCLK�������ŵĴ��� */
                                    | SCT_EVENT_CTRL_IOCOND(1)                      /* ����ʱ��Ϊ���������� 1��������    2���½��� */  
                                    | SCT_EVENT_CTRL_COMBMODE(2)                    /* ��ʹ��IO���Ų����Ĵ����źţ��������Ƕ�ʱ��ϵͳ�Ĵ������� */
                                    | SCT_EVENT_CTRL_STATELD(1)                     /* ����״̬���ķ�ʽ��ֱ��������ֵ */
                                    | SCT_EVENT_CTRL_STATEV(1)                      /* �¼������������µ�״ֵ̬ */   
                                    | SCT_EVENT_CTRL_MATCHMEM(0)                    /* ��������Ч */
                                    | SCT_EVENT_CTRL_DIRECTION(0)                   /* ��������Ч */

                                    );
    SCT0->DMA0REQUEST = SCT_DMA0REQUEST_DEV_0(1U<<CAMERA_SCT_EVENT_PCLK);            //ʹ��PCLK�¼�����DMA
                      
    SCT0->CTRL &= ~(SCT_CTRL_HALT_L_MASK | SCT_CTRL_HALT_H_MASK);                    /* ����״̬�� */
    
}



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
void SCT_CapPinInit(SCT0_InputChannel_t channel)
{
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    switch(channel)
    {
      case SctInput0_P0_24:
        PIN_MuxSet(P0_24, PIOFun4_config);
        break;
      case SctInput0_P0_13:
        PIN_MuxSet(P0_13, PIOFun4_config);
        break;
      case SctInput0_P1_5:
        PIN_MuxSet(P1_5,  PIOFun4_config);
        break;  
      case SctInput0_P0_0:
        PIN_MuxSet(P0_0,  PIOFun4_config);
        break;  
      case SctInput1_P0_1:
        PIN_MuxSet(P0_1,  PIOFun4_config);
        break; 
      case SctInput1_P0_25:
        PIN_MuxSet(P0_25, PIOFun4_config);
        break;
      case SctInput2_P0_20:
        PIN_MuxSet(P0_20, PIOFun4_config);
        break;  
      case SctInput2_P0_2:
        PIN_MuxSet(P0_2,  PIOFun4_config);
        break;  
      case SctInput3_P1_6:
        PIN_MuxSet(P1_6,  PIOFun4_config);
        break;
      case SctInput3_P0_21:
        PIN_MuxSet(P0_21, PIOFun4_config);
        break;
      case SctInput3_P0_3:
        PIN_MuxSet(P0_3,  PIOFun4_config);
        break;  
      case SctInput4_P1_7:
        PIN_MuxSet(P1_7,  PIOFun4_config);
        break;
      case SctInput4_P1_0:
        PIN_MuxSet(P1_0,  PIOFun4_config);
        break;
      case SctInput4_P0_4:
        PIN_MuxSet(P0_4,  PIOFun4_config);
        break;
      case SctInput5_P0_5:
        PIN_MuxSet(P0_5,  PIOFun4_config);
        break;
      case SctInput5_P1_22:
        PIN_MuxSet(P1_22, PIOFun4_config);
        break;
      case SctInput5_P1_1:
        PIN_MuxSet(P1_1,  PIOFun4_config);
        break;
      case SctInput6_P1_2:
        PIN_MuxSet(P1_2,  PIOFun4_config);
        break;
      case SctInput6_P1_29:
        PIN_MuxSet(P1_29, PIOFun3_config);
        break;
      case SctInput6_P0_6:
        PIN_MuxSet(P0_6,  PIOFun4_config);
        break;
      case SctInput7_P1_19:
        PIN_MuxSet(P1_19, PIOFun4_config);
        break;
      case SctInput7_P1_30:
        PIN_MuxSet(P1_30, PIOFun3_config);
        break;
      case SctInput7_P0_12:
        PIN_MuxSet(P0_12, PIOFun4_config);
        break;
      case SctInput7_P0_17:
        PIN_MuxSet(P0_17, PIOFun3_config);
        break;
      default:
        break;
    }
}


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
void SCT_PwmPinInit(SCT0_OutChnannel_t SCT0_Chn)
{   
    uint32_t PIOFun2_config = FUNC2|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    /* ���� ʱ�� */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    switch(SCT0_Chn)
    {
      case SctOutPut0_P0_2:
        IOCON_PinMuxSet(IOCON, 0, 2, PIOFun3_config);
        break;
      case SctOutPut0_P0_17:
        IOCON_PinMuxSet(IOCON, 0,17, PIOFun4_config);
        break;
      case SctOutPut0_P1_4:
        IOCON_PinMuxSet(IOCON, 1, 4, PIOFun4_config);
        break;
      case SctOutPut0_P1_23:
        IOCON_PinMuxSet(IOCON, 1, 23, PIOFun2_config);
        break;
      case SctOutPut1_P0_3:
        IOCON_PinMuxSet(IOCON, 0, 3, PIOFun3_config);
        break;
      case SctOutPut1_P0_18:
        IOCON_PinMuxSet(IOCON, 0,18, PIOFun4_config);
        break;
      case SctOutPut1_P1_8:
        IOCON_PinMuxSet(IOCON, 1, 8, PIOFun4_config);
        break;
      case SctOutPut1_P1_24:
        IOCON_PinMuxSet(IOCON, 1,24, PIOFun2_config);
        break;
      case SctOutPut2_P0_15:
        IOCON_PinMuxSet(IOCON, 0, 15, PIOFun4_config);
        break;
      case SctOutPut2_P0_19:
        IOCON_PinMuxSet(IOCON, 0, 19, PIOFun4_config);
        break;
      case SctOutPut2_P1_9:
        IOCON_PinMuxSet(IOCON, 1, 9, PIOFun4_config);
        break;
      case SctOutPut2_P1_25:
        IOCON_PinMuxSet(IOCON, 1, 25, PIOFun2_config);
        break;
      case SctOutPut3_P0_22:
        IOCON_PinMuxSet(IOCON, 0, 22, PIOFun4_config);
        break;
      case SctOutPut3_P0_31:
        IOCON_PinMuxSet(IOCON, 0, 31, PIOFun4_config);
        break;
      case SctOutPut3_P1_10:
        IOCON_PinMuxSet(IOCON, 1, 10, PIOFun4_config);
        break;
      case SctOutPut3_P1_26:
        IOCON_PinMuxSet(IOCON, 1, 26, PIOFun2_config);
        break;
      case SctOutPut4_P0_23:
        IOCON_PinMuxSet(IOCON, 0, 23, PIOFun4_config);
        break;
      case SctOutPut4_P1_3:
        IOCON_PinMuxSet(IOCON, 1, 3, PIOFun4_config);
        break;
      case SctOutPut4_P1_17:
        IOCON_PinMuxSet(IOCON, 1, 17, PIOFun4_config);
        break;
      case SctOutPut5_P0_26:
        IOCON_PinMuxSet(IOCON, 0, 26, PIOFun4_config);
        break;
      case SctOutPut5_P1_18:
        IOCON_PinMuxSet(IOCON, 1, 18, PIOFun4_config);
        break;
      case SctOutPut6_P0_27:
        IOCON_PinMuxSet(IOCON, 0, 27, PIOFun4_config);
        break;
      case SctOutPut6_P1_31:
        IOCON_PinMuxSet(IOCON, 1, 31, PIOFun4_config);
        break;
      case SctOutPut7_P0_28:
        IOCON_PinMuxSet(IOCON, 0, 28, PIOFun4_config);
        break;
      case SctOutPut7_P1_19:
        IOCON_PinMuxSet(IOCON, 1, 19, PIOFun2_config);
        break;
      case SctOutPut8_P0_29:
        IOCON_PinMuxSet(IOCON, 0, 29, PIOFun4_config);  
        break;
      case SctOutPut9_P0_30:
        IOCON_PinMuxSet(IOCON, 0, 30, PIOFun4_config);      
        break;
    }
}


