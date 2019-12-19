/*!
  * @file     TEST_ULTRASONIC.c
  *
  * @brief    ����������
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
  * @date     2019/10/19 ������
  */ 
#include "stdio.h"
#include "fsl_debug_console.h"
#include "config.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"
#include "LQ_SYSTICK.h"
#include "TEST_Ultrasonic.h"
#include "LQ_GPIO.h"

/*!
  * @brief    ���Գ�����ģ��
  *
  * @param    
  *
  * @return   
  *
  * @note     �жϷ�ʽ ������HCSR04_TRIG�ܽ��øߵ�ƽ15us���ң�
  *           ������ģ��ᷢ�䳬���� ͬʱHCSR04_ECHO�ܽ���Ϊ�ߵ�ƽ 
  *           ���յ������������ź�ʱHCSR04_ECHO�ܽű�ɵ͵�ƽ 
  *           ��¼HCSR04_ECHO�ܽŸߵ�ƽʱ�� ͨ�����پͿ��Լ��������
  *
  * @example  Test_HCSR04(); //��ͨ�ȴ���ʽ  ���Ứ�ѱȽϳ���ʱ��
  *
  * @date     2019/10/9 ������
  */
void Test_HCSR04(void)
{
	/* ��ʼ����������IO */
	PIN_InitConfig(HCSR04_TRIG, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(HCSR04_ECHO, PIN_MODE_INPUT_PULLDOWN, 0);
	
	systime.init();                                  //����systick��ʱ��
	LED_Init();
	PRINTF("\r\nLQ HC-SR04 Test\n");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ HC-SR04 Test");
#else
	TFTSPI_Init(1);                //TFT1.8��ʼ��  0��������ʾ  1��������ʾ  
    TFTSPI_CLS(u16BLUE);           //����
	TFTSPI_P8X16Str(0,0,"LQ HC-SR04 Test",u16RED,u16BLUE);
#endif
	char txt[16];
	uint32_t now_time = systime.get_time_us();
	static uint8_t count = 0;
	uint32_t hc_time;
	float dis = 0;
	while(1)
	{
		if(systime.get_time_us() - now_time >= 50000)
		{
			now_time = systime.get_time_us();
			
			/* HC_TRIG ����8-15us�ĸߵ�ƽ */
			PIN_Write(HCSR04_TRIG, 1);
			systime.delay_us(15);
			PIN_Write(HCSR04_TRIG, 0);
			
			/* ������ģ�鿪ʼ���ͳ����� */
			while(!PIN_Read(HCSR04_ECHO));
			
			/* ��¼�ߵ�ƽʱ�� */
			hc_time = systime.get_time_us();
			
			/* ������ģ���յ����������� */
			while(PIN_Read(HCSR04_ECHO));
		
			/* ��¼�ߵ�ƽʱ�� */
			hc_time = systime.get_time_us() - hc_time;
			
			/* ������� hc_time/2 * 340m/s */
			dis = (float)(hc_time * 0.017);          //�������dis
			
			if(count++ % 5 == 0)
			{
				sprintf(txt, "Dis:%5.2fcm ", dis);
				PRINTF(txt);
                PRINTF("\n");
				LED_ColorReverse(green);
#ifdef OLED
				LCD_P8x16Str(0,3,txt);
#else
				TFTSPI_P8X16Str(2,3,txt,u16RED,u16BLUE);
#endif
			}
		}
	}
}


/**  hc_starttime ��¼���������ECHO �ߵ�ƽ��ʼʱ��  hc_time ��¼ECHO�ߵ�ƽ����ʱ�� */
volatile uint32_t hc_starttime; 
volatile uint16_t hc_time;


/*!
  * @brief    ���Գ�����ģ��
  *
  * @param    
  *
  * @return   
  *
  * @note     �жϷ�ʽ ������HCSR04_TRIG�ܽ��øߵ�ƽ15us���ң�
  *           ������ģ��ᷢ�䳬���� ͬʱHCSR04_ECHO�ܽ���Ϊ�ߵ�ƽ 
  *           ���յ������������ź�ʱHCSR04_ECHO�ܽű�ɵ͵�ƽ 
  *           ��¼HCSR04_ECHO�ܽŸߵ�ƽʱ�� ͨ�����پͿ��Լ��������
  *
  * @example  Test_HCSR(); //��irq.c�ж��м�¼ʱ��
  *
  * @date     2019/10/9 ������
  */
void Test_HCSR(void)
{
    systime.init();                      //����systick��ʱ��
	LED_Init();
	PRINTF("\r\nLQ HC-SR04 Test \n");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ HC-SR04 Test");
#else
	TFTSPI_Init(1);                //TFT1.8��ʼ��  0��������ʾ  1��������ʾ  
    TFTSPI_CLS(u16BLUE);           //����
	TFTSPI_P8X16Str(0,0,"LQ HC-SR04 Test",u16RED,u16BLUE);
#endif
	char txt[16];
	uint32_t now_time = systime.get_time_us();
	static uint8_t count = 0;
	float dis = 0;
    
    
	/* ��ʼ����������IO */
	PIN_InitConfig(HCSR04_TRIG, PIN_MODE_OUTPUT, 0);
    PIN_Exti(HCSR04_ECHO, 4, PIN_IRQ_MODE_RISING_FALLING);
    
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIN_INT4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    
	EnableIRQ(PIN_INT4_IRQn);			 //ʹ���ж�  
    /*GPIO �ⲿ�ж����ý���*/  
	
	while(1)
	{       
		if(systime.get_time_us() - now_time >= 50000)
		{
			now_time = systime.get_time_us();
            
			/* HC_TRIG ����8-15us�ĸߵ�ƽ */
			PIN_Write(HCSR04_TRIG, 1);
			systime.delay_us(15);
			PIN_Write(HCSR04_TRIG, 0);
			
		
			/* ������� hc_time/2 * 340m/s */
			dis = (float)(hc_time * 0.017);          //�������dis
			
			if(count++ % 5 == 0)
			{
				sprintf(txt, "Dis:%5.2fcm ", dis);
				PRINTF(txt);
                PRINTF("\n");
				LED_ColorReverse(green);
#ifdef OLED
				LCD_P8x16Str(0,3,txt);
#else
				TFTSPI_P8X16Str(2,3,txt,u16RED,u16BLUE);
#endif
			}
		}
	}
}

