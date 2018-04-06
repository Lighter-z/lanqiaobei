#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<ds1302.c>
#include<iic.c>
#include<display.c>

void banzi_init()
{
	P2 = 0xa0;
	P0 = 0x00;
	
	P2 = 0x80;
	P0 = 0xff;
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
}

void xianshi()
{
	P2 = 0xc0;
	P0 = 0x01;
	P2 = 0xff;
	P0 = seven_seg[yi];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x02;
	P2 = 0xff;
	P0 = seven_seg[er];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x04;
	P2 = 0xff;
	P0 = seven_seg[san];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x08;
	P2 = 0xff;
	P0 = seven_seg[si];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x10;
	P2 = 0xff;
	P0 = seven_seg[wu];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x20;
	P2 = 0xff;
	P0 = seven_seg[liu];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x40;
	P2 = 0xff;
	P0 = seven_seg[qi];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0x80;
	P2 = 0xff;
	P0 = seven_seg[ba];
	Delay1ms();
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
	Delay1ms();
}

void main()
{
	banzi_init();
	DS1302_init();
	iic_write(0x00,12);
	while(1)
	{
		wendu = DS18B20_Get();
//		yi = wendu / 10;
//		er = wendu % 10;
//		san = (wenxiaoshu % 16) * 10 / 16;
		DS1302_Read();
//		sec = shijian[0];
//		min = shijian[1];
//		hour = shijian[2];
//		date = shijian[3];
//		month = shijian[4];
//		nian = shijian[6];
		AD = AD_Read(0x03);
		AD = AD * 0.39;
		yi = AD / 10;
		er = AD % 10;
		jieshou = iic_read(0x00);
		si = jieshou / 10;
		wu = jieshou % 10;
		//display();
		xianshi();
	}
}