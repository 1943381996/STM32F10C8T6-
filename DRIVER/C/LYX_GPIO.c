#include "headfile.h"

GPIO_TypeDef *gpio_group[4] = {GPIOA , GPIOB , GPIOC , GPIOD };	//强转换为指针类型的结构体

//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO初始化
// @param		pin			选择的引脚 (可选择范围由 gpio.h 内PIN_enum枚举值确定)
// @param		dir		引脚的方向
// @param		dat			引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
// @param		mode		引脚的模式
// @param		speed		引脚输出速度
// @return		void
// Sample usage: gpio_init(PA13, GPO, 1, GPO_PUSH_PULL,GPIO_SPEED_50MHZ);//D5初始化为GPIO功能、输出模式、输出高电平、速度50MHZ
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(GPIO_Num pin , GPIO_Dir dir ,uint8 dat , GPIO_Mode mode , GPIO_Speed speed)
{
	RCC->APB2ENR |= 0x01<<(2+get_group(pin));				//开启对应GPIO通道的时钟
  gpio_dir(pin ,  dir ,  mode ,  speed);          //GPIO方向设置
	gpio_set(pin,dat); 															//GPIO电平设置
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO方向设置
// @param		pin			选择的引脚 (可选择范围由 gpio.h 内PIN_enum枚举值确定)
// @param		dir			引脚的方向   输出：GPO   输入：GPI
// @param		mode		引脚的模式
// @param		speed		引脚输出速度
// @return		void
// Sample usage:			gpio_dir(PC13,GPO,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);//设置PC13为推挽输出模式（速度50MHZ）
//-------------------------------------------------------------------------------------------------------------------
void gpio_dir(GPIO_Num pin , GPIO_Dir dir , GPIO_Mode mode , GPIO_Speed speed)
{
	if(dir == GPI )												  																	//如果是输入
	{
		if(get_pin (pin) < 8)																										//0~7  配置低位寄存器
		{
			gpio_group[get_group (pin)]->CRL &= ~(0x0f<<get_pin (pin)*4);					//寄存器先清0
			gpio_group[get_group (pin)]->CRL |=  (mode<<get_pin (pin)*4);					//写入寄存器
		}
		else																																		//8~15	配置高位寄存器	
		{
			gpio_group[get_group (pin)]->CRH &= ~(0x0f<<(get_pin (pin)-8)*4);			//寄存器先清0
			gpio_group[get_group (pin)]->CRH |=  (mode<<(get_pin (pin)-8)*4);			//写入寄存器
		}
	}
	if(dir == GPO )																														//如果是输出
	{
		if(get_pin (pin) < 8)																										//0~7  配置低位寄存器
		{
			gpio_group[get_group (pin)]->CRL &= ~(0x0f <<get_pin (pin)*4);				//寄存器先清0
			gpio_group[get_group (pin)]->CRL |=  (mode <<get_pin (pin)*4);				//写入寄存器
			gpio_group[get_group (pin)]->CRL |=  (speed<<get_pin (pin)*4);				//写入寄存器
		}
		else																																		//8~15 配置高位寄存器
		{
			gpio_group[get_group (pin)]->CRH &= ~(0x0f	<<(get_pin (pin)-8)*4);		//寄存器先清0
			gpio_group[get_group (pin)]->CRH |=  (mode	<<(get_pin (pin)-8)*4);		//写入寄存器
			gpio_group[get_group (pin)]->CRH |=  (speed <<(get_pin (pin)-8)*4);		//写入寄存器
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO设置引脚电平
// @param		pin			选择的引脚 (可选择范围由 gpio.h 内PIN_enum枚举值确定)
// @param		dat			0：低电平 1：高电平
// @return		void
// Sample usage:			gpio_set(PC5,1);//PC5 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(GPIO_Num pin , uint8 dat)
{
	if(dat)		Gpio_set(pin);															//置1高电平								
	else		Gpio_reset(pin);															//置0低电平
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO获取引脚电平
// @param		pin			选择的引脚 (可选择范围由 gpio.h 内PIN_enum枚举值确定)
// @return		uint8		0：低电平 1：高电平
// Sample usage:			uint8 status = gpio_get(D5);//获取D5引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get(GPIO_Num pin)
{
	if(gpio_group[get_group(pin)]->IDR & 0x01<<get_pin(pin)) 		return 1; //输入寄存器配置			
	else 																												return 0;
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		GPIO翻转
// @param		pin			选择的引脚 (可选择范围由 gpio.h 内PIN_enum枚举值确定)
// @return		void
// Sample usage:			gpio_toggle(D5);//设置D5为输出模式
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle(GPIO_Num pin)
{
	gpio_group [get_group (pin)]->ODR ^=0x01<<get_pin (pin);							//输出寄存器配置	
}
