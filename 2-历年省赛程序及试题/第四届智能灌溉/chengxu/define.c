unsigned char code seven_seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};

unsigned char shijian[] = {0,30,8,0,0,0,0,0};
unsigned char min,hour;
unsigned char yi,er,san,si,wu,liu,qi,ba;
unsigned char shidu,fazhi = 50;
unsigned char temp = 0x00;
bit zidong = 1;
bit fazhitiaozheng = 0;
bit tixing = 1;
bit guan = 0;

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