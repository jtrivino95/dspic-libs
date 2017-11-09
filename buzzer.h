/*
 * Inicializa el zumbador de manera que
 * el resto de funciones operen correctamente.
 */
void buzzerInit();

/* 
 * Hace vibrar al zumbador a frecuencia $freq durante $s segundos.
 * $freq puede tomar como máximo el valor 1000.
 */ 
void buzz(unsigned int freq, unsigned int s);

// Activa el zumbador.
void buzzerOn();

// Desactiva el zumbador.
void buzzerOff();

/*
 * Devuelve el estado del zumbador.
 * 0 -> Desactivado
 * 1 -> Activado
 */
char isBuzzerStateOn();
