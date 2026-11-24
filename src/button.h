
#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"

typedef struct
{
    GPIO_Port port;
    uint8_t pin;
    bool active_low;
    uint16_t debounce_ms;
} Button_Config;

typedef struct
{
    Button_Config config;
    bool raw_state;
    bool stable_state;
    uint32_t last_change_time;
    bool initialized;
} Button_Handle;

typedef enum
{
    BUTTON_STATUS_OK,
    BUTTON_STATUS_INVALID_CONFIG,
    BUTTON_STATUS_NULL_POINTER,
    BUTTON_STATUS_GPIO_ERROR,
    BUTTON_STATUS_NOT_INITIALIZED
} Button_Status;

Button_Status button_init(
    Button_Handle *handle,
    const Button_Config *config
);

Button_Status button_is_pressed(
    Button_Handle *handle,
    bool *pressed,
    uint32_t current_time
);

#endif
