#include "LPC810lib.h"

#define LED1 2
#define LED2 3
#define LED3 4

void kitt( int i ){


    if(i==0) {
       pin_set( LED1, 1);
       pin_set( LED2, 0 );
       pin_set( LED3, 0 );
     }
    if(i==1) {
       pin_set( LED1, 0 );
       pin_set( LED2, 1 );
       pin_set( LED3, 0 );
     }
    if(i==2) {
       pin_set( LED1, 0 );
       pin_set( LED2, 0 );
       pin_set( LED3, 1 );
     }


}

void blink(){

      pin_set( LED1, 1 );
      pin_set( LED2, 1 );
      pin_set( LED3, 1 );
      wait_us( 200 * 1000 );
      pin_set( LED1, 0 );
      pin_set( LED2, 0 );
      pin_set( LED3, 0 );
      wait_us( 200 * 1000 );

}

int main( void ){
   int mode = 0, p = 0,i = 0,t=0;
   pin_configure_as_output( LED1 );
   pin_configure_as_output( LED2 );
   pin_configure_as_output( LED3 );
   pin_configure_as_input(1);

   while(1) {
        if(!pin_get(1)) {
          if(!p) {
            mode++;
            p = 1;
            wait_us( 200 * 1000 );
         }
        } else {
            p = 0;
        }
        if(mode == 0) {
         pin_set( LED1, 0);
         pin_set( LED2, 0 );
         pin_set( LED3, 0 );
        }

        if(mode == 1){
         pin_set( LED1, 1 );
         pin_set( LED2, 1 );
         pin_set( LED3, 1 );
        }
        if(mode == 2){
          blink();
        }
        if(mode == 3){
         kitt(i);
         wait_us( 200 * 1000 );
         if(t) {
             i++;
         } else {
             i--;
         }
         if(i > 2) {
            t=0;
         }
         if(i < 0) {
            t=1;
         }
        }

        if(mode > 3) {
            mode =0;
        }

    }
}
