/*!
  * @file     LQ_LED.c
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
#include "LQ_GPIO.h"
#include "LQ_LED.h"


/** �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);




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
void LED_Init(void)
{
    PIN_InitConfig(LED_R_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_G_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_B_PIN,  PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_D0_PIN, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(LED_D1_PIN, PIN_MODE_OUTPUT, 0);
    
}



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
void LED_Color(LED_t color)
{
    switch(color)
    {
        case white:
            PIN_Write(LED_G_PIN,  0U);//LED��; 
            PIN_Write(LED_R_PIN,  0U);//LED��; 
            PIN_Write(LED_B_PIN,  0U);//LED��; 
            break;
        case black:
            PIN_Write(LED_G_PIN,  1U);//LED��; 
            PIN_Write(LED_R_PIN,  1U);//LED��; 
            PIN_Write(LED_B_PIN,  1U);//LED��; 
            break;
        case red:
            PIN_Write(LED_G_PIN,  1U);//LED��; 
            PIN_Write(LED_R_PIN,  0U);//LED��; 
            PIN_Write(LED_B_PIN,  1U);//LED��; 
            break;
        case green:
            PIN_Write(LED_G_PIN,  0U);//LED��; 
            PIN_Write(LED_R_PIN,  1U);//LED��; 
            PIN_Write(LED_B_PIN,  1U);//LED��; 
            break;
        case blue:
            PIN_Write(LED_G_PIN,  1U);//LED��; 
            PIN_Write(LED_R_PIN,  1U);//LED��; 
            PIN_Write(LED_B_PIN,  0U);//LED��; 
            break;
        case yellow:
            PIN_Write(LED_G_PIN,  0U);//LED��; 
            PIN_Write(LED_R_PIN,  0U);//LED��; 
            PIN_Write(LED_B_PIN,  1U);//LED��; 
            break;
        case violet:
            PIN_Write(LED_G_PIN,  1U);//LED��; 
            PIN_Write(LED_R_PIN,  0U);//LED��; 
            PIN_Write(LED_B_PIN,  0U);//LED��; 
            break;
        case cyan:
            PIN_Write(LED_G_PIN,  0U);//LED��; 
            PIN_Write(LED_R_PIN,  1U);//LED��; 
            PIN_Write(LED_B_PIN,  0U);//LED��; 
            break;      
    }
}




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
void LED_ColorReverse(LED_t color)
{
    static uint8_t count = 0;
    if(count++ % 2)
    {
        LED_Color(color);   //��ָ����ɫ�ĵ�
    }
    else
    {
        LED_Color(black);   //��
    }
    
}


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
void Test_LED(void)
{
  LED_Init();   
  while (1)
  {          
        LED_Color(red);     //���
        delayms(500);
        LED_Color(green);   //�̵�
        delayms(500);
        LED_Color(blue);    //����
        delayms(500);
        LED_Color(violet);  //�ϵ�
        delayms(500);
        LED_Color(yellow);  //�Ƶ�
        delayms(500);
        LED_Color(cyan);    //���
        delayms(500);
        LED_Color(white);   //�׵�
        delayms(500);
        LED_Color(black);   //�ص�
        delayms(500);
        
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(red);     //�����˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(green);   //�̵���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(blue);    //������˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(violet);  //�ϵ���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(yellow);  //�Ƶ���˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(cyan);    //�����˸
            delayms(100);
        }
        for(int i = 0; i < 20; i++)
        {
            LED_ColorReverse(white);   //�׵���˸
            delayms(100);
        }
        
        for(int i = 0; i < 20; i++)
        {
            PIN_Write(LED_D0_PIN,  1U);//LED��;
            PIN_Write(LED_D1_PIN,  1U);//LED��;
            delayms(100);
            PIN_Write(LED_D0_PIN,  0U);//LED��;
            PIN_Write(LED_D1_PIN,  0U);//LED��;
            delayms(100);
        }

  }
}

