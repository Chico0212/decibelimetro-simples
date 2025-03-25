#include "decibelimetro.h"

void acende_led_coordenada(int x, int y) {

}


void acende_coluna(int col) {
                      // aqui tem que ser passada a calibracao (eu acho)
    uint8_t intensidade = get_intensity(1.F);

    switch (intensidade)
    {
    case 0:
        acende_led_coordenada(col, 0);
    case 1:
        acende_led_coordenada(col, 1);
    case 2:
        acende_led_coordenada(col, 2);
    case 3:
        acende_led_coordenada(col, 3);
    case 4:
        acende_led_coordenada(col, 4);
    default:
        break;
    }

    // talvez enviar tudo pra matriz
}

