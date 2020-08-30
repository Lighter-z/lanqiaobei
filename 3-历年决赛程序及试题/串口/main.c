#include<stc15f2k60s2.h>
#include<intrins.h>
/*
��ע΢�Ź��ںţ�Ƕ��ʽ����
��̨�ظ������ű�  ��ȡ����
 */
unsigned char aaa[] = "zm\r\n";
unsigned char zzz[] = "lmz\r\n";
unsigned char num,flag;

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


void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE0;		//�趨��ʱ��ֵ
	TH1 = 0xFE;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}

void Uart() interrupt 4 using 1
{
	RI = 0;
	num = SBUF;
	if(num == 'A')
	{
		P2 = 0x80;
		P0 = 0xfe;
	}
}

void send(unsigned char *p)
{
	unsigned char i = 0;
	do
	{
		SBUF = p[i++];
		while(TI == 0);
		TI = 0;
	}while(p[i] != 0);
}

void key()
{
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			send(aaa);
		}
	}
}

void main()
{
	banzi_init();
	UartInit();
	EA = 1;
	ES = 1;
	while(1)
	{
		key();
	}
}	
