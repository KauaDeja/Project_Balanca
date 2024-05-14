//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// NÃO ALTERAR ESSA FUNÇÃO!
void conecta_wifi()
{
  WiFi.mode(WIFI_STA);
  if (ssid != "")
  WiFi.begin(ssid, password);
  WiFi.begin();
  Serial.println("");

  // Aguarda Conexão
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado em ");
  Serial.println(ssid);
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
  Serial.println(F("Dispositivo Conectado!!!"));
  
  digitalWrite(LED_ESP32 , HIGH);
  delay(500);
}





//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// NÃO ALTERAR ESSA FUNÇÃO!
void envia_TagoIO(float variavel, char nome[], char unit[])
{
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode=0;
  char x_variavel [100] = "{\n\t\"variable\": \"";
  strncat (x_variavel, nome, 100);
  strncat (x_variavel, "\",\n\t\"value\": ", 100);
  strcpy(postData, x_variavel);
  dtostrf(variavel, 6, 2, anyData);
  strncat(postData, anyData, 100);
  char x_unit [100] = ",\n\t\"unit\": \"";
  strncat (x_unit, unit, 100);
  strncat (x_unit, "\"\n\t}\n", 100);
  strncat (postData, x_unit, 100);
  
  
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
}




//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// NÃO ALTERAR ESSA FUNÇÃO!
void Task1code( void * pvParameters )
{
    esp_task_wdt_init(30, false);
    while(1)
    {
      loop_2 ();
    }
}