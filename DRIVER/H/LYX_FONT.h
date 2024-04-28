#ifndef _LYX_FONT_h_
#define _LYX_FONT_h_

#include "headfile.h"

//-------������ɫ----------
#define RED          	0xF800	//��ɫ
#define BLUE         	0x001F  //��ɫ
#define YELLOW       	0xFFE0	//��ɫ
#define GREEN        	0x07E0	//��ɫ
#define WHITE        	0xFFFF	//��ɫ
#define BLACK        	0x0000	//��ɫ
#define GRAY  				0X8430 	//��ɫ
#define BROWN 				0XBC40 	//��ɫ
#define PURPLE    		0XF81F	//��ɫ
#define PINK    			0XFE19	//��ɫ

extern const uint8 TFT_ascii[95][16];

extern const uint8 gImage_qq[3200];

extern const uint8 chinese_test[8][16];

extern const uint8 OLED_6x8[][6];

extern const uint8 OLED_8x16[][16];

extern const uint8 OLED_16x16_chinese[][16];

#endif
