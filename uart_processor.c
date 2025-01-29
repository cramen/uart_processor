#include "uart_processor.h"

// Инициализация UARTProcessor
bool UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, uint16_t bufferSize, DataCallback callback) {
    // Проверка на минимальный размер буфера
    if (bufferSize < 1) {
        return false; // Некорректный размер буфера
    }

    // Выделение памяти под буфер
    processor->buffer = (char *)malloc(bufferSize);
    if (!processor->buffer) {
        return false; // Ошибка выделения памяти
    }

    processor->uart = uart;
    processor->prefix = prefix;
    processor->lineEnding = lineEnding;
    processor->baudRate = baudRate;
    processor->bufferSize = bufferSize;
    processor->index = 0;
    processor->callback = callback;

    return true;
}

// Освобождение ресурсов UARTProcessor
void UARTProcessor_Destroy(UARTProcessor *processor) {
    if (processor->buffer) {
        free(processor->buffer); // Освобождаем память
        processor->buffer = NULL;
    }
}

// Инициализация UART
void UARTProcessor_Begin(UARTProcessor *processor) {
    if (processor->uart) {
        processor->uart->begin(processor->baudRate);
    }
}

// Вспомогательная функция для завершения строки и вызова колбэка
static void _processBuffer(UARTProcessor *processor) {
    processor->buffer[processor->index] = '\0';  // Завершаем строку
    processor->callback(processor->buffer, processor->prefix);  // Вызываем колбэк
    processor->index = 0;  // Сбрасываем индекс буфера
}

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor) {
    if (!processor->uart || !processor->callback || !processor->buffer) {
        return; // Проверка на корректность указателей
    }

    while (processor->uart->available()) {
        char c = processor->uart->read();
        if (c == processor->lineEnding) {  // Если встретился символ конца строки
            if (processor->index > 0) {    // Проверяем, что буфер не пустой
                _processBuffer(processor);
            }
        } else {
            if (processor->index < processor->bufferSize - 1) {
                processor->buffer[processor->index++] = c;  // Добавляем символ в буфер
            } else {
                // Обработка переполнения буфера
                _processBuffer(processor);
            }
        }
    }
}