#include <Arduino.h>
#include "uart_processor.h"

// Создаем объекты UARTProcessor
UARTProcessor uart0Processor;
UARTProcessor uart1Processor;

// Конфигурация Serial2
Serial2Config serial2Config = { &Serial2, 9600 };

void setup() {
    // Инициализация UART0 и UART1
    UARTProcessor_Init(&uart0Processor, &Serial, "Rx", '\r', 9600, &serial2Config);
    UARTProcessor_Init(&uart1Processor, &Serial1, "Tx", '\r', 9600, &serial2Config);

    UARTProcessor_Begin(&uart0Processor);
    UARTProcessor_Begin(&uart1Processor);
}

void loop() {
    // Обработка данных с UART0
    UARTProcessor_Process(&uart0Processor);

    // Обработка данных с UART1
    UARTProcessor_Process(&uart1Processor);
}