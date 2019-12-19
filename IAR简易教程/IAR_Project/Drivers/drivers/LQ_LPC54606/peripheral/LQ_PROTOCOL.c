/*!
  * @file     LQ_PROTOCOL.c
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

#include "LQ_PROTOCOL.h"


/* ���ݲ�ֺ궨�壬�ڷ���int16_t��������ʱ,��Ҫ�����ݲ�ֳɵ����ֽڽ��з��� */
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )  /*!< int16_t ���ݲ�� byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )    /*!< int16_t ���ݲ�� byte1  */


/* �����Լ��������ݵ�ʵ�ַ�ʽ */
#include "LQ_UART.h"
/*!
  * @brief    ��������  �ײ�
  *
  * @param    data    :�������ݵ��׵�ַ
  * @param    length  :�������ݵĳ��� �ֽ�
  *
  * @return   
  *
  * @note     ��ֲ��ʱ�򣬽�����ĳ��Լ���ʵ�ַ�ʽ����
  *
  * @see      
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendData(uint8_t *data , uint32_t length)
{
    /**ʹ�ô��������������ݣ������Ҫ1.5ms*/
	UART_PutBuff(USART1, data, length);     //�����޸Ĳ�ͬ�Ĵ��ڷ�������
}


/*!
  * @brief    У������  �ײ��û������ע
  *
  * @param    data    :�������ݵ��׵�ַ
  * @param    length  :�������ݵĳ��� �ֽ�
  *
  * @return   У��ֵ
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/11/6 ������
  */
uint8_t PROTOCOL_CheckSum(uint8_t *data , uint8_t length)
{
    uint8_t sum = 0;
    uint16_t temp = 0;
    while(length--)
    {
        sum += data[temp++];
    }
    return sum;
}

/** �շ����ݻ����� */
static uint8_t tx_buff[TX_BUFF_SIZE]; 

/** �շ����ݻ����� */
static uint8_t rx_buff[RX_BUFF_SIZE]; 

/*!
  * @brief    �������ݸ���λ��   �ײ��û������ע
  *
  * @param    config  :������
  * @param    data    :�������ݵ��׵�ַ
  * @param    length  :�������ݵĳ��� �ֽ�   ��������֡ͷ ������ ���� У��� ֡β�� 
  *
  * @return   ��
  *
  * @note     ֻ֧��int6_t ���͵�����  �����Ҫ���͸����� ���԰�һ������ת��Ϊint6_t ����
  *
  * @see      int16_t databuff[10];
  * @see      PROTOCOL_Send(PROTOCOL_CONFIG_1, databuff, sizeof(databuff)); //����10������ ��Ӧ��λ��ǰʮ��ͨ��
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_Send(uint8_t config, int16_t *data, uint8_t length)
{
    uint8_t _cnt=0;
    
    tx_buff[_cnt++] = 'L';                /*!< ֡ͷ */
	tx_buff[_cnt++] = 'Q';                /*!< ֡ͷ */
    tx_buff[_cnt++] = config;              /*!< ������ */
    tx_buff[_cnt++] = length;              /*!< ���ݳ��� */
    
    /* ��䷢�ͻ����� */
    for(int i = 0; i < length/2; i++)
    {
        tx_buff[_cnt++] = BYTE1(data[i]);
        tx_buff[_cnt++] = BYTE0(data[i]);
    }
    
    /* ���У��� */
    tx_buff[_cnt] = PROTOCOL_CheckSum(tx_buff, _cnt);
    
    _cnt++;
    
	/* ���֡β */
    tx_buff[_cnt++] = 'O';
	
    /* ���ͳ�ȥ */
    PROTOCOL_SendData(tx_buff, _cnt);
}


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
void PROTOCOL_SendWave(int16_t *data, uint8_t length)
{
    PROTOCOL_Send(PROTOCOL_CONFIG_1, data, length);
}


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
void PROTOCOL_SendPID(int16_t *data, uint8_t length)
{
    PROTOCOL_Send(PROTOCOL_CONFIG_2, data, length);
}



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
void PROTOCOL_ReceivePrepare(uint8_t data)
{
	static uint8_t _data_len = 0,_data_cnt = 0;
	static uint8_t state = 0;
    
    /* ���֡ͷ */
    if(state==0 && data=='L')
	{
		state = 1;
		rx_buff[0] = data;
	}
	else if(state==1 && data=='Q')
	{
		state = 2;
		rx_buff[1] = data;
	}
    /* ������ */
	else if(state==2)
	{
		state = 3;
		rx_buff[2] = data;
	}
    /* ���ݳ��� */
	else if(state==3)
	{
		state = 4;
		rx_buff[3] = data;
        _data_len = data;
        _data_cnt = 4;
	}
    /* �������� */
	else if(state==4 && _data_len>0)
	{
		_data_len--;
		rx_buff[_data_cnt++] = data;
		if(_data_len==0)
			state = 5;
	}
    /* ����У�����ݲ�У�� */
	else if(state==5)
	{
		rx_buff[_data_cnt++]=data;
        
        if(PROTOCOL_CheckSum(rx_buff, _data_cnt-1) == data)
        {
			state = 6;
        }
        else
        {
			state = 0;
            //У��ʧ��
        }
	}
	/* ����֡β �����봦���� ����Э�������ݴ��� */
	else if(state==6)
	{
		state = 0;
		
		rx_buff[_data_cnt++]=data;
        
        if('O' == data)
        {
            PROTOCOL_ReceiveParse(rx_buff,_data_cnt);
        }
        else
        {
            //֡β���� ͨ��ʧ��
        }
	}
	else
    {
        state = 0;
    }	
}

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
void PROTOCOL_ReceiveParse(uint8_t *data, uint8_t length)
{
    /* �ٴ�У�� ֡�Ƿ���ȷ */
    if(*data == 'L' && *(data+1) == 'Q' && *(data + length-1) == 'O' && PROTOCOL_CheckSum(data, length-2) == *(data + length-2))
    {
        /* ���ݹ����� ����ͬ�Ĵ��� */
        switch (data[2])
        {
          /*!< ��λ�����͹�����5 Ҫ��ȡ��λ��PID����  */
          case PROTOCOL_CONFIG_5:
            {
                /* �û����� �����PID���� ���浽temp_data�в����ͳ�ȥ ע��temp_data��int16_t ������PID�����Ǹ����� ���԰��������� */
                int16_t temp_senddata[18] = {1, 2, 3, 4, 5, 6, 7, 8, 30000, -1, -2, -3, -4, -5, -6, -7, -8, -30000};
                PROTOCOL_SendPID(&temp_senddata[0], sizeof(temp_senddata));
                
                break;
            }
          /*!< ��λ�����͹�����6 Ҫд��PID����  */  
          case PROTOCOL_CONFIG_6:
            {
//                int16_t temp_recivedata[18];
//                /* �û����� ���������ݸ�ֵ����� PID  */
//                temp_recivedata[0] = (short)(*(rx_buff+4)<<8)|*(rx_buff+5);
//                temp_recivedata[1] = (short)(*(rx_buff+6)<<8)|*(rx_buff+7);
//                temp_recivedata[2] = (short)(*(rx_buff+8)<<8)|*(rx_buff+9);
//                temp_recivedata[3] = (short)(*(rx_buff+10)<<8)|*(rx_buff+11);
//                temp_recivedata[4] = (short)(*(rx_buff+12)<<8)|*(rx_buff+13);
//                temp_recivedata[5] = (short)(*(rx_buff+14)<<8)|*(rx_buff+15);
//                temp_recivedata[6] = (short)(*(rx_buff+16)<<8)|*(rx_buff+17);
//                temp_recivedata[7] = (short)(*(rx_buff+18)<<8)|*(rx_buff+19);
//                temp_recivedata[8] = (short)(*(rx_buff+20)<<8)|*(rx_buff+21);
//                temp_recivedata[9] = (short)(*(rx_buff+22)<<8)|*(rx_buff+23);
//                temp_recivedata[10] = (short)(*(rx_buff+24)<<8)|*(rx_buff+25);
//                temp_recivedata[11] = (short)(*(rx_buff+26)<<8)|*(rx_buff+27);
//                temp_recivedata[12] = (short)(*(rx_buff+28)<<8)|*(rx_buff+29);
//                temp_recivedata[13] = (short)(*(rx_buff+30)<<8)|*(rx_buff+31);
//                temp_recivedata[14] = (short)(*(rx_buff+32)<<8)|*(rx_buff+33);
//                temp_recivedata[15] = (short)(*(rx_buff+34)<<8)|*(rx_buff+35);
//                temp_recivedata[16] = (short)(*(rx_buff+36)<<8)|*(rx_buff+37);
//                temp_recivedata[17] = (short)(*(rx_buff+38)<<8)|*(rx_buff+39);

                break;
            }
          case PROTOCOL_CONFIG_7:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_8:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_9:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_A:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_B:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_C:
            {
                /* �û�����  */

                break;
            }
          case PROTOCOL_CONFIG_D:
            {
                /* �û�����  */


                break;
            }
          case PROTOCOL_CONFIG_E:
            {
                /* �û�����  */

                
                break;
            }
          case PROTOCOL_CONFIG_F:
            {
                /* �û�����  */

                
                break;
            }
            
        }
        
        
    }
    else
    {
       //У��ʧ�� 
    }

            
}


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
void PROTOCOL_SendCameraGrayData(uint8_t *data, uint32_t length)
{
    /* ����֡ͷ */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_4;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* ����ͼ������ */
    PROTOCOL_SendData(data, length);
	
	/* ����У�� ��������ͷ���ݱȽ϶� ����ʹ�ù̶�У�� 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);

}


/*!
  * @brief    ��ÿ���ֽڴ���һ�����ص�Ķ�ֵ������ ѹ��Ϊһ���ֽڴ���8�����ص������  
  *
  * @param    data           :����ͷ���ݵ��׵�ַ
  * @param    data_encode    :ѹ��������ͷ���ݵ��׵�ַ
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
void PROTOCOL_DataEncode(uint8_t *data, uint8_t *data_encode, uint32_t length)
{
	uint32_t len = (length+7)/8;
	uint32_t temp = 0;
	for(uint32_t i = 0; i < len; i++)
	{
		data_encode[i]   = ( ((data[0+temp]&0x01)<<7) + ((data[1+temp]&0x01)<<6) + ((data[2+temp]&0x01)<<5 )
		                   | ((data[3+temp]&0x01)<<4) + ((data[4+temp]&0x01)<<3) + ((data[5+temp]&0x01)<<2 )
		                   | ((data[6+temp]&0x01)<<1) + ((data[7+temp]&0x01)<<0));
		temp += 8;
	}
}



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
void PROTOCOL_SendCameraBinData(uint8_t *data, uint32_t length)
{
    /* ����֡ͷ */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_10;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* ����ͼ������ */
    PROTOCOL_SendData((uint8_t *)data, length);
	
	/* ����У�� ��������ͷ���ݱȽ϶� ����ʹ�ù̶�У�� 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);
}



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
void PROTOCOL_SendCameraRGB565Data(uint16_t *data, uint32_t length)
{
    /* ����֡ͷ */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_11;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
	
    /* ����ͼ������ */
    PROTOCOL_SendData((uint8_t *)data, length);
	
	/* ����У�� ��������ͷ���ݱȽ϶� ����ʹ�ù̶�У�� 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);
}





/*!
  * @brief    ��������ͷ����
  *
  * @param    data    :CCD���ݵ��׵�ַ
  * @param    length  :CCD���ݵĳ���  �ֽ�   ��������֡ͷ ������ ���� У��� ֡β��  
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      
  *
  * @date     2019/11/6 ������
  */
void PROTOCOL_SendCCDData(uint8_t *data, uint32_t length)
{
    /* ����֡ͷ */
    uint8_t temp_data[4];
    temp_data[0] = 'L';
	temp_data[1] = 'Q';
    temp_data[2] = PROTOCOL_CONFIG_11;
    temp_data[3] = length;
    PROTOCOL_SendData(temp_data, sizeof(temp_data));
    
    /* ����ͼ������ */
    PROTOCOL_SendData(data, length);
	
	/* ����У�� �������ݱȽ϶� ����ʹ�ù̶�У�� 0xff*/
	temp_data[0] = 0xff;
	temp_data[1] = 'O';
	PROTOCOL_SendData(temp_data, 2);

}
