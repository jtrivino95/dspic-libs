void timerInit(void);

void timerConfig(
    unsigned int max_counter_value,
    unsigned char prescaling_factor,
    unsigned char priority);

// Activa el timer.
void timerStart(void);

// Desactiva el timer.
void timerStop(void);