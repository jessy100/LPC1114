#include "bmptk.h"
#include "timer.h"
#include "sw-uart.h"

void adc_init( void ){
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // enable clock for I/O config
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13); // enable clock for ADC
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);	  // power ADC
	
	LPC_ADC->CR |= (11<<8);
    LPC_ADC->CR |= (0<<16);
	
}

void adc_pin_init( int pin ){
	switch(pin) {
		case 0 :
			LPC_IOCON->R_PIO1_0  &= ~0x8F;	
			LPC_IOCON->R_PIO1_0  |= 0x02; 
			LPC_ADC->CR |= (1<<1);
		break;
		case 1 :
			LPC_IOCON->R_PIO1_1  &= ~0x8F;	
			LPC_IOCON->R_PIO1_1  |= 0x02; 
			LPC_ADC->CR |= (1<<2);
		break;
		case 2 :
			LPC_IOCON->R_PIO1_2  &= ~0x8F;	
			LPC_IOCON->R_PIO1_2  |= 0x02; 
			LPC_ADC->CR |= (1<<3);
		break;
	}
}

int read_adc() {
	LPC_ADC->CR |= (1<<24);
	
	while(1) {
		delay(12);
		if(LPC_ADC->GDR & (0x1 << 31)) {
			break;
		}
		
	}
	
	int value = (LPC_ADC->GDR >> 6) & 0x3FF;
	LPC_ADC->CR |= (0<<24);
	return value;
}