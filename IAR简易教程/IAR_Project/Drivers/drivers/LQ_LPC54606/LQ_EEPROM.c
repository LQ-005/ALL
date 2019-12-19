/*!
  * @file     LQ_EEPROM.c
  *
  * @brief    eeprom����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "LQ_EEPROM.h"
#include "fsl_eeprom.h"


/**
  * @brief    ��ʼ��eeprom
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     LPC54606 eeprom һ��16Kb ��Ϊ128ҳ  ÿҳ�ɴ�� 32����
  *
  * @see      EEPROM_InitConfig();  
  *
  * @date     2019/5/9 ������
  */
void EEPROM_InitConfig(void)
{
    eeprom_config_t config;

    EEPROM_GetDefaultConfig(&config);
    
    EEPROM_Init(EEPROM, &config, CLOCK_GetFreq(kCLOCK_BusClk));    
}

/*!
  * @brief    eeprom дһ����
  *
  * @param    offset  ��ƫ�Ƶ�ַ 0 - 4095
  * @param    data    ��Ҫд�������
  *
  * @return   ��
  *
  * @note     ʹ��ǰ��Ҫ��ʼ��EEPROM
  *
  * @see      EEPROM_WriteData(0, 1234);  //��1234����д��EEPROM ƫ�Ƶ�ַ0�ĵط�
  *
  * @date     2019/10/29 ���ڶ�
  */
void EEPROM_WriteData(uint32_t offset, uint32_t data)
{
    EEPROM_WriteWord(EEPROM,  (offset * 4), data);
}

/*!
  * @brief    eeprom д����
  *
  * @param    offset  ��ƫ�Ƶ�ַ 0 - 4095
  * @param    Buf     ��Ҫд������ݵ�ַ
  * @param    len     ��Ҫд������ݵĳ���  һ����sizeof����
  *
  * @return   ��
  *
  * @note     ʹ��ǰ��Ҫ��ʼ��EEPROM
  *
  * @see      float data[8];
  * @see      EEPROM_WriteBuff(0, data, sizeof(data));  //��data����д��EEPROM
  *
  * @date     2019/10/29 ���ڶ�
  */
void EEPROM_WriteBuff(uint32_t offset, void *Buf, uint32_t len)
{
    uint32_t *Buff = Buf; 
    int temp = (len+3)/4;
    while(temp --)
    {
        EEPROM_WriteData(offset++, *(Buff++));
    }
}


/*!
  * @brief    ��ȡeeprom������
  *
  * @param    offset  ��ƫ�Ƶ�ַ 0 - 4095
  * @param    Buf     ����Ŷ�ȡ����
  * @param    len     ����ȡ���ݵĳ���
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      float data[8];
  * @see      EEPROM_ReadBuff(0, (uint8_t *)data, sizeof(data));  //��EEPROM ��ȡ���ݵ�data��   
  *
  * @date     2019/10/29 ���ڶ�
  */
void EEPROM_ReadBuff(uint32_t offset, uint8_t *Buf, uint32_t len)
{
    uint8_t *addr = ((uint8_t *)((uint32_t)(FSL_FEATURE_EEPROM_BASE_ADDRESS + (offset)*4))) ;
    while(len--)
    {
        *(Buf++) = *(addr++); 
    }
}


