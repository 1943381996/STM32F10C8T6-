#ifndef _LYX_IIC_h_
#define _LYX_IIC_h_

#include "headfile.h"
#define IIC_PIN_SCL		PB15
#define IIC_PIN_SDA		PB14

//IO方向设置
#define SDA_IN()  gpio_dir(IIC_PIN_SDA,GPI,GPI_PULL_UD,GPIO_SPEED_50MHZ);
#define SDA_OUT() gpio_dir(IIC_PIN_SDA,GPO,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);

//IO操作函数	 
#define IIC_SCL(x)		gpio_set(IIC_PIN_SCL,x)
#define IIC_SDA(x)		gpio_set(IIC_PIN_SDA,x)
#define READ_SDA      gpio_get(IIC_PIN_SDA) 	//输入SDA 



//IIC操作函数
void IIC_OLED_init(void);               //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif
