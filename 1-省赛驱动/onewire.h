#ifndef _ONEWIRE_H
#define _ONEWIRE_H

#include "reg52.h"

#define OW_SKIP_ROM 0xcc
#define DS18B20_CONVERT 0x44
#define DS18B20_READ 0xbe

//IC引脚定义
sbit DQ = P1^4;

//函数声明
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
bit Init_DS18B20(void);
unsigned char Read_DS18B20(void);

#endif