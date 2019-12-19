/*!
  * @file     config.h
  *
  * @brief    ����һ�������ļ� ���һЩȫ�ֺ궨��
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.0
  *
  * @Software IAR8.22 or MDK5.25
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/28 ����һ
  */ 

#ifndef __CONFIG_H
#define __CONFIG_H

/* �жϿ��غ궨�� */
#define EnableInterrupts  __asm(" CPSIE i");//�����ж�
#define DisableInterrupts __asm(" CPSID i");//�����ж�


/* ������Ҫ���һЩȫ�ֺ궨�� */

/* ��ʾ��Ļ */
//#define OLED
//#define TFT1_8

/* ʹ������ͷ */
//#define LQMT9V034    //ʹ������


/* MPU6050   ֻ��ʹ�� Ӳ��IIC �����IIC */
/* ICM20602  ��ʹ�� Ӳ��IIC �����IIC  Ӳ��SPI �����SPI */
/* �������  ֻ��ʹ�� Ӳ��IIC �����IIC */
/* �궨�� ʹ�ò�ͬ�Ľ��߷�ʽ */
#define USE_HAL_SPI  0    /* Ӳ��SPI */
#define USE_SOFT_SPI 1    /* ģ��SPI */
#define USE_SOFT_IIC 2    /* ģ��IIC */
#define USE_HAL_IIC  3    /* Ӳ��IIC */

/* MPU6050/ICM20602/������� ѡ��ʹ��?IIC */
//#define IMU_USE_SELECT  USE_HAL_IIC

/* VL53 ʹ�ã�IIC */
//#define VL53_USE_SELECT USE_SOFT_IIC

/* ICM20602 ѡ��ʹ�� SPI */
//#define ICM_USE_SELECT  USE_SOFT_SPI

/* �Ƿ�ʹ��DMA��ʽ�������ݸ�������λ�� */
//#define ANO_DT_USE_DMA  1



#endif
