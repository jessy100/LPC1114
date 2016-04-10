void pin_configure_as_input(int port, int pin) {
  if(port == 0) {
       LPC_GPIO0->DIR = LPC_GPIO0->DIR & ~ ( 0x1 << pin );
  }
  if(port == 1) {
       LPC_GPIO1->DIR = LPC_GPIO1->DIR & ~ ( 0x1 << pin );
  } 
};

void pin_configure_as_output(int port, int pin) {
  if(port == 0) {
      LPC_GPIO0->DIR = LPC_GPIO0->DIR | ( 0x1 << pin ); 
  }
  if(port == 1) {
      LPC_GPIO1->DIR = LPC_GPIO1->DIR | ( 0x1 << pin ); 
  }
}

void pin_set(int port, int pin, unsigned char x) { 
  if(port == 0) {
   if(x) {
          LPC_GPIO0->DATA = LPC_GPIO0->DATA | ( 0x1 << pin );
    } else {
          LPC_GPIO0->DATA = LPC_GPIO0->DATA & ~ ( 0x1 << pin );
    }
  }
  if(port == 1) {
    if(x) {
          LPC_GPIO1->DATA = LPC_GPIO1->DATA | ( 0x1 << pin );
    } else {
          LPC_GPIO1->DATA = LPC_GPIO1->DATA & ~ ( 0x1 << pin );
    }
  }   
     
}
unsigned char pin_get(int port, int pin) {
  if(port == 0) {
      return ( LPC_GPIO0->DATA & ( 0x1 << pin ) ) != 0x0;
  }
  if(port == 1) {
      return ( LPC_GPIO1->DATA & ( 0x1 << pin ) ) != 0x0;
  }
return 0;  
}
