#include "gpio_hal_mock.h"

#define GPIO_PORT_COUNT 3
#define GPIO_PIN_COUNT 8

static bool pins[GPIO_PORT_COUNT][GPIO_PIN_COUNT];

void gpio_hal_mock_reset(void)
{
    for (uint8_t port = 0; port < GPIO_PORT_COUNT; port++)
    {
        for (uint8_t pin = 0; pin < GPIO_PIN_COUNT; pin++)
        {
            pins[port][pin] = false;
        }
    }
}

bool gpio_hal_mock_set_level(GPIO_Port port, uint8_t pin, bool level)
{
    if (port >= GPIO_PORT_COUNT || pin >= GPIO_PIN_COUNT)
    {
        return false;
    }

    pins[port][pin] = level;
    return true;
}

bool gpio_hal_read(GPIO_Port port, uint8_t pin)
{
    if (port >= GPIO_PORT_COUNT || pin >= GPIO_PIN_COUNT)
    {
        return false;
    }

    return pins[port][pin];
}
