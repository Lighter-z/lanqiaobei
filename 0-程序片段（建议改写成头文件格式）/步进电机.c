/*******************************************************************************  
* 文件名称：15单片机直流电机&五线四相步进电机正返转、加减速程序
* 实验目的：1.掌握直流电机PWM调速方法&五线四相步进电机正返转、加减速程序相关使用方法
* 硬件说明：IAP15F2K61S2@11.0592MHz
* 日期版本：2017-2-1 
*******************************************************************************/

/*
#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	

void delayms(int ms);
void allinit();


void main()
{
	allinit();
	
	P2=0XA0;
	while(1)
	{
		P05=1;
		delayms(1);
		P05=0;
		delayms(4);
	}
}

void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}

*/






//------------------------------------正反转测试程序-------------------------------------------------------//
/*
#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //步进电机控制接口定义
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//正转 电机导通相序 D-C-B-A//0000 1000

uchar phaseccw[4]={0x01,0x02,0x04,0x08};//反转 电机导通相序 A-B-C-D

void delayms(int ms);
void allinit();

void MotorStop(void);
void MotorCCW(void);
void MotorCW(void);


void main()
{
	uint i;
	allinit();
	
	P2=0XA0;
	while(1)
	{
		for(i=0;i<500;i++)
		{
		 MotorCW();   //顺时针转动
		} 
		MotorStop();  //停止转动
		delayms(500);delayms(500);delayms(500);delayms(500);
		
		
		for(i=0;i<500;i++)
		{
		 MotorCCW();  //逆时针转动
		} 
		MotorStop();  //停止转动
		delayms(500);delayms(500);delayms(500);delayms(500);
	}
}


//顺时针转动
void MotorCW(void)
{
  uchar i;
  for(i=0;i<4;i++)
	{
	 MotorData=phasecw[i];//uchar phasecw[4] ={0x08,0x04,0x02,0x01};
	 delayms(4);
	}
}

//逆时针转动
void MotorCCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phaseccw[i];//phaseccw[4]={0x01,0x02,0x04,0x08};//反转 电机导通相序 A-B-C-D
   delayms(4);
  }
}

//停止转动
void MotorStop(void)
{
 MotorData=0x00;
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}

*/




//------------------------------------加速转测试程序-------------------------------------------------------//

#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //步进电机控制接口定义
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//正转 电机导通相序 D-C-B-A
uchar phaseccw[4]={0x01,0x02,0x04,0x08};//反转 电机导通相序 A-B-C-D

uchar speed;

void delayms(int ms);
void allinit();

void MotorStop(void);
void MotorCW(void);


void main()
{
	uint i;
	allinit();
	
	speed=25;
	
	P2=0XA0;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			MotorCW();  //顺时针转动
		} 
		
		speed--;     //加速 
		
		if(speed<4)  
		{
		 speed=25;    //重新开始加速运动
		 MotorStop();
		 delayms(500);delayms(500);delayms(500);delayms(500);
		}
	}
}


//顺时针转动
void MotorCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phasecw[i];
   delayms(speed);//转速调节
  }
}

//停止转动
void MotorStop(void)
{
 MotorData=0x00;
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}


//------------------------------------减速转测试程序-------------------------------------------------------//
/*
#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //步进电机控制接口定义
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//正转 电机导通相序 D-C-B-A
uchar phaseccw[4]={0x01,0x02,0x04,0x08};//反转 电机导通相序 A-B-C-D

uchar speed;

void delayms(int ms);
void allinit();

void MotorStop(void);
void MotorCW(void);


void main()
{
	uint i;
	allinit();
	
	speed=4;
	
	P2=0XA0;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			MotorCW();  //顺时针转动
		} 
		
		speed++;     //减速 
		
		if(speed>100)  
		{
		 speed=100;    //重新开始加速运动
		 MotorStop();
		 delayms(500);delayms(500);delayms(500);delayms(500);
		}
	}
}


//顺时针转动
void MotorCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phasecw[i];
   delayms(speed);//转速调节
  }
}

//停止转动
void MotorStop(void)
{
 MotorData=0x00;
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//关闭蜂鸣器，继电器
	
	P2=0X80;
	P0=0XFF;//关闭LED灯
	
	P2=0XC0;
	P0=0XFF;//选择所有数码管
	P2=0XFF;
	P0=0XFF;//关闭所有数码管
}
*/




























