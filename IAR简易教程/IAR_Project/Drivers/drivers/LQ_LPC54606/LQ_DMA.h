/*!
  * @file     LQ_DMA.h
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
#ifndef __LQ_DMA_H
#define __LQ_DMA_H
#include "stdint.h"

/*! 摄像头 DMA 传输通道*/
#define CAMERA_DMA_CH   4U

/** 摄像头传输完成标志位 */
extern volatile uint8_t camera_flag;

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
void DMA_CameraInitConfig(void* srcStartAddr, void* dstStartAddr, uint32_t len);


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
void DMA_CameraReload(void* srcStartAddr, void* dstStartAddr);

#endif
