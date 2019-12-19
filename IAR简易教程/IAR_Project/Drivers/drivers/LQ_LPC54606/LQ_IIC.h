/*!
  * @file     LQ_IIC.h
  *
  * @brief    IIC�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_IIC_H
#define __LQ_IIC_H
#include "fsl_i2c.h"
#include "LQ_GPIO.h"

//����ʵ���ǽ�flexcom������IIC�����ʹ����flexcom0����IIC0����ôflexcom0 �Ͳ�����������0��SPI0��
/**********************************  IIC(flexcom���Ÿ���ΪIIC) ***************************************/
//        ģ����           �˿�          ��ѡ��Χ����   
#define IIC0_SCL_PIN        P0_25        /*!< ��ѡ��Χ P0_25  P0_30  P1_0  P1_6  P1_7 */
#define IIC0_SDA_PIN        P0_24        /*!< ��ѡ��Χ P0_24  P0_29  P0_31 P1_5  P1_8 */
                                         
#define IIC1_SCL_PIN        P0_14        /*!< ��ѡ��Χ P0_10  P0_14  P1_11             */
#define IIC1_SDA_PIN        P0_13        /*!< ��ѡ��Χ P0_13  P1_10                    */
                                         
#define IIC2_SCL_PIN        P0_27        /*!< ��ѡ��Χ P0_27  P1_25  P1_27             */
#define IIC2_SDA_PIN        P0_26        /*!< ��ѡ��Χ P0_26  P1_24  P1_26             */
                                         
#define IIC3_SCL_PIN        P0_2         /*!< ��ѡ��Χ P0_2   P0_7   P0_12  P0_21      */
#define IIC3_SDA_PIN        P0_3         /*!< ��ѡ��Χ P0_1   P0_3   P0_20  P1_1       */
                                         
#define IIC4_SCL_PIN        P0_16        /*!< ��ѡ��Χ P0_16  P0_19  P1_15  P1_20      */
#define IIC4_SDA_PIN        P0_5         /*!< ��ѡ��Χ P0_5   P0_18  P1_9   P1_21      */
                                         
#define IIC5_SCL_PIN        P0_9         /*!< ��ѡ��Χ P0_9   P1_15                    */
#define IIC5_SDA_PIN        P0_8         /*!< ��ѡ��Χ P0_8   P1_14                    */
                                         
#define IIC6_SCL_PIN        P0_22        /*!< ��ѡ��Χ P0_22  P1_16                    */
#define IIC6_SDA_PIN        P0_11        /*!< ��ѡ��Χ P0_11  P0_15  P1_13             */
                                         
#define IIC7_SCL_PIN        P0_19        /*!< ��ѡ��Χ P0_19  P1_20  P1_30             */
#define IIC7_SDA_PIN        P0_20        /*!< ��ѡ��Χ P0_20  P1_21  P1_29             */

#define IIC8_SCL_PIN        P1_18        /*!< ��ѡ��Χ P1_18  P1_22                    */
#define IIC8_SDA_PIN        P1_17        /*!< ��ѡ��Χ P1_17  P1_31                    */


/*!
  * @brief    IIC��ʼ��
  *
  * @param    base      ��  IIC�˿ں�  I2C0 - I2C8
  * @param    baudrate  ��  ������ 
  *
  * @return   ��
  *
  * @note     ����ʵ���ǽ�flexcom������IIC�����ʹ����flexcom0����IIC0����ôflexcom0 �Ͳ�����������0��SPI0��
  *
  * @see      IIC_InitConfig(I2C3, 400000);  //��ʼ��IIC3  ������400K  �ܽ���LQ_IIC.h��ͨ���궨��ѡ��
  *
  * @date     2019/10/23 ������
  */
void IIC_InitConfig(I2C_Type *base, uint32_t baudrate);


/**
  * @brief    IIC ��n���Ĵ���
  *
  * @param    base    ��  IIC�˿ں�  I2C0 - I2C8
  * @param    addr    ��  ������ַ����7λ�� 
  * @param    reg     ��  Ҫ���ļĴ��� 
  * @param    val     ��  ��Ŷ������ݵĵ�ַ 
  * @param    len     ��  ��ȡ����  
  *
  * @return   ��ȡ�Ƿ�ɹ�
  *
  * @note     ��
  *
  * @see      uint8_t buf;
  * @see      IIC_ReadReg(I2C3, 0x68, 0X75, &buf, 1);  //ʹ��IIC3��ȡ������ַ����7λ��Ϊ0x68��MPU6050  ��0x75�Ĵ���
  *
  * @date     2019/6/12 ������
  */
status_t IIC_ReadReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t *val, uint8_t len);


/**
  * @brief    IIC дһ���Ĵ���
  *
  * @param    base    ��  IIC�˿ں�  I2C0 - I2C8 
  * @param    addr    ��  ������ַ����7λ�� 
  * @param    reg     ��  Ҫд�ļĴ��� 
  * @param    val     ��  Ҫд���ֵ  
  *
  * @return   ��ȡ�Ƿ�ɹ�
  *
  * @note     ��
  *
  * @see      IIC_WriteReg(I2C3, 0x68, 0X75, 0x10);  //ʹ��IIC3��������ַ����7λ��Ϊ0x68��MPU6050  ��0x75�Ĵ��� д��0x10
  *
  * @date     2019/6/12 ������
  */
status_t IIC_WriteReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t val) ;




/*!
  * @brief    IIC�ܽŸ��ù��ܳ�ʼ��
  *
  * @param    base  ��  IIC�˿ں�  I2C0 - I2C8
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      IIC_PinInit(I2C0); //��ʼ�� IIC0�ܽ�  I2C�ܽ���LQ_IIC.h��ͨ���궨��ѡ��
  *
  * @date     2019/10/23 ������
  */
void IIC_PinInit(I2C_Type *base);


#endif
