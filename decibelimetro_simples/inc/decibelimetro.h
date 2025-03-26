#ifndef DECIBELIMETRO_H
#define DECIBELIMETRO_H

#include "microphone_dma.h"
#include "neopixel.h"
#include <stdio.h>

extern int intensidades[5];

void acende_led_coordenada(int x, int y, uint8_t r, uint8_t g, uint8_t b);
void acende_coluna(int col);
void decibelimetro(float calib);

#endif
