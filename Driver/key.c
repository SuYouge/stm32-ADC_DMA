#include "key.h"
//#include "stdbool.h"

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/*开启安检端口PE5的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Delay(u32 i)
{
while(i--);
}

u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )
	{
		Delay(10000);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )
		{
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);
			return KEY_ON;
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}
