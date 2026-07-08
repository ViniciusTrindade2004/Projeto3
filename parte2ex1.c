#include <ESP32Servo.h>

// Definição dos pinos
const int pinoPotenciometro = 34; // Pino analógico ligado ao potenciômetro
const int pinoServo = 18;         // Pino de sinal (PWM) do servomotor

// Criação do objeto da classe Servo
Servo meuServo;

void setup() {
  // Inicializa a comunicação serial para monitoramento
  Serial.begin(115200);

  // Anexa o servomotor ao pino definido
  meuServo.attach(pinoServo);
  
  Serial.println("Controle de Servomotor via Potenciômetro Iniciado!");
}

void loop() {
  // 1. Lê o valor analógico do potenciômetro
  // O ADC da ESP32 tem resolução de 12 bits, portanto retorna valores de 0 a 4095
  int valorADC = analogRead(pinoPotenciometro);

  // 2. Converte (Mapeia) o valor do ADC (0 a 4095) para o ângulo do servo (0 a 180 graus)
  int angulo = map(valorADC, 0, 4095, 0, 180);

  // 3. Envia o comando de posição para o servomotor
  meuServo.write(angulo);

  // 4. Imprime os valores no monitor serial para visualização
  Serial.print("Valor ADC: ");
  Serial.print(valorADC);
  Serial.print(" | Ângulo: ");
  Serial.print(angulo);
  Serial.println(" graus");

  // Pequeno atraso para dar tempo ao servo de chegar à posição e não sobrecarregar a Serial
  delay(15);
}