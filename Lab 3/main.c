/*
 * EE312 Lab 3 Main File
 * Wiktor Jurek 05/12/2019
 * A program that lights the LED's on the MSP430 board in a circle,
 * Button 1 changes the isClockWise of the rotation.
 * Button 2 changes the speed of the led's
 */

#include "main.h"
int SW1_interruptFlag_;
int SW2_interruptFlag_;
bool isClockWise = true;
int speed = 2;
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
     case P1IV_P1IFG3: //Switch 1 interrupt
      	SW1_interruptFlag_ = 1;
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
      break;
      
      case P1IV_P1IFG4:  // Switch 2 interrupt
    	SW2_interruptFlag_ = 1;
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);
      break;
} 
}

int main(void) {
  //Default MCLK = 1MHz
  unsigned char dialValue = 0;  // Counter for enabling specific leds. 
  WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer
  initialiseLedDial();          // Initialise GPIO for LEDS
  initialiseInterrupts();       // Initialise GPIO for interrupts
  __enable_interrupt();         // Enables Interrupts now that we have initialised all
  PMM_unlockLPM5();             // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

  while (1) {                   // Main loop
    if(SW1_interruptFlag_ == 1){        // If our first interrupt has been triggered
        isClockWise  = !isClockWise;    // Change Direction
      SW1_interruptFlag_ = 0;           // Business as usual
    }
    if (isClockWise) {
      dialValue = dialValue + 1;        // Increment up
            if (9 == dialValue)
        dialValue = 0;
    } else {
          dialValue = dialValue - 1;    // Increment down
            if (0 == dialValue)
        dialValue = 9;
    }
    
    if (SW2_interruptFlag_ == 1){       // If our second interrupt has been triggered
      if(speed == 2){                   // Change speed dependant on current speed
      speed = 5;
      } else if (speed == 5){
      speed = 10;
      } else if (speed == 10){
      speed = 2;
      } else {
        speed = 2;
      }
      SW2_interruptFlag_ = 0;           // Business as usual
    }

    setLedDial(dialValue);              // Sets the ledValue_ to the correct value
    for (int i = 0; i < speed; i++){    // Refresh display (speed times for each LED)
      refreshLedDial();                 // Ensures each led is refreshed 'speed' times
    }
  }
}
