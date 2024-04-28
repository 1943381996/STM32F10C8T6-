#ifndef _LYX_GPIO_H
#define _LYX_GPIO_H
#include "headfile.h"

/*��������ö������*/
typedef enum 
{
	
	PA0=0x00 , PA1=0x01 , PA2=0x02 , PA3=0x03 , PA4=0x04 , PA5=0x05 , PA6=0x06 , PA7=0x07 , PA8=0x08 , PA9=0x09 , PA10=0x0A , PA11=0x0B , PA12=0x0C , PA13=0x0D , PA14=0x0E , PA15=0x0F,  //����GPIOA
	
	PB0=0x10 , PB1=0x11 , PB2=0x12 , PB3=0x13 , PB4=0x14 , PB5=0x15 , PB6=0x16 , PB7=0x17 , PB8=0x18 , PB9=0x19 , PB10=0x1A , PB11=0x1B , PB12=0x1C , PB13=0x1D , PB14=0x1E , PB15=0x1F,  //����GPIOB
	
	PC0=0x20 , PC1=0x21 , PC2=0x22 , PC3=0x23 , PC4=0x24 , PC5=0x25 , PC6=0x26 , PC7=0x27 , PC8=0x28 , PC9=0x29 , PC10=0x2A , PC11=0x2B , PC12=0x2C , PC13=0x2D , PC14=0x2E , PC15=0x2F,  //����GPIOC
	
}GPIO_Num;

/*����IO�ڷ���ö������*/
typedef enum 
{
	GPI,													//����ܽ�����
	GPO,													//����ܽ����
}GPIO_Dir;

/*����IO��ģʽö������*/
typedef enum 
{
	
	GPI_ANAOG_IN		=0x00,		//ģ������
	GPI_FLOATING_IN		=0x04,		//��������
	GPI_PULL_UD			=0x08,		//��������������
	
	GPO_PUSH_PULL		=0x00,		//�������
	GPO_OPEN_DTAIN		=0x04,		//��©���
	GPO_AF_PUSH_PULL	=0x08,		//�����������
	GPO_AF_OPEN_DTAIN	=0x0C,		//���ÿ�©���
	
}GPIO_Mode;

/*����IO���ٶ�ö������*/
typedef enum
{ 
	
	GPIO_SPEED_2MHZ		=0x02,			//2MHZ
	GPIO_SPEED_10MHZ	=0x01,			//10MHZ
	GPIO_SPEED_50MHZ	=0x03,			//50MHZ
	
}GPIO_Speed;

#define get_group(x) 			(x>>4)		//��ȡ����ͨ����
#define get_pin(x)		    	(x&0x0f)	//��ȡ�������

#define Gpio_set(x)		    	gpio_group [get_group(x)]->ODR |=   0x01<<get_pin(x)		//��Ϊ�ߵ�ƽ
#define Gpio_reset(x)			gpio_group [get_group(x)]->ODR &= ~(0x01<<get_pin(x))		//��Ϊ�͵�ƽ

uint8 gpio_get(GPIO_Num pin);
void gpio_init(GPIO_Num pin , GPIO_Dir dir ,uint8 dat , GPIO_Mode mode , GPIO_Speed speed);
void gpio_dir(GPIO_Num pin , GPIO_Dir dir , GPIO_Mode mode , GPIO_Speed speed);
void gpio_set(GPIO_Num pin , uint8 dat);
void gpio_toggle(GPIO_Num pin);

extern GPIO_TypeDef *gpio_group[4];	

#endif
