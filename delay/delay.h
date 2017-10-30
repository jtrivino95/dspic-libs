/*
 *  Delay functions for dsPIC30F devices
 *  
 *  These functions suppose that the microcontroller has a 7,37 MHz clock, and
 *  that the PLL is configured to x16.
 */
 
// Sub-microsecond delay function
void Delay3Tcy(); // 407 ns

// Microsecond delay functions
void Delay10us();
void Delay20us();
void Delay150us();

// Millisecond delay functions
void Delay5ms();
void Delay15ms();