/*!
  * @file     LQ_SOFTIIC.c
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
#include "LQ_SOFTIIC.h"

/*!
  * @brief    IIC��ʱ
  *
  * @param    us      ��  ��ʱʱ�� 
  *
  * @return   ��
  *
  * @note     �ڲ����� �޸�������Ե���IIC����  
  *
  * @see      iic_delay(1);  //�򵥵���ʱ
  *
  * @date     2019/10/23 ������
  */	
void iic_delay(uint8_t us)
{
    for(int i = 0; i < 30; i++) //�޸�������Ե���IIC����  
    {
        __asm("NOP");
    }
}
/*!
  * @brief    ģ��IIC��ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      IIC_Init();  //ģ��IIC��ʼ�� IIC�ܽ���LQ_SOFTIIC.h�ж���
  *
  * @date     2019/10/23 ������
  */	
void IIC_Init(void)
{			
    PIN_InitConfig(SOFT_IIC_SCL_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_IIC_SDA_PIN, PIN_MODE_OUTPUT, 1);
    
    IIC_SCL_H; 
    IIC_SDA_H;
}
/*!
  * @brief    ģ��IIC��ʼ�ź�
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      IIC_Start();  
  *
  * @date     2019/10/23 ������
  */		
void IIC_Start(void)
{
	SDA_OUT;   //sda����� 
	IIC_SDA_H;	
	IIC_SCL_H;
	iic_delay(4);
 	IIC_SDA_L; //START:when CLK is high,DATA change form high to low 
	iic_delay(4);
	IIC_SCL_L; //ǯסI2C���ߣ�׼�����ͻ�������� 
}

/*!
  * @brief    ģ��IICֹͣ�ź�
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      IIC_Stop();  
  *
  * @date     2019/10/23 ������
  */		  
void IIC_Stop(void)
{
	SDA_OUT; //sda�����
	IIC_SCL_L;
	IIC_SDA_L; //STOP:when CLK is high DATA change form low to high
    iic_delay(4);
	IIC_SCL_H; 
    iic_delay(4);
	IIC_SDA_H; //����I2C���߽����ź�
    iic_delay(4);							   	
}


/*!
  * @brief    ģ��IIC�ȴ�Ӧ���ź�
  *
  * @param    ��
  *
  * @return   1������Ӧ��ʧ��    0������Ӧ��ɹ�
  *
  * @note     �ڲ����� ��ЧӦ�𣺴ӻ���9�� SCL=0 ʱ SDA ���ӻ�����,���� SCL = 1ʱ SDA��ȻΪ��
  *
  * @see      IIC_WaitAck();  
  *
  * @date     2019/10/23 ������
  */	
uint8_t IIC_WaitAck(void)
{
	uint8_t ucErrTime=0;
	SDA_IN; //SDA����Ϊ����  ���ӻ���һ���͵�ƽ��ΪӦ�� 
	IIC_SDA_H;iic_delay(1);	   
	IIC_SCL_H;iic_delay(1);	 
	while(IIC_SDA_READ)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L; //ʱ�����0 	   
	return 0;  
} 


/*!
  * @brief    ģ��IIC����ACKӦ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     �ڲ����� ����������һ���ֽ����ݺ�����������ACK֪ͨ�ӻ�һ���ֽ���������ȷ����
  *
  * @see      IIC_Ack();  
  *
  * @date     2019/10/23 ������
  */
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_L;
	iic_delay(1);
	IIC_SCL_H;
	iic_delay(2);
	IIC_SCL_L;
}


/*!
  * @brief    ģ��IIC������ACKӦ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     �ڲ����� �������������һ���ֽ����ݺ�����������NACK֪ͨ�ӻ����ͽ������ͷ�SDA,�Ա���������ֹͣ�ź�
  *
  * @see      IIC_NAck();  
  *
  * @date     2019/10/23 ������
  */
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_H;
	iic_delay(1);
	IIC_SCL_H;
	iic_delay(1);
	IIC_SCL_L;
}					 				     

	
/*!
  * @brief    ģ��IIC����һ���ֽ�
  *
  * @param    data   :  ���͵��ֽ�
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      IIC_SendByte(0x12);  
  *
  * @date     2019/10/23 ������
  */	  
void IIC_SendByte(uint8_t data)
{                        
    uint8_t t;   
    SDA_OUT; 	    
    IIC_SCL_L; //����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {     
        if(data&0x80)
        {
            IIC_SDA_H;
        }
        else 
        {
            IIC_SDA_L;
        }
        iic_delay(1);			
        IIC_SCL_H;
        data<<=1;
        iic_delay(1);
        IIC_SCL_L;	   
    }
    iic_delay(1);
} 	 


/*!
  * @brief    ģ��IIC��ȡһ���ֽ�
  *
  * @param    ack=1 ʱ���������ݻ�û������ ack=0 ʱ����������ȫ���������
  *
  * @return   ���յ����ֽ�
  *
  * @note     �ڲ�����
  *
  * @see      IIC_ReadByte(0x12);  
  *
  * @date     2019/10/23 ������
  */	  	
uint8_t IIC_ReadByte(uint8_t ack)
{
	uint8_t i,receive=0;
	SDA_IN; //SDA����Ϊ����ģʽ �ȴ����մӻ���������
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        iic_delay(1);
        IIC_SCL_H;
        receive<<=1;
        if(IIC_SDA_READ)receive++; //�ӻ����͵ĵ�ƽ
        iic_delay(1); 
    }					 
    if(ack)
        IIC_Ack(); //����ACK 
    else
        IIC_NAck(); //����nACK  
    return receive;
}


/*!
  * @brief    ģ��IIC��ȡָ���豸 ָ���Ĵ�����һ��ֵ
  *
  * @param    I2C_Addr  Ŀ���豸��ַ
  * @param    reg       Ŀ��Ĵ���
  * @param    buf       ��Ŷ����ֽ�
  *
  * @return   1ʧ�� 0�ɹ�
  *
  * @note     ��
  *
  * @see      uint8_t data;  
  * @see      IIC_ReadByteFromSlave(0xD0, 0x75, &data);   //�� IIC��ַΪ 0xD0������MPU6050���Ĵ���0x75
  *
  * @date     2019/10/23 ������
  */	 
uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf)
{
	IIC_Start();	
	IIC_SendByte(I2C_Addr);	 //���ʹӻ���ַ
	if(IIC_WaitAck()) //����ӻ�δӦ�������ݷ���ʧ��
	{
		IIC_Stop();
		return 1;
	}
	IIC_SendByte(reg); //���ͼĴ�����ַ
	IIC_WaitAck();	  
	
	IIC_Start();
	IIC_SendByte(I2C_Addr+1); //�������ģʽ			   
	IIC_WaitAck();
	*buf=IIC_ReadByte(0);	   
    IIC_Stop(); //����һ��ֹͣ����
	return 0;
}
 
/*!
  * @brief    ģ��IIC��ȡָ���豸 ָ���Ĵ�����һ��ֵ
  *
  * @param    I2C_Addr  Ŀ���豸��ַ
  * @param    reg       Ŀ��Ĵ���
  * @param    data      д�������
  *
  * @return   1ʧ�� 0�ɹ�
  *
  * @note     ��
  *
  * @see      IIC_ReadByteFromSlave(0xD0, 0X6B, 0X80);   //IIC��ַΪ 0xD0������MPU6050���Ĵ���0x6B д��0x80
  *
  * @date     2019/10/23 ������
  */	 
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t data)
{
	IIC_Start();
	IIC_SendByte(I2C_Addr); //���ʹӻ���ַ
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_SendByte(reg); //���ͼĴ�����ַ
    IIC_WaitAck();	  
	IIC_SendByte(data); 
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //����д��ʧ��
	}
	IIC_Stop(); //����һ��ֹͣ����
    
    //return 1; //status == 0;
	return 0;
}


/*!
  * @brief    ģ��IIC��ȡָ���豸 ָ���Ĵ�����һ��ֵ
  *
  * @param    dev       Ŀ���豸��ַ
  * @param    reg       Ŀ��Ĵ���
  * @param    length    ��ȡ����
  * @param    data      ��Ŷ����ֽ�
  *
  * @return   1ʧ�� 0�ɹ�
  *
  * @note     ��
  *
  * @see      uint8_t data[14];  
  * @see      IIC_ReadByteFromSlave(0xD0, 0X3B, 14, &data);   //�� 14���ֽ�
  *
  * @date     2019/10/23 ������
  */	
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data)
{
    uint8_t count = 0;
	uint8_t temp;
	IIC_Start();
	IIC_SendByte(dev); //���ʹӻ���ַ
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_SendByte(reg); //���ͼĴ�����ַ
    IIC_WaitAck();	  
	IIC_Start();
	IIC_SendByte(dev+1); //�������ģʽ	
	IIC_WaitAck();
    for(count=0;count<length;count++)
	{
		if(count!=(length-1))
            temp = IIC_ReadByte(1); //��ACK�Ķ�����
		else  
            temp = IIC_ReadByte(0); //���һ���ֽ�NACK
        
		data[count] = temp;
	}
    IIC_Stop(); //����һ��ֹͣ����
    //return count;
    return 0;
}


/*!
  * @brief    ģ��IIC��ȡָ���豸 ָ���Ĵ�����һ��ֵ
  *
  * @param    dev       Ŀ���豸��ַ
  * @param    reg       Ŀ��Ĵ���
  * @param    length    д�볤��
  * @param    data      ���д���ֽ�
  *
  * @return   1ʧ�� 0�ɹ�
  *
  * @note     ��
  *
  * @see      IIC_WriteMultByteToSlave(0xD0, 0X6B, 1, 0X80);   //��Ĵ���0x6Bд��0x80
  *
  * @date     2019/10/23 ������
  */
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data)
{
    
 	uint8_t count = 0;
	IIC_Start();
	IIC_SendByte(dev); //���ʹӻ���ַ
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_SendByte(reg); //���ͼĴ�����ַ
    IIC_WaitAck();	  
	for(count=0;count<length;count++)
	{
		IIC_SendByte(data[count]); 
		if(IIC_WaitAck()) //ÿһ���ֽڶ�Ҫ�ȴӻ�Ӧ��
		{
			IIC_Stop();
			return 1; //����д��ʧ��
		}
	}
	IIC_Stop(); //����һ��ֹͣ����
    
	return 0;
}




