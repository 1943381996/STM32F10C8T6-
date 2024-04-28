#include "headfile.h" 

void CLOCK_int(void)
{
				/* ����HSI ���ڲ�����ʱ�� */
        RCC->CR |= RCC_CR_HSION ;
				RCC->CR |= RCC_CR_HSITRIM<<3 ;
        /*ѡ��HSIΪPLL��ʱ��ԴHSI����2��Ƶ��PLL*/
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_Div2;
        /*PLLCLK=8/2*12=48MHz  ���ñ�Ƶ�õ�ʱ��ԴPLL��Ƶ��*/
        RCC->CFGR |= RCC_CFGR_PLLMULL12;			//���ñ�Ƶ���Ƶ��
        /* PLL����Ƶ���*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
        /* ʹ�� PLLʱ�� */
        RCC->CR |= RCC_CR_PLLON;
        /* �ȴ�PLLʱ�Ӿ���*/
        while ( ( RCC->CR & RCC_CR_PLLRDY ) == 0 )
        {
        }
        /* ѡ��PLLΪϵͳʱ�ӵ�ʱ��Դ */
        RCC->CFGR &= ~ RCC_CFGR_SW ;
        RCC->CFGR |= 	 RCC_CFGR_SW_PLL;
        /* �ȵ�PLL��Ϊϵͳʱ�ӵ�ʱ��Դ*/
        while ( ( RCC->CFGR &  RCC_CFGR_SWS ) != ( uint32_t ) 0x08 )
        { }
//				/* APB1ʱ�ӷ�Ƶ */
//				RCC->CFGR =   RCC_CFGR_PPRE1_DIV2;  							
				/* ADCʱ�ӷ�Ƶ */
				RCC->CFGR &= ~ RCC_CFGR_ADCPRE;
        RCC->CFGR |=   RCC_CFGR_ADCPRE_DIV8;

}
