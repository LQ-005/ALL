/*!
  * @file     LQ_12864.h
  *
  * @brief    OLED����
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.1  2019/12/06 �Ż�ע�� Doxygen
  *
  * @Software IAR8.32 or MDK5.28
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2019/11/11 ����һ
  */ 
#ifndef _LQOLED_H
#define _LQOLED_H
#include "stdint.h"

/*!
  * @brief    OLED��ʼ��
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ����޸Ĺܽ� ��Ҫ�޸ĳ�ʼ���Ĺܽ� 
  *
  * @see      LCD_Init();
  *
  * @date     2019/6/13 ������
  */
void LCD_Init(void);

/*!
  * @brief    OLEDȫ��
  *
  * @param    ��   
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Fill(); //OLEDȫ�� ���ڼ�⻵��
  *
  * @date     2019/6/13 ������
  */
void LCD_Fill(void);

/*!
  * @brief    OLED����
  *
  * @param    ��  
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_CLS(); //����
  *
  * @date     2019/6/13 ������
  */
void LCD_CLS(void);

/*!
  * @brief    ��һ����
  *
  * @param    x  : 0-127 
  * @param    y  : 0-63
  *
  * @return   ��
  *
  * @note     OLED�ǰ��ֽ���ʾ�� һ���ֽ�8λ������8���������ص㣬
  * @note     ���������� LCD_PutPixel(0,0); LCD_PutPixel(0,1); ֻ����ʾ��(0, 1) (0,0)���ڻ���(0,1)ʱ�����
  *
  * @see      LCD_PutPixel(0, 0); //��һ���� ���Ͻ�Ϊ0,0  ���½� 127,63
  *
  * @date     2019/6/13 ������
  */
void LCD_PutPixel(unsigned char x,unsigned char y);

/*!
  * @brief    ���8����
  *
  * @param    x  : 0-127
  * @param    y  : 0-63
  *
  * @return   ��
  *
  * @note     OLED�ǰ��ֽ���ʾ�� һ���ֽ�8λ������8���������ص㣬
  *
  * @see      LCD_ClrDot(0, 0); //���(0,0)-(0,7)8���� ���Ͻ�Ϊ0,0  ���½� 127,63
  *
  * @date     2019/6/13 ������
  */
void LCD_ClrDot(unsigned char x,unsigned char y);

/*!
  * @brief    ������
  *
  * @param    x1  : 0-127   ���Ͻ����꣨x1,y1��
  * @param    y1  : 0-63
  * @param    x2  : 0-127   ���½����꣨x2��y2��
  * @param    y2  : 0-63
  * @param    gif : �Ƿ�������Ч��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Rectangle(0, 0, 127,62,0);   //���ƾ���
  *
  * @date     2019/6/13 ������
  */
void LCD_Rectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char gif);

/*!
  * @brief    д��һ���׼ASCII�ַ���
  *
  * @param    x  : 0-127   
  * @param    y  : 0-7
  * @param    ch : Ҫ��ʾ���ַ���
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_P6x8Str(0,0,"OLED 3.");  //��ʾ�ַ���
  *
  * @date     2019/6/13 ������
  */
void LCD_P6x8Str(unsigned char x,unsigned char y, char ch[]);

/*!
  * @brief    д��һ���׼ASCII�ַ���
  *
  * @param    x  : 0-127   
  * @param    y  : 0-6
  * @param    ch : Ҫ��ʾ���ַ���
  *
  * @return   ��
  *
  * @note     һ���ַ���16  OLED�߶�64  
  *
  * @see      LCD_P8x16Str(0,0,"OLED 3.");  //��ʾ�ַ���
  *
  * @date     2019/6/13 ������
  */
void LCD_P8x16Str(unsigned char x,unsigned char y, char ch[]);

/*!
  * @brief    ��������ַ���
  *
  * @param    x  : 0-127   
  * @param    y  : 0-6
  * @param    ch : Ҫ��ʾ���ַ���
  *
  * @return   ��
  *
  * @note     һ���ַ���16  OLED�߶�64   �ֿ���Ҫ�Լ�����
  *
  * @see      LCD_P14x16Str(0,4,"��������");   //��ʾ����
  *
  * @date     2019/6/13 ������
  */
void LCD_P14x16Str(unsigned char x,unsigned char y, char ch[]);

/*!
  * @brief    ������ֺ��ַ�����ַ���
  *
  * @param    x  : 0-127   
  * @param    y  : 0-6
  * @param    ch : Ҫ��ʾ���ַ���
  *
  * @return   ��
  *
  * @note     һ���ַ���16  OLED�߶�64   �ֿ���Ҫ�Լ�����
  *
  * @see      LCD_Print(0,6,"�������� OLED.");  //��ʾ����+�ַ�
  *
  * @date     2019/6/13 ������
  */
void LCD_Print(unsigned char x, unsigned char y,  char ch[]);

/*!
  * @brief    ��ʾBMPͼƬ128��64
  *
  * @param    x  : 0-127   
  * @param    y  : 0-6
  * @param    ch : Ҫ��ʾ���ַ���
  *
  * @return   ��
  *
  * @note     ͼƬ��Ҫ�����ת��
  *
  * @see      
  *
  * @date     2019/6/13 ������
  */
void LCD_Show_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char * bmp);

/*!
  * @brief    ��ʾ����ͼƬ128��64
  *
  * @param    �� 
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Show_LQLogo();
  *
  * @date     2019/6/13 ������
  */
void LCD_Show_LQLogo(void);

/*!
  * @brief    ������ OV7725��ʾͼ��ʱ ���������������
  *
  * @param    �� 
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Show_Frame80();
  *
  * @date     2019/6/13 ������
  */
void LCD_Show_Frame80(void);

/*!
  * @brief    ������ MT9V034��ʾͼ��ʱ ���������������
  *
  * @param    �� 
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Show_Frame80();
  *
  * @date     2019/6/13 ������
  */
void LCD_Show_Frame94(void);

/**
  * @brief    OLED ��ֵ��ͼ����ʾ
  *
  * @param    high �� ��ʾͼ��߶�
  * @param    wide �� ��ʾͼ����
  * @param    Pixle�� ��ʾͼ�����ݵ�ַ
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      LCD_Road(LCDH, LCDW, (uint8_t *)Pixle);
  *
  * @date     2019/6/25 ���ڶ�
  */
void LCD_Road(uint16_t high, uint16_t wide, uint8_t *Pixle);

/*!
  * @brief    OLED����
  *
  * @param    cmd ������
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      �ڲ�����
  *
  * @date     2019/6/13 ������
  */
void LCD_WrCmd(unsigned char cmd);

/*!
  * @brief    OLED���õ�
  *
  * @param    x ������   
  * @param    y ������
  *
  * @return   ��
  *
  * @note     ��
  *
  * @see      �ڲ�����
  *
  * @date     2019/6/13 ������
  */
void LCD_Set_Pos(unsigned char x, unsigned char y);
	
/**
  * @brief    OLED ���Ժ���
  *
  * @param    ��
  *
  * @return   ��
  *
  * @note     ��
  *
  * @example  Test_OLED();
  *
  * @date     2019/6/25 ���ڶ�
  */
void Test_OLED(void);

#endif


