#include "headfile.h"

//软件SPI

//-------------------------------------------------------------------------------------------------------------------
// @brief			OLED_写命令
// @param		
// @return	void
// Sample usage: OLED_SPI_Write_CMD(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_Write_CMD(uint8 commond)
{
    uint8 i=8;

    SPI_Start();
    SPI_DC(0);
	while(i--)
	{
		if(commond&0x80){SPI_SDA(1);}
		else{SPI_SDA(0);}

		SPI_SCL(1);
		SPI_SCL(0);

		commond<<=1;
	}
    SPI_Stop();
}
//-------------------------------------------------------------------------------------------------------------------
// @brief			OLED_写数据
// @param		
// @return	void
// Sample usage: OLED_SPI_Write_DAT(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_Write_DAT(uint8 date)
{
    uint8 i=8;

    SPI_Start();
	while(i--)
	{
		if(date&0x80){SPI_SDA(1);}
		else{SPI_SDA(0);}

		SPI_SCL(1);
		SPI_SCL(0);
        
		date<<=1;
	}
    SPI_Stop();  
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_设置光标	
// @param		
// @return	void
// Sample usage: OLED_SetCursor(0,0,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_SetCursor(uint8 x, uint8 y)
{
	OLED_SPI_Write_CMD(0xB0 | y);					//设置Y位置
	OLED_SPI_Write_CMD(0x10 | ((x & 0xF0) >> 4));	//设置X位置高4位
	OLED_SPI_Write_CMD(0x00 | ((x & 0x0F) << 4));			//设置X位置低4位
	
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_清屏
// @param		
// @return	void
// Sample usage: OLED_SetCursor(0,0,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_Clear(uint16 COLOR)
{  
	uint8 i, j;
	if(COLOR==OLED_BLACK)
	{
	for (j = 0; j < 8; j++)
	{
		OLED_SPI_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_SPI_Write_DAT(0xFF);
		}
	}
	}
	else 
	{
	for (j = 0; j < 8; j++)
	{
		OLED_SPI_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			
			OLED_SPI_Write_DAT(0x00);
		}
	}
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED清屏函数
//  @param      bmp_data	填充颜色选着(0x00 or 0xff)
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_full(uint8 bmp_data)
{
	uint8 y,x;
	
	for(y=0;y<8;y++)
	{
		OLED_SPI_Write_CMD(0xb0+y);
		OLED_SPI_Write_CMD(0x01);
		OLED_SPI_Write_CMD(0x10);
		for(x=0;x<OLED_L;x++)	OLED_SPI_Write_DAT(bmp_data); 
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED初始化函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_init(void)
{
	DWT_Delay_ms (300);
			//上电延时 300ms
	SPI_OLED_init();			//端口初始化
	OLED_SPI_Write_CMD(0xA);	//关闭显示
	                      
	OLED_SPI_Write_CMD(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_SPI_Write_CMD(0x80);
	                      
                          
	                      
	OLED_SPI_Write_CMD(0xA8);	//设置多路复用率
	OLED_SPI_Write_CMD(0x3F);
	                      
	OLED_SPI_Write_CMD(0xD3);	//设置显示偏移
	OLED_SPI_Write_CMD(0x00);
	                      
	OLED_SPI_Write_CMD(0x40);	//设置显示开始行
	                      
	OLED_SPI_Write_CMD(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	                      
	OLED_SPI_Write_CMD(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置
                         
	OLED_SPI_Write_CMD(0xDA);	//设置COM引脚硬件配置
	OLED_SPI_Write_CMD(0x12);
	                    
	OLED_SPI_Write_CMD(0xFF);	//设置对比度控制
	OLED_SPI_Write_CMD(0xCF);
                         
	OLED_SPI_Write_CMD(0xD9);	//设置预充电周期
	OLED_SPI_Write_CMD(0xF1);

	OLED_SPI_Write_CMD(0xDB);	//设置VCOMH取消选择级别
	OLED_SPI_Write_CMD(0x30);
                          
	OLED_SPI_Write_CMD(0xA4);	//设置整个显示打开/关闭
                          
	OLED_SPI_Write_CMD(0xA6);	//设置正常/倒转显示
                          
	OLED_SPI_Write_CMD(0x8D);	//设置充电泵
	OLED_SPI_Write_CMD(0x14);
                         
	OLED_SPI_Write_CMD(0xAF);	//开启显示
	
		
	OLED_SPI_full(0x00);				//OLED清屏
	OLED_SPI_SetCursor(0,0);
	
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED控制一个坐标下8个像素的点亮与熄灭
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			OLED_putpixel(0,0,0xff);//将0,0坐标 8个点全部点亮
//  Sample usage:			OLED_putpixel(0,0,0x01);//将0,0坐标 最低位点亮其余7个熄灭
//  @note                   同理可以任意控制一个坐标下8个像素的点亮与熄灭
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_putpixel(uint8 x,uint8 y,uint8 data)
{
	OLED_SPI_SetCursor(x,y);
  	OLED_SPI_Write_CMD(0xb0+y);
	OLED_SPI_Write_CMD(((x&0xf0)>>4)|0x10);
	OLED_SPI_Write_CMD((x&0x0f)|0x00);
	OLED_SPI_Write_DAT(data);
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示字符串(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch[]        字符串
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_p6x8str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
	  	c =ch[j]-32;
	  	if(x>126){x=0;y++;}
	  	OLED_SPI_SetCursor(x,y);
	  	for(i=0;i<6;i++)	/*OLED_gram[x+i][y] = OLED_6x8[c][i];*/OLED_SPI_Write_DAT(OLED_6x8[c][i]);
	  	x+=6;
	  	j++;
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示字符串(8*16字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      ch[]        字符串
//  @return     void
//  @since      v1.0
//  Sample usage:			务必注意，本函数字符列高位16，因此y应该是每次递增2
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_p8x16str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;
	
	while (ch[j]!='\0')
	{
	  	c =ch[j]-32;
	  	if(x>120){x=0;y++;}
		
	  	OLED_SPI_SetCursor(x,y);
	  	for(i=0;i<8;i++)	OLED_SPI_Write_DAT(OLED_8x16[c+i][1]);
	  	  
	  	OLED_SPI_SetCursor(x,y+1);
	  	for(i=0;i<8;i++)	OLED_SPI_Write_DAT(OLED_8x16[c+i+8][1]);
	  	  
	  	x+=8;
	  	j++;
	}
}
