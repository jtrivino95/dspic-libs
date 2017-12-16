/* 
 * File:   libCAN.h
 * Author: QUELMI
 *
 * Created on 14 de noviembre de 2017, 17:45
 */

#ifndef LIBCAN_H
#define	LIBCAN_H

void initCAN();

void transmitCAN(unsigned char * data, unsigned short datalength);

#endif	/* LIBCAN_H */

