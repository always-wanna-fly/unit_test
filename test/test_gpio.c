#include "unity.h"

#include "gpio.h"
#include "gpio_hal_mock.h"

void test_gpio_read_high_level(void)
{
    bool level = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    GPIO_Status result = gpio_read(GPIO_PORT_A, 0, &level);

    TEST_ASSERT_EQUAL(GPIO_STATUS_OK, result);
    TEST_ASSERT_TRUE(level);
}

void test_gpio_read_low_level(void)
{
    bool level = true;

    gpio_hal_mock_set_level(GPIO_PORT_A, 1, false);

    GPIO_Status result = gpio_read(GPIO_PORT_A, 1, &level);

    TEST_ASSERT_EQUAL(GPIO_STATUS_OK, result);
    TEST_ASSERT_FALSE(level);
}

void test_gpio_read_invalid_pin(void)
{
    bool level = true;

    GPIO_Status result = gpio_read(GPIO_PORT_A, 8, &level);

    TEST_ASSERT_EQUAL(GPIO_STATUS_INVALID_PIN, result);
    TEST_ASSERT_TRUE(level);
}

void test_gpio_read_null_pointer(void)
{
    GPIO_Status result = gpio_read(GPIO_PORT_A, 0, NULL);

    TEST_ASSERT_EQUAL(GPIO_STATUS_NULL_POINTER, result);
}
