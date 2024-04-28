#include "headfile.h"
//0.96���Ľ���ʾ�������ɷֱ����������ʾ�� ��ַ��.h�궨��//
uint8 OLED_gram[128][8];  //�Դ�����

//IIC OLED��ʾ
//-------------------------------------------------------------------------------------------------------------------
// @brief			OLED_д����
// @param		
// @return	void
// Sample usage: OLED_IIC_Write_CMD(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_Write_CMD(uint8 Command)
{
	IIC_Start();
	IIC_Send_Byte(0x78);		//�ӻ���ַ
	IIC_Send_Byte(0x00);		//д����
	IIC_Send_Byte(Command); 
	IIC_Stop();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_д����	
// @param		
// @return	void
// Sample usage: void OLED_IIC_Write_DAT(0x00,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_Write_DAT(uint8 Data)
{
	IIC_Start();
	IIC_Send_Byte(0x78);	//�ӻ���ַ
	IIC_Send_Byte(0x40);		//д����
	IIC_Send_Byte(Data);
	IIC_Stop();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_����
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
// @brief		OLED_���
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
// @brief		OLED_����
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
// @brief		OLED_����
// @param		
// @return	void
// Sample usage: OLED_DrawPoint(0,0);
//-------------------------------------------------------------------------------------------------------------------
//void OLED_DrawLine(uint8 x,uint8 y)



//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_��ʾ�ַ���	
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
//  @brief      OLED��ʾ�޷�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �޷�����
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
			OLED_IIC_Write_DAT(OLED_6x8[date_num_1[i]][j]);//��ʾ����  6*8����		
		}
	}   
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʼ������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_init(void)
{
	DWT_Delay_ms (300);
			//�ϵ���ʱ 300ms
	IIC_OLED_init();			//�˿ڳ�ʼ��
	OLED_IIC_Write_CMD(0xA);	//�ر���ʾ
	                      
	OLED_IIC_Write_CMD(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_IIC_Write_CMD(0x80);
	                      
                          
	                      
	OLED_IIC_Write_CMD(0xA8);	//���ö�·������
	OLED_IIC_Write_CMD(0x3F);
	                      
	OLED_IIC_Write_CMD(0xD3);	//������ʾƫ��
	OLED_IIC_Write_CMD(0x00);
	                      
	OLED_IIC_Write_CMD(0x40);	//������ʾ��ʼ��
	                      
	OLED_IIC_Write_CMD(0xA1);	//�������ҷ���0xA1���� 0xA0���ҷ���
	                      
	OLED_IIC_Write_CMD(0xC8);	//�������·���0xC8���� 0xC0���·���
                         
	OLED_IIC_Write_CMD(0xDA);	//����COM����Ӳ������
	OLED_IIC_Write_CMD(0x12);
	                    
	OLED_IIC_Write_CMD(0xFF);	//���öԱȶȿ���
	OLED_IIC_Write_CMD(0xCF);
                         
	OLED_IIC_Write_CMD(0xD9);	//����Ԥ�������
	OLED_IIC_Write_CMD(0xF1);

	OLED_IIC_Write_CMD(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_IIC_Write_CMD(0x30);
                          
	OLED_IIC_Write_CMD(0xA4);	//����������ʾ��/�ر�
                          
	OLED_IIC_Write_CMD(0xA6);	//��������/��ת��ʾ
                          
	OLED_IIC_Write_CMD(0x8D);	//���ó���
	OLED_IIC_Write_CMD(0x14);
                         
	OLED_IIC_Write_CMD(0xAF);	//������ʾ
	
		
	OLED_IIC_full();				//OLED����
	OLED_IIC_SetCursor(0,0);
	
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ��������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_SetCursor(uint8 x, uint8 y)
{
    if(OLED_L>x) 		      //�������ԣ�������Ա�־����������Χ
    if((OLED_H/8)>y)
    
    OLED_IIC_Write_CMD(0xb0+y);
    OLED_IIC_Write_CMD(((x&0xf0)>>4)|0x10);
    OLED_IIC_Write_CMD((x&0x0f)|0x00);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��������
//  @param      bmp_data	�����ɫѡ��(0x00 or 0xff)
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
//  @brief      OLED����һ��������8�����صĵ�����Ϩ��
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @return     void
//  @since      v1.0
//  Sample usage:			OLED_putpixel(0,0,0xff);//��0,0���� 8����ȫ������
//  Sample usage:			OLED_putpixel(0,0,0x01);//��0,0���� ���λ��������7��Ϩ��
//  @note                   ͬ������������һ��������8�����صĵ�����Ϩ��
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
//  @brief      OLED�ر�һ��������������
//  @param      x			x����������0-127
//  @param      y           y����������0-7
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
//  @brief      OLED��ʾ�ַ���(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      ch[]        �ַ���
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
//  @brief      OLED��ʾ�ַ���(8*16����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      ch[]        �ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:			���ע�⣬�������ַ��и�λ16�����yӦ����ÿ�ε���2
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
//  @brief      OLED��ʾ�޷�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �޷�����
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_uint16(uint8 x, uint8 y, uint16 num)
{
	int8 ch[7];
	
//	OLED_hexascii(num,ch);
    
    OLED_IIC_p6x8str(x, y, &ch[1]);	    //��ʾ����  6*8����
    //OLED_p8x16str(x, y, &ch[1]);	//��ʾ����  8*16����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ�з�����(6*8����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      num         �з�����
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
  OLED_IIC_p6x8str(x, y, &ch[1]);	    //��ʾ����  6*8����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ32λ�з���(ȥ������������Ч��0)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      dat       	��Ҫ��ʾ�ı�������������uint32
//  @param      num       	��Ҫ��ʾ��λ�� ���10λ  ������������
//  @return     void
//  @since      v1.0
//  Sample usage:           OLED_printf_int32(0,0,x,5);//x����Ϊint32 uint16 int16 uint8 int8����
//  Sample usage:           ��������ʾһ�� ��-����   ������ʾһ���ո�
//-------------------------------------------------------------------------------------------------------------------
void OLED_IIC_printf_int32(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)
		{
			//length = zf_sprintf( &buff[0],"%d",dat);//����
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
    
    OLED_IIC_p6x8str(x, y, buff);	//��ʾ����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾ������(ȥ������������Ч��0)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      dat       	��Ҫ��ʾ�ı�������������float��double
//  @param      num         ����λ��ʾ����   ���10λ  
//  @param      pointnum    С��λ��ʾ����   ���6λ
//  @return     void
//  @since      v1.0
//  Sample usage:           OLED_printf_float(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
//  @note                   �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
//                          ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
//                          �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
//                          ��������ʾһ�� ��-����   ������ʾһ���ո�
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
//			//length = zf_sprintf( &buff[0],"%f",dat);//����
//		}			
//    else
//    {
//      //  length = zf_sprintf( &buff[1],"%f",dat);
//        length++;
//    }
//    point = length - 7;         //����С����λ��
//    start = point - num - 1;    //������ʼλ
//    end = point + pointnum + 1; //�������λ
//    while(0>start)//����λ����  ĩβӦ�����ո�
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
//    OLED_p6x8str(x, y, buff);	//��ʾ����
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      OLED��ʾͼ��
//  @param      high  		ͼ��߶�
//  @param      width 		ͼ����
//  @param      *p    		ͼ���ַ�����飩
//  @param      value 		��ֵ����ֵ
//  @return     void
//  @since      v1.0
//  Sample usage:	
//  @Note       ʹ��Image2lcd V3.2���ȡģ   C��������   ˮƽɨ��   
//              ��ȸ߶���������   ��ɫ��ת  256ɫ
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
//  @brief      ������ʾ
//  @param      x       ������ 0-127
//  @param      y       ������ 0-7
//  @param      size    ȡģ��ʱ�����õĺ��������С��Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��㣬ȡģ��ʱ����Ҫ������һ���ġ�
//  @param      *p      ��Ҫ��ʾ�ĺ�������
//  @param      len     ��Ҫ��ʾ����λ
//  @return     void
//  @since      v1.0
//  Sample usage:		
//  @Note       ʹ��PCtoLCD2002���ȡģ		    ���롢����ʽ��˳��   16*16
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
//	OLED_IIC_Write_CMD(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
//	OLED_IIC_Write_CMD(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
}
