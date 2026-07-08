// Definição dos pinos do LED RGB
const int pinR = 25;
const int pinG = 26;
const int pinB = 27;

// Configurações do PWM
const int frequencia = 5000; // 5 kHz
const int resolucao = 8;     // 8 bits (0 a 255)

// Variáveis para armazenar o Duty Cycle atual (0 a 255)
int dutyR = 0;
int dutyG = 0;
int dutyB = 0;

// Taxas de incremento
// Verde: passos de 5. Azul: dobro do verde (10). Vermelho: triplo do verde (15).
const int incG = 5;
const int incB = 10;
const int incR = 15;

void setup() {
  // Inicializa a comunicação Serial com baud rate de 115200
  Serial.begin(115200);

  // Configura os canais PWM e associa os pinos aos respectivos canais
  ledcAttach(pinR, frequencia, resolucao);
  ledcAttach(pinG, frequencia, resolucao);
  ledcAttach(pinB, frequencia, resolucao);
  
  Serial.println("Iniciando controle PWM do LED RGB...");
}

void loop() {
  // Atualiza os valores do duty cycle
  dutyG += incG;
  dutyB += incB;
  dutyR += incR;

  // Lógica de Loop: Se passar de 255 (100%), zera o valor
  if (dutyG > 255) dutyG = 0;
  if (dutyB > 255) dutyB = 0;
  if (dutyR > 255) dutyR = 0;

  // Aplica o duty cycle aos pinos diretamente
  ledcWrite(pinR, dutyR);
  ledcWrite(pinG, dutyG);
  ledcWrite(pinB, dutyB);

  // Envia as informações pela interface Serial UART
  Serial.print("Incrementos -> R:");
  Serial.print(incR);
  Serial.print(" G:");
  Serial.print(incG);
  Serial.print(" B:");
  Serial.print(incB);
  
  Serial.print(" | Duty Cycles (0-255) -> R:");
  Serial.print(dutyR);
  Serial.print(" G:");
  Serial.print(dutyG);
  Serial.print(" B:");
  Serial.println(dutyB);

  // Atraso para visualização no terminal e no LED (200 milissegundos)
  delay(200); 
}