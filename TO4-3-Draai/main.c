#include "bmptk.h"
#include "timer.h"
#include "sw-uart.h"
#include "pins.h"
#include "adc.h"
	
int main( void ){	

  
  timer_init();
  uart_init();
  adc_init();
  adc_pin_init(0);
  
  
  while(1) {
	  
	uart_put_int_decimal(read_adc());
    uart_put_string(" raw ");
    double mV = (read_adc()/1024.0) * 3300;
    double kelvin = (mV/10);
    uart_put_int_decimal(kelvin);
    uart_put_string(" degrees Kelvin ");
      
    double celsius = kelvin - 273.15;
    uart_put_int_decimal(celsius);
    uart_put_string(" degrees Celsius");
    uart_put_string( "\n" );

  }
  
  return 0;
}