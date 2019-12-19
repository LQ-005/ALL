/*!
  * @file     ANO_DT.h
  *
  * @brief    匿名上位机驱动
  *
  * @company  匿名
  *
  * @author   匿名
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @Software IAR8.32 or MDK5.28
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "fsl_common.h"

/*!
  * @brief    向上位机发送发送8个short数据
  *
  * @param    data1 - data8  ： 发送给上位机显示波形
  *
  * @return   无
  *
  * @note     无
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 /*,short data7, short data8, short .....可根据需要自行添加 */);

/*!
  * @brief    向上位机发送发送PID帧
  *
  * @param    group         : PID组
  * @param    p1_p - p3_d   : PID数据
  *
  * @return   无
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/6/17 星期一
  */
void ANO_DT_Send_PID(uint8_t group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);


/**
  * @brief    测试上报匿名上位机
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/17 星期一
  */
void Test_ANO_DT(void);


/*!
  * @brief    协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
  *
  * @param    data_buf ：数据包
  * @param    num      ：数据包长度
  *
  * @return   无
  *
  * @note     校验通过后对数据进行解析，实现相应功能 此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
  *
  * @see  
  *
  * @date     2019/6/17 星期一
  */
void ANO_DT_Data_Receive_Anl(uint8_t *data_buf,uint8_t num);

/*!
  * @brief    协议预解析，根据协议的格式，将收到的数据进行一次格式性解析，格式正确的话再进行数据解析
  *
  * @param    data ：数据包  
  *
  * @return   无
  *
  * @note     移植时，此函数应由用户根据自身使用的通信方式自行调用，比如串口每收到一字节数据，则调用此函数一次
  * @note     此函数解析出符合格式的数据帧后，会自行调用数据解析函数   
  *
  * @see        
  *
  * @date     2019/6/17 星期一
  */
void ANO_DT_Data_Receive_Prepare(uint8_t data);
	
#endif

