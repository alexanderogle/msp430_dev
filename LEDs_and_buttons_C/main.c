
#include "msp430g2553.h"

// Pins for LED and button on port 1
#define LED1    BIT6
#define B1      BIT3

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT = LED1;                             // Preload LED1 OFF
  P1REN &= B1;                              // Enable pull-ups on P1.3
  P1DIR = LED1;                             // Set pin with LED1 to output
  for(;;){                                  // Loop forever
    if((P1IN & B1) == 0){                   // Is button down? 
      P1OUT |= LED1;                        // Yes: Turn LED1 on (active LOW?)
    }                                       
    else {                                  
      P1OUT &= ~LED1;                       // No: Turn LED1 off (active LOW?)
    }
  }     

}
