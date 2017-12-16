#include "libCAN.h"
#include <p30f4011.h>

#include "LCDlib.h"
#include <stdio.h>

void initCAN() {
    C1CTRLbits.REQOP = 0b100; // Set configuration mode
    while (C1CTRLbits.OPMODE != 0b100); // Wait until configuration mode
    C1CTRLbits.CANCKS = 1; // FCAN = FCY
    /* BTR */
    // BTR1
    C1CFG1bits.BRP = 0; // 1Mbps
    C1CFG1bits.SJW = 0b00; // 1 TQ
    // BTR2
    C1CFG2bits.PRSEG = 0b00; // 1 TQs
    C1CFG2bits.SEG1PH = 0b11; // 4 TQs
    C1CFG2bits.SEG2PH = 0b01; // 2 TQs
    /* Tx buffer 0 */
    C1TX0CONbits.TXREQ = 0; // Clear tx request
    /* Rx buffer 0 */
    C1RX0CONbits.RXFUL = 0; // Clear rx status
    // Disable double buffer
    C1RX0CONbits.DBEN = 0;
    // Configure acceptance masks
    C1RXM0SIDbits.SID = 0; // No bits to compare
    C1RXM0SIDbits.MIDE = 1; // Determine as EXIDE
    // Configure acceptance filters
    C1RXF0SIDbits.SID = 0; // Doesn't matter the value as mask is ?0?
    C1RXF0SIDbits.EXIDE = 0; // Enable filter for standard identifier
    /* Interrupts */
    IEC1bits.C1IE = 1; // Enable global CAN interrupt
    IFS1bits.C1IF = 0; // Clear global CAN interrupt flag
    // Enable Configure interrupts
    C1INTE = 0;
    C1INTEbits.RX0IE = 1; // Enable interrupt associated to rx buffer 0
    C1INTFbits.RX0IF = 0; // Clear interrupt flag associated to rx buffer 0
    C1CTRLbits.REQOP = 0b000; // Set normal mode
    while (C1CTRLbits.OPMODE != 0b000); // Wait until normal mode
}

void transmitCAN(unsigned char * data, unsigned short datalength) {
    /* Tx buffer 0 */
    C1TX0DLCbits.TXRTR = 0; // Set data frame
    C1TX0SIDbits.TXIDE = 0; // Set standard identifier
    // Set identifier 1
    C1TX0SIDbits.SID5_0 = 0; // Set the lowest 6 bits
    C1TX0SIDbits.SID10_6 = 1; // Set the highest 5 bits
    C1TX0DLCbits.DLC = datalength; // DLC 1 byte

    switch (datalength) {
        case 8:
            C1TX0B4 = (data[7] << 8);
        case 7:
            C1TX0B4 = (C1TX0B4 & 0xFF00) | (data[6] & 0xFF);
        case 6:
            C1TX0B3 = (data[5] << 8);
        case 5:
            C1TX0B3 = (C1TX0B3 & 0xFF00) | (data[4] & 0xFF);
        case 4:
            C1TX0B2 = (data[3] << 8);
        case 3:
            C1TX0B2 = (C1TX0B2 & 0xFF00) | (data[2] & 0xFF);
        case 2:
            C1TX0B1 = (data[1] << 8);
        case 1:
            C1TX0B1 = (C1TX0B1 & 0xFF00) | (data[0] & 0xFF);
    }
    C1TX0CONbits.TXREQ = 1; // Transmit
    while (C1TX0CONbits.TXREQ != 0); // Wait for transmission
}
