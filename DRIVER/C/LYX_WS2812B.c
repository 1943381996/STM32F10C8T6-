#include "headfile.h" 
	
uint8 LED_date_R[LED_NUM];
uint8 LED_date_G[LED_NUM];	
uint8 LED_date_B[LED_NUM];
 
// RGB���ݻ��� 230������resetʱ�䣬RESET��Ҫ280us���ϣ�����һ��bit��Ҫ1.25us������������Ҫreset bit��>280/1.25 = 224,����ȡ��230��bit
// һ����ɫ��Ҫ8����RGB����3*8 = 24,Ҳ����һ���������ɫ����
/*
��������˵����������һ����о��GRB���ݣ�ʵ��RGB�����ǰ���GRB˳��������ģ�
�磺 87 87 33 33 87 33 33 33     33 33 33 33 33 33 33 33        87 87 87 87 87 87 87 87
����24�����ݣ�ÿ8��һ�飬�ֱ����G R B
87��1�� 33��0�룬�������������ɣ�
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
// Sample usage:			DWT_Delay(time);  ʱ��Ϊ52MHZ  T1H  ��ʱ650ns ԼΪ31����������
//												     T1L ��ʱ600ns ԼΪ29����������
//                                                   T0H ��ʱ350ns ԼΪ17����������
//                                                   T0L ��ʱ950ns ԼΪ45����������
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
