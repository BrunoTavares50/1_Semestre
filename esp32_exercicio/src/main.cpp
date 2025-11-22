//Exercicio
//Montar um circuito contendo 2 botões e 1 LED
//Etapa 1
//Ao pressionar o botão 1 o led deve aumentar a intensidade (de 0 a 100%)
//Ao pressionar o botão 2 o led deve diminuir a intensidade (de 100% a 0)

//Etapa 2
//Escrever no LCD a porcentagem da intensidade do LED

#include <Arduino.h>
#include <Bounce2.h>
#include <LiquidCrystal_I2C.h>

Bounce botaozinho = Bounce();
Bounce botaozinhoB = Bounce();

LiquidCrystal_I2C lcd(0x27,20,4);

#define pinLed 14
#define botaoA 0
#define botaoB 12

int Brilho;
int BrilhoAnt = -1;
int Brilho_remap;

void setup() 
{
  Serial.begin(9600);

  botaozinho.attach(botaoA, INPUT_PULLUP);
  botaozinhoB.attach(botaoB, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Brilho: ");
 
  pinMode(pinLed, OUTPUT);

}

void loop() 
{
  botaozinho.update();
  botaozinhoB.update();

  if(botaozinho.fell())
  { 
    Brilho += 10;
  }

  if(botaozinhoB.fell())
  {
    Brilho -= 10;   
  }

  Brilho = constrain(Brilho, 0, 100);

  Brilho_remap = map(Brilho, 0, 100, 0, 255);
  analogWrite(pinLed, Brilho_remap);

  if(Brilho != BrilhoAnt)
  {
    lcd.setCursor(8, 0);
    lcd.print(Brilho + String("%"));

    if(Brilho < 100)
    {
     lcd.setCursor(11, 0);
     lcd.print(" ");
    }
    
    if(Brilho < 10)
    {
     lcd.setCursor(10, 0);
     lcd.print(" ");
    }
  }
  
}