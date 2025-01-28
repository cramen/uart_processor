## Description
Simple library for uart data processing

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
    UARTProcessor_Init(&uart0Processor, &Serial, "Rx", '\r', 9600, handleData);
    UARTProcessor_Init(&uart1Processor, &Serial1, "Tx", '\r', 9600, handleData);
}

void loop() {
    UARTProcessor_Process(&uart0Processor);
    UARTProcessor_Process(&uart1Processor);
}
```
