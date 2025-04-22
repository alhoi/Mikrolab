#ifndef GPIOTE_H
#define GPIOTE_H

#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000)

typedef struct {
    volatile uint32_t TASKS_OUT[8];        // Offset: 0x000
    volatile uint32_t RESERVED0[4];        // Offset: 0x020
    volatile uint32_t TASKS_SET[8];        // Offset: 0x030
    volatile uint32_t RESERVED1[4];        // Offset: 0x050
    volatile uint32_t TASKS_CLR[8];        // Offset: 0x060
    volatile uint32_t RESERVED2[32];       // Offset: 0x080
    volatile uint32_t EVENTS_IN[8];        // Offset: 0x100
    volatile uint32_t RESERVED3[23];       // Offset: 0x120
    volatile uint32_t EVENTS_PORT;         // Offset: 0x17C
    volatile uint32_t RESERVED4[97];       // Offset: 0x180
    volatile uint32_t INTENSET;            // Offset: 0x300
    volatile uint32_t INTENCLR;            // Offset: 0x304
    volatile uint32_t RESERVED5[129];      // Offset: 0x308
    volatile uint32_t CONFIG[8];           // Offset: 0x508
} NRF_GPIOTE_REG;

#endif // GPIOTE_H
