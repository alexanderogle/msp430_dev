//------------------------------------------------------------------------------
// ledson.c - simple program to light LEDs
// Set pins to output, lights pattern of LEDs, then loops forever
// MSP-EXP430G board with LEDs active low(or is it high?) on P1.0 and P1.6
// A J Ogle, 2017-01-25; IAR Kickstart version 6.50.4
//------------------------------------------------------------------------------
#include <io430.h>                     // Specific device header

//function declaration for the light show
void lightShow(int);
#define LED1    BIT0
#define LED2    BIT6

/* Main function here */
void main(void) {
  WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog timer
  P2OUT = ~LED1;                            // Preload LED1 on, LED2 off
  P2DIR = LED1|LED2;                        // Set pins for LED1, 2 to output
  TACTL = MC_2 | ID_3 | TASSEL_2 | TACLR;   // Set up and start Timer A
  // Continuous up mode, divide clock by 8, clock from SMCLK, clear timer
  for(;;){                                  // Loop forever
    while(TA0CTL_bit.TAIFG == 0){            // Wait for overflow
    }                                       // doing nothing
    TA0CTL_bit.TAIFG = 0;                    // Clear overflow flag
    P2OUT ^= LED1 | LED2;                   // Toggle LEDs
  }                                         // Back around infinite loop

}

/* Original main function for doing light shows on MSP430 */
/*
void main_version1(void){
    volatile int i;
  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // set up P1.0 (LED1) and P1.6 as output
  P1DIR = 0x41;
  // intialize all pins to 0 (off)
  P1OUT = 0x00;
  
  // loop forever 
  for(;;) {
    lightShow(2);
  }
}
*/

void lightShow(int sequence){
  // Function for implementing different light shows using a single function
  
  //We declare the functions used in this program first;
  void waitForIt(int);
  
  if(sequence == 1){
    P1OUT = 0x41;
    waitForIt(500);
    P1OUT = 0x00;
    waitForIt(500);
  }
  else if(sequence == 2){
    P1OUT = 0x01;
    waitForIt(500);
    P1OUT = 0x41;
    waitForIt(500);
    P1OUT = 0x40;
    waitForIt(500);
    P1OUT = 0x00;
    waitForIt(500);
  }
}

void waitForIt(int time){
  // A value of 0x6000 in the for loop results in a wait speed of about 
  // a half second. We'll use that to calculate the wait time in terms of
  // milliseconds. (0x6000)base16 == (24,576)base10
  int thisTime = 0;
  //calculate the number of milliseconds required for the timer
  for(int i = 0; i < time; i++){
    // A millisecond is about 49.152 iterations within the for loop
    thisTime += 49;
  }
  for(int i = 0; i < thisTime; i++){
    //Do nothing, just let the CPU run while we wait
  }
}