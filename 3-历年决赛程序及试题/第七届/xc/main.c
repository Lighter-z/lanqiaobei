#include<stc15f2k60s2.h>
#include<intrins.h>
#include<define.c>
#include<ds1302.c>
#include<iic.c>
#include<key.c>

void Timer0Init(void)		//5΢��@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xC9;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
//	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0x9A;		//���ö�ʱ��ֵ
	TH1 = 0xA9;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}


void timer0()interrupt 1
{
	if(P34 == 0)
	{
		fan++;
		if(plv_flag == 0)
		{
			plv_flag = 1;
			zheng_now = zheng;
			zheng = 0;
		}
	}
	else if(P34 == 1)
	{
		zheng++;
		if(plv_flag == 1)
		{
			plv_flag = 0;
			fan_now = fan;
			fan = 0;
		}
	}
}

void tm1_isr() interrupt 3 using 1
{
	if(pinlv == 1)
	{
		cp++;
		if(cp >= 495)
		{
			ET0 = 1;
			TR0 = 1;
		}
		else if(cp == 500)
		{
			cp = 0;
			ET0 = 1;
			TR0 = 1;
		}
	}
}

void display()
{
	//shizhong
	if(shizhong_flag == 1)
	{
		if(shizhong == 1)
		{
			shitiao = 0;
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			san = 10;
			si = shijian[1] / 10;
			wu = shijian[1] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(shitiao == 1)
		{
			if((shijian[0] % 2) == 0)
			{
				yi = shijian[2] / 10;
			er = shijian[2] % 10;
			}
			else 
			{
				yi = 11;
				er = 11;
			}
			san = 10;
			si = shijian[1] / 10;
			wu = shijian[1] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(shitiao == 2)
		{
			if((shijian[0] % 2) == 0)
			{
				si = shijian[1] / 10;
			wu = shijian[1] % 10;
				
			}
			else 
			{
				si = 11;
				wu = 11;
			}
			san = 10;
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			liu = 10;
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;
		}
		else if(shitiao == 3)
		{
			if((shijian[0] % 2) == 0)
			{
			qi = shijian[0] / 10;
			ba = shijian[0] % 10;		
			}
			else 
			{
				qi = 11;
				ba = 11;
			}
			san = 10;
			yi = shijian[2] / 10;
			er = shijian[2] % 10;
			liu = 10;
						si = shijian[1] / 10;
			wu = shijian[1] % 10;
		}
	}
	
	//dianya
	if(dianya_an_flag == 1)
	{
		dianya_max = Read_at(0x00);
		Delay1ms();
		dianya_min = Read_at(0x01);
		
		dianya_min = dianya_min * 100;
		dianya_max = dianya_max * 100;
		if(dianya_an == 1)
		{
			fazhi = 0;
			yi = san = 10;
			er = 1;
			si = 11;
			wu = dianya / 1000;
			liu = dianya % 1000 / 100;
			qi = dianya % 100 / 10;
			ba = dianya % 10;
		}
		else if(fazhi == 1)
		{
			if((shijian[0] % 2) == 0)
			{
				yi = dianya_max / 1000;
				er = dianya_max % 1000 / 100;
				san = dianya_max % 100 / 10;
				si = dianya_max % 10;
			}
			else 
			{
				yi = er = san = si = 11;
			}	
			wu = dianya_min / 1000;
			liu = dianya_min % 1000 / 100;
			qi = dianya_min % 100 / 10;
			ba = dianya_min % 10;
		}
		else if(fazhi == 2)
		{
			if((shijian[0] % 2) == 0)
			{
				wu = dianya_min / 1000;
				liu = dianya_min % 1000 / 100;
				qi = dianya_min % 100 / 10;
				ba = dianya_min % 10;
			}
			else 
			{
				wu = liu = qi = ba = 11;
			}	
			yi = dianya_max / 1000;
			er = dianya_max % 1000 / 100;
			san = dianya_max % 100 / 10;
			si = dianya_max % 10;
		}
	}
	
	//pinlv
	if(pinlv_flag == 1)
	{
		if(pinlv == 1)
		{
			time = (zheng_now + fan_now) * 5;
			f = 1000000 / time;
			yi = san = 10;er = 2;
			if(xinhaojiemian == 0)
			{
				si = time / 10000;
				wu = time % 10000 / 1000;
				liu = time % 100 / 100;
				qi = time % 100 / 10;
				ba = time % 10;
			}
			else if(xinhaojiemian == 1)
			{
				si = f / 10000;
				wu = f % 10000 / 1000;
				liu = f % 100 / 100;
				qi = f % 100 / 10;
				ba = f % 10;
			}
		}
	}
	//chaxun
	dianya_max = Read_at(0x00);
		Delay1ms();
		dianya_min = Read_at(0x01);
		
		dianya_min = dianya_min * 100;
		dianya_max = dianya_max * 100;
	if(dianya >= dianya_max)
	{
		shijiancha = 1;
		sec = shijian[0];
		min = shijian[1];
		hour = shijian[2];
	}
	else if(dianya < dianya_min)
	{
		shijiancha = 2;
		sec = shijian[0];
		min = shijian[1];
		hour = shijian[2];
	}
//	else
//	{
//		shijiancha = 0;
//		sec = 5;
//		min = 5;
//		hour = 5;
//	}
	if(chaxun_flag == 1)
	{
		if(cha_flag == 0)
		{
			yi = er = san = si = wu = liu = 11;
			if(shijiancha == 1)
			{
				qi = ba = 0;
			}
			else if(shijiancha == 2)
			{
				qi = 0;ba = 1;
			}
//			else if(shijiancha == 0)
//			{
//				qi = ba = 5;
//			}
		}
		else 
		{
			yi = hour / 10;
			er = hour % 10;
			san = 10;
			si = min / 10;
			wu = min % 10;
			liu = 10;
			qi = sec / 10;
			ba = sec % 10;
		}
	}
}

void main()
{
	banzi_init();
	Write_ds1302();
	Timer0Init();
	Timer1Init();
	EA = 1;
	ET1 = 1;
//	Write_at(0x00,20);
//	Delay1ms();
//	Write_at(0x01,10);
	while(1)
	{
		Read_ds1302();
		dianya = AD(0x03);
		dianya = dianya * 0.023 * 1000;//����
		if(dianya > 5000)dianya = 5000;
		keyscan();
		display();
		xianshi();
	}
}
