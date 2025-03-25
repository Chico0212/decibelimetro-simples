#include <stdio.h>
#include "inc/button.h"
#include "inc/microphone_dma.h"
#include "pico/stdlib.h"



int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
