#define uchar unsigned char 
#define uint unsigned int
uchar code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
uchar yi,er,san,si,wu,liu,qi,ba;
uchar wendu,wendumax = 30,wendumin = 20;
uchar qujian,num;
uint cp;
bit shanshuo = 0;
bit shezhi = 0;
bit qingchu = 0;
bit key_flag = 0;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}
