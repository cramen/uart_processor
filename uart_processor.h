#ifndef UART_PROCESSOR_H
#define UART_PROCESSOR_H

#include <Arduino.h>
#include <stdlib.h> // Для malloc и free

// Тип колбэк-функции для обработки данных
typedef void (*DataCallback)(const char *data, const char *prefix);

// Структура для хранения данных UART
typedef struct {
    HardwareSerial *uart;       // Указатель на объект HardwareSerial (например, &Serial, &Serial1)
    char *buffer;               // Динамический буфер для хранения данных
    uint16_t bufferSize;        // Размер буфера
    uint16_t index;             // Индекс для записи в буфер
    const char *prefix;         // Префикс для отправки данных
    char lineEnding;            // Символ конца строки
    uint32_t baudRate;          // Скорость передачи данных
    DataCallback callback;      // Колбэк-функция для обработки данных
} UARTProcessor;

// Инициализация UARTProcessor
bool UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, uint16_t bufferSize, DataCallback callback);

// Освобождение ресурсов UARTProcessor
void UARTProcessor_Destroy(UARTProcessor *processor);

// Инициализация UART
void UARTProcessor_Begin(UARTProcessor *processor);

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor);

#endif