sbit SCK=P1^7;		
sbit SD=P2^3;		
sbit RST=P1^3;
/********************************************************************/ 
/*��λ��*/
#define RST_CLR	RST=0	/*��ƽ�õ�*/
#define RST_SET	RST=1	/*��ƽ�ø�*/
/*˫������*/
#define SDA_CLR	SD=0	/*��ƽ�õ�*/
#define SDA_SET	SD=1	/*��ƽ�ø�*/
#define SDA_R	SD	/*��ƽ��ȡ*/	
/*ʱ���ź�*/
#define SCK_CLR	SCK=0	/*ʱ���ź�*/
#define SCK_SET	SCK=1	/*��ƽ�ø�*/
/********************************************************************/ 
#define ds1302_sec_addr			0x80		//�����ݵ�ַ
#define ds1302_min_addr			0x82		//�����ݵ�ַ
#define ds1302_hr_addr			0x84		//ʱ���ݵ�ַ
#define ds1302_date_addr		0x86		//�����ݵ�ַ
#define ds1302_month_addr		0x88		//�����ݵ�ַ
#define ds1302_day_addr			0x8A		//�������ݵ�ַ
#define ds1302_year_addr		0x8C		//�����ݵ�ַ

#define ds1302_control_addr		0x8Ee		//д���������ֵ�Ԫ��ַ
#define ds1302_charger_addr		0x90 		//丵�����������ֵ�ַ			 
#define ds1302_clkburst_addr	0xBE		//������ʱ��ͻ��ģʽ�����ֵ�ַ


/********************************************************************/ 
/*���ֽ�д��һ�ֽ�����*/
void Write_Ds1302_Byte(unsigned char dat) 
{
	unsigned char i;
	SCK = 0;
	for (i=0;i<8;i++) 
	{ 
	    SD=0;
		if (dat & 0x01) 	// �ȼ���if((addr & 0x01) ==1) 
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*��ƽ�ø�*/
		}
		else 
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*��ƽ�õ�*/
		}		 
		SCK_SET;
		SCK_CLR;		
		dat = dat >> 1; 
	} 
}
/********************************************************************/ 
/*���ֽڶ���һ�ֽ�����*/
unsigned char Read_Ds1302_Byte(void) 
{
	unsigned char i, dat=0;	
	for (i=0;i<8;i++)
	{	
		dat = dat >> 1;
		if (SDA_R) 	  //�ȼ���if(SDA_R==1)    #define SDA_R SDA /*��ƽ��ȡ*/	
		{
			dat |= 0x80;
		}
		else 
		{
			dat &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;
	}
	return dat;
}

/********************************************************************/ 
/*��DS1302 ���ֽ�д��һ�ֽ�����*/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{ 

	RST_CLR;			/*RST���õͣ�ʵ��DS1302�ĳ�ʼ��*/
	SCK_CLR;			/*SCK���õͣ�ʵ��DS1302�ĳ�ʼ��*/

	RST_SET;			/*����DS1302����,RST=1��ƽ�ø� */
	addr = addr & 0xFE;	 
	Write_Ds1302_Byte(addr); /*д��Ŀ���ַ��addr,��֤��д����,д֮ǰ�����λ����*/	
	Write_Ds1302_Byte((dat / 10) << 4 | (dat % 10));	 /*д�����ݣ�dat*/
	RST_CLR;				 /*ֹͣDS1302����*/
}

/********************************************************************/ 
/*��DS1302���ֽڶ���һ�ֽ�����*/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr) 
{ 
	unsigned char temp;
	unsigned char dat1,dat2;
	RST_CLR;			/*RST���õͣ�ʵ��DS1302�ĳ�ʼ��*/
	SCK_CLR;			/*SCK���õͣ�ʵ��DS1302�ĳ�ʼ��*/

	RST_SET;	/*����DS1302����,RST=1��ƽ�ø� */	
	addr = addr | 0x01;	 
	Write_Ds1302_Byte(addr); /*д��Ŀ���ַ��addr,��֤�Ƕ�����,д֮ǰ�����λ�ø�*/
	temp=Read_Ds1302_Byte(); /*��DS1302�ж���һ���ֽڵ�����*/		
	RST_CLR;	/*ֹͣDS1302����*/
	dat1 = temp / 16;
	dat2 = temp % 16;
	temp = dat1 * 10 + dat2;
	return temp;
}

void DS1302_init()
{
	unsigned char i = 0,add = 0x80;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		Ds1302_Single_Byte_Write(add,shijian[i]);
		add += 2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}

void DS1302_Read()
{
	unsigned char i = 0,add = 0x81;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	for(i = 0;i < 7;i++)
	{
		shijian[i] = Ds1302_Single_Byte_Read(add);
		add += 2;
	}
	Ds1302_Single_Byte_Write(0x8e,0x80);
}
