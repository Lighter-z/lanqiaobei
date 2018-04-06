#ifndef __DS1302_H
#define __DS1302_H

void Write_Ds1302_Byte(unsigned  char temp);
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void DS1302_init();
void DS1302_Read();
#endif
