#ifndef TERMINAL_H
#define	TERMINAL_H

void uartConfig(void);
void uartColocarCursor(char *col, char *fila);
void uartImprimir(char c);
char uartGetUltimaTecla(void);
void uartImprimirString(char *str);

#endif	/* TERMINAL_H */

