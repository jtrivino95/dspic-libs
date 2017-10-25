/* 
 * File:   buzzer.h
 * Author: jtm648
 *
 * Created on 2 de octubre de 2017, 19:01
 */

#include <p30F4011.h>
#include "delay.h"


void init_buzzer();
void buzz(int freq, int ms);