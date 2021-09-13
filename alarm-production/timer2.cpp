/*
 * exec.cpp
 * 
 * Created: 28.06.2021 12:40:31
 * Author: ThePetrovich
 */


#include "sched.h"
#include <stdint.h>
#include <avr/io.h>
//#include <avr/iom32u4.h>
#include <avr/interrupt.h>

static sSched_t* tickSched;

/*
void timer2_init(sSched_t* sched) 
{
    tickSched = sched;

    uint8_t sreg = SREG;
    cli();

    TCCR2B |= (1 << CS00);
    TCNT2 = 0;
    OCR2A = 63;

    sei();
    SREG = sreg;
}

void timer2_enable()
{
    uint8_t sreg = SREG;
    cli();

    TIMSK2 = (1 << OCIE2A); 

    sei();
    SREG = sreg;
}

ISR(TIMER2_COMPA_vect)
{
    sched_tick(tickSched);
}*/

/*void timer2_init(sSched_t* sched) 
{
    tickSched = sched;

    uint8_t sreg = SREG;
    cli();

    TCCR4B |= (3 << CS00);
    TCNT4 = 0;
    OCR4A = 63;

    sei();
    SREG = sreg;
}

void timer2_enable()
{
    uint8_t sreg = SREG;
    cli();

    TIMSK4 = (1 << OCIE4A); 

    sei();
    SREG = sreg;
}

ISR(TIMER4_COMPA_vect)
{
    sched_tick(tickSched);
}*/