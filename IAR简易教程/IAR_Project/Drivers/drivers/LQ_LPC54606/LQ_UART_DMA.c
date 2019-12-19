/*!
  * @file     LQ_UART_DMA.c
  *
  * @brief    ����DMA����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/29 ���ڶ�
  */ 
#include "LQ_UART_DMA.h"
#include "LQ_UART.h"
#include "fsl_usart_dma.h"

/* ����+DMA ��־λ */
volatile bool rxBufferEmpty = true;   /** ���տ� */
volatile bool txBufferFull = false;   /** ������ */
volatile bool txOnGoing = false;      /** ���ڷ��� */
volatile bool rxOnGoing = false;      /** ���ڽ��� */


/**
  * @brief    ����+DMA �Ļص�����  �����ڷ�����ɻ��߽�����ɣ����Զ����øú���
  *
  * @param    �û������ϵ��������
  *
  * @return   ��
  *
  * @note     ���ʹ�ûص������������Լ�������Ӧ���жϷ�����
  *
  * @see      ��
  *
  * @date     2019/6/15 ������
  */
void USART_UserCallback(USART_Type *base, usart_dma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_USART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }

    if (kStatus_USART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing     = false;
    }
}


/* ���� + DMA ���ýṹ�� */
usart_dma_handle_t g_uartDmaHandle;  /** ����DMA��� */
dma_handle_t g_uartTxDmaHandle;      /** DMA���;�� */
dma_handle_t g_uartRxDmaHandle;      /** DMA���վ�� */

/* DMA ����ṹ�� */
usart_transfer_t sendXfer;           /** ����DMA���ʹ���ṹ�� */
usart_transfer_t receiveXfer;        /** ����DMA���մ���ṹ�� */


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
void UART_DMAInitConfig(USART_Type *base, uint32_t bound)
{
    /* ��ʼ�����ڶ�Ӧ�Ĺܽ� ��Ӧ�ܽ���LQ_UART.h ��ͨ���궨��ȷ�� */
    UART_InitConfig(base, bound);
    
    /* �رս����ж� */
    USART_DisableInterrupts(base, kUSART_RxLevelInterruptEnable);
    
    uint8_t temp = USART_GetInstance(base);
    
    uint8_t RX_channel = 0;
    
    if(temp > 7)
    {
        RX_channel = (kDmaRequestFlexcomm8Rx + (temp - 8)*2);
    }
    else
    {
        RX_channel = (kDmaRequestFlexcomm0Rx + temp *2);
    }
    
    
    /* ʹ��DMA */
    DMA_Init(DMA0);
    DMA_EnableChannel(DMA0, RX_channel);
    DMA_EnableChannel(DMA0, RX_channel + 1);

    /* ����DMA��� .*/
    DMA_CreateHandle(&g_uartRxDmaHandle, DMA0, RX_channel);
    DMA_CreateHandle(&g_uartTxDmaHandle, DMA0, RX_channel + 1);

    /* ����USART_DMA��� .*/
    USART_TransferCreateHandleDMA(base, &g_uartDmaHandle, USART_UserCallback, NULL, &g_uartTxDmaHandle,
                                  &g_uartRxDmaHandle);
    
    
}









