//Main for "Poor mans lidar"
//Author: Jessy Visch

#include "bmptk.h"
#include "pins.h"
#include "timer.h"
#include "sw-uart.h"
#include "sr-04.h"
#include "lcd5510.h"

#define ECHO_PIN 1,8 //Input
#define TRIG_PIN 1,9 //Ouput

int main( void ){
    timer_init();
    uart_init();
	sr04_init(ECHO_PIN, TRIG_PIN);
    lcd5510_init();
    lcd5510_clear();
    int duration = 0;
	int second = 1000000;

	while(1) {

		if(!pin_get(1,5)){
			duration = awaitPulse(ECHO_PIN,TRIG_PIN, 16000);
			if(duration == -1) {
					uart_put_string("error\n");
			} else {
                    //Duration divided by 58 is the distance in centimeters.
					uart_put_int_decimal(duration/58);
					uart_put_string("\n");
                    lcd5510_clear();
                    drawInt(18,0, duration/58);
			}
			delay(1 * second);
		}
	}
}
