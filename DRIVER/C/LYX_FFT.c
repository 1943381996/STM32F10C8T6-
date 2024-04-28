#include "headfile.h"


uint32 lBufInArray[NPT];    /* FFT 运算的输入数组 */
uint32 lBufOutArray[NPT/2]; /* FFT 运算的输出数组 */
uint32 lBufMagArray[NPT/2]; /* 各次谐波的幅值	  */

uint32 sample_arr; 				// 根据实际情况设置初始值
uint32 sample_psc; 				// 根据实际情况设置初始值
uint32 frequency_max_position; 	// 根据实际情况设置初始值
float sample_frequency; 		// 根据实际情况设置初始值
float wave_frequency; 			// 根据实际情况设置初始值

uint8 commond_flag;


//-------------------------------------------------------------------------------------------------------------------
// @brief		ADC采样
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
// @brief		FFT计算
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
			
        // 除以32768再乘65536是为了符合浮点数计算规律
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
// @brief		FFT显示
// @param		
// @return	void
// Sample usage: adc_sample(void);
//-------------------------------------------------------------------------------------------------------------------
void FFT_disply(void)
{
	//写入FFT数据
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
		OLED_SPI_Write_CMD(0xa0);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
		OLED_SPI_Write_CMD(0xc0);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常		
		commond_flag = 1;
	}

	//显示频域图像
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
