/*
 * file: led.cpp
 * purpose: Implement an LED object using AVR I/O port hardware.
 */

#include <avr/io.h>
#include "led.hpp"


namespace
{

constexpr uint8_t convertPortToAddressOffset(GPIO_PORT port)
{
    return (static_cast<uint8_t>(port) - 1u) * 3;
}

} // anonymous namespace


LED::LED(GPIO_PORT port, uint8_t pin_number)
    : my_pin_number(pin_number),
      my_output_state(STATE::OFF),
      my_port_data_register(&PORTB + convertPortToAddressOffset(port)),
      my_port_direction_register(&DDRB + convertPortToAddressOffset(port)),
      my_port_input_register(&PINB + convertPortToAddressOffset(port))
{
    // Set to output and output state low
    *(this->my_port_direction_register) |= (1u << 5);
    //DDRB |= 1u << PINB5;
    this->setState(STATE::OFF);
    //PORTB &= ~(1 << PINB5);
}


void LED::setState(LED::STATE state)
{
    if (STATE::OFF == state)
    {
        //PORTB &= ~(1 << PINB5);
        *(this->my_port_data_register) &= ~(1u << this->my_pin_number);
    }
    else
    {
        //PORTB |= (1 << PINB5);
        *(this->my_port_data_register) |= (1u << this->my_pin_number);
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
