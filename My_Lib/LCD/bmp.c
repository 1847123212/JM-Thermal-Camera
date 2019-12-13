
#include "bmp.h"
#include "tft_commands.h"
#include "LCD.h"
#include "os_global.h"
#include "ff.h"
#include "fatfs_demo.h"
#include "CCM.h"
extern  FIL flashFIL;


u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0, g=0, b=0;
	   
	LCD_SetCursor(x,y);	    
	LLCD_WRITE_CMD(0X2E);  

       r = LCD_RD_DATA();
 	r = LCD_RD_DATA();    //ʵ��������ɫ
  
	b = LCD_RD_DATA(); 
	g = r & 0XFF;	
	g <<= 8;
	
       return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));
}

static uint16_t bmp_cnt;

u8 bmp_encode(u16 x0, u16 y0, u16 x1, u16 y1)
{				
	u16 bmpheadsize;			// bmpͷ��С	   	
 	BITMAPINFO hbmp;			// bmpͷ	 
	FRESULT res;
       u32 y_idx, x_idx;
       u32  buf_idx = 0;
       u16 * bmp_buf;
       UINT bw = 0;
 	char tmp_name[20]; 
 	u16  width = x1 -x0 + 1;
 	u16 height = y1 - y0 + 1;
       u16 h = height;

       bmp_buf = (u16 *)ccm_buf;
	bmpheadsize = sizeof(hbmp);  // �õ�bmp�ļ�ͷ�Ĵ�С   
	os_memset((u8*)&hbmp,0,sizeof(hbmp)); // ��������뵽���ڴ�.	    
	
	hbmp.bmiHeader.biSize=sizeof(BITMAPINFOHEADER); // ��Ϣͷ��С
	hbmp.bmiHeader.biWidth   = width;	       // bmp�Ŀ��
	hbmp.bmiHeader.biHeight = height; 	// bmp�ĸ߶�
	hbmp.bmiHeader.biPlanes  = 1;	 		// ��Ϊ1
	hbmp.bmiHeader.biBitCount = 16;	 	// bmpΪ16λɫbmp
	hbmp.bmiHeader.biCompression = BI_BITFIELDS; // ÿ�����صı�����ָ�������������
 	hbmp.bmiHeader.biSizeImage = height  * width * (hbmp.bmiHeader.biBitCount / 8);  // bmp��������С
 				   
	hbmp.bmfHeader.bfType=((u16)'M'<<8)+'B';//BM��ʽ��־
	hbmp.bmfHeader.bfSize      = bmpheadsize+hbmp.bmiHeader.biSizeImage;  // ����bmp�Ĵ�С
   	hbmp.bmfHeader.bfOffBits= bmpheadsize;//����������ƫ��

	hbmp.RGB_MASK[0]=0X00F800;	 		//��ɫ����
	hbmp.RGB_MASK[1]=0X0007E0;	 		//��ɫ����
	hbmp.RGB_MASK[2]=0X00001F;	 		//��ɫ����

       os_snprintf((char*)tmp_name, sizeof(tmp_name), "%d.bmp",  bmp_cnt++);
       res = FILE_Open( &flashFIL,  "0:/image",  tmp_name);
       if(res){  os_printf("snap failed: res = %d\r\n",  res);  return 1;   }
       
	res=f_write(&flashFIL, (u8*)&hbmp, bmpheadsize, &bw); // д��BMP�ײ�  

       h = height;
       for(y_idx = y0 + h - 1;  h; y_idx--)
        //for(y_idx = y0; y_idx < h; y_idx++)
       {
	       for(x_idx = x0;  x_idx < width; x_idx++)
		{
			bmp_buf[buf_idx] = LCD_ReadPoint(x_idx, y_idx);
			buf_idx++;
			
                     if((buf_idx * 2) >= sizeof(ccm_buf))
                     {
                             os_printf("write bmp: buf_idx *2 = %ld, %ld \r\n",  buf_idx * 2,   os_get_tick());
                             res = f_write(&flashFIL,  bmp_buf,  buf_idx * 2,  &bw);
                             buf_idx = 0;
                     }
		}
		h--;
       }

       if(buf_idx)
       {
               os_printf("write last, write_cnt = %ld, %ld \r\n", buf_idx * 2,  os_get_tick());
               res = f_write(&flashFIL,  bmp_buf,  buf_idx * 2,  &bw);
       }
       res = f_close(&flashFIL); 

       
	return (u8)res;
}

