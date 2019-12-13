#include "usbd_msc_mem.h"
#include "usb_conf.h"
#include "GlobalDef.h" 
#if FLASH_DISK_EN
#include "spi_flash_interface.h"
#endif

#if ROM_DISK_EN
#include "rom_flash_interface.h"
#endif


#if SD_DISK_EN
#include "sd_card_interface.h"
#endif



////////////////////////////�Լ������һ�����USB״̬�ļĴ���///////////////////
//bit0:��ʾ����������SD��д������
//bit1:��ʾ��������SD����������
//bit2:SD��д���ݴ����־λ
//bit3:SD�������ݴ����־λ
//bit4:1,��ʾ��������ѯ����(�������ӻ�������)
vu8 USB_STATUS_REG = 0;



/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata[] = {   // 36
   
	/* LUN 0 */ 
	0x00,		
	0x80,		
	0x02,		
	0x02,
	(USBD_STD_INQUIRY_LENGTH - 5),
	0x00,
	0x00,	
	0x00,
    /* Vendor Identification */
    'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
    /* Product Identification */
    'S', 'P', 'I', 'F', 'L', 'A', 'S', 'H', ' ', /* Product : 16 Bytes */
    ' ','D', 'i', 's', 'k', ' ',
    /* Product Revision Level */	
    '1', '.', '0', ' ',							/* Version : 4 Bytes */	
	
	/* LUN 1 */
	0x00,
	0x80,		
	0x02,		
	0x02,
	(USBD_STD_INQUIRY_LENGTH - 5),
	0x00,
	0x00,	
	0x00,
	/* Vendor Identification */
	'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
	/* Product Identification */				
	'S', 'D', ' ', 'F', 'l', 'a', 's', 'h', ' ',  /* Product : 16 Bytes */
	'D', 'i', 's', 'k', ' ', ' ',  
    /* Product Revision Level */
	'1', '.', '0' ,' ',                      	/* Version : 4 Bytes */
}; 
int8_t STORAGE_Init (uint8_t lun);
int8_t STORAGE_GetCapacity (uint8_t lun,uint32_t *block_num,uint32_t *block_size);
int8_t  STORAGE_IsReady (uint8_t lun);
int8_t  STORAGE_IsWriteProtected (uint8_t lun);
int8_t STORAGE_Read (uint8_t lun,uint8_t *buf, uint32_t blk_addr,uint16_t blk_len);
int8_t STORAGE_Write (uint8_t lun,uint8_t *buf, uint32_t blk_addr,uint16_t blk_len);
int8_t STORAGE_GetMaxLun (void);

//USB Device �û��ص������ӿ�
USBD_STORAGE_cb_TypeDef USBD_MICRO_SDIO_fops =
{
	STORAGE_Init,
	STORAGE_GetCapacity,
	STORAGE_IsReady,
	STORAGE_IsWriteProtected,
	STORAGE_Read,
	STORAGE_Write,
	STORAGE_GetMaxLun,
	(int8_t *)STORAGE_Inquirydata,
};
USBD_STORAGE_cb_TypeDef  *USBD_STORAGE_fops = &USBD_MICRO_SDIO_fops;

//��ʼ���洢�豸
//lun:�߼���Ԫ���,0,SD��;1,SPI FLASH
//����ֵ:0,�ɹ�;
//    ����,�������
int8_t STORAGE_Init (uint8_t lun)
{
       int8_t status  = 0;
       
	#if FLASH_DISK_EN
        status = (int8_t)flash_initialize();
	#endif

	#if SD_DISK_EN
        status = (int8_t)sd_initialize();
	#endif

	#if ROM_DISK_EN
        status = rom_flash_initialize();
	#endif

	return status;
} 

//��ȡ�洢�豸�������Ϳ��С
//lun:�߼���Ԫ���: 0 -2
//block_num:������(������)
//block_size:���С(������С)
//����ֵ:0,�ɹ�;
//    ����,�������
int8_t STORAGE_GetCapacity (uint8_t lun, uint32_t *block_num, uint32_t *block_size)
{     
	switch(lun)
     {
          #if FLASH_DISK_EN
          case FLASH_DISK:  // SPI FLASH
	  {
                *block_num = SPI_FLASH_SECTOR_COUNT; 
                *block_size  = SPI_FLASH_SECTOR_SIZE; 
	  }break;
	  #endif

	  #if SD_DISK_EN
	  case SD_DISK:  // SD ��
	  {
	          *block_num = SDCardInfo.CardCapacity / SDCardInfo.CardBlockSize;
                 *block_size  = SDCardInfo.CardBlockSize;
	  }break;
	  #endif

	  #if ROM_DISK_EN
	  case ROM_DISK:   // ROM FLASH
	  {
		 *block_num = ROM_FLASH_SIZE / ROM_FLASH_PAGE_SIZE; 
               *block_size  =  ROM_FLASH_PAGE_SIZE; 
	  }break;
	  #endif
	  
	  default:
	  	return 1;
     }
     return 0;
} 

//�鿴�洢�豸�Ƿ����
//lun:�߼���Ԫ���,0,SD��;1,SPI FLASH
//����ֵ:0,����;
//    ����,δ����
int8_t  STORAGE_IsReady (uint8_t lun)
{ 
	USB_STATUS_REG |= 0X10;//�����ѯ
	return 0;
} 

//�鿴�洢�豸�Ƿ�д����
//lun:�߼���Ԫ���,0,SD��;1,SPI FLASH
//����ֵ:0,û��д����;
//    ����,д����(ֻ��)
int8_t  STORAGE_IsWriteProtected (uint8_t lun)
{
	return  0;
} 

//�Ӵ洢�豸��ȡ����
//lun:�߼���Ԫ���
//buf:���ݴ洢���׵�ַָ��
//sector_addr:Ҫ��ȡ�ĵ�ַ(������ַ)
//sector_cnt:Ҫ��ȡ�Ŀ���(������) 
//����ֵ:0,�ɹ�;
//    ����,������� 
int8_t STORAGE_Read (uint8_t lun, uint8_t * Readbuff,uint32_t  sector_addr, uint16_t sector_cnt)
{
           int8_t res = 0;

          USB_STATUS_REG |= 0X02; // mask reading
          switch (lun)
         {
#if FLASH_DISK_EN
                 case FLASH_DISK:
           	  {
           		res = flash_mal_read(lun, sector_addr << 9, (uint32_t *)Readbuff,  sector_cnt << 9);
           	   }break;
#endif
           
#if SD_DISK_EN
                 case SD_DISK:
           	  {
           	           res = SD_ReadDisk(lun, Readbuff,  sector_addr,  sector_cnt);
           	   }break;
#endif
           
#if ROM_DISK_EN
           	  case ROM_DISK:
             	 {
           		res = rom_flash_mal_read(lun, sector_addr << 9, (uint32_t *)Readbuff,  sector_cnt << 9);
               }break;
#endif
           	
               default:
                     return 1;
          }
          if(res)
          {
                     if(res)USB_STATUS_REG |= 0X08;  // read error
                     return 1;
          }
          return 0;
}

//��洢�豸д����
//lun:�߼���Ԫ���,0,SD��;1,SPI FLASH
//buf:���ݴ洢���׵�ַָ��
//blk_addr:Ҫд��ĵ�ַ(������ַ)
//blk_len:Ҫд��Ŀ���(������) 
//����ֵ:0,�ɹ�;
//    ����,������� 
int8_t STORAGE_Write (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len) 
{
       int8_t res = 0; 

       USB_STATUS_REG |= 0X01; // mask on writing
	switch(lun)  //����,����lun��ֵȷ����Ҫ�����Ĵ���
	{
	       #if FLASH_DISK_EN
	       case FLASH_DISK:  //����0Ϊ SPI FLASH��
		{
		        res = (int8_t)flash_mal_write(lun, blk_addr << 9,  (uint32_t *)buf,  blk_len << 9);
		}break;
		#endif

		#if SD_DISK_EN
		case SD_DISK:  //����1ΪSD��	
		{
		         res = (int8_t)SD_WriteDisk(lun, buf,  blk_addr, blk_len);
		}break;
		#endif

		#if ROM_DISK_EN
		case ROM_DISK:  
	      {
			 res = (int8_t)rom_flash_mal_write(lun,  blk_addr << 9,  (uint32_t *)buf,  blk_len << 9);
	       }break;
	      #endif
		
		default:
			return 1;
	}
	if(res)
	{
	          USB_STATUS_REG |= 0X04; // mask write error
	          return 1;
	}
	return 0;
}

//��ȡ֧�ֵ�����߼���Ԫ����
//����ֵ:֧�ֵ��߼���Ԫ����-1
int8_t STORAGE_GetMaxLun (void)
{
	return MAX_LUN;
}
























