#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG *)0x40002000)

typedef struct
{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3;
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init()
{
    GPIO->PIN_CNF[6] = (0 << 0);
    GPIO->PIN_CNF[8] = (1 << 0);
    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->PSELRTS = ~0;
    UART->PSELCTS = ~0;

    UART->BAUDRATE = 0x00275000; // Setter baudraten til 9600
    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (!(UART->EVENTS_TXDRDY))
        ;
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;
}

char uart_read()
{

    if (!UART->EVENTS_RXDRDY)
        return '\0';
    UART->EVENTS_RXDRDY = 0;

    return (char)UART->RXD;
}

void toggle_leds()
{
    int sleep = 0;
    int isOn = GPIO->OUT == (0 << 17 | 0 << 18 | 0 << 19 | 0 << 20);
    /* Check if button 1 is pressed;
     * turn on LED matrix if it is. */
    if (isOn)
    {
        GPIO->OUT = 1 << 17 | 1 << 18 | 1 << 19 | 1 << 20;
    }
    else
    {
        GPIO->OUT = 0 << 17 | 0 << 18 | 0 << 19 | 0 << 20;
    }
    sleep = 10000;
    while (--sleep)
        ; // Delay
}
