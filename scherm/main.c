// lines:

#include "bmptk.h"
#include "lcd5510.h"
#include "timer.h"

int rand(){
   static int n = 0;
   n = n * 214013L + 2531011L;
   return ( n >> 16) & 0x7fff;
}

unsigned int random_in_range( unsigned int min, unsigned int max ){
   unsigned int x = rand();
   x = x % ( max - min + 1 );
   return min + x;
}

void drawChar(int x, int y, char c) {
	int i,j;
	char temp;

	for (i = 0; i < 5; i++) {
		temp = ASCII[c - 0x20][i];

		for(j = 0; j < 8; j++) {
			if(temp & (1<<j)) {
				lcd5510_write(x + i,y+j, 1);
			} else {
				lcd5510_write(x + i,y+j, 0);
			}
		}
	}
}

void drawString(int x, int y, char *c) {
    while(*c) {
        drawChar(x,y,*c);
        x+= 6;//font width
        c++;
    }
}

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
