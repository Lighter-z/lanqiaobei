void display()
{
	if((sec % 2) == 0)
	{
		yi = hour/ 10;
		er = hour % 10;
		san = 10;
		si = min / 10;
		wu = min % 10;
		liu = 10;
		qi = sec / 10;
		ba = sec % 10;
	}
	else if((sec / 2) != 0)
	{
		yi = nian / 10;
		er = nian % 10;
		san = 10;
		si = month / 10;
		wu = month % 10;
		liu = 10;
		qi = date / 10;
		ba = date % 10;
	}
}