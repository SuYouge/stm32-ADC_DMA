#ifndef _key_H
#define _key_H

#include "stm32f10x.h"
void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
void Delay(u32 i);

#define KEY_ON 0
#define KEY_OFF 1

#endif
