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
//#define Btn  attachInterrupt(0, blink, RISING);

bool step_ch1 = 0;
bool step_ch2 = 0;
bool step_ch3 = 0;
bool step_ch4 = 0;

unsigned long startTime_ch;
unsigned long stopTime_ch;

const String str[5] = {" ", "PH", "GREEN", "BLACK", "RED"};

struct Parametr
{
  float PV;
  byte Pin;
  byte EEPROM_ADR;
  byte V;
  byte K;
};

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
  channel ch1;
  channel ch2;
  channel ch3;
  channel ch4;
  bool Start;
  bool Stop;
  bool IsRun;
  String RCP_Name;

  void start(){
    ch1.start();
    ch2.start();
    ch3.start();
    ch4.start();
    };
};



#define count_device  3 //количество устройств
//add r[count_device]; //создаём массив этих устройств 
program prg1, prg2, prg3;
program prg[count_device] = {prg1, prg2, prg3};


String inString;

void setup() {
  enc.begin(); 
  display.begin(&Adafruit128x64, OLED_CS, OLED_DC, OLED_CLK, OLED_DATA, OLED_RESET);
  display.setFont(Adafruit5x7);

  eeprom_str_adr(); 
  initialization();
  
  Serial.begin(9600);
  Serial.println("RCP Connection manager:");
  //Serial.println("Choise Recipe:");
  for (byte y=0; y <= count_device-1; y++){
  Serial.print(y);
  Serial.print(": ");
  Serial.println(prg[y].RCP_Name); 
  Serial.print(prg[y].ch1.ch_name);
  Serial.print(": ");  
  Serial.print(EEPROM.read(prg[y].ch1.V));
  Serial.println("ml");
  Serial.print(prg[y].ch2.ch_name);
  Serial.print(": "); 
  Serial.print(EEPROM.read(prg[y].ch2.V));
  Serial.println("ml");
  Serial.print(prg[y].ch3.ch_name);
  Serial.print(": ");  
  Serial.print(EEPROM.read(prg[y].ch3.V));
  Serial.println("ml");
  Serial.print(prg[y].ch4.ch_name);
  Serial.print(": "); 
  Serial.print(EEPROM.read(prg[y].ch4.V));
  Serial.println("ml");
  Serial.println(); 
 
 
 prg[0].ch1.K = 10;
  prg[0].ch1.V = 12;
  prg[0].ch1.Pin = 14;
  prg[0].ch1.ch_name = str[1];
  
   }

//  Serial.print("1:");
//  Serial.println(prg[0].RCP_Name);  
//  Serial.print("2:");
//  Serial.println(prg[1].RCP_Name);  
//  Serial.print("3:");
//  Serial.println(prg[2].RCP_Name);  

  

//  for(byte n = 0; n < count_device; n++) {
//    CM(n);
//    structures(n);
//    }  

  pinMode(buttonPin, INPUT); 
   display.clear();

}

void loop() {

if (Serial.available() > 0) {
    int inByte = Serial.read();

 
    switch (inByte) {
    case 'a':    
      prg[0].start();
      break;
    case 'b':    
      prg[1].start();
      break;
    case 'c':    
      prg[2].start();
      break;
    case 't':    
      Serial.println(updateDS(0));
      break;
    case '?':    
      Serial.println("help:");
      Serial.println("a: CHERENKI");
      Serial.println("b: VEGA");
      Serial.println("c: CVETENIE");
      Serial.println("t: temp");
      
      
      
      
      break;
      
      
      
      
    case 13:
      break;
    case 10:
      break;


      

    default:

     Serial.println("Error:Unknown command");
    }

    
      
   
   
//   //Serial.flush();
//   //switch(action){
//     if (action[0] == "1"){
//            Serial.print("You choise recipe: ");
//            Serial.println(action);
//            prg[0].start();
//            Serial.print("Batch is OK");
//     }
//     if (action[0] == "2"){
//            prg[1].start();
//            Serial.print("Batch is OK");
//     }
//     if (action == "3"){
//            prg[2].start();
//            Serial.print("Batch is OK");
//     }
//            
//     else {
//            Serial.println("Error:Unknown command");
//            
//   }
}
  //for(byte n = 0; n < count_device; n++) {
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
  
  if (i >= count_device){i=0;}
  if (i < 0){i= count_device - 1;}   
  
  if (!Btn){
    delay(500);
    
    screen_recipe((*_prg));
    //delay(500);
    }

}//loop


