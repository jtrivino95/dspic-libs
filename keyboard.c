#include <p30F4011.h>
#include "delay.h"
#include "keyboard.h"


#define COLUMNA0   LATBbits.LATB0
#define COLUMNA1   LATBbits.LATB1
#define COLUMNA2   LATBbits.LATB2

#define FILA0   PORTDbits.RD0
#define FILA1   PORTDbits.RD1
#define FILA2   PORTDbits.RD2
#define FILA3   PORTDbits.RD3

#define INPUT 1
#define OUTPUT 0

#define ON 0
#define OFF 1


void keyboardInit(){
    TRISBbits.TRISB0 = OUTPUT;
    TRISBbits.TRISB1 = OUTPUT;
    TRISBbits.TRISB2 = OUTPUT;

    TRISDbits.TRISD0 = INPUT;
    TRISDbits.TRISD1 = INPUT;
    TRISDbits.TRISD2 = INPUT;
    TRISDbits.TRISD3 = INPUT;
}

int wait_for_key_press(){
    int key = -1;
    
    while(key < 0){
        key = get_pressed_key();
    }

    return key;
}

int get_pressed_key(){
        COLUMNA0 = ON;
        COLUMNA1 = OFF;
        COLUMNA2 = OFF;
        Delay10us();
        if(FILA0 == ON)         return 0;
        else if(FILA1 == ON)    return 3;
        else if(FILA2 == ON)    return 6;
        else if(FILA3 == ON)    return 9;

        COLUMNA0 = OFF;
        COLUMNA1 = ON;
        COLUMNA2 = OFF;
        Delay10us();
        if(FILA0 == ON)         return 1;
        else if(FILA1 == ON)    return 4;
        else if(FILA2 == ON)    return 7;
        else if(FILA3 == ON)    return 10;

        COLUMNA0 = OFF;
        COLUMNA1 = OFF;
        COLUMNA2 = ON;
        Delay10us();
        if(FILA0 == ON)         return 2;
        else if(FILA1 == ON)    return 5;
        else if(FILA2 == ON)    return 8;
        else if(FILA3 == ON)    return 11;

        return -1;
}
