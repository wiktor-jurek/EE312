#include <msp430.h>
#include <driverlib.h>

extern void initialiseLedDial();  //Initialise LED Dial, setting GPIO parameters
extern void setLedDial(unsigned char value); //Set dial value
extern void refreshLedDial(); //Refresh the display
extern void initialiseInterrupts(); //Initialise interrupt GPIO