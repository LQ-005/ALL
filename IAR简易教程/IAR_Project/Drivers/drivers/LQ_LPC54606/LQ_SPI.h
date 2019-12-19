/*!
  * @file     LQ_SPI.h
  *
  * @brief    SPI驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1   2019/11/27  修改了SPI时钟源 12M->48M  优化了SPI片选管脚可以使用任意IO
                     2019/12/11  优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
  */ 
#ifndef __LQ_SPI_H
#define __LQ_SPI_H
#include "fsl_spi.h"
#include "LQ_GPIO.h"

//这里实际是将flexcom口用作SPI，如果使用了flexcom0当作SPI0，那么flexcom0 就不可用作串口0，IIC0了
/**********************************  SPI(flexcom引脚复用为SPI) ***************************************/
//        模块编号           端口          可选范围完整  
#define SPI0_SCK_PIN        P0_28      /*!<可选范围完整 P0_28  P1_4         */
#define SPI0_MOSI_PIN       P0_24      /*!<可选范围完整 P0_24  P0_29  P1_5  */
#define SPI0_MISO_PIN       P0_25      /*!<可选范围完整 P0_25  P0_30  P1_6  */
#define SPI0_CS0_PIN        P0_31      /*!<可选范围完整 任意IO */
                                       
#define SPI1_SCK_PIN        P0_7       /*!<可选范围完整 P0_7   P1_9  */
#define SPI1_MOSI_PIN       P1_10      /*!<可选范围完整 P1_10        */
#define SPI1_MISO_PIN       P0_10      /*!<可选范围完整 P0_10  P1_11 */
#define SPI1_CS0_PIN        P0_13      /*!<可选范围完整 任意IO       */
                                       
#define SPI2_SCK_PIN        P1_23      /*!<可选范围完整 P1_23        */
#define SPI2_MOSI_PIN       P0_26      /*!<可选范围完整 P0_26  P1_24 */
#define SPI2_MISO_PIN       P0_27      /*!<可选范围完整 P0_27  P1_25 */
#define SPI2_CS0_PIN        P1_26      /*!<可选范围完整 任意IO       */
                                           
#define SPI3_SCK_PIN        P0_6       /*!<可选范围完整 P0_0  P0_6   */
#define SPI3_MOSI_PIN       P0_3       /*!<可选范围完整 P0_3  P1_1   */
#define SPI3_MISO_PIN       P0_2       /*!<可选范围完整 P0_2  P0_12  */
#define SPI3_CS0_PIN        P0_20      /*!<可选范围完整 任意IO       */
                                       
#define SPI4_SCK_PIN        P0_4       /*!<可选范围完整 P0_4   P1_19 */
#define SPI4_MOSI_PIN       P0_5       /*!<可选范围完整 P0_5   P1_21 */
#define SPI4_MISO_PIN       P0_16      /*!<可选范围完整 P0_16  P1_20 */
#define SPI4_CS0_PIN        P0_18      /*!<可选范围完整 任意IO       */
                                           
#define SPI5_SCK_PIN        P0_7       /*!<可选范围完整 P0_7         */
#define SPI5_MOSI_PIN       P0_8       /*!<可选范围完整 P0_8         */
#define SPI5_MISO_PIN       P0_9       /*!<可选范围完整 P0_9         */
#define SPI5_CS0_PIN        P1_14      /*!<可选范围完整 任意IO       */
                                       
#define SPI6_SCK_PIN        P0_10      /*!<可选范围完整 P0_10  P1_12 */
#define SPI6_MOSI_PIN       P0_11      /*!<可选范围完整 P0_11  P1_13 */
#define SPI6_MISO_PIN       P0_22      /*!<可选范围完整 P0_22  P1_16 */
#define SPI6_CS0_PIN        P0_15      /*!<可选范围完整 任意IO       */
                                           
#define SPI7_SCK_PIN        P0_21      /*!<可选范围完整 P0_21  P1_28 */
#define SPI7_MOSI_PIN       P0_20      /*!<可选范围完整 P0_20  P1_29 */
#define SPI7_MISO_PIN       P0_19      /*!<可选范围完整 P0_19  P1_30 */
#define SPI7_CS0_PIN        P1_21      /*!<可选范围完整 任意IO       */

#define SPI8_SCK_PIN        P1_19      /*!<可选范围完整 P1_19        */
#define SPI8_MOSI_PIN       P1_17      /*!<可选范围完整 P1_17        */
#define SPI8_MISO_PIN       P1_18      /*!<可选范围完整 P1_18        */
#define SPI8_CS0_PIN        P1_31      /*!<可选范围完整 任意IO       */


/**
  * @brief    SPI 主机模式初始化
  *
  * @param    base      ：  SPI0 - SPI8
  * @param      mode            0: CLK空闲时刻为低电平 在第一个CLK跳边沿 捕获数据
  * @param      mode            1: CLK空闲时刻为低电平 在第二个CLK跳边沿 捕获数据
  * @param      mode            2: CLK空闲时刻为高电平 在第一个CLK跳边沿 捕获数据
  * @param      mode            3: CLK空闲时刻为高电平 在第二个CLK跳边沿 捕获数据
  * @param    baudrate  ：  SPI 波特率    
  *
  * @return   注意 SPI波特率不要超过8M 
  *
  * @note     这里实际是将flexcom口用作SPI，如果使用了flexcom0当作SPI0，那么flexcom0 就不可用作串口0，IIC0了
  *
  * @see      SPI_MasterInitConfig(SPI3, 3, 4000000U); //初始化SPI3 使用片选CS0 4M速率
  *
  * @date     2019/6/3 星期一
  */
void SPI_MasterInitConfig(SPI_Type * base, uint8_t mode, uint32_t baudrate);


/**
  * @brief    SPI读写N个字节
  *
  * @param    base    ：  SPI0 - SPI8
  * @param    txData  ：  写入的buff
  * @param    rxData  ：  读出的buff
  * @param    len     ：  长度
  *
  * @return   无
  *
  * @note     无
  *
  * @see      uint8_t buff[2];
  * @see      SPI_ReadWriteNByte(SPI3, buff, buff, 2); //使用SPI3 读写两个字节 
  *
  * @date     2019/6/3 星期一
  */
uint8_t SPI_ReadWriteNByte(SPI_Type * base, uint8_t *txData, uint8_t *rxData, uint32_t len);



/*!
  * @brief    设置片选信号
  *
  * @param    base    ：  SPI0 - SPI8 
  * @param    output  ：  片选输出电平  0：低电压    其他高电平
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SPI_SetCS(SPI0, 0); //令SPI0的片选为低电平
  *
  * @date     2019/11/27 星期三
  */
void SPI_SetCS(SPI_Type * base, uint8_t output);




/*!
  * @brief    SPI管脚初始化
  *
  * @param    base      ：  SPI0 - SPI8   
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SPI_PinInit(SPI0, 1); //初始化SPI0管脚 片选使用 SPI0_CS1_PIN
  *
  * @date     2019/10/29 星期二
  */
void SPI_PinInit(SPI_Type * base);



#endif
