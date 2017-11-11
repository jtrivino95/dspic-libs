/*
 * Configura el timer de modo que geneŕará
 * una interrupción cada 1/$freq segundos cuando
 * esté activado.
 * $freq no puede superar el valor de 460800 Hz
 */
void timerConfig(float freq);

// Activa el timer.
void timerStart();

// Desactiva el timer.
void timerStop();