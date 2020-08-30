#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<key.c>
#include<display.c>


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

void Timer1Init(void)		//100΢��@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xAE;		//���ö�ʱ��ֵ
	TH1 = 0xFB;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	EA = 1;
	ET1 = 1;
}

void tm1_isr() interrupt 3 using 1
{
   cp++;
	if(cp >= 10)
	{
		cp = 0;
	}
	if(shengyushijian != 0)
	{
		if(cp > zhankongbi)
		{
			P34 = 0;
		}
		else 
		{
			P34 = 1;
		}
	}
	else if(shengyushijian == 0)
	{
		P34 = 0;
	}
}

void Timer0Init(void)		//5����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x28;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA = 1;
	ET0 = 1;
}

void timer0()interrupt 1
{
	cp1++;
	if(cp1 >= 200)
	{
		cp1 = 0;
		if(shengyushijian <= 0)
		{
			shengyushijian = 0;
		}
		else 
		{		
			shengyushijian--;
		}
	}
}

void main()
{
	banzi_init();
	Timer1Init();
	Timer0Init();
	while(1)
	{
		wendu = DS18B20_get();
		keyscan();
		display();
		xianshi();
	}
}