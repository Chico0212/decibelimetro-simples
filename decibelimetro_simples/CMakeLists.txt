# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

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
    target_link_libraries(${LIB_NAME} PRIVATE pico_stdlib hardware_pio hardware_adc hardware_dma hardware_i2c)  # Adiciona suporte ao ADC
endfunction()


# Adicionando bibliotecas
add_pico_library(button)
add_pico_library(microphone_dma)
add_pico_library(decibelimetro)
add_pico_library(neopixel)
add_pico_library(ssd1306_fonts)
add_pico_library(ssd1306)

# Executável principal
add_executable(decibelimetro_simples decibelimetro_simples.c)

# Configurações do projeto
pico_set_program_name(decibelimetro_simples "decibelimetro_simples")
pico_set_program_version(decibelimetro_simples "0.1")

# Habilita stdio
pico_enable_stdio_uart(decibelimetro_simples 0)
pico_enable_stdio_usb(decibelimetro_simples 1)

# Vincula bibliotecas ao executável
target_link_libraries(decibelimetro_simples
    button
    decibelimetro
    neopixel
    pico_stdlib
    hardware_pio
    microphone_dma
    ssd1306_fonts
    ssd1306
    )

# Gera arquivos adicionais (UF2, etc)
pico_add_extra_outputs(decibelimetro_simples)
