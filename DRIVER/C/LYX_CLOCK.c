#include "headfile.h" 

void CLOCK_int(void)
{
				/* 开启HSI 即内部晶振时钟 */
        RCC->CR |= RCC_CR_HSION ;
				RCC->CR |= RCC_CR_HSITRIM<<3 ;
        /*选择HSI为PLL的时钟源HSI必须2分频给PLL*/
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
        /*PLLCLK=8/2*12=48MHz  设置倍频得到时钟源PLL的频率*/
        RCC->CFGR |= RCC_CFGR_PLLMULL12;			//设置倍频后的频率
        /* PLL不分频输出*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
        /* 使能 PLL时钟 */
        RCC->CR |= RCC_CR_PLLON;
        /* 等待PLL时钟就绪*/
        while ( ( RCC->CR & RCC_CR_PLLRDY ) == 0 )
        {
        }
        /* 选择PLL为系统时钟的时钟源 */
        RCC->CFGR &= ~ RCC_CFGR_SW ;
        RCC->CFGR |= 	 RCC_CFGR_SW_PLL;
        /* 等到PLL成为系统时钟的时钟源*/
        while ( ( RCC->CFGR &  RCC_CFGR_SWS ) != ( uint32_t ) 0x08 )
        { }
//				/* APB1时钟分频 */
//				RCC->CFGR =   RCC_CFGR_PPRE1_DIV2;  							
				/* ADC时钟分频 */
				RCC->CFGR &= ~ RCC_CFGR_ADCPRE;
        RCC->CFGR |=   RCC_CFGR_ADCPRE_DIV8;

}
