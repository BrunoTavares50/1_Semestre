#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

#define pinLed 27
#define botao 0

#define DHTPIN 15
#define DHTTYPE DHT22

// unsigned long tempoA_T;
// unsigned long tempoI_T;

// unsigned long tempoA_U;
// unsigned long tempoI_U;

// unsigned long tempoA_F;
// unsigned long tempoI_F;

bool pisca;
bool estLed;
bool estBotao;
bool tempoBotao;

float leituraAnt_T;
float leituraAnt_U;
float leituraAnt_F;

BluetoothSerial BT;
Bounce botaozinho = Bounce();
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);
JsonDocument doc;

// F4:65:0B:47:1F:56
uint8_t endSlave[] = {0xF4, 0x65, 0x0B, 0x47, 0x1F, 0x56};

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(5000);
  pinMode(pinLed, OUTPUT);
  botaozinho.attach(0, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  dht.begin();

  // float t = dht.readTemperature();
  // float u = dht.readHumidity();
  // float f = dht.readTemperature(true);

  // leituraAnt_T = dht.readTemperature();
  // t = leituraAnt_T;

  // leituraAnt_U = dht.readTemperature();
  // u = leituraAnt_U;

  // leituraAnt_F = dht.readTemperature();
  // f = leituraAnt_F;

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
  // tempoA_T = millis();
  // tempoA_U = millis();
  // tempoA_F = millis();
  botaozinho.update();
  tempoBotao = botaozinho.read();

  float t = dht.readTemperature();
  float u = dht.readHumidity();
  float f = dht.readTemperature(true);

  // if(t != leituraAnt_T && tempoA_T - tempoI_T >= 1000)
  // {
  //   Serial.print("Temperatura: ");
  //   Serial.print(t);
  //   leituraAnt_T = t;
  //   tempoI_T = tempoA_T;
  //   Serial.println("");
  // }

  // if(u != leituraAnt_U && tempoA_U - tempoI_U >= 1000)
  // {
  //   Serial.print("Umidade: ");
  //   Serial.print(u);
  //   leituraAnt_U = u;
  //   tempoI_U = tempoA_U;
  //   Serial.println("");
  // }

  // if(f != leituraAnt_F && tempoA_F - tempoI_F >= 1000)
  // {
  //   Serial.print("Fahrenheit: ");
  //   Serial.print(f);
  //   leituraAnt_F = f;
  //   tempoI_F = tempoA_F;
  //   Serial.println("");
  // }
  
  if (BT.available())
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    deserializeJson(doc, mensagemRecebida);
    Serial.println(mensagemRecebida);
    
    float umidade = doc["Umidade"];
    float tempC = doc["Temperatura"];
    float tempF = doc["Fah"];

    lcd.setCursor(0, 0);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.setCursor(0, 1);
    lcd.print("Temp C: ");
    lcd.print(tempC);
    lcd.setCursor(0, 2);
    lcd.print("Temp F: ");
    lcd.print(tempF);

    if(mensagemRecebida.substring(0, 1) == "U")
    {
      
    }

    if(mensagemRecebida.substring(0, 1) == "T")
    {
      
    }

    if(mensagemRecebida.substring(0, 1) == "f")
    {
      
    }
  }
  //   if (mensagemRecebida == "liga")
  //   {
  //     digitalWrite(pinLed, HIGH);
  //   }

  //   else if (mensagemRecebida == "desliga")
  //   {
  //     digitalWrite(pinLed, LOW);
  //     pisca = 0;
  //   }
  //   else if (mensagemRecebida == "pisca")
  //   {
  //     pisca = 1;
  //   }
  // }

  // if(botaozinho.fell() && estBotao == 0)
  // {
  //   estBotao = 1;
  //   BT.println("liga");
  // }
  // else if(botaozinho.fell() && estBotao == 1)
  // {
  //   estBotao = 0;
  //   BT.println("desliga");
  // }


  // if(tempoBotao == 0 && botaozinho.currentDuration() == 2000)
  // {
  //   tempoBotao = 1;
  //   BT.println("pisca");
  // }
  
  //Serial.println(botaozinho.currentDuration());

    

  // if (pisca)
  // {
  //   if (tempoA - tempoI >= 500)
  //   {
  //     estLed = !estLed;
  //     tempoI = tempoA;
  //   }
  //   digitalWrite(pinLed, estLed);
  // }

   

  if (Serial.available())
  {
    String mensagemEnviar = Serial.readStringUntil('\n');
    mensagemEnviar.trim();

    
    
    if (!mensagemEnviar.equals(""))
    {
      Serial.printf("Mensagem enviada: %s\n", mensagemEnviar);
      BT.println(mensagemEnviar);
      Serial.println("");
    }
  }
}