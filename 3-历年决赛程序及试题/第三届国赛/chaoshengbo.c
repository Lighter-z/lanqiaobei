bit flag = 0;
unsigned char cp = 0;
unsigned int juli,t;

sbit TX = P1^0;
sbit RX = P1^1;

void chaoshengbo()
{
	unsigned char i = 8;
	do
	{
		TX = 1;
		smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;
		TX = 0;
		smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;smoenop;
	}
	while(i--);
}

void Timer0Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x9A;		//���ö�ʱ��ֵ
	TH0 = 0xA9;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}
void Timer1Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
}

void timer0()interrupt 1
{
	cp++;
	if(cp >= 100)
	{
		cp = 0;
		flag = 1;
	}
	if(jidianqi == 1)
	{
		cp1++;
		if(cp1 >= 2500)
		{
			cp1 = 0;
			jidianqi = 0;
			P2 = 0xa0;
			P0 = 0x00;
		}
	}
	if(fengmingqi == 1)
	{
		cp2++;
		if(cp2 >= 1500)
		{
			cp2 = 0;
			fengmingqi = 0;
			P2 = 0xa0;
			P0 = 0x00;
		}
	}
}

void ceju()
{
	if(flag == 1)
	{
		flag = 0;
		TR1 = 1;
		chaoshengbo();
		while((TF1 == 0) && (RX == 1));
		TR1 = 0;
		if(TF1 == 1)
		{
			TF1 = 0;
			juli = 999;
		}
		else 
		{
			t = TH1;
			t = t << 8;
			t |= TL1;
			juli = (unsigned int)(t * 0.017);
			juli = juli / 12;
		}
		TH1 = 0;
		TL1 = 0;
	}
}

