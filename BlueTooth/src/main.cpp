#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define pinLed 27
#define botao 0

#define DHTPIN 15
#define DHTTYPE DHT22

unsigned long tempoA;
unsigned long tempoI;

bool pisca;
bool estLed;
bool estBotao;
bool tempoBotao;

int dhtAlteracao;

BluetoothSerial BT;
Bounce botaozinho = Bounce();
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);

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
  tempoA = millis();
  botaozinho.update();
  tempoBotao = botaozinho.read();

  float t = dht.readTemperature();
  float u = dht.readHumidity();
  float f = dht.readTemperature(true);


  if (BT.available())
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    Serial.printf("\nMensagem recebida: %s", mensagemRecebida);

    if(mensagemRecebida.substring(0, 1) == "U")
    {
      lcd.setCursor(0, 0);
      lcd.print(mensagemRecebida);
    }

    if(mensagemRecebida.substring(0, 1) == "T")
    {
      lcd.setCursor(0, 1);
      lcd.print(mensagemRecebida);
    }

    if(mensagemRecebida.substring(0, 1) == "f")
    {
      lcd.setCursor(0, 2);
      lcd.print(mensagemRecebida);
    }

    if (mensagemRecebida == "liga")
    {
      digitalWrite(pinLed, HIGH);
    }

    else if (mensagemRecebida == "desliga")
    {
      digitalWrite(pinLed, LOW);
      pisca = 0;
    }
    else if (mensagemRecebida == "pisca")
    {
      pisca = 1;
    }
  }

  if(botaozinho.fell() && estBotao == 0)
  {
    estBotao = 1;
    BT.println("liga");
  }
  else if(botaozinho.fell() && estBotao == 1)
  {
    estBotao = 0;
    BT.println("desliga");
  }


  if(tempoBotao == 0 && botaozinho.currentDuration() == 2000)
  {
    tempoBotao = 1;
    BT.println("pisca");
  }
  
  //Serial.println(botaozinho.currentDuration());

    

  if (pisca)
  {
    if (tempoA - tempoI >= 500)
    {
      estLed = !estLed;
      tempoI = tempoA;
    }
    digitalWrite(pinLed, estLed);
  }

   

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