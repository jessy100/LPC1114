
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
	delay(time);
	servo_low(port,pin);
}

//reset the servo to starting position
void servo_reset(int port, int pin){
		int i = 0;
	  for(i = 0; i < 75; i++){
				servo_pulse(port,pin,2500);
				delay(1000 * 30);
		}
}

#endif
