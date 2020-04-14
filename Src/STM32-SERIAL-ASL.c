
#include "STM32-SERIAL-ASL.h"

// bool Serial::println(char* string)
// {
// 	uint8_t n=sizeof(string)/sizeof(char);
// 	char* stringln[n+1];
// 	memcpy(string,stringln,n);
// 	stringln[n+1]="\n";
// 	HAL_UART_Transmit(&Serial_huart, (uint8_t*) stringln, n + 1, 100);
// }
// ;
/*bool print(uint8_t num ,char* type)
{
	//Unit16_t max 3 digits
	char a[3]={0};
	sprintf(a,"%d",num);
	HAL_UART_Transmit(&Serial_huart, (uint8_t*)&a, 3, 100);
}*/
// int Serial_print(UART_HandleTypeDef *huart,float num ,char* type[3])
// { 
//     int n=0;
// 	char data[40]="";
// 	if (type == "DEC")
//     {
// 		n=sprintf(&data, "%f\n", num);
// 	}
//     if (type == "HEX")
//     {
// 		n=sprintf(&data, "%#X\n", num);
// 	}
// 	else if (type == "BIN")
// 	{
// 		//Unit16_t max 16 bits
// 		n = 16;
//         long b=0;
//         for (uint8_t i = 0; i < n; i++) {
//             b += ((num >> i) & 1)*pow(10,i);
//         }
// 		//for (uint8_t i = 0; i < n; i++) data[n -1 - i] = ((num >> i) & 1);
//         sprintf(&data, "%016d\n",b);
// 	}
// 	HAL_UART_Transmit(huart, &data, n+1, 100);
// }
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

// int Serial_print(UART_HandleTypeDef *huart,uint8_t num ,char* type[3])
// { 
//     int n=0;
// 	char data[40]="";
// 	if (type == "DEC")
//     {
// 		n=sprintf(&data, "%d\n", num);
// 	}
//     if (type == "HEX")
//     {
// 		n=sprintf(&data, "%#X\n", num);
// 	}
// 	else if (type == "BIN")
// 	{
// 		//Unit16_t max 8 bits
// 		n = 8;
//         long b=0;
//         for (uint8_t i = 0; i < n; i++) {
//             b += ((num >> i) & 1)*pow(10,i);
//         }
// 		//for (uint8_t i = 0; i < n; i++) data[n -1 - i] = ((num >> i) & 1);
//         sprintf(&data, "%08d\n",b);
// 	}
// 	HAL_UART_Transmit(huart, &data, n+1, 100);
// }
/*bool print(uint32_t num ,char* type[]=0)
{
	//Unit16_t max 10 digits
	char a[10]={0};
	sprintf(a,"%d",num);
	HAL_UART_Transmit(&Serial_huart, (uint8_t*)&a, 10, 100);
}*/
	
// bool Serial::begin(uint8_t port, uint32_t baud)
// {
//     UART_HandleTypeDef Serial_huart;

// 	switch (port){
// 	case 1:
// 		#define HUART1
// 		break;
// 		//add other ports below...........................
// 	case 2:
// 		#define HUART2
// 		break;
// 		//add other ports below...........................
// 	case 3:
// 		#define HUART3
// 		break;
// 		//add other ports below...........................
		
// 	default:
// 		#define HUART1
// 		break;
//     }

//     #ifdef HUART1
//         /* USART1 class Configuration */
//         Serial_huart.Instance = USART1;
//         Serial_huart.Init.BaudRate = baud;
//         Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
//         Serial_huart.Init.StopBits = UART_STOPBITS_1;
//         Serial_huart.Init.Parity = UART_PARITY_NONE;
//         Serial_huart.Init.Mode = UART_MODE_TX_RX;
//         Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//         Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
//         if (HAL_UART_Init(&Serial_huart) != HAL_OK)
//         {
//             Error_Handler();
//         }

//         /* USART1 clock enable */
//         __HAL_RCC_USART1_CLK_ENABLE();
    
//         __HAL_RCC_GPIOA_CLK_ENABLE();
//         /**USART1 GPIO Configuration    
//         PA9     ------> USART1_TX
//         PA10     ------> USART1_RX 
//         */
//         GPIO_InitStruct.Pin = GPIO_PIN_9;
//         GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//         GPIO_InitStruct.Pin = GPIO_PIN_10;
//         GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//     #endif

//     #ifdef HUART2
//         /* USART2 class Configuration */
//         Serial_huart.Instance = USART2;
//         Serial_huart.Init.BaudRate = baud;
//         Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
//         Serial_huart.Init.StopBits = UART_STOPBITS_1;
//         Serial_huart.Init.Parity = UART_PARITY_NONE;
//         Serial_huart.Init.Mode = UART_MODE_TX_RX;
//         Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//         Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
//         if (HAL_UART_Init(&Serial_huart) != HAL_OK)
//         {
//             Error_Handler();
//         }

//         /* USART2 clock enable */
//         __HAL_RCC_USART2_CLK_ENABLE();
    
//         __HAL_RCC_GPIOA_CLK_ENABLE();
//         /**USART2 GPIO Configuration    
//         PA2     ------> USART2_TX
//         PA3     ------> USART2_RX 
//         */
//         GPIO_InitStruct.Pin = GPIO_PIN_2;
//         GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//         GPIO_InitStruct.Pin = GPIO_PIN_3;
//         GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        
//     #endif

//     #ifdef HUART3
//         /* USART3 class Configuration */
//         Serial_huart.Instance = USART3;
//         Serial_huart.Init.BaudRate = baud;
//         Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
//         Serial_huart.Init.StopBits = UART_STOPBITS_1;
//         Serial_huart.Init.Parity = UART_PARITY_NONE;
//         Serial_huart.Init.Mode = UART_MODE_TX_RX;
//         Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//         Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
//         if (HAL_UART_Init(&Serial_huart) != HAL_OK)
//         {
//             Error_Handler();
//         }

//         /* USART3 clock enable */
//         __HAL_RCC_USART3_CLK_ENABLE();
    
//         __HAL_RCC_GPIOB_CLK_ENABLE();
//         /**USART3 GPIO Configuration    
//         PB10     ------> USART3_TX
//         PB11     ------> USART3_RX 
//         */
//         GPIO_InitStruct.Pin = GPIO_PIN_10;
//         GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//         GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//         HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//         GPIO_InitStruct.Pin = GPIO_PIN_11;
//         GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//         GPIO_InitStruct.Pull = GPIO_NOPULL;
//         HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//     #endif
// }



//  };
