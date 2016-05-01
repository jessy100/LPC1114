//Library for the SR04 Ultrasonic Sensor.
//Author: Jessy Visch
//AwaitPulse function is based on adruino's pulseIn function.

#ifndef SR04_H
#define SR04_H

#include "timer.h"

int awaitPulse(int echoPort, int echoPin, int trigPort, int trigPin, unsigned int t ){
	sr04_pulse(trigPort,trigPin);
	
	int start = now();
	
	while(!pin_get(echoPort, echoPin)){
		if(t+start < now()) {
			return -1;
		}
	}
	
	start = now();
	
	while(pin_get(echoPort, echoPin)) {
		if(t+start < now()) {
			return -1;
		}
	}
	
	int current = now();
	return current - start;
}

void sr04_init(int echoPort, int echoPin, int trigPort, int trigPin){
	pin_configure_as_input(echoPort,echoPin);
	pin_configure_as_output(trigPort,trigPin);
	pin_set(trigPort,trigPin,0); 
}

void sr04_low(int port,int pin){
	pin_set(port,pin,0);
}

void sr04_high(int port, int pin){
	pin_set(port,pin,1);
}

void sr04_pulse(int port,int pin){
	sr04_high(port,pin);
	delay(10);
	sr04_low(port,pin);
}

#endif