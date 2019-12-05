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
 * Initialises the interrupt GPIO on the MSP430 boards
 */
void initialiseInterrupts(){
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);  
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN3);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
}
/*
 * Function:  initialiseADC
 * --------------------
 * Initialises the ADC parameters for optimal usage.
 */
void initialiseADC(){
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION); // 8.1 is our potentiometer - ADC Configured.
  SYSCFG2|=ADCPCTL9;            // 
  ADCCTL0|=ADCSHT_2|ADCON;      // ADCON - Turns the ADC ON. | ADCSHT_2 - Sets the sampling period to 16 samples 
  ADCCTL1|=ADCSHP;              // SAMPCON is sourced from the sample timer
  ADCCTL2|=ADCRES_1;            // Sets the sampling resolution to 10 bits.
  ADCMCTL0|=ADCINCH_9;          //
  ADC_clearInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);         // Interrupt configuration - Clear interrupt
  ADC_enableInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);        // Interrupt configuration - Enable interrupt
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