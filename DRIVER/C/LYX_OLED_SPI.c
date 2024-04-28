#include "headfile.h"

//���SPI

//-------------------------------------------------------------------------------------------------------------------
// @brief			OLED_д����
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
// @brief			OLED_д����
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
// @brief		OLED_���ù��	
// @param		
// @return	void
// Sample usage: OLED_SetCursor(0,0,1);
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_SetCursor(uint8 x, uint8 y)
{
	OLED_SPI_Write_CMD(0xB0 | y);					//����Yλ��
	OLED_SPI_Write_CMD(0x10 | ((x & 0xF0) >> 4));	//����Xλ�ø�4λ
	OLED_SPI_Write_CMD(0x00 | ((x & 0x0F) << 4));			//����Xλ�õ�4λ
	
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		OLED_����
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
//  @brief      OLED��������
//  @param      bmp_data	�����ɫѡ��(0x00 or 0xff)
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
//  @brief      OLED��ʼ������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:			
//-------------------------------------------------------------------------------------------------------------------
void OLED_SPI_init(void)
{
	DWT_Delay_ms (300);
			//�ϵ���ʱ 300ms
	SPI_OLED_init();			//�˿ڳ�ʼ��
	OLED_SPI_Write_CMD(0xA);	//�ر���ʾ
	                      
	OLED_SPI_Write_CMD(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	OLED_SPI_Write_CMD(0x80);
	                      
                          
	                      
	OLED_SPI_Write_CMD(0xA8);	//���ö�·������
	OLED_SPI_Write_CMD(0x3F);
	                      
	OLED_SPI_Write_CMD(0xD3);	//������ʾƫ��
	OLED_SPI_Write_CMD(0x00);
	                      
	OLED_SPI_Write_CMD(0x40);	//������ʾ��ʼ��
	                      
	OLED_SPI_Write_CMD(0xA1);	//�������ҷ���0xA1���� 0xA0���ҷ���
	                      
	OLED_SPI_Write_CMD(0xC8);	//�������·���0xC8���� 0xC0���·���
                         
	OLED_SPI_Write_CMD(0xDA);	//����COM����Ӳ������
	OLED_SPI_Write_CMD(0x12);
	                    
	OLED_SPI_Write_CMD(0xFF);	//���öԱȶȿ���
	OLED_SPI_Write_CMD(0xCF);
                         
	OLED_SPI_Write_CMD(0xD9);	//����Ԥ�������
	OLED_SPI_Write_CMD(0xF1);

	OLED_SPI_Write_CMD(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_SPI_Write_CMD(0x30);
                          
	OLED_SPI_Write_CMD(0xA4);	//����������ʾ��/�ر�
                          
	OLED_SPI_Write_CMD(0xA6);	//��������/��ת��ʾ
                          
	OLED_SPI_Write_CMD(0x8D);	//���ó���
	OLED_SPI_Write_CMD(0x14);
                         
	OLED_SPI_Write_CMD(0xAF);	//������ʾ
	
		
	OLED_SPI_full(0x00);				//OLED����
	OLED_SPI_SetCursor(0,0);
	
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
void OLED_SPI_putpixel(uint8 x,uint8 y,uint8 data)
{
	OLED_SPI_SetCursor(x,y);
  	OLED_SPI_Write_CMD(0xb0+y);
	OLED_SPI_Write_CMD(((x&0xf0)>>4)|0x10);
	OLED_SPI_Write_CMD((x&0x0f)|0x00);
	OLED_SPI_Write_DAT(data);
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
//  @brief      OLED��ʾ�ַ���(8*16����)
//  @param      x			x����������0-127
//  @param      y           y����������0-7
//  @param      ch[]        �ַ���
//  @return     void
//  @since      v1.0
//  Sample usage:			���ע�⣬�������ַ��и�λ16�����yӦ����ÿ�ε���2
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
