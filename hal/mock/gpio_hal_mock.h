#ifndef GPIO_HAL_MOCK_H
#define GPIO_HAL_MOCK_H

#include "gpio_hal.h"

void gpio_hal_mock_reset(void);
bool gpio_hal_mock_set_level(GPIO_Port port, uint8_t pin, bool level);

#endif
