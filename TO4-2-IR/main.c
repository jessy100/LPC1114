#include "bmptk.h"
#include "pins.h"
#include "timer.h"
			
int main( void ){	
    int n = 6;
    timer_init();
    uart_init();
    pin_configure_as_output(1,4);
    pin_configure_as_input(1,1);
    
    while(1) {
      if(!pin_get(1,1)) {
            pin_set(1,4,1);
            delay(10);
            pin_set(1,4,0); 
            delay(10);
      }                     
    }

}