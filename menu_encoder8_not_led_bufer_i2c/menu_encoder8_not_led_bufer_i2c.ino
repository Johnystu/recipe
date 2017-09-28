#include <EEPROM.h>
#include <iarduino_Encoder_tmr.h>             //  Подключаем библиотеку iarduino_Encoder_tmr для работы с энкодерами через аппаратный таймер
iarduino_Encoder_tmr enc(5,6);   
int    i = 0;  
int _i = 0;
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

#define I2C_ADDRESS 0x3C
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

SSD1306AsciiAvrI2c display;


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
  
 // unsigned int _K = EEPROM_uint_read(K);
 // byte _V = EEPROM.read(V);
  //byte _Pin = EEPROM.read(Pin);


  void start(){
    unsigned int _K = EEPROM_uint_read(K); 
    byte _V = EEPROM.read(V);
    byte _Pin = EEPROM.read(Pin);
    
    startTime = millis();
    stopTime = startTime + (_V * _K);
 
    display.clear();
    display.setCursor(0,0);
  
    display.print("Ch "); 
    display.println(ch_name);

    display.print("V = ");
    display.println(_V);

    display.print("Pin = ");
    display.println(_Pin);
    
    display.print("IsRun = ");
    display.println(IsRun);



    Serial.print("Dosing: ");    
    Serial.println(ch_name);

    
    while(1){
  
      digitalWrite(_Pin, HIGH);
      display.setCursor(0,10);
      display.print(_V-((stopTime - millis())/_K));
      if (millis() > stopTime) {
        digitalWrite(_Pin, LOW); 
        Serial.print(ch_name);
        Serial.println(" Ready");
        IsRun = 0;
        break;
      }
      
      }
    };
    
  void correction(){
    unsigned int _K = EEPROM_uint_read(K); 
    byte _V = EEPROM.read(V);
    byte _Pin = EEPROM.read(Pin);
    
    digitalWrite(_Pin, HIGH);   
    startTime = millis();
  
 
    display.clear();
    display.setCursor(0,0);
  
    display.print("Ch "); 
    display.println(ch_name);

    display.println("10ml adjustment");
    display.println("Push Btn to stop");
    display.println("and fix value K");
    display.print("Now K=");    
    display.println(_K);    
    
 //   display.println(_V);

    display.print("Pin = ");
    display.println(_Pin);
  
    while(1){
      //display.clear();
      if (!Btn){
        stopTime = millis();
        digitalWrite(_Pin, LOW);
//        display.clear();
        _K = (stopTime - startTime)/10;
        EEPROM_uint_write(K, _K); // 10 это колибровка насоса по 10милиграмам(измеряемый объем)
 //       display.println(_K);
 //       display.println(EEPROM_uint_read(K));
        
        delay(5000);
        display.clear();
        break;
              }
  
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
    for (byte x=0; x<= count_channel-1; x++){
      ch[x].IsRun = 1;
      ch[x].startTime = millis();
      
     // ch[x].stopTime = ch[x].startTime + (ch[x]._V * ch[x]._K);
      ch[x].start();
    }

  };
  
  void stop(){

    for (byte x=0; x<= count_channel-1; x++){
      ch[x].IsRun = 0;
    }
    IsRun = false; 
    Start = false; 
  }
};
program prg[count_recipe];// создали объекты рецептов


void setup() {
  enc.begin(); 

  display.begin(&Adafruit128x64, I2C_ADDRESS);
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
  
  
  for (byte y=0; y <= count_recipe-1; y++){
    for (byte x=0; x<= count_channel-1; x++){
      pinMode(EEPROM.read(prg[y].ch[x].Pin), OUTPUT);
    }
  }
  
  display.clear();
}

void loop() {

serial();

  display.setCursor(0,0);
  display.println("PRESS BTN");

  program *_prg = &prg[i];
  display.print(i); 
  display.print(" ");
  display.println((*_prg).RCP_Name);
 
   for (byte x=0; x<= count_channel-1; x++){
    display.print((*_prg).ch[x].ch_name);
    display.print("= ");
    display.println(EEPROM.read((*_prg).ch[x].V));

   }
   for (byte y=0; y <= count_recipe-1; y++){
     program *_prg = &prg[y];
     ControlRecipe(*_prg);  
   }
  display.setCursor(56,54);
  display.print("temp="); 
  display.println(updateDS(0));  
    
  encoder();
  
  if (_i != i) {display.clear(); _i=i;} 
  if (i > count_recipe-1){i=0;}
  if (i < 0){i= count_recipe - 1;}   
  
  if (!Btn){
    delay(500);
    
    screen_recipe((*_prg));
    //delay(500);
    }

}//loop


