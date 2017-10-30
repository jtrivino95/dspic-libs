#include "buzzer.h"

#define OUTPUT 0

#define ON 0
#define OFF 1

void BuzzerInit(){
    TRISBbits.TRISB7 = OUTPUT;
}

void buzz(unsigned int freq, unsigned int s){
    unsigned int i, j,
            delay = 100000 / freq,
            half_delay = delay / 2;

    unsigned long periods = (long) (freq * s);

    for (i = 0; i < periods; i++) {
        LATBbits.LATB7 = ON;
        for (j = 0; j < half_delay; j++){
            Delay10us();
        }

        LATBbits.LATB7 = OFF;
        for (j = 0; j < half_delay; j++){
            Delay10us();
        }
    }
}
