#include "headfile.h"
//0.96寸四角显示屏，最多可分别控制两个显示屏 地址在.h宏定义//
uint8 OLED_gram[128][8];  //显存数组

//IIC OLED显示
//-------------------------------------------------------------------------------------------------------------------
// @brief			OLED_写命令
// @param		
// @return	void
// Sample usage: OLED_IIC_Write_CMD(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_Write_CMD(uint8 Command)
{
	IIC_Start();
	IIC_Send_Byte(0x78);		//从机地址
	IIC_Send_Byte(0x00);		//写命令
	IIC_Send_Byte(Command); 
	IIC_Stop();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_写数据	
// @param		
// @return	void
// Sample usage: void OLED_IIC_Write_DAT(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_Write_DAT(uint8 Data)
{
	IIC_Start();
	IIC_Send_Byte(0x78);	//从机地址
	IIC_Send_Byte(0x40);		//写数据
	IIC_Send_Byte(Data);
	IIC_Stop();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_清屏
// @param		
// @return	void
// Sample usage: OLED_SetCursor(0,0,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_Clear(uint16 COLOR)
{  
	uint8 i, j;
	if(COLOR==OLED_BLACK)
	{
	for (j = 0; j < 8; j++)
	{
		OLED_IIC_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_IIC_Write_DAT(0xFF);
		}
	}
	}
	else 
	{
	for (j = 0; j < 8; j++)
	{
		OLED_IIC_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			
			OLED_IIC_Write_DAT(0x00);
		}
	}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_填充
// @param		
// @return	void
// Sample usage: OLED_full(oxff);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_full(void)
{  
	uint8 i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_IIC_SetCursor(0, j);
		for(i = 0; i < 128; i++)
		{
			OLED_IIC_Write_DAT(0x00);
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_画点
// @param		
// @return	void
// Sample usage: OLED_DrawPoint(0,0);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_DrawPoint(uint8 x,uint8 y)
{
	uint8 tem_y = 0;
	uint8 dat = 0x00;
	tem_y = y % 8;
	OLED_IIC_SetCursor(x,y/8);
	switch(tem_y)
		{
			case 0:dat=0x01;break;
			case 1:dat=0x02;break;
			case 2:dat=0x04;break;
			case 3:dat=0x08;break;
			case 4:dat=0x10;break;
			case 5:dat=0x20;break;
			case 6:dat=0x40;break;
			case 7:dat=0x80;break;
		}
	OLED_IIC_Write_DAT(dat);
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_画线
// @param		
// @return	void
// Sample usage: OLED_DrawPoint(0,0);
//-------------------------------------------------------------------------------------------------------------------
//void OLED_DrawLine(uint8 x,uint8 y)



//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_显示字符串	
// @param		
// @return	void
// Sample usage: OLED_ShowChar(0,0,"0x00");
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_ShowChar(uint8 x, uint8 y, const uint8 ch[])
{      	
	uint8 c=0,i=0,j=0;
	
 while (ch[j]!='\0')
	{
			c = ch[j]-32;
	  	if(x>126){x=0;y++;}
	  	OLED_IIC_SetCursor(x,y);
	  	for(i=0;i<6;i++)	/*oled_gram[x+i][y] = oled_6x8[c][i];*/OLED_IIC_Write_DAT(OLED_6x8[c][i]);
	  	x+=6;
	  	j++;
	}
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示无符号数(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      num         无符号数
//  @return     void
//  @since      
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void oled_IIC_uint16(uint8 x, uint8 y, uint16 num)
{
	uint16 num_1=0,num_2=0,num_3=0,num_4=0,num_5=0;
	uint16 date_num_1[5];
	
	num_1 = num /10000;
	num_2 = (num - (num_1 * 10000))/1000;
	num_3 = (num - (num_1 * 10000 + num_2 *1000))/100;
	num_4 = (num - (num_1 * 10000 + num_2 *1000 + num_3 *100))/10;
	num_5 = (num - (num_1 * 10000 + num_2 *1000 + num_3 *100 +num_4 *10))/1;
	
	date_num_1[0] = num_1 + 16;
	date_num_1[1] = num_2 + 16;
	date_num_1[2] = num_3 + 16;
	date_num_1[3] = num_4 + 16;
	date_num_1[4] = num_5 + 16;
	
	for(uint8 i=0; i<5; i++)
	{
		for(uint8 j=0; j<6; j++)
		{
			OLED_IIC_SetCursor(x+6*i+j,y);
			OLED_IIC_Write_DAT(OLED_6x8[date_num_1[i]][j]);//显示数字  6*8字体		
		}
	}   
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED初始化函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_init(void)
{
	DWT_Delay_ms (300);
			//上电延时 300ms
	IIC_OLED_init();			//端口初始化
	OLED_IIC_Write_CMD(0xA);	//关闭显示
	                      
	OLED_IIC_Write_CMD(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_IIC_Write_CMD(0x80);
	                      
                          
	                      
	OLED_IIC_Write_CMD(0xA8);	//设置多路复用率
	OLED_IIC_Write_CMD(0x3F);
	                      
	OLED_IIC_Write_CMD(0xD3);	//设置显示偏移
	OLED_IIC_Write_CMD(0x00);
	                      
	OLED_IIC_Write_CMD(0x40);	//设置显示开始行
	                      
	OLED_IIC_Write_CMD(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	                      
	OLED_IIC_Write_CMD(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置
                         
	OLED_IIC_Write_CMD(0xDA);	//设置COM引脚硬件配置
	OLED_IIC_Write_CMD(0x12);
	                    
	OLED_IIC_Write_CMD(0xFF);	//设置对比度控制
	OLED_IIC_Write_CMD(0xCF);
                         
	OLED_IIC_Write_CMD(0xD9);	//设置预充电周期
	OLED_IIC_Write_CMD(0xF1);

	OLED_IIC_Write_CMD(0xDB);	//设置VCOMH取消选择级别
	OLED_IIC_Write_CMD(0x30);
                          
	OLED_IIC_Write_CMD(0xA4);	//设置整个显示打开/关闭
                          
	OLED_IIC_Write_CMD(0xA6);	//设置正常/倒转显示
                          
	OLED_IIC_Write_CMD(0x8D);	//设置充电泵
	OLED_IIC_Write_CMD(0x14);
                         
	OLED_IIC_Write_CMD(0xAF);	//开启显示
	
		
	OLED_IIC_full();				//OLED清屏
	OLED_IIC_SetCursor(0,0);
	
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示坐标设置
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_SetCursor(uint8 x, uint8 y)
{
    if(OLED_L>x) 		      //参数断言，进入断言标志参数超出范围
    if((OLED_H/8)>y)
    
    OLED_IIC_Write_CMD(0xb0+y);
    OLED_IIC_Write_CMD(((x&0xf0)>>4)|0x10);
    OLED_IIC_Write_CMD((x&0x0f)|0x00);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED清屏函数
//  @param      bmp_data	填充颜色选着(0x00 or 0xff)
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_fill(uint8 bmp_data)
{
	uint8 y,x;
	
	for(y=0;y<8;y++)
	{
		OLED_IIC_Write_CMD(0xb0+y);
		OLED_IIC_Write_CMD(0x01);
		OLED_IIC_Write_CMD(0x10);
		for(x=0;x<OLED_L;x++)	OLED_IIC_Write_DAT(bmp_data); 
	}
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
void OLED_IIC_putpixel(uint8 x,uint8 y,uint8 data1)
{
	OLED_IIC_SetCursor(x,y);
  	OLED_IIC_Write_CMD(0xb0+y);
	OLED_IIC_Write_CMD(((x&0xf0)>>4)|0x10);
	OLED_IIC_Write_CMD((x&0x0f)|0x00);
	OLED_IIC_Write_DAT(data1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED关闭一个坐标所有亮点
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_clrpixel(uint8 x,uint8 y)
{
	OLED_IIC_SetCursor(x,y);
    OLED_IIC_Write_CMD(0xb0+y);
	OLED_IIC_Write_CMD(((x&0xf0)>>4)|0x10);
	OLED_IIC_Write_CMD((x&0x0f)|0x00);
	OLED_IIC_Write_DAT(0x00);
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
void OLED_IIC_p6x8str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
	  	c =ch[j]-32;
	  	if(x>126){x=0;y++;}
	  	OLED_IIC_SetCursor(x,y);
	  	for(i=0;i<6;i++)	/*OLED_gram[x+i][y] = OLED_6x8[c][i];*/OLED_IIC_Write_DAT(OLED_6x8[c][i]);
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
void OLED_IIC_p8x16str(uint8 x,uint8 y,const int8 ch[])
{
	uint8 c=0,i=0,j=0;
	
	while (ch[j]!='\0')
	{
	  	c =ch[j]-32;
	  	if(x>120){x=0;y++;}
		
	  	OLED_IIC_SetCursor(x,y);
	  	for(i=0;i<8;i++)	OLED_IIC_Write_DAT(OLED_8x16[c+i][1]);
	  	  
	  	OLED_IIC_SetCursor(x,y+1);
	  	for(i=0;i<8;i++)	OLED_IIC_Write_DAT(OLED_8x16[c+i+8][1]);
	  	  
	  	x+=8;
	  	j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示无符号数(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      num         无符号数
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_uint16(uint8 x, uint8 y, uint16 num)
{
	int8 ch[7];
	
//	OLED_hexascii(num,ch);
    
    OLED_IIC_p6x8str(x, y, &ch[1]);	    //显示数字  6*8字体
    //OLED_p8x16str(x, y, &ch[1]);	//显示数字  8*16字体
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示有符号数(6*8字体)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      num         有符号数
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_int16(uint8 x, uint8 y, int16 num)
{
	int8 ch[7];
	if(num<0)   {num = -num;OLED_IIC_p6x8str(x, y, "-");}
	else         OLED_IIC_p6x8str(x, y, " ");
	x+=6;       
    
//	OLED_hexascii(num,ch);
  OLED_IIC_p6x8str(x, y, &ch[1]);	    //显示数字  6*8字体
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示32位有符号(去除整数部分无效的0)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      dat       	需要显示的变量，数据类型uint32
//  @param      num       	需要显示的位数 最高10位  不包含正负号
//  @return     void
//  @since      v1.0
//  Sample usage:           OLED_printf_int32(0,0,x,5);//x可以为int32 uint16 int16 uint8 int8类型
//  Sample usage:           负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_printf_int32(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)
		{
			//length = zf_sprintf( &buff[0],"%d",dat);//负数
		}			
    else
    {
        buff[0] = ' ';
      //  length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';
    
    OLED_IIC_p6x8str(x, y, buff);	//显示数字
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示浮点数(去除整数部分无效的0)
//  @param      x			x轴坐标设置0-127
//  @param      y           y轴坐标设置0-7
//  @param      dat       	需要显示的变量，数据类型float或double
//  @param      num         整数位显示长度   最高10位  
//  @param      pointnum    小数位显示长度   最高6位
//  @return     void
//  @since      v1.0
//  Sample usage:           OLED_printf_float(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
//  @note                   特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//                          可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//                          有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//                          负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_printf_float(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
//    uint8   length;
//	int8    buff[34];
//	int8    start,end,point;

//	if(6<pointnum)  pointnum = 6;
//    if(10<num)      num = 10;
//        
//    if(0>dat)
//		{
//			//length = zf_sprintf( &buff[0],"%f",dat);//负数
//		}			
//    else
//    {
//      //  length = zf_sprintf( &buff[1],"%f",dat);
//        length++;
//    }
//    point = length - 7;         //计算小数点位置
//    start = point - num - 1;    //计算起始位
//    end = point + pointnum + 1; //计算结束位
//    while(0>start)//整数位不够  末尾应该填充空格
//    {
//        buff[end] = ' ';
//        end++;
//        start++;
//    }
//    
//    if(0>dat)   buff[start] = '-';
//    else        buff[start] = ' ';
//    
//    buff[end] = '\0';
//    
//    OLED_p6x8str(x, y, buff);	//显示数字
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED显示图像
//  @param      high  		图像高度
//  @param      width 		图像宽度
//  @param      *p    		图像地址（数组）
//  @param      value 		二值化阀值
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       使用Image2lcd V3.2软件取模   C语言数组   水平扫描   
//              宽度高度自行设置   颜色反转  256色
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_dis_bmp(uint16 high, uint16 width, uint8 *p,uint8 value)
{
    int16 i,j;
    int16 temp,temp1;
    uint8 dat;
    
    temp1 = high%8;
    if(temp1 == 0) temp = high/8;
    else           temp = high/8+1;

    for(i=0; i<temp; i++)
    {
        OLED_IIC_SetCursor(0,i);
        for(j=0; j<width; j++)
        {
            dat = 0;
            if( i<(temp-1) || !temp1 || temp1>=1)dat |= (*(p+i*8*width+j+width*0) > value? 1: 0)<<0;
            if( i<(temp-1) || !temp1 || temp1>=2)dat |= (*(p+i*8*width+j+width*1) > value? 1: 0)<<1;
            if( i<(temp-1) || !temp1 || temp1>=3)dat |= (*(p+i*8*width+j+width*2) > value? 1: 0)<<2;
            if( i<(temp-1) || !temp1 || temp1>=4)dat |= (*(p+i*8*width+j+width*3) > value? 1: 0)<<3;
            if( i<(temp-1) || !temp1 || temp1>=5)dat |= (*(p+i*8*width+j+width*4) > value? 1: 0)<<4;
            if( i<(temp-1) || !temp1 || temp1>=6)dat |= (*(p+i*8*width+j+width*5) > value? 1: 0)<<5;
            if( i<(temp-1) || !temp1 || temp1>=7)dat |= (*(p+i*8*width+j+width*6) > value? 1: 0)<<6;
            if( i<(temp-1) || !temp1 || temp1>=8)dat |= (*(p+i*8*width+j+width*7) > value? 1: 0)<<7;
           
            OLED_IIC_Write_DAT(dat);
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      汉字显示
//  @param      x       横坐标 0-127
//  @param      y       纵坐标 0-7
//  @param      size    取模的时候设置的汉字字体大小，也就是一个汉字占用的点阵长宽为多少个点，取模的时候需要长宽是一样的。
//  @param      *p      需要显示的汉字数组
//  @param      len     需要显示多少位
//  @return     void
//  @since      v1.0
//  Sample usage:		
//  @Note       使用PCtoLCD2002软件取模		    阴码、逐行式、顺向   16*16
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_print_chinese(uint8 x, uint8 y, uint8 size, const uint8 *p, uint8 len)
{
    int16 i,j,k;
    
    for(i=0; i<len; i++)
    {
        for(j=0; j<(size/8); j++)
        {
            OLED_IIC_SetCursor(x+i*size,y+j);
            for(k=0; k<16; k++)
            {
                OLED_IIC_Write_DAT(*p);
                p++;
            }
        }
    }
}



void OLED_IIC_display(void)
{
//	OLED_IIC_Write_CMD(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
//	OLED_IIC_Write_CMD(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
}
