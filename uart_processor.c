#include "uart_processor.h"

// Инициализация UARTProcessor
void UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, DataCallback callback) {
    processor->uart = uart;
    processor->prefix = prefix;
    processor->lineEnding = lineEnding;
    processor->baudRate = baudRate;
    processor->index = 0;
    processor->callback = callback;
    if (processor->uart) {
        processor->uart->begin(processor->baudRate);
    }
}

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor) {
    if (!processor->uart || !processor->callback) {
        return; // Проверка на корректность указателей
    }

    while (processor->uart->available()) {
        char c = processor->uart->read();
        if (c == processor->lineEnding) {  // Если встретился символ конца строки
            if (processor->index > 0) {    // Проверяем, что буфер не пустой
                processor->buffer[processor->index] = '\0';  // Завершаем строку
                processor->callback(processor->buffer, processor->prefix);  // Вызываем колбэк
                processor->index = 0;  // Сбрасываем индекс буфера
            }
        } else {
            if (processor->index < DEFAULT_BUFFER_SIZE - 1) {
                processor->buffer[processor->index++] = c;  // Добавляем символ в буфер
            } else {
                // Обработка переполнения буфера
                processor->buffer[processor->index] = '\0';  // Завершаем строку
                processor->callback(processor->buffer, "Buffer overflow!");  // Вызываем колбэк
                processor->index = 0;  // Сбрасываем индекс буфера
            }
        }
    }
}