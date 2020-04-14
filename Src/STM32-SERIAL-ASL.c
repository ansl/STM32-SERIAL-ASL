
#include "STM32-SERIAL-ASL.h"

int Serial_print(UART_HandleTypeDef *huart,...)
{ 
	int n=0;
	char data[40]="";
	va_list args;
	va_start(args, *huart);
	
	struct val_types val;
	val.a=0;
	val.b=0;
	val.c=0;
	enum format frmt;
	enum disp_format d_frmt;
	enum NL newline;
	frmt=va_arg(args, int);
		switch (frmt){
			case _uint:
				val.b=(uint32_t)va_arg(args, uint32_t);
			break;
			case _int:
				val.a=(int32_t)va_arg(args, int);
			break;
			case _float:
				val.c=va_arg(args, double);
			break;
			// default:
			// 	val.a=va_arg(args, int);
		};
	
	d_frmt=va_arg(args, int);

	newline=va_arg(args, int);
	char nl=0;
	if (newline==1){nl=10;}

	va_end(args);

	switch (frmt){
		case _uint:
			switch(d_frmt){
				case DEC:
					n=sprintf(&data, "%u%c", val.b,nl);
				break;
				case BIN:
					n = 32;
					long b=0;
					for (uint8_t i = n; i > 0; i--) {
						data[i-1] = ((val.a >> n-i) & 1)|0x30;//transforms number int o ascii number
					}
					data[n]=nl;
				break;
				case HEX:
					n=sprintf(&data, "%#X%c", val.b,nl);
				break;
				// default:
				// 	n=sprintf(&data, "%u\n", val.b);
			}
			
			break;
		case _int:
			switch(d_frmt){
				case DEC:
					n=sprintf(&data, "%d%c", val.a,nl);
				break;
				case BIN:
					n = 32;
					char b[32]={0};
					// if (val.a<0) {
					// 	int32_t a= ~val.a;
					// 	a=a+1;
					// }
					for (uint8_t i = n; i > 0; i--) {
						data[i-1] = ((val.a >> n-i) & 1)|0x30;//transforms number int o ascii number
					}
					data[n]=nl;
					//n=sprintf(&data, "%s\n", b);
				break;
				case HEX:
					n=sprintf(&data, "%#X%c", val.a,nl);
				break;
				// default:
				// 	n=sprintf(&data, "%d\n", val.a);
			}
			break;
		case _float:
			switch(d_frmt){
				case DEC:
					n=sprintf(&data, "%f%c", val.c,nl);
				break;
				 case BIN:
				// 	n = 32;
				// 	long b=0;
				// 	for (uint8_t i = 0; i < n; i++) {
				// 		b += ((val.c >> i) & 1)*pow(10,i);
				// 	}	
				// 	n=sprintf(&data, "%032d\n", b);
					n=sprintf(&data, "%f%c", val.c,nl);
				 break;
				case HEX:
					// n=sprintf(&data, "%#X\n", val.c);
					n=sprintf(&data, "%f%c", val.c,nl);
				break;
				// default:
				// 	n=sprintf(&data, "%d\n", val.c);
			}
			break;
		// default:
		// 	switch(d_frmt){
		// 		case DEC:
		// 			n=sprintf(&data, "%d\n", val.a);
		// 		break;
		// 		case BIN:
		// 			n = 32;
		// 			long b=0;
		// 			for (uint8_t i = 0; i < n; i++) {
		// 				b += ((val.a >> i) & 1)*pow(10,i);
		// 			}	
		// 			n=sprintf(&data, "%032d\n", b);
		// 		break;
		// 		case HEX:
		// 			n=sprintf(&data, "%#X\n", val.a);
		// 		break;
		// 		default:
		// 			n=sprintf(&data, "%d\n", val.a);
		// 	}
			
	};
	
	HAL_UART_Transmit(huart, &data, n+1, 1000);
};

