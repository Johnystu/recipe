#include <EEPROM.h>
#include <iarduino_Encoder_tmr.h>             //  Подключаем библиотеку iarduino_Encoder_tmr для работы с энкодерами через аппаратный таймер
iarduino_Encoder_tmr enc(5,6);   
int    i = 0;  

#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//#include "DHT.h"
// If using software SPI (the default case):

//#define DHTPIN 2
//#define DHTTYPE DHT22
//DHT dht(DHTPIN, DHTTYPE);

//ds1820 temp
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
//float in_tempC;
//float out_tempC;
//--ds1820

#define OLED_DC   11
#define OLED_CS   12
#define OLED_CLK  10
#define OLED_DATA 9
#define OLED_RESET 8

#include "SSD1306Ascii.h"
#include "SSD1306AsciiSoftSpi.h"

SSD1306AsciiSoftSpi display;

#define buttonPin  2     // кнопка эенкодера
#define Btn digitalRead(buttonPin)

unsigned long startTime_ch;
unsigned long stopTime_ch;

#define count_channel  4 //количество каналов дозаторов
const String channel_name[count_channel] = {"PH", "GREEN", "BLACK", "RED"};

#define count_recipe  3 //количество рецептов
const String recipe_name[count_recipe] = {"Baby", "Vega", "Cvet"};

struct channel
{
  byte K; 
  byte V;
  byte Pin;
  String ch_name;
  bool IsRun;
  unsigned long startTime;
  unsigned long stopTime;
 
  void start(){
    byte _K = EEPROM.read(K); 
    byte _V = EEPROM.read(V);
    byte _Pin = EEPROM.read(Pin);
    
    startTime = millis();
    stopTime = startTime + ((_V / _K) * 1000);
 
    display.clear();
    display.setCursor(0,0);
  
    display.print("Ch "); 
    display.println(ch_name);

    display.print("V = ");
    display.println(_V);

    display.print("Pin = ");
    display.println(_Pin);
  
    while(1){
  
      digitalWrite(_Pin, HIGH);
      display.setCursor(0,10);
      display.print((stopTime - millis())/1000);
      if (millis() > stopTime) {digitalWrite(_Pin, LOW); break;}
      
      }
    };
};


struct program
{

  channel ch[count_channel];

  bool Start;
  bool Stop;
  bool IsRun;
  String RCP_Name;

  void start(){
    ch[0].start();
    ch[1].start();
    ch[2].start();
    ch[3].start();
    };
};

program prg[count_recipe];// 


void setup() {
  enc.begin(); 
  display.begin(&Adafruit128x64, OLED_CS, OLED_DC, OLED_CLK, OLED_DATA, OLED_RESET);
  display.setFont(Adafruit5x7);

  eeprom_str_adr(); 
  initialization();
  
  Serial.begin(9600);
  Serial.println("RCP Connection manager");
  Serial.println("Available recipes:");
  
  //Serial.println("Choise Recipe:");
  for (byte y=0; y <= count_recipe-1; y++){
    Serial.print(y);
    Serial.print(": ");
    Serial.println(prg[y].RCP_Name); 
    for (byte x=0; x<= count_channel-1; x++){

      Serial.print(prg[y].ch[x].ch_name);
      Serial.print(": ");  
      Serial.print(EEPROM.read(prg[y].ch[x].V));
      Serial.println("ml");
 
      }
     Serial.println();
   }


  pinMode(buttonPin, INPUT); 
   display.clear();

}

void loop() {

if (Serial.available() > 0) {
    int inByte = Serial.read();
    if ((inByte < (count_recipe + 48)) && (inByte >= 48)){ 
 
    
      Serial.print("Start ");
      Serial.println(prg[inByte-48].RCP_Name);      
      prg[inByte-48].start();
      Serial.print("Batch ");
      Serial.print(prg[inByte-48].RCP_Name);
      Serial.println(" is Done");     

    }
    else {
      
      switch (inByte) {
      case 't':    
        Serial.println(updateDS(0));
        break;
      case '?':    
        Serial.println("help:");
        Serial.println("0: CHERENKI");
        Serial.println("1: VEGA");
        Serial.println("2: CVETENIE");
        Serial.println("t: temp");
  
        break;
  
      case 13:
        break;
      case 10:
        break;


      

    default:
     Serial.print(inByte);

     
     Serial.println(": BAD command");
    }
    }


}
  //for(byte n = 0; n < count_recipe; n++) {
//    start_recipe(prg1);
//    structures(n);
 //   }
//  display.clearDisplay();
  display.setCursor(0,0);
//  display.setTextSize(1);
 // display.setTextColor(WHITE);
  display.println("PRESS BTN");
//  start_recipe(prg1);
  program *_prg = &prg[i];
  display.println((*_prg).RCP_Name);
  display.println(i); 

 // display.println(i);
//    display.write(i);
//  display.println(i);
  display.setCursor(56,9);
//  display.print("STS.inAuto=");
 // display.println(r[i].STS.inAuto);
  display.setCursor(56,18);
 // display.print("STS.isRun=");
 // display.println(r[i].STS.isRun); 
 display.setCursor(56,27);
  display.print("start = ");
     display.println(prg[i].Start);
     display.setCursor(56,36);
  display.print("stop = "); 
     display.println(prg[i].Stop);
     display.setCursor(56,45);
  display.write(i);
  display.setCursor(56,54);
  display.print("temp="); 
  display.println(updateDS(0));  
 // display.display();
    
  encoder();
  
  if (i >= count_recipe){i=0;}
  if (i < 0){i= count_recipe - 1;}   
  
  if (!Btn){
    delay(500);
    
    screen_recipe((*_prg));
    //delay(500);
    }

}//loop


