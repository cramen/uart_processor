## Description
Simple library for uart data processing for arduino

## Usage example
```c
#include <Arduino.h>
#include "uart_processor.h"

UARTProcessor uart0Processor;
UARTProcessor uart1Processor;

void handleData(const char *data, const char *prefix) {
    Serial2.print(prefix);
    Serial2.print(": ");
    Serial2.println(data);
}

void setup() {
    Serial2.begin(9600);

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
    UARTProcessor_Process(&uart0Processor);
    UARTProcessor_Process(&uart1Processor);
}

void onDestroy() {
    UARTProcessor_Destroy(&uart0Processor);
    UARTProcessor_Destroy(&uart1Processor);
}
```
