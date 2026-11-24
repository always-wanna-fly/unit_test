#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"

bool gpio_hal_read(GPIO_Port port, uint8_t pin);

#endif
