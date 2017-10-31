#include "timer.h"
#include <p30f4011.h>
#include <math.h>


void timerInit(float freq){

    signed long frecuencia_reloj_interno = 29491200;
    signed int
            factor_preescalado = 64,
            index_preescalado = 2,
            valor_a_alcanzar = ceilf(frecuencia_reloj_interno / (freq * factor_preescalado)),
            half_valor_a_alcanzar = valor_a_alcanzar / 2;

    // Configurar interrupciones
    IEC0bits.T1IE = 1; // Activar interrupción timer 1
    IFS0bits.T1IF = 0; // Limpiar flag de estado (no hay interrupcion)
    IPC0bits.T1IP = 4; // Prioridad por defecto

    // Configurar el registro de control del timer 1
    T1CON = 0x000; // timer parado, sin pre-escalado y reloj interno
    T1CONbits.TCKPS = index_preescalado; // 1:64    // TODO: (Si se usan distintos preescalados para cada freq, se gana precision)
    T1CONbits.TCS = 0; // Interna, 30 MHz, 29491200 Hz
    TMR1 = 0x0000; // Limpiar registro contador
    PR1 = half_valor_a_alcanzar;
    
}

void timerStart(){
  T1CONbits.TON = 1;
}

void timerStop(){
  T1CONbits.TON = 0;
  TMR1 = 0x0000; // mejor en timerStart??
}
