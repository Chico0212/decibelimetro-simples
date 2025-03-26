#include <stdio.h>
#include "inc/decibelimetro.h"
#include "pico/stdlib.h"
#include <math.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"



float get_calib(float alpha) {
    sample_mic();

    static float smoothed_mag = 0.0f;

    // Calcula o valor RMS (potência média) das amostras
    float raw_rms = mic_power();
        
    // Converte o valor RMS para tensão ajustada (centralizada em 1.65 V)
    float adjusted = ADC_ADJUST(raw_rms);
    
    // Calcula a magnitude: multiplica por 2 e toma o valor absoluto
    float magnitude = 2.f * fabsf(adjusted);
    
    // Aplica suavização (EMA): combina o valor atual com o histórico
    smoothed_mag = alpha * magnitude + (1.0f - alpha) * smoothed_mag;
    
    return smoothed_mag;
}

int main()
{
    stdio_init_all();

    microphone_init();

    npInit(LED_PIN);

    npClear();

    ssd1306_Init();             // Initialize the display
    ssd1306_Fill(Black);        // Fill the display with black color

    ssd1306_DrawRectangle(0, 0, 127, 63, White);            // Draw a rectangle from (0, 0) to (127, 31) with white color
    ssd1306_SetCursor(25, 28);                              // Set the cursor to the position (25, 28)
    ssd1306_WriteString("Testando", Font_7x10, White);   // Write the string "Hello World" to the display
    ssd1306_UpdateScreen();      

    while (true) {
        npClear();
        decibelimetro(get_calib(1));
        sleep_ms(250);
    }
}
