// Chamar as bibliotecas complementares para o HX711 e o LCD
#include "HX711.h"
#include "LiquidCrystal_I2C.h"


// Configuração dos pinos no ESP32 e HX711
const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 5;

HX711 escala;    // Relaciona a variável escala
 
void setup() {
  escala.begin (LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.begin(9600);
  Serial.print("Leitura da Tara:  ");
  Serial.println(escala.read());  // Aguada o termino de verificação do peso
  Serial.println("Aguarde!");
  Serial.println("Iniciando ...");
  escala.set_scale();             // Utiliza uma escala padrão de verificação
 
  escala.tare(20);                // Fixa o peso como tara
  Serial.println("Insira o item para Pesar"); 
}
 
void loop() {
  Serial.print("Valor da Leitura:  ");
  Serial.println(escala.get_value(10),0);  // Retorna peso descontada a tara
  delay(100);
}
