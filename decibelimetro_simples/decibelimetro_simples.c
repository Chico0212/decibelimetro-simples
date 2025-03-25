#include <stdio.h>
#include "inc/decibelimetro.h"
#include "pico/stdlib.h"



int main()
{
    stdio_init_all();

    while (true) {
        for (int col = 0; col < 5; ++col) {
            acende_coluna(col);
            sleep_ms(500);
        }
    }
}
