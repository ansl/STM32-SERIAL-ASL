
#include "STM32-SERIAL-ASL.h"

//int Serial_print(UART_HandleTypeDef *huart,enum format frmt,...)
int Serial_print(UART_HandleTypeDef *huart,char *frmt,...)
{ 
	int n=0;
	va_list args;
	va_start(args, frmt);
	
	struct val_types val;
	val.i=0;
	val.c=0;

	char buf[400]="";


	if (strcmp(frmt,"BIN")==0)
	{
		n=32;
		val.i=(int32_t)va_arg(args, int);
		for (uint8_t i = n; i > 0; i--) {
			buf[i-1] = ((val.i >> n-i) & 1)|0x30;//transforms number int o ascii number
			}
		HAL_UART_Transmit(huart, &buf, n, 1000);
	}
	else {
	 	n=vsprintf(&buf,frmt,args);
	 	HAL_UART_Transmit(huart, &buf, n, 1000);
	}
	};