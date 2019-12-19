/*!
  * @file     LQ_SOFTIIC.h
  *
  * @brief    ģ��IIC�����ļ�
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
  * @date     2019/10/23 ������
  */ 
#ifndef __LQ_SOFTIIC_H
#define __LQ_SOFTIIC_H

#include "fsl_common.h"
#include "LQ_GPIO.h"

/* ע�� IIC���߹涨��IIC����ʱ SCL��SDA��Ϊ�ߵ�ƽ ����ⲿ������һ������������ */
/* ģ�� IIC��Ҫע�⣬��ַ��ҪӲ��IIC��ַ����һλ ����MPU6050 Ӳ��IIC��ַ�� 0x68  ��ģ�����0xD0*/
/* �뻻�ñ��IO ֱ���޸ĺ궨�� SOFT_IIC_SCL_PIN �� SOFT_IIC_SDA_PIN ���� */
#define SOFT_IIC_SCL_PIN  P0_2   /*!< P0_2  ��Ϊ SCL */
#define SOFT_IIC_SDA_PIN  P0_3   /*!< P0_3  ��Ϊ SDA */

#define SDA_IN         PIN_Dir(SOFT_IIC_SDA_PIN, 0);
#define SDA_OUT        PIN_Dir(SOFT_IIC_SDA_PIN, 1);

#define IIC_SCL_H      PIN_Write(SOFT_IIC_SCL_PIN, 1);
#define IIC_SCL_L      PIN_Write(SOFT_IIC_SCL_PIN, 0);

#define IIC_SDA_H      PIN_Write(SOFT_IIC_SDA_PIN, 1);
#define IIC_SDA_L      PIN_Write(SOFT_IIC_SDA_PIN, 0);

#define IIC_SDA_READ   PIN_Read(SOFT_IIC_SDA_PIN)


/*---------------------------------------------------------------
            IIC�ڲ�����
----------------------------------------------------------------*/		 
void IIC_Start(void);			        //����IIC��ʼ�ź�
void IIC_Stop(void);	  	            //����IICֹͣ�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				    //IIC������ACK�ź�
uint8_t IIC_WaitAck(void); 		        //IIC�ȴ�ACK�ź�
void IIC_SendByte(uint8_t data);        //IIC����һ���ֽ�
uint8_t IIC_ReadByte(uint8_t ack);       //IIC��ȡһ���ֽ�


/*---------------------------------------------------------------
            IIC�û�����
----------------------------------------------------------------*/
void IIC_Init(void);                    //��ʼ��IIC��IO��   
uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t buf);
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);

#endif
