/*!
  * @file     LQ_ICM20602.c
  *
  * @brief    ICM20602 SPI驱动
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @Software IAR8.32 or MDK5.28
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 星期六
  */ 
#include "include.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_ICM20602.h"

/* 根据使用的接线方式，选择不同头文件 */
#if (ICM_USE_SELECT == USE_HAL_SPI)
#include "LQ_SPI.h"

#else
#include "LQ_SOFTSPI.h"
#endif

/*!
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      delayms_icm(100);
  *
  * @date     2019/4/22 星期一
*/
void delayms_icm(uint16_t ms)
{
	volatile uint32_t i = 0;
	while(ms--)
	{
		for (i = 0; i < 30000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}	
}




/*!
  * @brief    初始化ICM20602 或者 ICM20602
  *
  * @param    无
  *
  * @return   0：初始化成功   1：失败  
  *
  * @note     使用SPI接线方式的初始化
  *
  * @see      ICM20602_Init();
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM20602_Init(void)
{
    uint8_t res;
    res = ICM_Read_Byte(WHO_AM_I);           //读取ICM20602的ID
    if(res == 0x12)                          //器件ID正确
    {
        PRINTF("ICM20602 is OK!\n");
    }
    else  
    {
        PRINTF("\r\nThe correct IMU was not detected\r\nPlease check the wiring ID=%X\r\n",res);
        return 1;
    }
    
    res = 0;
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//复位ICM20602
    delayms_icm(100);  //延时100ms
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//唤醒ICM20602
    res += ICM_Set_Gyro_Fsr(3);					  //陀螺仪传感器,±2000dps   
    res += ICM_Set_Accel_Fsr(1);				  //加速度传感器,±4g
    res += ICM_Set_Rate(1000);					  //设置采样率1000Hz
    res += ICM_Write_Byte(ICM_CFG_REG,0x02);      //设置数字低通滤波器   98hz
    res += ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //关闭所有中断
    res += ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C主模式关闭
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
    res += ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作
    
    if(res == 0)  //上面寄存器都写入成功
    {
        PRINTF("MPU set is OK!\n");
    }
    else return 1;
    
    return 0;
}




/*!
  * @brief    设置陀螺仪测量范围
  *
  * @param    fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
  *
  * @return   0 ：设置成功  
  *
  * @note     使用SPI接线方式的初始化
  *
  * @see      ICM_Set_Gyro_Fsr(3);	//陀螺仪传感器,±2000dps   
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Set_Gyro_Fsr(uint8_t fsr)
{
	return ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);
}



/*!
  * @brief    设置加速度计测量范围
  *
  * @param    fsr:0,±2g;  1,±4g;  2,±8g;   3,±16g
  *
  * @return   0：设置成功
  *
  * @note     使用SPI接线方式的初始化
  *
  * @see      ICM_Set_Accel_Fsr(1);				  //加速度传感器,±4g
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Set_Accel_Fsr(uint8_t fsr)
{
	return ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);
}



/*!
  * @brief    设置数字低通滤波
  *
  * @param    lpf:数字低通滤波频率(Hz) 
  *
  * @return   0：设置成功
  *
  * @note     使用SPI接线方式的初始化
  *
  * @see      ICM_Set_LPF(100); //设置数字低通滤波
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return ICM_Write_Byte(ICM_CFG_REG,data);//设置数字低通滤波器  
}




/*!
  * @brief    设置采样率
  *
  * @param    rate:4~1000(Hz)
  *
  * @return   0：设置成功
  *
  * @note     使用SPI接线方式的初始化
  *
  * @see      ICM_Set_Rate(1000);		//设置采样率1000Hz
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=ICM_Write_Byte(ICM_SAMPLE_RATE_REG,data);	    //设置数字低通滤波器
 	return ICM_Set_LPF(rate/2);	                                //自动设置LPF为采样率的一半
}



/*!
  * @brief    获取温度值
  *
  * @param    无
  *
  * @return   温度值(扩大了100倍)
  *
  * @note     温度值(扩大了100倍)
  *
  * @see      ICM_Get_Temperature();
  *
  * @date     2019/6/12 星期三
  */
short ICM_Get_Temperature(void)
{
    uint8_t buf[3]; 
    short raw;
	float temp;
	ICM_Read_Len(ICM_TEMP_OUTH_REG,2,buf); 
    raw=((uint16_t)buf[1]<<8)|buf[2];  
    temp=21+((double)raw)/333.87;  
    return (short)temp*100;
}





/*!
  * @brief    获取陀螺仪值
  *
  * @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      int6_t data[3];
  * @see      ICM_Get_Gyroscope(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[7],res; 
	res=ICM_Read_Len(ICM_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16_t)buf[1]<<8)|buf[2];  
		*gy=((uint16_t)buf[3]<<8)|buf[4];  
		*gz=((uint16_t)buf[5]<<8)|buf[6];
	} 	
    return res;
}




/*!
  * @brief    获取加速度值
  *
  * @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      int6_t data[3];
  * @see      ICM_Get_Accelerometer(&data[0], &data[1], &data[2]);      
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[7],res;  
	res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[1]<<8)|buf[2];  
		*ay=((uint16_t)buf[3]<<8)|buf[4];  
		*az=((uint16_t)buf[5]<<8)|buf[6];
	} 	
    return res;
}




/*!
  * @brief    获取 加速度值 角速度值
  *
  * @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
  * @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)  
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      int6_t data[6];
  * @see      ICM_Get_Raw_data(&data[0], &data[1], &data[2],&data[3], &data[4], &data[5]);    
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
    uint8_t buf[15],res;  
	res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[1]<<8)|buf[2];  
		*ay=((uint16_t)buf[3]<<8)|buf[4];  
		*az=((uint16_t)buf[5]<<8)|buf[6];
        *gx=((uint16_t)buf[9]<<8)|buf[10];  
		*gy=((uint16_t)buf[11]<<8)|buf[12];  
		*gz=((uint16_t)buf[13]<<8)|buf[14];
	} 	
    return res;
}



#if (ICM_USE_SELECT == USE_HAL_SPI)

/*!
  * @brief    SPI 连续读
  *
  * @param    reg :要读取的寄存器地址
  * @param    len :要读取的长度
  * @param    buf :读取到的数据存储区
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      uint8_t buf[15],res;  
  * @see      res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);     
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    buf[0] = reg | 0x80;

    /* 写入要读的寄存器地址 */
    return SPI_ReadWriteNByte(SPI3, buf, buf, len + 1);
}



/*!
  * @brief    SPI 写一个寄存器
  *
  * @param    reg   :要写的寄存器地址
  * @param    value :要写入的值
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      ICM_Write_Byte(ICM_SAMPLE_RATE_REG,1);	    
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //先发送寄存器
    buff[1] = value;        //再发送数据

    return SPI_ReadWriteNByte(SPI3, buff, buff, 2); //发送buff里数据，并采集到 buff里  
}

/*!
  * @brief    SPI 读一个寄存器
  *
  * @param    reg   :要写的寄存器地址
  *
  * @return   读取的值
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      ICM_Read_Byte(WHO_AM_I);          
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8_t buff[2];
    buff[0] = reg | 0x80;          //先发送寄存器

    SPI_ReadWriteNByte(SPI3, buff, buff, 2);
    return buff[1];
}



#else

/*!
  * @brief    SPI 连续读
  *
  * @param    reg :要读取的寄存器地址
  * @param    len :要读取的长度
  * @param    buf :读取到的数据存储区
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      uint8_t buf[15],res;  
  * @see      res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);     
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    buf[0] = reg | 0x80;

    /* 写入要读的寄存器地址 */
    SPI_SoftRadeWriteNbyte( buf, len + 1);
    return 0;
}



/*!
  * @brief    SPI 写一个寄存器
  *
  * @param    reg   :要写的寄存器地址
  * @param    value :要写入的值
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      ICM_Write_Byte(ICM_SAMPLE_RATE_REG,1);	    
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //先发送寄存器
    buff[1] = value;        //再发送数据

    SPI_SoftRadeWriteNbyte(buff, 2); //发送buff里数据，并采集到 buff里
    return 0;
}

/*!
  * @brief    SPI 读一个寄存器
  *
  * @param    reg   :要写的寄存器地址
  *
  * @return   读取的值
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      ICM_Read_Byte(WHO_AM_I);          
  *
  * @date     2019/6/12 星期三
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8_t buff[2];
    buff[0] = reg | 0x80;          //先发送寄存器

    SPI_SoftRadeWriteNbyte( buff, 2);
    return buff[1];
}


#endif






