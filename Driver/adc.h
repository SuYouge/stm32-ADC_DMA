#ifndef _adc_H
#define _adc_H

#include "stm32f10x.h"

void ADC1_Init(void);
static void ADC1_GPIO_Config(void);
static void ADC1_Mode_Config(void);

#define ADC1_DR_Address ((u32)0x40012400 + 0x4c)

#endif
