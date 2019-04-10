#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "adc.h"
//加入按键
//实现printf重定向 实现USART1_frintf()

//ADC1 转换的电压值通过DMA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;

//局部变量 用于保存转换计算后的电压值
float ADC_ConvertedValueLocal;

void Delayms(u16 ms)
{
  u16 i,j;
  u8 k;
  for(i=0;i<ms;i++)
    for(j=0;j<0x0500;j++) k++;
}

int main()
{
	uart_init(9600); 
	ADC1_Init();
	printf("\r\n ----------这是一个ADC试验-------\r\n");
	while(1)
	{		
			ADC_ConvertedValueLocal = (float) ADC_ConvertedValue/4096*3.3;
			printf("\r\n -----The current AD value = 0x%04X \r\n",ADC_ConvertedValue);
			printf("\r\n -----The current AD value = %f V \r\n",ADC_ConvertedValueLocal);
			Delayms(5000);
	}
}
