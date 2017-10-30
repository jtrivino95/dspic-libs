#include <p30F4011.h>
#include "delay.h"
#include "adc.h"


void ADCInit(){
  ADPCFG = 0xFF7F;               // all PORTB = Digital; RB2 = analog
  ADCON1 = 0x0004;               // SAMP bit = 0 ends sampling ...
  ADCHS  = 0x0007;              // Connect RB2/AN7 as CH0 input
  ADCSSL = 0;
  ADCON3 = 0x0002;               // Manual Sample, Tad = internal 2 Tcy
  ADCON2 = 0;
  ADCON1bits.ADON = 1;           // turn ADC ON
}

short ADCGetValue(){
    int i; for (i = 0; i < 20; i++) Delay5ms();        // delay 100ms
    ADCON1bits.SAMP = 0;                               // start Converting
    while (!ADCON1bits.DONE);                          // wait for conversion done
    return ADCBUF0;                                    // return ADC value
}
