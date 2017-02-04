//------------------------------------------------------------------------------
// aogle_loops.c - program for playing with loops in C
// Check inputs from MSP-EXP430G2 pushbuttons, output this to LEDs
// A J Ogle, 2017-01-26; IAR Kickstart version 6.50.4
//------------------------------------------------------------------------------
#include <io430.h>                          // Header file for MSP430 devices

// Pins for LED and button on port 2
#define LED1    BIT0
#define LED2    BIT6
#define B1      BIT3

/* Function prototype */
void waitForIt(int);
/* Global variables */
int thisCounter = 0;

void main(void){
  WDTCTL = WDTPW | WDTHOLD;                 // stop watchdog timer
  P1OUT = 0x41;                             // Preload all output pins to off
  P1DIR = 0x41;                             // Set LED1 and LED 2 pins as output
  P1SEL = 0x00;                             // Select GPIO function for pins
  P1REN = 0x03;                             // Set the pull-up resistor for P1.3
  
  /* Begin the main function */
  for(;;){
    // Infinite loop to maintain machine state. Put the main code here.
    // Let's just see what the input is on the pushbutton
    if((P1IN & BIT3) == 0){
      // Turn on the lights
      P1OUT = LED1 | LED2;
    }
    else{
      // Turn off the lights
      P1OUT = LED1 & LED2;
    }
  }
  
}

/* Function for waiting by taking up CPU time. Time is in milliseconds. */

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