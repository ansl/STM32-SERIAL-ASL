#ifndef STM32F1
#define STM32F1
#endif

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif

// #if defined(STM32F1)
//  #include "stm32f1xx_hal.h"
// 	#include <stm32_hal_legacy.h>
// #elif defined(STM32F4)
// 	#include "stm32f4xx_hal.h"
// #else
// 	#error "Error"
// #endif

#include "main.h"
struct val_types{
		int32_t i;
		char *c;
	};
int Serial_print(UART_HandleTypeDef *huart,char *frmt,...); //huart,format,value,disp_format
	




