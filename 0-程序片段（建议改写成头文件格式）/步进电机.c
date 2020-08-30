/*******************************************************************************  
* �ļ����ƣ�15��Ƭ��ֱ�����&�������ಽ���������ת���Ӽ��ٳ���
* ʵ��Ŀ�ģ�1.����ֱ�����PWM���ٷ���&�������ಽ���������ת���Ӽ��ٳ������ʹ�÷���
* Ӳ��˵����IAP15F2K61S2@11.0592MHz
* ���ڰ汾��2017-2-1 
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
	P0=0X00;//�رշ��������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�ر����������
}

*/






//------------------------------------����ת���Գ���-------------------------------------------------------//
/*
#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //����������ƽӿڶ���
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//��ת �����ͨ���� D-C-B-A//0000 1000

uchar phaseccw[4]={0x01,0x02,0x04,0x08};//��ת �����ͨ���� A-B-C-D

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
		 MotorCW();   //˳ʱ��ת��
		} 
		MotorStop();  //ֹͣת��
		delayms(500);delayms(500);delayms(500);delayms(500);
		
		
		for(i=0;i<500;i++)
		{
		 MotorCCW();  //��ʱ��ת��
		} 
		MotorStop();  //ֹͣת��
		delayms(500);delayms(500);delayms(500);delayms(500);
	}
}


//˳ʱ��ת��
void MotorCW(void)
{
  uchar i;
  for(i=0;i<4;i++)
	{
	 MotorData=phasecw[i];//uchar phasecw[4] ={0x08,0x04,0x02,0x01};
	 delayms(4);
	}
}

//��ʱ��ת��
void MotorCCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phaseccw[i];//phaseccw[4]={0x01,0x02,0x04,0x08};//��ת �����ͨ���� A-B-C-D
   delayms(4);
  }
}

//ֹͣת��
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
	P0=0X00;//�رշ��������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�ر����������
}

*/




//------------------------------------����ת���Գ���-------------------------------------------------------//

#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //����������ƽӿڶ���
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//��ת �����ͨ���� D-C-B-A
uchar phaseccw[4]={0x01,0x02,0x04,0x08};//��ת �����ͨ���� A-B-C-D

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
			MotorCW();  //˳ʱ��ת��
		} 
		
		speed--;     //���� 
		
		if(speed<4)  
		{
		 speed=25;    //���¿�ʼ�����˶�
		 MotorStop();
		 delayms(500);delayms(500);delayms(500);delayms(500);
		}
	}
}


//˳ʱ��ת��
void MotorCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phasecw[i];
   delayms(speed);//ת�ٵ���
  }
}

//ֹͣת��
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
	P0=0X00;//�رշ��������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�ر����������
}


//------------------------------------����ת���Գ���-------------------------------------------------------//
/*
#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	
	
#define MotorData P0                    //����������ƽӿڶ���
uchar phasecw[4] ={0x08,0x04,0x02,0x01};//��ת �����ͨ���� D-C-B-A
uchar phaseccw[4]={0x01,0x02,0x04,0x08};//��ת �����ͨ���� A-B-C-D

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
			MotorCW();  //˳ʱ��ת��
		} 
		
		speed++;     //���� 
		
		if(speed>100)  
		{
		 speed=100;    //���¿�ʼ�����˶�
		 MotorStop();
		 delayms(500);delayms(500);delayms(500);delayms(500);
		}
	}
}


//˳ʱ��ת��
void MotorCW(void)
{
 uchar i;
 for(i=0;i<4;i++)
  {
   MotorData=phasecw[i];
   delayms(speed);//ת�ٵ���
  }
}

//ֹͣת��
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
	P0=0X00;//�رշ��������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�ر����������
}
*/




























