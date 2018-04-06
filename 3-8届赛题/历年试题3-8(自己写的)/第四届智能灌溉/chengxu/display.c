void display()
{
	if(zidong == 1)
	{
		
		min = shijian[1];
		hour = shijian[2];
		yi = hour / 10;
		er = hour % 10;
		san = 10;
		si = min / 10;
		wu = min % 10;
		liu = 11;
		qi = shidu / 10;
		ba = shidu % 10;
		if(shidu < fazhi)
		{
			P2 = 0x80;
			P0 = 0xfe;
			P2 = 0xa0;
			P0 = 0x10;
		}
		else if(shidu > fazhi)
		{
			P2 = 0x80;
			P0 = 0xff;
			P2 = 0xa0;
			P0 = 0x00;
		}
		if(fazhitiaozheng == 1)
		{
			yi = 10;
			er = 10;
			san = 11;
			si = 11;
			wu = 11;
			liu = 11;
			qi = fazhi / 10;
			ba = fazhi % 10;
		}
	}
	
	if(zidong == 0)
	{
		min = shijian[1];
		hour = shijian[2];
		yi = hour / 10;
		er = hour % 10;
		san = 10;
		si = min / 10;
		wu = min % 10;
		liu = 11;
		qi = shidu / 10;
		ba = shidu % 10;
		if(tixing == 1)
		{
			if(shidu < fazhi)
			{
				P2 = 0x80;
				P0 = 0xfd;
				P2 = 0xa0;
				temp = temp | 0x40;
			P0 = temp;
			}
			else if(shidu > fazhi)
			{
				P2 = 0x80;
				P0 = 0xff;
				P2 = 0xa0;
				temp = temp & 0x00;
			P0 = temp;
			}
		}
		else if(tixing == 0)
		{
				P2 = 0x80;
				P0 = 0xff;
				P2 = 0xa0;
				temp = temp & 0x00;
			P0 = temp;
		}
		if(guan == 1)
		{
			P2 = 0xa0;
			temp = temp & 0x00;
			P0 = temp;
		}
		else if(guan == 0)
		{
			P2 = 0xa0;
			temp = temp | 0x10;
			P0 = temp;
		}
	}
}