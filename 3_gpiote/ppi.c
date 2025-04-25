#include "ppi.h"
#include "gpiote.h"
#include <stdint.h>

void ppi_init(void) {
    // Koble BUTTON1-event til fire LED-oppgaver
    for (int i = 0; i < 4; i++) {
        PPI->CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
        PPI->CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[i + 1]);
    }

    // Aktiver PPI-kanalene 0–3
    PPI->CHENSET = 0x0F;
}
