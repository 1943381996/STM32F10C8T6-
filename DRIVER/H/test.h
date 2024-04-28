#ifndef _test_h_
#define _test_h_

//晶振48M,每个nop是20.83ns
#define DELAY_20_8nS		__nop()		//1个nop是20.8ns
#define DELAY_104nS			DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS //5个nop是104ns
#define Delay_320nS()		DELAY_104nS;DELAY_104nS;DELAY_104nS  //30个nop

void Delay_850nS(void);
void Delay_300uS(void);
void WS2812B_WriteByte(uint8_t dat);
void WS2812B_Reset(void);
#endif

