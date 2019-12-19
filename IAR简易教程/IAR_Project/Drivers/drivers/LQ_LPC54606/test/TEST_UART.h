/*!
  * @file     TEST_UART.h
  *
  * @brief    ���ڲ����ļ�
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
  * @date     2019/10/18 ������
  */ 
#ifndef __TEST_UART_H
#define __TEST_UART_H

/*!
  * @brief    ���ڲ�������
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     
  *
  * @example      
  *
  * @date     2019/10/31 ������
  */
void Test_UART(void);



/**
  * @brief    ���� + DMA ���Ժ���
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����USART_DMA_LEN�����ݣ� ����ӡ���� ע�����ûص���������Ҫ�Լ�д�����жϷ�����
  * @note     ����ͷĬ��ռ�� DMAͨ��CAMERA_DMA_CH --- CAMERA_DMA_CH + 22  Ĭ�ϴ���0������1������DMA
  *
  * @example  
  *
  * @date     2019/6/6 ������
  */
void Test_UART_DMA(void);

#endif
