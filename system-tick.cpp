/*
 * file: system-tick.cpp
 * purpose: Define SYSTEM_TICK implementation for Atmega328P.
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include "system-tick.hpp"


namespace
{
constexpr uint32_t DEFAULT_PERIOD_MICROSECONDS(1000U);
volatile uint32_t number_of_ticks_occurred(0);

void enable_timer1()
{
    TCNT1H = 0;
    TCNT1L = 0;
    // Set Timer 1 prescaler to system clock with divider= 1/64 -> CS12:10 = 0b011
    TCCR1B |= 1u << CS11 | 1u << CS10;
}


void disable_timer1()
{
    // Disable timer 1 -> CS12:10 = 0b000
    TCCR1B &= ~(1u << CS12 | 1u << CS11 << 1u << CS10);
}
} // anonymous namespace


/*
 * Interrupt for handling the system tick events.
 */
/*extern "C" */ ISR(TIMER1_COMPA_vect)
{
    number_of_ticks_occurred++;
}


SYSTEM_TICK::SYSTEM_TICK(uint32_t period_us) : my_period_microseconds(period_us)
{
    // Empty constructor for now, initialization of peripherals comes later
    // Set Timer 1 to CTC mode, this requires WGM 13:10 = 0b0100
    TCCR1B |= 1u << WGM12;
    TCCR1B &= ~(1u << WGM13);
    TCCR1A &= ~(1u << WGM11 | 1u << WGM10);
    // Clock divider assumes 16 MHz clock, 1/64 is 250 kHz -> period of 4 us
    // Make sure the High byte is accessed first!
    OCR1AH = static_cast<uint8_t>((this->my_period_microseconds >> 2u) >> 8u);
    OCR1AL = static_cast<uint8_t>((this->my_period_microseconds >> 2u) & 0xFFu);
    // Enable the interrupt
    sei();
    TIMSK1 |= 1u << OCIE1A;
}


SYSTEM_TICK & SYSTEM_TICK::getInstance()
{
    static SYSTEM_TICK instance(DEFAULT_PERIOD_MICROSECONDS);
    return instance;
}


bool SYSTEM_TICK::configure(uint32_t period_us)
{
    this->my_period_microseconds = period_us;

    // Clock divider assumes 16 MHz clock, 1/64 is 250 kHz -> period of 4 us
    // Make sure the High byte is accessed first!
    OCR1AH = static_cast<uint8_t>((this->my_period_microseconds >> 2u) >> 8u);
    OCR1AL = static_cast<uint8_t>((this->my_period_microseconds >> 2u) & 0xFFu);

    return true;
}


void SYSTEM_TICK::start()
{
    enable_timer1();
    this->my_running_state = true;
}


void SYSTEM_TICK::stop()
{
    disable_timer1();
    this->my_running_state = false;
}


bool SYSTEM_TICK::waitForTick()
{
    bool retVal(false);

    if (this->my_running_state)
    {
        uint32_t current_ticks(number_of_ticks_occurred);
        // Wait for the next tick event
        while (current_ticks == number_of_ticks_occurred) {}
        retVal = true;
    }

    return retVal;
}
