
#ifndef __GLOBAL_DEF_H
#define __GLOBAL_DEF_H

#include "stm32f4xx_conf.h"

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "reglib.h"

#define  DEBUG_EN  0

#if  DEBUG_EN
#define os_printf(fmt, ...)  printf(fmt, ##__VA_ARGS__)
#else
#define  os_printf(...)
#endif


// debug output enable : 0: disable;  1: enable
#define    FAT_DEBUG_EN   0    // fatfs debug output






#define OS_PER_TICK_MS   (10)         // ÿ��tick��ʱ��: 10ms


#define  SD_DISK_EN            0   // SD ���洢ʹ��
#define  FLASH_DISK_EN    1   // SPI FLASH DISK �洢ʹ��(1)
#define  ROM_DISK_EN       0  // ROM FLASH DISK �洢ʹ��

#define  MAX_LUN         0    // MAX_LUN + 1 �����ƶ����� :   SD�� + SPI FLASH

typedef enum
{
   FLASH_DISK = 0,
   SD_DISK       = 1, 
   ROM_DISK    = 2,
}DISK_ENUM;

typedef enum
{
   APP_SUCCESS = 0,
   APP_FAILED = 1,
   APP_NULL = 0xFF,
}E_RESULT;


#define FREQ_512KHz       (512000L)
#define FREQ_1MHz        (1000000L)
#define FREQ_2MHz        (2000000L)
#define FREQ_8MHz        (8000000L)
#define FREQ_16MHz      (16000000L)
#define FREQ_24MHz      (24000000L)
#define FREQ_48MHz      (48000000L)
#define FREQ_72MHz      (72000000L)


#define CPU_CLOCK       FREQ_72MHz  // MCU ʱ��


/************************************************************************************************************************************************************
 spi flash ����������СΪ4KB, ������������Ϊ512, ���� 2MB
 ���� 260KB �ռ� Ϊ Ӧ�ó����ϵͳ���������洢��
| <---sector 0 - sector 63--->  | <-----------sector 64 ~ 127-----------> | <--sector 128 ----- >  |<-sector 65 ~ sector 511-------->   |
| <-----256 KB -----------> | <--------256 KB--------------------> | <------4KB------->|---------�ļ�ϵͳ---------- -|
| APP1 ������(�³���)     |  APP2 ������(��һ���汾����)    |   ϵͳ������        |---------�ļ�ϵͳ----------- |  
|-------------------------- 516 KB (129����������)    --------------------------------|--ʣ��Ϊ FatFs �ļ�ϵͳ��---|
*************************************************************************************************************************************************************/
// APP1 BIN ���ݵ�ַ: 256 KB, sector 0 - sector 63
#define FLASH_APP1_START_SECTOR  ((uint32_t)0L)

// APP2 BIN ���ݵ�ַ: 256 KB, sector 64 - sector 127
#define FLASH_APP2_START_SECTOR  ((uint32_t)64L)

// ϵͳ����������ʼ������ַ, sector 128 ����, ��С 4KB
#define  FLASH_SYS_ENV_START_SECTOR    ((uint32_t)128L) 

// ����������Ϣ��ʼ��ַ
//#define  FLASH_FONT_START_SECTOR (FLASH_SYS_ENV_START_SECTOR + 1)  //(FLASH_SYS_ENV_START_SECTOR + 1)

// �ļ�ϵͳ��ʼ��ַ
#define  FLASH_FATFS_START_SECTOR    (FLASH_SYS_ENV_START_SECTOR + 1)   //(FLASH_FONT_START_SECTOR + 128)










#define WEAK_ATTR   __attribute__((weak))

#define READ_REG_32_BIT(reg,  b)      ((uint32_t)((reg)&((uint32_t)b)))      //b����Ϊ����, regΪ32 bit �Ĵ���
#define CLEAR_REG_32_BIT(reg, b)      ((reg)&=(uint32_t)(~((uint32_t)b)))   //b����Ϊ����, regΪ32 bit �Ĵ���
#define SET_REG_32_BIT(reg,   b)      ((reg)|=(uint32_t)(b))                  //b����Ϊ����, regΪ32 bit �Ĵ���

#define READ_REG_8_BIT(reg,b)     ((uint8_t)((reg)&((uint8_t)b)))           //b����Ϊ8bit����, regΪ�Ĵ���
#define CLEAR_REG_8_BIT(reg,b)    ((reg)&=(uint8_t)(~((uint8_t)b)))        //b����Ϊ8bit����, regΪ�Ĵ���
#define SET_REG_8_BIT(reg,b)      ((reg)|=(uint8_t)(b))                      //b����Ϊ8bit����, regΪ�Ĵ���


#define ALIGN_4  __align(4)

#define  ALIGN4(len)   ( (sizeof(len) + sizeof(int) - 1) &  ~(sizeof(int) - 1) ) 

// ��4�ֽڶ����ĳ���
#define  ALIGN4_SIZE(len)   ( ( len & 0xFFFFFFFC) + ((len % 4) ?  4 : 0))

// ��4�ֽڶ���ʱȱ�ٵ��ֽڳ���: 0 - 3
#define ALIGN4_LEFT(len)     ((len % 4) ? (4 - len % 4) : 0)


#endif

