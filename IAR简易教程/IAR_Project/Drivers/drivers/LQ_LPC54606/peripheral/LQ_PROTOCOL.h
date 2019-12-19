/*!
  * @file     LQ_PROTOCOL.h
  *
  * @brief    龙邱上位机通讯协议
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/11/6 星期三
  */ 
#ifndef __LQ_PROTOCOL_H
#define __LQ_PROTOCOL_H

#include "stdint.h"

/* 上位机功能字 */
#define   PROTOCOL_CONFIG_0  0x00   /*!< 上位机写入数据给下位机  下位机收到数据并校验没有问题后 发送功能字0给上位机 */
#define   PROTOCOL_CONFIG_1  0x01   /*!< 下位机发送功能字1 代表波形数据  */
#define   PROTOCOL_CONFIG_2  0x02   /*!< 下位机发送功能字2 代表PID数据  */
#define   PROTOCOL_CONFIG_3  0x03   /*!< 下位机发送功能字3 代表CCD数据  */
#define   PROTOCOL_CONFIG_4  0x04   /*!< 下位机发送功能字4 代表灰度摄像头数据  */
#define   PROTOCOL_CONFIG_5  0x05   /*!< 上位机发送功能字5 要读取下位机PID数据  */
#define   PROTOCOL_CONFIG_6  0x06   /*!< 上位机发送功能字6 要写入PID数据  */
#define   PROTOCOL_CONFIG_7  0x07   /*!< 上位机发送功能字7 上位机按键1按下  */
#define   PROTOCOL_CONFIG_8  0x08   /*!< 上位机发送功能字8 上位机按键2按下  */
#define   PROTOCOL_CONFIG_9  0x09   /*!< 上位机发送功能字9 上位机按键3按下  */
#define   PROTOCOL_CONFIG_A  0x0A   /*!< 上位机发送功能字A 上位机按键4按下  */
#define   PROTOCOL_CONFIG_B  0x0B   /*!< 上位机发送功能字B 上位机按键5按下  */
#define   PROTOCOL_CONFIG_C  0x0C   /*!< 上位机发送功能字C 上位机按键6按下  */
#define   PROTOCOL_CONFIG_D  0x0D   /*!< 上位机发送功能字D 上位机按键7按下  */
#define   PROTOCOL_CONFIG_E  0x0E   /*!< 上位机发送功能字E 上位机按键8按下  */
#define   PROTOCOL_CONFIG_F  0x0F   /*!< 上位机发送功能字F 上位机按键9按下  */
#define   PROTOCOL_CONFIG_10 0x10   /*!< 下位机发送功能字10 代表二值化摄像头数据  */
#define   PROTOCOL_CONFIG_11 0x11   /*!< 下位机发送功能字11 代表RGB565摄像头数据  */
#define   PROTOCOL_CONFIG_12 0x12   /*!< 下位机发送功能字12 代表YUV摄像头数据  */

/* 收发缓冲区长度 */
#define   TX_BUFF_SIZE    100  /*!< 发送数据缓冲区  */
#define   RX_BUFF_SIZE    100  /*!< 接收数据缓冲区  */

/*!
  * @brief    发送数据给上位机 显示波形
  *
  * @param    data    :发送数据的首地址
  * @param    length  :发送数据的长度 字节   （不包括帧头 功能字 长度 校验和 帧尾） 
  *
  * @return   无
  *
  * @note     只支持int6_t 类型的数据  如果想要发送浮点数 可以按一定比例转化为int6_t 发送
  *
  * @see      int16_t databuff[10];
  * @see      PROTOCOL_SendWave(databuff, sizeof(databuff)); //发送10个数据 对应上位机前十个通道     
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendWave(int16_t *data, uint8_t length);


/*!
  * @brief    发送PID数据给上位机
  *
  * @param    data    :发送数据的首地址
  * @param    length  :发送数据的长度字节  字节   （不包括帧头 功能字 长度 校验和 帧尾） 
  *
  * @return   无
  *
  * @note     只支持int6_t 类型的数据  如果想要发送浮点数 可以按一定比例转化为int6_t 发送
  *
  * @see      int16_t databuff[9];
  * @see      PROTOCOL_SendPID(databuff, sizeof(databuff)); //发送9个PID数据 对应上位机前三组PID     
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendPID(int16_t *data, uint8_t length);



/*!
  * @brief    接收上位机数据 解析预处理
  *
  * @param    data  ： 数据
  *
  * @return   无
  *
  * @note     一般单片机使用串口中断接收数据 一次只能接收一个数据 
  *
  * @see      PROTOCOL_ReceivePrepare(data);  //将这个函数放到串口中断中即可  data是串口中断接收到的字符
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_ReceivePrepare(uint8_t data);


/*!
  * @brief    接收上位机数据 并根据协议做一些处理
  *
  * @param    data    :要解析数据的首地址
  * @param    length  :要解析数据的长度    字节   （包括帧头 功能字 长度 校验和 帧尾）  
  *
  * @return   无
  *
  * @note     接收到一帧数据后 使用此函数对数据进行解析
  *
  * @see      uint8_t data[100];   
  * @see      PROTOCOL_ReceiveParse(data, length);  //一般使用DMA接收到一帧数据存放在data中 然后调用该函数对协议进行解析
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_ReceiveParse(uint8_t *data, uint8_t length);


/*!
  * @brief    发送 灰度 摄像头数据
  *
  * @param    data    :摄像头数据的首地址
  * @param    length  :摄像头数据的长度  字节   （不包括帧头 功能字 长度 校验和 帧尾） 
  *
  * @return   无
  *
  * @note     摄像头灰度数据 0-0xff
  *
  * @see      uint8_t Image_Data[IMAGEH][IMAGEW]; //摄像头数据
  * @see      PROTOCOL_SendCameraGrayData((uint8_t *)Image_Data, sizeof(Image_Data)); //发送数据上报上位机
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendCameraGrayData(uint8_t *data, uint32_t length);


/*!
  * @brief    将每个字节代表一个像素点的二值化数组 压缩为一个字节代表8个像素点的数组  
  *
  * @param    data           :摄像头数据的首地址
  * @param    data_encode    :摄像头数据的首地址
  * @param    length         :二值化摄像头数据的长度  
  *
  * @return   无
  *
  * @note     一个字节中高位表示图像左边的像素点  低位表示图像右边的像素点  
  *
  * @see      uint8_t Pixle[IMAGEH][IMAGEW]; //摄像头二值化数据
  * @see      uint8_t dataencode[(IMAGEH*IMAGEW+7)/8];       //摄像头二值化压缩后的数据
  * @see      PROTOCOL_DataEncode((uint8_t *)Pixle, dataencode, sizeof(Pixle)); //压缩二值化数据
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_DataEncode(uint8_t *data, uint8_t *data_encode, uint32_t length);


/*!
  * @brief    发送 二值化 摄像头数据
  *
  * @param    data    :摄像头数据的首地址
  * @param    length  :摄像头数据的长度  字节   （不包括帧头 功能字 长度 校验和 帧尾）  
  *
  * @return   无
  *
  * @note     一个字节代表8个像素点   一个字节中高位表示图像左边的像素点  低位表示图像右边的像素点
  *
  * @see      uint8_t Pixle[IMAGEH][IMAGEW]; //摄像头二值化数据
  * @see      uint8_t dataencode[(IMAGEH*IMAGEW+7)/8];       //摄像头二值化压缩后的数据
  * @see      PROTOCOL_DataEncode((uint8_t *)Pixle, dataencode, (IMAGEH*IMAGEW)); //压缩二值化数据
  * @see      PROTOCOL_SendCameraBinData((uint8_t *)dataencode, sizeof(dataencode)); //发送数据上报上位机
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendCameraBinData(uint8_t *data, uint32_t length);



/*!
  * @brief    发送 RGB565 摄像头数据
  *
  * @param    data    :摄像头数据的首地址
  * @param    length  :摄像头数据的长度  字节   （不包括帧头 功能字 长度 校验和 帧尾） 
  *
  * @return   无
  *
  * @note     小端格式
  *
  * @see      uint16_t Image_Data[IMAGEH][IMAGEW]; //摄像头二值化数据
  * @see      PROTOCOL_SendCameraRGB565Data((uint16_t *)Image_Data, sizeof(Image_Data)); //发送数据上报上位机
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendCameraRGB565Data(uint16_t *data, uint32_t length);



/*!
  * @brief    发送摄像头数据
  *
  * @param    data    :CCD数据的首地址
  * @param    length  :CCD数据的长度（不包括帧头 功能字 长度 校验）   
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendCCDData(uint8_t *data, uint32_t length);

#endif



