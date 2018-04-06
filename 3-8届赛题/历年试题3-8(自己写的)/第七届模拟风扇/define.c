unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char wendu,xiaoshu;
unsigned char zhuangtai,wenshi = 0,moshi = 1,zhankongbi;
unsigned char cp,cp1;
unsigned char shijian = 0,shengyushijian = 0;

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