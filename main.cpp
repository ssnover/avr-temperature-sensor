/*
 * file: main.cpp
 * purpose: Entry point of the application.
 */

#include "system-tick.hpp"

int main()
{
    // Initialization routines
    SNO::SYSTEM_TICK & my_ticker = SNO::SYSTEM_TICK::getInstance();
    my_ticker.configure(100u * 1000u);
    my_ticker.start();

    // Loop forever
    while (true)
    {
        my_ticker.waitForTick();
        // toggle an led
    }
}