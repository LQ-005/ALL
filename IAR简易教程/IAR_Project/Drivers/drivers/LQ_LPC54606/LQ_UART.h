/*!
  * @file     LQ_UART.h
  *
  * @brief    UART驱动文件
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
#ifndef __LQ_UART_H
#define __LQ_UART_H

#include "LQ_GPIO.h"
#include "fsl_usart.h"

//这里实际是将flexcom口用作串口，如果使用了flexcom0当作串口0，那么flexcom0 就不可用作IIC0，SPI0了
/**********************************  UART(flexcom引脚复用为串口) ***************************************/
//      模块通道    端口        可选范围完整20171023                          
#define UART0_RX    P0_29       /*!< 可选范围完整 P0_29  P0_24   P1_5  */
#define UART0_TX    P0_30       /*!< 可选范围完整 P0_30  P0_25   P1_6  */
                                
#define UART1_RX    P1_10       /*!< 可选范围完整 P1_10       */
#define UART1_TX    P1_11       /*!< 可选范围完整 P1_11 P0_10 */
                                
#define UART2_RX    P0_26       /*!< 可选范围完整 P0_26 P1_24 */
#define UART2_TX    P0_27       /*!< 可选范围完整 P0_27 P1_25 */
                                
#define UART3_RX    P0_3        /*!< 可选范围完整 P0_3  P1_1   */
#define UART3_TX    P0_2        /*!< 可选范围完整 P0_2  P0_12  */
                                
#define UART4_RX    P1_21       /*!< 可选范围完整 P0_5  P1_21 */
#define UART4_TX    P1_20       /*!< 可选范围完整 P0_16 P1_20 */
                                
#define UART5_RX    P0_8        /*!< 可选范围完整 P0_8   */
#define UART5_TX    P0_9        /*!< 可选范围完整 P0_9   */
                                
#define UART6_RX    P1_13       /*!< 可选范围完整 P0_11 P1_13    */ 
#define UART6_TX    P0_22       /*!< 可选范围完整 P0_22 P1_16    */
                                
#define UART7_RX    P1_29       /*!< 可选范围完整 P0_20 P1_29    */
#define UART7_TX    P1_30       /*!< 可选范围完整 P0_19 P1_30    */

#define UART8_RX    P1_17       /*!< 可选范围完整  P1_17  */
#define UART8_TX    P1_18       /*!< 可选范围完整  P1_18  */

/*!
  * @brief    串口模块初始化
  *
  * @param    uratn ： USART0 - USART8
  * @param    bdr   ： 波特率
  *
  * @return   无
  *
  * @note     这里实际是将flexcom口用作串口，如果使用了flexcom0当作串口0，那么flexcom0 就不可用作IIC0，SPI0了
  * 
  * @see      UART_InitConfig(USART0, 115200);   //初始化串口0 波特率 115200 无奇偶校验 1停止位 使用管脚LQ_UART.h中通过宏定义选取
  *
  * @date     2019/10/19 星期六
  */
void UART_InitConfig(USART_Type * uratn,uint32_t bdr);



/*!
  * @brief    串口打印一个字符
  *
  * @param    uratn ： USART0 - USART8 
  * @param    ch    ： 要打印的字符
  *
  * @return   无
  *
  * @note     使用前请先初始化对应串口
  *
  * @see      UART_PutChar(USART0, 'a');  //打印字符a
  *
  * @date     2019/10/19 星期六
  */
void UART_PutChar(USART_Type * uratn, char ch);



/*!
  * @brief    串口打印字符串
  *
  * @param    uratn ： USART0 - USART8 
  * @param    str   ： 要打印的字符串地址 
  *
  * @return   无
  *
  * @note     使用前请先初始化对应串口
  *
  * @see      UART_PutStr(USART4, "123456789"); //发送9个字节      
  *
  * @date     2019/10/21 星期一
  */
void UART_PutStr(USART_Type * uratn, char *str);


/*!
  * @brief    打印已知长度的数组
  *
  * @param    uratn ： USART0 - USART8 
  * @param    buff  ： 要打印的字符串地址    
  * @param    len   ： 要打印的长度
  *
  * @return   无
  *
  * @note     使用前请先初始化对应串口
  *
  * @see      UART_PutBuff(USART4, "123456789",5);//实际发送5个字节‘1’‘2’‘3’‘4’‘5’    
  *
  * @date     2019/10/21 星期一
  */
void UART_PutBuff(USART_Type *base, uint8_t *buff, uint32_t len);


/*!
  * @brief    接收一个字符
  *
  * @param    uratn ： USART0 - USART8   
  *
  * @return   接收到的字符
  *
  * @note     使用前请先初始化对应串口
  *
  * @see      UART_GetChar(USART4); //接收一个字符
  *
  * @date     2019/10/21 星期一
  */
char UART_GetChar(USART_Type * uratn);




/*!
  * @brief    串口管脚复用设置
  *
  * @param    uratn ： USART0 - USART8
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      UART_PinInit(USART0); //初始化串口0的管脚 管脚在LQ_UART.h中通过宏定义选择
  *
  * @date     2019/10/19 星期六
  */
void UART_PinInit(USART_Type * uratn);

#endif
