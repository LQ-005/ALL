/*!
  * @file     LQ_EEPROM.c
  *
  * @brief    eeprom驱动
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "LQ_EEPROM.h"
#include "fsl_eeprom.h"


/**
  * @brief    初始化eeprom
  *
  * @param    无
  *
  * @return   无
  *
  * @note     LPC54606 eeprom 一共16Kb 分为128页  每页可存放 32个字
  *
  * @see      EEPROM_InitConfig();  
  *
  * @date     2019/5/9 星期四
  */
void EEPROM_InitConfig(void)
{
    eeprom_config_t config;

    EEPROM_GetDefaultConfig(&config);
    
    EEPROM_Init(EEPROM, &config, CLOCK_GetFreq(kCLOCK_BusClk));    
}

/*!
  * @brief    eeprom 写一个字
  *
  * @param    offset  ：偏移地址 0 - 4095
  * @param    data    ：要写入的数据
  *
  * @return   无
  *
  * @note     使用前需要初始化EEPROM
  *
  * @see      EEPROM_WriteData(0, 1234);  //将1234数组写入EEPROM 偏移地址0的地方
  *
  * @date     2019/10/29 星期二
  */
void EEPROM_WriteData(uint32_t offset, uint32_t data)
{
    EEPROM_WriteWord(EEPROM,  (offset * 4), data);
}

/*!
  * @brief    eeprom 写数据
  *
  * @param    offset  ：偏移地址 0 - 4095
  * @param    Buf     ：要写入的数据地址
  * @param    len     ：要写入的数据的长度  一般用sizeof计算
  *
  * @return   无
  *
  * @note     使用前需要初始化EEPROM
  *
  * @see      float data[8];
  * @see      EEPROM_WriteBuff(0, data, sizeof(data));  //将data数组写入EEPROM
  *
  * @date     2019/10/29 星期二
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
  * @brief    读取eeprom的数据
  *
  * @param    offset  ：偏移地址 0 - 4095
  * @param    Buf     ：存放读取数据
  * @param    len     ：读取数据的长度
  *
  * @return   无
  *
  * @note     无
  *
  * @see      float data[8];
  * @see      EEPROM_ReadBuff(0, (uint8_t *)data, sizeof(data));  //从EEPROM 读取数据到data中   
  *
  * @date     2019/10/29 星期二
  */
void EEPROM_ReadBuff(uint32_t offset, uint8_t *Buf, uint32_t len)
{
    uint8_t *addr = ((uint8_t *)((uint32_t)(FSL_FEATURE_EEPROM_BASE_ADDRESS + (offset)*4))) ;
    while(len--)
    {
        *(Buf++) = *(addr++); 
    }
}


