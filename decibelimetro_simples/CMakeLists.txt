cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o SDK do Pico
include(pico_sdk_import.cmake)

project(decibelimetro_simples C CXX ASM)

pico_sdk_init()

# Função para adicionar bibliotecas de forma simplificada
function(add_pico_library LIB_NAME)
    add_library(${LIB_NAME} src/${LIB_NAME}.c)
    target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)
    target_link_libraries(${LIB_NAME} PRIVATE pico_stdlib hardware_pio hardware_adc hardware_dma)  # Adiciona suporte ao ADC
endfunction()


# Adicionando bibliotecas
add_pico_library(button)
add_pico_library(microphone_dma)
add_pico_library(decibelimetro)
# add_pico_library(led_matrix)

# Executável principal
add_executable(decibelimetro_simples decibelimetro_simples.c)

# Configurações do projeto
pico_set_program_name(decibelimetro_simples "decibelimetro_simples")
pico_set_program_version(decibelimetro_simples "0.1")

# Habilita stdio
pico_enable_stdio_uart(decibelimetro_simples 1)
pico_enable_stdio_usb(decibelimetro_simples 1)

# Vincula bibliotecas ao executável
target_link_libraries(decibelimetro_simples
    button
    decibelimetro
    # led_matrix
    pico_stdlib
    hardware_pio
    microphone_dma
    )

# Gera arquivos adicionais (UF2, etc)
pico_add_extra_outputs(decibelimetro_simples)
