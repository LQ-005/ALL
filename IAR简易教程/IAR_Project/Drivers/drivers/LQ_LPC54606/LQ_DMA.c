/*!
  * @file     LQ_DMA.c
  *
  * @brief    DMA�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ���ʹ����������ͷ��ɫ������ DMA0���ᱻռ��23��ͨ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "fsl_dma.h"
#include "fsl_inputmux.h"
#include "LQ_DMA.h"

/** ����ͷ DMA������ */
dma_handle_t camera_dma_handle;

/** DMA link���������� */
extern dma_descriptor_t s_dma_descriptor_table0[];

/** ����ͷ������ɱ�־λ */
volatile uint8_t camera_flag = false;


/*!
  * @brief    ����ͷ DMA������ɻص�����
  *
  * @param    �û��������
  *
  * @return   
  *
  * @note     ����ͷ������һ֡ͼ����Զ����øú���
  *
  * @see      
  *
  * @date     2019/10/22 ���ڶ�
  */
void camera_dma_callback(struct _dma_handle *handle, void *userData, bool transferDone, uint32_t intmode)
{
    /* һ��ͼ�� 120*188 ��DMA����1024���ֽھͻ����һ��DMA�ж� */
    if(!DMA_ChannelIsActive(DMA0, CAMERA_DMA_CH))//�ж�����ͷһ֡�����Ƿ������
    {
        /* ������ɱ�־λ */
        camera_flag = true;
    }
}


/*!
  * @brief    ����ͷDMA�����ʼ��
  *
  * @param    srcStartAddr   ��Դ��ַ IO��ַ LQ_GPIO.h ���ж�Ӧ�궨�� ����PT0__BYTE0
  * @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����
  * @param    len            �����䳤��
  *
  * @return   ��
  *
  * @note     ���SCTʹ��ʱ������ȳ�ʼ��DMA  ʹ��DMA linkģʽ ��ռ��DMAͨ��CAMERA_DMA_CH --- CAMERA_DMA_CH + 22 ��ͨ��������(DMA���30��ͨ��������)
  *
  * @see      DMA_CameraInitConfig(&PT1__BYTE3, (uint8_t *)Image_Data, (IMAGEH * IMAGEW)); //��P1_24-P1_31 ��λ����IO���źŴ��䵽Image_Data����
  *
  * @date     2019/10/22 ���ڶ�
  */
void DMA_CameraInitConfig(void* srcStartAddr, void* dstStartAddr, uint32_t len)
{
    /* ��·��������ʼ�� */
    INPUTMUX_Init(INPUTMUX);
    
    /* ���ܽ����ӵ���Ӧ��DMAͨ���� */
    INPUTMUX_AttachSignal(INPUTMUX, CAMERA_DMA_CH, kINPUTMUX_Sct0DmaReq0ToDma);   
    
    /* ע�� DMA����ʱ�� �ḴλDMA */
    DMA_Init(DMA0);
    
    /* ���ô�������� */
    int temp = 0;
    int i    = len;
    for( ; i > 1024; i -= 1024)
    {
        DMA_SetupDescriptor(&s_dma_descriptor_table0[CAMERA_DMA_CH + temp], 
                    		DMA_CHANNEL_XFER(true, false, true, false, 1, 0, 1, 1024), srcStartAddr, (void *)((uint32_t)dstStartAddr + temp * 1024), &s_dma_descriptor_table0[CAMERA_DMA_CH + temp + 1]);
        temp ++;
    }
    DMA_SetupDescriptor(&s_dma_descriptor_table0[CAMERA_DMA_CH + temp],  DMA_CHANNEL_XFER(false, false, true, false, 1, 0, 1, i), srcStartAddr,  (void *)((uint32_t)dstStartAddr + temp * 1024), NULL);

    /* ����DMAͨ�� */
    dma_channel_trigger_t   dma_trigger;
    
    /* DMA������ʽ �����ش��� */
    dma_trigger.type  = kDMA_RisingEdgeTrigger; 
    dma_trigger.burst = kDMA_EdgeBurstTransfer1;
    dma_trigger.wrap  = kDMA_NoWrap;
    DMA_SetChannelConfig(DMA0, CAMERA_DMA_CH, &dma_trigger, false);
    
    /* ����DMAͨ�����ȼ� ��� */
    DMA_SetChannelPriority(DMA0, CAMERA_DMA_CH, kDMA_ChannelPriority0);
    
    /* ����DMA��� */
    DMA_CreateHandle(&camera_dma_handle, DMA0, CAMERA_DMA_CH);
    
    /* ���ȼ����� ��ռ���ȼ�1 �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(DMA0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,0));
    EnableIRQ(DMA0_IRQn);			          
    
    /* ���ûص����� */
    DMA_SetCallback(&camera_dma_handle, camera_dma_callback, NULL);
    
    /* �ύ���������� */
    DMA_SubmitChannelTransferParameter(&camera_dma_handle, DMA_CHANNEL_XFER(true, false, true, false, 1, 0, 1, 1024), srcStartAddr, dstStartAddr, &s_dma_descriptor_table0[CAMERA_DMA_CH + 1]);
 
    /* ��ʼ���� */
    DMA_StartTransfer(&camera_dma_handle);
    
}


/*!
  * @brief    ����ͷ���һ֡ͼ������ٴμ��ش���������
  *
  * @param    srcStartAddr   ��Դ��ַ IO��ַ LQ_GPIO.h ���ж�Ӧ�궨�� ����PT0__BYTE0
  * @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����  
  *
  * @return   ��
  *
  * @note     ���˺����ŵ����ж��� ���жϷ����� ���øú��������µ�ͼ����
  *
  * @see      DMA_CameraReload(&PT1__BYTE3, (uint8_t *)Image_Data);   //��������DMA������
  *
  * @date     2019/10/22 ���ڶ�
  */
inline void DMA_CameraReload(void* srcStartAddr, void* dstStartAddr)
{
    /* ��ͣDMA���� */
    DMA0->COMMON[0].ENABLECLR = 1<<CAMERA_DMA_CH;
    DMA0->COMMON[0].ABORT = 1<<CAMERA_DMA_CH;
    
    /* ��������ͨ�������� */
    s_dma_descriptor_table0[CAMERA_DMA_CH].linkToNextDesc = (void *)(&s_dma_descriptor_table0[CAMERA_DMA_CH + 1]);
    s_dma_descriptor_table0[CAMERA_DMA_CH].dstEndAddr = (void *)((uint32_t)dstStartAddr + 1024 - 1);
    DMA0->CHANNEL[CAMERA_DMA_CH].XFERCFG = s_dma_descriptor_table0[CAMERA_DMA_CH].xfercfg;
  
    /* ��ʼ���� */
    DMA_StartTransfer(&camera_dma_handle);

}




