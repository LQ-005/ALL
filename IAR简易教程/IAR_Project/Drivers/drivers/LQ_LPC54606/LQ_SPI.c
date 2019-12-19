/*!
  * @file     LQ_SPI.c
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
#include "fsl_spi.h"
#include "fsl_clock.h"
#include "LQ_SPI.h"


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
void SPI_MasterInitConfig(SPI_Type * base, uint8_t mode, uint32_t baudrate)
{
    /* ��ʼ���ܽ� */
    SPI_PinInit(base);
    
    /* ��ȡҪ��ʼ����SPI */
    uint8_t temp = SPI_GetInstance(base);
    
	/* ����FlexComʱ�� 48M */
	SYSCON->FROHFCLKDIV = ((SYSCON->FROHFCLKDIV & ~SYSCON_FROHFCLKDIV_DIV_MASK) | SYSCON_FROHFCLKDIV_DIV(0U)); /*!< Set FROHF CLKDIV  to value 0 */ 
    CLOCK_AttachClk((clock_attach_id_t)(kFRO_HF_to_FLEXCOMM0 + temp));

    spi_master_config_t masterConfig;
    
    /*Master config*/
    masterConfig.baudRate_Bps = baudrate;                           //���ò�����
    masterConfig.dataWidth    = kSPI_Data8Bits;                     //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    if(mode / 2)
    {
        masterConfig.polarity = kSPI_ClockPolarityActiveLow;  //ʱ�ӿ���ʱΪ�ߵ�ƽ
    }
    else
    {
        masterConfig.polarity = kSPI_ClockPolarityActiveHigh; //ʱ�ӿ���ʱΪ�͵�ƽ
    }
    
    if(mode % 2)
    {
        masterConfig.phase = kSPI_ClockPhaseSecondEdge;  //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    }
    else
    {
        masterConfig.phase = kSPI_ClockPhaseFirstEdge;  //����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
    }
    
    masterConfig.direction = kSPI_MsbFirst;             //MSB��ǰ

    /* ��ʼ�� SPI */
    SPI_MasterInit(base, &masterConfig, CLOCK_GetFreq((clock_name_t)(kCLOCK_Flexcomm0 + temp)));
}



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
uint8_t SPI_ReadWriteNByte(SPI_Type * base, uint8_t *txData, uint8_t *rxData, uint32_t len)
{
    /* Ƭѡѡ�� */
    SPI_SetCS(base, 0);
    
	/*!< SPI����ṹ�� */
    spi_transfer_t spi_tranxfer;
    spi_tranxfer.txData = txData;   //��������
    spi_tranxfer.rxData = rxData;   //��������
    spi_tranxfer.dataSize = len;    //���� 
    
    uint8_t err = SPI_MasterTransferBlocking(base, &spi_tranxfer);        //spi��������;
    
    /* Ƭѡ���� */
    SPI_SetCS(base, 1);
    return err;
}

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
void SPI_SetCS(SPI_Type * base, uint8_t output)
{
    switch((uint32_t)base)
    {
      case (uint32_t)SPI0:
        PIN_Write(SPI0_CS0_PIN,  output);
        break;
      case (uint32_t)SPI1:
        PIN_Write(SPI1_CS0_PIN,  output);
        break;
      case (uint32_t)SPI2:
        PIN_Write(SPI2_CS0_PIN,  output);
        break;
      case (uint32_t)SPI3:
        PIN_Write(SPI3_CS0_PIN,  output);
        break;
      case (uint32_t)SPI4:
        PIN_Write(SPI4_CS0_PIN,  output);
        break;
      case (uint32_t)SPI5:
        PIN_Write(SPI5_CS0_PIN,  output);
        break;
      case (uint32_t)SPI6:
        PIN_Write(SPI6_CS0_PIN,  output);
        break;
      case (uint32_t)SPI7:
        PIN_Write(SPI7_CS0_PIN,  output);
        break;
      case (uint32_t)SPI8:
        PIN_Write(SPI8_CS0_PIN,  output);
        break;
      default:
        break;
        
    }
}


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
void SPI_PinInit(SPI_Type * base)
{

    switch((uint32_t)base)
    {
        case (uint32_t)SPI0:
        {
            if      (P0_28 == SPI0_SCK_PIN)       PIN_MuxSet(P0_28,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_4 == SPI0_SCK_PIN)        PIN_MuxSet(P1_4, FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P0_24 == SPI0_MOSI_PIN)     PIN_MuxSet(P0_24,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P0_29 == SPI0_MOSI_PIN)     PIN_MuxSet(P0_29,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_5  == SPI0_MOSI_PIN)     PIN_MuxSet(P1_5, FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P0_25 == SPI0_MISO_PIN)     PIN_MuxSet(P0_25,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P0_30 == SPI0_MISO_PIN)     PIN_MuxSet(P0_30,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_6  == SPI0_MISO_PIN)     PIN_MuxSet(P1_6, FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
             
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI0_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI1:
        {
            if      (P0_7 == SPI1_SCK_PIN)        PIN_MuxSet(P0_7, FUNC4 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_9 == SPI1_SCK_PIN)        PIN_MuxSet(P1_9, FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P1_10 == SPI1_MOSI_PIN)     PIN_MuxSet(P1_10, FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P0_10 == SPI1_MISO_PIN)     PIN_MuxSet(P0_10,FUNC4 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_11 == SPI1_MISO_PIN)     PIN_MuxSet(P1_11,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI1_CS0_PIN, PIN_MODE_OUTPUT, 1);
            
            
        }break;
        
        case (uint32_t)SPI2:
        {
            if      (P1_23 == SPI2_SCK_PIN)       PIN_MuxSet(P1_23,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
         
            if      (P0_26 == SPI2_MOSI_PIN)     PIN_MuxSet(P0_26,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_24 == SPI2_MOSI_PIN)     PIN_MuxSet(P1_24,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
        
            if      (P0_27 == SPI2_MISO_PIN)     PIN_MuxSet(P0_27,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_25 == SPI2_MISO_PIN)     PIN_MuxSet(P1_25,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
          
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI2_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI3:
        {
            if      (P0_0 == SPI3_SCK_PIN)        PIN_MuxSet(P0_0, FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            else if (P0_6 == SPI3_SCK_PIN)        PIN_MuxSet(P0_6, FUNC1 | DIGIMODE_Digital | FILTER_Disable);
          
            if      (P0_3 == SPI3_MOSI_PIN)      PIN_MuxSet(P0_3, FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_1 == SPI3_MOSI_PIN)      PIN_MuxSet(P1_1, FUNC1 | DIGIMODE_Digital | FILTER_Disable);
           
            if      (P0_2 == SPI3_MISO_PIN)      PIN_MuxSet(P0_2, FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P0_12 == SPI3_MISO_PIN)     PIN_MuxSet(P0_12,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
           
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI3_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI4:
        {
            if      (P0_4 == SPI4_SCK_PIN)        PIN_MuxSet(P0_4, FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_19 == SPI4_SCK_PIN)       PIN_MuxSet(P1_19,FUNC5 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P0_5 == SPI4_MOSI_PIN)      PIN_MuxSet(P0_5, FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_21 == SPI4_MOSI_PIN)     PIN_MuxSet(P1_21,FUNC5 | DIGIMODE_Digital | FILTER_Disable);
          
            if      (P0_16 == SPI4_MISO_PIN)     PIN_MuxSet(P0_16,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_20 == SPI4_MISO_PIN)     PIN_MuxSet(P1_20,FUNC5 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
           
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI4_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI5:
        {
            if      (P0_7 == SPI5_SCK_PIN)        PIN_MuxSet(P0_7, FUNC3 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P0_8 == SPI5_MOSI_PIN)      PIN_MuxSet(P0_8, FUNC3 | DIGIMODE_Digital | FILTER_Disable);
           
            if      (P0_9 == SPI5_MISO_PIN)      PIN_MuxSet(P0_9, FUNC3 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
           
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI5_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI6:
        {
            if      (P0_10 == SPI6_SCK_PIN)       PIN_MuxSet(P0_10,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_12 == SPI6_SCK_PIN)       PIN_MuxSet(P1_12,FUNC2 | DIGIMODE_Digital | FILTER_Disable);
           
            if      (P0_11 == SPI6_MOSI_PIN)     PIN_MuxSet(P0_11,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_13 == SPI6_MOSI_PIN)     PIN_MuxSet(P1_13,FUNC2 | DIGIMODE_Digital | FILTER_Disable);
          
            if      (P0_22 == SPI6_MISO_PIN)     PIN_MuxSet(P0_22,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_16 == SPI6_MISO_PIN)     PIN_MuxSet(P1_16,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);

            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI6_CS0_PIN, PIN_MODE_OUTPUT, 1);

        }break;
        
        case (uint32_t)SPI7:
        {
            if      (P0_21 == SPI7_SCK_PIN)       PIN_MuxSet(P0_21,FUNC7 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_28 == SPI7_SCK_PIN)       PIN_MuxSet(P1_28,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
           
            if      (P0_20 == SPI7_MOSI_PIN)     PIN_MuxSet(P0_20,FUNC7 | DIGIMODE_Digital | FILTER_Disable);
            else if (P1_29 == SPI7_MOSI_PIN)     PIN_MuxSet(P1_29,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
           
            if      (P0_19 == SPI7_MISO_PIN)     PIN_MuxSet(P0_19,FUNC7 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            else if (P1_30 == SPI7_MISO_PIN)     PIN_MuxSet(P1_30,FUNC1 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
            
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI7_CS0_PIN, PIN_MODE_OUTPUT, 1);
        }break;
        
        case (uint32_t)SPI8:
        {
            if      (P1_19 == SPI8_SCK_PIN)       PIN_MuxSet(P1_19,FUNC1 | DIGIMODE_Digital | FILTER_Disable);
          
            if      (P1_17 == SPI8_MOSI_PIN)     PIN_MuxSet(P1_17,FUNC2 | DIGIMODE_Digital | FILTER_Disable);
            
            if      (P1_18 == SPI8_MISO_PIN)     PIN_MuxSet(P1_18,FUNC2 | DIGIMODE_Digital | FILTER_Disable | MODE_Up);
           
            /* SPIƬѡCS�ܽ� ����IO */
            PIN_InitConfig(SPI8_CS0_PIN, PIN_MODE_OUTPUT, 1);

        }break;
        
    }
}
