#include "uart_processor.h"

// Инициализация UARTProcessor
void UARTProcessor_Init(UARTProcessor *processor, HardwareSerial *uart, const char *prefix, char lineEnding, uint32_t baudRate, Serial2Config *serial2Config) {
    processor->uart = uart;
    processor->prefix = prefix;
    processor->lineEnding = lineEnding;
    processor->baudRate = baudRate;
    processor->index = 0;
    processor->serial2Config = serial2Config;

    // Инициализация Serial2, если конфигурация предоставлена
    if (processor->serial2Config && processor->serial2Config->uart) {
        processor->serial2Config->uart->begin(processor->serial2Config->baudRate);
    }
}

// Инициализация UART
void UARTProcessor_Begin(UARTProcessor *processor) {
    if (processor->uart) {
        processor->uart->begin(processor->baudRate);
    }
}

static void UARTProcessor_FlushBuffer(UARTProcessor *processor) {
    if (processor->index > 0) {    // Проверяем, что буфер не пустой
        processor->buffer[processor->index] = '\0';  // Завершаем строку
        processor->serial2Config->uart->print(processor->prefix);  // Добавляем префикс
        processor->serial2Config->uart->println(processor->buffer);  // Отправляем сообщение в Serial2
        processor->index = 0;  // Сбрасываем индекс буфера
    }
}

// Обработка данных
void UARTProcessor_Process(UARTProcessor *processor) {
    if (!processor->uart || !processor->serial2Config || !processor->serial2Config->uart) {
        return; // Проверка на корректность указателей
    }

    while (processor->uart->available()) {
        char c = processor->uart->read();
        if (c == processor->lineEnding) {  // Если встретился символ конца строки
            UARTProcessor_FlushBuffer(processor);
        } else {
            if (processor->index < DEFAULT_BUFFER_SIZE - 1) {
                processor->buffer[processor->index++] = c;  // Добавляем символ в буфер
            } else {
                UARTProcessor_FlushBuffer(processor); // Обработка переполнения буфера
            }
        }
    }
}