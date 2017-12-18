#ifndef LIBCAN_H
#define	LIBCAN_H

void initCAN();

/*
 * Se envian hasta 8 bytes de datos 
 */
void transmitCAN(unsigned char *data, unsigned short datalength);

#endif	/* LIBCAN_H */