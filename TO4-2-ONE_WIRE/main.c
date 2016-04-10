// read a DS1990 identity button
// use pin GP0_4 ('SCL')
//

#include "bmptk.h"
#include "timer.h"
#include "sw-uart.h"
#include "pins.h"

// if input
// else output en set 0
void ds_pin_set(int port, int pin, unsigned char x ){
	if(x) {
		pin_configure_as_input(port,pin);
	} else {
		pin_configure_as_output(port,pin);
		pin_set( port, pin, 0);
	}
}

unsigned char ds_pin_get(int port, int pin){
	pin_configure_as_input(port,pin);
	return pin_get(port,pin);
}

void ds_pin_pulse(int port, int pin, unsigned long long int t ){
	ds_pin_set( port,pin, 0 );
	delay( t );
	ds_pin_set(port, pin, 1 );
}

unsigned char ds_present(int port, int pin){

   // give the device time to get back to the 'rest' state
   ds_pin_set( port,pin, 1 );
   delay( 2000 );
   
   // test for stuck-at-0
   if( ! ds_pin_get( port,pin) ){ return 0; }
   
   // request a presence pulse
   ds_pin_pulse( port,pin, 1000 );   
   
   // test for the presence pulse 
   delay( 30 );
   if( ds_pin_get( port,pin) ){ return 0; }
   
   // test whether the presence pulse ends
   delay( 1000 );
   if( ! ds_pin_get( port,pin) ){ return 0; }
   
   // all tests succeeded
   return 1;   
}

void ds_send_bit(int port, int pin, unsigned char b ){


  if(  b == 0 ){
     ds_pin_pulse(port,pin,60);
  } else {
     ds_pin_pulse(port,pin,5);
  }
  
  delay( 100 );
   
}

void ds_send_byte(int port, int pin, unsigned char b ){

  int x;
  char temp;
	for (x = 0; x<8; x++)
	{
		temp = (b>>x);
		temp &= 0x1;    // check meest rechter bit
		ds_send_bit(port,pin,temp);
	}
  delay( 1000 );
}

unsigned char ds_receive_bit( int port, int pin ){
   unsigned char x;
   ds_pin_pulse(port,pin,5);
   delay(5);

    
   x = ds_pin_get(port,pin);
   delay( 100 );
   return x;
}

unsigned char ds_receive_byte(int port, int pin){
   int i;
   unsigned char d = 0;
   for( i = 0; i < 8; i++ ){
      d = d >> 1;
      if( ds_receive_bit(port,pin) ){
         d = d | 0x80;   
      } else {
         d = d & ~ 0x80;
      }
   }
   return d;
}

void ds1990_id_print(int port, int pin){
   int i, d;
   ds_send_byte(port,pin, 0x33 );
   for( i = 0; i < 8; i++ ){
      d = ds_receive_byte(port,pin);
      uart_put_int_hexadecimal( d, 2 );
      uart_put_string( " " );
   }
   uart_put_string( "\n" );
}

int main( void ){	
   timer_init();
   uart_init(); 
   uart_put_string( "DS1990 reader\n" );
   for(;;){
      delay( 500 * 1000 );
      if( ds_present(0,4) ){
         uart_put_string( "***\n" );
         ds1990_id_print(0,4); 
      } else {
         uart_put_string( "-\n" );
      }   
   }  
   return 0;
}