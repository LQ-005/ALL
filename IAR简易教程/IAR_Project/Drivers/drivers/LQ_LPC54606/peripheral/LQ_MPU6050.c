/*!
  * @file     LQ_MPU6050.c
  *
  * @brief    MPU6050/ICM20602驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     MPU6050/ICM20602使用IIC驱动时，除了芯片ID不一样 其他一致
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "config.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_MPU6050.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"

/* 根据使用的接线方式，选择不同头文件 */
#if (IMU_USE_SELECT == USE_HAL_IIC)
#include "LQ_IIC.h"

#else
#include "LQ_SOFTIIC.h"

#endif


/**
  * @brief    不精确延时
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @example  delayms_mpu(100);
  *
  * @date     2019/4/22 星期一
*/
void delayms_mpu(uint16_t ms)
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


/**
  * @brief    初始化MPU6050 或者 ICM20602
  *
  * @param    无
  *
  * @return   0：初始化成功   1：失败  
  *
  * @note     使用前先初始化IIC接口
  *
  * @see      MPU6050_Init();
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU6050_Init(void)
{
    uint8_t res;
    res = MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);           //读取MPU6050的ID
    if(res == MPU6050_ID)                                 //器件ID正确
    {
        PRINTF("MPU6050 is OK!\n");
    }
    else if(res == 0x12)                                  //ICM20602 器件ID正确
    {
        
        PRINTF("ICM20602 is OK!\n");
    }
    else  
    {
        PRINTF("\r\nThe correct IMU was not detected\r\nPlease check the wiring ID=%X\r\n",res);
        return 1;
    }
    
    res = 0;
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU6050
    delayms_mpu(100);  //延时100ms
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU6050
    res += MPU_Set_Gyro_Fsr(3);					        	   //陀螺仪传感器,±2000dps   
    res += MPU_Set_Accel_Fsr(1);					       	   //加速度传感器,±4g
    res += MPU_Set_Rate(1000);						       	   //设置采样率1000Hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //设置数字低通滤波器   98hz
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
    res += MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作
    
    if(res == 0)  //上面寄存器都写入成功
    {
        PRINTF("MPU set is OK!\n");
    }
    else return 1;
    
    return 0;
}




/**
  * @brief    设置陀螺仪测量范围
  *
  * @param    fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
  *
  * @return   0 ：设置成功  
  *
  * @note     无
  *
  * @see      MPU_Set_Gyro_Fsr(3);		  //陀螺仪传感器,±2000dps 
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}



/**
  * @brief    设置加速度计测量范围
  *
  * @param    fsr:0,±2g;1,±4g;2,±8g;3,±16g
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_Accel_Fsr(1);		  //加速度传感器,±4g
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}



/**
  * @brief    设置数字低通滤波
  *
  * @param    lpf:数字低通滤波频率(Hz) 
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_LPF(100);
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Set_LPF(uint16_t lpf)
{
	uint8_t data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}




/**
  * @brief    设置采样率
  *
  * @param    rate:4~1000(Hz)
  *
  * @return   0：设置成功
  *
  * @note     无
  *
  * @see      MPU_Set_Rate(1000);       	   //设置采样率1000Hz
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,data);	    //设置数字低通滤波器
 	return MPU_Set_LPF(rate/2);	                                //自动设置LPF为采样率的一半
}



/**
  * @brief    获取温度值
  *
  * @param    无
  *
  * @return   温度值(扩大了100倍)
  *
  * @note     无
  *
  * @see      int16_t temp = MPU_Get_Temperature();
  *
  * @date     2019/6/12 星期三
  */
short MPU_Get_Temperature(void)
{
    uint8_t buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU6050_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((uint16_t)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return (short)temp*100;
}





/**
  * @brief    获取陀螺仪值
  *
  * @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      int6_t data[3];
  * @see      MPU_Get_Gyroscope(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[6],res; 
	res=MPU_Read_Len(MPU6050_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((uint16_t)buf[0]<<8)|buf[1];  
		*gy=((uint16_t)buf[2]<<8)|buf[3];  
		*gz=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;
}




/**
  * @brief    获取加速度值
  *
  * @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
  *
  * @return   0：读取成功
  *
  * @note     无
  *
  * @see      int6_t data[3];
  * @see      MPU_Get_Accelerometer(&data[0], &data[1], &data[2]); 
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[6],res;  
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];  
		*ay=((uint16_t)buf[2]<<8)|buf[3];  
		*az=((uint16_t)buf[4]<<8)|buf[5];
	} 	
    return res;
}




/**
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
uint8_t MPU_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
    uint8_t buf[14],res;  
	res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
	if(res==0)
	{
		*ax=((uint16_t)buf[0]<<8)|buf[1];  
		*ay=((uint16_t)buf[2]<<8)|buf[3];  
		*az=((uint16_t)buf[4]<<8)|buf[5];
        *gx=((uint16_t)buf[8]<<8)|buf[9];  
		*gy=((uint16_t)buf[10]<<8)|buf[11];  
		*gz=((uint16_t)buf[12]<<8)|buf[13];
	} 	
    return res;
}


#if (IMU_USE_SELECT == USE_HAL_IIC)
/**
  * @brief    IIC 连续读
  *
  * @param    addr:器件地址 
  * @param    reg :要读取的寄存器地址
  * @param    len :要读取的长度
  * @param    buf :读取到的数据存储区
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      uint8_t buf[14];  
  * @see      MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);  
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    return IIC_ReadReg(I2C1, addr, reg, buf, len);     
}



/**
  * @brief    IIC 写一个寄存器
  *
  * @param    addr  :器件地址 
  * @param    reg   :要写的寄存器地址
  * @param    value :要写入的值
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,1);	
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t value)
{
    return IIC_WriteReg(I2C1, addr, reg, value);    
}

/**
  * @brief    IIC 读一个寄存器
  *
  * @param    addr  :器件地址 
  * @param    reg   :要写的寄存器地址
  *
  * @return   读取的值
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);   
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t value[1];
    IIC_ReadReg(I2C1, addr, reg, value, 1);
    return value[0];
}



#else


/**
  * @brief    IIC 连续读
  *
  * @param    addr:器件地址 
  * @param    reg :要读取的寄存器地址
  * @param    len :要读取的长度
  * @param    buf :读取到的数据存储区
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      uint8_t buf[14];  
  * @see      MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);     
}



/**
  * @brief    IIC 写一个寄存器
  *
  * @param    addr  :器件地址 
  * @param    reg   :要写的寄存器地址
  * @param    value :要写入的值
  *
  * @return   0 ：读取成功
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,1);	
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t value)
{
    return IIC_WriteByteToSlave(addr<<1, reg, value);    
}


/**
  * @brief    IIC 读一个寄存器
  *
  * @param    addr  :器件地址 
  * @param    reg   :要写的寄存器地址
  *
  * @return   读取的值
  *
  * @note     底层驱动 移植时需要修改
  *
  * @see      MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);        
  *
  * @date     2019/6/12 星期三
  */
uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t value[1];
    MPU_Read_Len(addr, reg, 1, value);
    return value[0];
}


#endif






