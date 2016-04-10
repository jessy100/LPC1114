#include "pins.h"

void ultrasonic_init()
{
	
	pin_configure_as_output(1, 1);
	pin_configure_as_intput(1, 0);
}

float getDistance()
{
	float duration, distance;
	pin_set(1,0,0);
	delay(1);
	pin_set(1,0,1);
	delay(1);
	pin_set(1,0,0);
	delay(1);
	
	int startTime = now();
	while(pin_get(1,1)){}
	int endTime = now();
	
	//duration = startTime - endTime;
	//distance = (duration/2) / 29.41176;
	return distance;
}