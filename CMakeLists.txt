cmake_minimum_required(VERSION 3.20)

project(embedded_driver_library C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# GPIO Driver
add_library(gpio_driver STATIC
        src/gpio.c
)

target_include_directories(gpio_driver PUBLIC
        src
        hal
)

# Mock HAL
add_library(gpio_mock STATIC
        hal/mock/gpio_hal_mock.c
)

target_include_directories(gpio_mock PUBLIC
        hal/mock
        hal
        src
)

# Unity
add_library(unity STATIC
        unity/src/unity.c
)

target_include_directories(unity PUBLIC
        unity/src
)

# GPIO Unit Tests
add_executable(test_gpio
        test/test_gpio.c
        test/test_button.c
        test/test_main.c
)

target_link_libraries(test_gpio PRIVATE
        button_driver
        gpio_driver
        gpio_mock
        unity
)

# Button Driver
add_library(button_driver STATIC
        src/button.c
)

target_include_directories(button_driver PUBLIC
        src
        hal
)

target_link_libraries(button_driver PUBLIC
        gpio_driver
)

# Sanitizers
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(SANITIZER_FLAGS
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -g
    )

    target_compile_options(gpio_driver PRIVATE ${SANITIZER_FLAGS})
    target_compile_options(gpio_mock PRIVATE ${SANITIZER_FLAGS})
    target_compile_options(test_gpio PRIVATE ${SANITIZER_FLAGS})
    target_compile_options(button_driver PRIVATE ${SANITIZER_FLAGS})

    target_link_options(test_gpio PRIVATE
            -fsanitize=address,undefined
    )

endif()

