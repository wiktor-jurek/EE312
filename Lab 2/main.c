/*
 * EE312 Lab 2 Main File
 * Wiktor Jurek 05/12/2019
 * A program that lights the LED's on the MSP430 board in a circle,
 * Button 1 changes the direction of the rotation.
 */
#include "main.h"

int main(void) {
  // Default MCLK = 1MHz
  unsigned char dialValue = 0;  // Counter for enabling specific leds. 
  WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog timer
  bool isClockWise = true;      // Rotation operator
  initialiseLedDial();          // Initialising GPIO for LED's
  initialiseSwitch();           // Initialising GPIO for switch
  PMM_unlockLPM5();             // Disable the GPIO power-on default high-impedance mode 
                                // to activate previously configured port settings

  while (1) {                   // Main Loop
    isClockWise = checkChange(isClockWise); // Check for a button press
    if (isClockWise) {
      dialValue = dialValue + 1;
      if (9 == dialValue)
        dialValue = 0;
    } else {
      dialValue = dialValue - 1;
      if (0 == dialValue)
        dialValue = 9;
    }
    
    setLedDial(dialValue);      // Sets the ledValue_ to the correct one
    for (int i = 0; i < 10; i++)// Refresh display (10 times for each position)
      refreshLedDial();         // Ensures each led is refreshed i times.
  }
}
/*
 * Function:  checkChange
 * --------------------
 * Changes direction if button has been pressed with debouncing
 *
 *  isClokwise: A boolean operator that determines rotation direction
 *
 *  returns: The direction of the rotation after a button press 
 *  (or not press, in which it stays the same)
 */
bool checkChange(bool isClockWise) {
  int pinState = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN3);
  if (pinState == 0) {
    __delay_cycles(1000);       // Debouncing
    if (pinState == 0) {
      return !isClockWise;
    } else {
      return isClockWise;
    }
  } else {
    return isClockWise;
  }
}
