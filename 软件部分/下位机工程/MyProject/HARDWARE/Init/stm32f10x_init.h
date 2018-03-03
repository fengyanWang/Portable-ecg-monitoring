
/*
主要存放STM32 上电初始化功能函数
#include "stm32f10x_init.h"
*/
#ifndef __STM32F10x_INIT_H
#define __STM32F10x_INIT_H

#include "stdio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_exti.h"
#include "sys.h"


//RCC配置
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void SPI_Configuration(void);
void TIMER_Configuration(void);
void EXIT_Configuration(void);


#endif /* __STM32F10x_INIT_H */
