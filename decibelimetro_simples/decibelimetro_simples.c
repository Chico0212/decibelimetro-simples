#include <stdio.h>
#include "inc/decibelimetro.h"
#include "inc/button.h"
#include "pico/stdlib.h"
#include <math.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"

// ------------------ Variáveis globais ------------------
float sensibilidades[] = {0.5f, 1.0f, 1.5f, 2.0f};
int sens_idx = 1;
float sensibilidade = 1.0f;
bool sistema_ativo = true;
bool mostrar_status_reativado = false;


// fator de calibracao do microfone
const float alpha = 0.5f; //talvez seja interessante mudar para 0.2

void update_screen(const char *format, ...) {
    char buffer[64];  // Ajuste o tamanho conforme necessário
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    ssd1306_Fill(Black); 
    
    ssd1306_DrawRectangle(0, 0, 127, 63, White);   // Desenha um retângulo na tela
    ssd1306_SetCursor(12, 28);                     // Define a posição do cursor
    ssd1306_WriteString(buffer, Font_7x10, White); // Escreve o texto formatado
    ssd1306_UpdateScreen();                        // Atualiza a tela
}
// ------------------ Callback: Botão Direito (B) ------------------
void onchange_botao_direito(button_t *b) {
    static absolute_time_t pressed_time;

    if (!gpio_get(b->pin)) {
        pressed_time = get_absolute_time();  // Pressionado
    } else {
        int64_t dt = absolute_time_diff_us(pressed_time, get_absolute_time());

        if (dt >= 2000000) {
            sistema_ativo = false;
            printf("Sistema pausado.\n");
            update_screen("Sistema pausado");
        } else {
            sens_idx = (sens_idx + 1) % 4;
            sensibilidade = sensibilidades[sens_idx];
            printf("Sensibilidade ajustada: %.2f\n", sensibilidade);
            update_screen("Sensi: %.2f%%", sensibilidade * 100.f);
        }
    }
}

// ------------------ Callback: Botão Esquerdo (A) ------------------
void onchange_botao_esquerdo(button_t *b) {
    static absolute_time_t pressed_time;

    if (!gpio_get(b->pin)) {
        pressed_time = get_absolute_time();  // Pressionado
    } else {
        int64_t dt = absolute_time_diff_us(pressed_time, get_absolute_time());

        if (dt >= 2000000) {
            sistema_ativo = true;
            mostrar_status_reativado = true;
            printf("Sistema reativado.\n");
            update_screen("Sistema reativado");
        }
    }
}


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

     // Configura os botões
    create_button(BITDOGLAB_BUTTON_A_PIN, onchange_botao_esquerdo);
    create_button(BITDOGLAB_BUTTON_B_PIN, onchange_botao_direito);

    npInit(LED_PIN);

    npClear();

    ssd1306_Init();             // Initialize the display
    ssd1306_Fill(Black);        // Fill the display with black color

    update_screen("Sensi: %.2f%%", alpha * 100.f);      

    while (true) {
        if (sistema_ativo && mostrar_status_reativado) {
            update_screen("Sistema ligado");
            sleep_ms(1500);
            update_screen("Sensi: %.2f%%", sensibilidade * 100.f);
            mostrar_status_reativado = false;
        }

        while (sistema_ativo) {
            npClear();
            decibelimetro(get_calib(alpha) * sensibilidade);
            sleep_ms(250);
        }

        npClear(); npWrite();  // apaga os LEDs

    }
}
