#pragma once
#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stdio.h>

void uart_init();
void uart_send(char letter);
char uart_read();
void toggle_leds();

#endif