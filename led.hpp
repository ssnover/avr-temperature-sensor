/*
 * file: led.hpp
 * purpose: Defines access to an LED object.
 */

#ifndef LED_HPP
#define LED_HPP


#include "stdint.h"


class LED final
{

public:

    enum class STATE
    {
        OFF = 0u,
        ON  = 1u,
    };

    static LED & getInstance();

    void setState(STATE state);

    void toggleState();

private:

    LED();
    ~LED() = default;

    STATE my_output_state;

}; // class LED


#endif // LED_HPP