/*!
  * @file     TEST_EEPROM.c
  *
  * @brief    EEPROM����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "LQ_EEPROM.h"
#include "LQ_UART.h"
#include "stdio.h"
#include "TEST_EEPROM.h"
/*!
  * @brief    ����EEPROM
  *
  * @param    
  *
  * @return   
  *
  * @note     ���Լ�¼һЩ���� ���粻�ᶪʧ
  *
  * @see      
  *
  * @date     2019/11/2 ������
  */
void Test_EEPROM(void)
{
    /* ��ʼ�� EEPROM */
    EEPROM_InitConfig();
    
    /* ��ʼ������ */
    UART_InitConfig(USART0,115200);
    
    /* ��д������ */
    float w_buff[100];
    float r_buff[100];
    
    for(int i = 0; i < 100; i++)
    {
        w_buff[i] = 1000*i*0.8;
    }
    
    /* д��EEPROM */
    EEPROM_WriteBuff(0, w_buff, sizeof(w_buff));
    
    /* ������ */
    EEPROM_ReadBuff(0, (uint8_t *)r_buff, sizeof(r_buff));
    
    /* �Ƚ�д��Ͷ������Ƿ�һ�� */
    if(strcmp((char *)w_buff, (char *)r_buff))
    {
        printf("EEPROM ��д���� ��\n\r");
        while(1);
    }
    printf("EEPROM ��д���Գɹ� ��\n\r");

}




