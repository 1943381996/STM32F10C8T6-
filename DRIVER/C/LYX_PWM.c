#include "headfile.h" 
TIM_TypeDef *pwm_tim_index[4] = {TIM1,TIM2,TIM3,TIM4};
//-------------------------------------------------------------------------------------------------------------------
// @brief		pwm��ʼ������
// @param	    num	          			ģ���
// @param	    pin	    			  		����
// @param	    freq	    					Ƶ��
// @param	    duty	    					��ʼռ�ձ�
// @return		void                       
// Sample usage: 		pwm_init(PWM_TIM1 , TIM1_CH1_PA08 , 50,5000);
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWM_TIM num , PWM_Num pin , uint16 freq , uint16 duty)
{	 
	switch(num)
	{																	
		case PWM_TIM1:
		{
			RCC  ->APB2ENR |= RCC_APB2ENR_TIM1EN ,TIM1->BDTR|= TIM_BDTR_MOE;			//ʹ�ܶ�ʱ��1ʱ��
			gpio_init ((pin&0x3F),GPO,1,GPO_AF_PUSH_PULL,GPIO_SPEED_50MHZ);

				 if((pin&0x30) == 0x00){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM1_REMAP;																		 	 }//���TIM1��AFIO����,����TIM1��AFIO����
			else if((pin&0x30) == 0x10){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM1_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM1_REMAP_0;}
			else if((pin&0x30) == 0x20){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM1_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM1_REMAP_1;}
			else if((pin&0x30) == 0x30){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM1_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM1_REMAP  ;}
			else    									 {;;}
																				
			TIM1 ->PSC = 52000/1000;																							//��Ƶ������
			TIM1 ->ARR = 66;																										//�Զ�װ�ؼĴ�������
			
				 if((pin&0x0300) == 0x0000){TIM1 ->CCMR1 |=	(TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1); TIM1 ->CCMR1 |= TIM_CCMR1_OC1PE; TIM1 ->CCR1 |= duty; TIM1 ->CCER |= TIM_CCER_CC1E; }
			else if((pin&0x0300) == 0x0100){TIM1 ->CCMR1 |=	(TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1); TIM1 ->CCMR1 |= TIM_CCMR1_OC2PE; TIM1 ->CCR2 |= duty; TIM1 ->CCER |= TIM_CCER_CC2E; }
			else if((pin&0x0300) == 0x0200){TIM1 ->CCMR2 |=	(TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1); TIM1 ->CCMR2 |= TIM_CCMR2_OC3PE; TIM1 ->CCR3 |= duty; TIM1 ->CCER |= TIM_CCER_CC3E; }
			else if((pin&0x0300) == 0x0300){TIM1 ->CCMR2 |=	(TIM_CCMR2_OC4M); TIM1 ->CCMR2 |= TIM_CCMR2_OC4PE; TIM1 ->CCR4 |= duty; TIM1 ->CCER |= TIM_CCER_CC4E; }
			else													 {;;}
			
			TIM1 ->CR1   |= TIM_CR1_CEN ;	
			TIM1 ->CR1   |=	TIM_CR1_ARPE;			
			break;
		}
		case PWM_TIM2:
		{
			RCC  ->APB1ENR |= RCC_APB1ENR_TIM2EN;																	//ʹ�ܶ�ʱ��2ʱ��
			gpio_init ((pin&0x3F),GPO,1,GPO_AF_PUSH_PULL,GPIO_SPEED_50MHZ);

				 if((pin&0x30) == 0x00){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM2_REMAP;																		 	 }//���TIM2��AFIO����,����TIM2��AFIO����
			else if((pin&0x30) == 0x10){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM2_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM2_REMAP_0;}
			else if((pin&0x30) == 0x20){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM2_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM2_REMAP_1;}
			else if((pin&0x30) == 0x30){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM2_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM2_REMAP  ;}
			else    									 {;;}
				
			TIM2 ->PSC = 52000000/(freq*52)-1;																		//��Ƶ������
			TIM2 ->ARR = 9999;																										//�Զ�װ�ؼĴ�������1
			
				 if((pin&0x0300) == 0x0000){TIM2 ->CCMR1 |=	(TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1); TIM2 ->CCMR1 |= TIM_CCMR1_OC1PE; TIM2 ->CCR1 |= duty; TIM2 ->CCER |= TIM_CCER_CC1E; }
			else if((pin&0x0300) == 0x0100){TIM2 ->CCMR1 |=	(TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1); TIM2 ->CCMR1 |= TIM_CCMR1_OC2PE; TIM2 ->CCR2 |= duty; TIM2 ->CCER |= TIM_CCER_CC2E; }
			else if((pin&0x0300) == 0x0200){TIM2 ->CCMR2 |=	(TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1); TIM2 ->CCMR2 |= TIM_CCMR2_OC3PE; TIM2 ->CCR3 |= duty; TIM2 ->CCER |= TIM_CCER_CC3E; }
			else if((pin&0x0300) == 0x0300){TIM2 ->CCMR2 |=	(TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1); TIM2 ->CCMR2 |= TIM_CCMR2_OC4PE; TIM2 ->CCR4 |= duty; TIM2 ->CCER |= TIM_CCER_CC4E; }
			else													 {;;}
			
			TIM2 ->CR1   |= TIM_CR1_CEN ;	
			TIM2 ->CR1   |=	TIM_CR1_ARPE;		
			break;
		}
		case PWM_TIM3:
		{
			RCC  ->APB1ENR |= RCC_APB1ENR_TIM3EN;																	//ʹ�ܶ�ʱ��3ʱ��
			gpio_init ((pin&0x3F),GPO,1,GPO_AF_PUSH_PULL,GPIO_SPEED_50MHZ);		
	
				 if((pin&0x30) == 0x00){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM3_REMAP;																		 	 }//���TIM3��AFIO����,����TIM3��AFIO����
			else if((pin&0x30) == 0x10){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM3_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP_0;}
			else if((pin&0x30) == 0x20){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM3_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP_1;}
			else if((pin&0x30) == 0x30){ AFIO ->MAPR &= ~ AFIO_MAPR_TIM3_REMAP;AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP  ;}
			else    									 {;;}
				
			TIM3 ->PSC = 52000000/(freq*52)-1;																		//��Ƶ������
			TIM3 ->ARR = 9999;																										//�Զ�װ�ؼĴ�������
		
				 if((pin&0x0300) == 0x0000){TIM3 ->CCMR1 |=	(TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1); TIM3 ->CCMR1 |= TIM_CCMR1_OC1PE; TIM3 ->CCR1 |= duty; TIM3 ->CCER |= TIM_CCER_CC1E; }
			else if((pin&0x0300) == 0x0100){TIM3 ->CCMR1 |=	(TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1); TIM3 ->CCMR1 |= TIM_CCMR1_OC2PE; TIM3 ->CCR2 |= duty; TIM3 ->CCER |= TIM_CCER_CC2E; }
			else if((pin&0x0300) == 0x0200){TIM3 ->CCMR2 |=	(TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1); TIM3 ->CCMR2 |= TIM_CCMR2_OC3PE; TIM3 ->CCR3 |= duty; TIM3 ->CCER |= TIM_CCER_CC3E; }
			else if((pin&0x0300) == 0x0300){TIM3 ->CCMR2 |=	(TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1); TIM3 ->CCMR2 |= TIM_CCMR2_OC4PE; TIM3 ->CCR4 |= duty; TIM3 ->CCER |= TIM_CCER_CC4E; }
			else 													 {;;}
			
			TIM3 ->CR1   |= TIM_CR1_CEN ;	
			TIM3 ->CR1   |=	TIM_CR1_ARPE;			
			break;
		}
		case PWM_TIM4:
		{
			RCC  ->APB1ENR |= RCC_APB1ENR_TIM4EN;																	//ʹ�ܶ�ʱ��4ʱ��
			gpio_init ((pin&0x3F),GPO,1,GPO_AF_PUSH_PULL,GPIO_SPEED_50MHZ);

			AFIO ->MAPR &= ~ AFIO_MAPR_TIM4_REMAP;															  //���TIM4��AFIO����,����TIM4��AFIO����
																	
			TIM4 ->PSC = 52000000/(freq*52)-1;																		//��Ƶ������
			TIM4 ->ARR = 9999;																										//�Զ�װ�ؼĴ�������1
			
				 if((pin&0x0300) == 0x0000){TIM4 ->CCMR1 |=	(TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1); TIM4 ->CCMR1 |= TIM_CCMR1_OC1PE; TIM4 ->CCR1 |= duty; TIM4 ->CCER |= TIM_CCER_CC1E; }
			else if((pin&0x0300) == 0x0100){TIM4 ->CCMR1 |=	(TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1); TIM4 ->CCMR1 |= TIM_CCMR1_OC2PE; TIM4 ->CCR2 |= duty; TIM4 ->CCER |= TIM_CCER_CC2E; }
			else if((pin&0x0300) == 0x0200){TIM4 ->CCMR2 |=	(TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1); TIM4 ->CCMR2 |= TIM_CCMR2_OC3PE; TIM4 ->CCR3 |= duty; TIM4 ->CCER |= TIM_CCER_CC3E; }
			else if((pin&0x0300) == 0x0300){TIM4 ->CCMR2 |=	(TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1); TIM4 ->CCMR2 |= TIM_CCMR2_OC4PE; TIM4 ->CCR4 |= duty; TIM4 ->CCER |= TIM_CCER_CC4E; }
			else {;;}
			
			TIM4 ->CR1   |= TIM_CR1_CEN ;	
			TIM4 ->CR1   |=	TIM_CR1_ARPE;			
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		pwm����
// @param	    num	          			ģ���
// @param	    pin	    			  		����
// @param	    duty	    					����ռ�ձ�
// @return		void                       
// Sample usage: 		pwm_init(PWM_TIM1 , TIM1_CH1_PA08 ,5000);
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWM_TIM num , PWM_Num pin , uint16 duty)
{
		switch(num)
	{
		case PWM_TIM1 :
		{
				 if((pin&0x0300) == 0x0000){ TIM1 ->CCR1 |= duty; }
			else if((pin&0x0300) == 0x0100){ TIM1 ->CCR2 |= duty; }
			else if((pin&0x0300) == 0x0200){ TIM1 ->CCR3 |= duty; }
			else if((pin&0x0300) == 0x0300){ TIM1 ->CCR4 |= duty; }
			else 													 {;;}
			break;
		}
		case PWM_TIM2 : 
		{
				 if((pin&0x0300) == 0x0000){ TIM2 ->CCR1 |= duty; }
			else if((pin&0x0300) == 0x0100){ TIM2 ->CCR2 |= duty; }
			else if((pin&0x0300) == 0x0200){ TIM2 ->CCR3 |= duty; }
			else if((pin&0x0300) == 0x0300){ TIM2 ->CCR4 |= duty; }
			else													 {;;}
			break;
		}
		case PWM_TIM3 :
		{
				 if((pin&0x0300) == 0x0000){ TIM3 ->CCR1 |= duty; }
			else if((pin&0x0300) == 0x0100){ TIM3 ->CCR2 |= duty; }
			else if((pin&0x0300) == 0x0200){ TIM3 ->CCR3 |= duty; }
			else if((pin&0x0300) == 0x0300){ TIM3 ->CCR4 |= duty; }
			else													 {;;}
			break;
		}
		case PWM_TIM4 : 
		{
				 if((pin&0x0300) == 0x0000){ TIM4 ->CCR1 |= duty; }
			else if((pin&0x0300) == 0x0100){ TIM4 ->CCR2 |= duty; }
			else if((pin&0x0300) == 0x0200){ TIM4 ->CCR3 |= duty; }
			else if((pin&0x0300) == 0x0300){ TIM4 ->CCR4 |= duty; }
			else													 {;;} 
			break;
		}
	}
}