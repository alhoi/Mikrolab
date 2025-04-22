#include "ppi.h"
#include "gpiote.h"

void ppi_init(void) {
    // Koble GPIOTE->EVENTS_IN[0] til hver av GPIOTE->TASKS_OUT[1–4]
    for (int i = 0; i < 4; i++) {
        PPI->PPI_CH[i].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];
        PPI->PPI_CH[i].TEP = (uint32_t)&GPIOTE->TASKS_OUT[i + 1];
    }

    // Aktiver kanalene
    PPI->CHENSET = 0x0F; // Kanal 0–3
}
