/*!
  * @file     LQ_SOFTSPI.h
  *
  * @brief    ģ��SPI����
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
  * @date     2019/10/19 ������
  */ 
#ifndef __LQ_SOFTSPI_H
#define __LQ_SOFTSPI_H

#include "fsl_common.h" 
#include "LQ_GPIO.h"

/* ע�� ICM20602 ʱ�ӿ���ʱΪ�ߵ�ƽ  ��ʱ�ӵڶ��������ش�������  ��NRF2401�Ĳ�ͬ������SPI��ͨ��  */
/*! 0: ʱ�ӿ���ʱ��Ϊ�͵�ƽ   1��ʱ�ӿ���ʱ��Ϊ�ߵ�ƽ*/ 
#define CPOL  1

/*! 0��ʱ�ӵ�һ�������ش�������   1��ʱ�ӵĵڶ��������ش������� */
#define CPHA  1 


#define SOFT_SPI_SCK_PIN    P0_6   /*!< ģ��SPI SCK�ܽ� */
#define SOFT_SPI_MISO_PIN   P0_2   /*!< ģ��SPI MISO�ܽ� */
#define SOFT_SPI_MOSI_PIN   P0_3   /*!< ģ��SPI MOSI�ܽ� */
#define SOFT_SPI_CS_PIN     P0_20  /*!< ģ��SPI CS�ܽ� */


#if CPOL
#define SPI_SCK_IDLE      PIN_Write(SOFT_SPI_SCK_PIN, 1); 
#define SPI_SCK_ACTIVE    PIN_Write(SOFT_SPI_SCK_PIN, 0); 
#else
#define SPI_SCK_IDLE      PIN_Write(SOFT_SPI_SCK_PIN, 0); 
#define SPI_SCK_ACTIVE    PIN_Write(SOFT_SPI_SCK_PIN, 1); 
#endif

#define SPI_MOSI_OUT(x)   PIN_Write(SOFT_SPI_MOSI_PIN, x); 
#define SPI_MISO_IN       PIN_Read(SOFT_SPI_MISO_PIN);
#define SPI_CS_OUT(x)     PIN_Write(SOFT_SPI_CS_PIN, x); 


/*!
  * @brief    ģ��SPI��ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ģ��SPIʹ�ùܽ� LQ_SOFTSPI.h�к궨��
  *
  * @see      SPI_SoftInit();  //ģ��SPI�ܽų�ʼ��
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftInit(void);


/*!
  * @brief    ģ��SPI��дn �ֽ�
  *
  * @param    buff[] ���Ҫд���ֵ д����Ŷ�ȡ��ֵ
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      uint8_t data[8];
  * @see      SPI_SoftRadeWriteNbyte(data, sizeof(data)); //SPI��д8���ֽ�
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len);

#endif
