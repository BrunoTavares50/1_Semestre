#include <Arduino.h>

//char - mais recomendado para uso profissioal
//String - mais fácil

char palavra2[] = "OLA MUNDO";
String palavra3 = "OLA MUNDO";


void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println(palavra2);

  //------------- FUNCOES PARA CHAR -----------------//
  
  strcpy(palavra2, "SENAI");//substitui o valor anterior
  // Serial.println(palavra2);

  // Serial.println(strcmp(palavra2, "SENAI"));//se for igual retorna 0

  // if(strcmp(palavra2, "SENAI") == 0)
  // {
  //   Serial.println("São iguais");
  // }

  // else
  // {
  //   Serial.println("São diferentes");
  // }

  // Serial.println(strncmp(palavra2, "SENAI", 5));//compara a quantidade de caracteres

  // if(!strncmp(palavra2, "SENAI", 5))
  // {
  //   Serial.println("Quantidade de caracteres iguais");
  // }

  //strstr();//procura dentro da string pela primeira ocorrencia de uma substring
  // if(strstr(palavra2, "NAI"))
  // {
  //   Serial.println("palavra encontrada");
  // }

  // Serial.println(strcat(palavra2, "-SP"));//concatena duas strings, ou seja junta


  
  //---------------------- FUNCOES PARA STRING --------------------------//
  // Serial.println(palavra3.length());//retorna a quantidade de caracteres 
  // Serial.println(palavra3.charAt(2));//retorna o caracter da posição indicada
  // Serial.println(palavra3.substring(2, 5));//retorna um pedaço da string original
  // Serial.println(palavra3.indexOf("M"));//retorna a posição do elemento procurado
  // Serial.println(palavra3.lastIndexOf("O"));//retorna a posição do ultimo elemento procurado
  
  //equals() //Compara se é igual
  // if(palavra3.equalsIgnoreCase("ola mundo"))
  // {
  //   Serial.println("iguais");
  // }

  // if(palavra3.startsWith("OLA"))
  // Serial.println("o inicio é igual");

  // if(palavra3.endsWith("DO"))
  // Serial.println("o fim é igual");

  // palavra3.toLowerCase();//converte para caixa baixa
  // palavra3.toUpperCase();//converte para caixa alta
  // Serial.println(palavra3);

  // String valor = "100";
  // int numero = valor.toInt();
  // float numeroF = valor.toFloat();

  // String texto = "texto          ";
  // texto.trim();

  // String instrucao = "Led = ON";
  // instrucao.replace("ON", "OFF");

  Serial.setTimeout(10000);
  String texto = Serial.readStringUntil('\n');
  texto.trim();
  Serial.printf("voce digitou %s!", texto);

  // Serial.printf("variavel1 : %s, variavel2 : %i", texto);//concatenação com printf
  
  


}

void loop() 
{


}

