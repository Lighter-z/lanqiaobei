#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<display.c>
#include<key.c>

/*
��ע΢�Ź��ںţ�Ƕ��ʽ����
��̨�ظ������ű�  ��ȡ����
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

void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA = 1;
	ET0 = 1;
}

void timer0()interrupt 1
{
	cp++;
	if((cp >= 800) && (qujian == 0))
	{
		cp  = 0;
		if(shanshuo == 0)
		{
			shanshuo = 1;
			P2 = 0x80;
			P0 = 0xff;
		}
		else if(shanshuo == 1)
		{
			shanshuo = 0;
			P2 = 0x80;
			P0 = 0xfe;
		}
	}
	
	if((cp >= 400) && (qujian == 1))
	{
		cp  = 0;
		if(shanshuo == 0)
		{
			shanshuo = 1;
			P2 = 0x80;
			P0 = 0xff;
		}
		else if(shanshuo == 1)
		{
			shanshuo = 0;
			P2 = 0x80;
			P0 = 0xfe;
		}
	}
	
	if((cp >= 200) && (qujian == 2))
	{
		cp  = 0;
		if(shanshuo == 0)
		{
			shanshuo = 1;
			P2 = 0x80;
			P0 = 0xff;
		}
		else if(shanshuo == 1)
		{
			shanshuo = 0;
			P2 = 0x80;
			P0 = 0xfe;
		}
	}
}

void main()
{
	banzi_init();
	Timer0Init();
	while(1)
	{
		wendu = DS18B20_get();
		keyscan();
		display();
		xianshi();
	}
}