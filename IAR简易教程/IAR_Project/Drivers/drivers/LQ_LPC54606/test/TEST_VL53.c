/*!
  * @file     TEST_VL53.c
  *
  * @brief    VL53�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 ������
  */ 

#include "config.h"
#include "stdio.h"
#include "fsl_debug_console.h"
#include "TEST_VL53.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "LQ_LED.h"
#include "LQ_GPIO.h"
/* ����ʹ�õĽ��߷�ʽ��ѡ��ͬͷ�ļ� */
#if (VL53_USE_SELECT == USE_HAL_IIC)
#include "LQ_IIC.h"

#else
#include "LQ_SOFTIIC.h"

#endif

/* �����ⲿ��ʱ���� */
extern void delayms(uint16_t ms);


/**
  * @brief    ����VL53
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @example  
  *
  * @date     2019/4/17 ������
  */
void Test_Vl53(void)
{
    LED_Init();
	PRINTF("\r\nLQ VL53 Test");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ VL53 Test");
#else
	TFTSPI_Init(1);                //TFT1.8��ʼ��  0��������ʾ  1��������ʾ  
    TFTSPI_CLS(u16BLUE);           //����
	TFTSPI_P8X16Str(0,0,"LQ VL53 Test",u16RED,u16BLUE);
#endif
	char txt[16];
	
#if (VL53_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#else
    IIC_Init(); 
#endif       

    uint8_t VL53_STAR = 0x02;    //0x02 ��������ģʽ    0x01 ���β���ģʽ
    uint8_t dis_buff[2];
    uint16_t dis, last_dis;
	/* ��ʼ��� */
    VL53_Write_Byte(VL53ADDR, VL53L0X_REG_SYSRANGE_START, VL53_STAR);
    while(1)
    {
        /* ��ȡ�������� */
		VL53_Read_nByte(VL53ADDR, VL53_REG_DIS, 2, dis_buff);
    
        /* ת������ */
        dis = (dis_buff[0]<<8) | (dis_buff[1]);
        
        /* ����2Mû���ϰ� */
        if(dis > 8000)
        {
            dis = 0;
        }
     
        if(dis == 20)
        {
            dis = last_dis;
        }
        last_dis = dis;
		sprintf(txt, "DIS %5d mm",dis);
#ifdef OLED
		LCD_P8x16Str(0,5,txt);
#else
		TFTSPI_P8X16Str(2,5,txt,u16RED,u16BLUE);
#endif
		delayms(50);
		LED_ColorReverse(blue);
    
    }
    
}




/* VL53 Ƭѡ�� */
#define VL53_CS_PIN  P1_13

/**
  * @brief    ����VL53
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����һ·IIC������VL53  VL53ģ���IIC��ַ�����ó����޸ģ������ϵ��ʱ��
  *           Ĭ��IIC��ַ����0x29    �����޸ĵ�ַ��ʱ����ʧ��һ��ģ�飨XS���ͣ����޸�ʹ��ģ���
  *           IIC��ַ���޸�����ٽ�ģ��ʹ�ܣ�����ģ��ĵ�ַ��ͬ�ˣ��Ϳ��԰���ͬ��ַ�����ˡ�
  *
  * @example  
  *
  * @date     2019/4/17 ������
  */
void Test_Vl53_TWO(void)
{

    /* ��ʼ�� A3��Ϊ һ��VL53 ��XSʹ�ܹܽ� */
    PIN_InitConfig(VL53_CS_PIN, PIN_MODE_OUTPUT, 0);  
    
    LED_Init();
	PRINTF("\r\nLQ VL53 Test");
	
#ifdef OLED
	LCD_Init();
    LCD_CLS();
	LCD_P8x16Str(5,0,"LQ VL53 Test");
#else
	TFTSPI_Init(1);                //TFT1.8��ʼ��  0��������ʾ  1��������ʾ  
    TFTSPI_CLS(u16BLUE);           //����
	TFTSPI_P8X16Str(0,0,"LQ VL53 Test",u16RED,u16BLUE);
#endif
	char txt[16];
	
#if (VL53_USE_SELECT == USE_HAL_IIC)
    IIC_InitConfig(I2C1, 400000);
#elif (VL53_USE_SELECT == USE_SOFT_IIC) 
    IIC_Init(); 
#endif    
    
    PIN_Write(VL53_CS_PIN, 0U);   //ʧ��A3���ӵ�VL53 
    delayms(100);
    /* �޸�IIC��ַ�󣬽�ʹ�ܵ�VL53��ַ��Ϊ 0x30 */
    VL53_Write_Byte(VL53ADDR, VL53L0X_REG_I2C_SLAVE_DEVICE_ADDRESS, VL53NEWADDR);
    
    PIN_Write(VL53_CS_PIN, 1U);   //ʹ��A3���ӵ�VL53 
    delayms(100);
    
    uint8_t VL53_STAR = 0x01;
    uint8_t dis_buff[2];
    uint16_t dis1, dis2;
    while(1)
    {
        
        
        /* ��ȡ�������� */
		VL53_Read_nByte(VL53NEWADDR, VL53_REG_DIS, 2, dis_buff);
        
        /* ��ʼһ�β�� */
        VL53_Write_Byte(VL53NEWADDR, VL53L0X_REG_SYSRANGE_START,  VL53_STAR);
        
        /* ת������ */
        dis1 = (dis_buff[0]<<8) | (dis_buff[1]);
        if(dis1 > 8000)
        {
            dis1 = 0;
        }
        
        /* ��ȡ�������� */
		VL53_Read_nByte(VL53ADDR, VL53_REG_DIS, 2, dis_buff);
        
        /* ��ʼһ�β�� */
        VL53_Write_Byte(VL53ADDR, VL53L0X_REG_SYSRANGE_START, VL53_STAR);
        
        /* ת������ */
        dis2 = (dis_buff[0]<<8) | (dis_buff[1]);
        if(dis1 > 8000)
        {
            dis2 = 0;
        }
        
		sprintf(txt, "DIS %5d mm",dis1);
#ifdef OLED
		LCD_P8x16Str(0,3,txt);
#else
		TFTSPI_P8X16Str(2,5,txt,u16RED,u16BLUE);
#endif
        sprintf(txt, "DIS %5d mm",dis2);
#ifdef OLED
		LCD_P8x16Str(0,5,txt);
#else
		TFTSPI_P8X16Str(2,7,txt,u16RED,u16BLUE);
#endif
        
		delayms(50);
		LED_ColorReverse(blue);
    
    }
    
}


#if (VL53_USE_SELECT == USE_HAL_IIC)

/**
  * @brief    VL53 д1���Ĵ���
  *
  * @param    dev��    ��ַ
  * @param    reg��    �Ĵ���
  * @param    data��   д������
  *
  * @return   
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Write_Byte(uint8_t dev, uint8_t reg, uint8_t data)
{
    IIC_WriteReg(I2C1, dev, reg, data);    
}

/**
  * @brief    VL53 ��n���Ĵ���
  *
  * @param    dev��    ��ַ
  * @param    reg��    �Ĵ���
  * @param    length;  ����
  * @param    data��   ָ���Ŷ�����
  *
  * @return   
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Read_nByte(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data)
{
    IIC_ReadReg(I2C1, dev, reg, data, length);   
}


#else

/**
  * @brief    VL53 д1���Ĵ���
  *
  * @param    dev��    ��ַ
  * @param    reg��    �Ĵ���
  * @param    data��   д������
  *
  * @return   
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Write_Byte(uint8_t dev, uint8_t reg, uint8_t data)
{
    IIC_WriteByteToSlave(dev<<1, reg, data);  
}

/**
  * @brief    VL53 ��n���Ĵ���
  *
  * @param    dev��    ��ַ
  * @param    reg��    �Ĵ���
  * @param    length;  ����
  * @param    data��   ָ���Ŷ�����
  *
  * @return   
  *
  * @note     
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Read_nByte(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data)
{
    IIC_ReadMultByteFromSlave(dev<<1, reg, length, data);    
}

#endif 
