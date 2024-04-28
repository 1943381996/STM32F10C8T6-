#include "headfile.h"


uint32 lBufInArray[NPT];    /* FFT ������������� */
uint32 lBufOutArray[NPT/2]; /* FFT ������������ */
uint32 lBufMagArray[NPT/2]; /* ����г���ķ�ֵ	  */

uint32 sample_arr; 				// ����ʵ��������ó�ʼֵ
uint32 sample_psc; 				// ����ʵ��������ó�ʼֵ
uint32 frequency_max_position; 	// ����ʵ��������ó�ʼֵ
float sample_frequency; 		// ����ʵ��������ó�ʼֵ
float wave_frequency; 			// ����ʵ��������ó�ʼֵ

uint8 commond_flag;


//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC����
// @param		
// @return	void
// Sample usage: adc_sample(void);
//-------------------------------------------------------------------------------------------------------------------
void adc_sample(void)
{
    for (uint16 i = 0; i < NPT; i++)
    {
       /* lBufInArray[i] = */adc_get(ADC_1, ADC1_CH04_A04);/* - 1500;*/
    }
    cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);
    GetPowerMag();
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		FFT����
// @param		
// @return	void
// Sample usage: adc_sample(void);
//-------------------------------------------------------------------------------------------------------------------
void GetPowerMag(void)
{
    signed short lX, lY;
    float X, Y, Mag;
    unsigned short i;
    for (i = 0; i < NPT/2; i++)
    {
        lX  = (lBufOutArray[i] << 16) >> 16;
        lY  = (lBufOutArray[i] >> 16);
			
        // ����32768�ٳ�65536��Ϊ�˷��ϸ������������
        X = NPT * ((float)lX) / 32768;
        Y = NPT * ((float)lY) / 32768;
        Mag = sqrt(X * X + Y * Y) * 1.0 / NPT;
        if (i == 0)	
            lBufMagArray[i] = (unsigned long)(Mag * 32768);
        else
            lBufMagArray[i] = (unsigned long)(Mag * 65536);
    }

}


void wave_frequency_calculate(void)
{
    sample_frequency = 54000000.0 / (float)((sample_arr + 1) * (sample_psc + 1));
    wave_frequency = frequency_max_position * sample_frequency / NPT;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		FFT��ʾ
// @param		
// @return	void
// Sample usage: adc_sample(void);
//-------------------------------------------------------------------------------------------------------------------
void FFT_disply(void)
{
	//д��FFT����
	uint8 FFT_date = 0, dat=0;
	for(uint8 i=0; i<64; i++)
	{
		FFT_date = 0;
		FFT_date = lBufMagArray[i];
			 if((FFT_date > 64*1)&&(FFT_date < 64*2 )) {	FFT_date = FFT_date/2 ; }
		else if((FFT_date > 64*2)&&(FFT_date < 64*3 )) {	FFT_date = FFT_date/3 ; }  
		else if((FFT_date > 64*3)&&(FFT_date < 64*4 )) {	FFT_date = FFT_date/4 ; }
		else if((FFT_date > 64*4)&&(FFT_date < 64*5 )) {	FFT_date = FFT_date/5 ; }
		else if((FFT_date > 64*5)&&(FFT_date < 64*6 )) {	FFT_date = FFT_date/6 ; }
		else if((FFT_date > 64*6)&&(FFT_date < 64*7 )) {	FFT_date = FFT_date/7 ; }
		else if((FFT_date > 64*7)&&(FFT_date < 64*8 )) {	FFT_date = FFT_date/8 ; }
		else if((FFT_date > 64*8)&&(FFT_date < 64*9 )) {	FFT_date = FFT_date/9 ; }
		else if((FFT_date > 64*9)&&(FFT_date < 64*10)) {	FFT_date = FFT_date/10; }
		for(uint8 j=63; j> FFT_date; j--)
		{
			switch(j%8)
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
			OLED_gram[i*2][j/8] |= dat;
			OLED_gram[i*2+1][j/8] |= dat;
		}
	}
	for(uint8 i=0; i<128; i++)
	{
		for(uint8 j=0; j<8; j++)
		{
			OLED_gram[i][j] = ~ OLED_gram[i][j];
		}
	}
	if(commond_flag == 0)
	{
		OLED_SPI_Write_CMD(0xa0);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
		OLED_SPI_Write_CMD(0xc0);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����		
		commond_flag = 1;
	}

	//��ʾƵ��ͼ��
	for(uint8 j=0; j<8; j++)
	{
		OLED_SPI_SetCursor(0, j);
		for(uint8 i=0; i<128; i++)
		{
			OLED_SPI_Write_DAT(OLED_gram[i][j]);
		}
	}
	for(uint8 i=0; i<128; i++)
	{
		for(uint8 j=0; j<8; j++)
		{
			OLED_gram[i][j]= 0;
		}
	}
}
