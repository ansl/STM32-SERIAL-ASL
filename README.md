# STM32-SERIAL print printf style 
This library creates aims the creation of a serial print for STM32f1xx devices. 
Syntax:
    - vsprintf wrapper Example:Serial_print(&huart1,"hello world %d %1.4f\n",a,b)
    - binary plotter Example:Serial_print(&huart1,"BIN",a)
    
Requirements:
  This library requires the separated initialization of  UART ports. A new fork will be created with the implicit initialization. 
