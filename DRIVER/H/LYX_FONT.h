#ifndef _LYX_FONT_h_
#define _LYX_FONT_h_

#include "headfile.h"

//-------常用颜色----------
#define RED          	0xF800	//红色
#define BLUE         	0x001F  //蓝色
#define YELLOW       	0xFFE0	//黄色
#define GREEN        	0x07E0	//绿色
#define WHITE        	0xFFFF	//白色
#define BLACK        	0x0000	//黑色
#define GRAY  				0X8430 	//灰色
#define BROWN 				0XBC40 	//棕色
#define PURPLE    		0XF81F	//紫色
#define PINK    			0XFE19	//粉色

extern const uint8 TFT_ascii[95][16];

extern const uint8 gImage_qq[3200];

extern const uint8 chinese_test[8][16];

extern const uint8 OLED_6x8[][6];

extern const uint8 OLED_8x16[][16];

extern const uint8 OLED_16x16_chinese[][16];

#endif
