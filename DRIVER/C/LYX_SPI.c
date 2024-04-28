#include "headfile.h"

//���SPI

//-------------------------------------------------------------------------------------------------------------------
// @brief		SPI_��ʼ��
// @param		
// @return	void
// Sample usage: SPI_OLED_int();
//-------------------------------------------------------------------------------------------------------------------
void SPI_OLED_init (void)
{
	gpio_init (SPI_PIN_SCL, GPO,1,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
	gpio_init (SPI_PIN_SDA, GPO,0,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
  	gpio_init (SPI_PIN_RST, GPO,1,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
  	gpio_init (SPI_PIN_DC , GPO,1,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
  	gpio_init (SPI_PIN_CS , GPO,1,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
    
	SPI_SCL(1);
	SPI_RST(0);
	DWT_Delay_ms(50);
	SPI_RST(1);

}
//-------------------------------------------------------------------------------------------------------------------
// @brief		SPI_��ʼ
// @param		
// @return	void
// Sample usage: SPI_Start();
//-------------------------------------------------------------------------------------------------------------------
void SPI_Start(void)
{
	SPI_CS(0); //ʹ���źŶˣ�����ʱ����ʹ��
	SPI_DC(1);
	SPI_SCL(0);
}	  
//-------------------------------------------------------------------------------------------------------------------
// @brief		SPI_ֹͣ
// @param		
// @return	void
// Sample usage: SPI_Stop();
//-------------------------------------------------------------------------------------------------------------------
void SPI_Stop(void)
{
	SPI_CS(1); //ʹ���źŶˣ�����ʱ����ʹ��
}
