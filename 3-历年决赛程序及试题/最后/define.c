#include<intrins.h>

#define some {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();};

sbit TX = P1^0;
sbit RX = P1^1;

unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char yi,er,san,si,wu,liu,qi,ba;

unsigned char shijian[] = {55,59,23,0,0,0,0};

unsigned char cp,wendu,wenxiaoshu,dianya;
unsigned int juli,t;

bit chao_flag = 0;


void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void banzi_init()
{
	P2 = 0x80;
	P0 = 0xff;
	
	P2 = 0xa0;
	P0 = 0x00;
	
	P2 = 0xc0;
	P0 = 0xff;
	P2 = 0xff;
	P0 = 0xff;
}

void xianshi()
{
	static unsigned char i = 0;
	switch(i)
	{
		case 0:P2 = 0xc0;P0 = 0x01;P2 = 0xff;P0 = seven_seg[yi];break;
		case 1:P2 = 0xc0;P0 = 0x02;P2 = 0xff;P0 = seven_seg[er];break;
		case 2:P2 = 0xc0;P0 = 0x04;P2 = 0xff;P0 = seven_seg[san];break;
		case 3:P2 = 0xc0;P0 = 0x08;P2 = 0xff;P0 = seven_seg[si];break;
		case 4:P2 = 0xc0;P0 = 0x10;P2 = 0xff;P0 = seven_seg[wu];break;
		case 5:P2 = 0xc0;P0 = 0x20;P2 = 0xff;P0 = seven_seg[liu];break;
		case 6:P2 = 0xc0;P0 = 0x40;P2 = 0xff;P0 = seven_seg[qi];break;
		case 7:P2 = 0xc0;P0 = 0x80;P2 = 0xff;P0 = seven_seg[ba];break;
	}
	i++;
	if(i >= 8)i = 0;
//	P2 = 0xc0;
//	P0 = 0x01;
//	P2 = 0xff;
//	P0 = seven_seg[yi];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x02;
//	P2 = 0xff;
//	P0 = seven_seg[er];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x04;
//	P2 = 0xff;
//	P0 = seven_seg[san];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x08;
//	P2 = 0xff;
//	P0 = seven_seg[si];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x10;
//	P2 = 0xff;
//	P0 = seven_seg[wu];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x20;
//	P2 = 0xff;
//	P0 = seven_seg[liu];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x40;
//	P2 = 0xff;
//	P0 = seven_seg[qi];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0x80;
//	P2 = 0xff;
//	P0 = seven_seg[ba];
//	Delay1ms();
//	
//	P2 = 0xc0;
//	P0 = 0xff;
//	P2 = 0xff;
//	P0 = 0xff;
//	Delay1ms();
}

void Timer0Init(void)		//1����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void timer()interrupt 1
{
	cp++;
	if(cp >= 200)
	{
		cp = 0;
		chao_flag = 1;
	}
	xianshi();
}

void Timer1Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
//	TL1 = 0x9A;		//���ö�ʱ��ֵ
//	TH1 = 0xA9;		//���ö�ʱ��ֵ
//	TF1 = 0;		//���TF1��־
//	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}


void chaoshengbo()
{
	unsigned char i = 8;
	do
	{
		TX = 1;
		some;some;some;some;some;some;some;some;some;some;
		TX = 0;
		some;some;some;some;some;some;some;some;some;some;
	}while(i--);
}

void ceju()
{
	if(chao_flag == 1)
	{
		chao_flag = 0;
		chaoshengbo();
		TR1 = 1;
		while((RX == 1) && (TF1 == 0));
		TR1 = 0;
		if(TF1 == 1)
		{
			TF1 = 0;
			juli = 999;
		}
		else 
		{
			t = TH1 << 8;
			t |= TL1;
			juli = (unsigned int)(t * 0.017);
			juli = juli / 12;
		}
		TH1 = 0;
		TL1 = 0;
	}
}
