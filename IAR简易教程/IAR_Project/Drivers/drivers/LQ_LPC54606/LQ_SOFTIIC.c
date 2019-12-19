/*!
  * @file     LQ_SOFTIIC.c
  *
  * @brief    模拟IIC驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/23 星期三
  */ 
#include "LQ_SOFTIIC.h"

/*!
  * @brief    IIC延时
  *
  * @param    us      ：  延时时间 
  *
  * @return   无
  *
  * @note     内部调用 修改这里可以调整IIC速率  
  *
  * @see      iic_delay(1);  //简单的延时
  *
  * @date     2019/10/23 星期三
  */	
void iic_delay(uint8_t us)
{
    for(int i = 0; i < 30; i++) //修改这里可以调整IIC速率  
    {
        __asm("NOP");
    }
}
/*!
  * @brief    模拟IIC初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      IIC_Init();  //模拟IIC初始化 IIC管脚在LQ_SOFTIIC.h中定义
  *
  * @date     2019/10/23 星期三
  */	
void IIC_Init(void)
{			
    PIN_InitConfig(SOFT_IIC_SCL_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_IIC_SDA_PIN, PIN_MODE_OUTPUT, 1);
    
    IIC_SCL_H; 
    IIC_SDA_H;
}
/*!
  * @brief    模拟IIC起始信号
  *
  * @param    无
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      IIC_Start();  
  *
  * @date     2019/10/23 星期三
  */		
void IIC_Start(void)
{
	SDA_OUT;   //sda线输出 
	IIC_SDA_H;	
	IIC_SCL_H;
	iic_delay(4);
 	IIC_SDA_L; //START:when CLK is high,DATA change form high to low 
	iic_delay(4);
	IIC_SCL_L; //钳住I2C总线，准备发送或接收数据 
}

/*!
  * @brief    模拟IIC停止信号
  *
  * @param    无
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      IIC_Stop();  
  *
  * @date     2019/10/23 星期三
  */		  
void IIC_Stop(void)
{
	SDA_OUT; //sda线输出
	IIC_SCL_L;
	IIC_SDA_L; //STOP:when CLK is high DATA change form low to high
    iic_delay(4);
	IIC_SCL_H; 
    iic_delay(4);
	IIC_SDA_H; //发送I2C总线结束信号
    iic_delay(4);							   	
}


/*!
  * @brief    模拟IIC等待应答信号
  *
  * @param    无
  *
  * @return   1，接收应答失败    0，接收应答成功
  *
  * @note     内部调用 有效应答：从机第9个 SCL=0 时 SDA 被从机拉低,并且 SCL = 1时 SDA依然为低
  *
  * @see      IIC_WaitAck();  
  *
  * @date     2019/10/23 星期三
  */	
uint8_t IIC_WaitAck(void)
{
	uint8_t ucErrTime=0;
	SDA_IN; //SDA设置为输入  （从机给一个低电平做为应答） 
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
	IIC_SCL_L; //时钟输出0 	   
	return 0;  
} 


/*!
  * @brief    模拟IIC产生ACK应答
  *
  * @param    无
  *
  * @return   无
  *
  * @note     内部调用 主机接收完一个字节数据后，主机产生的ACK通知从机一个字节数据已正确接收
  *
  * @see      IIC_Ack();  
  *
  * @date     2019/10/23 星期三
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
  * @brief    模拟IIC不产生ACK应答
  *
  * @param    无
  *
  * @return   无
  *
  * @note     内部调用 主机接收完最后一个字节数据后，主机产生的NACK通知从机发送结束，释放SDA,以便主机产生停止信号
  *
  * @see      IIC_NAck();  
  *
  * @date     2019/10/23 星期三
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
  * @brief    模拟IIC发送一个字节
  *
  * @param    data   :  发送的字节
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      IIC_SendByte(0x12);  
  *
  * @date     2019/10/23 星期三
  */	  
void IIC_SendByte(uint8_t data)
{                        
    uint8_t t;   
    SDA_OUT; 	    
    IIC_SCL_L; //拉低时钟开始数据传输
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
  * @brief    模拟IIC读取一个字节
  *
  * @param    ack=1 时，主机数据还没接收完 ack=0 时主机数据已全部接收完成
  *
  * @return   接收到的字节
  *
  * @note     内部调用
  *
  * @see      IIC_ReadByte(0x12);  
  *
  * @date     2019/10/23 星期三
  */	  	
uint8_t IIC_ReadByte(uint8_t ack)
{
	uint8_t i,receive=0;
	SDA_IN; //SDA设置为输入模式 等待接收从机返回数据
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        iic_delay(1);
        IIC_SCL_H;
        receive<<=1;
        if(IIC_SDA_READ)receive++; //从机发送的电平
        iic_delay(1); 
    }					 
    if(ack)
        IIC_Ack(); //发送ACK 
    else
        IIC_NAck(); //发送nACK  
    return receive;
}


/*!
  * @brief    模拟IIC读取指定设备 指定寄存器的一个值
  *
  * @param    I2C_Addr  目标设备地址
  * @param    reg       目标寄存器
  * @param    buf       存放读出字节
  *
  * @return   1失败 0成功
  *
  * @note     无
  *
  * @see      uint8_t data;  
  * @see      IIC_ReadByteFromSlave(0xD0, 0x75, &data);   //读 IIC地址为 0xD0器件（MPU6050）寄存器0x75
  *
  * @date     2019/10/23 星期三
  */	 
uint8_t IIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf)
{
	IIC_Start();	
	IIC_SendByte(I2C_Addr);	 //发送从机地址
	if(IIC_WaitAck()) //如果从机未应答则数据发送失败
	{
		IIC_Stop();
		return 1;
	}
	IIC_SendByte(reg); //发送寄存器地址
	IIC_WaitAck();	  
	
	IIC_Start();
	IIC_SendByte(I2C_Addr+1); //进入接收模式			   
	IIC_WaitAck();
	*buf=IIC_ReadByte(0);	   
    IIC_Stop(); //产生一个停止条件
	return 0;
}
 
/*!
  * @brief    模拟IIC读取指定设备 指定寄存器的一个值
  *
  * @param    I2C_Addr  目标设备地址
  * @param    reg       目标寄存器
  * @param    data      写入的数据
  *
  * @return   1失败 0成功
  *
  * @note     无
  *
  * @see      IIC_ReadByteFromSlave(0xD0, 0X6B, 0X80);   //IIC地址为 0xD0器件（MPU6050）寄存器0x6B 写入0x80
  *
  * @date     2019/10/23 星期三
  */	 
uint8_t IIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t data)
{
	IIC_Start();
	IIC_SendByte(I2C_Addr); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	IIC_SendByte(data); 
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //数据写入失败
	}
	IIC_Stop(); //产生一个停止条件
    
    //return 1; //status == 0;
	return 0;
}


/*!
  * @brief    模拟IIC读取指定设备 指定寄存器的一个值
  *
  * @param    dev       目标设备地址
  * @param    reg       目标寄存器
  * @param    length    读取长度
  * @param    data      存放读出字节
  *
  * @return   1失败 0成功
  *
  * @note     无
  *
  * @see      uint8_t data[14];  
  * @see      IIC_ReadByteFromSlave(0xD0, 0X3B, 14, &data);   //读 14个字节
  *
  * @date     2019/10/23 星期三
  */	
uint8_t IIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data)
{
    uint8_t count = 0;
	uint8_t temp;
	IIC_Start();
	IIC_SendByte(dev); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop(); 
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	IIC_Start();
	IIC_SendByte(dev+1); //进入接收模式	
	IIC_WaitAck();
    for(count=0;count<length;count++)
	{
		if(count!=(length-1))
            temp = IIC_ReadByte(1); //带ACK的读数据
		else  
            temp = IIC_ReadByte(0); //最后一个字节NACK
        
		data[count] = temp;
	}
    IIC_Stop(); //产生一个停止条件
    //return count;
    return 0;
}


/*!
  * @brief    模拟IIC读取指定设备 指定寄存器的一个值
  *
  * @param    dev       目标设备地址
  * @param    reg       目标寄存器
  * @param    length    写入长度
  * @param    data      存放写入字节
  *
  * @return   1失败 0成功
  *
  * @note     无
  *
  * @see      IIC_WriteMultByteToSlave(0xD0, 0X6B, 1, 0X80);   //相寄存器0x6B写入0x80
  *
  * @date     2019/10/23 星期三
  */
uint8_t IIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data)
{
    
 	uint8_t count = 0;
	IIC_Start();
	IIC_SendByte(dev); //发送从机地址
	if(IIC_WaitAck())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_SendByte(reg); //发送寄存器地址
    IIC_WaitAck();	  
	for(count=0;count<length;count++)
	{
		IIC_SendByte(data[count]); 
		if(IIC_WaitAck()) //每一个字节都要等从机应答
		{
			IIC_Stop();
			return 1; //数据写入失败
		}
	}
	IIC_Stop(); //产生一个停止条件
    
	return 0;
}




