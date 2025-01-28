#ifndef UART_PROCESSOR_H
#define UART_PROCESSOR_H

#include <Arduino.h>

#define DEFAULT_BUFFER_SIZE 128

// Структура для настройки Serial2
typedef struct {
    HardwareSerial *uart;  // Указатель на объект HardwareSerial (например, &Serial2)
    uint32_t baudRate;     // Скорость передачи данных для Serial2
} Serial2Config;

// Структура для хранения данных UART
typedef struct {
    HardwareSerial *uart;       // Указатель на объект HardwareSerial (например, &Serial, &Serial1)
    char buffer[DEFAULT_BUFFER_SIZE]; // Буфер для хранения данных
    uint8_t index;              // Индекс для записи в буфер
    const char *prefix;         // Префикс для отправки в Serial2
    char lineEnding;            // Символ конца строки
    uint32_t baudRate;          // Скорость передачи данных
    Serial2Config *serial2Config; // Конфигурация Serial2
} UARTProcessor;

// Инициализация UARTProcessor
void UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, Serial2Config *serial2Config);

// Инициализация UART
void UARTProcessor_Begin(UARTProcessor *processor);

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor);

#endif