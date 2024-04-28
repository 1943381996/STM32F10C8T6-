#include "headfile.h" 

ADC_TypeDef *adc_index[2] = {ADC1, ADC2};

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC初始化	
// @param		
// @return	void
// Sample usage: adc_init(ADC_1, ADC1_CH00_A00);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADC_Num num, ADC_CH pin)
{
	uint8 C_H = pin>>8;																	//获取通道号
	gpio_init((GPIO_Num)(pin&0xff), GPI, 0, GPI_ANAOG_IN, GPIO_SPEED_50MHZ);			//引脚初始化为模拟输入
	RCC->APB2ENR  |= 0x01 << (num + 9);													//ADC通道时钟使能
	RCC->APB2RSTR |= 0X01 << (num + 9);													//ADC通道寄存器复位
	RCC->APB2RSTR &= ~(0x01<<(9+num));													//ADC通道寄存器复位清除
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;														//ADC通道寄存器分频配置清除
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;													//ADC通道寄存器分频配置
	adc_index[num]->CR2 |= ADC_CR2_EXTSEL;												//ADC启动规则通道组转换
	adc_index[num]->CR2 |= ADC_CR2_EXTTRIG;												//ADC通道转换外部事件配置
	adc_index[num]->CR1 &= ~ADC_CR1_DUALMOD;											//ADC通道双模式选择
	ADC1 -> CR2 |= ADC_CR2_DMA ; 														//启动DMA直接访问数据
	ADC1 -> CR1 |= ADC_CR1_SCAN ;														//启动扫描模式
	
	
	if(num == 0&&C_H == 16)	ADC1->CR2 |= ADC_CR2_TSVREFE;								//温度和电压传感器使能
	if(C_H>10)	adc_index[num]->SMPR2 |= 0x07<<(3*C_H);									//配置时间采样寄存器17-10
	else				adc_index[num]->SMPR1 |= 0x07<<(3*(C_H-10));					//配置时间采样寄存器0-9
							adc_index[num]->CR2 |= ADC_CR2_ADON;						//ADC通道转换开启
							adc_index[num]->CR2 |= ADC_CR2_RSTCAL;						//等待ADC通道转复位校准
	while(adc_index[num]->CR2 & ADC_CR2_RSTCAL);										//ADC通道复位校准
	adc_index[num]->CR2 |= ADC_CR2_CAL;													//ADC通道转校准
	while(adc_index[num]->CR2 & ADC_CR2_CAL);											//等待A/D校准
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC转换一次
// @param		
// @return	void
// Sample usage: adc_get(ADC_1, ADC1_CH00_A00);
//-------------------------------------------------------------------------------------------------------------------
uint32 adc_get(ADC_Num num, ADC_CH pin)
{
	uint8 C_H = pin>>8;																	//获取ADC通道
	adc_index[num]->SQR3 &= ADC_SQR3_clear;												//ADC通道清除规则通道组转换
	adc_index[num]->SQR3 |= C_H;														//ADC通道规则序列寄存器配置
	adc_index[num]->CR2 |= ADC_CR2_SWSTART;												//ADC通道规则转换开始
//	while(!(adc_index[num]->SR&1<<1));													//等待ADC规则通道开始位
	return adc_index[num]->DR & 0xFFFFFF;
}
