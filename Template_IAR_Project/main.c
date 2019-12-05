#include <msp430.h>
#include <driverlib.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();

    while(1)
    {
        P1OUT ^= BIT0;                      // Toggle P1.0 using exclusive-OR
        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s
    }
}
