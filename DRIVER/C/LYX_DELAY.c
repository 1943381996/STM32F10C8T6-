#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief		DWT_INT
// @param		
// @return		void
// Sample usage:			DWT_init();
//-------------------------------------------------------------------------------------------------------------------
void DWT_init(void)
{
  DEM_CR |= (uint32_t)DEM_CR_TRCENA; 	//使能DWT外设 
  DWT_CYCCNT = (uint32_t)0u;			//DWT CYCCNT寄存器计数清0
  DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA; //使能Cortex-M DWT CYCCNT寄存器
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
// @brief		DWT_Delay  WS2812B灯珠用
// @param		
// @return		void
// Sample usage:			DWT_Delay(time);  时钟为52MHZ  T1H  延时650ns 约为31个机器周期
//													   	                     T1L 延时600ns 约为29个机器周期
//                                                   T0H 延时350ns 约为17个机器周期
//                                                   T0L 延时950ns 约为45个机器周期
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
