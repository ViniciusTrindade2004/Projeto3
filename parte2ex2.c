#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/mcpwm.h" // Importação da biblioteca nativa MCPWM

// Configurações do Display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Definição de Pinos
#define SERVO_PIN 18
#define POT_PIN 34
#define BUTTON_PIN 12

// Constantes do Servo (Largura de pulso típica para 0º e 180º)
#define SERVO_MIN_PULSEWIDTH 500  // μs
#define SERVO_MAX_PULSEWIDTH 2500 // μs

// Variáveis de Controle e Estado
volatile bool autoMode = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 250;

int servoAngle = 0;
uint32_t pulseWidth = 0;

// Função de Interrupção Externa (ISR) para o botão
void IRAM_ATTR toggleMode() {
  unsigned long currentTime = millis();
  // Lógica simples de debounce
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    autoMode = !autoMode;
    lastDebounceTime = currentTime;
  }
}

void setup() {
  Serial.begin(115200);
  
  // 1. Configuração do Botão (Interrupção Externa)
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleMode, FALLING);
  
  // 2. Configuração do Display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao inicializar o OLED"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // 3. Inicialização e Configuração da biblioteca MCPWM nativa
  // Mapeia o pino 18 para o sinal PWM do Operador A, Unidade 0
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PIN);
  
  mcpwm_config_t pwm_config;
  pwm_config.frequency = 50;                // 50Hz (frequência padrão para servos, período de 20ms)
  pwm_config.cmpr_a = 0;                    // Duty cycle inicial
  pwm_config.cmpr_b = 0;
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0; // Sinal alto no início do ciclo
  
  // Aplica as configurações ao Timer 0 da Unidade 0
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
  
  Serial.println("Sistema Iniciado. MCPWM Configurado.");
}

void loop() {
  static int autoAngle = 0;
  static int direction = 1;

  // Lógica de Controle do Sistema
  if (autoMode) {
    // MODO AUTOMÁTICO: Faz a varredura do motor
    autoAngle += (5 * direction);
    if (autoAngle >= 180 || autoAngle <= 0) {
      direction *= -1; // Inverte o sentido ao chegar nos limites
    }
    servoAngle = autoAngle;
    delay(50); // Controla a velocidade do movimento automático
  } else {
    // MODO MANUAL: Lê o valor do ADC (Potenciômetro)
    int potValue = analogRead(POT_PIN); // Retorna de 0 a 4095
    servoAngle = map(potValue, 0, 4095, 0, 180); // Mapeia para graus
    delay(15); // Pequeno atraso para estabilidade do ADC
  }

  // 4. Mapeamento e Aplicação do Sinal MCPWM
  // Converte o ângulo (0-180) para a largura de pulso em microssegundos (500-2500)
  pulseWidth = map(servoAngle, 0, 180, SERVO_MIN_PULSEWIDTH, SERVO_MAX_PULSEWIDTH);
  
  // Aplica a largura de pulso exata utilizando a função avançada da API MCPWM
  mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulseWidth);

  // 5. Monitoramento via Serial (Conforme exigido)
  Serial.print("Modo: "); 
  Serial.print(autoMode ? "AUTOMATICO" : "MANUAL    ");
  Serial.print(" | Angulo: "); 
  Serial.print(servoAngle);
  Serial.print(" graus | Largura de Pulso: "); 
  Serial.print(pulseWidth);
  Serial.println(" us");

  // 6. Atualização do Display OLED (Monitoramento visual local)
  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.println("--- Controle MCPWM ---");
  
  display.setCursor(0, 20);
  display.print("Modo: ");
  display.println(autoMode ? "AUTOMATICO" : "MANUAL");
  
  display.setCursor(0, 35);
  display.print("Posicao: ");
  display.print(servoAngle);
  display.println((char)247); // Símbolo ASCII para "Graus"
  
  display.setCursor(0, 50);
  display.print("Pulso: ");
  display.print(pulseWidth);
  display.println(" us");
  
  display.display();
}