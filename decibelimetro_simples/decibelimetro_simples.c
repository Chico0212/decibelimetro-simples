#include <stdio.h>
#include "inc/decibelimetro.h"
#include "pico/stdlib.h"
#include <math.h>


volatile static float smoothed_mag = 0.0f;

float get_calib() {
    sample_mic();

    float alpha = 1.f;

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

    while (true) {
        decibelimetro(get_calib());
        sleep_ms(10);
        npClear();
    }
}
