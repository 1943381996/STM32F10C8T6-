#ifndef _LYX_PWM_h_
#define _LYX_PWM_h_

#include "headfile.h"

/*PWM引脚枚举类型*/
typedef enum 
{
	//高级定时器普通通道
	TIM1_CH1_PA08 = 0x0008,
	TIM1_CH2_PA09 = 0x0109,
	TIM1_CH3_PA10 = 0x020A,
	TIM1_CH4_PA11 = 0x030B,
	//高级定时器互补通道
	TIM1_CH1N_PB13 = 0x001C,
	TIM1_CH2N_PB14 = 0x011D,
	TIM1_CH3N_PB15 = 0x021E,
	//通用定时器通道                     
	TIM2_CH1_PA00 = 0x0000, TIM2_CH1_PA15 = 0x001F,
	TIM2_CH2_PA01 = 0x0101,	TIM2_CH2_PB03 = 0x0113,
	TIM2_CH3_PA02 = 0x0202,	TIM2_CH3_PB10 = 0x021A,
	TIM2_CH4_PA03 = 0x0303,	TIM2_CH4_PB11 = 0x031B,
	                                             
	TIM3_CH1_PA06 = 0x0006,	TIM3_CH1_PB04 = 0x0014,
	TIM3_CH2_PA07 = 0x0107,	TIM3_CH2_PB05 = 0x0115,
	TIM3_CH3_PB00 = 0x0210,
	TIM3_CH4_PB01 = 0x0311,
	                      
	TIM4_CH1_PB06 = 0x0016,
	TIM4_CH2_PB07 = 0x0117,
	TIM4_CH3_PB08 = 0x0218,
	TIM4_CH4_PB09 = 0x0319,
	
}PWM_Num;
/*定时器枚举类型*/
typedef enum
{
	
	PWM_TIM1,//高级定时器
	PWM_TIM2,//通用定时器
	PWM_TIM3,//通用定时器
	PWM_TIM4,//通用定时器
	
}PWM_TIM;


void pwm_init(PWM_TIM num , PWM_Num pin , uint16 freq , uint16 duty);
void pwm_duty(PWM_TIM num , PWM_Num pin , uint16 duty);

#endif

