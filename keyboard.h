/*
 * Los enteros identificativos de cada tecla
 * son los siguientes:
 * 
 * | 0 | 1  | 2  |
 * | 3 | 4  | 5  |
 * | 6 | 7  | 8  |
 * | 9 | 10 | 11 |
 */

// Inicializa el teclado para un correcto funcionamiento.
void keyboardInit();

/*
 * Bloquea el programa hasta que detecte
 * la pulsación de una tecla. Devuelve un
 * entero correspondiente al número de tecla.
 */
short waitForKeyPress();

/* 
 * Devuelve el entero correspondiente a la tecla pulsada
 * en ese instante.
 * Si no hay pulsada ninguna tecla, devuelve el valor -1.
 */
short getPressedKey();