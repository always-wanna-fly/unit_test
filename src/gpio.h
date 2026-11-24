#ifndef GPIO_H
#define GPIO_H
#define GPIO_PORT_COUNT 3
#define GPIO_PIN_COUNT 8

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C
} GPIO_Port;

typedef enum
{
    GPIO_STATUS_OK,
    GPIO_STATUS_INVALID_PIN,
    GPIO_STATUS_NULL_POINTER
} GPIO_Status;

GPIO_Status gpio_read(GPIO_Port port, uint8_t pin, bool *level);

#endif
