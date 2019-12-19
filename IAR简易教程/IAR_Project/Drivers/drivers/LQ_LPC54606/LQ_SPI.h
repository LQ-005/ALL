/*!
  * @file     LQ_SPI.h
  *
  * @brief    SPI�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     ��
  *
  * @version  V1.1   2019/11/27  �޸���SPIʱ��Դ 12M->48M  �Ż���SPIƬѡ�ܽſ���ʹ������IO
                     2019/12/11  �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#ifndef __LQ_SPI_H
#define __LQ_SPI_H
#include "fsl_spi.h"
#include "LQ_GPIO.h"

//����ʵ���ǽ�flexcom������SPI�����ʹ����flexcom0����SPI0����ôflexcom0 �Ͳ�����������0��IIC0��
/**********************************  SPI(flexcom���Ÿ���ΪSPI) ***************************************/
//        ģ����           �˿�          ��ѡ��Χ����  
#define SPI0_SCK_PIN        P0_28      /*!<��ѡ��Χ���� P0_28  P1_4         */
#define SPI0_MOSI_PIN       P0_24      /*!<��ѡ��Χ���� P0_24  P0_29  P1_5  */
#define SPI0_MISO_PIN       P0_25      /*!<��ѡ��Χ���� P0_25  P0_30  P1_6  */
#define SPI0_CS0_PIN        P0_31      /*!<��ѡ��Χ���� ����IO */
                                       
#define SPI1_SCK_PIN        P0_7       /*!<��ѡ��Χ���� P0_7   P1_9  */
#define SPI1_MOSI_PIN       P1_10      /*!<��ѡ��Χ���� P1_10        */
#define SPI1_MISO_PIN       P0_10      /*!<��ѡ��Χ���� P0_10  P1_11 */
#define SPI1_CS0_PIN        P0_13      /*!<��ѡ��Χ���� ����IO       */
                                       
#define SPI2_SCK_PIN        P1_23      /*!<��ѡ��Χ���� P1_23        */
#define SPI2_MOSI_PIN       P0_26      /*!<��ѡ��Χ���� P0_26  P1_24 */
#define SPI2_MISO_PIN       P0_27      /*!<��ѡ��Χ���� P0_27  P1_25 */
#define SPI2_CS0_PIN        P1_26      /*!<��ѡ��Χ���� ����IO       */
                                           
#define SPI3_SCK_PIN        P0_6       /*!<��ѡ��Χ���� P0_0  P0_6   */
#define SPI3_MOSI_PIN       P0_3       /*!<��ѡ��Χ���� P0_3  P1_1   */
#define SPI3_MISO_PIN       P0_2       /*!<��ѡ��Χ���� P0_2  P0_12  */
#define SPI3_CS0_PIN        P0_20      /*!<��ѡ��Χ���� ����IO       */
                                       
#define SPI4_SCK_PIN        P0_4       /*!<��ѡ��Χ���� P0_4   P1_19 */
#define SPI4_MOSI_PIN       P0_5       /*!<��ѡ��Χ���� P0_5   P1_21 */
#define SPI4_MISO_PIN       P0_16      /*!<��ѡ��Χ���� P0_16  P1_20 */
#define SPI4_CS0_PIN        P0_18      /*!<��ѡ��Χ���� ����IO       */
                                           
#define SPI5_SCK_PIN        P0_7       /*!<��ѡ��Χ���� P0_7         */
#define SPI5_MOSI_PIN       P0_8       /*!<��ѡ��Χ���� P0_8         */
#define SPI5_MISO_PIN       P0_9       /*!<��ѡ��Χ���� P0_9         */
#define SPI5_CS0_PIN        P1_14      /*!<��ѡ��Χ���� ����IO       */
                                       
#define SPI6_SCK_PIN        P0_10      /*!<��ѡ��Χ���� P0_10  P1_12 */
#define SPI6_MOSI_PIN       P0_11      /*!<��ѡ��Χ���� P0_11  P1_13 */
#define SPI6_MISO_PIN       P0_22      /*!<��ѡ��Χ���� P0_22  P1_16 */
#define SPI6_CS0_PIN        P0_15      /*!<��ѡ��Χ���� ����IO       */
                                           
#define SPI7_SCK_PIN        P0_21      /*!<��ѡ��Χ���� P0_21  P1_28 */
#define SPI7_MOSI_PIN       P0_20      /*!<��ѡ��Χ���� P0_20  P1_29 */
#define SPI7_MISO_PIN       P0_19      /*!<��ѡ��Χ���� P0_19  P1_30 */
#define SPI7_CS0_PIN        P1_21      /*!<��ѡ��Χ���� ����IO       */

#define SPI8_SCK_PIN        P1_19      /*!<��ѡ��Χ���� P1_19        */
#define SPI8_MOSI_PIN       P1_17      /*!<��ѡ��Χ���� P1_17        */
#define SPI8_MISO_PIN       P1_18      /*!<��ѡ��Χ���� P1_18        */
#define SPI8_CS0_PIN        P1_31      /*!<��ѡ��Χ���� ����IO       */


/**
  * @brief    SPI ����ģʽ��ʼ��
  *
  * @param    base      ��  SPI0 - SPI8
  * @param      mode            0: CLK����ʱ��Ϊ�͵�ƽ �ڵ�һ��CLK������ ��������
  * @param      mode            1: CLK����ʱ��Ϊ�͵�ƽ �ڵڶ���CLK������ ��������
  * @param      mode            2: CLK����ʱ��Ϊ�ߵ�ƽ �ڵ�һ��CLK������ ��������
  * @param      mode            3: CLK����ʱ��Ϊ�ߵ�ƽ �ڵڶ���CLK������ ��������
  * @param    baudrate  ��  SPI ������    
  *
  * @return   ע�� SPI�����ʲ�Ҫ����8M 
  *
  * @note     ����ʵ���ǽ�flexcom������SPI�����ʹ����flexcom0����SPI0����ôflexcom0 �Ͳ�����������0��IIC0��
  *
  * @see      SPI_MasterInitConfig(SPI3, 3, 4000000U); //��ʼ��SPI3 ʹ��ƬѡCS0 4M����
  *
  * @date     2019/6/3 ����һ
  */
void SPI_MasterInitConfig(SPI_Type * base, uint8_t mode, uint32_t baudrate);


/**
  * @brief    SPI��дN���ֽ�
  *
  * @param    base    ��  SPI0 - SPI8
  * @param    txData  ��  д���buff
  * @param    rxData  ��  ������buff
  * @param    len     ��  ����
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      uint8_t buff[2];
  * @see      SPI_ReadWriteNByte(SPI3, buff, buff, 2); //ʹ��SPI3 ��д�����ֽ� 
  *
  * @date     2019/6/3 ����һ
  */
uint8_t SPI_ReadWriteNByte(SPI_Type * base, uint8_t *txData, uint8_t *rxData, uint32_t len);



/*!
  * @brief    ����Ƭѡ�ź�
  *
  * @param    base    ��  SPI0 - SPI8 
  * @param    output  ��  Ƭѡ�����ƽ  0���͵�ѹ    �����ߵ�ƽ
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      SPI_SetCS(SPI0, 0); //��SPI0��ƬѡΪ�͵�ƽ
  *
  * @date     2019/11/27 ������
  */
void SPI_SetCS(SPI_Type * base, uint8_t output);




/*!
  * @brief    SPI�ܽų�ʼ��
  *
  * @param    base      ��  SPI0 - SPI8   
  *
  * @return   ��
  *
  * @note     �ڲ�����
  *
  * @see      SPI_PinInit(SPI0, 1); //��ʼ��SPI0�ܽ� Ƭѡʹ�� SPI0_CS1_PIN
  *
  * @date     2019/10/29 ���ڶ�
  */
void SPI_PinInit(SPI_Type * base);



#endif
