/*
 * file: __utility.hpp
 * purpose: Define some functions to satisfy the AVR linker.
 *
 * credit: https://www.avrfreaks.net/forum/avr-c-micro-how?page=all
 */

#ifndef AVR_TEMPERATURE_SENSOR_UTILITY_HPP
#define AVR_TEMPERATURE_SENSOR_UTILITY_HPP

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release(__guard *);
extern "C" void __cxa_guard_abort(__guard *);
extern "C" void __cxa_pure_virtual(void);

#endif //AVR_TEMPERATURE_SENSOR_UTILITY_HPP
