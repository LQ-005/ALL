/*!
  * @file     LQ_GPIO.c
  *
  * @brief    GPIO�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_clock.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"
#include "LQ_GPIO.h"


/*!
  * @brief    ����IO���ù���
  *
  * @param    pin      �� �ܽű��    LQ_GPIO.h�ж���
  * @param    mode     �� GPIO ģʽ   LQ_GPIO.h�еĺ궨����ѡ��   
  *
  * @return   ��
  *
  * @note     ÿ��IO���8�ָ��� ���ù��ܾ�����Բ鿴RM�ֲ� �ھ���IOCON��󲿷�
  *
  * @see      PIN_MuxSet(P0_0, PIN_MODE_OUTPUT); //P0_0�ܽ�����ΪGPIO�����������
  *
  * @date     2019/10/18 ������
  */
void PIN_MuxSet(GPIO_Name_t pin, uint32_t mode)
{
    /* ���� ʱ�� */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    /* ���� ���� */
    IOCON_PinMuxSet(IOCON, PTx(pin), PTn(pin), mode);
}




/*!
  * @brief    GPIO��ʼ��
  *
  * @param    pin      �� �ܽű��  LQ_GPIO.h�ж���
  * @param    mode     �� GPIO ģʽ   LQ_GPIO.h�еĺ궨����ѡ��
  * @param    output   �� ���ģʽʱ�������ƽ 1���ߵ�ƽ  0���͵�ƽ   
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      PIN_InitConfig(P0_0, PIN_MODE_OUTPUT, 1);  //P0_0��ʼ��������� �ߵ�ƽ
  *
  * @date     2019/10/18 ������
  */
void PIN_InitConfig(GPIO_Name_t pin, uint32_t mode, uint8_t output)
{
    /* ���ø��ù��� */
    PIN_MuxSet(pin, mode);
    
    gpio_pin_config_t pin_config_t;
    
    /* IO���� */
    pin_config_t.pinDirection = (gpio_pin_direction_t)((mode & 0x8000000)>>27);
    
    /* �����ƽ */
    pin_config_t.outputLogic = output;
   
    /* ��GPIOʱ�� */
    if(0 == PTx(pin))
    {
        CLOCK_EnableClock(kCLOCK_Gpio0);
    }
    else if(1 == PTx(pin))
    {
        CLOCK_EnableClock(kCLOCK_Gpio1);
    }

    /* ��ʼ��GPIO */
    GPIO_PinInit(GPIO, PTx(pin), PTn(pin), &pin_config_t);
}

/*!
  * @brief    GPIO��ʼ��
  *
  * @param    pin      �� �ܽű��  LQ_GPIO.h�ж���  
  *
  * @return   ��ȡ�ĵ�ƽ  1���ߵ�ƽ  0���͵�ƽ   
  *
  * @note     ʹ��ǰ�ȳ�ʼ��IO
  *
  * @see      PIN_Read(P0_0, PIN_MODE_OUTPUT, 1);  //P0_0��ʼ��������� �ߵ�ƽ
  *
  * @date     2019/10/18 ������
  */
uint8_t PIN_Read(GPIO_Name_t pin)
{
    return GPIO->B[PTx(pin)][PTn(pin)];
}

/*!
  * @brief    ����GPIO���״̬
  *
  * @param    pin      �� �ܽű�� LQ_GPIO_Cfg.h�ж���
  * @param    output   �� 1:�ߵ�ƽ  0���͵�ƽ
  *
  * @return   ��
  *
  * @note     ʹ��ǰ�ȳ�ʼ��IO
  *
  * @example  PIN_Write(P0_0, 1);//P0_0��Ϊ�ߵ�ƽ
  *
  * @date     2019/8/19 ����һ
  */
void PIN_Write(GPIO_Name_t pin, uint8_t output)
{
    uint8_t ptx = PTx(pin);
    uint8_t ptn = PTn(pin);
    GPIO->B[ptx][ptn] = output;
}


/*!
  * @brief    ����GPIO�������
  *
  * @param    pin      �� �ܽű�� LQ_GPIO_Cfg.h�ж���
  * @param    mode     �� 1:���  0������
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ��
  *
  * @example  PIN_Dir(P0_0, 1);//P0_0����Ϊ���
  *
  * @date     2019/8/19 ����һ
  */
void PIN_Dir(GPIO_Name_t pin, uint8_t mode)
{ 
    if(0 == mode)
    {
        GPIO->DIR[PTx(pin)] &= ~((uint32_t)(1<<PTn(pin)));
    }
    else
    {
        GPIO->DIR[PTx(pin)] |= 1<<PTn(pin);
    }
}

/*!
  * @brief    GPIO��ת����
  *
  * @param    pin      �� �ܽű�� LQ_GPIO_Cfg.h�ж���
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ��
  *
  * @see      PIN_Reverse(P0_0); //��תP0_0�ܽ�
  *
  * @date     2019/10/18 ������
  */
void PIN_Reverse(GPIO_Name_t pin)
{
    GPIO->NOT[PTx(pin)]  = 1<<PTn(pin);
}


/*!
  * @brief    GPIO�ⲿ�жϳ�ʼ��
  *
  * @param    pin      �� �ܽű�� LQ_GPIO_Cfg.h�ж���
  * @param    mode     �� GPIO �ж�ģʽ   LQ_GPIO.h�еĺ궨����ѡ��
  * @param    Channel  �� ʹ�õ��ⲿ�ж�ͨ�� 0-7
  *
  * @return   ��
  *
  * @note     LPC54606һ����8���ⲿ�жϣ����йܽŶ��������ӵ���8���ⲿ�ж��� 
  *
  * @example  PIN_Exti(P0_0, 0, PIN_IRQ_MODE_FALLING);//����P0_0 �½��ش����ж�
  * @example  ���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
  * @example  NVIC_SetPriority(PIN_INT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @example  EnableIRQ(PIN_INT0_IRQn);			          //ʹ���ⲿ�ж�ͨ�� 0   
  *
  * @date     2019/8/19 ����һ
  */
void PIN_Exti(GPIO_Name_t pin, uint8_t Channel, uint8_t mode)
{
    assert(Channel < 8);
    uint32_t temp = 0;
    
    if(mode == PIN_IRQ_MODE_RISING || mode == PIN_IRQ_MODE_HIGH_LEVEL)
    {
        temp = PIN_MODE_INPUT_PULLDOWN;
    }
    else if(mode == PIN_IRQ_MODE_FALLING || mode == PIN_IRQ_MODE_LOW_LEVEL)
    {
        temp = PIN_MODE_INPUT_PULLUP;
    }
    else
    {
        temp = PIN_MODE_INPUT;
    }
    /* ��ʼ�� IO״̬ */
    PIN_MuxSet(pin, temp);

    static uint8_t count = 0;
    if(0 == count)
    {
        count ++;
        
        // ��ʼ��PINT 
        PINT_Init(PINT);
        
        /* �жϸ�������ʼ�� */
        INPUTMUX_Init(INPUTMUX);
    }

    /* ���ܽ����ӵ���Ӧ���ж�ͨ���� */
    INPUTMUX_AttachSignal(INPUTMUX, (pint_pin_int_t)Channel, (inputmux_connection_t)(pin + (PINTSEL_PMUX_ID << PMUX_SHIFT)));   

    // ���ùܽŴ�����ʽ �� �жϺ��� 
    PINT_PinInterruptConfig(PINT, (pint_pin_int_t)Channel, (pint_pin_enable_t)mode, NULL);

    // �����־λ
    PINT_PinInterruptClrStatusAll(PINT);
}

