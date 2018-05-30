/*
 * file: led.cpp
 * purpose: Implement an LED object using AVR I/O port hardware.
 */

#include <avr/io.h>
#include "led.hpp"


LED::LED()
    : my_output_state(STATE::OFF)
{
    // Set to output and output state low
    DDRB |= (1u << 5);
    PORTB &= ~(1 << PINB5);
}


LED & LED::getInstance()
{
    static LED instance;
    return instance;
}


void LED::setState(LED::STATE state)
{
    if (STATE::OFF == state)
    {
        PORTB &= ~(1 << PINB5);
    }
    else
    {
        PORTB |= (1 << PINB5);
    }

    this->my_output_state = state;
}


void LED::toggleState()
{
    if (STATE::OFF == this->my_output_state)
    {
        this->setState(STATE::ON);
    }
    else
    {
        this->setState(STATE::OFF);
    }
}
