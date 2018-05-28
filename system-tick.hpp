/*
 * file: system-tick.hpp
 * purpose: Define the SYSTEM_TICK class.
 */

#ifndef AVR_TEMPERATURE_SENSOR_SYSTEM_TICK_HPP
#define AVR_TEMPERATURE_SENSOR_SYSTEM_TICK_HPP

#include "stdint.h" // It is incredibly annoying that there is no cstdint in avr-libc


class SYSTEM_TICK final
{
public:

    /*
     * Gets a Singleton instance of a SYSTEM_TICK object.
     */
    static SYSTEM_TICK & getInstance();

    /*
     * Sets the period of the system tick event.
     */
    bool configure(uint32_t period_us);

    /*
     * Runs the system tick.
     */
    void start();

    /*
     * Stops the system tick.
     */
    void stop();

    /*
     * Block until the next event occurs to trigger a system tick.
     *
     * Returns:
     * True if a tick event happened. False if an error occurred.
     */
    bool waitForTick();

private:

    /*
     * Constructor.
     *
     * period - The number of microseconds between system tick events.
     */
    explicit SYSTEM_TICK(uint32_t period_us);
    ~SYSTEM_TICK() = default;

    uint32_t my_period_microseconds; // The number of microseconds between system ticks
    bool my_running_state; // Sets whether the system tick is running or not
};


#endif //AVR_TEMPERATURE_SENSOR_SYSTEM_TICK_HPP
