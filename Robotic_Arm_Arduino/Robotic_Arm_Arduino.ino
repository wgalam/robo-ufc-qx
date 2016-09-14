/*
  Autor: Davi Cedraz

  Data: Agosto 2016

  Arduino

  Braço Robótico

  ############################################

  Controle dos servos via Monitor Serial

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

// Funções para movimento suave
void splitString(char* data);
void setPosition(char* data);

// Variáveis
char buffer[18]; //vetor para armazenar string de texto
boolean run = false; //verifica constantemente se o comando de guarda foi recebido

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

 servo_garra.write(70);           // seta um posicionamento inicial para teste do braço
 servo_base.write(97);
 servo_central.write(150);
 servo_lateral.write(30);

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
    }
    splitString(buffer); //chama a função splitString com buffer como parametro
  }

}

// Funções de Movimento de cada Servo

void splitString(char* data){
  Serial.println(" ");
  Serial.print("                  Data entered: ");
  Serial.println(data);
  Serial.println("....................................");
  Serial.print(">> ");
  char* parameter; //variavel para acessar os elementos do vetor data
  parameter = strtok (data, " ,"); //divide a string quando encontrar um espaço ou uma
  //vírgula

  while (parameter != NULL){ //executa enquanto parameter não estiver vazia
    setPosition(parameter);
    parameter = strtok (NULL, " ,"); //preenche o vetor com caracteres NULL
  }

  //Limpa o texto e os buffers seriais
  for (int x = 0; x < 16; x++){
    buffer[x] = '\0';
  }

  Serial.flush(); //libera caracteres que estejam na linha
  //serial, deixando-a pronta para in/outs
}

// Funções de Movimento de cada Servo

void setPosition(char* data) {
  if (data[0] == '!') {
    
    run = true;
    
    if ((data[1] == 'a') || (data[1] == 'A')) { //verifica letra inicial (qual servo irá receber os comandos de movimento)

      int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
      Ans = constrain(Ans, 70, 105); //garante que Ans esteja entre 0 e 45

      int Ans2 = 0;

      if (Ans < Ans2) {        //condição que define a direção do movimento(Abre/Fecha, Sobe/Desce)

        int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
        Ans = constrain(Ans, 70, 105); //garante que Ans esteja entre 0 e 45

        for (int i = 0; Ans2 >= Ans; i--) {
          servo_garra.write(i); //atribui o grau da posição do eixo do servo
          delay(10);
        }

        Serial.print("A Garra esta na angulacao: ");
        Serial.println(Ans);
      }

      for (int i = 0; i < Ans; i++) {
        servo_garra.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Ans2 = Ans;

      Serial.print("A Garra esta na angulacao: ");
      Serial.println(Ans);
    }

    if ((data[1] == 'b') || (data[1] == 'B')) { //verifica letra inicial (qual servo irá receber os comandos de movimento)

      int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
      Ans = constrain(Ans, 35, 160); //garante que Ans esteja entre 0 e 45

      int Ans2 = 0;

      if (Ans < Ans2) {   //condição que define a direção do movimento(Abre/Fecha, Sobe/Desce)

        int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
        Ans = constrain(Ans, 35, 160); //garante que Ans esteja entre 0 e 45

        for (int i = 0; Ans2 >= Ans; i--) {
          servo_base.write(i); //atribui o grau da posição do eixo do servo
          delay(10);
        }

        Serial.print("A Base esta na angulacao: ");
        Serial.println(Ans);
      }

      for (int i = 0; i < Ans; i++) {
        servo_base.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Ans2 = Ans;

      Serial.print("A Base esta na angulacao: ");
      Serial.println(Ans);
    }

    if ((data[1] == 'c') || (data[1] == 'C')) { //verifica letra inicial (qual servo irá receber os comandos de movimento)

      int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
      Ans = constrain(Ans, 30, 160); //garante que Ans esteja entre 0 e 45

      int Ans2 = 0;

      if (Ans < Ans2) {   //condição que define a direção do movimento(Abre/Fecha, Sobe/Desce)

        int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
        Ans = constrain(Ans, 30, 160); //garante que Ans esteja entre 0 e 45

        for (int i = 0; Ans2 >= Ans; i--) {
          servo_central.write(i); //atribui o grau da posição do eixo do servo
          delay(10);
        }

        Serial.print("O Servo central esta na angulacao: ");
        Serial.println(Ans);
      }

      for (int i = 0; i < Ans; i++) {
        servo_central.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Ans2 = Ans;

      Serial.print("O Servo central esta na angulacao: ");
      Serial.println(Ans);
    }

    if ((data[1] == 'd') || (data[1] == 'D')) { //verifica letra inicial (qual servo irá receber os comandos de movimento)

      int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
      Ans = constrain(Ans, 30, 160); //garante que Ans esteja entre 0 e 45

      int Ans2 = 0;

      if (Ans < Ans2) {   //condição que define a direção do movimento(Abre/Fecha, Sobe/Desce)

        int Ans = strtol(data + 2, NULL, 10);   //define Ans como numero na proxima parte do texto
        Ans = constrain(Ans, 30, 160); //garante que Ans esteja entre 0 e 45

        for (int i = 0; Ans2 >= Ans; i--) {
          servo_lateral.write(i); //atribui o grau da posição do eixo do servo
          delay(10);
        }

        Serial.print("O Servo lateral esta na angulacao: ");
        Serial.println(Ans);
      }

      for (int i = 0; i < Ans; i++) {
        servo_lateral.write(i); //atribui o grau da posição do eixo do servo
        delay(10);
      }

      Ans2 = Ans;

      Serial.print("O Servo lateral esta na angulacao: ");
      Serial.println(Ans);
    }
  }
  else {
    run = false;
    Serial.print("Erro de comunicacao");
  }

}
