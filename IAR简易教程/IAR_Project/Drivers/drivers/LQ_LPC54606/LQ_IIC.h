/*!
  * @file     LQ_IIC.h
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
#ifndef __LQ_IIC_H
#define __LQ_IIC_H
#include "fsl_i2c.h"
#include "LQ_GPIO.h"

//这里实际是将flexcom口用作IIC，如果使用了flexcom0当作IIC0，那么flexcom0 就不可用作串口0，SPI0了
/**********************************  IIC(flexcom引脚复用为IIC) ***************************************/
//        模块编号           端口          可选范围完整   
#define IIC0_SCL_PIN        P0_25        /*!< 可选范围 P0_25  P0_30  P1_0  P1_6  P1_7 */
#define IIC0_SDA_PIN        P0_24        /*!< 可选范围 P0_24  P0_29  P0_31 P1_5  P1_8 */
                                         
#define IIC1_SCL_PIN        P0_14        /*!< 可选范围 P0_10  P0_14  P1_11             */
#define IIC1_SDA_PIN        P0_13        /*!< 可选范围 P0_13  P1_10                    */
                                         
#define IIC2_SCL_PIN        P0_27        /*!< 可选范围 P0_27  P1_25  P1_27             */
#define IIC2_SDA_PIN        P0_26        /*!< 可选范围 P0_26  P1_24  P1_26             */
                                         
#define IIC3_SCL_PIN        P0_2         /*!< 可选范围 P0_2   P0_7   P0_12  P0_21      */
#define IIC3_SDA_PIN        P0_3         /*!< 可选范围 P0_1   P0_3   P0_20  P1_1       */
                                         
#define IIC4_SCL_PIN        P0_16        /*!< 可选范围 P0_16  P0_19  P1_15  P1_20      */
#define IIC4_SDA_PIN        P0_5         /*!< 可选范围 P0_5   P0_18  P1_9   P1_21      */
                                         
#define IIC5_SCL_PIN        P0_9         /*!< 可选范围 P0_9   P1_15                    */
#define IIC5_SDA_PIN        P0_8         /*!< 可选范围 P0_8   P1_14                    */
                                         
#define IIC6_SCL_PIN        P0_22        /*!< 可选范围 P0_22  P1_16                    */
#define IIC6_SDA_PIN        P0_11        /*!< 可选范围 P0_11  P0_15  P1_13             */
                                         
#define IIC7_SCL_PIN        P0_19        /*!< 可选范围 P0_19  P1_20  P1_30             */
#define IIC7_SDA_PIN        P0_20        /*!< 可选范围 P0_20  P1_21  P1_29             */

#define IIC8_SCL_PIN        P1_18        /*!< 可选范围 P1_18  P1_22                    */
#define IIC8_SDA_PIN        P1_17        /*!< 可选范围 P1_17  P1_31                    */


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
void IIC_InitConfig(I2C_Type *base, uint32_t baudrate);


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
status_t IIC_ReadReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t *val, uint8_t len);


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
status_t IIC_WriteReg(I2C_Type *base, uint16_t addr, uint8_t reg, uint8_t val) ;




/*!
  * @brief    IIC管脚复用功能初始化
  *
  * @param    base  ：  IIC端口号  I2C0 - I2C8
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      IIC_PinInit(I2C0); //初始化 IIC0管脚  I2C管脚在LQ_IIC.h中通过宏定义选择
  *
  * @date     2019/10/23 星期三
  */
void IIC_PinInit(I2C_Type *base);


#endif
