//按键的p1 p3没有改
#include<reg52.h>
#include <intrins.h>
#include <string.h>
#define uchar unsigned char
#define uint unsigned int

sbit P30=P3^0;
sbit P31=P3^1;
sbit P32=P3^2;
sbit DQ=P2^2;//ds18b20与单片机连接口
sbit RS=P3^5;
sbit RW=P3^6;
sbit EN=P3^4;
sbit BELL=P2^3;//蜂鸣器
sbit red=P1^0;
sbit green=P1^1;

unsigned char  str1[]={"temperature: "};
unsigned char  str2[]={" "};
unsigned char  str3[]={"upper limit: "};


uchar data disdata[5];
uchar data yuzhi[5];
uint tvalue,top=22;//温度值
uchar tflag;//温度正负标志
uchar xianshi=0,ok=0,jian;
uchar jindong=0;



/*************************lcd1602程序**************************/
void delay1ms(unsigned int ms)//延时1毫秒
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<114;j++);
}

void wr_com(unsigned char com)//写指令//
{ 
	delay1ms(1);
	RS=0;
	RW=0;
	EN=0;	
	P0=com;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}

void wr_dat(unsigned char dat)//写数据//
{
	delay1ms(1);
	RS=1;
	RW=0;
	EN=0;
	P0=dat;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}

void lcd_init()//初始化设置//
{
	delay1ms(15);
	wr_com(0x38);delay1ms(5);
	wr_com(0x08);delay1ms(5);
	wr_com(0x01);delay1ms(5);
	wr_com(0x06);delay1ms(5);
	wr_com(0x0c);delay1ms(5);
}

void display(unsigned char *p)//显示//
{
	while(*p!='\0')
	{
		wr_dat(*p);
		p++;
		delay1ms(1);
	}
}

void init_play()//初始化显示

{ 
	lcd_init();
	wr_com(0x80);
	display(str1);
	wr_com(0x80+0x40);
	display(str2);
}

/******************************ds1820程序***************************************/

void delay_18B20(unsigned int i)//延时1微秒
{
	while(i--);
}

void ds1820rst()/*ds1820复位*/
{
	unsigned char x=0;
	DQ = 1; //DQ复位
	delay_18B20(4); //延时
	DQ = 0; //DQ拉低
	delay_18B20(100); //精确延时大于480us
	DQ = 1; //拉高
	delay_18B20(40);
}

uchar ds1820rd()/*读数据*/
{ 
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; //给脉冲信号
		dat>>=1;
		DQ = 1; //给脉冲信号
		if(DQ)
		dat|=0x80;
		delay_18B20(10);
	}
	return(dat);
}

void ds1820wr(uchar wdata)/*写数据*/
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{ 
		DQ = 0;
		DQ = wdata&0x01;
		delay_18B20(10);
		DQ = 1;
		wdata>>=1;
	}

}

read_temp()/*读取温度值并转换*/
{
	uchar a,b;
	ds1820rst();
	ds1820wr(0xcc);//*跳过读序列号*/
	ds1820wr(0x44);//*启动温度转换*/
	ds1820rst();
	ds1820wr(0xcc);//*跳过读序列号*/
	ds1820wr(0xbe);//*读取温度*/
	a=ds1820rd();
	b=ds1820rd();
	tvalue=b;
	tvalue<<=8;
	tvalue=tvalue|a;
	if(tvalue<0x0fff)
	tflag=0;
	else
	{
		tvalue=~tvalue+1;
		tflag=1;
	}
	tvalue=tvalue*(0.625);//温度值扩大10倍，精确到1位小数
	return(tvalue);
}

/*******************************************************************/

void ds1820disp()//温度值显示
	{ 
		uchar flagdat;
		disdata[0]=tvalue/1000+0x30;//百位数
		disdata[1]=tvalue%1000/100+0x30;//十位数
		disdata[2]=tvalue%100/10+0x30;//个位数
		disdata[3]=tvalue%10+0x30;//小数位
		if(tflag==0)
			flagdat=0x20;//正温度不显示符号
		else
			flagdat=0x2d;//负温度显示负号:-
		if(disdata[0]==0x30)
		{
			disdata[0]=0x20;//如果百位为0，不显示
			if(disdata[1]==0x30)
			{
				disdata[1]=0x20;//如果百位为0，十位为0也不显示
			}
		}
		wr_com(0xc0);
		wr_dat(flagdat);//显示符号位
		wr_com(0xc1);
		wr_dat(disdata[0]);//显示百位
		wr_com(0xc2);
		wr_dat(disdata[1]);//显示十位
		wr_com(0xc3);
		wr_dat(disdata[2]);//显示个位
		wr_com(0xc4);
		wr_dat(0x2e);//显示小数点
		wr_com(0xc5);
		wr_dat(disdata[3]);//显示小数位
//		wr_com(0xc6);
//		wr_dat(disdata[4]);//显示小数位
}

void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}


/******************************按键检测部分***************************************/
void keyscan()
{
	if(P30==0)//设置
	{
		delayms(5);
		if(P30==0)
		{
		 xianshi++;wr_com(0xc0);	wr_dat(0x20);
							 wr_com(0xc1);	wr_dat(0x20);
							 wr_com(0xc2);	wr_dat(0x20);
							 wr_com(0xc3);	wr_dat(0x20);
							 wr_com(0xc4);	wr_dat(0x20);
							 wr_com(0xc5);	wr_dat(0x20);//设置
		}
		while(!P30);
	}
	else if(P31==0)//s6
	{
		delayms(5);
		if(P31==0)
		{
			top++;
		}
		while(!P31);
	}
	else if(P32==0)//s5
	{
		delayms(5);
		if(P32==0)
		{
			top--;
		}
		while(!P32);
	}
}

/********************主程序***********************************/
void main()
{ 
	uchar i=0,wendu;
	init_play();//初始化显示
	while(1)
	{
		read_temp();//读取温度
		wendu=tvalue/10;
		keyscan();//按键扫描
		
		
		if(xianshi==0)//温度显示界面
		{
			wr_com(0x80);
			display(str1);
			ds1820disp();//显示
			ok=0;
		}
		
		if(xianshi==1)//温度阈值设置界面
		{
			if(jindong==1)
			{
				top=jian*10;
			}
			if(jindong==2)
			{
				top+=jian;
				jindong=0;
			}
			yuzhi[0]=top/10+0x30;
			yuzhi[1]=top%10+0x30;
			wr_com(0x80);
			display(str3);
			wr_com(0xc2);
			wr_dat(yuzhi[0]);
			wr_com(0xc3);
			wr_dat(yuzhi[1]);
			
		}
		if(xianshi==2)
		{
			xianshi=0;
		}
		if(wendu>=top)
		{
			BELL=0;
			red=0;
			green=1;
		}
		if(wendu<top)
		{
			BELL=1;
			green=0;
			red=1;
		}
	}
}