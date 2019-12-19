/*!
  * @file     LQ_SOFTSPI.c
  *
  * @brief    ģ��SPI����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/19 ������
  */ 
#include "LQ_SOFTSPI.h"
#include "LQ_GPIO.h"
/*!
  * @brief    ģ��SPI ��ʱ����
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      SPI_SoftDelay();
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftDelay(void)
{
    __asm("NOP");
    __asm("NOP");
    __asm("NOP");
}


/*!
  * @brief    ģ��SPI��ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ģ��SPIʹ�ùܽ� LQ_SOFTSPI.h�к궨��
  *
  * @see      SPI_SoftInit();  //ģ��SPI�ܽų�ʼ��
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftInit(void)
{
    PIN_InitConfig(SOFT_SPI_CS_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_SPI_SCK_PIN, PIN_MODE_OUTPUT, 1);
    PIN_InitConfig(SOFT_SPI_MISO_PIN, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(SOFT_SPI_MOSI_PIN, PIN_MODE_OUTPUT, 1);

}

/*!
  * @brief    ģ��SPI��дn �ֽ�
  *
  * @param    buff[] ���Ҫд���ֵ д����Ŷ�ȡ��ֵ
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      uint8_t data[8];
  * @see      SPI_SoftRadeWriteNbyte(data, sizeof(data)); //SPI��д8���ֽ�
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len)
{
    SPI_CS_OUT(0);
    SPI_SCK_IDLE;
//    SPI_SoftDelay();
#if CPHA    //�ڶ���ʱ��������
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
