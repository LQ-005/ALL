/*!
  * @file     include.h
  *
  * @brief    ����ͷ�ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ����ֱ�Ӱ������ͷ�ļ�
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
#ifndef __INCLUDE__H
#define __INCLUDE__H

/* ����ͷ�ļ� */
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"

/* fsl �ٷ��ײ������� */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_ctimer.h"
#include "fsl_dma.h"
#include "fsl_eeprom.h"
#include "fsl_flashiap.h"
#include "fsl_flexcomm.h"
#include "fsl_gint.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"
#include "fsl_inputmux.h"
#include "fsl_iocon.h"
#include "fsl_mrt.h"
#include "fsl_otp.h"
#include "fsl_pint.h"
#include "fsl_power.h"
#include "fsl_reset.h"
#include "fsl_rit.h"
#include "fsl_sctimer.h"
#include "fsl_spi.h"
#include "fsl_usart.h"
#include "fsl_usart_dma.h"
#include "fsl_wwdt.h"


/* �������fsl���װ�����ܳ��ϲ㺯�� */
#include "LQ_ADC.h"         /* ������ѹ */
#include "LQ_CTIME.h"       /* ���PWM  ������� */
#include "LQ_DMA.h"         /* DMA */
#include "LQ_EEPROM.h"      /* ���籣������ */
#include "LQ_GPIO.h"        /* GPIO */
#include "LQ_IIC.h"         /* Ӳ��IIC */
#include "LQ_MRT.h"         /* �����жϼ�ʱ�� */
#include "LQ_RIT.h"         /* ��ʱ�� */
#include "LQ_SCTIME.h"      /* ����ʱ�� �������PWM */
#include "LQ_SOFTIIC.h"     /* ģ��IIC */
#include "LQ_SOFTSPI.h"     /* ģ��SPI */
#include "LQ_SPI.h"         /* Ӳ��SPI */
#include "LQ_SYSTICK.h"     /* systick ϵͳ��ʱ�� */
#include "LQ_UART.h"        /* ���� */
#include "LQ_UART_DMA.h"    /* DMA���� */
#include "LQ_WDOG.h"        /* ���Ź� */


///* ���� ����� */
#include "ANO_DT.h"         /* ������λ��ͨ��Э�� */
#include "LQ_12864.h"       /* OLED���� */
#include "LQ_9AX.h"         /* �������� */
#include "LQ_CAMERA.h"      /* ����ͷ���� */
#include "LQ_ICM20602.h"    /* ICM20602���� */
#include "LQ_KEY.h"         /* �������� */
#include "LQ_LED.h"         /* LED���� */
#include "LQ_MPU6050.h"     /* MPU6050���� */
#include "LQ_SGP18T.h"      /* TFT18���� */
#include "LQ_MT9V034.h"     /* �������� */
#include "LQ_PROTOCOL.h"    /* ��λ��ͨ��Э�� */


///* ���� �����ļ� */
#include "config.h"         /* �����ļ� */
#include "TEST_9AX.h"       /* ����������� */
#include "TEST_ADC.h"       /* ����ADC��ѹ��ȡ */
#include "TEST_CAMERA.h"    /* ����ͷ���� */
#include "TEST_ENC.h"       /* ��������������� */
#include "TEST_EEPROM.h"    /* ����FLASH */
#include "TEST_ICM20602.h"  /* ����ICM20602 SPI���߷�ʽ */
#include "TEST_MPU6050.h"   /* ����MPU6050/ICM20602 IIC���߷�ʽ */
#include "TEST_MRT.h"       /* ����MRT��ʱ�� */
#include "TEST_RIT.h"       /* ����RIT */
#include "TEST_PWM.h"       /* PWM������� */
#include "TEST_SYSTICK.h"   /* ����systickϵͳ��ʱ�� */
#include "TEST_UART.h"      /* ���Դ��� */
#include "TEST_Ultrasonic.h"/* ���Գ����� */
#include "TEST_VL53.h"      /* ����VL53 ��� */
#include "TEST_WDog.h"      /* ���Կ��Ź� */


#endif
