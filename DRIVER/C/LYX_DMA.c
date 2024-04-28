#include "headfile.h"

//DMA_TypeDef *dma_group[2] = {DMA1, DMA2};	//ǿת��Ϊָ�����͵Ľṹ��
//DMA��ʼ��
//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA����ADC����
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       
//-------------------------------------------------------------------------------------------------------------------
void DMA_init(void)
{
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN ; 									//DMAʱ��ʹ��

	DMA1_Channel1 -> CMAR |= (uint32)(&(lBufInArray[0])) ;					//����DMA�洢�������ַ
	DMA1_Channel1 -> CPAR |= (uint32)(&(ADC1->DR)) ;						//����DMA���贫���ַ
  
	DMA1_Channel1 -> CCR |= DMA_CCR1_PL ;									//����DMAͨ�����ȼ�
	DMA1_Channel1 -> CCR |= DMA_CCR1_MSIZE_0 ;								//����DMA�洢�����ݿ��
	DMA1_Channel1 -> CCR |= DMA_CCR1_PSIZE_0 ;								//����DMA�������ݿ��
	DMA1_Channel1 -> CCR |= DMA_CCR1_MINC ;    								//���ô洢����ַ����ģʽ
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_PINC ;    							//���ô������ַ����ģʽ
	DMA1_Channel1 -> CCR |= DMA_CCR1_CIRC ;   								//����ѭ��ģʽ
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_DIR ;   								//���ô��䷽��	
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_PINC ;    							//���ô洢����ַ����ģʽ

	DMA1_Channel1 -> CNDTR |= (DMA_CNDTR1_NDT &0X00FF) >> 1 ;				 //���ô�������
	
	DMA1_Channel1 ->CCR |= DMA_CCR1_TCIE ;									//DMAͨ��1��������ж�ʹ��
	DMA1_Channel1 ->CCR |= DMA_CCR1_EN ;									//DMAͨ��1ʹ��
	
}
