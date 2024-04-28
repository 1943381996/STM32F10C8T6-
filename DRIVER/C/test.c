#include "headfile.h"
  
/*---------------------------------------------------------------------------
@Function   :Delay_850nS
@Description:检测开关初始化
@Input      :无
@Retrun     :无
@Others     :T1H T0L 时间在  580ns~1.6us,取850ns   实测855us
----------------------------------------------------------------------------*/
void Delay_850nS(void)
{
	//进入函数所用的时间约为310ns
	DELAY_104nS;
	DELAY_104nS;
	Delay_320nS();
	DELAY_20_8nS;
}
/*---------------------------------------------------------------------------
@Function   :Delay_300uS
@Description:
@Input      :无
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void Delay_300uS(void)
{
	uint8_t i;
	while(i--)
	{
		Delay_320nS();
	}
}
/*---------------------------------------------------------------------------
@Function   :WS2812B_WriteByte
@Description:写一个字节
@Input      :无
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_WriteByte(uint8_t dat)
{
	u8 i;
	for (i=0;i<8;i++)
	{
		//先发送高位
		if (dat & 0x80) //1
		{
			gpio_set(PA11 ,1);
			Delay_850nS(); //T1H
			gpio_set(PA11 ,0);
			Delay_320nS(); //T1L
		}
		else	//0
		{
			gpio_set(PA11 ,1);
			Delay_320nS(); //T0H
			gpio_set(PA11 ,0);
			Delay_850nS(); //T0L
		}
		dat<<=1;
	}
}
void WS2812B_Reset(void)          //复位函数
{
	gpio_set(PA11 ,0);
	Delay_300uS();
}