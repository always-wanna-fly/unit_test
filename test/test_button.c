
#include "unity.h"

#include "button.h"
#include "gpio_hal_mock.h"

void test_button_active_low_pressed(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 0)
    );

    TEST_ASSERT_TRUE(pressed);
}

void test_button_active_low_released(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = true;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 0)
    );

    TEST_ASSERT_FALSE(pressed);
}

void test_button_active_high_pressed(void)
{
    Button_Config config = {
        .port = GPIO_PORT_B,
        .pin = 3,
        .active_low = false,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_B, 3, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 0)
    );

    TEST_ASSERT_TRUE(pressed);
}

void test_button_null_handle(void)
{
    bool pressed = false;

    Button_Status status = button_is_pressed(
        NULL,
        &pressed,
        0
    );

    TEST_ASSERT_EQUAL(BUTTON_STATUS_NULL_POINTER, status);
}

void test_button_null_output(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    Button_Status status = button_is_pressed(
        &handle,
        NULL,
        0
    );

    TEST_ASSERT_EQUAL(BUTTON_STATUS_NULL_POINTER, status);
}

void test_button_invalid_port(void)
{
    Button_Config config = {
        .port = (GPIO_Port)-1,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};

    Button_Status status = button_init(&handle, &config);

    TEST_ASSERT_EQUAL(BUTTON_STATUS_INVALID_CONFIG, status);
}

void test_button_invalid_pin(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 8,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};

    Button_Status status = button_init(&handle, &config);

    TEST_ASSERT_EQUAL(BUTTON_STATUS_INVALID_CONFIG, status);
}

void test_button_init_null_config(void)
{
    Button_Handle handle = {0};

    Button_Status status = button_init(&handle, NULL);

    TEST_ASSERT_EQUAL(BUTTON_STATUS_NULL_POINTER, status);
}

void test_button_init_null_handle(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Status status = button_init(NULL, &config);

    TEST_ASSERT_EQUAL(BUTTON_STATUS_NULL_POINTER, status);
}

void test_button_debounce_pressed(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 100)
    );
    TEST_ASSERT_FALSE(pressed);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 119)
    );
    TEST_ASSERT_FALSE(pressed);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 120)
    );
    TEST_ASSERT_TRUE(pressed);
}

void test_button_debounce_reject_short_pulse(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 100)
    );

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 110)
    );

    TEST_ASSERT_FALSE(pressed);
    TEST_ASSERT_TRUE(handle.stable_state);
}

void test_button_debounce_multiple_transitions(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    // Натискання
    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);

    button_is_pressed(&handle, &pressed, 100);
    button_is_pressed(&handle, &pressed, 120);

    TEST_ASSERT_TRUE(pressed);

    // Відпускання
    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    button_is_pressed(&handle, &pressed, 130);
    button_is_pressed(&handle, &pressed, 150);

    TEST_ASSERT_FALSE(pressed);
}

void test_button_not_initialized(void)
{
    Button_Handle handle = {0};
    bool pressed = false;

    Button_Status status = button_is_pressed(
        &handle,
        &pressed,
        100
    );

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_NOT_INITIALIZED,
        status
    );
}


void test_button_zero_debounce(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 0
    };

    Button_Handle handle = {0};
    bool pressed = false;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    // Натискання
    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_is_pressed(&handle, &pressed, 100)
    );

    TEST_ASSERT_TRUE(pressed);
}

void test_button_debounce_timer_overflow(void) {
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 10
    };
    Button_Handle handle = {0};
    bool pressed = true;

    /* Початковий стан GPIO — HIGH (для active_low = true це відпущена кнопка) */
    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);
    TEST_ASSERT_EQUAL(BUTTON_STATUS_OK, button_init(&handle, &config));

    /* Змінюємо GPIO на LOW і фіксуємо last_change_time = 0xFFFFFFFA */
    gpio_hal_mock_set_level(GPIO_PORT_A, 0, false);
    TEST_ASSERT_EQUAL(BUTTON_STATUS_OK, button_is_pressed(&handle, &pressed, 0xFFFFFFFAu));
    TEST_ASSERT_FALSE(pressed);

    /* Перед самим переповненням (0xFFFFFFFF): минуло 5 мс < 10 мс */
    TEST_ASSERT_EQUAL(BUTTON_STATUS_OK, button_is_pressed(&handle, &pressed, 0xFFFFFFFFu));
    TEST_ASSERT_FALSE(pressed);

    /* Після переповнення таймера до 4: минуло 10 мс >= 10 мс */
    TEST_ASSERT_EQUAL(BUTTON_STATUS_OK, button_is_pressed(&handle, &pressed, 4u));
    TEST_ASSERT_TRUE(pressed);
}

void test_button_reinit_invalid_config(void)
{
    Button_Config valid_config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Config invalid_config = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_COUNT,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &valid_config)
    );

    TEST_ASSERT_TRUE(handle.initialized);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_INVALID_CONFIG,
        button_init(&handle, &invalid_config)
    );

    TEST_ASSERT_FALSE(handle.initialized);
}

void test_button_gpio_error_preserves_state(void)
{
    Button_Config config = {
        .port = GPIO_PORT_A,
        .pin = 0,
        .active_low = true,
        .debounce_ms = 20
    };

    Button_Handle handle = {0};
    bool pressed = true;

    gpio_hal_mock_set_level(GPIO_PORT_A, 0, true);

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_OK,
        button_init(&handle, &config)
    );

    // Запам'ятовуємо відомий стан
    handle.raw_state = false;
    handle.stable_state = true;
    handle.last_change_time = 100;

    // Навмисно пошкоджуємо конфігурацію
    handle.config.pin = GPIO_PIN_COUNT;

    Button_Status status = button_is_pressed(
        &handle,
        &pressed,
        150
    );

    TEST_ASSERT_EQUAL(
        BUTTON_STATUS_GPIO_ERROR,
        status
    );

    TEST_ASSERT_FALSE(handle.raw_state);
    TEST_ASSERT_TRUE(handle.stable_state);
    TEST_ASSERT_EQUAL_UINT32(100, handle.last_change_time);

    TEST_ASSERT_TRUE(pressed);
}