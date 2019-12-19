/*!
  * @file     irq.c
  *
  * @brief    �жϷ�����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     �жϷ����� ��֪�����ֿ���ȥstartup_LPC54606.s������
  *
  * @version  V1.0
  *
  * @Software IAR8.22 or MDK5.25
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 ������
  */ 
#include "include.h"

/*!
  * @brief    HardFault�жϷ�����
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/11/4 ����һ
  */
void HardFault_Handler(void)
{
    PRINTF("�������һ�㶼������Խ����߲�����δ��ʼ��������\r\n");
    PRINTF("�ڳ���ʼ�׶Σ����Թر�ȫ���ж� DisableInterrupts  ���������趼��ʼ����ɺ��ٿ���ȫ���ж� EnableInterrupts\r\n");
    PRINTF("��������жϷ������в���δ��ʼ������\r\n");
    PRINTF("�����ʼ����MRT��ʱ�� ��MRT�ж���ʹ�ô���1��ӡ������MRT�ȳ�ʼ���������ж�ʱ����1��δ��ʼ�����͵����˲���δ��ʼ���Ĵ���1���ͻ��������\r\n");
    while(1);
}




