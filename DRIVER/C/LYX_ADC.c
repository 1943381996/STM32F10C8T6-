#include "headfile.h" 

ADC_TypeDef *adc_index[2] = {ADC1, ADC2};

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC��ʼ��	
// @param		
// @return	void
// Sample usage: adc_init(ADC_1, ADC1_CH00_A00);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADC_Num num, ADC_CH pin)
{
	uint8 C_H = pin>>8;																	//��ȡͨ����
	gpio_init((GPIO_Num)(pin&0xff), GPI, 0, GPI_ANAOG_IN, GPIO_SPEED_50MHZ);			//���ų�ʼ��Ϊģ������
	RCC->APB2ENR  |= 0x01 << (num + 9);													//ADCͨ��ʱ��ʹ��
	RCC->APB2RSTR |= 0X01 << (num + 9);													//ADCͨ���Ĵ�����λ
	RCC->APB2RSTR &= ~(0x01<<(9+num));													//ADCͨ���Ĵ�����λ���
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;														//ADCͨ���Ĵ�����Ƶ�������
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;													//ADCͨ���Ĵ�����Ƶ����
	adc_index[num]->CR2 |= ADC_CR2_EXTSEL;												//ADC��������ͨ����ת��
	adc_index[num]->CR2 |= ADC_CR2_EXTTRIG;												//ADCͨ��ת���ⲿ�¼�����
	adc_index[num]->CR1 &= ~ADC_CR1_DUALMOD;											//ADCͨ��˫ģʽѡ��
	ADC1 -> CR2 |= ADC_CR2_DMA ; 														//����DMAֱ�ӷ�������
	ADC1 -> CR1 |= ADC_CR1_SCAN ;														//����ɨ��ģʽ
	
	
	if(num == 0&&C_H == 16)	ADC1->CR2 |= ADC_CR2_TSVREFE;								//�¶Ⱥ͵�ѹ������ʹ��
	if(C_H>10)	adc_index[num]->SMPR2 |= 0x07<<(3*C_H);									//����ʱ������Ĵ���17-10
	else				adc_index[num]->SMPR1 |= 0x07<<(3*(C_H-10));					//����ʱ������Ĵ���0-9
							adc_index[num]->CR2 |= ADC_CR2_ADON;						//ADCͨ��ת������
							adc_index[num]->CR2 |= ADC_CR2_RSTCAL;						//�ȴ�ADCͨ��ת��λУ׼
	while(adc_index[num]->CR2 & ADC_CR2_RSTCAL);										//ADCͨ����λУ׼
	adc_index[num]->CR2 |= ADC_CR2_CAL;													//ADCͨ��תУ׼
	while(adc_index[num]->CR2 & ADC_CR2_CAL);											//�ȴ�A/DУ׼
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		ADCת��һ��
// @param		
// @return	void
// Sample usage: adc_get(ADC_1, ADC1_CH00_A00);
//-------------------------------------------------------------------------------------------------------------------
uint32 adc_get(ADC_Num num, ADC_CH pin)
{
	uint8 C_H = pin>>8;																	//��ȡADCͨ��
	adc_index[num]->SQR3 &= ADC_SQR3_clear;												//ADCͨ���������ͨ����ת��
	adc_index[num]->SQR3 |= C_H;														//ADCͨ���������мĴ�������
	adc_index[num]->CR2 |= ADC_CR2_SWSTART;												//ADCͨ������ת����ʼ
//	while(!(adc_index[num]->SR&1<<1));													//�ȴ�ADC����ͨ����ʼλ
	return adc_index[num]->DR & 0xFFFFFF;
}
