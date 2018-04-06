void keyscan()
{
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			while(P33 == 0);
			moshi++;
			if(moshi >= 4)moshi = 1;
		}
	}
	
	if(P32 == 0)
	{
		Delay1ms();
		if(P32 == 0)
		{
			while(P32 == 0);
			shijian++;
			if(shijian >= 3)
			{
				shijian = 0;
			}
			if(shijian == 0)
			{
				shengyushijian = 0;
			}
			else if(shijian == 1)
			{
				shengyushijian = 60;
			}	
			else if(shijian == 2)
			{
				shengyushijian = 120;
			}
		}
	}
	
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);
			shengyushijian = 0;
		}
	}
	
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			if(wenshi == 0)
			{
				zhuangtai = moshi;
				wenshi = 1;
			}
			else if(wenshi == 1)
			{
				wenshi = 0;
				moshi = zhuangtai;
			}
		}
	}
}