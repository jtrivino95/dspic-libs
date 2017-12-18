#define LED0 LATEbits.LATE0
#define LED1 LATEbits.LATE1
#define LED2 LATEbits.LATE2
#define LED3 LATEbits.LATE3
#define LED4 LATEbits.LATE4
#define LED5 LATEbits.LATE5

#define LED_ON 1
#define LED_OFF 0


void initLeds();
void setLed(int nled, int status);