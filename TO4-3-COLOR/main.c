// read a DS1990 identity button
// use pin GP0_4 ('SCL')
//

#include "bmptk.h"
#include "timer.h"
#include "sw-uart.h"
#include "pins.h"
#include <stdlib.h>
#include "adc.h"

int colors[6][3] = {  
 {178, 178, 180} ,   /* white */
 {231, 201, 239} ,   /*  green */
 {203, 195, 180} ,  /*  lightblue */
 {177, 183, 223} ,  /*  yellow */
 {181, 217, 246} , /*  red */
 {242, 213, 189}   /*  blue */
};

int colorcorrect = 8;

long map(long x, long in_min, long in_max, long out_min, long out_max)// arduino map fuction 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void test(int r, int g, int b) {  

    int i;
    for(i =0; i < 6; i++) {
        if(abs(r - colors[i][0]) < colorcorrect &&
           abs(g - colors[i][1]) < colorcorrect &&
           abs(b - colors[i][2]) < colorcorrect ){
              switch(i) {
                case 0: 
                     uart_put_string( "wit\n" );
                break;
                case 1: 
                     uart_put_string( "groen\n" );
                break;
                case 2: 
                    uart_put_string( "licht blauw\n" );
                break;
                case 3: 
                    uart_put_string( "geel\n" );
                break;
                case 4: 
                     uart_put_string( "rood\n" );
                break;
                case 5: 
                    uart_put_string( "blauw\n" );
                break;
              } 
        }
    }
}


	
int main( void ){	

  timer_init();
  uart_init();
  adc_init();
  adc_pin_init(2);
  
  pin_configure_as_output(1,4);
  pin_configure_as_output(1,5);
  pin_configure_as_output(1,8);
  pin_configure_as_input(1,9);
  
   pin_set(1,4,0);//rood
   pin_set(1,5,0);//blauw
   pin_set(1,8,0);//groen
   
  int r,g,b;
  int rc,gc,bc;
  int fristrun = 1;
  while(1) {
    if(!pin_get(1,9) ){
        
    
    
        uart_put_string("checking \n" );
        delay(1000 * 1000 *2);
        
        //rood
       pin_set(1,4,1);
       delay(1000 * 500) ;
       r = read_adc();
       pin_set(1,4,0); 
       
       //groen
       pin_set(1,8,1);
       delay(1000 * 500) ;
       g = read_adc();
       pin_set(1,8,0);
       
       //blauw
       pin_set(1,5,1);
       delay(1000 * 500) ;
       b = read_adc();
       pin_set(1,5,0);
       
       if(fristrun){
        
        int temp = (r + g + b) /3;
        
        rc = temp - r;
        gc = temp - g;
        bc = temp - b;
       
        uart_put_string( "correction " );
        uart_put_int_decimal(rc);
        uart_put_string( " " ); 
        uart_put_int_decimal(gc);
        uart_put_string( " " ); 
        uart_put_int_decimal(bc);
        uart_put_string( "\n" );
        fristrun = 0;
      } else {

      uart_put_string( "rood " );
      uart_put_int_decimal(map(r + rc,0,1023,0,255));
      uart_put_string( "\n" );
      uart_put_string( "groen " );
      uart_put_int_decimal(map(g + gc,0,1023,0,255));
      uart_put_string( "\n" );
      uart_put_string( "blauw " );
      uart_put_int_decimal(map(b + bc,0,1023,0,255));
      uart_put_string( "\n" );
      
      test(map(r + rc,0,1023,0,255),map(g + gc,0,1023,0,255),map(b + bc,0,1023,0,255));
       }
     }

  }
  
  return 0;
}