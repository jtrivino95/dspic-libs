#include <p30F4011.h>
#include "delay.h"

void buzzerInit();

/**
 *
 * @param freq 0 - 100,000
 * @param s 0 - 65,535
 */
void buzz(unsigned int freq, unsigned int s);

void buzzerOn();
void buzzerOff();
char isBuzzerStateOn();
