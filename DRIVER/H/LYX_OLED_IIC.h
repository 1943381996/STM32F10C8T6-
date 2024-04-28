#ifndef _LYX_OLED_H_
#define _LYX_OLED_H_

#include "headfile.h"
extern uint8 OLED_gram[128][8];  //显存数组

#define OLED_H 64	
#define OLED_L 128
#define OLED1_ADD 	0x78		//默地址为0x78
#define OLED2_ADD 	0x7A		//需要将显示屏背面电阻焊到另一侧
#define OLED_BLACK 	0x00		//全黑
#define OLED_WHITE  0XFF		//全白
#define OLED_W_SCL(x)		gpio_set(IIC_PIN_SCL,x)
#define OLED_W_SDA(x)		gpio_set(IIC_PIN_SDA,x)

void OLED_IIC_init(void);
void OLED_IIC_full(void);
void OLED_IIC_WriteData(uint8 Data);
void OLED_IIC_WriteCommand(uint8 Command);
void OLED_IIC_SetCursor(uint8 x, uint8 y);
void OLED_IIC_Clear(uint16 COLOR);
void OLED_IIC_DrawPoint(uint8 x,uint8 y);
void OLED_IIC_ShowChar(uint8 x, uint8 y, const uint8 ch[]);

void oled_IIC_uint16(uint8 x, uint8 y, uint16 num);
void OLED_IIC_display(void);


#endif
