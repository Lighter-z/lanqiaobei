void display()
{
	if(wenshi == 0)
	{
		yi = 10;
		er = moshi;
		san = 10;
		si = 11;
		wu = shengyushijian / 1000;
		liu = shengyushijian % 1000 / 100;
		qi = shengyushijian % 100 / 10;
		ba = shengyushijian % 10;
	}
	else if(wenshi == 1)
	{
		yi = 10;
		er = 4;
		san = 10;
		si = 11;
		wu = 11;
		liu = wendu / 10;
		qi = wendu % 10;
		ba = 10;
	}
	if(moshi == 1)
	{
		zhankongbi = 2;
	}
	else if(moshi == 2)
	{
		zhankongbi = 3;
	}
	else if(moshi == 3)
	{
		zhankongbi = 7;
	}
}