/*!
  * @file     main.c
  *
  * @brief    
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
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

/* �ж����ȼ��� */
#define NVIC_Group0   0x07
#define NVIC_Group1   0x06
#define NVIC_Group2   0x05
#define NVIC_Group3   0x04


/**
  * @brief    ����ȷ��ʱ
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     LPC54606 ��32KB��I&D SRAM  �����ͨ��SRAM�ٶȿ�ܶ� 
  * @note     �ڷ�ɢ�����ļ��� Ĭ�Ͻ�32K��I&D SRAM�ֳ�16K��ջ����16K��RamFunction
  * @note     ����ʹ��RAMFUNCTION_SECTION_CODE()���ؼ����ִ���ŵ�I&D SRAM�������
  * @note     ����ֻ����һ��ʾ���õ� 
  *
  * @example  delayms(100);
  *
  * @date     2019/4/22 ����һ
*/
RAMFUNCTION_SECTION_CODE(void delayms(uint16_t ms))
{
	volatile uint32_t i = 0;
	while(ms--)
	{
		for (i = 0; i < 15000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}	
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* ��ʼ������ʱ�� 180M */
    BOARD_BootClockPLL180M();
    
    /* ��ʼ������0 ����ʹ�� PRINTF���� */
    BOARD_InitDebugConsole();

    
    /*�����ж����ȼ���  0: 0����ռ���ȼ� 8�������ȼ� 
     *                  1: 2����ռ���ȼ� 4�������ȼ� 
	 *		            2: 4����ռ���ȼ� 2�������ȼ� 
     *                  3: 8����ռ���ȼ� 0�������ȼ� 
     */
	/* �������ȼ����� 3: 8����ռ���ȼ� 0-7  0���ȼ���� */
    NVIC_SetPriorityGrouping(NVIC_Group3);
    
    /*!
      * @brief   һ�����ӹ���  �û����Ի�����������޸�
      *
      *          
      *          
      * @note    ��config.h�� ѡ����ʾ����Ļ   
      */ 
    Test_LED();
    while(1)
    {

    }
}
