/*!
  * @file     TEST_UART.c
  *
  * @brief    ���ڲ����ļ�
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
#include "fsl_debug_console.h"
#include "stdio.h"
#include "stdlib.h"
#include "LQ_UART.h"
#include "LQ_UART_DMA.h"
#include "LQ_LED.h"
#include "TEST_UART.h"

/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


/*!
  * @brief    ���ڲ�������
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     
  *
  * @example      
  *
  * @date     2019/10/31 ������
  */
void Test_UART(void)
{
    /* ��ʼ������0 */
    UART_InitConfig(USART0, 115200);
    
    /* ��ʼ������4 */
    UART_InitConfig(USART3, 115200);
    
    /* ʹ�ܴ���0�����ж� */
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
    NVIC_SetPriority(FLEXCOMM0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM0_IRQn);  //ʹ���ж�  FLEXCOMM0����USART0�ˣ�����ʹ���ж�ʹ�ܵ���FLEXCOMM0

    /* ʹ�ܴ���3�����ж� */
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
    NVIC_SetPriority(FLEXCOMM3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM3_IRQn);  //ʹ���ж�  FLEXCOMM3����USART3�ˣ�����ʹ���ж�ʹ�ܵ���FLEXCOMM3
    
    /* printf ʹ�ô���0 ������LQ_UART.c���޸� fputc �����޸�printf�Ĵ��� */
    printf("\n\r���ڴ�ӡ����\n\r");
    
    while(1)
    {
        UART_PutStr(USART0, "123456789\r\n");
        UART_PutStr(USART3, "123456789\r\n");
        
        UART_PutBuff(USART0, "123456789",5);
        UART_PutBuff(USART3, "123456789",5);
        
        /* ���ͻ��� */
        UART_PutChar(USART3, 0x0d);
        
        printf("\n\r���ڴ�ӡ����\n\r");
        delayms(2000);
    }
}







//                       .::::.
//                     .::::::::.
//                    :::::::::::
//                 ..:::::::::::'
//              '::::::::::::'
//                .::::::::::
//           '::::::::::::::..
//                ..::::::::::::.
//              ``::::::::::::::::
//               ::::``:::::::::'        .:::.
//              ::::'   ':::::'       .::::::::.
//            .::::'      ::::     .:::::::'::::.
//           .:::'       :::::  .:::::::::' ':::::.
//          .::'        :::::.:::::::::'      ':::::.
//         .::'         ::::::::::::::'         ``::::.
//     ...:::           ::::::::::::'              ``::.
//    ```` ':.          ':::::::::'                  ::::..
//                       '.:::::'                    ':'````..
/*************************************************************************/
/*************************************************************************/
/***************************DMA��������***********************************/
/*************************************************************************/
/*************************************************************************/


/*! DMA�շ����� */
#define USART_DMA_LEN  10



/**
  * @brief    ���� + DMA ���Ժ���
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����USART_DMA_LEN�����ݣ� ����ӡ���� ע�����ûص���������Ҫ�Լ�д�����жϷ�����
  * @note     ����ͷĬ��ռ�� DMAͨ��CAMERA_DMA_CH --- CAMERA_DMA_CH + 22  Ĭ�ϴ���0������1������DMA
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void Test_UART_DMA(void)
{
    /* �����շ� ������ */
    uint8_t g_txBuffer[USART_DMA_LEN] = {0};
    uint8_t g_rxBuffer[USART_DMA_LEN] = {0};

    LED_Init();   
    
    /* ��ʼ�� ����0 */
    UART_DMAInitConfig(USART0, 115200);   
    
    //���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(FLEXCOMM0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
    EnableIRQ(FLEXCOMM0_IRQn);	                            //ʹ��FLEXCOMM0_IRQn�ж�
	
    delayms(100);
    PRINTF("\r\n���񴮿ڲ�������\r\n");
    PRINTF("����ģ�鲨����:\n");
    PRINTF("LPUART1 init: 115200!\n"); 
    
    /* �������� */
    receiveXfer.data = g_rxBuffer;              //�������ݴ��λ��
    receiveXfer.dataSize = USART_DMA_LEN;       //�������ݳ���
    
    /* �������� */
    sendXfer.data    = g_txBuffer;              //�������ݴ��λ��
    sendXfer.dataSize = USART_DMA_LEN;          //�������ݳ���
    while(1)
    {
        
        /* ���յ����ݣ������Ѿ�copy�����ͻ��������ͳ�ȥ. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            rxOnGoing = true;
            
            /* ����DMA ���� */
            USART_TransferReceiveDMA(USART0, &g_uartDmaHandle, &receiveXfer);
        }

        /* ������ɺ󣬷��ͳ�ȥ. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;

            /* ʹ�ܷ��� */
            USART_TransferSendDMA(USART0, &g_uartDmaHandle, &sendXfer);
        }

        /* ���յ�һ֡���ݺ󣬴ӽ����ַ�������copy�����ͻ�����. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, USART_DMA_LEN);
            rxBufferEmpty = true;
            txBufferFull = true;
            LED_ColorReverse(blue);
        }
        
    }  
}


