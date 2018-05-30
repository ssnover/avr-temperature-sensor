/*
 * file: main.cpp
 * purpose: Entry point of the application.
 */

#include <util/delay.h>
#include "led.hpp"
#include "system-tick.hpp"

int main()
{
    // Initialization routines
    SYSTEM_TICK & my_ticker = SYSTEM_TICK::getInstance();
    my_ticker.configure(100u * 1000u);
    my_ticker.start();

    LED & my_blinking_led = LED::getInstance();
    my_blinking_led.setState(LED::STATE::OFF);

    // Loop forever
    while (true)
    {
        //_delay_ms(1000);
        for (auto i = 0; i < 10; ++i)
        {
            my_ticker.waitForTick();
        }
        my_blinking_led.toggleState();
    }
}