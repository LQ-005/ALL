/*!
  * @file     LQ_KEY.c
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
#include "LQ_LED.h"
#include "LQ_KEY.h"
#include "LQ_GPIO.h"
/** �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);




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
void KEY_Init(void)
{  
    /* ������������ */
    PIN_InitConfig(KEY0_PIN,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(KEY1_PIN,  PIN_MODE_INPUT_PULLUP, 1);
    PIN_InitConfig(KEY2_PIN,  PIN_MODE_INPUT_PULLUP, 1);  
}


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
uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
        key_up=1;      //֧������
    }
    if(key_up && (PIN_Read(KEY0_PIN)==0 || PIN_Read(KEY1_PIN)==0 || PIN_Read(KEY2_PIN)==0))
    {
        delayms(10);   //����
        key_up=0;
        if(PIN_Read(KEY0_PIN)==0)      
        {
            return 1;
        }
        
        else if(PIN_Read(KEY1_PIN)==0) 
        {
            return 2;    
        }
        
        else if(PIN_Read(KEY2_PIN)==0) 
        {
            return 3;    
        }
        
    }
    if(PIN_Read(KEY0_PIN)==1 && PIN_Read(KEY1_PIN)==1 && PIN_Read(KEY2_PIN)==1) 
    {
        key_up=1;   
    }
    return 0;   //�ް�������
    
}



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
void Test_ExtiKEY(void)
{
    LED_Init();
    
    /* �����½��ش����ж� */
    PIN_Exti(KEY0_PIN, 0, PIN_IRQ_MODE_FALLING);
    PIN_Exti(KEY1_PIN, 1, PIN_IRQ_MODE_FALLING);
    PIN_Exti(KEY2_PIN, 2, PIN_IRQ_MODE_FALLING);
  
    //���ȼ����� ��ռ���ȼ�4  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIN_INT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4,0));
    
	EnableIRQ(PIN_INT0_IRQn);			          //ʹ��PIN_INT0_IRQn���ж�  
    
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIN_INT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    
	EnableIRQ(PIN_INT1_IRQn);			          //ʹ��PIN_INT1_IRQn���ж� 

    //���ȼ����� ��ռ���ȼ�6  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIN_INT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
    
	EnableIRQ(PIN_INT2_IRQn);			          //ʹ��PIN_INT2_IRQn���ж� 
    /* ��irq.c �� �����ж� */
    while(1);



}


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
void Test_KEY(void)
{ 
    LED_Init();
    KEY_Init(); 
    while (1)
    {  
        switch(KEY_Read(1))  
        {
            case 1:
                LED_Color(red);     
                break;           
            case 2:      
                LED_Color(green);   
                break;
            case 3:      
                LED_Color(blue);    
                break;
            default:
                LED_Color(white);   
                break;
        }

        delayms(50);
    }
}


