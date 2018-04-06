#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds18b20.c>
#include<ds1302.c>
#include<key.c>
#include<display.c>

void banzi_init() //���ӳ�ʼ��
{
	P2 = 0xa0;
	P0 = 0x00;//�رշ��������̵���
	
	P2 = 0x80;
	P0 = 0xff;//�ر�LED
	
	P2 = 0xc0;
	P0 = 0xff;//�ر�����ܶ�ѡ
	P2 = 0xff;
	P0 = 0xff;//�ر������λѡ
}

void xianshi()
{
	P2 = 0xc0;
	P0 = 0x01;
	P2 = 0xff;
	P0 = seven_seg[yi];
	Delay1ms();//��ʾ��һ�������
	
	P2 = 0xc0;
	P0 = 0x02;
	P2 = 0xff;
	P0 = seven_seg[er];
	Delay1ms();//��ʾ�ڶ��������
	
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
	Delay1ms();//��Ӱ
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
	if(cp >= 200)
	{
		cp = 0;
		if(naozhongkai == 1)
		{
			cp2++;
			if(cp2 >= 25)//5s
			{
				cp2 = 0;
				naozhongkai = 0;//�ر����ӱ�־λ
			}
			if(shanshuo == 0)//L1��   ��˸
			{
				P2 = 0x80;
				P0 = 0xfe;
				shanshuo = 1;
			}
			else if(shanshuo == 1)//L1��  ��˸
			{
				shanshuo = 0;
				P2 = 0x80;
				P0 = 0xff;
			}
		}
		else if(naozhongkai == 0)//�ر�LED
		{
			P2 = 0x80;
			P0 = 0xff;
		}
	}
}

void main()
{
	banzi_init();
	DS1302_init();//ds1302��ʼ��
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