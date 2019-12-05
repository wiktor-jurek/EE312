#include "LedDriver.h"
#define DELAY 10000
unsigned char ledValue_ = 0;


/*
 * Function:  initialiseLedDial
 * --------------------
 * Initialises GPIO for LED's on MSP430 board
 */
void initialiseLedDial() {
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0);
}

/*
 * Function:  initialiseInterrupts
 * --------------------
 * Initialises GPIO for interrupts
 */
void initialiseInterrupts(){
    // Configure button S1 interrupt
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);  
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN3);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
    
    // Configure button S2 interrupt
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);
}
/*
 * Function:  refreshLedDial
 * --------------------
 * Changes which LED is lit based on the ledValue_ operator
 * Ranges from 1-8, one for each specific LED.
 */
void refreshLedDial() {
  switch(ledValue_){
  case 1 ://LED1          
          GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
          GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7); 
          GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
          GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
          GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
          __delay_cycles(DELAY);
          break;
  case 2://LED2
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
          break;
  case 3://LED3
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
        break;
  case 4://LED4
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
        break;
  case 5://LED8
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
        break;
  case 6: //LED7
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
        break;
  case 7://LED6
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);
        break;
  case 8://LED5
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7); 
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
        __delay_cycles(DELAY);  
        break;
  default:
    break;
  }
}

/*
 * Function:  setLedDial
 * --------------------
 * Changes the ledValue to the value passed in,
 * this helps in changing the speed of the change.
 * 
 * value: value that ledValue_ is to be changed to
 */
void setLedDial(unsigned char value) {
    ledValue_ = value;
}