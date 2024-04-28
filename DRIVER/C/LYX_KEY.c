#include "headfile.h" 
/***************************************************************
* 函数名称：按键扫描函数
* 功能说明：
* 参数说明：
* 函数返回：
* 修改时间：2023年2月7日
* 备 注：
***************************************************************/
short key()
{
	uint8 key_sum;
	uint16 time;
	if(gpio_get(PA0) == 0||gpio_get(PA1) == 0||gpio_get(PA2) == 0||gpio_get(PA3) == 0)
	{
		key_sum++;
	}
	else
	{
		key_sum=0;
	}
	if(key_sum <= 10)
	{
		time = 45;
	}
	if(key_sum > 10 && key_sum <= 25)
	{
		time = 30;
	}
	if(key_sum > 25 && key_sum <= 35)
	{
		time = 15;
	}
	if(key_sum > 35)
	{
		time = 1;
	}
	
	if(gpio_get(PA2) == 0)
	{
		DWT_Delay_ms(time);
		return 1;
	}
	else if(gpio_get(PA0) == 0)
	{
		DWT_Delay_ms(time);
		return 2;
	}
	else if(gpio_get(PA1) == 0)
	{
		DWT_Delay_ms(time);
		return 3;
	}
	else if(gpio_get(PA3) == 0)
	{
		DWT_Delay_ms(time);
		return 4;
	}
	else
	{
		return 0;
	}
}
