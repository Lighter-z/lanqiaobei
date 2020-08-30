#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<ds1302.c>
#include<ky.c>
#include<display.c>

/*
关注微信公众号：嵌入式基地
后台回复：蓝桥杯  获取资料
 */

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

void Timer0Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x28;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
}

void timer0()interrupt 1
{
	unsigned char i;
	cp++;
	if(cp >= 200)
	{
		cp = 0;
		cp1++;
		if(cp1 >= jiange)
		{
			wendu[i] = wen;
			i++;
			if(i >= 10)
			{
				i = 0;
				canshushezhi = 2;
			}
		}
		if(canshushezhi == 2)
		{
			if(shanshuo == 0)
				{
					shanshuo = 1;
					P2 = 0x80;
					P0 = 0xfe;
				}
				else if(shanshuo == 1)
				{
					shanshuo = 0;
					P2 = 0x80;
					P0 = 0xff;
				}
		}
	}
}

void Timer1Init(void)		//5毫秒@11.0592MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0x28;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA = 1;
	ET1 = 1;
}

void tm1_isr() interrupt 3 using 1
{
    cp2++;
	if((cp2 >= 200) && (kaishi == 1))
	{
		cp2 = 0;
		suoyin++;
		if(suoyin >= 10)
		{
			suoyin = 0;
		}
	}
}

void main()
{
	banzi_init();
	Timer0Init();
	Timer1Init();
	DS1302_init();
	while(1)
	{
		DS1302_Read();
		wen = DS18B20_Get();
		sec = shijian[0];
		min = shijian[1];
		hour = shijian[2];
		keyscan();
		display();
		xianshi();
	}
}