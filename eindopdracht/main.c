//Main for "Poor mans lidar"
//Author: Jessy Visch

#include "bmptk.h"
#include "pins.h"
#include "timer.h"
#include "sw-uart.h"
#include "sr-04.h"
#include "lcd5510.h"
#include "servo.h"

#define ECHO_PIN 1,8 //Input
#define TRIG_PIN 1,9 //Ouput
#define SERVO_PIN 0,7

int main( void ){
  timer_init();
  uart_init();
  sr04_init(ECHO_PIN, TRIG_PIN);
  lcd5510_init();
  lcd5510_clear();
  servo_init(SERVO_PIN);
  int duration = 0;
  int second = 1000000;
  int n = 2500;
  int scanning = 0;
  int scans = 0;
  char scan_data[99] = {0};
  int distanceLimit = 96;



  servo_reset(SERVO_PIN);

	while(1) {
    //Check for button presses, if pressed set scanmode to true
    if(!pin_get(1,5) && scanning == 0){
      scanning = 1;
    }
    //if scanmode
		if(scanning == 1){
      //move servo to current position +n
      servo_pulse(SERVO_PIN, n);

      //get the duration it takes for the echo to return
			duration = awaitPulse(ECHO_PIN,TRIG_PIN, 16000);
      
      // if the duration returns -1 or is greater then distance limit, output error
			if(duration == -1 || (duration/58) > distanceLimit) {
					uart_put_string("error\n");
			} else {
          //Duration divided by 58 is the distance in centimeters.
          duration = duration/58;
          lcd5510_clear();
          //add latest scan to the data array
          scan_data[scans] = duration;
			}
      //decrease servo angle by ~2 degrees
      n -= 30;
      scans++;
      if(n <= 25){
        scanning = 0;
        uart_put_string("scans: ");
        uart_put_int_decimal(scans);
        uart_put_string("\n");
        int x = 0;
        drawArray(scan_data);
      }
      delay(250000);
		}
    delay(1000 * 30);
	}
}
