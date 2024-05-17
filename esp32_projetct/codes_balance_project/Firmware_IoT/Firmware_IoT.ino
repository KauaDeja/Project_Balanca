// INCLUI BIBLIOTECAS
#include <WiFi.h>         // Biblioteca que permite comunicação WiFi do Hardware embutido no ESP32
#include <HTTPClient.h>   // Biblioteca que permite comunicar ESP32 com um servidor WEB
#include <Arduino.h>      // Biblioteca que permite utilizar algumas funções do Arduino no ESP32
#include <esp_task_wdt.h> // Biblioteca que permite manipular o watchdog no segundo núcleo
#include <HX711.h>
#include <LiquidCrystal_I2C.h>

TaskHandle_t Task1;       // Declara tarefa que será executada no segundo núcleo (dual core)

#define LED_ESP32 2

const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 5;

const char *ssid = "iPhone de Andressa";
const char *password = "";

float PESO_MAXIMO = 5000;
float PESO_ATUAL = 0.0;
float PORCENTAGEM_USADA = 0.0;
float PORCENTAGEM_MAXIMA = 0.0;
bool balancaFuncionando = false;


char serverAddress[] = "https://api.tago.io/data"; 
char contentHeader[] = "application/json";                   
char tokenHeader[] = "382c22ac-af3f-40ed-ae58-415e30caf7c2";  


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// CRIA CLASSES
WiFiClient wifi;                           
HTTPClient client;           
HX711 escala;   
LiquidCrystal_I2C lcd(0x27, 16, 2);

//SETUP -----------------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
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

  pinMode(LED_ESP32, OUTPUT); // Declara LED da placa do ESP32 como saída
  Serial.begin(9600);     // Inicia comunicação Serial para monitoramento
  conecta_wifi();         // Conecta Wifi
  xTaskCreatePinnedToCore( Task1code,"Task1", 10000, NULL, 1, &Task1, 0); //Habilita o uso do Núcleo 0 (dual core)
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------



//LOOP ------------------------------------------------------------------------------------------------------------------------------------------------------
void loop ()
{
  //Calculo 
  PESO_ATUAL = escala.get_units(20) * 1000, 1;
  PORCENTAGEM_MAXIMA = 100;
  PORCENTAGEM_USADA = (PESO_ATUAL / PESO_MAXIMO) * 100;

  lcd.setCursor(2, 0);
  lcd.print("Balanca SENAI");
  lcd.setCursor(0, 1);
  lcd.print("Peso: ");
  lcd.print(escala.get_units(20) * 1000, 1);
  
  //Serial.println(PESO_ATUAL);
  Serial.begin(9600);
  //Serial.print(PORCENTAGEM_USADA);
  delay(1000);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------


        

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
void loop_2 ()
{


    //LOOP do núcleo 0
      // Envia variável TEMPERATURA para o TagoIO (VARIAVEL, GRANDEZA, UNIDADE)
      envia_TagoIO (PESO_ATUAL, "PESO", "g");
      envia_TagoIO (PORCENTAGEM_MAXIMA, "MAXIMA", "%");
      envia_TagoIO (PORCENTAGEM_USADA, "PORCENTAGEM", "%");

      Serial.begin(9600);
      delay(3000);   // Aguarda até o próximo envio 
      digitalWrite(LED_ESP32, LOW);
      delay(1000);
      digitalWrite(LED_ESP32, HIGH);
      delay(1000);

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------