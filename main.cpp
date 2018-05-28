/*
 * file: main.cpp
 * purpose: Entry point of the application.
 */

#include "led.hpp"
//#include "system-tick.hpp"

int main()
{
    // Initialization routines
    //SYSTEM_TICK & my_ticker = SYSTEM_TICK::getInstance();
    //my_ticker.configure(100u * 1000u);
    //my_ticker.start();

    LED & my_blinking_led = LED::getInstance<GPIO_PORT::B, 5>();
    my_blinking_led.setState(LED::STATE::OFF);

    // Loop forever
    while (true)
    {
        for (volatile uint32_t i = 0; i < 32000000; ++i)
        {
            asm volatile (" nop\r\n");
        }
        my_blinking_led.toggleState();
    }
}