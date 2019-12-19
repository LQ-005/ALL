/*!
  * @file     TEST_PWM.c
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
#include "config.h"
#include "TEST_PWM.h"
#include "LQ_CTIME.h"
#include "LQ_SCTIME.h"
#include "LQ_KEY.h"
#include "LQ_LED.h"
#include "LQ_SGP18T.h"
#include "LQ_12864.h"
#include "LQ_UART.h"
#include "stdio.h"
#include "fsl_debug_console.h"
/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


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
void PWM_SetServoDuty(uint16_t duty)    
{
    if(duty > 850) duty = 850;    //�޷����������޸�
    if(duty < 650) duty = 650;
    CTIMER_SetDuty(CT1Output0_P1_10, duty);
}

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
void TEST_Servo(void)
{
    /* ���PWM ��ʼ�� */
    CTIMER_InitPwmConfig(CT1Output0_P1_10, 0, 50);
    
    LED_Init();
    KEY_Init();
    UART_InitConfig(USART0, 115200);
#ifdef TFT1_8
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    TFTSPI_P8X16Str(3,0,"LQ Motor PWM",u16RED,u16BLUE);
#else
    LCD_Init();
    LCD_CLS();                     //LCD����  
    LCD_P8x16Str(13,0,"LQ Servo PWM");
#endif

    char txt[16];
    int servopwm = 750; 
    float time = 0;
    
    while (1)
    {      
        switch(KEY_Read(1))  //��ⰴ�� mode:0������mode:1����
        {
            case 0:
            break;
            case 1:
                servopwm -= 10;   
				if(servopwm < 650) servopwm = 650;     //�޷����������޸�
                PWM_SetServoDuty(servopwm);//ˢ��servopwmƵ��
                break;           
            case 2:           
                servopwm = 750;
                PWM_SetServoDuty(servopwm);//ˢ��servopwmƵ��
                break;
            case 3:           
                servopwm += 10;
				if(servopwm > 850) servopwm = 850; 
                PWM_SetServoDuty(servopwm);//ˢ��servopwmƵ��
                break;
        }
        time=(servopwm)*20.0/10000;
        sprintf(txt,"Time:%4.3fms",time);
#ifdef TFT1_8        
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
#else        
        LCD_P8x16Str(2,3,txt);
#endif  
        printf(txt); 
        
        //LED��˸
        LED_ColorReverse(red);      
        delayms(50);
    }
    
}


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
void PWM_SetMotorDuty(uint8_t num, short duty)
{
    /* ��ֹPWMԽ�� */
    assert(abs(duty) < SCT_PWM_MAX);
    switch(num)
    {
      case 1:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut5_P0_26, 0);
                SCT_PwmSetDuty(SctOutPut4_P1_17, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut5_P0_26, -duty);
                SCT_PwmSetDuty(SctOutPut4_P1_17, 0);
            }
        }
        break;
        
        case 2:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut7_P0_28, 0);
                SCT_PwmSetDuty(SctOutPut6_P0_27, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut7_P0_28, -duty);
                SCT_PwmSetDuty(SctOutPut6_P0_27, 0);
            }
        }
        break;
        
        case 3:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut2_P0_19, 0);
                SCT_PwmSetDuty(SctOutPut3_P0_22, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut2_P0_19, -duty);
                SCT_PwmSetDuty(SctOutPut3_P0_22, 0);
            }
        }
        break;
        
        case 4:
        {
            if(duty > 0)
            {
                SCT_PwmSetDuty(SctOutPut1_P0_18, 0);
                SCT_PwmSetDuty(SctOutPut0_P0_17, duty);
            }
            else
            {
                SCT_PwmSetDuty(SctOutPut1_P0_18, -duty);
                SCT_PwmSetDuty(SctOutPut0_P0_17, 0);
            }
        }
        break;
    }

}

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
void TEST_MOTOR(void)
{
    /* ��ʼ��PWM */
    SCT_InitPwmConfig(SctOutPut0_P0_17, 18000, 0);
    SCT_InitPwmConfig(SctOutPut1_P0_18, 18000, 0);
    SCT_InitPwmConfig(SctOutPut2_P0_19, 18000, 0);
    SCT_InitPwmConfig(SctOutPut3_P0_22, 18000, 0);
    SCT_InitPwmConfig(SctOutPut4_P1_17, 18000, 0);
    SCT_InitPwmConfig(SctOutPut5_P0_26, 18000, 0);
    SCT_InitPwmConfig(SctOutPut6_P0_27, 18000, 0);
    SCT_InitPwmConfig(SctOutPut7_P0_28, 18000, 0);
    
    LED_Init();
    KEY_Init();
    UART_InitConfig(USART0, 115200);
#ifdef TFT1_8
    TFTSPI_Init(1);                //TFT1.8��ʼ��  
    TFTSPI_CLS(u16BLUE);           //����
    TFTSPI_P8X16Str(3,0,"LQ Motor PWM",u16RED,u16BLUE);
#else
    LCD_Init();
    LCD_CLS();                     //LCD����  
    LCD_P8x16Str(13,0,"LQ Servo PWM");
#endif
    char txt[16];
    short motorpwm=0;   
    
    while (1)
    {        
        switch(KEY_Read(1))  //��ⰴ��
        {
            case 0:
                break;
            case 1:
                motorpwm -= 100;
                if(motorpwm < -10000) motorpwm = -10000;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
                break;           
            case 3:           
                motorpwm += 100;
                if(motorpwm > 10000) motorpwm = 10000;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
                break;
            case 2:
                motorpwm = 0;
                PWM_SetMotorDuty(1, motorpwm);
                PWM_SetMotorDuty(2, motorpwm);
                PWM_SetMotorDuty(3, motorpwm);
                PWM_SetMotorDuty(4, motorpwm);
            break;
        }
        
        sprintf(txt,"PWM: %4.2f %%",motorpwm/100.0f);
#ifdef TFT1_8        
        TFTSPI_P8X16Str(3,3,txt,u16RED,u16BLUE);
#else        
        LCD_P8x16Str(2,3,txt);
#endif       
        printf(txt); 
        
        //LED��˸
        LED_ColorReverse(red);     
        delayms(50);
    }
}
