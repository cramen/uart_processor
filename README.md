## Description
Simple library for uart data processing

## Usage example
```c
#include <Arduino.h>
#include "uart_processor.h"

UARTProcessor uart0Processor;
UARTProcessor uart1Processor;

Serial2Config serial2Config = { &Serial2, 9600 };

void setup() {
    UARTProcessor_Init(&uart0Processor, &Serial, "Rx", '\r', 9600, &serial2Config);
    UARTProcessor_Init(&uart1Processor, &Serial1, "Tx", '\r', 9600, &serial2Config);

    UARTProcessor_Begin(&uart0Processor);
    UARTProcessor_Begin(&uart1Processor);
}

void loop() {
    UARTProcessor_Process(&uart0Processor);
    UARTProcessor_Process(&uart1Processor);
}
```
