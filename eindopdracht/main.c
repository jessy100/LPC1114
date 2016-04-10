// blink a LED on pin PIO1_4
//
// This is a very simple blink-a-LED application.
// It aims to show direct use of the hardware rather than
// good programming practices (like abstracting from the GPIO pin
// used and using a timer for the delay).
//
// It uses the CMSIS header file to access the direction
// and value registers for pin GPIO1_4.
// It uses a busy-wait for the delay, which can be affected
// by the compiler and optimization settings used.
//
// Note that after a reset the GPIO1_4 pin is automatically
// configured as GPIO, hence there is no need to configure
// the pin. Some other pins are NOT configured to GPIO by a reset,
// hence blinking on such a pin requires the additional step of
// configuring the pin as GPIO.
//

// includes the cmsis definitions for the LPC1114
#include "bmptk.h"
#include "pins.h"
#include "timer.h"
#include "sw-uart.h"
			
int main( void ){
    timer_init();
    uart_init();
	pin_configure_as_output(1,9);
	pin_configure_as_input(1,4);
	pin_configure_as_input(1,1);
	pin_set(1,1,0); // zet laag
	
	int start = 0;
	int stop = 0;


	while(1){
		if(pin_get(1,4)){
			delay(5000);
			pin_set(1,1,1); // zet hoog
			delay(10);
			pin_set(1,1,0); // zet laag
			while(!pin_get(1,9)){
				uart_put_string("waiting for high\n");  
			} //wacht voor hoog
			start = now();     //timer start
			
			while(pin_get(1,9)){
				uart_put_string("waiting for low\n");
			}//wacht op laag
			
			stop = now();        //timer stop
			int timetaken = stop - start;
			int distance = (timetaken/58);
			uart_put_int_decimal(distance);
			uart_put_string("\n");
		
		}
	}
	

}