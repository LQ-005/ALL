/*!
  * @file     LQ_PROTOCOL.h
  *
  * @brief    ������λ��ͨѶЭ��
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
  * @date     2019/11/6 ������
  */ 
#ifndef __LQ_PROTOCOL_H
#define __LQ_PROTOCOL_H

#include "stdint.h"

/* ��λ�������� */
#define   PROTOCOL_CONFIG_0  0x00   /*!< ��λ��д�����ݸ���λ��  ��λ���յ����ݲ�У��û������� ���͹�����0����λ�� */
#define   PROTOCOL_CONFIG_1  0x01   /*!< ��λ�����͹�����1 ����������  */
#define   PROTOCOL_CONFIG_2  0x02   /*!< ��λ�����͹�����2 ����PID����  */
#define   PROTOCOL_CONFIG_3  0x03   /*!< ��λ�����͹�����3 ����CCD����  */
#define   PROTOCOL_CONFIG_4  0x04   /*!< ��λ�����͹�����4 ����Ҷ�����ͷ����  */
#define   PROTOCOL_CONFIG_5  0x05   /*!< ��λ�����͹�����5 Ҫ��ȡ��λ��PID����  */
#define   PROTOCOL_CONFIG_6  0x06   /*!< ��λ�����͹�����6 Ҫд��PID����  */
#define   PROTOCOL_CONFIG_7  0x07   /*!< ��λ�����͹�����7 ��λ������1����  */
#define   PROTOCOL_CONFIG_8  0x08   /*!< ��λ�����͹�����8 ��λ������2����  */
#define   PROTOCOL_CONFIG_9  0x09   /*!< ��λ�����͹�����9 ��λ������3����  */
#define   PROTOCOL_CONFIG_A  0x0A   /*!< ��λ�����͹�����A ��λ������4����  */
#define   PROTOCOL_CONFIG_B  0x0B   /*!< ��λ�����͹�����B ��λ������5����  */
#define   PROTOCOL_CONFIG_C  0x0C   /*!< ��λ�����͹�����C ��λ������6����  */
#define   PROTOCOL_CONFIG_D  0x0D   /*!< ��λ�����͹�����D ��λ������7����  */
#define   PROTOCOL_CONFIG_E  0x0E   /*!< ��λ�����͹�����E ��λ������8����  */
#define   PROTOCOL_CONFIG_F  0x0F   /*!< ��λ�����͹�����F ��λ������9����  */
#define   PROTOCOL_CONFIG_10 0x10   /*!< ��λ�����͹�����10 �����ֵ������ͷ����  */
#define   PROTOCOL_CONFIG_11 0x11   /*!< ��λ�����͹�����11 ����RGB565����ͷ����  */
#define   PROTOCOL_CONFIG_12 0x12   /*!< ��λ�����͹�����12 ����YUV����ͷ����  */

/* �շ����������� */
#define   TX_BUFF_SIZE    100  /*!< �������ݻ�����  */
#define   RX_BUFF_SIZE    100  /*!< �������ݻ�����  */

/*!
  * @brief    �������ݸ���λ�� ��ʾ����
  *
  * @param    data    :�������ݵ��׵�ַ
  * @param    length  :�������ݵĳ��� �ֽ�   ��������֡ͷ ������ ���� У��� ֡β�� 
  *
  * @return   ��
  *
  * @note     ֻ֧��int6_t ���͵�����  �����Ҫ���͸����� ���԰�һ������ת��Ϊint6_t ����
  *
  * @see      int16_t databuff[10];
  * @see      PROTOCOL_SendWave(databuff, sizeof(databuff)); //����10������ ��Ӧ��λ��ǰʮ��ͨ��     
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendWave(int16_t *data, uint8_t length);


/*!
  * @brief    ����PID���ݸ���λ��
  *
  * @param    data    :�������ݵ��׵�ַ
  * @param    length  :�������ݵĳ����ֽ�  �ֽ�   ��������֡ͷ ������ ���� У��� ֡β�� 
  *
  * @return   ��
  *
  * @note     ֻ֧��int6_t ���͵�����  �����Ҫ���͸����� ���԰�һ������ת��Ϊint6_t ����
  *
  * @see      int16_t databuff[9];
  * @see      PROTOCOL_SendPID(databuff, sizeof(databuff)); //����9��PID���� ��Ӧ��λ��ǰ����PID     
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendPID(int16_t *data, uint8_t length);



/*!
  * @brief    ������λ������ ����Ԥ����
  *
  * @param    data  �� ����
  *
  * @return   ��
  *
  * @note     һ�㵥Ƭ��ʹ�ô����жϽ������� һ��ֻ�ܽ���һ������ 
  *
  * @see      PROTOCOL_ReceivePrepare(data);  //����������ŵ������ж��м���  data�Ǵ����жϽ��յ����ַ�
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_ReceivePrepare(uint8_t data);


/*!
  * @brief    ������λ������ ������Э����һЩ����
  *
  * @param    data    :Ҫ�������ݵ��׵�ַ
  * @param    length  :Ҫ�������ݵĳ���    �ֽ�   ������֡ͷ ������ ���� У��� ֡β��  
  *
  * @return   ��
  *
  * @note     ���յ�һ֡���ݺ� ʹ�ô˺��������ݽ��н���
  *
  * @see      uint8_t data[100];   
  * @see      PROTOCOL_ReceiveParse(data, length);  //һ��ʹ��DMA���յ�һ֡���ݴ����data�� Ȼ����øú�����Э����н���
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_ReceiveParse(uint8_t *data, uint8_t length);


/*!
  * @brief    ���� �Ҷ� ����ͷ����
  *
  * @param    data    :����ͷ���ݵ��׵�ַ
  * @param    length  :����ͷ���ݵĳ���  �ֽ�   ��������֡ͷ ������ ���� У��� ֡β�� 
  *
  * @return   ��
  *
  * @note     ����ͷ�Ҷ����� 0-0xff
  *
  * @see      uint8_t Image_Data[IMAGEH][IMAGEW]; //����ͷ����
  * @see      PROTOCOL_SendCameraGrayData((uint8_t *)Image_Data, sizeof(Image_Data)); //���������ϱ���λ��
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendCameraGrayData(uint8_t *data, uint32_t length);


/*!
  * @brief    ��ÿ���ֽڴ���һ�����ص�Ķ�ֵ������ ѹ��Ϊһ���ֽڴ���8�����ص������  
  *
  * @param    data           :����ͷ���ݵ��׵�ַ
  * @param    data_encode    :����ͷ���ݵ��׵�ַ
  * @param    length         :��ֵ������ͷ���ݵĳ���  
  *
  * @return   ��
  *
  * @note     һ���ֽ��и�λ��ʾͼ����ߵ����ص�  ��λ��ʾͼ���ұߵ����ص�  
  *
  * @see      uint8_t Pixle[IMAGEH][IMAGEW]; //����ͷ��ֵ������
  * @see      uint8_t dataencode[(IMAGEH*IMAGEW+7)/8];       //����ͷ��ֵ��ѹ���������
  * @see      PROTOCOL_DataEncode((uint8_t *)Pixle, dataencode, sizeof(Pixle)); //ѹ����ֵ������
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_DataEncode(uint8_t *data, uint8_t *data_encode, uint32_t length);


/*!
  * @brief    ���� ��ֵ�� ����ͷ����
  *
  * @param    data    :����ͷ���ݵ��׵�ַ
  * @param    length  :����ͷ���ݵĳ���  �ֽ�   ��������֡ͷ ������ ���� У��� ֡β��  
  *
  * @return   ��
  *
  * @note     һ���ֽڴ���8�����ص�   һ���ֽ��и�λ��ʾͼ����ߵ����ص�  ��λ��ʾͼ���ұߵ����ص�
  *
  * @see      uint8_t Pixle[IMAGEH][IMAGEW]; //����ͷ��ֵ������
  * @see      uint8_t dataencode[(IMAGEH*IMAGEW+7)/8];       //����ͷ��ֵ��ѹ���������
  * @see      PROTOCOL_DataEncode((uint8_t *)Pixle, dataencode, (IMAGEH*IMAGEW)); //ѹ����ֵ������
  * @see      PROTOCOL_SendCameraBinData((uint8_t *)dataencode, sizeof(dataencode)); //���������ϱ���λ��
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendCameraBinData(uint8_t *data, uint32_t length);



/*!
  * @brief    ���� RGB565 ����ͷ����
  *
  * @param    data    :����ͷ���ݵ��׵�ַ
  * @param    length  :����ͷ���ݵĳ���  �ֽ�   ��������֡ͷ ������ ���� У��� ֡β�� 
  *
  * @return   ��
  *
  * @note     С�˸�ʽ
  *
  * @see      uint16_t Image_Data[IMAGEH][IMAGEW]; //����ͷ��ֵ������
  * @see      PROTOCOL_SendCameraRGB565Data((uint16_t *)Image_Data, sizeof(Image_Data)); //���������ϱ���λ��
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendCameraRGB565Data(uint16_t *data, uint32_t length);



/*!
  * @brief    ��������ͷ����
  *
  * @param    data    :CCD���ݵ��׵�ַ
  * @param    length  :CCD���ݵĳ��ȣ�������֡ͷ ������ ���� У�飩   
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendCCDData(uint8_t *data, uint32_t length);

#endif



