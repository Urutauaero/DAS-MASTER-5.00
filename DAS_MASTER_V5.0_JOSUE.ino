// Edição feita por mim (Josué Souza)
#include <Zanshin_BME680.h>
/*
    SISTEMA DE AQUISIÇÃO DE DADOS - DAS 2019 - MASTER
    URUTAU AERODESIGN - MANAUS, 02/06/2019
    
    WALDISMAR DE OLIVEIRA SAMPAIO FILHO
    JACOBUS LAURENS DE JAGER
*/

#define dasVersion "v3.0.0"          //O define é utilizado para pré definir os parâmetros que serão usados durante o programa 
#define versionName "Versão alpha"   

#define DEBUG // Antes de iniciar o programa ou teste já eé definido um "Debug" que visa encontrar erros pré-existentes no código

#pragma GCC optimize ("-Ofast") // Pré-processamento da manipulação do otimizaddor 
#include <Wire.h> // Iniciando a biblioteca do I2C

#define baudrate 115200 // Definindo a taxa de tranferência da serial 

void MotionSystem_setup(); 
void heading_setup();     
void hp_setup();          
void telemetria_setup();  
void vcas_setup();        

float xv, yv, zv;
float heading;
float headingDegrees;

void get_data();
void serial_write();
void SD_write();

// ###########################################################################
// VARIÁVEIS GLOBAIS #########################################################
// ###########################################################################

String GyroX, GyroY, GyroZ;
String AccelX, AccelY, AccelZ;

String data_string, IDV_string;

int16_t gpsDay = 0, gpsMonth = 0, gpsYear = 0;
int16_t gpsHour = 0, gpsMinute = 0, gpsSecond = 0;

byte data_string_serial[45];

int rps;
int altint;
int wow, rpm, control_1, control_2, control_3, control_4;
int sonarDistance;
int teste1, teste2;

float hp, pbmp, vcas, PVcas;
float longfloat, latfloat, altfloat;
float maghead;
float gForceX, gForceY, gForceZ;
float gyroXrate, gyroYrate, gyroZrate;

long magheadint;
long gyroXrateint;
long gyroYrateint;
double gForceXint;
double gForceYint;
double gForceZint;

uint32_t latuint, longuint;

uint16_t servo1uint, servo2uint, servo3uint, servo4uint;

uint32_t tempo;
double temp;

int i = 0, j = 0;
uint8_t cs; // Variável de armazenamento tipo byte
//uint8_t saux, aux, tempaux; 

//RTC ###################################################################################

#include <DS3231.h> // Inicializando a bilbioteca do módulo RTC DS3231

DS3231 rtc(); // Comunição através da biblioteca wire.h e definir um 'nome' a esta biblioteca  (SDA, SCL)
//Time = t;
DateTime t; 

unsigned long h, m, s; // Variáveis declaradas para o tempo horas, minutos e segundos
//unsigned long cs;   

unsigned long saux, aux, tempaux;
bool primeiro_ciclo = true; // Pré-definição de uma repetição para o tempo

void temporizador_rtc() {// Início da função RTC
  if (primeiro_ciclo == true)   //  Laço criado para ser a primeira variável de trabalho que visa  
  {                             // possuiur um maior controle do tempo do milis no arduino como 
    primeiro_ciclo = false;     // será mais possível de entender a frente
    tempaux = millis() + 1000;  //  O 1000 é mais para um controle durante o tempo

    while (aux < tempaux) // Enquanto o 'auxílio' for menor que o 'tempo auxiliar' observamos o controle do registro do tempo
    {
  //    t = rtc.getA1Time();
//      s = t.second; // A variável 's' vira o segundo registrado pelo RTC

      if(s == saux)                           //  Quando os segundos foram iguais a primeira expressão gera um 
      {                                       // resultado que esteja dentro do número de controle para igualar 
        if (millis() - aux >= 100 && cs < 9){  // a variável 'auxiliar' ao milis
         cs = cs + 1;                        //
          aux = millis();                     //
        }
      }
      else{
        cs = 0;
        aux = millis();
      }
//      saux = t.second;
    }
  }
}

//###########################################################################################

void setup(){
  Serial.begin(baudrate); //  Início das comunicações feitas no arduino
  Wire.begin();           

  Serial.println("\n\nBEGIN: rtc.begin --------------\n");
//  rtc.begin(); // Iniciando a comunicação com o RTC

  Serial.println("\n\nCALLING: MotionSystem_setup --------------\n");
  MotionSystem_setup(); // Iniciando o sistema de movimento

  Serial.println("\n\nCALLING: heading_setup --------------\n");
  heading_setup(); 

  Serial.println("\n\nCALLING: hp_setup --------------\n");
  hp_setup(); // Captação dos dados de pressão para definir a altura

  Serial.println("\n\nCALLING: vcas_setup --------------\n");
  vcas_setup(); // 
  
  Serial.println("\n\nCALLING: telemetria_setup --------------\n");
  telemetria_setup();
//  AS FUNÇÕES FEITAS NAS PRIMEIRA LINHAS DE CÓDIGOS SÃO SOLICITADAS NO SETUP NAIS QUAIS OS 
// DEMAIS CÓDIGOS FORNECEM 
   temporizador_rtc();  
}

void loop(){ // Função que estará escrevendo no cartão sd
  //t = rtc.getA1Time(); // Esse algorimtimo já foi esplica acima
//   s = t.second;

  if (s == saux) {
    if(millis() - aux >= 100 && cs < 9){
      cs++;
      aux = millis();

      get_data();
      serial_write();
      SD_write();
    }
  }
  else{
    cs = 0;
    aux = millis();

    get_data(); //Aquisição de dados
    serial_write(); // Escreve na serial e apos escreve no cartão SD
    SD_write();
  }

//  saux = t.second;
}
