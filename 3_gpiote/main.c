#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(void)
{
    gpiote_init();   // setter opp GPIOTE‑kanaler
    ppi_init();      // kobler knapp‑event → LED‑tasks via PPI

    // Alt skjer via hardware: knappetrykk toggler LED
    while (1) {
        __WFE();      // sleep til event
        __SEV();      // for sikkerhets skyld, clear WFE‑flagget
        __WFE();
    }
}
