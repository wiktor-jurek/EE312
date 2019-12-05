/**************************************************
 * EE312 Lab 4
 *
 * Copyright 2015 University of Strathclyde
 *
 *
 **************************************************/
#include <msp430.h>
#include <driverlib.h>
#include "LedDriver.h"
#include <stdio.h>
#include "hal_LCD.h"
int SW1_interruptFlag_;
bool direction = true;
int speed = 2;
int rate_ = 0;
//There are 6 ADC related interrupts – typically we only care about the conversion complete case:
// ADC interrupt service routine
void initialiseADC();

#pragma vector=ADC_VECTOR           // these two lines are used by IAR and CCC
__interrupt void ADC_ISR(void)
{
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
  {
    case ADCIV_ADCIFG:              // conversion complete
      speed = ADCMEM0/100;
      ADC_clearInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);
    break;
  }
  }

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
 switch(__even_in_range(P1IV,P1IV_P1IFG7)) 

{
     case P1IV_P1IFG3: //It is SW1
      	SW1_interruptFlag_ = 1;
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
      break;
} 
}

int main(void) {
  int rotations = 0;
  int units = 0;
  int tens = 0;
  int hundreds = 0;
  int thousands = 0;
  
  //Default MCLK = 1MHz

  unsigned int i = 0;
  unsigned char dialValue = 0;
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

  Init_LCD();
  displayScrollText("HELLO");
  initialiseLedDial();
  initialiseADC();
  __enable_interrupt();
  // Disable the GPIO power-on default high-impedance mode
  // to activate previously configured port settings
  PMM_unlockLPM5();
  while (1) {  
    // char str[7];
   // strcat(str,"N: ");
    // strcat(str,rotations);
    // displayScrollText(str);
    ADCCTL0 |= 0x03; //ADC enable conversion

    if(SW1_interruptFlag_ == 1){
        direction  = !direction;
      SW1_interruptFlag_ = 0; // Business as usual
    }
    if (direction) {
      dialValue = dialValue + 1;
            if (9 == dialValue)
        dialValue = 0;
    } else {
          dialValue = dialValue - 1;
            if (0 == dialValue)
        dialValue = 9;
    }
    
    //Set value
    setLedDial(dialValue);
    rotations++;
    
    if(rotations == 8){
      rotations = 0;
      units++;
      if(units == 10){
        units = 0;
        tens++;
      }
    if(tens == 10){
      tens = 0;
    hundreds++;
    }
    if(hundreds == 10){
      hundreds = 0;
    thousands++;
    }
    if (thousands == 10){
    thousands = 0;
    tens++;
    }
    showChar(thousands + 48,8);
    showChar(hundreds + 48,10);
    showChar(tens + 48,2);
    showChar(units + 48,18);
    }
    
    showChar('N',4);//positinos go - 4, 8, 10, 2, 18

    //Refresh display ('speed' times for each position)
    for(i = 0; i<=speed; i++){
    refreshLedDial();
    }
  }
}

void initialiseADC(){
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
  SYSCFG2|=ADCPCTL9;
  ADCCTL0|=ADCSHT_2|ADCON;
  ADCCTL1|=ADCSHP;
  ADCCTL2|=ADCRES_1;
  ADCMCTL0|=ADCINCH_9;
  ADC_clearInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);
  ADC_enableInterrupt(ADC_BASE,ADC_COMPLETED_INTERRUPT);
}
