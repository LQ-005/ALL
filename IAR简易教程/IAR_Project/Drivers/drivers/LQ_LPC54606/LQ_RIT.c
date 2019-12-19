/*!
  * @file     LQ_RIT.c
  *
  * @brief    RIT��ʱ�������ļ�
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
#include "fsl_rit.h"
#include "LQ_RIT.h"


/*!
  * @brief    RIT��ʱ���жϳ�ʼ��
  *
  * @param    us  �� ��ʱʱ��
  *
  * @return   ��
  *
  * @note     48λ�Ķ�ʱ��  ������ 0xFFFFFFFFFFFF
  *
  * @see      RIT_InitConfig(5000); //5ms����һ��RIT�ж�
  * @see      ���ȼ����� ��ռ���ȼ�5  �����ȼ�0   ԽС���ȼ�Խ��  ��ռ���ȼ��ߵĿɴ����ռ���ȼ��͵��ж�
  * @see      NVIC_SetPriority(RIT_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5,0));
  * @see      EnableIRQ(RIT_IRQn);  //ʹ���ж�
  *
  * @date     2019/10/19 ������
  */
void RIT_InitConfig(uint32_t us)
{
    /* У׼ֵ  */
//    us += (us/500)+1;
    
    rit_config_t ritConfig;  
    
    RIT_GetDefaultConfig(&ritConfig); 
    
    RIT_Init(RIT, &ritConfig);        //RIT��ʼ��
    RIT_SetTimerCompare(RIT, USEC_TO_COUNT(us, CLOCK_GetFreq(kCLOCK_CoreSysClk)));
    RIT_SetCountAutoClear(RIT, true); //���ڼ���
    RIT_ClearCounter(RIT, true);      //����    
    RIT_StartTimer(RIT);               //ʹ��  
    
}
