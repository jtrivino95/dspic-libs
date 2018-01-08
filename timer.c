#include <p30f4011.h>
#include "timer.h"

#define FREQ_INTERNAL_CLOCK 29491200
#define INTERNAL_CLOCK 0

// Configurar el registro de control del timer 1
void timerInit(void){
    T1CON = 0x0000;
    T1CONbits.TCS = 0;

    TMR1 = 0x0000;

    T1CONbits.TCS = INTERNAL_CLOCK;

    IEC0bits.T1IE = 1; // Activar interrupción timer 1
    IFS0bits.T1IF = 0; // Limpiar flag de estado
}

void timerConfig(unsigned int max_counter_value, unsigned char prescaling_factor, unsigned char priority){
    IPC0bits.T1IP = priority;
    T1CONbits.TCKPS = prescaling_factor;
    TMR1 = 0x0000; // Limpiar registro contador
    PR1 = max_counter_value;   
}

void timerStart(){
  T1CONbits.TON = 1;
}

void timerStop(){
  T1CONbits.TON = 0;
  TMR1 = 0x0000;
}