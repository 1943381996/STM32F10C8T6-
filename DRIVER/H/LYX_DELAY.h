#ifndef _LYX_DELAY_H_
#define _LYX_DELAY_H_
#include "headfile.h"

//���˱�д��DWT�Ĵ������ã����ܻ�������벻���Ĵ��������ʹ�ã���
/**********************************************************************
/*         ʱ�����ؼĴ�������
/*********************************************************************/
/*
��Cortex-M������һ�������DWT(Data Watchpoint and Trace)��
��������һ��32λ�ļĴ�����CYCCNT������һ�����ϵļ�������
��¼�����ں�ʱ�����еĸ�������ܼ�¼��ʱ��Ϊ��
82.59s=2��32�η�/52000000
(�����ں�Ƶ��Ϊ52M���ں���һ�ε�ʱ����Ϊ1/52M=19.2ns)
��CYCCNT���֮�󣬻���0���¿�ʼ���ϼ�����
ʹ��CYCCNT�����Ĳ������裺
1����ʹ��DWT���裬����������ں˵��ԼĴ���DEMCR��λ24���ƣ�д1ʹ��
2��ʹ��CYCCNT�Ĵ���֮ǰ������0
3��ʹ��CYCCNT�Ĵ����������DWT_CTRL(�����Ϻ궨��ΪDWT_CR)��λ0���ƣ�д1ʹ��
*/

#define  DWT_CR                          *(uint32_t*)0xE0001000 //DWT ���ƼĴ�����ַ
#define  DWT_CYCCNT                      *(uint32_t*)0xE0001004//
#define  DEM_CR                          *(uint32_t*)0xE000EDFC
//������ʹ��λ
#define  DEM_CR_TRCENA                  (1<<24)
#define  DWT_CR_CYCCNTENA               (1<<0)

void DWT_init(void);
uint32_t DWT_TS_GET(void);
void DWT_Delay_ms(uint32_t time_ms);
void DWT_Delay_us(uint32_t time_us);
void DWT_Delay(uint32_t time);

#endif
