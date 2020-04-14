


class Serial{
	extern UART_HandleTypeDef Serial_huart;

	public:
	Serial();
	bool begin(uint8_t port = 3, uint32_t baud = 115200);
	bool print(char* string);
	//bool print(uint8_t num ,char* type[]=0);
	bool print(uint16_t num ,char* type[]=0);
	//bool print(uint32_t num ,char* type[]=0);
	//bool println(char* string);
	//bool println(uint16_t num);	
}


