/*!
  * @file     LQ_IIC.c
  *
  * @brief    IIC驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/11 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#include "LQ_GPIO.h"
#include "LQ_IIC.h"
#include "fsl_i2c.h"
#include "fsl_clock.h"

/*!
  * @brief    IIC初始化
  *
  * @param    base      ：  IIC端口号  I2C0 - I2C8
  * @param    baudrate  ：  波特率 
  *
  * @return   无
  *
  * @note     这里实际是将flexcom口用作IIC，如果使用了flexcom0当作IIC0，那么flexcom0 就不可用作串口0，SPI0了
  *
  * @see      IIC_InitConfig(I2C3, 400000);  //初始化IIC3  波特率400K  管脚在LQ_IIC.h中通过宏定义选择
  *
  * @date     2019/10/23 星期三
  */
void IIC_InitConfig(I2C_Type *base, uint32_t baudrate)
{
    /* IIC 管脚初始化 */
    IIC_PinInit(base);
    
    /* 获取要初始化的SPI */
    uint8_t temp = I2C_GetInstance(base);
    
    /* 开启串口时钟 */
    CLOCK_AttachClk((clock_attach_id_t)(kFRO12M_to_FLEXCOMM0 + temp));
    
    i2c_master_config_t masterConfig;
    
    /* IIC 主机模式*/
    masterConfig.enableMaster = true;
    
    /* 设置波特率 */
    masterConfig.baudRate_Bps = baudrate;
    
    /* 启用内部超时 */
    masterConfig.enableTimeout= true;
    
    /* 初始化IIC 默认使用12M时钟 */
    I2C_MasterInit(base, &masterConfig, CLOCK_GetFreq((clock_name_t)(kCLOCK_Flexcomm0 + temp)));
}
    

/**  传输结构体 内部使用 */
i2c_master_transfer_t master_transfer; //   
    
    
    
/**
  * @brief    IIC 读n个寄存器
  *
  * @param    base    ：  IIC端口号  I2C0 - I2C8
  * @param    addr    ：  器件地址（高7位） 
  * @param    reg     ：  要读的寄存器 
  * @param    val     ：  存放读出数据的地址 
  * @param    len     ：  读取长度  
  *
  * @return   读取是否成功
  *
  * @note     无
  *
  * @see      uint8_t buf;
  * @see      IIC_ReadReg(I2C3, 0x68, 0X75, &buf, 1);  //使用IIC3读取器件地址（高7位）为0x68的MPU6050  的0x75寄存器
  *
  * @date     2019/6/12 星期三
  */
status_t IIC_ReadReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t *val, uint8_t len)  
{
    
    status_t status = kStatus_Success;
    
    /* 配置IIC传输结构体 */
    master_transfer.slaveAddress = addr;
    master_transfer.subaddress = (uint32_t)reg;              //寄存器地址
    master_transfer.subaddressSize = 1U;                     //按8位读
    master_transfer.data = val;                              //存放读出的数据
    master_transfer.dataSize = len;                          //要读多少个数据
    master_transfer.direction = kI2C_Read;                   //I2C读模式
    master_transfer.flags = kI2C_TransferDefaultFlag;

    if(I2C_MasterTransferBlocking(base, &master_transfer) == kStatus_Fail)
    {
        return kStatus_Fail;
    }
    return status;
}


/**
  * @brief    IIC 写一个寄存器
  *
  * @param    base    ：  IIC端口号  I2C0 - I2C8 
  * @param    addr    ：  器件地址（高7位） 
  * @param    reg     ：  要写的寄存器 
  * @param    val     ：  要写入的值  
  *
  * @return   读取是否成功
  *
  * @note     无
  *
  * @see      IIC_WriteReg(I2C3, 0x68, 0X75, 0x10);  //使用IIC3向器件地址（高7位）为0x68的MPU6050  的0x75寄存器 写入0x10
  *
  * @date     2019/6/12 星期三
  */
status_t IIC_WriteReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t val)    
{   
    status_t status = kStatus_Success;
    
    uint8_t buff[1];

    buff[0] = val;
    /* 配置IIC传输结构体 */
    master_transfer.slaveAddress = addr;
    master_transfer.subaddress = (uint32_t)reg;              //寄存器地址
    master_transfer.subaddressSize = 1U;                     //按8位读
    master_transfer.data = buff;                             //要写入的数据
    master_transfer.dataSize = 1;                            //要写多少个数据
    master_transfer.direction = kI2C_Write;                  //I2C写模式
    master_transfer.flags = kI2C_TransferDefaultFlag;

    if(I2C_MasterTransferBlocking(base, &master_transfer) == kStatus_Fail)
    {
        return kStatus_Fail;
    }
    return status;
}



/*!
  * @brief    IIC管脚复用功能初始化
  *
  * @param    base  ：  IIC端口号  I2C0 - I2C8
  *
  * @return   使用管脚在LQ_IIC.h中通过宏定义选择
  *
  * @note     内部调用
  *
  * @see      IIC_PinInit(I2C0); //初始化 IIC0管脚  I2C管脚在LQ_IIC.h中通过宏定义选择
  *
  * @date     2019/10/23 星期三
  */
void IIC_PinInit(I2C_Type *base)
{
    switch((uint32_t)base)
    {
        case (uint32_t)I2C0:
        {
            if     (P0_25 == IIC0_SCL_PIN)    PIN_MuxSet(P0_25, FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_30 == IIC0_SCL_PIN)    PIN_MuxSet(P0_30,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_0 == IIC0_SCL_PIN)     PIN_MuxSet(P1_0, FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_6  == IIC0_SCL_PIN)    PIN_MuxSet(P1_6 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_7  == IIC0_SCL_PIN)    PIN_MuxSet(P1_7 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                  
                                                                                                   
            if     (P0_24 == IIC0_SDA_PIN)    PIN_MuxSet(P0_24,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_29 == IIC0_SDA_PIN)    PIN_MuxSet(P0_29,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_31  == IIC0_SDA_PIN)    PIN_MuxSet(P0_31 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_5  == IIC0_SDA_PIN)    PIN_MuxSet(P1_5 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_8  == IIC0_SDA_PIN)    PIN_MuxSet(P1_8 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C1:
        {
            if     (P0_13 == IIC1_SDA_PIN)    PIN_MuxSet(P0_13,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_IIC);
            else if(P1_10 == IIC1_SDA_PIN)    PIN_MuxSet(P1_10,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
            if     (P0_10 == IIC1_SCL_PIN)    PIN_MuxSet(P0_10,FUNC4 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_14 == IIC1_SCL_PIN)    PIN_MuxSet(P0_14,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_IIC);
            else if(P1_11 == IIC1_SCL_PIN)    PIN_MuxSet(P1_11,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C2:
        {
            if     (P0_26 == IIC2_SDA_PIN)    PIN_MuxSet(P0_26,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_24 == IIC2_SDA_PIN)    PIN_MuxSet(P1_24,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_26 == IIC2_SDA_PIN)    PIN_MuxSet(P1_26,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                
                                                                                                   
            if     (P0_27 == IIC2_SCL_PIN)    PIN_MuxSet(P0_27,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_25 == IIC2_SCL_PIN)    PIN_MuxSet(P1_25,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_27 == IIC2_SCL_PIN)    PIN_MuxSet(P1_27,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C3:
        {
            if     (P0_1  == IIC3_SDA_PIN)    PIN_MuxSet(P0_1 ,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_3  == IIC3_SDA_PIN)    PIN_MuxSet(P0_3 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_20 == IIC3_SDA_PIN)    PIN_MuxSet(P0_20,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_1  == IIC3_SDA_PIN)    PIN_MuxSet(P1_1 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                 
                                                                                                   
            if     (P0_2  == IIC3_SCL_PIN)    PIN_MuxSet(P0_2 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_7  == IIC3_SCL_PIN)    PIN_MuxSet(P0_7 ,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_12 == IIC3_SCL_PIN)    PIN_MuxSet(P0_12,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_21 == IIC3_SCL_PIN)    PIN_MuxSet(P0_21,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C4:
        {
            if     (P0_5  == IIC4_SDA_PIN)    PIN_MuxSet(P0_5 ,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_18 == IIC4_SDA_PIN)    PIN_MuxSet(P0_18,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_9  == IIC4_SDA_PIN)    PIN_MuxSet(P1_9 ,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_21 == IIC4_SDA_PIN)    PIN_MuxSet(P1_21,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                  
                                                                                                   
            if     (P0_16 == IIC4_SCL_PIN)    PIN_MuxSet(P0_16,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_19 == IIC4_SCL_PIN)    PIN_MuxSet(P0_19,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_15 == IIC4_SCL_PIN)    PIN_MuxSet(P1_15,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_20 == IIC4_SCL_PIN)    PIN_MuxSet(P1_20,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C5:
        {
            if     (P0_8  == IIC5_SDA_PIN)    PIN_MuxSet(P0_8 ,FUNC3 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_14 == IIC5_SDA_PIN)    PIN_MuxSet(P1_14,FUNC4 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                  
                                                                                                   
            if     (P0_9  == IIC5_SCL_PIN)    PIN_MuxSet(P0_9 ,FUNC3 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_15 == IIC5_SCL_PIN)    PIN_MuxSet(P1_15,FUNC4 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C6:
        {
            if     (P0_11 == IIC6_SDA_PIN)    PIN_MuxSet(P0_11,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P0_15 == IIC6_SDA_PIN)    PIN_MuxSet(P0_15,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_13 == IIC6_SDA_PIN)    PIN_MuxSet(P1_13,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                 
                                                                                                   
            if     (P0_22 == IIC6_SCL_PIN)    PIN_MuxSet(P0_22,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_16 == IIC6_SCL_PIN)    PIN_MuxSet(P1_16,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C7:
        {
            if     (P0_20 == IIC7_SDA_PIN)    PIN_MuxSet(P0_20,FUNC7 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_21 == IIC7_SDA_PIN)    PIN_MuxSet(P1_21,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_29 == IIC7_SDA_PIN)    PIN_MuxSet(P1_29,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                 
                                                                                                   
            if     (P0_19 == IIC7_SCL_PIN)    PIN_MuxSet(P0_19,FUNC7 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_20 == IIC7_SCL_PIN)    PIN_MuxSet(P1_20,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_30 == IIC7_SCL_PIN)    PIN_MuxSet(P1_30,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
        
        case (uint32_t)I2C8:
        {
            if     (P1_17 == IIC8_SDA_PIN)    PIN_MuxSet(P1_17,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_31 == IIC8_SDA_PIN)    PIN_MuxSet(P1_31,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);                  
                                                                                                   
            if     (P1_18 == IIC8_SCL_PIN)    PIN_MuxSet(P1_18,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            else if(P1_22 == IIC8_SCL_PIN)    PIN_MuxSet(P1_22,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up | OD_Enable);
            
        }break;
    }
}
