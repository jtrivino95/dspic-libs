/* 
 * File:   buzzer.h
 * Author: jtm648
 *
 * Created on 2 de octubre de 2017, 19:01
 */

#include <p30F4011.h>
#include "delay.h"


void BuzzerInit();

/**
 *
 * @param freq 0 - 100,000
 * @param s 0 - 65,535
 */
void buzz(unsigned int freq, unsigned int s);