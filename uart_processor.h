#ifndef UART_PROCESSOR_H
#define UART_PROCESSOR_H

#include <Arduino.h>

#define DEFAULT_BUFFER_SIZE 128

// Тип колбэк-функции для обработки данных
typedef void (*DataCallback)(const char *data, const char *prefix);

// Структура для хранения данных UART
typedef struct {
    HardwareSerial *uart;       // Указатель на объект HardwareSerial (например, &Serial, &Serial1)
    char buffer[DEFAULT_BUFFER_SIZE]; // Буфер для хранения данных
    uint8_t index;              // Индекс для записи в буфер
    const char *prefix;         // Префикс для отправки данных
    char lineEnding;            // Символ конца строки
    uint32_t baudRate;          // Скорость передачи данных
    DataCallback callback;      // Колбэк-функция для обработки данных
} UARTProcessor;

// Инициализация UARTProcessor
void UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, DataCallback callback);

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor);

#endif