#include "lcd.h"
#include "ALL_Includes.h"
#include "16x8.h"

//TFT�ܽų�ʼ��
void LCD_GPIO_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

		//����FSmc��16λ���������Ϊ�����������
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE , ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                   GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;

  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

		//����IO�ĸ���
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 		 //�����������   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						 
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//(RS)
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 		 //�����������   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);  
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);	
	   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//(CS) 
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 		 //�����������   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);

       // TFT_RST 
       GPIO_InitStructure.GPIO_Pin =  TFT_RST_Pin;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  	GPIO_Init(TFT_RST_PORT, &GPIO_InitStructure);

	// TFT BackLight
	GPIO_InitStructure.GPIO_Pin = TFT_BLK_Pin;
  	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  	GPIO_Init(TFT_BLK_PORT, &GPIO_InitStructure);
		
	TFT_BackLight_Open();  // open back light
}

void TFT_FSMCConf(void)
{
  	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;

  	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
  	p.FSMC_AddressSetupTime = 5;
  	p.FSMC_AddressHoldTime = 0;
  	p.FSMC_DataSetupTime = 9;
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_A;
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

//================================================================================================
//	ʵ�ֹ��ܣ�	LCD ��ʼ��
//	���������	��
//================================================================================================
void LCD_init(void)
{
//	u16 DeviceCode=0;

	LCD_GPIO_Init();//���ų�ʼ��
	TFT_FSMCConf();
	LCD_Reset();//TFT��λ
/*
	LLCD_WRITE_CMD(0XD3);				   
	LCD_RD_DATA(); 			//dummy read 	
	LCD_RD_DATA();   	    //����0X00
	DeviceCode=LCD_RD_DATA()&0XBF;//�������0XD3,ʵ����0X93�Ŷ�.ǿ��ȥ����6λ  
	DeviceCode<<=8;
	DeviceCode|=LCD_RD_DATA();	   
	if(DeviceCode==0X9341)
	{*/
	//************* Start Initial Sequence **********//
	LLCD_WRITE_CMD(0xCF);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0xC1);
	LLCD_WRITE_DATA(0x30);
	
	LLCD_WRITE_CMD(0xED);
	LLCD_WRITE_DATA(0x64);
	LLCD_WRITE_DATA(0x03);
	LLCD_WRITE_DATA(0x12);
	LLCD_WRITE_DATA(0x81);
	
	LLCD_WRITE_CMD(0xE8);
	LLCD_WRITE_DATA(0x85);
	LLCD_WRITE_DATA(0x01);
	LLCD_WRITE_DATA(0x7A);
	
	LLCD_WRITE_CMD(0xCB);
	LLCD_WRITE_DATA(0x39);
	LLCD_WRITE_DATA(0x2C);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x34);
	LLCD_WRITE_DATA(0x02);
	
	LLCD_WRITE_CMD(0xF7);
	LLCD_WRITE_DATA(0x20);
	
	LLCD_WRITE_CMD(0xEA);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x00);
	
	LLCD_WRITE_CMD(0xC0); //Power control
	LLCD_WRITE_DATA(0x1B);   //VRH[5:0] 
	
	LLCD_WRITE_CMD(0xC1); //Power control
	LLCD_WRITE_DATA(0x01); //SAP[2:0];BT[3:0]

	LLCD_WRITE_CMD(0xC5); //VCM control
	LLCD_WRITE_DATA(0x30);
	LLCD_WRITE_DATA(0x30);
	
	LLCD_WRITE_CMD(0xC7); //VCM control2
	LLCD_WRITE_DATA(0xB7);
	
	LLCD_WRITE_CMD(0x36); // Memory Access Control
//	LLCD_WRITE_DATA(0x48);//���ҵ���,���ϵ���,
//	LLCD_WRITE_DATA(0x68);//���ϵ���,���ҵ���
	LLCD_WRITE_DATA(0x08);//������,���ϵ���,
//	LLCD_WRITE_DATA(0x28);//���ϵ���,������,

	LLCD_WRITE_CMD(0x3A); // Memory Access Control
	LLCD_WRITE_DATA(0x55);
	
	LLCD_WRITE_CMD(0xB1);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x1A);
	
	LLCD_WRITE_CMD(0xB6); // Display Function Control
	LLCD_WRITE_DATA(0x0A);
	LLCD_WRITE_DATA(0xA2);
	
	LLCD_WRITE_CMD(0xF2); // 3Gamma Function Disable
	LLCD_WRITE_DATA(0x00);
	
	LLCD_WRITE_CMD(0x26); //Gamma curve selected
	LLCD_WRITE_DATA(0x01);
	
	LLCD_WRITE_CMD(0xE0); //Set Gamma
	LLCD_WRITE_DATA(0x0F); 
	LLCD_WRITE_DATA(0x2A); 
	LLCD_WRITE_DATA(0x28); 
	LLCD_WRITE_DATA(0x08); 
	LLCD_WRITE_DATA(0x0E); 
	LLCD_WRITE_DATA(0x08); 
	LLCD_WRITE_DATA(0x54); 
	LLCD_WRITE_DATA(0XA9); 
	LLCD_WRITE_DATA(0x43); 
	LLCD_WRITE_DATA(0x0A); 
	LLCD_WRITE_DATA(0x0F); 
	LLCD_WRITE_DATA(0x00); 
	LLCD_WRITE_DATA(0x00); 
	LLCD_WRITE_DATA(0x00); 
	LLCD_WRITE_DATA(0x00); 	

	LLCD_WRITE_CMD(0XE1); //Set Gamma
	LLCD_WRITE_DATA(0x00); 
	LLCD_WRITE_DATA(0x15); 
	LLCD_WRITE_DATA(0x17); 
	LLCD_WRITE_DATA(0x07); 
	LLCD_WRITE_DATA(0x11); 
	LLCD_WRITE_DATA(0x06); 
	LLCD_WRITE_DATA(0x2B); 
	LLCD_WRITE_DATA(0x56); 
	LLCD_WRITE_DATA(0x3C); 
	LLCD_WRITE_DATA(0x05); 
	LLCD_WRITE_DATA(0x10); 
	LLCD_WRITE_DATA(0x0F); 
	LLCD_WRITE_DATA(0x3F); 
	LLCD_WRITE_DATA(0x3F); 
	LLCD_WRITE_DATA(0x0F); 
	
	LLCD_WRITE_CMD(0x2B); 
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x01);
	LLCD_WRITE_DATA(0x3f);
	LLCD_WRITE_CMD(0x2A); 
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0x00);
	LLCD_WRITE_DATA(0xef);

	LLCD_WRITE_CMD(0x11); // Sleep out
	delay_ms(120);
	LLCD_WRITE_CMD(0x29); // Display on
	LLCD_WRITE_CMD(0x2c);
//	}
	LCD_Fill(0,0,LCD_WidthX-1,LCD_WidthY-1,BLACK);
}

//================================================================================================
//	ʵ�ֹ��ܣ�	���ô���
//	���������	x0,y0,x1,y1    x�Ὺʼ��y�Ὺʼ��x�������y�����
//================================================================================================
void LCD_setwindow(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1)
{
	LLCD_WRITE_CMD(0x2a);   
	LLCD_WRITE_DATA(x0>>8);
	LLCD_WRITE_DATA(x0&0xff);
	LLCD_WRITE_DATA(x1>>8);
	LLCD_WRITE_DATA(x1&0xff);

	LLCD_WRITE_CMD(0x2b);   
	LLCD_WRITE_DATA(y0>>8);
	LLCD_WRITE_DATA(y0&0xff);
	LLCD_WRITE_DATA(y1>>8);
	LLCD_WRITE_DATA(y1&0xff);

	LLCD_WRITE_CMD(0x2C);		
}

//================================================================================================
//	ʵ�ֹ��ܣ�	��λ
//	���������	LCD ��λ
//================================================================================================
void LCD_Reset(void)
{
	TFT_RST_H;
	delay_ms(150);
	TFT_RST_L;
	delay_ms(150);
	TFT_RST_H;
	delay_ms(150);
}

//д�Ĵ���
//LCD_Reg:�Ĵ������
//LCD_RegValue:Ҫд���ֵ
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LLCD_WRITE_CMD(LCD_Reg);  
	LLCD_WRITE_DATA(LCD_RegValue);	    		 
}

//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{										   
	return *(volatile u16 *) (Bank1_LCD_D);  
}

//LCD������ʾ
void LCD_DisplayOn(void)
{	
	LLCD_WRITE_CMD(0X29);	//������ʾ
}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
	LLCD_WRITE_CMD(0X28);	//�ر���ʾ
}  

//���ù��λ��
//Xpos:������
//Ypos:������
__inline void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
		LLCD_WRITE_CMD(0x2a);   
		LLCD_WRITE_DATA(Xpos>>8);
		LLCD_WRITE_DATA(Xpos&0xff);
		LLCD_WRITE_DATA(Xpos>>8);
		LLCD_WRITE_DATA(Xpos&0xff);
		
		LLCD_WRITE_CMD(0x2b);   
		LLCD_WRITE_DATA(Ypos>>8);
		LLCD_WRITE_DATA(Ypos&0xff);
		LLCD_WRITE_DATA(Ypos>>8);
		LLCD_WRITE_DATA(Ypos&0xff);
}

//����
//x:0~239
//y:0~319
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y, u16 color)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
	LLCD_WRITE_CMD(0x2C);//ILI9341����0X2C��ʼ��
	LLCD_WRITE_DATA(color); 
}

//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{   
    unsigned int i,j; 

 	LCD_setwindow(sx,sy,ex,ey);

	for(i=sy;i<=ey;i++)
	{
	    for(j=sx;j<=ex;j++) 
		{  
			LLCD_WRITE_DATA(color);				
		}	
	}

}

/*****************
��ʾ���֡�
num��-999~999
*****************/
void LCD_ShowNum(unsigned int x, unsigned int y,int num, unsigned int color,unsigned int b_color)
{
	if(num<0)
	{
		num = -num;
		LCD_DrawLine(x,y+7,x+3,y+7,color);
		x=x+4;
	}
	
  if(num>=100)
	{
		LCD_Showchar(x, y,num/100+'0', color,b_color);
		LCD_Showchar(x+8, y,(num/10)%10+'0', color,b_color);
		LCD_Showchar(x+16, y,num%10+'0', color,b_color);
	}
	else if(num>=10)
	{
		LCD_Showchar(x, y,num/10+'0', color,b_color);
		LCD_Showchar(x+8, y,num%10+'0', color,b_color);
	}
	else
		LCD_Showchar(x, y,num+'0', color,b_color);
}

//================================================================================================
//	ʵ�ֹ��ܣ�	��ʾ�ַ���
//	���������	
//================================================================================================
void LCD_ShowString(unsigned int x, unsigned int y,const char *s, unsigned int color,unsigned int b_color)
{  
	while(*s!='\0')
	{
		LCD_Showchar(x, y,*s, color,b_color);
		x=x+8;
		s++;
	}
}	

void LCD_Showchar(unsigned int x, unsigned int y,unsigned char c, unsigned int color,unsigned int b_color)
{  
	unsigned int  s_x ,s_y, temp ;
  	unsigned int j;
  	c -= 32;
	if(x>LCD_WidthX-8||y>LCD_WidthY-16)return;	
	LCD_setwindow(x,y,x+7,y+15);
	for( s_y=0 ; s_y<16 ; s_y++ )
	{
		if(y+s_y<LCD_WidthY)
		{
		   j=c;
		   j=j*16+s_y;
		   temp=font16x8[j];
		   for( s_x=0 ; s_x < 8 ; s_x++ )
		   {
		   		if(s_x+x<LCD_WidthX)
				{
					 if((temp&(0x80>>(s_x))) == (0x80>>(s_x))  )
				   		LLCD_WRITE_DATA(color);
			     else
				     	LLCD_WRITE_DATA(b_color);
				}
		   }
		}
	}
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//��ʾ���ַ���26x16����
void LCD_N(int x,int y,unsigned char num,unsigned int color,unsigned int b_color)
{
    unsigned char temp;
    int pos,t;
//	int x0=x;
	//unsigned int  s_x ,s_y;
    
    if(x>LCD_WidthX-16||y>LCD_WidthY-26)return;	
	
	LCD_setwindow(x,y,x+15,y+25);	
	for(pos=0;pos<52;pos++)
	{ 
			temp=Num1626[num*52+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x80)
							LLCD_WRITE_DATA(color);
						else					
							LLCD_WRITE_DATA(b_color);
						temp<<=1; 
		    }
	}	  	   	 	  
} 




