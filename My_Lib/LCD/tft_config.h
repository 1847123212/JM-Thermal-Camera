
#ifndef __TFT_CONFIG_H
#define __TFT_CONFIG_H


//-------------------------��Ļ������������--------------------------------------//
#define LCD_X_SIZE	        240
#define LCD_Y_SIZE	        320

/////////////////////////////////////�û�������///////////////////////////////////	 
//֧�ֺ��������ٶ����л�
#define USE_HORIZONTAL  		0	//�����Ƿ�ʹ�ú��� 		0,��ʹ��.1,ʹ��.

#if USE_HORIZONTAL    //��������˺��� 
#define X_MAX_PIXEL	        LCD_Y_SIZE
#define Y_MAX_PIXEL	        LCD_X_SIZE
#else
#define X_MAX_PIXEL	        LCD_X_SIZE
#define Y_MAX_PIXEL	        LCD_Y_SIZE
#endif


#endif

