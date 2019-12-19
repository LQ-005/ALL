/*!
  * @file     LQ_SOFTSPI.c
  *
  * @brief    模拟SPI驱动
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     无
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 星期六
  */ 
#include "LQ_SOFTSPI.h"
#include "LQ_GPIO.h"
/*!
  * @brief    模拟SPI 延时函数
  *
  * @param    无
  *
  * @return   无
  *
  * @note     内部调用
  *
  * @see      SPI_SoftDelay();
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftDelay(void)
{
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
}


/*!
  * @brief    模拟SPI初始化
  *
  * @param    无
  *
  * @return   无
  *
  * @note     模拟SPI使用管脚 LQ_SOFTSPI.h中宏定义
  *
  * @see      SPI_SoftInit();  //模拟SPI管脚初始化
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftInit(void)
{
    PIN_InitConfig(SOFT_SPI_CS_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_SPI_SCK_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_SPI_MISO_PIN, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(SOFT_SPI_MOSI_PIN, PIN_MODE_OUTPUT, 1);

}

/*!
  * @brief    模拟SPI读写n 字节
  *
  * @param    buff[] 存放要写入的值 写入后存放读取的值
  *
  * @return   无
  *
  * @note     无
  *
  * @see      uint8_t data[8];
  * @see      SPI_SoftRadeWriteNbyte(data, sizeof(data)); //SPI读写8个字节
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len)
{
    SPI_CS_OUT(0);
    SPI_SCK_IDLE;
//    SPI_SoftDelay();
#if CPHA    //第二个时钟跳边沿
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            SPI_MOSI_OUT((*buff) >= 0x80);
            SPI_SCK_ACTIVE;
            (*buff) = (*buff)<<1;
            
//            SPI_SoftDelay();
            SPI_SCK_IDLE;
//            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;          
        }
        buff++;
    }while(--len);
#else
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {

            SPI_MOSI_OUT((*buff) >= 0x80);
            (*buff) = (*buff)<<1;
            SPI_SCK_ACTIVE;
            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;
            SPI_SCK_IDLE;
            SPI_SoftDelay();           
        }
        buff++;
    }while(--len);
    
    
#endif
    SPI_SCK_IDLE;
    SPI_CS_OUT(1);
    
}
