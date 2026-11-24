#include <stddef.h>
#include "button.h"


Button_Status button_init(
    Button_Handle *handle,
    const Button_Config *config)
{
    if (handle == NULL)
    {
        return BUTTON_STATUS_NULL_POINTER;
    }

    handle->initialized = false;

    if (config == NULL)
    {
        return BUTTON_STATUS_NULL_POINTER;
    }

    if (config->port < GPIO_PORT_A ||
        config->port >= GPIO_PORT_COUNT ||
        config->pin >= GPIO_PIN_COUNT)
    {
        return BUTTON_STATUS_INVALID_CONFIG;
    }

    bool initial_level = false;

    GPIO_Status status = gpio_read(
        config->port,
        config->pin,
        &initial_level
    );

    if (status != GPIO_STATUS_OK)
    {
        return BUTTON_STATUS_GPIO_ERROR;
    }

    handle->config = *config;
    handle->raw_state = initial_level;
    handle->stable_state = initial_level;
    handle->last_change_time = 0;
    handle->initialized = true;

    return BUTTON_STATUS_OK;
}



Button_Status button_is_pressed(
    Button_Handle *handle,
    bool *pressed,
    uint32_t current_time)
{
    if (handle == NULL || pressed == NULL)
    {
        return BUTTON_STATUS_NULL_POINTER;
    }

    if (!handle->initialized)
    {
        return BUTTON_STATUS_NOT_INITIALIZED;
    }

    bool level = false;

    GPIO_Status status = gpio_read(
        handle->config.port,
        handle->config.pin,
        &level
    );

    if (status != GPIO_STATUS_OK)
    {
        return BUTTON_STATUS_GPIO_ERROR;
    }

    // Виявляємо зміну фізичного сигналу
    if (level != handle->raw_state)
    {
        handle->raw_state = level;
        handle->last_change_time = current_time;
    }

    // Перевіряємо, чи сигнал стабільний достатньо довго
    if ((uint32_t)(current_time - handle->last_change_time)
        >= handle->config.debounce_ms)
    {
        handle->stable_state = handle->raw_state;
    }

    // Перетворюємо фізичний рівень на логічний стан кнопки
    *pressed = handle->config.active_low
        ? !handle->stable_state
        : handle->stable_state;

    return BUTTON_STATUS_OK;
}


