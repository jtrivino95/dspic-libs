#include <p30F4011.h>
#include "buzzer.h"

#define OUTPUT 0

#define ON 0
#define OFF 1

void init_buzzer(){
    TRISBbits.TRISB7 = OUTPUT;
}

void buzz(int freq, int ms){
    int i, j, delay = 100000 / freq;
    int periods = (freq * ms) / 1000;

    for (i = 0; i < periods; i++) {
        LATBbits.LATB7 = ON;
        for (j = 0; j < delay / 2; j++){
            Delay10us();
        }

        LATBbits.LATB7 = OFF;
        for (j = 0; j < delay / 2; j++){
            Delay10us();
        }
    }
}
