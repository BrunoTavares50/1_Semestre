#include <Arduino.h>
#include <ArduinoJson.h>


void setup() 
{
  Serial.begin(9600);

  // float umidade = 70.5;
  // float tempC = 24.3;
  // float tempF = 80.0;

  //ENVIO DE DADOS JSON
   JsonDocument doc;
  // doc["umidade"] = umidade;
  // doc["tempC"] = tempC;
  // doc["tempF"] = tempF;

  // String JsonString;
  // serializeJson(doc, JsonString);

  // Serial.println("Dados em formato JSON:");
  // Serial.println(JsonString);



  //RECEBIMENTO DE DADOS JSON
  String mensagemRecebida = "{\"umidade\":60.3, \"tempC\":20.5, \"tempF\":68.9}";

  DeserializationError erro = deserializeJson(doc, mensagemRecebida);
  if(erro)
  {
    Serial.print("Erro ao interpretar o JSON: ");
    Serial.println(erro.c_str());
    return;
  }

  float umidade = doc["umidade"];
  float tempC = doc["tempC"];
  float tempF = doc["tempF"];

  Serial.println("Dados recebidos em formato JSON: ");
  Serial.print("Umidade: "); Serial.println(umidade);
  Serial.print("Temperatura em Celsius: "); Serial.println(tempC);
  Serial.print("Temperatura em Fahrenheit: "); Serial.println(tempF);
  
  
}

void loop() 
{
 
}

