#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h>
#include <MQUnifiedsensor.h>

MQUnifiedsensor mq3("ESP-32", 3.3, 12, 25, "MQ-2");
BluetoothSerial BT;
Bounce botaozinho = Bounce();
JsonDocument doc;

String jsonString;

unsigned long tempoA;
unsigned long tempoI;

// F4:65:0B:47:1F:56
uint8_t endSlave[] = {0xF4, 0x65, 0x0B, 0x47, 0x1F, 0x56};

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(5000);

  botaozinho.attach(0, INPUT_PULLUP);

  mq3.init();

  if (BT.begin("EspMasterBrunotp", true))
  {
    Serial.println("Bluetooth iniciado com sucesso");
  }
  else
  {
    Serial.println("Erro ao iniciar o bluetooth");
  }

  if (BT.connect(endSlave))
  {
    Serial.println("Conectado com sucesso");
  }
  else
  {
    Serial.println("Erro ao conectar");
  }
}

void loop()
{
  botaozinho.update();
  tempoA = millis();

  mq3.update();
  float valor = mq3.getRS();

  serializeJson(doc, jsonString);
  doc["gas"] = mq3.getRS();
  
  if (BT.available())
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    Serial.println(mensagemRecebida);
    
  }
  if(tempoA - tempoI >= 1000)
    {
      BT.println(jsonString);
      tempoI = tempoA;
    }

  if (Serial.available())
  {
    String mensagemEnviar = Serial.readStringUntil('\n');
    mensagemEnviar.trim();
    
    
    
    if (!mensagemEnviar.equals(""))
    {
      Serial.printf("Mensagem enviada: %s\n", mensagemEnviar);

      Serial.println("");
    }
  }
}