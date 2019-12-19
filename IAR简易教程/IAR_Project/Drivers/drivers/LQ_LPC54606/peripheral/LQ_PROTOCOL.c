/*!
  * @file     LQ_PROTOCOL.c
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

#include "LQ_PROTOCOL.h"


/* 数据拆分宏定义，在发送int16_t数据类型时,需要把数据拆分成单独字节进行发送 */
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )  /*!< int16_t 数据拆分 byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )    /*!< int16_t 数据拆分 byte1  */


/* 包涵自己发送数据的实现方式 */
#include "LQ_UART.h"
/*!
  * @brief    发送数据  底层
  *
  * @param    data    :发送数据的首地址
  * @param    length  :发送数据的长度 字节
  *
  * @return   
  *
  * @note     移植的时候，将这里改成自己的实现方式即可
  *
  * @see      
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendData(uint8_t *data , uint32_t length)
{
    /**使用串口正常发送数据，大概需要1.5ms*/
	UART_PutBuff(USART1, data, length);     //可以修改不同的串口发送数据
}


/*!
  * @brief    校验数据  底层用户无需关注
  *
  * @param    data    :发送数据的首地址
  * @param    length  :发送数据的长度 字节
  *
  * @return   校验值
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/11/6 星期三
  */
uint8_t PROTOCOL_CheckSum(uint8_t *data , uint8_t length)
{
    uint8_t sum = 0;
    uint16_t temp = 0;
    while(length--)
    {
        sum += data[temp++];
    }
    return sum;
}

/** 收发数据缓冲区 */
static uint8_t tx_buff[TX_BUFF_SIZE]; 

/** 收发数据缓冲区 */
static uint8_t rx_buff[RX_BUFF_SIZE]; 

/*!
  * @brief    发送数据给上位机   底层用户无需关注
  *
  * @param    config  :功能字
  * @param    data    :发送数据的首地址
  * @param    length  :发送数据的长度 字节   （不包括帧头 功能字 长度 校验和 帧尾） 
  *
  * @return   无
  *
  * @note     只支持int6_t 类型的数据  如果想要发送浮点数 可以按一定比例转化为int6_t 发送
  *
  * @see      int16_t databuff[10];
  * @see      PROTOCOL_Send(PROTOCOL_CONFIG_1, databuff, sizeof(databuff)); //发送10个数据 对应上位机前十个通道
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_Send(uint8_t config, int16_t *data, uint8_t length)
{
    uint8_t _cnt=0;
    
    tx_buff[_cnt++] = 'L';                /*!< 帧头 */
	tx_buff[_cnt++] = 'Q';                /*!< 帧头 */
    tx_buff[_cnt++] = config;              /*!< 功能字 */
    tx_buff[_cnt++] = length;              /*!< 数据长度 */
    
    /* 填充发送缓冲区 */
    for(int i = 0; i < length/2; i++)
    {
        tx_buff[_cnt++] = BYTE1(data[i]);
        tx_buff[_cnt++] = BYTE0(data[i]);
    }
    
    /* 填充校验和 */
    tx_buff[_cnt] = PROTOCOL_CheckSum(tx_buff, _cnt);
    
    _cnt++;
    
	/* 填充帧尾 */
    tx_buff[_cnt++] = 'O';
	
    /* 发送出去 */
    PROTOCOL_SendData(tx_buff, _cnt);
}


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
void PROTOCOL_SendWave(int16_t *data, uint8_t length)
{
    PROTOCOL_Send(PROTOCOL_CONFIG_1, data, length);
}


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
void PROTOCOL_SendPID(int16_t *data, uint8_t length)
{
    PROTOCOL_Send(PROTOCOL_CONFIG_2, data, length);
}



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
void PROTOCOL_ReceivePrepare(uint8_t data)
{
	static uint8_t _data_len = 0,_data_cnt = 0;
	static uint8_t state = 0;
    
    /* 检测帧头 */
    if(state==0 && data=='L')
	{
		state = 1;
		rx_buff[0] = data;
	}
	else if(state==1 && data=='Q')
	{
		state = 2;
		rx_buff[1] = data;
	}
    /* 功能字 */
	else if(state==2)
	{
		state = 3;
		rx_buff[2] = data;
	}
    /* 数据长度 */
	else if(state==3)
	{
		state = 4;
		rx_buff[3] = data;
        _data_len = data;
        _data_cnt = 4;
	}
    /* 接收数据 */
	else if(state==4 && _data_len>0)
	{
		_data_len--;
		rx_buff[_data_cnt++] = data;
		if(_data_len==0)
			state = 5;
	}
    /* 接收校验数据并校验 */
	else if(state==5)
	{
		rx_buff[_data_cnt++]=data;
        
        if(PROTOCOL_CheckSum(rx_buff, _data_cnt-1) == data)
        {
			state = 6;
        }
        else
        {
			state = 0;
            //校验失败
        }
	}
	/* 接收帧尾 并进入处理函数 根据协议做数据处理 */
	else if(state==6)
	{
		state = 0;
		
		rx_buff[_data_cnt++]=data;
        
        if('O' == data)
        {
            PROTOCOL_ReceiveParse(rx_buff,_data_cnt);
        }
        else
        {
            //帧尾不对 通信失败
        }
	}
	else
    {
        state = 0;
    }	
}

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
void PROTOCOL_ReceiveParse(uint8_t *data, uint8_t length)
{
    /* 再次校验 帧是否正确 */
    if(*data == 'L' && *(data+1) == 'Q' && *(data + length-1) == 'O' && PROTOCOL_CheckSum(data, length-2) == *(data + length-2))
    {
        /* 根据功能字 做不同的处理 */
        switch (data[2])
        {
          /*!< 上位机发送功能字5 要读取下位机PID数据  */
          case PROTOCOL_CONFIG_5:
            {
                /* 用户代码 将你的PID数据 缓存到temp_data中并发送出去 注意temp_data是int16_t 如果你的PID数据是浮点型 可以按比例缩放 */
                int16_t temp_senddata[18] = {1, 2, 3, 4, 5, 6, 7, 8, 30000, -1, -2, -3, -4, -5, -6, -7, -8, -30000};
                PROTOCOL_SendPID(&temp_senddata[0], sizeof(temp_senddata));
                
                break;
            }
          /*!< 上位机发送功能字6 要写入PID数据  */  
          case PROTOCOL_CONFIG_6:
            {
//                int16_t temp_recivedata[18];
//                /* 用户代码 缓冲区数据赋值给你的 PID  */
//                temp_recivedata[0] = (short)(*(rx_buff+4)<<8)|*(rx_buff+5);
//                temp_recivedata[1] = (short)(*(rx_buff+6)<<8)|*(rx_buff+7);
//                temp_recivedata[2] = (short)(*(rx_buff+8)<<8)|*(rx_buff+9);
//                temp_recivedata[3] = (short)(*(rx_buff+10)<<8)|*(rx_buff+11);
//                temp_recivedata[4] = (short)(*(rx_buff+12)<<8)|*(rx_buff+13);
//                temp_recivedata[5] = (short)(*(rx_buff+14)<<8)|*(rx_buff+15);
//                temp_recivedata[6] = (short)(*(rx_buff+16)<<8)|*(rx_buff+17);
//                temp_recivedata[7] = (short)(*(rx_buff+18)<<8)|*(rx_buff+19);
//                temp_recivedata[8] = (short)(*(rx_buff+20)<<8)|*(rx_buff+21);
//                temp_recivedata[9] = (short)(*(rx_buff+22)<<8)|*(rx_buff+23);
//                temp_recivedata[10] = (short)(*(rx_buff+24)<<8)|*(rx_buff+25);
//                temp_recivedata[11] = (short)(*(rx_buff+26)<<8)|*(rx_buff+27);
//                temp_recivedata[12] = (short)(*(rx_buff+28)<<8)|*(rx_buff+29);
//                temp_recivedata[13] = (short)(*(rx_buff+30)<<8)|*(rx_buff+31);
//                temp_recivedata[14] = (short)(*(rx_buff+32)<<8)|*(rx_buff+33);
//                temp_recivedata[15] = (short)(*(rx_buff+34)<<8)|*(rx_buff+35);
//                temp_recivedata[16] = (short)(*(rx_buff+36)<<8)|*(rx_buff+37);
//                temp_recivedata[17] = (short)(*(rx_buff+38)<<8)|*(rx_buff+39);

                break;
            }
          case PROTOCOL_CONFIG_7:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_8:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_9:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_A:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_B:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_C:
            {
                /* 用户代码  */

                break;
            }
          case PROTOCOL_CONFIG_D:
            {
                /* 用户代码  */


                break;
            }
          case PROTOCOL_CONFIG_E:
            {
                /* 用户代码  */

                
                break;
            }
          case PROTOCOL_CONFIG_F:
            {
                /* 用户代码  */

                
                break;
            }
            
        }
        
        
    }
    else
    {
       //校验失败 
    }

            
}


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
void PROTOCOL_SendCameraGrayData(uint8_t *data, uint32_t length)
{
    /* 发送帧头 */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_4;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* 发送图像数据 */
    PROTOCOL_SendData(data, length);
	
	/* 发送校验 由于摄像头数据比较多 这里使用固定校验 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);

}


/*!
  * @brief    将每个字节代表一个像素点的二值化数组 压缩为一个字节代表8个像素点的数组  
  *
  * @param    data           :摄像头数据的首地址
  * @param    data_encode    :压缩后摄像头数据的首地址
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
void PROTOCOL_DataEncode(uint8_t *data, uint8_t *data_encode, uint32_t length)
{
	uint32_t len = (length+7)/8;
	uint32_t temp = 0;
	for(uint32_t i = 0; i < len; i++)
	{
		data_encode[i]   = ( ((data[0+temp]&0x01)<<7) + ((data[1+temp]&0x01)<<6) + ((data[2+temp]&0x01)<<5 )
		                   | ((data[3+temp]&0x01)<<4) + ((data[4+temp]&0x01)<<3) + ((data[5+temp]&0x01)<<2 )
		                   | ((data[6+temp]&0x01)<<1) + ((data[7+temp]&0x01)<<0));
		temp += 8;
	}
}



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
void PROTOCOL_SendCameraBinData(uint8_t *data, uint32_t length)
{
    /* 发送帧头 */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_10;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* 发送图像数据 */
    PROTOCOL_SendData((uint8_t *)data, length);
	
	/* 发送校验 由于摄像头数据比较多 这里使用固定校验 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);
}



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
void PROTOCOL_SendCameraRGB565Data(uint16_t *data, uint32_t length)
{
    /* 发送帧头 */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_11;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* 发送图像数据 */
    PROTOCOL_SendData((uint8_t *)data, length);
	
	/* 发送校验 由于摄像头数据比较多 这里使用固定校验 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);
}





/*!
  * @brief    发送摄像头数据
  *
  * @param    data    :CCD数据的首地址
  * @param    length  :CCD数据的长度  字节   （不包括帧头 功能字 长度 校验和 帧尾）  
  *
  * @return   无
  *
  * @note     无
  *
  * @see      
  *
  * @date     2019/11/6 星期三
  */
void PROTOCOL_SendCCDData(uint8_t *data, uint32_t length)
{
    /* 发送帧头 */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_11;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
    
    /* 发送图像数据 */
    PROTOCOL_SendData(data, length);
	
	/* 发送校验 由于数据比较多 这里使用固定校验 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);

}
