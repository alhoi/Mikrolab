#include "gpiote.h"
#include "gpio.h"

#define BUTTON1_PIN 13
const uint8_t led_pins2[4] = {17, 18, 19, 20};

void gpiote_init(void) {
    // Konfigurer BUTTON1 som EVENT (GPIOTE kanal 0)
    GPIOTE->CONFIG[0] = 1 | (BUTTON1_PIN << 8) | (2 << 16) | (0 << 20);                 // POLARITY = HiToLo

    // Konfigurer fire LED-kanaler (GPIOTE kanal 1–4) som TASK
    for (int i = 0; i < 4; i++) {
        GPIOTE->CONFIG[i + 1] =
            3|                 // MODE = Task
            (led_pins2[i] << 8) |       
            (3 << 16) |                
            (0 << 20);                 
    }
} 
