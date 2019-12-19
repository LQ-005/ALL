/*!
  * @file     TEST_EEPROM.c
  *
  * @brief    EEPROM测试
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "LQ_EEPROM.h"
#include "LQ_UART.h"
#include "stdio.h"
#include "TEST_EEPROM.h"
/*!
  * @brief    测试EEPROM
  *
  * @param    
  *
  * @return   
  *
  * @note     可以记录一些数据 掉电不会丢失
  *
  * @see      
  *
  * @date     2019/11/2 星期六
  */
void Test_EEPROM(void)
{
    /* 初始化 EEPROM */
    EEPROM_InitConfig();
    
    /* 初始化串口 */
    UART_InitConfig(USART0,115200);
    
    /* 读写缓冲区 */
    float w_buff[100];
    float r_buff[100];
    
    for(int i = 0; i < 100; i++)
    {
        w_buff[i] = 1000*i*0.8;
    }
    
    /* 写入EEPROM */
    EEPROM_WriteBuff(0, w_buff, sizeof(w_buff));
    
    /* 读出来 */
    EEPROM_ReadBuff(0, (uint8_t *)r_buff, sizeof(r_buff));
    
    /* 比较写入和读出的是否一致 */
    if(strcmp((char *)w_buff, (char *)r_buff))
    {
        printf("EEPROM 读写出错 ！\n\r");
        while(1);
    }
    printf("EEPROM 读写测试成功 ！\n\r");

}




