#ifndef _test_h_
#define _test_h_

//����48M,ÿ��nop��20.83ns
#define DELAY_20_8nS		__nop()		//1��nop��20.8ns
#define DELAY_104nS			DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS //5��nop��104ns
#define Delay_320nS()		DELAY_104nS;DELAY_104nS;DELAY_104nS  //30��nop

void Delay_850nS(void);
void Delay_300uS(void);
void WS2812B_WriteByte(uint8_t dat);
void WS2812B_Reset(void);
#endif

