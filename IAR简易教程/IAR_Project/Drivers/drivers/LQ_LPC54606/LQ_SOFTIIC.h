/*!
  * @file     LQ_SOFTIIC.h
  *
  * @brief    模拟IIC驱动文件
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
  * @date     2019/10/23 星期三
  */ 
#ifndef __LQ_SOFTIIC_H
#define __LQ_SOFTIIC_H

#include "fsl_common.h"
#include "LQ_GPIO.h"

/* 注意 IIC总线规定，IIC空闲时 SCL和SDA都为高电平 最好外部上拉（一定不能下拉） */
/* 模拟 IIC需要注意，地址需要硬件IIC地址左移一位 例如MPU6050 硬件IIC地址用 0x68  用模拟就是0xD0*/
/* 想换用别的IO 直接修改宏定义 SOFT_IIC_SCL_PIN 、 SOFT_IIC_SDA_PIN 即可 */
#define SOFT_IIC_SCL_PIN  P0_2   /*!< P0_2  作为 SCL */
#define SOFT_IIC_SDA_PIN  P0_3   /*!< P0_3  作为 SDA */

#define SDA_IN         PIN_Dir(SOFT_IIC_SDA_PIN, 0);
#define SDA_OUT        PIN_Dir(SOFT_IIC_SDA_PIN, 1);

#define IIC_SCL_H      PIN_Write(SOFT_IIC_SCL_PIN, 1);
#define IIC_SCL_L      PIN_Write(SOFT_IIC_SCL_PIN, 0);

#define IIC_SDA_H      PIN_Write(SOFT_IIC_SDA_PIN, 1);
#define IIC_SDA_L      PIN_Write(SOFT_IIC_SDA_PIN, 0);

#define IIC_SDA_READ   PIN_Read(SOFT_IIC_SDA_PIN)


/*---------------------------------------------------------------
            IIC内部函数
----------------------------------------------------------------*/		 
void IIC_Start(void);			        //发送IIC开始信号
void IIC_Stop(void);	  	            //发送IIC停止信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				    //IIC不发送ACK信号
uint8_t IIC_WaitAck(void); 		        //IIC等待ACK信号
void IIC_SendByte(uint8_t data);        //IIC发送一个字节
uint8_t IIC_ReadByte(uint8_t ack);       //IIC读取一个字节


/*---------------------------------------------------------------
            IIC用户函数
----------------------------------------------------------------*/
void IIC_Init(void);                    //初始化IIC的IO口   
uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t buf);
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);

#endif
