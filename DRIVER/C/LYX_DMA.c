#include "headfile.h"

//DMA_TypeDef *dma_group[2] = {DMA1, DMA2};	//强转换为指针类型的结构体
//DMA初始化
//-------------------------------------------------------------------------------------------------------------------
//  @brief      DMA传输ADC配置
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       
//-------------------------------------------------------------------------------------------------------------------
void DMA_init(void)
{
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN ; 									//DMA时钟使能

	DMA1_Channel1 -> CMAR |= (uint32)(&(lBufInArray[0])) ;					//配置DMA存储器传输地址
	DMA1_Channel1 -> CPAR |= (uint32)(&(ADC1->DR)) ;						//配置DMA外设传输地址
  
	DMA1_Channel1 -> CCR |= DMA_CCR1_PL ;									//配置DMA通道优先级
	DMA1_Channel1 -> CCR |= DMA_CCR1_MSIZE_0 ;								//配置DMA存储器数据宽度
	DMA1_Channel1 -> CCR |= DMA_CCR1_PSIZE_0 ;								//配置DMA外设数据宽度
	DMA1_Channel1 -> CCR |= DMA_CCR1_MINC ;    								//配置存储器地址增量模式
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_PINC ;    							//配置存外设地址增量模式
	DMA1_Channel1 -> CCR |= DMA_CCR1_CIRC ;   								//配置循环模式
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_DIR ;   								//配置传输方向	
	DMA1_Channel1 -> CCR &= ~DMA_CCR1_PINC ;    							//配置存储器地址增量模式

	DMA1_Channel1 -> CNDTR |= (DMA_CNDTR1_NDT &0X00FF) >> 1 ;				 //配置传输数量
	
	DMA1_Channel1 ->CCR |= DMA_CCR1_TCIE ;									//DMA通道1传输完成中断使能
	DMA1_Channel1 ->CCR |= DMA_CCR1_EN ;									//DMA通道1使能
	
}
