/*
  Autor: Davi Cedraz

  Data: Agosto 2016

  Arduino

  Braço Robótico

  ############################################

  Controle dos servos via Monitor Serial e comunicação Android

  INSTRUÇÕES

  A - (100 - 135  GRAUS) : MOVIMENTA A GARRA
  B - (35 - 160 GRAUS) : MOVIMENTA A BASE
  C - (80 - 100 GRAUS) : MOVIMENTA O EIXO CENTRAL
  D - (60 - 100 GRAUS) : MOVIMENTA O EIXO LATERAL

*/

// Bibliotecas auxiliares padrão
#include <Servo.h>

// Definição de constantes
#define servoGarra       10 // Servo 1 no protótipo
#define servoBase        9 // Servo 4 no protótipo
#define servoCentral     8 // Servo 2 no protótipo
#define servoLateral     7 // Servo 3 no protótipo

// Funções para movimento suave e comunicacao
void splitString(char* data);
void setPosition(char* data);

// Variáveis
char buffer[5]; //vetor para armazenar string de texto
boolean run = false; //verifica constantemente se o comando de guarda foi recebido
int Ans;   //recebe o valor inteiro do angulo recebido
int increment = 10;  //delay padrao para suavização dos movimentos

// variaveis para guardar a posição inicial dos servos
int Pos = 0;  //variavel genérica
int pos_garra = 70;
int pos_base = 97;
int pos_central = 150;
int pos_lateral = 30;

// Atribuição de objetos (servos do braço)
Servo servo;  //variavel genérica
Servo servo_base;
Servo servo_garra;
Servo servo_central;
Servo servo_lateral;

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

  servo_garra.write(pos_garra);           // seta um posicionamento inicial para teste do braço
  servo_base.write(pos_base);
  servo_central.write(pos_central);
  servo_lateral.write(pos_lateral);

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

    if (numChar > 5) numChar = 5; //evita o estouro do buffer

    while (numChar--) { //executa até que numChar seja zero

      buffer[index++] = Serial.read(); //le a serial e armazena no vetor
    }
    splitString(buffer); //chama a função splitString com buffer como parametro
  }

}

void splitString(char* data) {
  Serial.println(data);

  char* parameter; //variavel para acessar os elementos do vetor data
  parameter = strtok (data, " ,"); //divide a string quando encontrar um espaço ou uma
  //vírgula

  while (parameter != NULL) { //executa enquanto parameter não estiver vazia
    setPosition(parameter);
    parameter = strtok (NULL, " ,"); //preenche o vetor com caracteres NULL
  }

  //Limpa o texto e os buffers seriais
  for (int x = 0; x < 5; x++) {
    buffer[x] = '\0';
  }

  Serial.flush(); //libera caracteres que estejam na linha
  //serial, deixando-a pronta para in/outs
}

// Funções de Movimento de cada Servo
void selectServo(char comand) {
  if ((comand == 'a') || (comand == 'A')) {
    if (Pos != 0)
      pos_garra = Pos;
    else
      Pos = pos_garra;

    servo = servo_garra;
    Ans = constrain(Ans, 70, 105); //garante que o valor digitado esteja entre 70 e 105
  }
  else if ((comand == 'b') || (comand == 'B')) {
    if (Pos != 0)
      pos_base = Pos;
    else
      Pos = pos_base;

    servo = servo_base;
    Ans = constrain(Ans, 35, 160); //garante que valor digitado esteja entre 35 e 160
  }
  else if ((comand == 'c') || (comand == 'C')) {
    if (Pos != 0)
      pos_central = Pos;
    else
      Pos = pos_central;

    servo = servo_central;
    Ans = constrain(Ans, 30, 160); //garante que valor digitado esteja entre 30 e 160
  }
  else if ((comand == 'd') || (comand == 'D')) {
    if (Pos != 0)
      pos_lateral = Pos;
    else
      Pos = pos_lateral;

    servo = servo_lateral;
    Ans = constrain(Ans, 30, 160); //garante que valor digitado esteja entre 30 e 160
  }
}

void setPosition(char* data) {
  if (data[0] == '!') {

    run = true;
    Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto

    selectServo(data[1]);

    if (Ans < Pos) {        //condição que define a direção do movimento(Abre/Fecha, Sobe/Desce)

      for (int i = Pos; Pos >= Ans; i--) {
        servo.write(i); //atribui o grau da posição do eixo do servo
        delay(increment);
      }

      Serial.print("O servo esta na angulacao: ");
      Serial.println(Ans);
    }
    else {

      for (int i = Pos; i < Ans; i++) {
        servo.write(i); //atribui o grau da posição do eixo do servo
        delay(increment);
      }

      Serial.print("O servo esta na angulacao: ");
      Serial.println(Ans);
    }

    Pos = Ans;
    selectServo(data[1]);
  }
  else {
    run = false;
    Serial.print("Erro de comunicacao");
  }
}
