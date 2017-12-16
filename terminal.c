#include "terminal.h"
#include "uart/uart.h"

void colocarCursor(char *col, char *fila) {
    int i;
    
    WriteUART1(27);
    while (BusyUART1());
    WriteUART1(91);
    while (BusyUART1());
    for (i = 0; fila[i] != '\0'; i++) { 
        WriteUART1(fila[i]);
        while (BusyUART1());
    }

    WriteUART1(59);
    while (BusyUART1());
    for (i = 0; col[i] != '\0'; i++) { 
        WriteUART1(col[i]);
        while (BusyUART1());
    }
    WriteUART1(72);
    while (BusyUART1());
}

void imprimir(char c) {
    while (BusyUART1());
    WriteUART1(c);
}

char getUltimaTecla(){
    return ReadUART1();
}
