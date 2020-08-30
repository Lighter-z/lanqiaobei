void keyscan()
{
	
	//s4
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			if(canshushezhi == 1)
			{
				if(jiange == 1)
				{
					jiange = 5;
				}
				else if(jiange == 5)
				{
					jiange = 30;
				}
				else if(jiange == 30)
				{
					jiange = 60;
				}
				else if(jiange == 60)
				{
					jiange = 1;
				}
			}
		}
	}
	//s5
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			canshushezhi = 0;
			ET0 = 1;
		}
	}
	
	//s6
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);			
			ET0 = 0;
			P2 = 0x80;
			P0 = 0xff;
			kaishi = 1;
		}
	}
	
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			canshushezhi = 1;
			kaishi = 0;
		}
	}
}