#ifndef _LYX_OLED_SPI_h_
#define _LYX_OLED_SPI_h_

#include "headfile.h"

void OLED_SPI_Write_CMD(uint8 commond);
void OLED_SPI_Write_DAT(uint8 date);
void OLED_SPI_SetCursor(uint8 x, uint8 y);
void OLED_SPI_Clear(uint16 COLOR);
void OLED_SPI_full(uint8 bmp_data);
void OLED_SPI_putpixel(uint8 x,uint8 y,uint8 data);
void OLED_IIC_p6x8str(uint8 x,uint8 y,const int8 ch[]);
void OLED_IIC_p8x16str(uint8 x,uint8 y,const int8 ch[]);
#endif
