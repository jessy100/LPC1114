// lines:

#include "bmptk.h"
#include "lcd5510.h"
#include "timer.h"

int main( void ){
   int x, y, n, x1, y1;
   timer_init();
   lcd5510_init();
   lcd5510_clear();

   drawString(0,0,"HELLO");

   while(1) {
     for(y = 50; y > -50; y--) {
       drawString(30,y,"world");
       delay(50);
     }
   }
}
