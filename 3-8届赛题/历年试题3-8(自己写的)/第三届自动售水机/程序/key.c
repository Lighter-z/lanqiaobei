void keyscan()
{
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			P2 = 0xa0;
			P0 = 0x08;
			P2 = 0x80;
			P0 = 0xfe;
		}
	}
	
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			P2 = 0xa0;
			P0 = 0x00;
			P2 = 0x80;
			P0 = 0xff;
		}
	}
}