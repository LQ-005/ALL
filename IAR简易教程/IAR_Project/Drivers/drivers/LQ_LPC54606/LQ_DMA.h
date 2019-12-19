/*!
  * @file     LQ_DMA.h
  *
  * @brief    DMA�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ���ʹ����������ͷ��ɫ������ DMA0���ᱻռ��23��ͨ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_DMA_H
#define __LQ_DMA_H
#include "stdint.h"

/*! ����ͷ DMA ����ͨ��*/
#define CAMERA_DMA_CH   4U

/** ����ͷ������ɱ�־λ */
extern volatile uint8_t camera_flag;

/*!
  * @brief    ����ͷDMA�����ʼ��
  *
  * @param    srcStartAddr   ��Դ��ַ IO��ַ LQ_GPIO.h ���ж�Ӧ�궨�� ����PT0__BYTE0
  * @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����
  * @param    len            �����䳤��
  *
  * @return   ��
  *
  * @note     ���SCTʹ��ʱ������ȳ�ʼ��DMA  ʹ��DMA linkģʽ ��ռ��DMAͨ��CAMERA_DMA_CH --- CAMERA_DMA_CH + 22 ��ͨ��������(DMA���30��ͨ��������)
  *
  * @see      DMA_CameraInitConfig(&PT1__BYTE3, (uint8_t *)Image_Data, (IMAGEH * IMAGEW)); //��P1_24-P1_31 ��λ����IO���źŴ��䵽Image_Data����
  *
  * @date     2019/10/22 ���ڶ�
  */
void DMA_CameraInitConfig(void* srcStartAddr, void* dstStartAddr, uint32_t len);


/*!
  * @brief    ����ͷ���һ֡ͼ������ٴμ��ش���������
  *
  * @param    srcStartAddr   ��Դ��ַ IO��ַ LQ_GPIO.h ���ж�Ӧ�궨�� ����PT0__BYTE0
  * @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����  
  *
  * @return   ��
  *
  * @note     ���˺����ŵ����ж��� ���жϷ����� ���øú��������µ�ͼ����
  *
  * @see      DMA_CameraReload(&PT1__BYTE3, (uint8_t *)Image_Data);   //��������DMA������
  *
  * @date     2019/10/22 ���ڶ�
  */
void DMA_CameraReload(void* srcStartAddr, void* dstStartAddr);

#endif
