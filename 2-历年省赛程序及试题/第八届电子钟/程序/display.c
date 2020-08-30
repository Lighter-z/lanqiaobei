void display()
{
		if((hour == hour_n) && (min_n == min) && (sec == sec_n))
	{
			naozhongkai = 1;
	}
	else if(naozhongkai == 0)
	{
		P2 = 0x80;
		P0 = 0xff;
	}
	if((shizhongshezhi == 0) && (naozhongshezhi == 0) && (wenduxianshi == 0))
	{
		yi = hour / 10;
		er = hour % 10;
		san = 10;
		si = min / 10;
		wu = min % 10;
		liu = 10;
		qi = sec / 10;
		ba = sec % 10;
	}
	else if(shizhongshezhi == 1)
	{
		if((sec % 2) == 0)
		{
			yi = hour / 10;
			er = hour % 10;
		}
		else 
		{
			yi = 11;
			er = 11;
		}
		san = 10;
		si = min / 10;
		wu = min % 10;
		liu = 10;
		qi = sec / 10;
		ba = sec % 10;
	}
	else if(shizhongshezhi == 2)
	{
		if((sec % 2) == 0)
		{
			si = min / 10;
			wu = min % 10;
		}
		else 
		{
			si = 11;
			wu = 11;
		}
		yi = hour / 10;
		er = hour % 10;
		san = 10;		
		liu = 10;
		qi = sec / 10;
		ba = sec % 10;
	}
	else if(shizhongshezhi == 3)
	{
		if((sec % 2) == 0)
		{
			qi = sec / 10;
			ba = sec % 10;			
		}
		else 
		{
			qi = 11;
			ba = 11;
		}
		yi = hour / 10;
		er = hour % 10;
		san = 10;	
		si = min / 10;
		wu = min % 10;		
		liu = 10;
	}
	////////////////
	else if(naozhongshezhi == 1)
	{
		if((sec % 2) == 0)
		{
			yi = hour_n / 10;
			er = hour_n % 10;
		}
		else 
		{
			yi = 11;
			er = 11;
		}
		san = 10;
		si = min_n / 10;
		wu = min_n % 10;
		liu = 10;
		qi = sec_n / 10;
		ba = sec_n % 10;
	}
	else if(naozhongshezhi == 2)
	{
		if((sec % 2) == 0)
		{
			si = min_n / 10;
			wu = min_n % 10;
		}
		else 
		{
			si = 11;
			wu = 11;
		}
		yi = hour_n / 10;
		er = hour_n % 10;
		san = 10;		
		liu = 10;
		qi = sec_n / 10;
		ba = sec_n % 10;
	}
	else if(naozhongshezhi == 3)
	{
		if((sec % 2) == 0)
		{
			qi = sec_n / 10;
			ba = sec_n % 10;			
		}
		else 
		{
			qi = 11;
			ba = 11;
		}
		yi = hour_n / 10;
		er = hour_n % 10;
		san = 10;	
		si = min_n / 10;
		wu = min_n % 10;		
		liu = 10;
	}
	////
	else if(shizhongshezhi == 4)
	{
		yi = 11;
		er = 11;
		san = 11;
		si = 11;
		wu = 11;
		liu = wendu / 10;
		qi = wendu % 10;
		ba = 10;
	}
}