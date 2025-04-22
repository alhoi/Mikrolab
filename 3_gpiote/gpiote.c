#include "gpiote.h"
#include "gpio.h"

// --- PIN‑definisjoner (tilpass etter ditt hardware) ---
// Knapp på P0.11
#define BUTTON1_PIN    11  

// Fire LED‑forsyningspinner (f.eks. P0.13–P0.16)
static const uint8_t LED_PWR_PINS[4] = { 13, 14, 15, 16 };

// GPIOTE‑kanal‑nr
#define GPIOTE_CH_BUTTON  0   // event‑kanal
#define GPIOTE_CH_LED0    1   // task‑kanaler
#define GPIOTE_CH_LED1    2
#define GPIOTE_CH_LED2    3
#define GPIOTE_CH_LED3    4

void gpiote_init(void)
{
    // 1) Konfigurer knapp‑pin som input med pull‑up
    GPIO->PIN_CNF[BUTTON1_PIN] = 
          (0 << 0)    /* DIR = input */ 
        | (1 << 1)    /* INPUT buffer on */ 
        | (3 << 2);   /* PULL‑up */

    // 2) Kanal 0: event på knapp (hi→lo)
    GPIOTE->CONFIG[GPIOTE_CH_BUTTON] =
          (0 << 0)            /* MODE = Event */
        | (2 << 2)            /* POLARITY = Hi-to-Lo */
        | (BUTTON1_PIN << 8); /* PSEL = pin */

    // 3) Kanal 1–4: tasks som toggler LED‑forsyning
    for (int ch = GPIOTE_CH_LED0; ch <= GPIOTE_CH_LED3; ch++) {
        uint8_t pin = LED_PWR_PINS[ch - GPIOTE_CH_LED0];
        // Sett pin som output, uten pull, output = lav
        GPIO->PIN_CNF[pin] =
              (1 << 0)  /* DIR = output */
            | (0 << 1)  /* INPUT buffer off */
            | (0 << 2); /* no pull */

        GPIOTE->CONFIG[ch] =
              (1 << 0)        /* MODE = Task */
            | (3 << 2)        /* POLARITY = Toggle */
            | (pin << 8)      /* PSEL = pin */
            | (0 << 16);      /* OUTINIT = 0 */
    }
}
