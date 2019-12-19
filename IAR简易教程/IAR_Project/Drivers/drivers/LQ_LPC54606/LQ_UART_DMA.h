/*!
  * @file     LQ_UART_DMA.h
  *
  * @brief    ����DMA����
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
  * @date     2019/10/29 ���ڶ�
  */ 
#ifndef __LQ_UART_DMA_H
#define __LQ_UART_DMA_H
#include "fsl_usart_dma.h"

/* ����+DMA ��־λ */
extern volatile bool rxBufferEmpty;  /** ���տ� */
extern volatile bool txBufferFull;   /** ������ */
extern volatile bool txOnGoing;      /** ���ڷ��� */
extern volatile bool rxOnGoing;      /** ���ڽ��� */

/* DMA ����ṹ�� */
extern usart_transfer_t sendXfer;    /** ����DMA���ʹ���ṹ�� */
extern usart_transfer_t receiveXfer; /** ����DMA���մ���ṹ�� */

/* ���� + DMA ���ýṹ�� */
extern usart_dma_handle_t g_uartDmaHandle; /** ����DMA��� */

/**
  * @brief    ����DMA�����ʼ��
  *
  * @param    base  �� USART0 - USART8
  * @param    bound �� ���ڲ�����
  *
  * @return   ��
  *
  * @note     DMA �շ� ע������ͷ��ռ��ǰ��ͨ�� ���ʹ������ͷ 
  * @note     ��ռ��DMAͨ��CAMERA_DMA_CH --- CAMERA_DMA_CH + 22 ��ͨ��������(DMA���30��ͨ��������)
  * @note     dma_request_source_t �в鿴��Ӧͨ���Ƿ�����ͷռ�� 
  *
  * @see      UART_DMAInitConfig(USART0, 115200, 29, 28);  //��ʼ������0 + DMA
  *
  * @date     2019/6/6 ������
  */
void UART_DMAInitConfig(USART_Type *base, uint32_t bound);

#endif
