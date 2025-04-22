#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

extern void gpiote_init(void);
extern void ppi_init(void);

int main(void) {
    gpiote_init();  // Konfigurer GPIOTE
    ppi_init();     // Sett opp PPI

    while (1) {
        __WFI();    // CPU i dvale, venter på event
    }

    return 0;
}
