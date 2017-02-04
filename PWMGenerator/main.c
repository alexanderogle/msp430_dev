/*******************************************************************************
 *  Code for generating PWM signals using the onboard clocks of the MSP430     *
 *  Alexander J. Ogle                                                          *
 *  2017-02-03                                                                 *
 ******************************************************************************/
#include <msp430g2553.h>
/* This should already be defined in the above header file, but I get an error 
stating LMP0_bits is undefined, so we'll define it here */
#define LMP0_bits           (0x0010u)

void main( void )
{
  // Construct prototypes of functions we'll use later in this function
  /* PWMSignal( period, intensity, output pin, timer number) */
  void PWMSignal(int, int, char, int);
  
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  /*
  P1DIR |= BIT2;                            // P1.2 to output
  P1SEL |= BIT2;                            // P1.2 to TA0.1
  
  CCR0 = 1000-1;                              // PWM period          - frequency
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 100;                               // CCR1 PWM duty cycle - intensity
  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
  
  _BIS_SR(LMP0_bits);                       // Enter LMP0
  */
 
  // We can setup a varying PWM signal by resetting the values continuously.
  // There is probably a better way to go about doing this. 
  for(;;){
    // Code to run forever
    int frequencyLower = 100;
    int frequencyUpper = 1000;
    int intensity = 100;
    volatile int i = frequencyLower;
    for(i; i < frequencyUpper; i++){
      // Turn up the frequency of the PWM pulse
      PWMSignal(i, intensity-1, BIT2, 1);
    }
    for(i; i >= frequencyLower; i--){
      // Turn down the frequency of the PWM pulse
      PWMSignal(i, intensity-1, BIT2, 1);
    }
    
  }
  // PWMSignal(1000, 100, BIT2, 1);
}


/* PWMSignal generates a PWM signal using one of the MSP430G2553's onboard 
 * timers. This function needs some work. For now (2017-02-03), just make sure
 * you use outputPin = BIT2 and timerNumber = 1, and you'll be alright. 
 */
void PWMSignal( int period, int intensity, char outputPin, int timerNumber ){
  if ( timerNumber == 1 ){
    // Run code to setup the PWM signal to the output pin using Timer 1
    // We'll assume the output pin is for P1.X
    P1DIR |= outputPin;                     // P1.X to output
    P1SEL |= outputPin;                     // P1.X to TA0.1
    
    CCR0 = period-1;                     // PWM period (frequency of signal)
    CCTL1 = OUTMOD_7;                       // CCR1 reset/set
    CCR1 = intensity;                             // CCR1 PWM duty cycle - intensity
    TACTL = TASSEL_2 + MC_1;                // SSMCLK, up mode
    
    // Removed this as it ruined my ability to use the debugger while the chip 
    // is operating, since the debugger relies on interrupts. 
    //_BIS_SR(LMP0_bits);                     // Enter low power mode 0
  }
  else if (timerNumber == 2 ){
    /* This section not intended to work... need to read through reference 
     * manual in order to verify pin connections
     */
    // Run code to setup the PWM signal to the output pin using Timer 2
    // We'll assume the output pin is for P2.X
    P2DIR |= outputPin;                     // P2.X to output
    P2SEL |= outputPin;                     // P2.X to TA0.2
    
    CCR0 = period-1;                     // PWM period (frequency of signal)
    CCTL1 = OUTMOD_7;                       // CCR1 reset/set
    CCR1 = intensity;                             // CCR1 PWM duty cycle - intensity
    TACTL = TASSEL_2 + MC_1;                // SSMCLK, up mode
    
    _BIS_SR(LMP0_bits);                     // Enter low power mode 0
  }
}