/*!
  * @file     LQ_UART.h
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
#ifndef __LQ_UART_H
#define __LQ_UART_H

#include "LQ_GPIO.h"
#include "fsl_usart.h"

//����ʵ���ǽ�flexcom���������ڣ����ʹ����flexcom0��������0����ôflexcom0 �Ͳ�������IIC0��SPI0��
/**********************************  UART(flexcom���Ÿ���Ϊ����) ***************************************/
//      ģ��ͨ��    �˿�        ��ѡ��Χ����20171023                          
#define UART0_RX    P0_29       /*!< ��ѡ��Χ���� P0_29  P0_24   P1_5  */
#define UART0_TX    P0_30       /*!< ��ѡ��Χ���� P0_30  P0_25   P1_6  */
                                
#define UART1_RX    P1_10       /*!< ��ѡ��Χ���� P1_10       */
#define UART1_TX    P1_11       /*!< ��ѡ��Χ���� P1_11 P0_10 */
                                
#define UART2_RX    P0_26       /*!< ��ѡ��Χ���� P0_26 P1_24 */
#define UART2_TX    P0_27       /*!< ��ѡ��Χ���� P0_27 P1_25 */
                                
#define UART3_RX    P0_3        /*!< ��ѡ��Χ���� P0_3  P1_1   */
#define UART3_TX    P0_2        /*!< ��ѡ��Χ���� P0_2  P0_12  */
                                
#define UART4_RX    P1_21       /*!< ��ѡ��Χ���� P0_5  P1_21 */
#define UART4_TX    P1_20       /*!< ��ѡ��Χ���� P0_16 P1_20 */
                                
#define UART5_RX    P0_8        /*!< ��ѡ��Χ���� P0_8   */
#define UART5_TX    P0_9        /*!< ��ѡ��Χ���� P0_9   */
                                
#define UART6_RX    P1_13       /*!< ��ѡ��Χ���� P0_11 P1_13    */ 
#define UART6_TX    P0_22       /*!< ��ѡ��Χ���� P0_22 P1_16    */
                                
#define UART7_RX    P1_29       /*!< ��ѡ��Χ���� P0_20 P1_29    */
#define UART7_TX    P1_30       /*!< ��ѡ��Χ���� P0_19 P1_30    */

#define UART8_RX    P1_17       /*!< ��ѡ��Χ����  P1_17  */
#define UART8_TX    P1_18       /*!< ��ѡ��Χ����  P1_18  */

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
void UART_InitConfig(USART_Type * uratn,uint32_t bdr);



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
void UART_PutChar(USART_Type * uratn, char ch);



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
void UART_PutStr(USART_Type * uratn, char *str);


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
void UART_PutBuff(USART_Type *base, uint8_t *buff, uint32_t len);


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
char UART_GetChar(USART_Type * uratn);




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
void UART_PinInit(USART_Type * uratn);

#endif
