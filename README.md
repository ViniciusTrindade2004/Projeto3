# Projeto 3: Controle PWM e Comunicação
**Disciplina:** SEL0433 - Aplicação de Microprocessadores

* **Nome:** Vinícius Rafael Trindade
* **Número USP:** 15491900

---

## Descrição do Projeto
Este projeto tem como objetivo exercitar a programação de microcontroladores de 32 bits por meio do desenvolvimento de uma aplicação prática utilizando a plataforma ESP32 DevKit. Foram explorados conceitos de comunicação serial e modulação por largura de pulso (PWM), além da utilização de bibliotecas otimizadas para o controle de periféricos, incluindo UART, I2C e display OLED. O desenvolvimento e a validação do sistema foram realizados no ambiente de simulação virtual Wokwi.

---

## Parte 1: Controle PWM de LED RGB
Nesta primeira etapa, foi implementado o controle PWM de um LED RGB de catodo comum, conectado às GPIOs da ESP32 por meio de resistores de 220 Ω. 

* Cada terminal correspondente às cores vermelha, verde e azul foi associado a um canal PWM independente utilizando a biblioteca LEDC.
* O sistema opera com resolução mínima de 8 bits e frequência de 5 kHz, permitindo o ajuste individual da intensidade de cada cor.
* O *duty cycle* dos canais varia continuamente entre 0% e 100%, utilizando incrementos distintos predefinidos para cada cor.
* Durante a execução, o programa envia mensagens pela interface serial UART informando os valores de incremento e os *duty cycles* aplicados.
* A UART foi devidamente configurada para 115200 de *baud rate*.

---

## Parte 2: Controle de Motores
A segunda parte consistiu no desenvolvimento de aplicações baseadas no controle PWM de motores.

* **Exercício 1 (Servomotor):** Foi desenvolvida a leitura analógica de um potenciômetro pelo ADC da ESP32, convertendo a tensão em valores de ângulo para variar manualmente o *duty cycle* de um servomotor.
* O controle do servomotor foi implementado utilizando a biblioteca "ESP32 Servo" no Wokwi.
* **Exercício 2 (Aplicação Própria):** Foi desenvolvida uma aplicação própria com ênfase na biblioteca nativa MCPWM (Motor Control PWM).
* O sistema permite a escolha entre o controle manual e automático do ângulo de um servomotor através de um pushbutton.
* As informações e parâmetros de funcionamento são apresentados em um display OLED conectado via barramento I2C.
---

## Circuitos no Wokwi
# Parte 1:
![alt text](https://github.com/ViniciusTrindade2004/Projeto3/blob/main/projeto3parte1.png)
