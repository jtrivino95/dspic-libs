#include "LCDlib.h"

#include <p30f4011.h>
#include "delay.h"

/******************************************************************************/
/* Pre-processor directives                                                   */
/******************************************************************************/

#define LCD_EN_TRIS  TRISBbits.TRISB6
#define LCD_EN       LATBbits.LATB6

#define LCD_RS_TRIS  TRISCbits.TRISC15
#define LCD_RS       LATCbits.LATC15
#define LCD_RW_TRIS  TRISEbits.TRISE8
#define LCD_RW       LATEbits.LATE8

#define LCD_DB4_TRIS TRISDbits.TRISD0
#define LCD_DB4      LATDbits.LATD0
#define LCD_DB5_TRIS TRISDbits.TRISD1
#define LCD_DB5      LATDbits.LATD1
#define LCD_DB6_TRIS TRISDbits.TRISD2
#define LCD_DB6      LATDbits.LATD2
#define LCD_DB7_TRIS TRISDbits.TRISD3
#define LCD_DB7_R    PORTDbits.RD3
#define LCD_DB7      LATDbits.LATD3

#define CGRAM_BASE_ADDRESS 0x08
#define CGRAM_CELL_SIZE 0x08
#define CGRAM_NUM_CELLS 7
#define CGRAM_ROWS_PER_CELL 8

/******************************************************************************/
/* Prototypes of additional functions										 */
/******************************************************************************/

void waitLCD();

void LCDWriteCmd(char cmd);
void LCDWriteNibbleCmd(char cmd);

void LCDWriteData(char data);


/******************************************************************************/
/* Functions																  */
/******************************************************************************/

// Initialize LCD
// This function forces a reset and initialize the LCD (16x2)
void LCDInit()
{
	// Set main pins as outputs
	LCD_EN_TRIS = 0;
	LCD_RS_TRIS = 0;
	LCD_RW_TRIS = 0;

	// Reset
	Delay15ms();
	LCDWriteNibbleCmd(0x01); 
	Delay5ms();
	LCDWriteNibbleCmd(0xC0); 
	Delay150us();
	LCDWriteNibbleCmd(0x08); 
	waitLCD();

	// End reset
	LCDWriteNibbleCmd(0x20);  // Function set 4-bits interface
	waitLCD();

	// Function set 4-bits interface, number of lines and character font
	LCDWriteCmd(0x28);
	waitLCD();

	// Display OFF
	LCDWriteCmd(0x08);
	waitLCD();

	// Clear display
	LCDWriteCmd(0x01);
	waitLCD();

	// Entry mode set incr. address and no shift
	LCDWriteCmd(0x06);
	waitLCD();

	/* End Initialization */
	waitLCD();

	// Display ON
	LCDWriteCmd(0x0F);
	waitLCD();
}

// Clear LCD
void LCDClear(){
	LCDWriteCmd(0x01);
	waitLCD();
}

// Move the cursor of the LCD to home
void LCDMoveHome(){
	LCDWriteCmd(0x02);
	waitLCD();
}

// Move LCD cursor to first line
void LCDMoveFirstLine(){
	LCDWriteCmd(0x80);
	waitLCD();
}

// Move LCD cursor to second line
void LCDMoveSecondLine(){
	LCDWriteCmd(0xA8);
	waitLCD();
}

// Writes a string to the LCD
void LCDPrint(char *str){
	while(*str != '\0'){
		waitLCD();
		LCDWriteData(*str);
		str++;
	}
}

// Move LCD cursor left
void LCDMoveLeft(){
	LCDWriteCmd(0x10);
	waitLCD();
}

// Move LCD cursor right
void LCDMoveRight(){
	LCDWriteCmd(0x14);
	waitLCD();
}

// Scroll LCD Screen left
void LCDScrollLeft(){
	LCDWriteCmd(0x18);
	waitLCD();
}

// Scroll LCD right
void LCDScrollRight(){
	LCDWriteCmd(0x1E);
	waitLCD();
}

// Hide LCD cursor
void LCDHideCursor(){
	LCDWriteCmd(0x0C);
	waitLCD();
}

// Turn on underline LCD cursor
void LCDTurnOnUnderline(){
	LCDWriteCmd(0x0E);
	waitLCD();
}

// Turn on blinking-block LCD cursor
void LCDTurnOnBlinking(){
	LCDWriteCmd(0x0F);
	waitLCD();
}


/******************************************************************************/
/* Additional functions                                                       */
/******************************************************************************/

void waitLCD()
{
	char busyValue = 1;

	// Set LCD data pins as inputs
	LCD_DB7_TRIS = 1;
	LCD_DB6_TRIS = 1;
	LCD_DB5_TRIS = 1;
	LCD_DB4_TRIS = 1;

	Delay20us();

	// Read Busy Flag and Address Counter
	LCD_RS = 0;
	LCD_RW = 1; 

	// Setup time
	Delay20us();
	Delay20us();

	while(busyValue){
		LCD_EN = 1;

		// Data delay time
		Delay20us();
		Delay20us();

		busyValue = LCD_DB7_R;

		Delay20us();
		Delay20us();

		// Restore default state
		LCD_EN = 0;

		// Hold on time
		Delay20us();
		Delay20us();
	}
	/* Restore default state */
	LCD_RW = 0;
}

void LCDWriteCmd(char cmd)
{
	// Send command to Instruction Register
	LCD_RS = 0;
	LCD_RW = 0;

	// Set LCD data pins as outputs
	LCD_DB7_TRIS = 0;
	LCD_DB6_TRIS = 0;
	LCD_DB5_TRIS = 0;
	LCD_DB4_TRIS = 0;

	// Send first nibble
	LCD_DB7 = (cmd & 0b10000000) >> 7;
	LCD_DB6 = (cmd & 0b01000000) >> 6;
	LCD_DB5 = (cmd & 0b00100000) >> 5;
	LCD_DB4 = (cmd & 0b00010000) >> 4;

	// Wait until nibble is processed
	Delay20us(); // min 20us
	LCD_EN = 1;
	Delay20us(); // min 230n
	LCD_EN = 0;
	Delay20us();

	// Send command to Instruction Register
	LCD_RS = 0;
	LCD_RW = 0;

	// Send second nibble
        LCD_DB7 = (cmd & 0b00001000) >> 3;
	LCD_DB6 = (cmd & 0b00000100) >> 2;
	LCD_DB5 = (cmd & 0b00000010) >> 1;
	LCD_DB4 = (cmd & 0b00000001);

	// Wait until nibble is processed
	Delay20us(); // min 20us
	LCD_EN = 1;
	Delay20us(); // min 230n
	LCD_EN = 0;
	Delay20us();

	/* Restore default state */
	// Set LCD data pins as inputs
	LCD_DB7_TRIS = 1;
	LCD_DB6_TRIS = 1;
	LCD_DB5_TRIS = 1;
	LCD_DB4_TRIS = 1;
}

void LCDWriteNibbleCmd(char cmd)
{
	// Send command to Instruction Register
	LCD_RS = 0;
	LCD_RW = 0;

	// Set higher LCD data pins as outputs
	LCD_DB7_TRIS = 0;
	LCD_DB6_TRIS = 0;
	LCD_DB5_TRIS = 0;
	LCD_DB4_TRIS = 0;

	// Send nibble
	LCD_DB7 = (cmd & 0b10000000) >> 7;
	LCD_DB6 = (cmd & 0b01000000) >> 6;
	LCD_DB5 = (cmd & 0b00100000) >> 5;
	LCD_DB4 = (cmd & 0b00010000) >> 4;

	// Wait until nibble is processed
	Delay20us(); // min 20us
	LCD_EN = 1;
	Delay20us(); // min 230n
	LCD_EN = 0;
	Delay20us();

	/* Restore default state */
	// Set higher LCD data pins as inputs
	LCD_DB7_TRIS = 1;
	LCD_DB6_TRIS = 1;
	LCD_DB5_TRIS = 1;
	LCD_DB4_TRIS = 1;
}

void LCDWriteData(char data)
{
	// Write data to (DD|CG)RAM
	LCD_RS = 1;
	LCD_RW = 0;

	// Set LCD pins as outputs
	LCD_DB7_TRIS = 0;
	LCD_DB6_TRIS = 0;
	LCD_DB5_TRIS = 0;
	LCD_DB4_TRIS = 0;

	// Send first nibble
	LCD_DB7 = (data & 0b10000000) >> 7;
	LCD_DB6 = (data & 0b01000000) >> 6;
	LCD_DB5 = (data & 0b00100000) >> 5;
	LCD_DB4 = (data & 0b00010000) >> 4;

	// Wait until nibble is processed
	Delay20us(); // min 20us
	LCD_EN = 1;
	Delay20us(); // min 230n
	LCD_EN = 0;
	Delay20us();

	// Write data to (DD|CG)RAM
	LCD_RS = 1;
	LCD_RW = 0;

	// Send second nibble
	LCD_DB7 = (data & 0b00001000) >> 3;
	LCD_DB6 = (data & 0b00000100) >> 2;
	LCD_DB5 = (data & 0b00000010) >> 1;
	LCD_DB4 = (data & 0b00000001);

	// Wait until nibble is processed
	Delay20us(); // min 20us
	LCD_EN = 1;
	Delay20us(); // min 230n
	LCD_EN = 0;
	Delay20us();

	/* Restore default state */
	// Set LCD pins as inputs
	LCD_DB7_TRIS = 1;
	LCD_DB6_TRIS = 1;
	LCD_DB5_TRIS = 1;
	LCD_DB4_TRIS = 1;

	LCD_RW = 0;
	LCD_RS = 0;
}

/*
 * Pattern: array of size 8, that contains each line of the char represented by 8 bits.
 */
void LCDStoreCharPattern(char *pattern, short cell_index){
    if (cell_index > CGRAM_NUM_CELLS-1) return;

    // Point to the beginning of the CGRAM cell
    char
        set_cgram_address_cmd = 0x40,
        cgram_address = CGRAM_CELL_SIZE * cell_index,
        cmd = set_cgram_address_cmd + CGRAM_BASE_ADDRESS + cgram_address;
    LCDWriteCmd(cmd);

    // Write the provided pattern
    short i = 0;
    for (i = 0; i < CGRAM_ROWS_PER_CELL; i++) LCDWriteData(pattern[i]);

    // Point to the beginning of DDRAM
    LCDMoveHome();
}

void LCDShowCharPattern(short cgram_cell_index){
    if (cgram_cell_index > CGRAM_NUM_CELLS-1) return;

    char custom_pattern_ascii_code = cgram_cell_index + 1;
    LCDWriteData(custom_pattern_ascii_code);
}
