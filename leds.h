/* 
 * File:   leds.h
 * Author: jtm648
 *
 * Created on 26 de septiembre de 2017, 18:10
 */
#define LED0 LATEbits.LATE0
#define LED1 LATEbits.LATE1
#define LED2 LATEbits.LATE2
#define LED3 LATEbits.LATE3
#define LED4 LATEbits.LATE4
#define LED5 LATEbits.LATE5

#define LED_ON 1
#define LED_OFF 0

void init_leds();
void set_led(int nled, int status);
void toggle(int nled);