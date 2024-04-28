#ifndef _LYX_SPI_h_
#define _LYX_SPI_h_

#include "headfile.h"

//软件SPI定义
#define SPI_PIN_SCL   PB15 
#define SPI_PIN_SDA   PB14 
#define SPI_PIN_RST   PB13 
#define SPI_PIN_DC    PB12
#define SPI_PIN_CS    PB11 

//IO方向设置
#define SPI_SDA_IN()  gpio_dir(SPI_PIN_SDA,GPI,GPI_PULL_UD  ,GPIO_SPEED_50MHZ);
#define SPI_SDA_OUT() gpio_dir(SPI_PIN_SDA,GPO,GPO_PUSH_PULL,GPIO_SPEED_50MHZ);

//IO操作函数	 
#define SPI_SCL(x)  gpio_set (SPI_PIN_SCL	, x)
#define SPI_SDA(x)  gpio_set (SPI_PIN_SDA	, x)
#define SPI_RST(x)  gpio_set (SPI_PIN_RST	, x)
#define SPI_DC(x)   gpio_set (SPI_PIN_DC	, x)
#define SPI_CS(x)   gpio_set (SPI_PIN_CS  , x)

//命令和数据
#define OLED_SPI_CMD  0
#define OLED_SPI_DAT  1

void SPI_OLED_int(void);
void SPI_Start(void);
void SPI_Stop(void);

#endif
