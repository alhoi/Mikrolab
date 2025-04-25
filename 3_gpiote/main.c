#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


int main(void) {
    button_init();
    gpiote_init();
    ppi_init();

    while (1) {
          // Vent på event, lavere strømforbruk
    }

    return 0;
}
