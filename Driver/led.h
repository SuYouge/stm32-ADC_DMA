#ifndef _led_H
#define _led_H

#include "stm32f10x.h"
void LED_Init(void);

#define LED_PORT_RCC	RCC_APB2Periph_GPIOC
#define LED_PIN				(GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define LED_PORT			GPIOC

#endif
