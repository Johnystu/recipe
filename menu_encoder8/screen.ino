void screen(struct channel ch){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
 
  while(1){ 
 //   structures(id);
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      }
      
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);

    if (i == -1){i=3;}

    //if (i == 0) {display.setTextColor(BLACK,WHITE);}
   {display.setTextColor(WHITE);}
    display.println(ch.ch_name);
    
    if (i == 1) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("K=");
    display.println(EEPROM.read(ch.K));
    
    if (i == 2) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("V=");
    display.println(EEPROM.read(ch.V));
    //display.println(rele1.PAR.Pin);
    
    if (i == 3) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("Pin=");
    display.println(EEPROM.read(ch.Pin));
    
    if (i == 0) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("EXIT");
    
    if (i == 4){i=0;}
    
    display.display();

   if (!Btn){
     switch (i){
       case 1:{write_value_analog(ch.K); prevTime=millis(); break;}
       case 2:{write_value_analog(ch.V); prevTime=millis(); break;}
       case 3:{write_value_analog(ch.Pin);prevTime=millis(); break;}
 //      case 0:{break;}
      
   }
   
 }


 //   if (!Btn && (i == 1 || i == 2 || i == 3)){write_value(id, i); prevTime=millis();}
 //   if (!Btn && (i == 1 || i == 2 || i == 3)){write_value_analog(ch, i); prevTime=millis();}
    if ((!Btn && i == 0) || (millis()-  prevTime>10000)){ break;}


  }//while
} //screen

void write_value_analog(byte addres)
{
  digitalWrite(13, HIGH);
  int memEncoder_position = i; //запоминаем значение энкодера
  byte x;//вводим новую переменную
  i = EEPROM.read(addres);
 
       
  
  while(!Btn)
  {
    x = i;
    int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){i=i+a;}                     //  Если энкодер зафиксировал поворот, то ...
       /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).

    display.clearDisplay();
    display.setCursor(0,0);
    
    EEPROM.update(addres, x);
   
    display.println(x);
    display.display();
    
  }//while
  
  i=memEncoder_position; //возвращаем значение энкодера в исходное значение

  digitalWrite(13, LOW);

}




