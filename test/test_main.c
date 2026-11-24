
#include "unity.h"
#include "gpio_hal_mock.h"

void test_gpio_read_high_level(void);
void test_gpio_read_low_level(void);
void test_gpio_read_invalid_pin(void);
void test_gpio_read_null_pointer(void);
void test_button_active_low_pressed(void);
void test_button_active_low_released(void);
void test_button_active_high_pressed(void);
void test_button_null_handle(void);
void test_button_null_output(void);
void test_button_invalid_port(void);
void test_button_invalid_pin(void);
void test_button_init_null_config(void);

void test_button_debounce_pressed(void);
void test_button_debounce_reject_short_pulse(void);
void test_button_debounce_multiple_transitions(void);
void test_button_not_initialized(void);
void test_button_zero_debounce(void);
void test_button_debounce_timer_overflow(void);
void test_button_reinit_invalid_config(void);
void test_button_gpio_error_preserves_state(void);

void setUp(void)
{
    gpio_hal_mock_reset();
}

void tearDown(void)
{
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_gpio_read_high_level);
    RUN_TEST(test_gpio_read_low_level);
    RUN_TEST(test_gpio_read_invalid_pin);
    RUN_TEST(test_gpio_read_null_pointer);

    RUN_TEST(test_button_active_low_pressed);
    RUN_TEST(test_button_active_low_released);
    RUN_TEST(test_button_active_high_pressed);
    RUN_TEST(test_button_null_handle);
    RUN_TEST(test_button_null_output);

    RUN_TEST(test_button_invalid_port);
    RUN_TEST(test_button_invalid_pin);
    RUN_TEST(test_button_init_null_config);

    RUN_TEST(test_button_debounce_pressed);
    RUN_TEST(test_button_debounce_reject_short_pulse);
    RUN_TEST(test_button_debounce_multiple_transitions);
    RUN_TEST(test_button_not_initialized);
    RUN_TEST(test_button_zero_debounce);
    RUN_TEST(test_button_debounce_timer_overflow);
    RUN_TEST(test_button_reinit_invalid_config);
    RUN_TEST(test_button_gpio_error_preserves_state);

    UNITY_END();
}
