/*
 * EE312 Lab 4 Main File
 * Wiktor Jurek 05/12/2019
 * A program that lights the LED's on the MSP430 board in a circle,
 * Button 1 changes the direction of the rotation.
 * ADC is used with the potentiometer to change speed of LED's
 */
#include "main.h"
int SW1_interruptFlag_;
bool direction = true;
int speed = 2;
int rate_ = 0;
#pragma vector=ADC_VECTOR           // these two lines are used by IAR and CCC
/*
 * Function:  ADC_ISR
 * --------------------
 * ADC interrupt service routine changes the speed based on pot position
 */
__interrupt void ADC_ISR(void)
{
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
  {
    case ADCIV_ADCIFG:              // Conversion complete case interrupt routine:
      speed = ADCMEM0/100;          // MEM0 is the output of the ADC - pot position
      ADC_clearInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);  //Clear the interrupt
    break;
  }
  }

/*
 * Function:  P1_ISR
 * --------------------
 * An function that runs upon an inturrupt on Switch 1 or Switch 2
 * These set the flags accordingly
 */
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
 switch(__even_in_range(P1IV,P1IV_P1IFG7)) 
{
     case P1IV_P1IFG3:
      	SW1_interruptFlag_ = 1;         // Raise interrupt flag when button 1 is pressed.
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
      break;
} 
}

int main(void) {                
  //Default MCLK = 1MHz
  unsigned char dialValue = 0;  // Counter for enabling specific leds. 
  WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer
  initialiseLedDial();          // Initialise the LED GPIO
  initialiseADC();              // Set the ADC parameters
  initialiseInterrupts();       // Initialises the interrupts GPIO
  __enable_interrupt();         // Enable Interrupts
  PMM_unlockLPM5();             // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings


  while (1) {                           // Main Loop
    ADCCTL0 |= 0x03;                    // ADC enable conversion

    if(SW1_interruptFlag_ == 1){        // In the case of a button press
        direction  = !direction;        // Change direction
      SW1_interruptFlag_ = 0;           // Business as usual
    }
    if (direction) {
      dialValue = dialValue + 1;        // Go forwards
            if (9 == dialValue)
        dialValue = 0;
    } else {
          dialValue = dialValue - 1;    // Go Backwards
            if (0 == dialValue)
        dialValue = 9;
    }
    
    setLedDial(dialValue);              // Sets the ledvalue_ to the correct value
    for(int i = 0; i<=speed; i++){      // Refresh the display (speed times for each LED)
    refreshLedDial();                   // Ensures each led is refreshed 'speed' times
    }
  }
}



