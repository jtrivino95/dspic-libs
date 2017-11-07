#include <p30F4011.h>
#include "leds.h"


#define LED0 LATEbits.LATE0
#define LED1 LATEbits.LATE1
#define LED2 LATEbits.LATE2
#define LED3 LATEbits.LATE3
#define LED4 LATEbits.LATE4
#define LED5 LATEbits.LATE5

#define INPUT 1
#define OUTPUT 0


void init_leds(){
    TRISEbits.TRISE0 = OUTPUT;
    TRISEbits.TRISE1 = OUTPUT;
    TRISEbits.TRISE2 = OUTPUT;
    TRISEbits.TRISE3 = OUTPUT;
    TRISEbits.TRISE4 = OUTPUT;
    TRISEbits.TRISE5 = OUTPUT;

    LED0 = LED_OFF;
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
    LED5 = LED_OFF;
}

void set_led(int nled, int status){
    switch(nled){
        case 0:
            LED0 = status;
            break;
        case 1:
            LED1 = status;
            break;
        case 2:
            LED2 = status;
            break;
        case 3:
            LED3 = status;
            break;
        case 4:
            LED4 = status;
            break;
        case 5:
            LED5 = status;
            break;
    }
}

void toggle(int nled){
    switch(nled){
        case 0:
            LED0 = ~LED0;
            break;
        case 1:
            LED1 = ~LED1;
            break;
        case 2:
            LED2 = ~LED2;
            break;
        case 3:
            LED3 = ~LED3;
            break;
        case 4:
            LED4 = ~LED4;
            break;
        case 5:
            LED5 = ~LED5;
            break;
    }
}
