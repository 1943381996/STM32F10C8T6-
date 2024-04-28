#include "headfile.h"

int main()
{	
	CLOCK_int();
//	OLED_SPI_init();
//	DMA_init();
//	commond_flag = 0;
//	gpio_init(PA0, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PA1, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PA2, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PA3, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
	
//	gpio_init(PA11, GPO, 0, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
	gpio_init(PA8, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PB9, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PB7, GPO, 0, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
//	gpio_init(PB6, GPO, 0, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);
	
//	pwm_init(PWM_TIM4 , TIM4_CH2_PB07 , 1 , 5000);
//	pwm_init(PWM_TIM4 , TIM4_CH1_PB06 , 5 , 5000);
	
//	adc_init(ADC_1, ADC1_CH04_A04);
	
//	LED_date_R[0] = 0x00;
//	LED_date_G[0] = 0x00;
//	LED_date_B[0] = 0x0F;
//	uint16 date=1;
	while(1)
	{
			gpio_set(PA8, 1);
		
//		pwm_duty(PWM_TIM4 , TIM4_CH1_PB06 , 1000);
//		oled_uint16(0, 0, date);
//		oled_uint16(45, 0, adc_get(ADC_1, ADC1_CH04_A04));
		
//		adc_sample();
		
		
//		FFT_disply();
//		OLED_SPI_Write_DAT(0x01);
//		ws2812_send_RGB(LED_1, 0);
//		ws2812_send_rest(LED_1);
//		WS2812B_WriteByte(0x0f);
//		WS2812B_WriteByte(0x20);
//		WS2812B_WriteByte(0x03);
//		WS2812B_Reset();
//		DWT_Delay_ms(500);
//		switch(key())
//		{
//			case 1:
//			{
//				date+=1;
//				break;
//			}
//			case 2:
//			{
//				date-=1;
//				break;
//			}
//		}

	}
}
