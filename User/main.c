#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "adc.h"
//���밴��
//ʵ��printf�ض��� ʵ��USART1_frintf()

//ADC1 ת���ĵ�ѹֵͨ��DMA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

//�ֲ����� ���ڱ���ת�������ĵ�ѹֵ
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
	printf("\r\n ----------����һ��ADC����-------\r\n");
	while(1)
	{		
			ADC_ConvertedValueLocal = (float) ADC_ConvertedValue/4096*3.3;
			printf("\r\n -----The current AD value = 0x%04X \r\n",ADC_ConvertedValue);
			printf("\r\n -----The current AD value = %f V \r\n",ADC_ConvertedValueLocal);
			Delayms(5000);
	}
}
