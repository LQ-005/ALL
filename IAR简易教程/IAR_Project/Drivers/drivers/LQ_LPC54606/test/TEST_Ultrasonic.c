/*!
  * @file     TEST_ULTRASONIC.c
  *
  * @brief    超声波测试
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 星期六
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
  * @brief    测试超声波模块
  *
  * @param    
  *
  * @return   
  *
  * @note     中断方式 超声波HCSR04_TRIG管脚置高电平15us左右，
  *           超声波模块会发射超声波 同时HCSR04_ECHO管脚置为高电平 
  *           当收到超声波反射信号时HCSR04_ECHO管脚变成低电平 
  *           记录HCSR04_ECHO管脚高电平时间 通过声速就可以计算出距离
  *
  * @example  Test_HCSR04(); //普通等待方式  测距会花费比较长的时间
  *
  * @date     2019/10/9 星期三
  */
void Test_HCSR04(void)
{
	/* 初始化超声波的IO */
	PIN_InitConfig(HCSR04_TRIG, PIN_MODE_OUTPUT, 0);
    PIN_InitConfig(HCSR04_ECHO, PIN_MODE_INPUT_PULLDOWN, 0);
	
	systime.init();                                  //开启systick定时器
	LED_Init();
	PRINTF("\r\nLQ HC-SR04 Test\n");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ HC-SR04 Test");
#else
	TFTSPI_Init(1);                //TFT1.8初始化  0：横屏显示  1：竖屏显示  
    TFTSPI_CLS(u16BLUE);           //清屏
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
			
			/* HC_TRIG 保持8-15us的高电平 */
			PIN_Write(HCSR04_TRIG, 1);
			systime.delay_us(15);
			PIN_Write(HCSR04_TRIG, 0);
			
			/* 超声波模块开始发送超声波 */
			while(!PIN_Read(HCSR04_ECHO));
			
			/* 记录高电平时长 */
			hc_time = systime.get_time_us();
			
			/* 超声波模块收到超声波反射 */
			while(PIN_Read(HCSR04_ECHO));
		
			/* 记录高电平时长 */
			hc_time = systime.get_time_us() - hc_time;
			
			/* 计算距离 hc_time/2 * 340m/s */
			dis = (float)(hc_time * 0.017);          //计算距离dis
			
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


/**  hc_starttime 记录超声波测距ECHO 高电平开始时间  hc_time 记录ECHO高电平持续时间 */
volatile uint32_t hc_starttime; 
volatile uint16_t hc_time;


/*!
  * @brief    测试超声波模块
  *
  * @param    
  *
  * @return   
  *
  * @note     中断方式 超声波HCSR04_TRIG管脚置高电平15us左右，
  *           超声波模块会发射超声波 同时HCSR04_ECHO管脚置为高电平 
  *           当收到超声波反射信号时HCSR04_ECHO管脚变成低电平 
  *           记录HCSR04_ECHO管脚高电平时间 通过声速就可以计算出距离
  *
  * @example  Test_HCSR(); //在irq.c中断中记录时间
  *
  * @date     2019/10/9 星期三
  */
void Test_HCSR(void)
{
    systime.init();                      //开启systick定时器
	LED_Init();
	PRINTF("\r\nLQ HC-SR04 Test \n");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ HC-SR04 Test");
#else
	TFTSPI_Init(1);                //TFT1.8初始化  0：横屏显示  1：竖屏显示  
    TFTSPI_CLS(u16BLUE);           //清屏
	TFTSPI_P8X16Str(0,0,"LQ HC-SR04 Test",u16RED,u16BLUE);
#endif
	char txt[16];
	uint32_t now_time = systime.get_time_us();
	static uint8_t count = 0;
	float dis = 0;
    
    
	/* 初始化超声波的IO */
	PIN_InitConfig(HCSR04_TRIG, PIN_MODE_OUTPUT, 0);
    PIN_Exti(HCSR04_ECHO, 4, PIN_IRQ_MODE_RISING_FALLING);
    
    //优先级配置 抢占优先级5  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIN_INT4_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    
	EnableIRQ(PIN_INT4_IRQn);			 //使能中断  
    /*GPIO 外部中断配置结束*/  
	
	while(1)
	{       
		if(systime.get_time_us() - now_time >= 50000)
		{
			now_time = systime.get_time_us();
            
			/* HC_TRIG 保持8-15us的高电平 */
			PIN_Write(HCSR04_TRIG, 1);
			systime.delay_us(15);
			PIN_Write(HCSR04_TRIG, 0);
			
		
			/* 计算距离 hc_time/2 * 340m/s */
			dis = (float)(hc_time * 0.017);          //计算距离dis
			
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

