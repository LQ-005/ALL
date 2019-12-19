/*!
  * @file     LQ_ICM20602.c
  *
  * @brief    ICM20602 SPI����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
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
  * @date     2019/10/19 ������
  */ 
#include "include.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "LQ_ICM20602.h"

/* ����ʹ�õĽ��߷�ʽ��ѡ��ͬͷ�ļ� */
#if (ICM_USE_SELECT == USE_HAL_SPI)
#include "LQ_SPI.h"

#else
#include "LQ_SOFTSPI.h"
#endif

/*!
  * @brief    ����ȷ��ʱ
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      delayms_icm(100);
  *
  * @date     2019/4/22 ����һ
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
  * @brief    ��ʼ��ICM20602 ���� ICM20602
  *
  * @param    ��
  *
  * @return   0����ʼ���ɹ�   1��ʧ��  
  *
  * @note     ʹ��SPI���߷�ʽ�ĳ�ʼ��
  *
  * @see      ICM20602_Init();
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM20602_Init(void)
{
    uint8_t res;
    res = ICM_Read_Byte(WHO_AM_I);           //��ȡICM20602��ID
    if(res == 0x12)                          //����ID��ȷ
    {
        PRINTF("ICM20602 is OK!\n");
    }
    else  
    {
        PRINTF("\r\nThe correct IMU was not detected\r\nPlease check the wiring ID=%X\r\n",res);
        return 1;
    }
    
    res = 0;
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X80);//��λICM20602
    delayms_icm(100);  //��ʱ100ms
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X00);//����ICM20602
    res += ICM_Set_Gyro_Fsr(3);					  //�����Ǵ�����,��2000dps   
    res += ICM_Set_Accel_Fsr(1);				  //���ٶȴ�����,��4g
    res += ICM_Set_Rate(1000);					  //���ò�����1000Hz
    res += ICM_Write_Byte(ICM_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
    res += ICM_Write_Byte(ICM_INT_EN_REG,0X00);   //�ر������ж�
    res += ICM_Write_Byte(ICM_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
    res += ICM_Write_Byte(ICM_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
    res += ICM_Write_Byte(ICM_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����
    
    if(res == 0)  //����Ĵ�����д��ɹ�
    {
        PRINTF("MPU set is OK!\n");
    }
    else return 1;
    
    return 0;
}




/*!
  * @brief    ���������ǲ�����Χ
  *
  * @param    fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
  *
  * @return   0 �����óɹ�  
  *
  * @note     ʹ��SPI���߷�ʽ�ĳ�ʼ��
  *
  * @see      ICM_Set_Gyro_Fsr(3);	//�����Ǵ�����,��2000dps   
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Set_Gyro_Fsr(uint8_t fsr)
{
	return ICM_Write_Byte(ICM_GYRO_CFG_REG,fsr<<3);
}



/*!
  * @brief    ���ü��ٶȼƲ�����Χ
  *
  * @param    fsr:0,��2g;  1,��4g;  2,��8g;   3,��16g
  *
  * @return   0�����óɹ�
  *
  * @note     ʹ��SPI���߷�ʽ�ĳ�ʼ��
  *
  * @see      ICM_Set_Accel_Fsr(1);				  //���ٶȴ�����,��4g
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Set_Accel_Fsr(uint8_t fsr)
{
	return ICM_Write_Byte(ICM_ACCEL_CFG_REG,fsr<<3);
}



/*!
  * @brief    �������ֵ�ͨ�˲�
  *
  * @param    lpf:���ֵ�ͨ�˲�Ƶ��(Hz) 
  *
  * @return   0�����óɹ�
  *
  * @note     ʹ��SPI���߷�ʽ�ĳ�ʼ��
  *
  * @see      ICM_Set_LPF(100); //�������ֵ�ͨ�˲�
  *
  * @date     2019/6/12 ������
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
	return ICM_Write_Byte(ICM_CFG_REG,data);//�������ֵ�ͨ�˲���  
}




/*!
  * @brief    ���ò�����
  *
  * @param    rate:4~1000(Hz)
  *
  * @return   0�����óɹ�
  *
  * @note     ʹ��SPI���߷�ʽ�ĳ�ʼ��
  *
  * @see      ICM_Set_Rate(1000);		//���ò�����1000Hz
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Set_Rate(uint16_t rate)
{
	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=ICM_Write_Byte(ICM_SAMPLE_RATE_REG,data);	    //�������ֵ�ͨ�˲���
 	return ICM_Set_LPF(rate/2);	                                //�Զ�����LPFΪ�����ʵ�һ��
}



/*!
  * @brief    ��ȡ�¶�ֵ
  *
  * @param    ��
  *
  * @return   �¶�ֵ(������100��)
  *
  * @note     �¶�ֵ(������100��)
  *
  * @see      ICM_Get_Temperature();
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ������ֵ
  *
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
  *
  * @see      int6_t data[3];
  * @see      ICM_Get_Gyroscope(&data[0], &data[1], &data[2]);
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ���ٶ�ֵ
  *
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
  *
  * @see      int6_t data[3];
  * @see      ICM_Get_Accelerometer(&data[0], &data[1], &data[2]);      
  *
  * @date     2019/6/12 ������
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
  * @brief    ��ȡ ���ٶ�ֵ ���ٶ�ֵ
  *
  * @param    ax,ay,az:������x,y,z���ԭʼ����(������)
  * @param    gx,gy,gz:������x,y,z���ԭʼ����(������)  
  *
  * @return   0����ȡ�ɹ�
  *
  * @note     ��
  *
  * @see      int6_t data[6];
  * @see      ICM_Get_Raw_data(&data[0], &data[1], &data[2],&data[3], &data[4], &data[5]);    
  *
  * @date     2019/6/12 ������
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
  * @brief    SPI ������
  *
  * @param    reg :Ҫ��ȡ�ļĴ�����ַ
  * @param    len :Ҫ��ȡ�ĳ���
  * @param    buf :��ȡ�������ݴ洢��
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      uint8_t buf[15],res;  
  * @see      res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);     
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    buf[0] = reg | 0x80;

    /* д��Ҫ���ļĴ�����ַ */
    return SPI_ReadWriteNByte(SPI3, buf, buf, len + 1);
}



/*!
  * @brief    SPI дһ���Ĵ���
  *
  * @param    reg   :Ҫд�ļĴ�����ַ
  * @param    value :Ҫд���ֵ
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      ICM_Write_Byte(ICM_SAMPLE_RATE_REG,1);	    
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //�ȷ��ͼĴ���
    buff[1] = value;        //�ٷ�������

    return SPI_ReadWriteNByte(SPI3, buff, buff, 2); //����buff�����ݣ����ɼ��� buff��  
}

/*!
  * @brief    SPI ��һ���Ĵ���
  *
  * @param    reg   :Ҫд�ļĴ�����ַ
  *
  * @return   ��ȡ��ֵ
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      ICM_Read_Byte(WHO_AM_I);          
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8_t buff[2];
    buff[0] = reg | 0x80;          //�ȷ��ͼĴ���

    SPI_ReadWriteNByte(SPI3, buff, buff, 2);
    return buff[1];
}



#else

/*!
  * @brief    SPI ������
  *
  * @param    reg :Ҫ��ȡ�ļĴ�����ַ
  * @param    len :Ҫ��ȡ�ĳ���
  * @param    buf :��ȡ�������ݴ洢��
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      uint8_t buf[15],res;  
  * @see      res=ICM_Read_Len(ICM_ACCEL_XOUTH_REG,14,buf);     
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Read_Len(uint8_t reg,uint8_t len,uint8_t *buf)
{ 
    buf[0] = reg | 0x80;

    /* д��Ҫ���ļĴ�����ַ */
    SPI_SoftRadeWriteNbyte( buf, len + 1);
    return 0;
}



/*!
  * @brief    SPI дһ���Ĵ���
  *
  * @param    reg   :Ҫд�ļĴ�����ַ
  * @param    value :Ҫд���ֵ
  *
  * @return   0 ����ȡ�ɹ�
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      ICM_Write_Byte(ICM_SAMPLE_RATE_REG,1);	    
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Write_Byte(uint8_t reg,uint8_t value)
{
    uint8_t buff[2];

    buff[0] = reg;          //�ȷ��ͼĴ���
    buff[1] = value;        //�ٷ�������

    SPI_SoftRadeWriteNbyte(buff, 2); //����buff�����ݣ����ɼ��� buff��
    return 0;
}

/*!
  * @brief    SPI ��һ���Ĵ���
  *
  * @param    reg   :Ҫд�ļĴ�����ַ
  *
  * @return   ��ȡ��ֵ
  *
  * @note     �ײ����� ��ֲʱ��Ҫ�޸�
  *
  * @see      ICM_Read_Byte(WHO_AM_I);          
  *
  * @date     2019/6/12 ������
  */
uint8_t ICM_Read_Byte(uint8_t reg)
{
    uint8_t buff[2];
    buff[0] = reg | 0x80;          //�ȷ��ͼĴ���

    SPI_SoftRadeWriteNbyte( buff, 2);
    return buff[1];
}


#endif






