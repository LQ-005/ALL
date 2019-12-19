/*!
  * @file     LQ_UART.c
  *
  * @brief    UART�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1  2019/12/11 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "LQ_UART.h"
#include "pin_mux.h"
#include "fsl_iocon.h"
#include "fsl_clock.h"
#include "fsl_usart.h"
#include "stdio.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	 ��Ҫͷ�ļ� #include "stdio.h"
//IAR����Ҫ��options -> C/C++compiler -> Preprocessor ��Ӻ궨�� _DLIB_FILE_DESCRIPTOR
//MDK����Ҫ��options -> C/C++compiler -> Define ��Ӻ궨�� _DLIB_FILE_DESCRIPTOR 
//MDK����Ҫ��ѡoptions -> Target -> Use MicroLIB  
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����  ʹ�ô���0��Ϊprintf�Ĵ�ӡ��
int fputc(int ch, FILE *f)
{ 
	//��������
    UART_PutChar(USART0, ch);

	return ch;
}
#endif 

/*!
  * @brief    ����ģ���ʼ��
  *
  * @param    uratn �� USART0 - USART8
  * @param    bdr   �� ������
  *
  * @return   ��
  *
  * @note     ����ʵ���ǽ�flexcom���������ڣ����ʹ����flexcom0��������0����ôflexcom0 �Ͳ�������IIC0��SPI0��
  * 
  * @see      UART_InitConfig(USART0, 115200);   //��ʼ������0 ������ 115200 ����żУ�� 1ֹͣλ ʹ�ùܽ�LQ_UART.h��ͨ���궨��ѡȡ
  *
  * @date     2019/10/19 ������
  */
void UART_InitConfig(USART_Type * uratn,uint32_t bdr)
{
    /* ��IO����Ϊ���� */
    UART_PinInit(uratn);

    /* ��ȡҪ��ʼ���Ĵ��ں� */
    uint8_t temp = USART_GetInstance(uratn);
    
    /* ��������ʱ�� */
    CLOCK_AttachClk((clock_attach_id_t)(kFRO12M_to_FLEXCOMM0 + temp));
    
    /* usart ��ʼ�����ýṹ�� */
    usart_config_t config;
    USART_GetDefaultConfig(&config);
    
    /* ���ò����� */
    config.baudRate_Bps = bdr;
    
    /* ʹ�ܽ��շ��� */
    config.enableTx = true;
    config.enableRx = true;
    
    /* ������żУ��λ */
    config.parityMode = kUSART_ParityDisabled;
    
    /* ����ֹͣλ */
    config.stopBitCount = kUSART_OneStopBit;
    
    /* ���ô����ֽڳ��� */
    config.bitCountPerChar = kUSART_8BitsPerChar;
     
    /* ��ʼ������ģ�� */
    USART_Init(uratn, &config, CLOCK_GetFreq((clock_name_t)(kCLOCK_Flexcomm0 + temp))); 
    
    /* ���������ж� */
    USART_EnableInterrupts(uratn, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
    
}

/*!
  * @brief    ���ڴ�ӡһ���ַ�
  *
  * @param    uratn �� USART0 - USART8 
  * @param    ch    �� Ҫ��ӡ���ַ�
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ����Ӧ����
  *
  * @see      UART_PutChar(USART0, 'a');  //��ӡ�ַ�a
  *
  * @date     2019/10/19 ������
  */
void UART_PutChar(USART_Type * uratn, char ch)
{
    //�ȴ����ͻ�������
    while(!(kUSART_TxFifoNotFullFlag & USART_GetStatusFlags(uratn)));
    
    //��������
    USART_WriteByte(uratn, (uint8_t)ch);
}


/*!
  * @brief    ���ڴ�ӡ�ַ���
  *
  * @param    uratn �� USART0 - USART8 
  * @param    str   �� Ҫ��ӡ���ַ�����ַ 
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ����Ӧ����
  *
  * @see      UART_PutStr(USART4, "123456789"); //����9���ֽ�      
  *
  * @date     2019/10/21 ����һ
  */
void UART_PutStr(USART_Type * uratn, char *str)
{    
   while(*str)
    {
        UART_PutChar(uratn, *str++);
    }
    
}


/*!
  * @brief    ��ӡ��֪���ȵ�����
  *
  * @param    uratn �� USART0 - USART8 
  * @param    buff  �� Ҫ��ӡ���ַ�����ַ    
  * @param    len   �� Ҫ��ӡ�ĳ���
  *
  * @return   ��
  *
  * @note     ʹ��ǰ���ȳ�ʼ����Ӧ����
  *
  * @see      UART_PutBuff(USART4, "123456789",5);//ʵ�ʷ���5���ֽڡ�1����2����3����4����5��    
  *
  * @date     2019/10/21 ����һ
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
  * @brief    ����һ���ַ�
  *
  * @param    uratn �� USART0 - USART8   
  *
  * @return   ���յ����ַ�
  *
  * @note     ʹ��ǰ���ȳ�ʼ����Ӧ����
  *
  * @see      UART_GetChar(USART4); //����һ���ַ�
  *
  * @date     2019/10/21 ����һ
  */
char UART_GetChar(USART_Type * uratn)
{    
    /* �ȴ��������� */
    while(!(kUSART_RxFifoNotEmptyFlag & USART_GetStatusFlags(uratn)));
    
    /* ��ȡ���յ���8λ���� */
    return (USART_ReadByte(uratn));

}



/*!
  * @brief    ���ڹܽŸ�������
  *
  * @param    uratn �� USART0 - USART8 
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      UART_PinInit(USART0); //��ʼ������0�Ĺܽ� �ܽ���LQ_UART.h��ͨ���궨��ѡ��
  *
  * @date     2019/10/19 ������
  */
void UART_PinInit(USART_Type * uratn)
{
    /* �򿪸�����ʱ�� */
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
