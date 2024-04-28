#ifndef _LYX_IIC_h_
#define _LYX_IIC_h_

#include "headfile.h"
#define IIC_PIN_SCL		PB15
#define IIC_PIN_SDA		PB14

//IO��������
#define SDA_IN()  gpio_dir(IIC_PIN_SDA,GPI,GPI_PULL_UD,GPIO_SPEED_50MHZ);
#define SDA_OUT() gpio_dir(IIC_PIN_SDA,GPO,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);

//IO��������	 
#define IIC_SCL(x)		gpio_set(IIC_PIN_SCL,x)
#define IIC_SDA(x)		gpio_set(IIC_PIN_SDA,x)
#define READ_SDA      gpio_get(IIC_PIN_SDA) 	//����SDA 



//IIC��������
void IIC_OLED_init(void);               //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif
