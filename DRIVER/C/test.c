#include "headfile.h"
  
/*---------------------------------------------------------------------------
@Function   :Delay_850nS
@Description:��⿪�س�ʼ��
@Input      :��
@Retrun     :��
@Others     :T1H T0L ʱ����  580ns~1.6us,ȡ850ns   ʵ��855us
----------------------------------------------------------------------------*/
void Delay_850nS(void)
{
	//���뺯�����õ�ʱ��ԼΪ310ns
	DELAY_104nS;
	DELAY_104nS;
	Delay_320nS();
	DELAY_20_8nS;
}
/*---------------------------------------------------------------------------
@Function   :Delay_300uS
@Description:
@Input      :��
@Retrun     :��
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
@Description:дһ���ֽ�
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_WriteByte(uint8_t dat)
{
	u8 i;
	for (i=0;i<8;i++)
	{
		//�ȷ��͸�λ
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
void WS2812B_Reset(void)          //��λ����
{
	gpio_set(PA11 ,0);
	Delay_300uS();
}