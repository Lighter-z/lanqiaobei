void keyscan()
{
	//s7
	if(P30 == 0)
	{
		Delay1ms();
		if(P30 == 0)
		{
			while(P30 == 0);
			shizhongshezhi++;
			if(shizhongshezhi >= 4)
			{
				shizhongshezhi = 0;
			}
		}
	}
	
	//s6
	if(P31 == 0)
	{
		Delay1ms();
		if(P31 == 0)
		{
			while(P31 == 0);
			naozhongshezhi++;
			if(naozhongshezhi >= 4)
			{
				naozhongshezhi = 0;
				shizhongshezhi = 0;
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
			if(shizhongshezhi == 1)
			{
				shijian[2]++;
				if(shijian[2] >= 24)
				{
					shijian[2] = 23;
				}
				DS1302_init();
			}
			else if(shizhongshezhi == 2)
			{
				shijian[1]++;
				if(shijian[1] >= 60)
				{
					shijian[1] = 59;
				}
				DS1302_init();
			}
			else if(shizhongshezhi == 3)
			{
				shijian[0]++;
				if(shijian[0] >= 60)
				{
					shijian[0] = 59;
				}
				DS1302_init();
			}
			
			else if(naozhongshezhi == 1)
			{
				hour_n++;
				if(hour_n >= 24)
				{
					hour_n = 23;
				}
			}
			else if(naozhongshezhi == 2)
			{
				min_n++;
				if(min_n >= 60)
				{
					min_n = 59;
				}
			}
			else if(naozhongshezhi == 3)
			{
				sec_n++;
				if(sec_n >= 60)
				{
					sec_n = 59;
				}
			}
		}
	}
	
	//s4
	if(P33 == 0)
	{
		Delay1ms();
		if(P33 == 0)
		{
			s4 = 1;
			shizhongshezhi = 4;
		}
	}
	if((P33 == 1) && (s4 == 1))
		{
			s4 = 0;
			shizhongshezhi = 0;
			if(shizhongshezhi == 1)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				shijian[2]--;
				if(shijian[2] <= 0)
				{
					shijian[2] = 0;
				}
				DS1302_init();
			}
			else if(shizhongshezhi == 2)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				shijian[1]--;
				if(shijian[1] <= 0)
				{
					shijian[1] = 0;
				}
				DS1302_init();
			}
			else if(shizhongshezhi == 3)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				shijian[0]--;
				if(shijian[0] <= 0)
				{
					shijian[0] = 0;
				}
				DS1302_init();
			}
			
			else if(naozhongshezhi == 1)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				hour_n--;
				if(hour_n <= 0)
				{
					hour_n = 0;
				}
			}
			else if(naozhongshezhi == 2)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				min_n--;
				if(min_n <= 0)
				{
					min_n = 0;
				}
			}
			else if(naozhongshezhi == 3)
			{
			if(naozhongkai != 0)
			{
				naozhongkai = 0;
			}
				sec_n--;
				if(sec_n <= 0)
				{
					sec_n = 0;
				}
			}
		}
}