#include "headfile.h"

GPIO_TypeDef *gpio_group[4] = {GPIOA , GPIOB , GPIOC , GPIOD };	//ǿת��Ϊָ�����͵Ľṹ��

//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO��ʼ��
// @param		pin			ѡ������� (��ѡ��Χ�� gpio.h ��PIN_enumö��ֵȷ��)
// @param		dir		���ŵķ���
// @param		dat			���ų�ʼ��ʱ���õĵ�ƽ״̬�����ʱ��Ч 0���͵�ƽ 1���ߵ�ƽ
// @param		mode		���ŵ�ģʽ
// @param		speed		��������ٶ�
// @return		void
// Sample usage: gpio_init(PA13, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);//D5��ʼ��ΪGPIO���ܡ����ģʽ������ߵ�ƽ���ٶ�50MHZ
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(GPIO_Num pin , GPIO_Dir dir ,uint8 dat , GPIO_Mode mode , GPIO_Speed speed)
{
	RCC->APB2ENR |= 0x01<<(2+get_group(pin));				//������ӦGPIOͨ����ʱ��
  gpio_dir(pin ,  dir ,  mode ,  speed);          //GPIO��������
	gpio_set(pin,dat); 															//GPIO��ƽ����
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO��������
// @param		pin			ѡ������� (��ѡ��Χ�� gpio.h ��PIN_enumö��ֵȷ��)
// @param		dir			���ŵķ���   �����GPO   ���룺GPI
// @param		mode		���ŵ�ģʽ
// @param		speed		��������ٶ�
// @return		void
// Sample usage:			gpio_dir(PC13,GPO,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);//����PC13Ϊ�������ģʽ���ٶ�50MHZ��
//-------------------------------------------------------------------------------------------------------------------
void gpio_dir(GPIO_Num pin , GPIO_Dir dir , GPIO_Mode mode , GPIO_Speed speed)
{
	if(dir == GPI )												  																	//���������
	{
		if(get_pin (pin) < 8)																										//0~7  ���õ�λ�Ĵ���
		{
			gpio_group[get_group (pin)]->CRL &= ~(0x0f<<get_pin (pin)*4);					//�Ĵ�������0
			gpio_group[get_group (pin)]->CRL |=  (mode<<get_pin (pin)*4);					//д��Ĵ���
		}
		else																																		//8~15	���ø�λ�Ĵ���	
		{
			gpio_group[get_group (pin)]->CRH &= ~(0x0f<<(get_pin (pin)-8)*4);			//�Ĵ�������0
			gpio_group[get_group (pin)]->CRH |=  (mode<<(get_pin (pin)-8)*4);			//д��Ĵ���
		}
	}
	if(dir == GPO )																														//��������
	{
		if(get_pin (pin) < 8)																										//0~7  ���õ�λ�Ĵ���
		{
			gpio_group[get_group (pin)]->CRL &= ~(0x0f <<get_pin (pin)*4);				//�Ĵ�������0
			gpio_group[get_group (pin)]->CRL |=  (mode <<get_pin (pin)*4);				//д��Ĵ���
			gpio_group[get_group (pin)]->CRL |=  (speed<<get_pin (pin)*4);				//д��Ĵ���
		}
		else																																		//8~15 ���ø�λ�Ĵ���
		{
			gpio_group[get_group (pin)]->CRH &= ~(0x0f	<<(get_pin (pin)-8)*4);		//�Ĵ�������0
			gpio_group[get_group (pin)]->CRH |=  (mode	<<(get_pin (pin)-8)*4);		//д��Ĵ���
			gpio_group[get_group (pin)]->CRH |=  (speed <<(get_pin (pin)-8)*4);		//д��Ĵ���
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO�������ŵ�ƽ
// @param		pin			ѡ������� (��ѡ��Χ�� gpio.h ��PIN_enumö��ֵȷ��)
// @param		dat			0���͵�ƽ 1���ߵ�ƽ
// @return		void
// Sample usage:			gpio_set(PC5,1);//PC5 ����ߵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(GPIO_Num pin , uint8 dat)
{
	if(dat)		Gpio_set(pin);															//��1�ߵ�ƽ								
	else		Gpio_reset(pin);															//��0�͵�ƽ
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO��ȡ���ŵ�ƽ
// @param		pin			ѡ������� (��ѡ��Χ�� gpio.h ��PIN_enumö��ֵȷ��)
// @return		uint8		0���͵�ƽ 1���ߵ�ƽ
// Sample usage:			uint8 status = gpio_get(D5);//��ȡD5���ŵ�ƽ
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get(GPIO_Num pin)
{
	if(gpio_group[get_group(pin)]->IDR & 0x01<<get_pin(pin)) 		return 1; //����Ĵ�������			
	else 																												return 0;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO��ת
// @param		pin			ѡ������� (��ѡ��Χ�� gpio.h ��PIN_enumö��ֵȷ��)
// @return		void
// Sample usage:			gpio_toggle(D5);//����D5Ϊ���ģʽ
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle(GPIO_Num pin)
{
	gpio_group [get_group (pin)]->ODR ^=0x01<<get_pin (pin);							//����Ĵ�������	
}
