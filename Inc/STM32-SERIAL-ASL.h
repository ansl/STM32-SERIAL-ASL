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
		int32_t a;
		uint32_t b;
		double c;
	};
enum format{_uint,_int,_float};
enum disp_format{DEC,BIN,HEX};
enum NL{x,NL};
//  int Serial_print(UART_HandleTypeDef *huart,float num ,char* type[3]);
int Serial_print(UART_HandleTypeDef *huart,...); //huart,format,value,disp_format
//int Serial_print(UART_HandleTypeDef *huart,uint8_t num ,char* type[3]);
//bool print(uint32_t num ,char* type[]=0);
//bool println(char* string);
//bool println(uint16_t num);	




