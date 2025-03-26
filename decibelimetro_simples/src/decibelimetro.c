#include "decibelimetro.h"

int intensidades[5] = {-1, -1, -1, -1, -1}; 

void acende_led_coordenada(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    npSetLED(getIndex(x, y), r, g, b);
}

void guarda_intensidades(uint8_t intensidade) {
    for (int i = 4; i > 0; i--) {
        intensidades[i] = intensidades[i-1];
    }

    intensidades[0] = intensidade;
}

void acende_coluna(int col) {
    if (intensidades[col] >= 0)  // Verde
        acende_led_coordenada(col, 4, 0, 255, 0);
    if (intensidades[col] >= 1)  // Verde
        acende_led_coordenada(col, 3, 0, 255, 0);
    if (intensidades[col] >= 2)  // Amarelo
        acende_led_coordenada(col, 2, 255, 255, 0);
    if (intensidades[col] >= 3)  // Laranja
        acende_led_coordenada(col, 1, 255, 165, 0);
    if (intensidades[col] >= 4)  // Vermelho
        acende_led_coordenada(col, 0, 255, 0, 0);


    npWrite();
}

void decibelimetro(float calib) {
    uint8_t intensidade = get_intensity(calib);

    printf("intensidade: %d\n", intensidade);

    guarda_intensidades(intensidade);

    for (int i = 0; i < 5; ++i) {
        acende_coluna(i);
    }
}
