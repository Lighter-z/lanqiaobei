void display()
{
	if(wendu < wendumin)
	{
		qujian = 0;
		P2 = 0xa0;
		P0 = 0x00;
	}
	else if(wendu > wendumax)
	{
		qujian = 2;
		P2 = 0xa0;
		P0 = 0x10;
	}
	else if((wendu > wendumin) && (wendu < wendumax))
	{
		qujian = 1;
		P2 = 0xa0;
		P0 = 0x00;
	}
	
	if(shezhi == 0)
	{
		yi = 10;
		er = qujian;
		san = 10;
		si = 11;
		wu = 11;
		liu = 11;
		qi = wendu / 10;
		ba = wendu % 10;
	}
	else if(shezhi == 1)
	{
		if(qingchu == 1)
		{
			qingchu = 0;
			yi = 10;
			er = 11;
			san = 11;
			si = 11;
			wu = 11;
			liu = 10;
			qi = 11;
			ba = 11;
		}
		if((er == 11) && (key_flag == 1))
			{
				key_flag = 0;
				er = num;
			}
			else if((san == 11) && (key_flag == 1))
			{
				key_flag = 0;
				san = num;
			}
			else if((qi == 11) && (key_flag == 1))
			{
				key_flag = 0;
				qi = num;
			}
			else if((ba == 11) && (key_flag == 1))
			{
				key_flag = 0;
				ba = num;
				if((er * 10 + san) < (qi * 10 + ba))
				{
					P2 = 0x80;
					P0 = 0xfd;
				}
			}
	}
}