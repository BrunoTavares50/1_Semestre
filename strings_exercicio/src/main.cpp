#include <Arduino.h>

#define pinLed 2

void setup() 
{
  // Exercicio 1
  // 1 - O usuário digita um texto pelo (ex: "LED ON" ou "LED OFF").

  Serial.begin(9600);

  // pinMode(pinLed, OUTPUT);

  // Serial.setTimeout(10000);
  // String comando = Serial.readStringUntil('\n');
  // comando.trim();
  // Serial.printf("voce digitou %s!", comando);

  // if(comando.startsWith("ON"))
  // {
  //   digitalWrite(pinLed, HIGH);
  //   Serial.println("LIGAR LED");
  // }
  // else if(comando.endsWith("OFF"))
  // {
  //   digitalWrite(pinLed, LOW);
  //   Serial.println("DESLIGAR LED");
  // }
  // else
  //   Serial.print("COMANDO INVALIDO!");


  // Exercicio 2
  // 2 - Converter texto misto e extrair número

  // String mensagem = "Temperatura = 27C";
  // String valor;
  
  // valor = mensagem.substring(14, 16);
  // valor.toInt();
  // int temp = valor.toInt();
  // float fah = 80.60;


  // Serial.printf("A temperatura é: %i, em fahrenheit: %f", temp, fah);
  

  // Exercicio 3
  // 3 - Detectar palavra dentro da frase (char[])

  // char frase[] = "ESTAMOS APRENDENDO ARDUINO NA AULA";

  // if(strstr(frase, "ARDUINO") == 0)
  // {
  //   Serial.println("CONTEÚDO RELACIONADO A ARDUINO DETECTADO");
  // }
  // else
  //  Serial.println("NÃO ENCONTRADO");


  // Exercicio 4
  // 4 - Alternar maiúsculas e minúsculas   

  String frase = "sEnAi eSp32 ArDuInO";
  
  frase.toUpperCase();
  Serial.println(frase);

  frase.toLowerCase();
  Serial.println(frase);

  frase.setCharAt(0, toupper(frase.charAt(0)));
  Serial.println(frase);
  
}

void loop() 
{
  

}

