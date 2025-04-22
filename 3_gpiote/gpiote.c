#include "gpiote.h"
#include "gpio.h"

// Tilpass disse pinnene etter hva som er koblet på devkit
#define BUTTON1_PIN 13
const uint8_t led_pins[4] = {17, 18, 19, 20}; // Eksempel: LED supply pins

void gpiote_init(void) {
    // Konfigurer GPIOTE kanal 0 til å generere en hendelse på knappetrykk (event)
    GPIOTE->CONFIG[0] =
        (1 << 0) |                                // MODE = Event
        (BUTTON1_PIN << 8) |                      // PSEL
        (2 << 16) |                               // POLARITY = HiToLo
        (0 << 20);                                // OUTINIT = Low

    // Konfigurer kanal 1–4 til å toggle LED-pinnene (task)
    for (int i = 0; i < 4; i++) {
        GPIOTE->CONFIG[i + 1] =
            (3 << 0) |                            // MODE = Task
            (led_pins[i] << 8) |                  // PSEL
            (3 << 16) |                           // POLARITY = Toggle
            (0 << 20);                            // OUTINIT = Low

        // Sett pinnene som output i GPIO
        GPIO->PIN_CNF[led_pins[i]] = 1; // DIR=Output
    }

    // Sett knapp som input med pull-up
    GPIO->PIN_CNF[BUTTON1_PIN] = (1 << 1) | (3 << 2); // DIR=Input, Pull=Pull-up
}
