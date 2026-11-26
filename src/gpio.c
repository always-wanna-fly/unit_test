#include "gpio.h"
#include "gpio_hal.h"
#include <stddef.h>

#define GPIO_PORT_COUNT 3
#define GPIO_PIN_COUNT 8

GPIO_Status gpio_read(GPIO_Port port, uint8_t pin, bool *level)
{
    if (level == NULL)
    {
        return GPIO_STATUS_NULL_POINTER;
    }

    if (port < GPIO_PORT_A ||
    port >= GPIO_PORT_COUNT ||
    pin >= GPIO_PIN_COUNT)
    {
        return GPIO_STATUS_INVALID_PIN;
    }

    *level = gpio_hal_read(port, pin);

    return GPIO_STATUS_OK;
}
/* Master branch: independent change */