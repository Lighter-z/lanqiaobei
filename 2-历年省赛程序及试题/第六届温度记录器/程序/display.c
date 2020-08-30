void display()
{
	if(canshushezhi == 1)
	{
		yi = 11;
		er = 11;
		san = 11;
		si = 11;
		wu = 11;
		liu = 10;
		qi = jiange / 10;
		ba = jiange % 10;
	}
	else if(canshushezhi == 0)
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
	else if(canshushezhi == 2)
	{
		caijiwendu = wendu[suoyin];
		yi = 10;
		er = suoyin / 10;
		san = suoyin % 10;
		si = 11;
		wu = 11;
		liu = 10;
		qi = caijiwendu / 10;
		ba = caijiwendu % 10;
	}
}