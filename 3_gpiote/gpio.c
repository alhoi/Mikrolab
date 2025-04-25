#include "gpio.h"

/*
void button_init(void)
{
    // Sett BUTTON1 (P0.13) som input med pull-up
    GPIO->PIN_CNF[13] =
    (0 << 0) | // Input
        (1 << 1) | // Pull-up
        (0 << 2) | // Standard drive
        (0 << 8);  // Sense disabled (styres av GPIOTE)
        
        // LED-pinner som output
        GPIO->PIN_CNF[17] = 1;
        GPIO->PIN_CNF[18] = 1;
        GPIO->PIN_CNF[19] = 1;
        GPIO->PIN_CNF[20] = 1;
        
        GPIO->PIN_CNF[13] = (3 << 2); //Setter CC til 11 for å få pull up on pin
        // Fill inn the configuration for the remaining buttons 
        GPIO->PIN_CNF[14] = (3 << 2);
        
        for(int i = 17; i <= 20; i++){
            GPIO->DIRSET = (1 << i);
            GPIO->OUTCLR = (1 << i);
        }
        
        GPIO->OUT = 1 << 17 | 1 << 18 | 1 << 19 | 1 << 20;
    }
    */

#define BUTTON1_PIN 13
const uint8_t led_pins[4] = {17, 18, 19, 20};

void button_init(void) {
    // Konfigurer BUTTON1 (P0.13) som input med pull-up
    GPIO->PIN_CNF[BUTTON1_PIN] =
        (0 << 0)  |   // Input
        (1 << 1)  |   // Pull-up
        (0 << 2)  |   // Standard drive
        (0 << 8);     // Sense disabled (brukes via GPIOTE)

    // LED-pinner som output
    for (int i = 0; i < 4; i++) {
        GPIO->PIN_CNF[led_pins[i]] = 1; // Output
    }
}
