/*!
  * @file     LQ_UART.c
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
#include "LQ_UART.h"
#include "pin_mux.h"
#include "fsl_iocon.h"
#include "fsl_clock.h"
#include "fsl_usart.h"
#include "stdio.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	 需要头文件 #include "stdio.h"
//IAR，需要在options -> C/C++compiler -> Preprocessor 添加宏定义 _DLIB_FILE_DESCRIPTOR
//MDK，需要在options -> C/C++compiler -> Define 添加宏定义 _DLIB_FILE_DESCRIPTOR 
//MDK，需要勾选options -> Target -> Use MicroLIB  
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数  使用串口0作为printf的打印口
int fputc(int ch, FILE *f)
{ 
	//发送数据
    UART_PutChar(USART0, ch);

	return ch;
}
#endif 

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
void UART_InitConfig(USART_Type * uratn,uint32_t bdr)
{
    /* 将IO复用为串口 */
    UART_PinInit(uratn);

    /* 获取要初始化的串口号 */
    uint8_t temp = USART_GetInstance(uratn);
    
    /* 开启串口时钟 */
    CLOCK_AttachClk((clock_attach_id_t)(kFRO12M_to_FLEXCOMM0 + temp));
    
    /* usart 初始化配置结构体 */
    usart_config_t config;
    USART_GetDefaultConfig(&config);
    
    /* 设置波特率 */
    config.baudRate_Bps = bdr;
    
    /* 使能接收发送 */
    config.enableTx = true;
    config.enableRx = true;
    
    /* 设置奇偶校验位 */
    config.parityMode = kUSART_ParityDisabled;
    
    /* 设置停止位 */
    config.stopBitCount = kUSART_OneStopBit;
    
    /* 设置传输字节长度 */
    config.bitCountPerChar = kUSART_8BitsPerChar;
     
    /* 初始化串口模块 */
    USART_Init(uratn, &config, CLOCK_GetFreq((clock_name_t)(kCLOCK_Flexcomm0 + temp))); 
    
    /* 开启接收中断 */
    USART_EnableInterrupts(uratn, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
    
}

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
void UART_PutChar(USART_Type * uratn, char ch)
{
    //等待发送缓冲区空
    while(!(kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(uratn)));
    
    //发送数据
    USART_WriteByte(uratn, (uint8_t)ch);
}


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
void UART_PutStr(USART_Type * uratn, char *str)
{    
   while(*str)
    {
        UART_PutChar(uratn, *str++);
    }
    
}


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
void UART_PutBuff(USART_Type *base, uint8_t *buff, uint32_t len)
{
    while(len--)
    {
        UART_PutChar(base, *buff);
        buff++;
    }
}

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
char UART_GetChar(USART_Type * uratn)
{    
    /* 等待接收满了 */
    while(!(kUSART_RxFifoNotEmptyFlag & USART_GetStatusFlags(uratn)));
    
    /* 获取接收到的8位数据 */
    return (USART_ReadByte(uratn));

}



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
void UART_PinInit(USART_Type * uratn)
{
    /* 打开复用器时钟 */
    CLOCK_EnableClock(kCLOCK_Iocon);
    
    uint32_t PIOFun1_config = FUNC1|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun2_config = FUNC2|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun3_config = FUNC3|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun4_config = FUNC4|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun5_config = FUNC5|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    uint32_t PIOFun7_config = FUNC7|MODE_Up|MODE_GPIO|INVERT_Disable|DIGIMODE_Digital|FILTER_Disable;
    
    switch((uint32_t)uratn)
    {
      case (uint32_t)USART0:         
        if(UART0_RX==P0_29)
            IOCON_PinMuxSet(IOCON, 0, 29, PIOFun1_config); 
        else if(UART0_RX==P0_24)
            IOCON_PinMuxSet(IOCON, 0, 24, PIOFun1_config); 
        else if(UART0_RX==P1_5)
            IOCON_PinMuxSet(IOCON, 1, 5, PIOFun1_config);
        
        if(UART0_TX==P0_30)
            IOCON_PinMuxSet(IOCON, 0, 30, PIOFun1_config); 
        else if(UART0_TX==P0_25)
            IOCON_PinMuxSet(IOCON, 0, 25, PIOFun1_config);
        else if(UART0_TX==P1_6)
            IOCON_PinMuxSet(IOCON, 1, 6, PIOFun1_config);
        break;
        
      case (uint32_t)USART1:
        if(UART1_RX==P1_10)
            IOCON_PinMuxSet(IOCON, 1, 10, PIOFun2_config); 
        
        if(UART1_TX==P1_11)
            IOCON_PinMuxSet(IOCON, 1, 11, PIOFun2_config);  
        else if(UART1_TX==P0_10)
            IOCON_PinMuxSet(IOCON, 0,  10, PIOFun4_config); 
        break;
        
      case (uint32_t)USART2:
        if(UART2_RX==P0_26)
            IOCON_PinMuxSet(IOCON, 0, 26, PIOFun1_config); 
        else if(UART2_RX==P1_24)
            IOCON_PinMuxSet(IOCON, 1, 24, PIOFun1_config); 
        if(UART2_TX==P0_27)
            IOCON_PinMuxSet(IOCON, 0, 27, PIOFun1_config); 
        else if(UART2_TX==P1_25)
            IOCON_PinMuxSet(IOCON, 1, 25, PIOFun1_config); 
        break;
        
      case (uint32_t)USART3:
        if(UART3_RX==P0_3)
            IOCON_PinMuxSet(IOCON, 0, 3, PIOFun1_config);
        else if(UART3_RX==P1_1)
            IOCON_PinMuxSet(IOCON, 1, 1, PIOFun1_config);
        if(UART3_TX==P0_2)
            IOCON_PinMuxSet(IOCON, 0, 2, PIOFun1_config); 
        else if(UART3_TX==P0_12)
            IOCON_PinMuxSet(IOCON, 0, 12, PIOFun1_config);          
        break;
        
      case (uint32_t)USART4:
        if(UART4_RX==P1_21)
            IOCON_PinMuxSet(IOCON, 1, 21, PIOFun5_config); 
        else if(UART4_RX==P0_5)
            IOCON_PinMuxSet(IOCON, 0, 5, PIOFun2_config);   
        
        if(UART4_TX==P1_20)
            IOCON_PinMuxSet(IOCON, 1, 20, PIOFun5_config);   
        else if(UART4_TX==P0_16)
            IOCON_PinMuxSet(IOCON, 0, 16, PIOFun1_config);   
        break;
        
      case (uint32_t)USART5:
        if(UART5_RX==P0_8)
            IOCON_PinMuxSet(IOCON, 0, 8, PIOFun3_config);  

        if(UART5_TX==P0_9)
            IOCON_PinMuxSet(IOCON, 0, 9, PIOFun3_config);
        break;
        
      case (uint32_t)USART6:
        if(UART6_RX==P0_11)
            IOCON_PinMuxSet(IOCON, 0, 11, PIOFun1_config);  
        else if(UART6_RX==P1_13)
            IOCON_PinMuxSet(IOCON, 1, 13, PIOFun2_config);  
        if(UART6_TX==P0_22)
            IOCON_PinMuxSet(IOCON, 0, 22, PIOFun1_config); 
        else if(UART6_TX==P1_16)
            IOCON_PinMuxSet(IOCON, 1, 16, PIOFun2_config); 
        break;
        
      case (uint32_t)USART7:
        if(UART7_RX==P1_29)
            IOCON_PinMuxSet(IOCON, 1, 29, PIOFun1_config);
        else if(UART7_RX==P0_20)
            IOCON_PinMuxSet(IOCON, 0, 20, PIOFun7_config);
        
        if(UART7_TX==P1_30)
            IOCON_PinMuxSet(IOCON, 1, 30, PIOFun1_config);
        else if(UART7_TX==P0_19)         
            IOCON_PinMuxSet(IOCON, 0, 19, PIOFun7_config);
        break;
        
      case (uint32_t)USART8:
        if(UART8_RX==P1_17)
            IOCON_PinMuxSet(IOCON, 1, 17, PIOFun2_config);

        if(UART8_TX==P1_18)
            IOCON_PinMuxSet(IOCON, 1, 18, PIOFun2_config);
        break;

      default:
        break;
    }    
}
