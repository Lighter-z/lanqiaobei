#ifndef _IIC_H
#define _IIC_H


//º¯ÊýÉùÃ÷
void IIC_Start(void); 
void IIC_Stop(void);  
void IIC_Ack(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
bit IIC_WaitAck(void);  
unsigned char IIC_RecByte(void); 
unsigned char AD(unsigned char add);
void AT24C04_Write(unsigned char add,unsigned char dat);
unsigned char AT24C04_Read(unsigned char add);

#endif