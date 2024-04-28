#include "headfile.h" 
	
uint8 LED_date_R[LED_NUM];
uint8 LED_date_G[LED_NUM];	
uint8 LED_date_B[LED_NUM];
 
// RGB数据缓存 230是留的reset时间，RESET需要280us以上，传输一个bit需要1.25us，所以至少需要reset bit数>280/1.25 = 224,这里取了230个bit
// 一个颜色需要8个，RGB就是3*8 = 24,也就是一个灯珠的颜色数据
/*
数据样例说明：下面是一个灯芯的GRB数据（实际RGB传输是按照GRB顺序来传输的）
如： 87 87 33 33 87 33 33 33     33 33 33 33 33 33 33 33        87 87 87 87 87 87 87 87
上面24个数据，每8个一组，分别代表G R B
87是1码 33是0码，所以上面就译码成：
1 1 0 0 1 0 0 0    0 0 0 0 0 0 0 0 0   1 1 1 1 1 1 1 1
G = 200				R = 0				b = 255
*/

void ws2812_send_1(uint8 num)
{
	gpio_set(num ,1);
	DWT_Delay(T1H);
	gpio_set(num ,0);
	DWT_Delay(T1L);
}
void ws2812_send_0(uint8 num)
{
	gpio_set(num ,1);
	DWT_Delay(T0H);
	gpio_set(num ,0);
	DWT_Delay(T0L);
}

void ws2812_pwm_int(PWM_TIM num , PWM_Num pin , uint16 freq , uint16 duty)
{
	pwm_init(num , pin , freq , duty);
}
// Sample usage:			DWT_Delay(time);  时钟为52MHZ  T1H  延时650ns 约为31个机器周期
//												     T1L 延时600ns 约为29个机器周期
//                                                   T0H 延时350ns 约为17个机器周期
//                                                   T0L 延时950ns 约为45个机器周期
void ws2812_send_bit(WS2812_PASSAGE LED_passage, uint8 date)
{
	switch(LED_passage)
	{
		case LED_1: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_1_PIN);} else{ ws2812_send_0(LED_1_PIN);} date = date >> 1;}break;
		case LED_2: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_2_PIN);} else{ ws2812_send_0(LED_2_PIN);} date = date >> 1;}break;			
		case LED_3: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_3_PIN);} else{ ws2812_send_0(LED_3_PIN);} date = date >> 1;}break;			
		case LED_4: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_4_PIN);} else{ ws2812_send_0(LED_4_PIN);} date = date >> 1;}break;			
		case LED_5: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_5_PIN);} else{ ws2812_send_0(LED_5_PIN);} date = date >> 1;}break;			
		case LED_6: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_6_PIN);} else{ ws2812_send_0(LED_6_PIN);} date = date >> 1;}break;			
		case LED_7: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_7_PIN);} else{ ws2812_send_0(LED_7_PIN);} date = date >> 1;}break;			
		case LED_8: for(uint8 i=0; i<8; i++){	if((date&0x01) == 0x01){ ws2812_send_1(LED_8_PIN);} else{ ws2812_send_0(LED_8_PIN);} date = date >> 1;}break;				
	}
}

void ws2812_send_RGB(WS2812_PASSAGE LED_passage, uint8 LED_date_num)
{
	ws2812_send_bit(LED_passage, LED_date_G[LED_date_num]);
	ws2812_send_bit(LED_passage, LED_date_R[LED_date_num]);
	ws2812_send_bit(LED_passage, LED_date_B[LED_date_num]);
}
void ws2812_send_rest(WS2812_PASSAGE LED_passage)
{
	switch(LED_passage)
	{
		case LED_1: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;
		case LED_2: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;	
		case LED_3: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;		
		case LED_4: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;		
		case LED_5: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;		
		case LED_6: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;		
		case LED_7: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;		
		case LED_8: gpio_set(LED_1_PIN ,0); DWT_Delay_us(500); break;				
	}
}
