//! @file
//! This library implements a timer so there is a sensible way to mesure time

#ifndef NINCLUDE_TIMER_H
#define NINCLUDE_TIMER_H

//! initialize the timer 
//
//! Call this function to initialize the timer.
void timer_init( void );


//! Get the current time
//
//! Call this function to get the time that has passed since init.
unsigned int now();

//! Wait for t microseconds
//
//! Call this function to let the programm wait for t microseconds.
void await( unsigned int t );

//! Wait for x mivroseconds
//
//! Call this function to let the programm wait for x microseconds.
//! TODO
void delay( unsigned int x);

#endif