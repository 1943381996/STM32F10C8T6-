#include "headfile.h" 
/***************************************************************
* �������ƣ�����ɨ�躯��
* ����˵����
* ����˵����
* �������أ�
* �޸�ʱ�䣺2023��2��7��
* �� ע��
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
