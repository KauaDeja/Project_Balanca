#include "HX711.h";
#include "LiquidCrystal_I2C.h";

HX711 escala;


const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
  escala.begin (LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 
  lcd.init();
  lcd.backlight();
 
  Serial.begin(9600);
  Serial.print("Leitura do Valor ADC:  ");
  Serial.println(escala.read());   // Aguada até o dispositivo estar pronto
  Serial.println("Nao coloque nada na balanca!");
  Serial.println("Iniciando...");
  escala.set_scale(442278.125);     // Substituir o valor encontrado para escala
  escala.tare(20);                // O peso é chamado de Tare.
  Serial.println("Insira o item para Pesar");
}
 
void loop() {
  lcd.setCursor(2, 0);
  lcd.print("Balanca SENAS");
  lcd.setCursor(0, 1);
  lcd.print("Peso: ");
  lcd.print(escala.get_units(20) * 1000, 1);
  lcd.println(" g  ");
  delay(1000);
}