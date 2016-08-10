/*
  Autor: Davi Cedraz

  Data: Agosto 2016

  Arduino

  Braço Robótico

  ############################################

  Controle dos servos via Serial Monitor

  INSTRUÇÕES

  A - (0 - 180 GRAUS) : MOVIMENTA A GARRA
  B - (0 - 180 GRAUS) : MOVIMENTA A BASE
  C - (0 - 180 GRAUS) : MOVIMENTA O EIXO CENTRAL
  D - (0 - 180 GRAUS) : MOVIMENTA O EIXO LATERAL

  1 - PARA ABRIR/SUBIR
  0 - PARA FECHAR/DESCER

*/

// Bibliotecas auxiliares padrão
#include <Servo.h>


// Definição de constantes
#define servoGarra       10
#define servoBase        9
#define servoCentral     8
#define servoLateral     7


// Funções para movimento suave
void splitString(char* data);
void setPosition(char* data);
boolean comand(boolean*key);

// Variáveis
char buffer[18]; //vetor para armazenar string de texto

boolean key = false; //variavel para guardar a orientação do movimento p/ angulo

// Atribuição de objetos (servos do braço)
Servo servo_base;
Servo servo_garra;
Servo servo_central;
Servo servo_lateral;

// Configuração inicial do MCU
void setup() {

  Serial.begin(9600);  //inicia comunicação serial a 9600bps
  Serial.flush();      //libera caracteres que estejam na linha
  //serial, deixando-a pronta para in/outs

  pinMode(servoGarra, OUTPUT);
  pinMode(servoBase, OUTPUT);
  pinMode(servoCentral, OUTPUT);
  pinMode(servoLateral, OUTPUT);


  servo_garra.attach(10);
  servo_base.attach(9);
  servo_central.attach(8);
  servo_lateral.attach(7);


  servo_garra.write(90);           // seta um posicionamento inicial para teste do braço
  servo_base.write(90);
  servo_central.write(100);
  servo_lateral.write(110);

  delay(10000);

}


void loop() {

  if (Serial.available() > 0) { //verifica se foi enviado um caractere
    //para serial
    int index = 0; //armazena a posição de um ponteiro para os
    //caracteres do vetor

    delay(100); //deixa o buffer encher
    int numChar = Serial.available(); //atribui o numero de
    //caracteres digitados

    if (numChar > 15) numChar = 15; //evita o estouro do buffer

    while (numChar--) { //executa até que numChar seja zero

      buffer[index++] = Serial.read(); //le a serial e armazena no vetor
      key.Serial.read(); // le a orientação do movimento
    }
    splitString(buffer); //chama a função splitString com buffer como parametro
    comand(key);         //chama a função com a orientação do moivmento como parametro
  }


}

boolean comand(boolean* key) {
  if (key == true) {
    return true;
  }
  else {
    return false;
  }
}


void splitString(char* data) {
  Serial.println(" ");
  Serial.print("                  Data entered: ");
  Serial.println(data);
  Serial.println("....................................");
  Serial.print(">> ");
  char* parameter; //variavel para acessar os elementos do vetor data
  parameter = strtok (data, " ,"); //divide a string quando encontrar um espaço ou uma
  //vírgula

  while (parameter != NULL) //executa enquanto parameter não estiver vazia
  {
    setPosition(parameter);
    parameter = strtok (NULL, " ,"); //preenche o vetor com caracteres NULL
  }

  //Limpa o texto e os buffers seriais
  for (int x = 0; x < 16; x++)
  {
    buffer[x] = '\0';
  }

  Serial.flush(); //libera caracteres que estejam na linha
  //serial, deixando-a pronta para in/outs
}


// Funções de Movimento de cada Servo

void setPosition(char* data) {
  if ((data[0] == 'a') || (data[0] == 'A')) { //verifica letra inicial (qual servo)

    if (comand(key) == true) { //verifica a orientação do movimento (abre/fecha, sobe/desce)

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i < Ans; i++) {
        servo_garra.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("A Garra está na angulação: ");
      Serial.println(Ans);

    }
    else {

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i > Ans; i--) {
        servo_garra.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("A Garra está na angulação: ");
      Serial.println(Ans);

    }

  }

  if ((data[0] == 'b') || (data[0] == 'B')) {

    if (comand(key) == true) { //verifica a orientação do movimento (abre/fecha, sobe/desce)

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i < Ans; i++) {
        servo_base.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo da Base está na angulação: ");
      Serial.println(Ans);

    }
    else {

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i > Ans; i--) {
        servo_base.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo da Base está na angulação: ");
      Serial.println(Ans);

    }

  }

  if ((data[0] == 'c') || (data[0] == 'C')) {

    if (comand(key) == true) { //verifica a orientação do movimento (abre/fecha, sobe/desce)

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i < Ans; i++) {
        servo_central.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo Central está na angulação: ");
      Serial.println(Ans);

    }
    else {

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i > Ans; i--) {
        servo_central.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo Central está na angulação: ");
      Serial.println(Ans);

    }

  }

  if ((data[0] == 'd') || (data[0] == 'D')) {

    if (comand(key) == true) { //verifica a orientação do movimento (abre/fecha, sobe/desce)

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i < Ans; i++) {
        servo_lateral.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo Lateral está na angulação: ");
      Serial.println(Ans);

    }
    else {

      int Ans = strtol(data + 1, NULL, 10);   //define Ans como numero na proxima parte do texto

      Ans = constrain(Ans, 0, 180); //garante que Ans esteja entre 0 e 180

      for (int i = 0; i > Ans; i--) {
        servo_lateral.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Serial.print("O servo Lateral está na angulação: ");
      Serial.println(Ans);

    }

  }

}