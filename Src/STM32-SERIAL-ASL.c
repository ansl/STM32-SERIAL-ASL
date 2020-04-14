#include "STM32-SERIAL-ASL.h"



 Serial::Serial()
{
}
;

 bool Serial::print(char* string)
{
	HAL_UART_Transmit(&Serial_huart, (uint8_t*) string, sizeof (string)/sizeof (char), 100);
}
;

/*bool Serial::println(char* string)
{
	uint8_t n=sizeof(string)/sizeof(char);
	char* stringln[n+1];
	memcpy(string,stringln,n);
	stringln[n+1]="\n";
	HAL_UART_Transmit(&Serial_huart, (uint8_t*) stringln, n + 1, 100);
}
;*/
/*bool print(uint8_t num ,char* type)
{
	//Unit16_t max 3 digits
	char a[3]={0};
	sprintf(a,"%d",num);
	HAL_UART_Transmit(&Serial_huart, (uint8_t*)&a, 3, 100);
}*/
bool print(uint16_t num ,char* type)
{ 
	char* a;
	uint8_t n = 0;
	
	if (type == "DEC")
	{
		//Unit16_t max 5 digits
		n = 5;
		 a = new char[n];
		sprintf(a, "%d", num);
	}
	else if (type == "BIN")
	{
		//Unit16_t max 16 bits
		n = 16;
		a = new char[n];
		for (uint8_t i = 0; i < n; i++) a[n - 1 - i] = (num >> i) & 1;
	}
		
			HAL_UART_Transmit(&Serial_huart, (uint8_t*)&a, n, 100);
}
/*bool print(uint32_t num ,char* type[]=0)
{
	//Unit16_t max 10 digits
	char a[10]={0};
	sprintf(a,"%d",num);
	HAL_UART_Transmit(&Serial_huart, (uint8_t*)&a, 10, 100);
}*/
	
bool Serial::begin(uint8_t port, uint32_t baud)
{
    UART_HandleTypeDef Serial_huart;

	switch (port){
	case 1:
		#define HUART1
		break;
		//add other ports below...........................
	case 2:
		#define HUART2
		break;
		//add other ports below...........................
	case 3:
		#define HUART3
		break;
		//add other ports below...........................
		
	default:
		#define HUART1
		break;
    }

    #ifdef HUART1
        /* USART1 class Configuration */
        Serial_huart.Instance = USART1;
        Serial_huart.Init.BaudRate = baud;
        Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
        Serial_huart.Init.StopBits = UART_STOPBITS_1;
        Serial_huart.Init.Parity = UART_PARITY_NONE;
        Serial_huart.Init.Mode = UART_MODE_TX_RX;
        Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&Serial_huart) != HAL_OK)
        {
            Error_Handler();
        }

        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
    
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration    
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    #endif

    #ifdef HUART2
        /* USART2 class Configuration */
        Serial_huart.Instance = USART2;
        Serial_huart.Init.BaudRate = baud;
        Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
        Serial_huart.Init.StopBits = UART_STOPBITS_1;
        Serial_huart.Init.Parity = UART_PARITY_NONE;
        Serial_huart.Init.Mode = UART_MODE_TX_RX;
        Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&Serial_huart) != HAL_OK)
        {
            Error_Handler();
        }

        /* USART2 clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();
    
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration    
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        
    #endif

    #ifdef HUART3
        /* USART3 class Configuration */
        Serial_huart.Instance = USART3;
        Serial_huart.Init.BaudRate = baud;
        Serial_huart.Init.WordLength = UART_WORDLENGTH_8B;
        Serial_huart.Init.StopBits = UART_STOPBITS_1;
        Serial_huart.Init.Parity = UART_PARITY_NONE;
        Serial_huart.Init.Mode = UART_MODE_TX_RX;
        Serial_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        Serial_huart.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&Serial_huart) != HAL_OK)
        {
            Error_Handler();
        }

        /* USART3 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();
    
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**USART3 GPIO Configuration    
        PB10     ------> USART3_TX
        PB11     ------> USART3_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    #endif
}