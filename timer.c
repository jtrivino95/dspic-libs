#include "timer.h"
#include <p30f4011.h>
#include <stdio.h>


#define FREQ_INTERNAL_CLOCK 29491200
#define INTERNAL_CLOCK_INDEX 0
#define PRESCALING_FACTOR 64
#define PRESCALING_FACTOR_INDEX 2


void timerConfig(float freq){
    unsigned int
            max_counter_value = FREQ_INTERNAL_CLOCK / (freq * PRESCALING_FACTOR),
            half_max_counter_value = max_counter_value / 2;

    // Configurar interrupciones
    IEC0bits.T1IE = 1; // Activar interrupción timer 1
    IFS0bits.T1IF = 0; // Limpiar flag de estado (no hay interrupcion)
    IPC0bits.T1IP = 4; // Prioridad por defecto

    // Configurar el registro de control del timer 1
    T1CON = 0x000; // timer parado, sin pre-escalado y reloj interno
    T1CONbits.TCKPS = PRESCALING_FACTOR_INDEX;
    T1CONbits.TCS = INTERNAL_CLOCK_INDEX;
    TMR1 = 0x0000; // Limpiar registro contador
    PR1 = half_max_counter_value;   
}

void timerStart(){
  T1CONbits.TON = 1;
}

void timerStop(){
  T1CONbits.TON = 0;
  TMR1 = 0x0000;
}
