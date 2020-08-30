/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9

  关注微信公众号：嵌入式基地
后台回复：蓝桥杯  获取资料
*/



sbit SCK=P1^7;		
sbit SD=P2^3;		
sbit RST = P1^3;   // DS1302复位												

void Write_Ds1302_Byte(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SD=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();  
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte((dat / 10) << 4 | (dat % 10));		
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00;
	unsigned char dat1,dat2;
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SD)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	_nop_();
 	RST=0;
	SCK=0;
	_nop_();
	SCK=1;
	_nop_();
	SD=0;
	_nop_();
	SD=1;
	_nop_();
	dat1 = temp / 16;
	dat2 = temp % 16;
	temp = dat1 * 10 + dat2;
	return (temp);			
}


void DS1302_init()
{
	unsigned char i,add;
	add = 0x80;
	Write_Ds1302(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		Write_Ds1302(add,shijian[i]);
		add = add + 2;
	}
	Write_Ds1302(0x8e,0x80);
}
void DS1302_Read()
{
	unsigned char i,add;
	add = 0x81;
	Write_Ds1302(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		shijian[i] = Read_Ds1302(add);
		add = add + 2;
	}
	Write_Ds1302(0x8e,0x80);
}
