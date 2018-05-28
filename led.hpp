/*
 * file: led.hpp
 * purpose: Defines access to an LED object.
 */

#ifndef LED_HPP
#define LED_HPP


#include "stdint.h"


enum class GPIO_PORT
{
    ERROR   = 0u,
    B       = 1u,
    C       = 2u,
    D       = 3u,
};


class LED final
{

public:

    enum class STATE
    {
        OFF = 0u,
        ON  = 1u,
    };

    template <GPIO_PORT port, uint8_t pin_number>
    static LED & getInstance();

    void setState(STATE state);

    void toggleState();

private:

    LED(GPIO_PORT port, uint8_t pin_number);
    ~LED() = default;

    uint8_t const my_pin_number;
    STATE my_output_state;
    volatile uint8_t * const my_port_data_register;
    volatile uint8_t * const my_port_direction_register;
    volatile uint8_t * const my_port_input_register;

}; // class LED


template <GPIO_PORT port, uint8_t pin_number>
LED & LED::getInstance()
{
    static LED instance(port, pin_number);
    return instance;
}

#endif // LED_HPP