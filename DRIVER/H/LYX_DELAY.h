#ifndef _LYX_DELAY_H_
#define _LYX_DELAY_H_
#include "headfile.h"

//个人编写的DWT寄存器配置，可能会出现意想不到的错误，请谨慎使用！！
/**********************************************************************
/*         时间戳相关寄存器定义
/*********************************************************************/
/*
在Cortex-M里面有一个外设叫DWT(Data Watchpoint and Trace)，
该外设有一个32位的寄存器叫CYCCNT，它是一个向上的计数器，
记录的是内核时钟运行的个数，最长能记录的时间为：
82.59s=2的32次方/52000000
(假设内核频率为52M，内核跳一次的时间大概为1/52M=19.2ns)
当CYCCNT溢出之后，会清0重新开始向上计数。
使能CYCCNT计数的操作步骤：
1、先使能DWT外设，这个由另外内核调试寄存器DEMCR的位24控制，写1使能
2、使能CYCCNT寄存器之前，先清0
3、使能CYCCNT寄存器，这个由DWT_CTRL(代码上宏定义为DWT_CR)的位0控制，写1使能
*/

#define  DWT_CR                          *(uint32_t*)0xE0001000 //DWT 控制寄存器地址
#define  DWT_CYCCNT                      *(uint32_t*)0xE0001004//
#define  DEM_CR                          *(uint32_t*)0xE000EDFC
//定义需使能位
#define  DEM_CR_TRCENA                  (1<<24)
#define  DWT_CR_CYCCNTENA               (1<<0)

void DWT_init(void);
uint32_t DWT_TS_GET(void);
void DWT_Delay_ms(uint32_t time_ms);
void DWT_Delay_us(uint32_t time_us);
void DWT_Delay(uint32_t time);

#endif
