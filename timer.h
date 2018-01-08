#define PRESCALING_FACTOR_1 0
#define PRESCALING_FACTOR_8 1
#define PRESCALING_FACTOR_64 2
#define PRESCALING_FACTOR_256 3

void timerInit(void);

void timerConfig(
    unsigned int max_counter_value,
    unsigned char prescaling_factor,
    unsigned char priority);

// Activa el timer.
void timerStart(void);

// Desactiva el timer.
void timerStop(void);