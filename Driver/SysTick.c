#include "SysTick.h"
__IO u32 TimingDelay;

void SysTick_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 100000)) // ST3.5版本库
	{
		/* Capture error */
		while (1);
	}
	//关闭滴答定时器
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void Delay_us(__IO u32 nTime)
{
	TimingDelay = nTime;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

