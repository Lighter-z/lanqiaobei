void keyscan()
{
	unsigned char temp;
	P3 = 0x7f;P44 = 0;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0x7e:num = 0;key_flag = 1;break;
				case 0x7d:num = 3;key_flag = 1;break;
				case 0x7b:num = 6;key_flag = 1;break;
				case 0x77:num = 9;key_flag = 1;break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	P44 = 1;P3 = 0xbf;P42 = 0;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0xbe:num = 1;key_flag = 1;break;
				case 0xbd:num = 4;key_flag = 1;break;
				case 0xbb:num= 7;key_flag = 1;break;
				case 0xb7:if(shezhi == 0)
				{
					shezhi = 1;
					EA = 0;
					P2 = 0x80;
					P0 = 0xff;
					yi = 10;
					er = 11;
					san = 11;
					si = 11;
					wu = 11;
					liu = 10;
					qi = 11;
					ba = 11;
				}
				else if(shezhi == 1)
				{
					shezhi = 0;
					EA = 1;
					P2 = 0x80;
					P0 = 0xff;
					wendumax = er * 10 + san;
					wendumin = qi * 10 + ba;
				};break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
	
	
	P42 = 1;P3 = 0xdf;
	temp = P3;
	temp &= 0x0f;
	if(temp != 0x0f)
	{
		Delay1ms();
		temp = P3;
		temp &= 0x0f;
		if(temp != 0x0f)
		{
			temp = P3;
			switch(temp)
			{
				case 0xde:num = 2;key_flag = 1;break;
				case 0xdd:num = 5;key_flag = 1;break;
				case 0xdb:num = 8;key_flag = 1;break;
				case 0xd7:if(qingchu == 0)
				{
					qingchu = 1;
				};break;
			}
		}
		while(temp != 0x0f)
		{
			temp = P3;
			temp &= 0x0f;
		}
	}
}