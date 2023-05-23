//#include <SD.h>
//#include <SPI.h>
//#include "SdFat.h"

// Variaveis


// Verificação do Status do Cartão SD
//void SD_Status () 
//{
// 
//  String cabecalho1 = F("Tempo \tRPM \tWOW  \tHP \tVCAS \tLAT    \tLON  \tROLL  \tPIT \tHEAD \tnZ  \tTemp \tPABS");
//  String cabecalho2 = F("s     \trpm \tbit  \tft \tm/s  \tdeg    \tdeg  \tdeg   \tdeg \tdeg  \tg   \tºC   \thPa");
//
//  if (!SD.begin(chipSelect))
//  {
//    Serial.println(F("Status SD:  CARTÃO SD NÃO ENCONTRADO. VERIFIQUE A PORTA SD"));
//    SD_ERROR();
//  }
//  else
//  {
//    SD_flag = 1;
//    if (SD.exists("urutau.txt"))
//    {
//      Serial.println(F("Status SD:  ARQUIVO 'urutau.txt' PRESENTE NO CARTÃO SD"));
//    }
//    else
//    {
//      Serial.println(F("Status SD:  CARTÃO SD ENCONTRADO. CRIANDO O ARQUIVO 'urutau.txt'..."));
//      cartao_SD = SD.open("urutau.txt", FILE_WRITE);
//      cartao_SD.flush();
//      cartao_SD.println(cabecalho1);
//      cartao_SD.println(cabecalho2);
//      cartao_SD.close();
//    }
//  }
//
//  Serial.println(F("#########################################################################################################################################################################################################################"));
//  Serial.println(cabecalho1);
//  Serial.println(cabecalho2);
//}
// Escrita Cartão SD
//void SD_write()
//{
//  if (SD_flag == 1)
//  {
//    cartao_SD = SD.open("urutau.txt", FILE_WRITE);
//    cartao_SD.print(data_string);
//    cartao_SD.print("\n");
//    cartao_SD.close();
//  }
//}

//
//void SD_ERROR () {
//  while(true)
//  {
//    Serial.println("SD ERROR...");
//    delay(100);
//  }
//}
