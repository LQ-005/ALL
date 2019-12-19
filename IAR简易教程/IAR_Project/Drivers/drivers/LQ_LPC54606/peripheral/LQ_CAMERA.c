/*!
  * @file     LQ_CAMERA.c
  *
  * @brief    ����ͷ�����ļ�
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 ������
  */ 
#include "LQ_SCTIME.h"
#include "LQ_DMA.h"
#include "LQ_GPIO.h"
#include "LQ_MT9V034.h"
#include "LQ_UART.h"
#include "LQ_CAMERA.h"
#include "LQ_12864.h"
#include "LQ_SGP18T.h"
#include "config.h"

/** ͼ��ԭʼ���ݴ�� */
volatile uint8_t Image_Data[IMAGEH][IMAGEW]; 

/** ѹ����֮�����ڴ����Ļ��ʾ����  */
uint8_t Image_Use[LCDH][LCDW];       

/** ��ֵ��������OLED��ʾ������ */
uint8_t Pixle[LCDH][LCDW];   



/*!
  * @brief    �����ϱ���λ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��λ����֡ͷ������������ 
  *
  * @see      CAMERA_Reprot();
  *
  * @date     2019/9/24 ���ڶ�
  */
void CAMERA_Reprot(void)
{
  
    UART_PutChar(USART0, 0xfe);  //֡ͷ
    UART_PutChar(USART0, 0xef);  //֡ͷ
    
    for(int i = 0; i < 120; i++)
    {
        for(int j = 0; j < 188; j++)
        {
            if(Image_Data[i][j] == 0xfe )  //��ֹ������֡β
            {
                Image_Data[i][j] = 0xff;  
            }
            UART_PutChar(USART0, Image_Data[i][j]); //��������
            
        }
    }
    UART_PutChar(USART0, 0xef);  //֡β
    UART_PutChar(USART0, 0xfe);  //֡β

}

/*!
  * @brief    ����ͷ��������
  *
  * @param    fps:  ֡�� 
  *
  * @return   ��
  *
  * @note     ����ͷ��һЩ��������LQ_MT9V034.c�еĺ궨�����޸�
  *
  * @see      CAMERA_Init(50);   //��ʼ��MT9V034  50֡ ע��ʹ�ð�ɫ������Ű�ת����
  *
  * @date     2019/10/22 ���ڶ�
  */
void CAMERA_Init(uint8_t fps)
{
    /* �ر������ж� ��ֹ��ʼ�������� �жϷ����������δ��ʼ�����赼��Ӳ�������ж� */
    DisableInterrupts;
    
    /* ��ʼ������ͷ ����IO */
    PIN_InitConfig(P1_24, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_25, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_26, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_27, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_28, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_29, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_30, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_31, PIN_MODE_INPUT_PULLDOWN, 0);
    
    LQMT9V034_Init(fps);
 
    /* DMA��ʼ�� */
    DMA_CameraInitConfig(&PT1__BYTE3, (uint8_t *)Image_Data, (IMAGEH * IMAGEW));
    
    /* ��ʼ�� SCT ������������ͷ��PCLK  ����DMA���� ע��Ҫ�ȳ�ʼ��DMA */
    SCT_InitCameraConfig(SctInput0_P1_5);
    
    /* ʹ�ܳ��ж� */
    PIN_Exti(P0_0, 7, PIN_IRQ_MODE_RISING);
    
    //���ȼ����� ��ռ���ȼ�0  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж�
    NVIC_SetPriority(PIN_INT7_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,0));
    
	EnableIRQ(PIN_INT7_IRQn);			          //ʹ��PIN_INT7_IRQn���ж�  
    
    /* ��ʼ����� ���ж� */
    EnableInterrupts;
    
}

/**
  * @brief    ��ȡ��Ҫʹ�õ�ͼ������
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      Get_Use_Image();
  *
  * @date     2019/6/25 ���ڶ�
  */
void Get_Use_Image(void)
{ 
#ifdef LQMT9V034    //ʹ������
    
    uint8_t div_h, div_w;
    uint32_t temp_h = 0;
    uint32_t temp_w = 0;
    uint32_t row_start = 0;
    uint32_t lin_start = 0;
    
	div_h = IMAGEH/LCDH;
	div_w = IMAGEW/LCDW;
    
    /* ������ȡͼ�� */
    if(LCDH * div_h != IMAGEH)
    {
        row_start = (IMAGEH - LCDH * div_h)/2;
        temp_h = row_start;
    }
    if(LCDW * div_w != IMAGEW)
    {
        lin_start = (IMAGEW - LCDW * div_w)/2;       
    }
    for(int i = 0; i < LCDH; i++)
    {
        temp_w = lin_start;
        for(int j = 0; j < LCDW; j++)
        {  
            Image_Use[i][j] = Image_Data[temp_h][temp_w];
            temp_w += div_w;
        }
        temp_h += div_h;
    }
#endif
   
}

/*!
  * @brief    ��ֵ��
  *
  * @param    mode  ��  0��ʹ�ô����ֵ    1��ʹ��ƽ����ֵ
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      Get_01_Value(0); //ʹ�ô�򷨶�ֵ��
  *
  * @date     2019/6/25 ���ڶ�
  */
void Get_01_Value(uint8_t mode)
{
  int i = 0,j = 0;
  uint8_t Threshold;
  uint32_t  tv=0;
  char txt[16];
  if(mode)
  {
      //�ۼ�
      for(i = 0; i <LCDH; i++)
      {    
          for(j = 0; j <LCDW; j++)
          {                            
              tv+=Image_Use[i][j];   //�ۼ�  
          } 
      }
      Threshold=tv/LCDH/LCDW;        //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100
      Threshold=Threshold*7/10+10;   //�˴���ֵ���ã����ݻ����Ĺ������趨 
  }
  else
  {
      Threshold = GetOSTU(Image_Use);//�����ֵ
//      Threshold = (uint8_t)(Threshold * 0.5) + 70;
  } 
#ifdef OLED
  sprintf(txt,"%03d",Threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ  
  LCD_P6x8Str(80,0,txt);
#else
  sprintf(txt,"%03d",Threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ  
  TFTSPI_P8X8Str(0,15, txt,u16RED,u16BLUE);
#endif
  
  for(i = 0; i < LCDH; i++)
  {
    for(j = 0; j < LCDW; j++)
    {                                
      if(Image_Use[i][j] >Threshold) //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����    
        Pixle[i][j] =1;        
      else                                        
        Pixle[i][j] =0;
    }    
  }
}





/*!
  * @brief    �������ֵ��С 
  *
  * @param    tmImage �� ͼ������
  *
  * @return   ��ֵ
  *
  * @note     �ο���https://blog.csdn.net/zyzhangyue/article/details/45841255
  * @note     https://www.cnblogs.com/moon1992/p/5092726.html
  * @note     https://www.cnblogs.com/zhonghuasong/p/7250540.html     
  * @note     Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
  * @note     1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
  * @note     2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
  * @note     3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ����	1
  * @note     4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���w0����ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����������) ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
  * @note     5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
  * @note     6) i++��ת��4)��ֱ��iΪ256ʱ��������
  * @note     7) �����g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
  * @note     ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
  * @note     ������ղ�����  https://blog.csdn.net/kk55guang2/article/details/78475414
  * @note     https://blog.csdn.net/kk55guang2/article/details/78490069
  * @note     https://wenku.baidu.com/view/84e5eb271a37f111f0855b2d.html
  *
  * @see      GetOSTU(Image_Use);//�����ֵ
  *
  * @date     2019/6/25 ���ڶ�
  */
int GetOSTU(uint8_t tmImage[LCDH][LCDW]) 
{ 
	int16_t i,j; 
	uint32_t Amount = 0; 
	uint32_t PixelBack = 0; 
	uint32_t PixelIntegralBack = 0; 
	uint32_t PixelIntegral = 0; 
	int32_t PixelIntegralFore = 0; 
	int32_t PixelFore = 0; 
	float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
	int16_t MinValue, MaxValue; 
	uint8_t Threshold = 0;
	uint8_t HistoGram[256];              //  
	
	for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
	
	for (j = 0; j < LCDH; j++) 
	{ 
		for (i = 0; i < LCDW; i++) 
		{ 
			HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
		} 
	} 
	
	for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
	for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
	
	if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
	if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
	
	for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
	
	PixelIntegral = 0;
	for (j = MinValue; j <= MaxValue; j++)
	{
		PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
	}
	SigmaB = -1;
	for (j = MinValue; j < MaxValue; j++)
	{
		PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
		PixelFore = Amount - PixelBack;         //�������ص���
		OmegaBack = (float)PixelBack / Amount;//ǰ�����ذٷֱ�
		OmegaFore = (float)PixelFore / Amount;//�������ذٷֱ�
		PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
		MicroBack = (float)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
		MicroFore = (float)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
		if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
		{
			SigmaB = Sigma;
			Threshold = j;
		}
	}
	return Threshold;                        //���������ֵ;
} 


