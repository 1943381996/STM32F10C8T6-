#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_INT
// @param		
// @return		void
// Sample usage:			DWT_init();
//-------------------------------------------------------------------------------------------------------------------
void DWT_init(void)
{
  DEM_CR |= (uint32_t)DEM_CR_TRCENA; 	//ʹ��DWT���� 
  DWT_CYCCNT = (uint32_t)0u;			//DWT CYCCNT�Ĵ���������0
  DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA; //ʹ��Cortex-M DWT CYCCNT�Ĵ���
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_TS_GET
// @param		
// @return		void
// Sample usage:			DWT_TS_GET();
//-------------------------------------------------------------------------------------------------------------------
uint32_t DWT_TS_GET(void)
{
  return((uint32_t)DWT_CYCCNT);
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_Delay_ms
// @param		
// @return		void
// Sample usage:			DWT_Delay_ms(ms);
//-------------------------------------------------------------------------------------------------------------------
void DWT_Delay_ms(uint32_t time_ms)
{
  uint32_t old_counter,current_counter;
  uint32_t delay_ms;
  
  old_counter = DWT_TS_GET();
  current_counter = DWT_TS_GET();
  delay_ms = 0;
  while(delay_ms<time_ms)
  {
    current_counter = DWT_TS_GET();
    if(current_counter > old_counter)
	{
      delay_ms = (current_counter - old_counter)/(system_core_clock/1000);
	}
    else
	{
      delay_ms = (current_counter + 0XFFFFFFFF - old_counter)/(system_core_clock/1000);	
	}
  }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_Delay_us
// @param		
// @return		void
// Sample usage:			DWT_Delay_Ms(us);
//-------------------------------------------------------------------------------------------------------------------
void DWT_Delay_us(uint32_t time_us)
{
  uint32_t old_counter,current_counter;
  uint32_t delay_us;
  
  old_counter = DWT_TS_GET();
  current_counter = DWT_TS_GET();
  delay_us = 0;
  while(delay_us<time_us)
  {
    current_counter = DWT_TS_GET();
    if(current_counter > old_counter)
      delay_us = (current_counter - old_counter)/(system_core_clock/1000000);
    else
      delay_us = (current_counter + 0XFFFFFFFF - old_counter)/(system_core_clock/1000000);
  }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_Delay  WS2812B������
// @param		
// @return		void
// Sample usage:			DWT_Delay(time);  ʱ��Ϊ52MHZ  T1H  ��ʱ650ns ԼΪ31����������
//													   	                     T1L ��ʱ600ns ԼΪ29����������
//                                                   T0H ��ʱ350ns ԼΪ17����������
//                                                   T0L ��ʱ950ns ԼΪ45����������
//-------------------------------------------------------------------------------------------------------------------
void DWT_Delay(uint32_t time)
{
  uint32_t old_counter,current_counter;
  uint32_t delay;
  
  old_counter = DWT_TS_GET();
  current_counter = DWT_TS_GET();
  delay = 0;
  while(delay<time)
  {
    current_counter = DWT_TS_GET();
    if(current_counter > old_counter)
      delay = (current_counter - old_counter)/(system_core_clock/system_core_clock);
    else
      delay = (current_counter + 0XFFFFFFFF - old_counter)/(system_core_clock/system_core_clock);
  }
}
