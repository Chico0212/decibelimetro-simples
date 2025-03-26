
#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino de controle
#define LED_COUNT 25
#define LED_PIN 7

// Estrutura para armazenar cores RGB
typedef struct {
    uint8_t R, G, B;
} npLED_t;

// Declaração de funções
void npInit(uint pin);
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
void npClear();
void npWrite();
int getIndex(int x, int y);
void displayMatrix(const int matriz[5][5][3]);

#endif