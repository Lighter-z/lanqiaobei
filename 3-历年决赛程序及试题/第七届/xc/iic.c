

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}    


#define SlaveAddrW 0xA0
#define SlaveAddrR 0xA1

//�������Ŷ���
sbit SD = P2^1;  /* ������ */
sbit SCL = P2^0;  /* ʱ���� */


//������������
void IIC_Start(void)
{
	SD = 1;
	SCL = 1;
	somenop;
	SD = 0;
	somenop;
	SCL = 0;	
}

//����ֹͣ����
void IIC_Stop(void)
{
	SD = 0;
	SCL = 1;
	somenop;
	SD = 1;
}

//Ӧ��λ����
void IIC_Ack(bit ackbit)
{
	if(ackbit) 
	{	
		SD = 0;
	}
	else 
	{
		SD = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SD = 1; 
	somenop;
}

//�ȴ�Ӧ��
bit IIC_WaitAck(void)
{
	SD = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SD)    
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
			SD = 1;
		}
		else 
		{
			SD = 0;
		}
		somenop;
		SCL = 1;
		byt <<= 1;
		somenop;
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
		somenop;
		da <<= 1;
		if(SD) 
		da |= 0x01;
		SCL = 0;
		somenop;
	}
	return da;
}

unsigned char AD(unsigned char add)
{
	unsigned char temp;
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp = IIC_RecByte();
	IIC_Ack(0);
	IIC_Stop();
	return temp;
}

void Write_at(unsigned char add,unsigned char dat)
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

unsigned char Read_at(unsigned char add)
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
