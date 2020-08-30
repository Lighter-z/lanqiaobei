

#define smoe {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SDA = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */


//������������
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	smoe;
	SDA = 0;
	smoe;
	SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	smoe;
	SDA = 1;
}

//Ӧ��λ����
void IIC_Ack(unsigned char ackbit)
{
	if(ackbit) 
	{	
		SDA = 0;
	}
	else 
	{
		SDA = 1;
	}
	smoe;
	SCL = 1;
	smoe;
	SCL = 0;
	SDA = 1; 
	smoe;
}

//�ȴ�Ӧ��
bit IIC_WaitAck(void)
{
	SDA = 1;
	smoe;
	SCL = 1;
	smoe;
	if(SDA)    
	{   
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else  
	{ 
		SCL = 0;
		return 1;
	}
}

//ͨ��I2C���߷�������
void IIC_SendByte(unsigned char byt)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{   
		if(byt&0x80) 
		{	
			SDA = 1;
		}
		else 
		{
			SDA = 0;
		}
		smoe;
		SCL = 1;
		byt <<= 1;
		smoe;
		SCL = 0;
	}
}

//��I2C�����Ͻ�������
unsigned char IIC_RecByte(void)
{
	unsigned char da;
	unsigned char i;
	
	for(i=0;i<8;i++)
	{   
		SCL = 1;
		smoe;
		da <<= 1;
		if(SDA) 
		da |= 0x01;
		SCL = 0;
		smoe;
	}
	return da;
}

void Write_AT24c04(unsigned char add,unsigned char dat)
{
	IIC_Start();
	
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}
unsigned char Read_AT24c04(unsigned char add)
{
	unsigned char temp;
	
	IIC_Start();
	
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Ack(0);
	IIC_Stop();
	return temp;
}












//unsigned char AD_Read(unsigned char add)
//{
//	unsigned char temp;
//	IIC_Start();
//	IIC_SendByte(0x90);
//	IIC_WaitAck();
//	IIC_SendByte(add);
//	IIC_WaitAck();
//	IIC_Stop();
//	
////	IIC_Start();
////	IIC_SendByte(0x90);
////	IIC_WaitAck();
////	IIC_SendByte(add);
////	IIC_WaitAck();
////	IIC_Stop();
//	
//	IIC_Start();
//	IIC_SendByte(0x91);
//	IIC_WaitAck();
//	temp = IIC_RecByte();
//	IIC_Ack(0);
//	IIC_Stop();
//	return temp;
//}

//void iic_write(unsigned char add,unsigned char dat)
//{
//	IIC_Start();
//	IIC_SendByte(0xa0);
//	IIC_WaitAck();
//	IIC_SendByte(add);
//	IIC_WaitAck();
//	IIC_SendByte(dat);
//	IIC_WaitAck();
//	IIC_Stop();
//}

//unsigned char iic_read(unsigned char add)
//{
//	unsigned char temp;
//	IIC_Start();
//	IIC_SendByte(0xa0);
//	IIC_WaitAck();
//	IIC_SendByte(add);
//	IIC_WaitAck();
//	
//	IIC_Start();
//	IIC_SendByte(0xa1);
//	IIC_WaitAck();
//	temp = IIC_RecByte();
//	IIC_Ack(0);
//	IIC_Stop();
//	return temp;
//}
