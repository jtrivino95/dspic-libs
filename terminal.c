#include "terminal.h"
#include "uart/uart.h"

void uartConfig(void) {
    U1MODE = 0; // Clear UART config - to avoid problems with bootloader

    // Config UART
    OpenUART1(
            UART_EN & // Enable UART
            UART_DIS_LOOPBACK & // Disable loopback mode
            UART_NO_PAR_8BIT & // 8bits / No parity 
            UART_1STOPBIT, // 1 Stop bit

            UART_TX_PIN_NORMAL & // Tx break bit normal
            UART_TX_ENABLE, // Enable Transmition

            15 // Baudrate
            );
}

void uartColocarCursor(char *col, char *fila) {
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

void uartImprimir(char c) {
    while (BusyUART1());
    WriteUART1(c);
}

char uartGetUltimaTecla(void){
    return ReadUART1();
}
