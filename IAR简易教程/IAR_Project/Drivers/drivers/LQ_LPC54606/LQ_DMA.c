/*!
  * @file     LQ_DMA.c
  *
  * @brief    DMA驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     如果使用神眼摄像头白色排线座 DMA0将会被占用23个通道
  *
  * @version  V1.1  2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "fsl_dma.h"
#include "fsl_inputmux.h"
#include "LQ_DMA.h"

/** 摄像头 DMA传输句柄 */
dma_handle_t camera_dma_handle;

/** DMA link传输描述符 */
extern dma_descriptor_t s_dma_descriptor_table0[];

/** 摄像头传输完成标志位 */
volatile uint8_t camera_flag = false;


/*!
  * @brief    摄像头 DMA传输完成回调函数
  *
  * @param    用户无需关心
  *
  * @return   
  *
  * @note     摄像头传输完一帧图像会自动调用该函数
  *
  * @see      
  *
  * @date     2019/10/22 星期二
  */
void camera_dma_callback(struct _dma_handle *handle, void *userData, bool transferDone, uint32_t intmode)
{
    /* 一幅图像 120*188 ，DMA传输1024个字节就会进入一次DMA中断 */
    if(!DMA_ChannelIsActive(DMA0, CAMERA_DMA_CH))//判断摄像头一帧数据是否传输完成
    {
        /* 传输完成标志位 */
        camera_flag = true;
    }
}


/*!
  * @brief    摄像头DMA传输初始化
  *
  * @param    srcStartAddr   ：源地址 IO地址 LQ_GPIO.h 中有对应宏定义 例如PT0__BYTE0
  * @param    dstStartAddr   ：目的地址 摄像头数据缓冲区
  * @param    len            ：传输长度
  *
  * @return   无
  *
  * @note     配合SCT使用时，最好先初始化DMA  使用DMA link模式 会占用DMA通道CAMERA_DMA_CH --- CAMERA_DMA_CH + 22 的通道描述符(DMA最大30个通道描述符)
  *
  * @see      DMA_CameraInitConfig(&PT1__BYTE3, (uint8_t *)Image_Data, (IMAGEH * IMAGEW)); //将P1_24-P1_31 八位数据IO的信号传输到Image_Data数组
  *
  * @date     2019/10/22 星期二
  */
void DMA_CameraInitConfig(void* srcStartAddr, void* dstStartAddr, uint32_t len)
{
    /* 多路复用器初始化 */
    INPUTMUX_Init(INPUTMUX);
    
    /* 将管脚连接到对应的DMA通道上 */
    INPUTMUX_AttachSignal(INPUTMUX, CAMERA_DMA_CH, kINPUTMUX_Sct0DmaReq0ToDma);   
    
    /* 注意 DMA化的时候 会复位DMA */
    DMA_Init(DMA0);
    
    /* 设置传输表述符 */
    int temp = 0;
    int i    = len;
    for( ; i > 1024; i -= 1024)
    {
        DMA_SetupDescriptor(&s_dma_descriptor_table0[CAMERA_DMA_CH + temp], 
                    		DMA_CHANNEL_XFER(true, false, true, false, 1, 0, 1, 1024), srcStartAddr, (void *)((uint32_t)dstStartAddr + temp * 1024), &s_dma_descriptor_table0[CAMERA_DMA_CH + temp + 1]);
        temp ++;
    }
    DMA_SetupDescriptor(&s_dma_descriptor_table0[CAMERA_DMA_CH + temp],  DMA_CHANNEL_XFER(false, false, true, false, 1, 0, 1, i), srcStartAddr,  (void *)((uint32_t)dstStartAddr + temp * 1024), NULL);

    /* 配置DMA通道 */
    dma_channel_trigger_t   dma_trigger;
    
    /* DMA触发方式 上升沿触发 */
    dma_trigger.type  = kDMA_RisingEdgeTrigger; 
    dma_trigger.burst = kDMA_EdgeBurstTransfer1;
    dma_trigger.wrap  = kDMA_NoWrap;
    DMA_SetChannelConfig(DMA0, CAMERA_DMA_CH, &dma_trigger, false);
    
    /* 设置DMA通道优先级 最高 */
    DMA_SetChannelPriority(DMA0, CAMERA_DMA_CH, kDMA_ChannelPriority0);
    
    /* 创建DMA句柄 */
    DMA_CreateHandle(&camera_dma_handle, DMA0, CAMERA_DMA_CH);
    
    /* 优先级配置 抢占优先级1 子优先级0   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(DMA0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,0));
    EnableIRQ(DMA0_IRQn);			          
    
    /* 设置回调函数 */
    DMA_SetCallback(&camera_dma_handle, camera_dma_callback, NULL);
    
    /* 提交传输描述符 */
    DMA_SubmitChannelTransferParameter(&camera_dma_handle, DMA_CHANNEL_XFER(true, false, true, false, 1, 0, 1, 1024), srcStartAddr, dstStartAddr, &s_dma_descriptor_table0[CAMERA_DMA_CH + 1]);
 
    /* 开始传输 */
    DMA_StartTransfer(&camera_dma_handle);
    
}


/*!
  * @brief    摄像头完成一帧图像传输后，再次加载传输描述符
  *
  * @param    srcStartAddr   ：源地址 IO地址 LQ_GPIO.h 中有对应宏定义 例如PT0__BYTE0
  * @param    dstStartAddr   ：目的地址 摄像头数据缓冲区  
  *
  * @return   无
  *
  * @note     将此函数放到场中断中 场中断发生后 调用该函数进行新的图像传输
  *
  * @see      DMA_CameraReload(&PT1__BYTE3, (uint8_t *)Image_Data);   //重新设置DMA表述符
  *
  * @date     2019/10/22 星期二
  */
inline void DMA_CameraReload(void* srcStartAddr, void* dstStartAddr)
{
    /* 暂停DMA传输 */
    DMA0->COMMON[0].ENABLECLR = 1<<CAMERA_DMA_CH;
    DMA0->COMMON[0].ABORT = 1<<CAMERA_DMA_CH;
    
    /* 重新配置通道描述符 */
    s_dma_descriptor_table0[CAMERA_DMA_CH].linkToNextDesc = (void *)(&s_dma_descriptor_table0[CAMERA_DMA_CH + 1]);
    s_dma_descriptor_table0[CAMERA_DMA_CH].dstEndAddr = (void *)((uint32_t)dstStartAddr + 1024 - 1);
    DMA0->CHANNEL[CAMERA_DMA_CH].XFERCFG = s_dma_descriptor_table0[CAMERA_DMA_CH].xfercfg;
  
    /* 开始传输 */
    DMA_StartTransfer(&camera_dma_handle);

}




