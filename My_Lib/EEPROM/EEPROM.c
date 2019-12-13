#include "EEPROM.h"
#include "ALL_Includes.h"

/******************************
EEPROM �ڴ�滮����Ե�ַ
0--- 0xD5A5//�����״�д����
1--- TempH  //����
2--- TempL //����
3--- emissivity  //������

******************************/

/*******************************
EEP_Addr: ��Ե�ַ
EEP_Buf�� ����
EEP_Length: ���ݳ���(16bit Ϊ1������)
*******************************/
void EEP_Wirte(u16 *EEP_Buf, u16 EEP_Length)
{
	 u16 EEP_i;

	 FLASH_Unlock();	

	 FLASH_EraseSector(FLASH_Sector_7, VoltageRange_3);//���

	 for(EEP_i = 0; EEP_i < EEP_Length; EEP_i++)//д��EEP
	 {
				FLASH_ProgramHalfWord(EEP_BaseAddr +(EEP_i << 1), EEP_Buf[EEP_i]);
	 }

	 FLASH_Lock();
}

u16 EEP_ReadWord(u32 EEP_Addr)
{
	 return *(__IO uint16_t *)(EEP_BaseAddr + (EEP_Addr<<1));
}



void ReadDataFromEEP(u16 addr, u8 *data, u16 length)
{
	 u8 i;
	 u16 temp;

	 for(i = 0; i < length; i++)
	 {
		  temp = EEP_ReadWord(i+addr);
	  	  data[i] = (u8)temp;
	 }
}

