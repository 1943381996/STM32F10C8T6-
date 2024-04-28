#ifndef _LYX_WS2812B_H_
#define _LYX_WS2812B_H_

#include "headfile.h" 

#define LED_NUM	11				// LEDµ∆÷È ˝¡ø
//#define T1H 31
//#define T1L 29
//#define T0H 17
//#define T0L 45
#define T1H 41
#define T1L 14
#define T0H 15
#define T0L 41

#define LED_1_PIN PA11
#define LED_2_PIN PA10
#define LED_3_PIN PA9
#define LED_4_PIN PA8

#define LED_5_PIN PB1
#define LED_6_PIN PB0
#define LED_7_PIN PA7
#define LED_8_PIN PA6

extern uint8 LED_date_R[LED_NUM];
extern uint8 LED_date_G[LED_NUM];	
extern uint8 LED_date_B[LED_NUM];

typedef enum
{
	LED_1  = 0x01,
	LED_2  = 0x02,
	LED_3  = 0x03,
	LED_4  = 0x04,
	LED_5  = 0x05,
	LED_6  = 0x06,
	LED_7  = 0x07,
	LED_8  = 0x08,
	
}WS2812_PASSAGE;


void ws2812_send_bit(WS2812_PASSAGE LED_passage, uint8 date);
void ws2812_send_RGB(WS2812_PASSAGE LED_passage, uint8 LED_date_num);
void ws2812_send_rest(WS2812_PASSAGE LED_passage);
void ws2812_send_1(uint8 num);
void ws2812_send_0(uint8 num);

#endif

