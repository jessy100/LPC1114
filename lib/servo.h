
#ifndef SERVO_H
#define SERVO_H

#include "timer.h"

//Initilaises the lpc1114fn28's ports.
void servo_init(int pin, int port){
	pin_configure_as_output(pin,port);
	pin_set(pin,port,0);
}

//Set the given pin low
void servo_low(int port,int pin){
	pin_set(port,pin,0);
}

//set the given pin high
void servo_high(int port, int pin){
	pin_set(port,pin,1);
}


void servo_pulse(int port,int pin, int time){
	servo_high(port,pin);
	delay(delay);
	servo_low(port,pin);
}

#endif
