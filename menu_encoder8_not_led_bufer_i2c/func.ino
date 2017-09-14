void encoder(){
  int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){                                    //  Если энкодер зафиксировал поворот, то ...
        i=i+a;   /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).
                    //  Выводим значение переменной i
    } 
}

float updateDS(byte Pin){ // добавляем функцию read
       
  //       int iPin = Pin;
  //     data=analogRead(pin);  // считываем показания датчика в переменную data
  sensors.requestTemperatures(); // Send the command to get temperatures
  return (sensors.getTempCByIndex(Pin));  

 } 

void write_value_analog(int addres)
{
  digitalWrite(13, HIGH);
  unsigned int memEncoder_position = i; //запоминаем значение энкодера
  unsigned int x;//вводим новую переменную
  //i = EEPROM.read(addres);
  i = EEPROM_uint_read(addres);
       
  
  while(!Btn)
  {
    x = i;
    unsigned int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){i=i+a;}                     //  Если энкодер зафиксировал поворот, то ...
       /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).
   unsigned int s;
   if (s!=x){  display.clear(); s=x;}
  //  display.clearDisplay();
    display.setCursor(0,0);
    
    //EEPROM.update(addres, x);
    EEPROM_uint_write(addres, x);
    display.println(x);
 //   display.display();
    
  }//while
  
  i=memEncoder_position; //возвращаем значение энкодера в исходное значение

  digitalWrite(13, LOW);

}

unsigned int EEPROM_uint_read(int addr) {    
  byte raw[2];
  for(byte i = 0; i < 2; i++) raw[i] = EEPROM.read(addr+i);
  unsigned int &num = (unsigned int&)raw;
  return num;
}

void EEPROM_uint_write(int addr, unsigned int num) {
  byte raw[2];
  (unsigned int&)raw = num;
  for(byte i = 0; i < 2; i++) EEPROM.update(addr+i, raw[i]);
}
