/*!
  * @file     ANO_DT.h
  *
  * @brief    ������λ������
  *
  * @company  ����
  *
  * @author   ����
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @Software IAR8.32 or MDK5.28
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __ANO_DT_H
#define __ANO_DT_H

#include "fsl_common.h"

/*!
  * @brief    ����λ�����ͷ���8��short����
  *
  * @param    data1 - data8  �� ���͸���λ����ʾ����
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      ANO_DT_send_int16(1, 2, 3, 0, 0, 0, 0, 0);
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 /*,short data7, short data8, short .....�ɸ�����Ҫ������� */);

/*!
  * @brief    ����λ�����ͷ���PID֡
  *
  * @param    group         : PID��
  * @param    p1_p - p3_d   : PID����
  *
  * @return   ��
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/6/17 ����һ
  */
void ANO_DT_Send_PID(uint8_t group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);


/**
  * @brief    �����ϱ�������λ��
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/6/17 ����һ
  */
void Test_ANO_DT(void);


/*!
  * @brief    Э�����ݽ������������������Ƿ���Э���ʽ��һ������֡���ú��������ȶ�Э�����ݽ���У��
  *
  * @param    data_buf �����ݰ�
  * @param    num      �����ݰ�����
  *
  * @return   ��
  *
  * @note     У��ͨ��������ݽ��н�����ʵ����Ӧ���� �˺������Բ����û����е��ã��ɺ���Data_Receive_Prepare�Զ�����
  *
  * @see  
  *
  * @date     2019/6/17 ����һ
  */
void ANO_DT_Data_Receive_Anl(uint8_t *data_buf,uint8_t num);

/*!
  * @brief    Э��Ԥ����������Э��ĸ�ʽ�����յ������ݽ���һ�θ�ʽ�Խ�������ʽ��ȷ�Ļ��ٽ������ݽ���
  *
  * @param    data �����ݰ�  
  *
  * @return   ��
  *
  * @note     ��ֲʱ���˺���Ӧ���û���������ʹ�õ�ͨ�ŷ�ʽ���е��ã����紮��ÿ�յ�һ�ֽ����ݣ�����ô˺���һ��
  * @note     �˺������������ϸ�ʽ������֡�󣬻����е������ݽ�������   
  *
  * @see        
  *
  * @date     2019/6/17 ����һ
  */
void ANO_DT_Data_Receive_Prepare(uint8_t data);
	
#endif

