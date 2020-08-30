unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char shijian[] = {55,59,23,0,0,0,0,0};
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char sec,min,hour,sec_n,min_n,hour_n;
unsigned char xiaoshu;
unsigned char wendu,cp,cp2 = 0,naozhongkai = 0;
unsigned char shizhongshezhi = 0,naozhongshezhi = 0;
bit wenduxianshi = 0;
bit shanshuo = 0;
bit s4 = 0;
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
