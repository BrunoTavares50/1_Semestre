#include <Arduino.h>
#include <Bounce2.h>

#define pinLed 2
#define pinLedE 14
#define botao 0
#define botaoE 12

Bounce button = Bounce();

unsigned long tempoA;
unsigned long tempoI;

int contador = 0;

unsigned long tempoA_L;
unsigned long tempoI_L;

bool estBotao = 0;
bool estAnt = 0;
bool estBotaoE = 0;
bool estAntE = 0;
bool estLed = 0;
bool estLedE = 0;

bool pisca;



void setup()
{
  Serial.begin(9600);

  pinMode(pinLed, OUTPUT);
  //pinMode(botao, INPUT_PULLUP);
  pinMode(pinLedE, OUTPUT);
  //pinMode(botaoE, INPUT_PULLUP);

  button.attach(botaoE, INPUT_PULLUP);
}

void loop()
{
  button.update();//digitalRead

  //Serial.println(button.fell());
  //pressionado - retorna true quando o botao for pressionado

  //Serial.println(button.read());
  //le o botao e retorna a leitura

  //Serial.println(button.fell());
  //retorna true quando o botao for solto

  //Serial.println(button.changed());
  //retorna true quando existe uma alteração

  //Serial.println(button.currentDuration());
  //retorna o tempo do estado atual do botao

  //Serial.println(button.previousDuration());
  //retorna o tempo do estado anterior do botao


  if(button.currentDuration() >= 2000 && !button.read())
  {
    pisca = 1;
  }

   if(button.currentDuration() >= 2000 && button.read())
  {
    pisca = 0;
  }


  if(button.fell())
  {
    Serial.println(contador++);
  }


  tempoA = millis();
  tempoA_L = millis();
  

  /* if(estAnt == 1 && estBotao == 0)
  {
    tempoI = tempoA;
  }

  if(estAnt == 0 && estBotao == 1)
  {
    if(tempoA - tempoI >= 2000){
      pisca = !pisca;
      tempoI = tempoA;
    }
  }*/

  if(estAntE == 1 && estBotaoE == 0)
  {
    estLedE = !estLedE;
  }

  if(pisca == 1){ 
   estLed = !estLed;
  }
  
  if(tempoA_L - tempoI_L >= 500){
   
    digitalWrite(pinLed, estLed);    
    tempoI_L = tempoA_L;
  } 
  
  digitalWrite(pinLedE, estLedE);

  //estAnt = estBotao;
  //estAntE = estBotaoE;
  //Serial.println();
}

