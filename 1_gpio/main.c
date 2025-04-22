#include <stdint.h>
#include <stdio.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
    volatile uint32_t RESERVED0[321];
    volatile uint32_t OUT;
    volatile uint32_t OUTSET;
    volatile uint32_t OUTCLR;
    volatile uint32_t IN;
    volatile uint32_t DIR;
    volatile uint32_t DIRSET;
    volatile uint32_t DIRCLR;
    volatile uint32_t LATCH;
    volatile uint32_t DETECTMODE;
    volatile uint32_t RESERVED1[118];
    volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init() {
    // Configure button 1 (pin 13) and button 2 (pin 14) as inputs with pull-up resistors
    GPIO->PIN_CNF[13] = (3 << 2); // Input with pull-up
    GPIO->PIN_CNF[14] = (3 << 2); // Input with pull-up
}

void led_matrix_init() {
    // Configure LED pins (17 to 20) as outputs
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i);  // Set pin to output
        GPIO->OUTCLR = (1 << i);  // Turn off LEDs initially
    }
}

int main() {
    // Initialize the LED matrix and buttons
    led_matrix_init();
    button_init();
	int sleep = 0;
    while (1) {
        // Debug: Print button states for troubleshooting
        

        // Check if Button 1 (pin 13) is pressed (active-low)
        if ((GPIO->IN & (1 << 13)) == 0) {  // Button 1 pressed
            // Turn on LEDs (pins 17 to 20)
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTCLR = (1 << i);
            }
        }
        // Check if Button 2 (pin 14) is pressed (active-low)
        if ((GPIO->IN & (1 << 14)) == 0) {  // Button 2 pressed
            // Turn off LEDs (pins 17 to 20)
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTSET = (1 << i);
            }
        }

        // Simple delay to debounce the button press
        sleep = 10000;
        while (--sleep); // Delay loop
    }

    return 0;
}



