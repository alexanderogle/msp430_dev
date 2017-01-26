//------------------------------------------------------------------------------
// ledson.c - simple program to light LEDs
// Set pins to output, lights pattern of LEDs, then loops forever
// MSP-EXP430G board with LEDs active low(or is it high?) on P1.0 and P1.6
// A J Ogle, 2017-01-25; IAR Kickstart version 6.50.4
//------------------------------------------------------------------------------
#include <io430.h>                     // Specific device header

int main(void) {
  volatile int i;
  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // set up P1.0 (LED1) as output
  P1DIR = 0x01;
  // intialize P1.0 (LED1) to 0 (off)
  P1OUT = 0x00;
  
  // loop forever 
  for(;;) {
    //toggle LED1 on P1.0
    P1OUT ^= 0x01;
    // Wait! We need to see it at least, yo
    for (i = 0; i < 0x6000; i++){
      // We're just chilling in here until i increments past 0x6000
    }
  }
  
}

