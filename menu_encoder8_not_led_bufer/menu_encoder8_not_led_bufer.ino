#include <EEPROM.h>
#include <iarduino_Encoder_tmr.h>             //  Подключаем библиотеку iarduino_Encoder_tmr для работы с энкодерами через аппаратный таймер
iarduino_Encoder_tmr enc(5,6);   
int    i = 0;  

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
unsigned long startTime;
unsigned long stopTime;

struct ControlSignal
{
  bool MODE; //0 == auto 1 == manual
  bool CONTROL; //start stop
  bool INTERLOCK;
};

struct Status 
{
  bool inAuto;
  bool isRun;
  bool isLock;
  
 // bool V;
 // bool K;
};

struct Parametr
{
  float PV;
  byte Pin;
  byte EEPROM_ADR;
  byte V;
  byte K;
};

struct add
{
  ControlSignal CS;     //вкладываем одну структуру в определение второй
  Status STS;
  Parametr PAR;
  String name;
};
struct channel
{
  byte K; 
  byte V;
  byte Pin;
  String ch_name;
};
struct program
{
channel ch1;
channel ch2;
channel ch3;
channel ch4;
bool Start;
bool Stop;
String RCP_Name;
};

//void screen(byte id);
//void write_value(byte id, int n_bit);

#define count_device  3 //количество устройств
//add r[count_device]; //создаём массив этих устройств 
program prg1;
void setup() {
  enc.begin(); 
  display.begin(&Adafruit128x64, OLED_CS, OLED_DC, OLED_CLK, OLED_DATA, OLED_RESET);
  display.setFont(Adafruit5x7);

  eeprom_str_adr(); 

//  for(byte n = 0; n < count_device; n++) {
//    CM(n);
//    structures(n);
//    }  

  pinMode(buttonPin, INPUT); 
  for(byte n = 0; n < 10; n++) {
  display.clear();
  display.setCursor(0,0);
//  display.setTextColor(WHITE);

 // display.setTextSize(n);

  display.println("green garden");

 // display.display();

  }

}

void loop() {


  //for(byte n = 0; n < count_device; n++) {
 //   CM(n);
//    structures(n);
 //   }
//  display.clearDisplay();
  display.setCursor(0,0);
//  display.setTextSize(1);
 // display.setTextColor(WHITE);
  display.println("PRESS BTN");
  display.println();
  

  display.println(i);

  display.setCursor(56,9);
  display.print("STS.inAuto=");
 // display.println(r[i].STS.inAuto);
  display.setCursor(56,18);
  display.print("STS.isRun=");
 // display.println(r[i].STS.isRun); 
  display.setCursor(56,27);
  display.print("PAR.PV");
//  display.println(r[i].PAR.PV);
 display.println(startTime);
 display.println(stopTime);
//  display.println(r[i].STS.K);
  
  display.setCursor(56,56);
  display.print("temp="); 
  display.println(updateDS(0));  
 // display.display();
    
  encoder();
  
 // if (i >= count_device){i=0;}
 // if (i < 0){i= count_device - 1;}   
  
  if (!Btn){
    delay(500);
    screen_recipe(prg1);
    //delay(500);
    }

}//loop


