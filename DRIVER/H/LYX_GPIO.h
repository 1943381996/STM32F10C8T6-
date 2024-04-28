#ifndef _LYX_GPIO_H
#define _LYX_GPIO_H
#include "headfile.h"

/*设置引脚枚举类型*/
typedef enum 
{
	
	PA0=0x00 , PA1=0x01 , PA2=0x02 , PA3=0x03 , PA4=0x04 , PA5=0x05 , PA6=0x06 , PA7=0x07 , PA8=0x08 , PA9=0x09 , PA10=0x0A , PA11=0x0B , PA12=0x0C , PA13=0x0D , PA14=0x0E , PA15=0x0F,  //定义GPIOA
	
	PB0=0x10 , PB1=0x11 , PB2=0x12 , PB3=0x13 , PB4=0x14 , PB5=0x15 , PB6=0x16 , PB7=0x17 , PB8=0x18 , PB9=0x19 , PB10=0x1A , PB11=0x1B , PB12=0x1C , PB13=0x1D , PB14=0x1E , PB15=0x1F,  //定义GPIOB
	
	PC0=0x20 , PC1=0x21 , PC2=0x22 , PC3=0x23 , PC4=0x24 , PC5=0x25 , PC6=0x26 , PC7=0x27 , PC8=0x28 , PC9=0x29 , PC10=0x2A , PC11=0x2B , PC12=0x2C , PC13=0x2D , PC14=0x2E , PC15=0x2F,  //定义GPIOC
	
}GPIO_Num;

/*设置IO口方向枚举类型*/
typedef enum 
{
	GPI,													//定义管脚输入
	GPO,													//定义管脚输出
}GPIO_Dir;

/*设置IO口模式枚举类型*/
typedef enum 
{
	
	GPI_ANAOG_IN		=0x00,		//模拟输入
	GPI_FLOATING_IN		=0x04,		//浮空输入
	GPI_PULL_UD			=0x08,		//上拉、下拉输入
	
	GPO_PUSH_PULL		=0x00,		//推挽输出
	GPO_OPEN_DTAIN		=0x04,		//开漏输出
	GPO_AF_PUSH_PULL	=0x08,		//复用推挽输出
	GPO_AF_OPEN_DTAIN	=0x0C,		//复用开漏输出
	
}GPIO_Mode;

/*设置IO口速度枚举类型*/
typedef enum
{ 
	
	GPIO_SPEED_2MHZ		=0x02,			//2MHZ
	GPIO_SPEED_10MHZ	=0x01,			//10MHZ
	GPIO_SPEED_50MHZ	=0x03,			//50MHZ
	
}GPIO_Speed;

#define get_group(x) 			(x>>4)		//获取引脚通道号
#define get_pin(x)		    	(x&0x0f)	//获取引脚序号

#define Gpio_set(x)		    	gpio_group [get_group(x)]->ODR |=   0x01<<get_pin(x)		//置为高电平
#define Gpio_reset(x)			gpio_group [get_group(x)]->ODR &= ~(0x01<<get_pin(x))		//置为低电平

uint8 gpio_get(GPIO_Num pin);
void gpio_init(GPIO_Num pin , GPIO_Dir dir ,uint8 dat , GPIO_Mode mode , GPIO_Speed speed);
void gpio_dir(GPIO_Num pin , GPIO_Dir dir , GPIO_Mode mode , GPIO_Speed speed);
void gpio_set(GPIO_Num pin , uint8 dat);
void gpio_toggle(GPIO_Num pin);

extern GPIO_TypeDef *gpio_group[4];	

#endif
