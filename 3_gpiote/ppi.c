#include "ppi.h"
#include "gpiote.h"   // for GPIOTE_CH_BUTTON

void ppi_init(void)
{
    // Vi ønsker: ved GPIOTE‑event på kanal 0, trigge alle 4 LED‑tasks (kanal 1–4)
    const uint32_t event_addr = (uint32_t)&GPIOTE->EVENTS_IN[GPIOTE_CH_BUTTON];

    // Bruk PPI‑kanal 0–3 til hver sin LED‑task
    for (int i = 0; i < 4; i++) {
        // TEP = adresse til GPIOTE->TASKS_OUT[ i+1 ]
        uint32_t task_addr = (uint32_t)&GPIOTE->OUT[i+1];

        PPI->PPI_CH[i].EEP = event_addr;
        PPI->PPI_CH[i].TEP = task_addr;
        PPI->CHENSET    = (1 << i);   // enable PPI‑kanal i
    }
}
