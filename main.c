#include <Arduino.h>
#include "uart_processor.h"

// Создаем объекты UARTProcessor
UARTProcessor uart0Processor;
UARTProcessor uart1Processor;

// Колбэк-функция для обработки данных
void handleData(const char *data, const char *prefix) {
    // Выводим данные в Serial2
    Serial2.print(prefix);
    Serial2.print(": ");
    Serial2.println(data);
}

void setup() {
    // Инициализация Serial2
    Serial2.begin(9600);

    // Инициализация UART0 и UART1 с настраиваемым размером буфера
    if (!UARTProcessor_Init(&uart0Processor, &Serial, "Rx", '\r', 9600, 256, handleData)) {
        Serial2.println("Failed to initialize UART0!");
    }
    if (!UARTProcessor_Init(&uart1Processor, &Serial1, "Tx", '\r', 9600, 512, handleData)) {
        Serial2.println("Failed to initialize UART1!");
    }

    UARTProcessor_Begin(&uart0Processor);
    UARTProcessor_Begin(&uart1Processor);
}

void loop() {
    // Обработка данных с UART0
    UARTProcessor_Process(&uart0Processor);

    // Обработка данных с UART1
    UARTProcessor_Process(&uart1Processor);
}

void onDestroy() {
    // Освобождение ресурсов
    UARTProcessor_Destroy(&uart0Processor);
    UARTProcessor_Destroy(&uart1Processor);
}