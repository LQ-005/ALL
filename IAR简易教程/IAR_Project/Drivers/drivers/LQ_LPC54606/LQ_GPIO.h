/*!
  * @file     LQ_GPIO.h
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
#ifndef __LQ_GPIO_H
#define __LQ_GPIO_H

#include "fsl_gpio.h"

/** 
  * @brief GPIO ö�ٶ˿ڱ��
  */
typedef enum // 
{
    P0_0=0,  P0_1,  P0_2,  P0_3,  P0_4,  P0_5,  P0_6,  P0_7,
    P0_8,    P0_9,  P0_10, P0_11, P0_12, P0_13, P0_14, P0_15,
    P0_16,   P0_17, P0_18, P0_19, P0_20, P0_21, P0_22, P0_23,
    P0_24,   P0_25, P0_26, P0_27, P0_28, P0_29, P0_30, P0_31,
                                                         
    P1_0,    P1_1,  P1_2,  P1_3,  P1_4,  P1_5,  P1_6,  P1_7,
    P1_8,    P1_9,  P1_10, P1_11, P1_12, P1_13, P1_14, P1_15,
    P1_16,   P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23,
    P1_24,   P1_25, P1_26, P1_27, P1_28, P1_29, P1_30, P1_31,

}GPIO_Name_t;


/** 
  * @brief GPIO����ö����
  */
typedef enum
{
    /*!< GPIO���ù��� ÿ�ָ��ù��ܾ�����Բ鿴RM�ֲ� �ھ���IOCON��󲿷� */
    FUNC0          = IOCON_PIO_FUNC(0),
    FUNC1          = IOCON_PIO_FUNC(1),
    FUNC2          = IOCON_PIO_FUNC(2),
    FUNC3          = IOCON_PIO_FUNC(3),
    FUNC4          = IOCON_PIO_FUNC(4),
    FUNC5          = IOCON_PIO_FUNC(5),
    FUNC6          = IOCON_PIO_FUNC(6),
    FUNC7          = IOCON_PIO_FUNC(7),
    
    /*!< ��������������  ע�� PT013, PT014 �������������������� */
    MODE_Diaable   =   IOCON_PIO_MODE(0),   /*!< ��ʹ������������ */
    MODE_Down      =   IOCON_PIO_MODE(1),   /*!< ʹ���������� */
    MODE_Up        =   IOCON_PIO_MODE(2),   /*!< ʹ���������� */
    MODE_Repeater  =   IOCON_PIO_MODE(3),   /*!< ʹ��Repeater mode */

    /*!< IICģʽ��GPIOģʽ  PT013, PT014�ſ������� ������⣺�����Ҫ��Ϊ�˸���IIC��Ƶģ�
         һ������£�����ģ���IIC�������400K������Ҫ��ô����IIC�����ϵ�RCֵ�����Ǹ���IIC����Ҫע����Щ��*/
    MODE_IIC       =   IOCON_PIO_I2CSLEW(0), /*!< IICģʽ */
    MODE_GPIO      =   IOCON_PIO_I2CSLEW(1), /*!< GPIOģʽ */
    
    /*!< �źŵ���  */
    INVERT_Disable =   IOCON_PIO_INVERT(0),  /*!< ��ʹ���źŵ��ù��� */
    INVERT_Enable  =   IOCON_PIO_INVERT(1),  /*!< ʹ���źŵ��ù��� */
    
    /*!< ģ������ģʽ  */
    DIGIMODE_Analog=   IOCON_PIO_DIGIMODE(0),/*!< ģ�� ADCģʽ */
    DIGIMODE_Digital=  IOCON_PIO_DIGIMODE(1),/*!< ���� �ź�ģʽ */
    
    /*!< �˲�����  */
    FILTER_Enable  =   IOCON_PIO_FILTEROFF(0),/*!< ���� */
    FILTER_Disable =   IOCON_PIO_FILTEROFF(1),/*!< �ر� */
    
/*----------------------------------------------------------------*/
    /*!< ת������  PT010-PT016��PT023��PT031��PT10������ */
    SLEW_Standard  =   IOCON_PIO_SLEW(0),     /*!< ��׼ģʽ */
    SLEW_Fast      =   IOCON_PIO_SLEW(1),     /*!< ����ģʽ */
    
    /*!< IIC��������  ��PT013, PT014���� �����ת��������ʵ��һ��λ��ֻ����IICģʽ��GPIOģʽ�����ⲻͬ */
    I2CDRIVE_Low   =   IOCON_PIO_I2CDRIVE(0), /*!< һ��ģʽ 4mA*/
    I2CDRIVE_High  =   IOCON_PIO_I2CDRIVE(1), /*!< ������ģʽ 20mA*/
/*----------------------------------------------------------------*/
    
    /*!< ��©ģʽ  PT013, PT014������ */
    OD_Disable     =   IOCON_PIO_OD(0),       /*!< �رտ�©*/
    OD_Enable      =   IOCON_PIO_OD(1),       /*!< ʹ�ܿ�©*/
    
    /*!< IIC 50nsë���˲���  ��PT013, PT014���� */
    I2CFILTER_Disable = IOCON_PIO_I2CFILTER(0),/*!< �ر�*/
    I2CFILTER_Enable  = IOCON_PIO_I2CFILTER(1),/*!< ����*/
    
    
    /* ���� ���(Ϊ����ʹ���Լ���ӵģ��Ĵ�����û�����) */
    OUTPUT               = 0x8000000,    /*!< ��� */
    INPUT                = 0,            /*!< ���� */
    
}PinConfig_t;




/* GPIO�������� */
#define PIN_MODE_OUTPUT         OUTPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable   /*!< �������  */
#define PIN_MODE_INPUT          INPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Enable     /*!< ��������  */
#define PIN_MODE_INPUT_PULLUP   INPUT|FUNC0|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable         /*!< ��������  */
#define PIN_MODE_INPUT_PULLDOWN INPUT|FUNC0|MODE_Down|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Disable       /*!< ��������  */
#define PIN_MODE_OUTPUT_OD      OUTPUT|FUNC0|MODE_Diaable|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable|SLEW_Standard|OD_Enable    /*!< ��©���  */

/* GPIO �жϴ���ģʽ */
#define PIN_IRQ_MODE_RISING             0x01 /*!< �����أ������������ж� */  
#define PIN_IRQ_MODE_FALLING            0x02 /*!< �½��أ������������ж� */
#define PIN_IRQ_MODE_RISING_FALLING     0x03 /*!< ˫���أ���©�������ж� */
#define PIN_IRQ_MODE_LOW_LEVEL          0x04 /*!< �͵�ƽ�������������ж� */
#define PIN_IRQ_MODE_HIGH_LEVEL         0x05 /*!< �ߵ�ƽ�������������ж� */


/* ��ȡ�˿ںͱ�� */
#define PTx(PTX_n)  (PTX_n>>5)  /*!< ��ȡģ��� PTX_n/32 */
#define PTn(PTX_n)  (PTX_n&0x1f)/*!< ��ȡ���ź� PTX_n%32 */

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
void PIN_MuxSet(GPIO_Name_t pin, uint32_t mode);


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
void PIN_InitConfig(GPIO_Name_t pin, uint32_t mode, uint8_t output);



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
uint8_t PIN_Read(GPIO_Name_t pin);



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
void PIN_Write(GPIO_Name_t pin, uint8_t output);



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
void PIN_Dir(GPIO_Name_t pin, uint8_t mode);



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
void PIN_Reverse(GPIO_Name_t pin);



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
void PIN_Exti(GPIO_Name_t pin, uint8_t Channel, uint8_t mode);



/*!
  * @brief    ����51���Ĳ��� ��STM32�е�IO΢��������
  *
  * @param    x ���˿ں�
  *
  * @return   ��
  *
  * @note     ʹ��ǰҪ��ʼ��IO
  *
  * @see      PT0(2) = !PT0(2);  //��תPT0_2 �ܽŵ����״̬
  *
  * @date     2019/10/18 ������
  */
#define PT0(x)    GPIO->B[0][x]
#define PT1(x)    GPIO->B[1][x]

/*! ����PT0_�Ķ˿�  ����51���Ĳ��� */
#define PT0_0     GPIO->B[0][0]
#define PT0_1     GPIO->B[0][1]
#define PT0_2     GPIO->B[0][2]
#define PT0_3     GPIO->B[0][3]
#define PT0_4     GPIO->B[0][4]
#define PT0_5     GPIO->B[0][5]
#define PT0_6     GPIO->B[0][6]
#define PT0_7     GPIO->B[0][7]
#define PT0_8     GPIO->B[0][8]
#define PT0_9     GPIO->B[0][9]
#define PT0_10    GPIO->B[0][10]
#define PT0_11    GPIO->B[0][11]
#define PT0_12    GPIO->B[0][12]
#define PT0_13    GPIO->B[0][13]
#define PT0_14    GPIO->B[0][14]
#define PT0_15    GPIO->B[0][15]
#define PT0_16    GPIO->B[0][16]
#define PT0_17    GPIO->B[0][17]
#define PT0_18    GPIO->B[0][18]
#define PT0_19    GPIO->B[0][19]
#define PT0_20    GPIO->B[0][20]
#define PT0_21    GPIO->B[0][21]
#define PT0_22    GPIO->B[0][22]
#define PT0_23    GPIO->B[0][23]
#define PT0_24    GPIO->B[0][24]
#define PT0_25    GPIO->B[0][25]
#define PT0_26    GPIO->B[0][26]
#define PT0_27    GPIO->B[0][27]
#define PT0_28    GPIO->B[0][28]
#define PT0_29    GPIO->B[0][29]
#define PT0_30    GPIO->B[0][30]
#define PT0_31    GPIO->B[0][31]

/*! ����PT1_�Ķ˿�  */
#define PT1_0     GPIO->B[1][0]
#define PT1_1     GPIO->B[1][1]
#define PT1_2     GPIO->B[1][2]
#define PT1_3     GPIO->B[1][3]
#define PT1_4     GPIO->B[1][4]
#define PT1_5     GPIO->B[1][5]
#define PT1_6     GPIO->B[1][6]
#define PT1_7     GPIO->B[1][7]
#define PT1_8     GPIO->B[1][8]
#define PT1_9     GPIO->B[1][9]
#define PT1_10    GPIO->B[1][10]
#define PT1_11    GPIO->B[1][11]
#define PT1_12    GPIO->B[1][12]
#define PT1_13    GPIO->B[1][13]
#define PT1_14    GPIO->B[1][14]
#define PT1_15    GPIO->B[1][15]
#define PT1_16    GPIO->B[1][16]
#define PT1_17    GPIO->B[1][17]
#define PT1_18    GPIO->B[1][18]
#define PT1_19    GPIO->B[1][19]
#define PT1_20    GPIO->B[1][20]
#define PT1_21    GPIO->B[1][21]
#define PT1_22    GPIO->B[1][22]
#define PT1_23    GPIO->B[1][23]
#define PT1_24    GPIO->B[1][24]
#define PT1_25    GPIO->B[1][25]
#define PT1_26    GPIO->B[1][26]
#define PT1_27    GPIO->B[1][27]
#define PT1_28    GPIO->B[1][28]
#define PT1_29    GPIO->B[1][29]
#define PT1_30    GPIO->B[1][30]
#define PT1_31    GPIO->B[1][31]



/*! ����PT0_��8λ�˿�  */
#define PT0__BYTE0   GPIO->PINs[0].Byte0
#define PT0__BYTE1   GPIO->PINs[0].Byte1
#define PT0__BYTE2   GPIO->PINs[0].Byte2
#define PT0__BYTE3   GPIO->PINs[0].Byte3

#define PT1__BYTE0   GPIO->PINs[1].Byte0
#define PT1__BYTE1   GPIO->PINs[1].Byte1
#define PT1__BYTE2   GPIO->PINs[1].Byte2
#define PT1__BYTE3   GPIO->PINs[1].Byte3

/*! ����PT0_��������뷽��  */
#define PT0_0_DIR     GPIO->DIRs[0].BIT0
#define PT0_1_DIR     GPIO->DIRs[0].BIT1
#define PT0_2_DIR     GPIO->DIRs[0].BIT2
#define PT0_3_DIR     GPIO->DIRs[0].BIT3
#define PT0_4_DIR     GPIO->DIRs[0].BIT4
#define PT0_5_DIR     GPIO->DIRs[0].BIT5
#define PT0_6_DIR     GPIO->DIRs[0].BIT6
#define PT0_7_DIR     GPIO->DIRs[0].BIT7
#define PT0_8_DIR     GPIO->DIRs[0].BIT8
#define PT0_9_DIR     GPIO->DIRs[0].BIT9
#define PT0_10_DIR    GPIO->DIRs[0].BIT10
#define PT0_11_DIR    GPIO->DIRs[0].BIT11
#define PT0_12_DIR    GPIO->DIRs[0].BIT12
#define PT0_13_DIR    GPIO->DIRs[0].BIT13
#define PT0_14_DIR    GPIO->DIRs[0].BIT14
#define PT0_15_DIR    GPIO->DIRs[0].BIT15
#define PT0_16_DIR    GPIO->DIRs[0].BIT16
#define PT0_17_DIR    GPIO->DIRs[0].BIT17
#define PT0_18_DIR    GPIO->DIRs[0].BIT18
#define PT0_19_DIR    GPIO->DIRs[0].BIT19
#define PT0_20_DIR    GPIO->DIRs[0].BIT20
#define PT0_21_DIR    GPIO->DIRs[0].BIT21
#define PT0_22_DIR    GPIO->DIRs[0].BIT22
#define PT0_23_DIR    GPIO->DIRs[0].BIT23
#define PT0_24_DIR    GPIO->DIRs[0].BIT24
#define PT0_25_DIR    GPIO->DIRs[0].BIT25
#define PT0_26_DIR    GPIO->DIRs[0].BIT26
#define PT0_27_DIR    GPIO->DIRs[0].BIT27
#define PT0_28_DIR    GPIO->DIRs[0].BIT28
#define PT0_29_DIR    GPIO->DIRs[0].BIT29
#define PT0_30_DIR    GPIO->DIRs[0].BIT30
#define PT0_31_DIR    GPIO->DIRs[0].BIT31

/*! ����PT1_��������뷽��   */
#define PT1_0_DIR     GPIO->DIRs[1].BIT0
#define PT1_1_DIR     GPIO->DIRs[1].BIT1
#define PT1_2_DIR     GPIO->DIRs[1].BIT2
#define PT1_3_DIR     GPIO->DIRs[1].BIT3
#define PT1_4_DIR     GPIO->DIRs[1].BIT4
#define PT1_5_DIR     GPIO->DIRs[1].BIT5
#define PT1_6_DIR     GPIO->DIRs[1].BIT6
#define PT1_7_DIR     GPIO->DIRs[1].BIT7
#define PT1_8_DIR     GPIO->DIRs[1].BIT8
#define PT1_9_DIR     GPIO->DIRs[1].BIT9
#define PT1_10_DIR    GPIO->DIRs[1].BIT10
#define PT1_11_DIR    GPIO->DIRs[1].BIT11
#define PT1_12_DIR    GPIO->DIRs[1].BIT12
#define PT1_13_DIR    GPIO->DIRs[1].BIT13
#define PT1_14_DIR    GPIO->DIRs[1].BIT14
#define PT1_15_DIR    GPIO->DIRs[1].BIT15
#define PT1_16_DIR    GPIO->DIRs[1].BIT16
#define PT1_17_DIR    GPIO->DIRs[1].BIT17
#define PT1_18_DIR    GPIO->DIRs[1].BIT18
#define PT1_19_DIR    GPIO->DIRs[1].BIT19
#define PT1_20_DIR    GPIO->DIRs[1].BIT20
#define PT1_21_DIR    GPIO->DIRs[1].BIT21
#define PT1_22_DIR    GPIO->DIRs[1].BIT22
#define PT1_23_DIR    GPIO->DIRs[1].BIT23
#define PT1_24_DIR    GPIO->DIRs[1].BIT24
#define PT1_25_DIR    GPIO->DIRs[1].BIT25
#define PT1_26_DIR    GPIO->DIRs[1].BIT26
#define PT1_27_DIR    GPIO->DIRs[1].BIT27
#define PT1_28_DIR    GPIO->DIRs[1].BIT28
#define PT1_29_DIR    GPIO->DIRs[1].BIT29
#define PT1_30_DIR    GPIO->DIRs[1].BIT30
#define PT1_31_DIR    GPIO->DIRs[1].BIT31

#endif



