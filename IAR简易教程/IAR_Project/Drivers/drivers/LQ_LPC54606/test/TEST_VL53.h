/*!
  * @file     TEST_VL53.h
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
#ifndef __VL53L0X_H__
#define __VL53L0X_H__
#include "stdint.h"

#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14
#define VL53_REG_DIS                                0x1E
#define VL53L0X_REG_I2C_SLAVE_DEVICE_ADDRESS        0x8a
#define VL53ADDR                                    0x29    //0x52   Ĭ�ϵ�ַ
#define VL53NEWADDR                                 0x30   

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
void Test_Vl53(void);

/**
  * @brief    ����VL53
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����һ·IIC������VL53  VL53ģ���IIC��ַ�����ó����޸ģ������ϵ��ʱ��
  *           Ĭ��IIC��ַ����0x29    �����޸ĵ�ַ��ʱ����ʧ��һ��ģ�飬�޸�ʹ��ģ���
  *           IIC��ַ���޸��������ģ��ĵ�ַ��ͬ�ˣ��Ϳ��԰���ͬ��ַ�����ˡ�
  *
  * @example  
  *
  * @date     2019/4/17 ������
  */
void Test_Vl53_TWO(void);

/**
  * @brief    VL53 д1���Ĵ���
  *
  * @param    dev��    ��ַ
  * @param    reg��    �Ĵ���
  * @param    data��   д������
  *
  * @return   
  *
  * @note      ��ֲʱ��Ҫ�޸�����
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Write_Byte(uint8_t dev, uint8_t reg, uint8_t data);



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
  * @note     ��ֲʱ��Ҫ�޸�����
  *
  * @see  
  *
  * @date     2019/4/29 ����һ
  */
void VL53_Read_nByte(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);

#endif
