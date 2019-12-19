/*!
  * @file     LQ_CAMERA.c
  *
  * @brief    摄像头驱动文件
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     Tab键 4个空格
  *
  * @version  V1.1  2019/12/06 优化注释 Doxygen
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/10/18 星期五
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

/** 图像原始数据存放 */
volatile uint8_t Image_Data[IMAGEH][IMAGEW]; 

/** 压缩后之后用于存放屏幕显示数据  */
uint8_t Image_Use[LCDH][LCDW];       

/** 二值化后用于OLED显示的数据 */
uint8_t Pixle[LCDH][LCDW];   



/*!
  * @brief    串口上报上位机
  *
  * @param    无
  *
  * @return   无
  *
  * @note     上位机的帧头可能有所区别 
  *
  * @see      CAMERA_Reprot();
  *
  * @date     2019/9/24 星期二
  */
void CAMERA_Reprot(void)
{
  
    UART_PutChar(USART0, 0xfe);  //帧头
    UART_PutChar(USART0, 0xef);  //帧头
    
    for(int i = 0; i < 120; i++)
    {
        for(int j = 0; j < 188; j++)
        {
            if(Image_Data[i][j] == 0xfe )  //防止错误发送帧尾
            {
                Image_Data[i][j] = 0xff;  
            }
            UART_PutChar(USART0, Image_Data[i][j]); //发送数据
            
        }
    }
    UART_PutChar(USART0, 0xef);  //帧尾
    UART_PutChar(USART0, 0xfe);  //帧尾

}

/*!
  * @brief    摄像头测试例程
  *
  * @param    fps:  帧率 
  *
  * @return   无
  *
  * @note     摄像头的一些参数，在LQ_MT9V034.c中的宏定义中修改
  *
  * @see      CAMERA_Init(50);   //初始化MT9V034  50帧 注意使用白色带与非门版转接座
  *
  * @date     2019/10/22 星期二
  */
void CAMERA_Init(uint8_t fps)
{
    /* 关闭所有中断 防止初始化过程中 中断服务函数因操作未初始化外设导致硬件访问中断 */
    DisableInterrupts;
    
    /* 初始化摄像头 数据IO */
    PIN_InitConfig(P1_24, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_25, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_26, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_27, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_28, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_29, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_30, PIN_MODE_INPUT_PULLDOWN, 0);
    PIN_InitConfig(P1_31, PIN_MODE_INPUT_PULLDOWN, 0);
    
    LQMT9V034_Init(fps);
 
    /* DMA初始化 */
    DMA_CameraInitConfig(&PT1__BYTE3, (uint8_t *)Image_Data, (IMAGEH * IMAGEW));
    
    /* 初始化 SCT 用于连接摄像头的PCLK  触发DMA传输 注意要先初始化DMA */
    SCT_InitCameraConfig(SctInput0_P1_5);
    
    /* 使能场中断 */
    PIN_Exti(P0_0, 7, PIN_IRQ_MODE_RISING);
    
    //优先级配置 抢占优先级0  子优先级0   越小优先级越高  抢占优先级可打断别的中断
    NVIC_SetPriority(PIN_INT7_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,0));
    
	EnableIRQ(PIN_INT7_IRQn);			          //使能PIN_INT7_IRQn的中断  
    
    /* 初始化完成 打开中断 */
    EnableInterrupts;
    
}

/**
  * @brief    获取需要使用的图像数组
  *
  * @param    无
  *
  * @return   无
  *
  * @note     无
  *
  * @see      Get_Use_Image();
  *
  * @date     2019/6/25 星期二
  */
void Get_Use_Image(void)
{ 
#ifdef LQMT9V034    //使用神眼
    
    uint8_t div_h, div_w;
    uint32_t temp_h = 0;
    uint32_t temp_w = 0;
    uint32_t row_start = 0;
    uint32_t lin_start = 0;
    
	div_h = IMAGEH/LCDH;
	div_w = IMAGEW/LCDW;
    
    /* 从中心取图像 */
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
  * @brief    二值化
  *
  * @param    mode  ：  0：使用大津法阈值    1：使用平均阈值
  *
  * @return   无
  *
  * @note     无
  *
  * @see      Get_01_Value(0); //使用大津法二值化
  *
  * @date     2019/6/25 星期二
  */
void Get_01_Value(uint8_t mode)
{
  int i = 0,j = 0;
  uint8_t Threshold;
  uint32_t  tv=0;
  char txt[16];
  if(mode)
  {
      //累加
      for(i = 0; i <LCDH; i++)
      {    
          for(j = 0; j <LCDW; j++)
          {                            
              tv+=Image_Use[i][j];   //累加  
          } 
      }
      Threshold=tv/LCDH/LCDW;        //求平均值,光线越暗越小，全黑约35，对着屏幕约160，一般情况下大约100
      Threshold=Threshold*7/10+10;   //此处阈值设置，根据环境的光线来设定 
  }
  else
  {
      Threshold = GetOSTU(Image_Use);//大津法阈值
//      Threshold = (uint8_t)(Threshold * 0.5) + 70;
  } 
#ifdef OLED
  sprintf(txt,"%03d",Threshold);//前者为大津法求得的阈值，后者为平均值  
  LCD_P6x8Str(80,0,txt);
#else
  sprintf(txt,"%03d",Threshold);//前者为大津法求得的阈值，后者为平均值  
  TFTSPI_P8X8Str(0,15, txt,u16RED,u16BLUE);
#endif
  
  for(i = 0; i < LCDH; i++)
  {
    for(j = 0; j < LCDW; j++)
    {                                
      if(Image_Use[i][j] >Threshold) //数值越大，显示的内容越多，较浅的图像也能显示出来    
        Pixle[i][j] =1;        
      else                                        
        Pixle[i][j] =0;
    }    
  }
}





/*!
  * @brief    大津法求阈值大小 
  *
  * @param    tmImage ： 图像数据
  *
  * @return   阈值
  *
  * @note     参考：https://blog.csdn.net/zyzhangyue/article/details/45841255
  * @note     https://www.cnblogs.com/moon1992/p/5092726.html
  * @note     https://www.cnblogs.com/zhonghuasong/p/7250540.html     
  * @note     Ostu方法又名最大类间差方法，通过统计整个图像的直方图特性来实现全局阈值T的自动选取，其算法步骤为：
  * @note     1) 先计算图像的直方图，即将图像所有的像素点按照0~255共256个bin，统计落在每个bin的像素点数量
  * @note     2) 归一化直方图，也即将每个bin中像素点数量除以总的像素点
  * @note     3) i表示分类的阈值，也即一个灰度级，从0开始迭代	1
  * @note     4) 通过归一化的直方图，统计0~i 灰度级的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例w0，并统计前景像素的平均灰度u0；统计i~255灰度级的像素(假设像素值在此范围的像素叫做背景像素) 所占整幅图像的比例w1，并统计背景像素的平均灰度u1；
  * @note     5) 计算前景像素和背景像素的方差 g = w0*w1*(u0-u1) (u0-u1)
  * @note     6) i++；转到4)，直到i为256时结束迭代
  * @note     7) 将最大g相应的i值作为图像的全局阈值
  * @note     缺陷:OSTU算法在处理光照不均匀的图像的时候，效果会明显不好，因为利用的是全局像素信息。
  * @note     解决光照不均匀  https://blog.csdn.net/kk55guang2/article/details/78475414
  * @note     https://blog.csdn.net/kk55guang2/article/details/78490069
  * @note     https://wenku.baidu.com/view/84e5eb271a37f111f0855b2d.html
  *
  * @see      GetOSTU(Image_Use);//大津法阈值
  *
  * @date     2019/6/25 星期二
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
	float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差; 
	int16_t MinValue, MaxValue; 
	uint8_t Threshold = 0;
	uint8_t HistoGram[256];              //  
	
	for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图 
	
	for (j = 0; j < LCDH; j++) 
	{ 
		for (i = 0; i < LCDW; i++) 
		{ 
			HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
		} 
	} 
	
	for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
	for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值
	
	if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色    
	if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色
	
	for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  像素总数
	
	PixelIntegral = 0;
	for (j = MinValue; j <= MaxValue; j++)
	{
		PixelIntegral += HistoGram[j] * j;//灰度值总数
	}
	SigmaB = -1;
	for (j = MinValue; j < MaxValue; j++)
	{
		PixelBack = PixelBack + HistoGram[j];   //前景像素点数
		PixelFore = Amount - PixelBack;         //背景像素点数
		OmegaBack = (float)PixelBack / Amount;//前景像素百分比
		OmegaFore = (float)PixelFore / Amount;//背景像素百分比
		PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
		MicroBack = (float)PixelIntegralBack / PixelBack;   //前景灰度百分比
		MicroFore = (float)PixelIntegralFore / PixelFore;   //背景灰度百分比
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
		if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
		{
			SigmaB = Sigma;
			Threshold = j;
		}
	}
	return Threshold;                        //返回最佳阈值;
} 


