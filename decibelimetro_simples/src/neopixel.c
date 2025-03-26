#include "neopixel.h"

// Buffer de LEDs
static npLED_t leds[LED_COUNT];

// Variáveis PIO
static PIO np_pio;
static uint sm;

/**
 * Inicializa a máquina PIO para controle dos LEDs.
 */
void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    // Tenta alocar uma máquina de estado PIO
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0) {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    // Inicia programa PIO
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa a matriz
    npClear();
}

/**
 * Define a cor de um LED específico.
 */
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) {
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }

    sleep_ms(1);
}

/**
 * Limpa todos os LEDs (desliga todos).
 */
void npClear() {
    for (uint i = 0; i < LED_COUNT; i++) {
        npSetLED(i, 0, 0, 0);
    }
    npWrite();
}

/**
 * Atualiza a matriz de LEDs com os valores do buffer.
 */
void npWrite() {
    for (uint i = 0; i < LED_COUNT; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Reset
}

/**
 * Converte coordenadas (x, y) em um índice linear considerando o layout em zigue-zague.
 */
int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24 - (y * 5 + x);
    } else {
        return 24 - (y * 5 + (4 - x));
    }
}

/**
 * Exibe uma matriz 5x5 de cores RGB nos LEDs.
 */
void displayMatrix(const int matriz[5][5][3]) {
    for (int linha = 0; linha < 5; linha++) {
        for (int coluna = 0; coluna < 5; coluna++) {
            int posicao = getIndex(linha, coluna);
            npSetLED(posicao, matriz[coluna][linha][0], matriz[coluna][linha][1], matriz[coluna][linha][2]);
        }
    }
    npWrite();
    sleep_ms(2000);
}