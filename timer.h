/*
 * Configura el timer de modo que geneŕará
 * una interrupción cada 1/$freq segundos cuando
 * esté activado.
 */
void timerConfig(float freq);

// Activa el timer.
void timerStart();

// Desactiva el timer.
void timerStop();