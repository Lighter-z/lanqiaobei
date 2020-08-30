#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<ds1302.c>
#include<key.c>
#include<display.c>

void banzi_init() //板子初始化
{
	P2 = 0xa0;
	P0 = 0x00;//关闭蜂鸣器，继电器
	
	P2 = 0x80;
	P0 = 0xff;//关闭LED
	
	P2 = 0xc0;
	P0 = 0xff;//关闭数码管段选
	P2 = 0xff;
	P0 = 0xff;//关闭数码管位选
}

void xianshi()
{
	P2 = 0xc0;
	P0 = 0x01;
	P2 = 0xff;
	P0 = seven_seg[yi];
	Delay1ms();//显示第一个数码管
	
	P2 = 0xc0;
	P0 = 0x02;
	P2 = 0xff;
	P0 = seven_seg[er];
	Delay1ms();//显示第二个数码管
	
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
	Delay1ms();//消影
}

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

void timer0()interrupt 1
{
	cp++;
	if(cp >= 200)
	{
		cp = 0;
		if(naozhongkai == 1)
		{
			cp2++;
			if(cp2 >= 25)//5s
			{
				cp2 = 0;
				naozhongkai = 0;//关闭闹钟标志位
			}
			if(shanshuo == 0)//L1亮   闪烁
			{
				P2 = 0x80;
				P0 = 0xfe;
				shanshuo = 1;
			}
			else if(shanshuo == 1)//L1灭  闪烁
			{
				shanshuo = 0;
				P2 = 0x80;
				P0 = 0xff;
			}
		}
		else if(naozhongkai == 0)//关闭LED
		{
			P2 = 0x80;
			P0 = 0xff;
		}
	}
}

void main()
{
	banzi_init();
	DS1302_init();//ds1302初始化
	Timer0Init();
	while(1)
	{
		wendu = DS18B20_get();
		DS1302_Read();
		sec = shijian[0];
		min = shijian[1];
		hour = shijian[2];
		keyscan();
		display();
		xianshi();
	}
}