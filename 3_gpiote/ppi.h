#ifndef PPI_H
#define PPI_H
#include <stdint.h>

#define PPI ((NRF_PPI_REG*)0x4001F000)

typedef struct {
	uint32_t EEP; // Event Endpoint
	uint32_t TEP; // Task Endpoint
} PPI_CHANNEL_TYPE;

typedef struct {
	volatile uint32_t RESERVED0[1284]; // 0x000 to 0x510
	volatile uint32_t CHEN;       // 0x500
	volatile uint32_t CHENSET;    // 0x504
	volatile uint32_t CHENCLR;    // 0x508
	volatile uint32_t RESERVED1;
	volatile PPI_CHANNEL_TYPE PPI_CH[16]; // 0x510–0x58F
	volatile uint32_t RESERVED2[156];
	volatile uint32_t CHG[4]; // 0x800–0x80C
} NRF_PPI_REG;

#endif
