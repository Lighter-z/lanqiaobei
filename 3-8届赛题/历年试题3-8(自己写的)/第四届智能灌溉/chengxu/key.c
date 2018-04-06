void keyscan()
{
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			if(zidong == 1)
			{
				zidong = 0;
			}
			else if(zidong == 0)
			{
				zidong = 1;
			}
		}
	}
	
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);
			if(zidong == 1)
			{
				if(fazhitiaozheng == 1)
				{
					fazhitiaozheng = 0;
					AT24C04_Write(0x00,fazhi);
				}
				else if(fazhitiaozheng == 0)
				{
					fazhitiaozheng = 1;
				}
			}
			else if(zidong == 0)
			{
				if(tixing == 0)
				{
					tixing = 1;
				}
				else if(tixing == 1)
				{
					tixing = 0;
				}
			}
		}
	}
	
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			if(zidong == 1)
			{
				if(fazhitiaozheng == 1)
				{
					fazhi++;
				}
			}
			else if(zidong == 0)
			{
				guan = 0;
			}
		}
	}
	
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			if(zidong == 1)
			{
				if(fazhitiaozheng == 1)
				{
					fazhi--;
				}
			}
			else if(zidong == 0)
			{
				guan = 1;
			}
		}
	}
}