cmake_minimum_required(VERSION 3.5)
project(avr_temperature_sensor)

set(CMAKE_CXX_STANDARD 14)
set(ARDUINO_DEVICE_PORT /dev/ttyACM0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-threadsafe-statics")

add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        led.hpp led.cpp
        system-tick.hpp system-tick.cpp
        )
# Mark this as a project using the AVR ATmega328P microcontroller
add_definitions(-D__AVR_ATmega328P__)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -lstdc++)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${CMAKE_PROJECT_NAME}.elf
        COMPILE_FLAGS "-save-temps"
        )
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND avr-objcopy -j .text -j .data -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex)

add_custom_target(flash-arduino
        COMMAND avrdude -v -p atmega328p -P ${ARDUINO_DEVICE_PORT} -c arduino -b 115200 -D -U flash:w:${CMAKE_PROJECT_NAME}.hex:i
        DEPENDS ${CMAKE_PROJECT_NAME}
        VERBATIM)