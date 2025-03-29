# Decibelímetro Simples 🎙️💡

Um projeto baseado na Raspberry Pi Pico que mede a intensidade sonora do ambiente e representa visualmente os níveis de som usando uma matriz de LEDs. O sistema também permite o controle de sensibilidade e estado (ativo/pausado) através de dois botões físicos.

Este projeto foi desenvolvido com base nas **bibliotecas de botões, matriz de LEDs e microfone** criadas pela dupla **Nicholas Gomes** e **Emily Xavier**.

---

## 📦 Funcionalidades

- Leitura da intensidade do som com microfone via ADC + DMA
- Suavização do sinal (filtro EMA)
- Mapeamento da intensidade em níveis (0 a 4)
- Visualização na matriz de LEDs em 5 colunas
- **Botão direito (B)**:
  - Clique curto: altera o valor da intensidade manual (`smoothed_mag`)
  - Clique longo (>2s): pausa o sistema
- **Botão esquerdo (A)**:
  - Clique longo (>2s): reativa o sistema

---

## 🛠️ Requisitos

- Raspberry Pi Pico
- Microfone analógico compatível com entrada ADC
- Matriz de LEDs (5x5)
- 2 botões físicos (Botão A e Botão B)
- SDK da Raspberry Pi Pico

---

## 🧪 Como Usar

### 🔹 1️⃣ Instale a Extensão da Raspberry Pi no VS Code  
Se ainda não tiver instalado, adicione a extensão **"Raspberry Pi Pico - C/C++ Project"** no **VS Code**.

### 🔹 2️⃣ Importe o Exemplo Desejado  
1. No VS Code, clique em **"Importar Projeto"**   
2. Compile e **grave na bitdoglab** 🚀

---

## 📁 Estrutura do Projeto
```
decibelimetro-simples/
├── inc/
│   ├── button.h
│   ├── decibelimetro.h
│   ├── microphone_dma.h
│   ├── neopixel.h
│   └── ws2818b.pio.h
├── src/
│   ├── button.c
│   ├── decibelimetro.c
│   ├── main.c
│   └── microphone_dma.c
├── CMakeLists.txt
├── LICENSE
├── pico_sdk_import.cmake
└── README.md
```

---

## 👨‍💻 Desenvolvedores
- Pedro Augusto Gonçalves Lucena ([@pedrodev3005](https://github.com/pedrodev3005))
- Francisco Bezerra da Silva Neto ([@chico0212](https://github.com/chico0212))

---

## Dificuldades Encontradas

- Controle da Sensibilidade: Decidir como controlar a intensidade do microfone.

- Controle da Matriz: Modificar o funcionamento da matriz, para que ela acenda verticalmente e não horizontalmente.

- Testes: Encontrar uma forma de testar de forma correta o funcionamento, visto que por se tratar de um microfone, é necessário um ambiente silencioso e sons constantes em volume, para constatar o devido funcionamento da sensibilidade



