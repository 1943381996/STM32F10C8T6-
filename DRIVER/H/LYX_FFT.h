#ifndef _LYX_FFT_h_
#define _LYX_FFT_h_

#include "headfile.h" 
#define NPT 256             /* 采样点数 */
extern uint32 lBufInArray[NPT];    /* FFT 运算的输入数组 */
extern uint32 lBufOutArray[NPT/2]; /* FFT 运算的输出数组 */
extern uint32 lBufMagArray[NPT/2]; /* 各次谐波的幅值 */

extern uint32 sample_arr; 
extern uint32 sample_psc; 
extern uint32 frequency_max_position; 

extern float sample_frequency; 
extern float wave_frequency;

extern float sample_frequency; 
extern float wave_frequency; 

extern uint8 commond_flag;

void adc_sample(void);
void GetPowerMag(void);
void wave_frequency_calculate(void);
void FFT_disply(void);

#endif
