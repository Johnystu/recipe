void screen_recipe(struct program& prg){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
  display.clear(); 
  while(1){ 
 //   structures(id);
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
        display.clear(); 
      }
      
   // display.clearDisplay();
    display.setCursor(0,0);
   // display.setTextSize(1);

    if (i == -1){i=3;}

 //   display.setTextColor(WHITE);
    display.println(prg.RCP_Name);
    display.println();
    if (i == 1) {display.print("=>");}
//    else {display.setTextColor(WHITE);}
    display.println("START");
 
    
    if (i == 2) {display.print("=>");}
 //   else {display.setTextColor(WHITE);}
//    display.print("V=");
    display.println("RESET");
    //display.println(rele1.PAR.Pin);
    
    if (i == 3) {display.print("=>");}
  //  else {display.setTextColor(WHITE);}
//    display.print("Pin=");
    display.println("Settings");
 
    
    if (i == 0) {display.print("=>");}
//    else {display.setTextColor(WHITE);}
    display.println("EXIT");
    
    if (i == 4){i=0;}
      display.print(" "); 
 //    display.print(startTime);
  //   display.println(prg.Start);

//     display.println(prg.IsRun); 
//    display.print(" "); 
//     display.print(stopTime);    
 //    display.println(stopTime - millis())/1000;
      start_recipe(prg);
 //   display.display();
  // if ((!Btn && i == 0) || (millis()-  prevTime>10000)){  break;}
   if (!Btn){
     delay(500);
     switch (i){
       case 1:{prg.Start = true; prg.Stop = false; prevTime=millis(); break;}
       case 2:{prg.Stop = true; prg.Start = false; prevTime=millis(); break;}
       case 3:{screen_change_ch(prg);  display.clear();   prevTime=millis(); break;}
       //case 4:{screen_ch_setting(prg.ch4); prevTime=millis(); break;}       
 //      case 0:{break;}
      
   }
   
 }
    if ((!Btn && i == 0) || (millis()-  prevTime>10000)){  display.clear();  break;}


  }//while
} //screen

void screen_change_ch(struct program &prg){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
   display.clear(); 
  while(1){ 
 //   structures(id);
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      display.clear(); 
      }
      
 //   display.clearDisplay();
    display.setCursor(0,0);
   // display.setTextSize(1);

    if (i == -1){i=4;}

 //   display.setTextColor(WHITE);
    display.println(prg.RCP_Name);
    display.println();
    
    for (byte x=0; x<= count_channel-1; x++){
      if (i == x) {display.print("=>");}
      display.println(prg.ch[x].ch_name);
    }
    
    display.println();
 
    
    if (i == count_channel) {display.print("=>");}
      display.print("EXIT");
    
    if (i == count_channel + 1){i=0;}
    
    if (!Btn && i < count_channel){
       delay(500);
       screen_ch_setting(prg.ch[i]);
       display.clear();  
       prevTime=millis();
  
   }

    if ((!Btn && i == count_channel) || (millis()-  prevTime>10000)){delay(500); break;}


  }//while
} //screen

void screen_ch_setting(struct channel ch){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
 display.clear(); 
  while(1){ 
 //   structures(id);
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      display.clear(); 
      }
      
//    display.clearDisplay();
    display.setCursor(0,0);
 //   display.setTextSize(1);

    if (i == -1){i=3;}

    //if (i == 0) {display.setTextColor(BLACK,WHITE);}
 //  {display.setTextColor(WHITE);}
    display.println(ch.ch_name);
    display.println();

    if (i == 1) {display.print("=>");}
 //   else {display.setTextColor(WHITE);}
    display.print("K=");
    display.print(EEPROM_uint_read(ch.K));
    display.println("mSec");    
    if (i == 2) {display.print("=>");}
 //   else {display.setTextColor(WHITE);}
    display.print("V=");
    display.print(EEPROM.read(ch.V));
    display.println(" ml");
    //display.println(rele1.PAR.Pin);
    
    if (i == 3) {display.print("=>");}
 //   else {display.setTextColor(WHITE);}
    display.print("Pin=");
    display.println(EEPROM.read(ch.Pin));
    
    display.println();  
    
    if (i == 0) {display.print("=>");}
 //   else {display.setTextColor(WHITE);}
    display.print("EXIT");
    display.println(i);
    if (i == 4){i=0;}
    
    //display.display();

   if (!Btn){
     switch (i){
       //case 1:{write_value_analog(ch.K); prevTime=millis(); break;}
       case 1:{delay(500); ch.correction(); prevTime=millis(); break;}
       //case 2:{EEPROM_uint_write(ch.V, 0); prevTime=millis(); break;}     
       case 2:{write_value_analog(ch.V); prevTime=millis(); break;}
       case 3:{write_value_analog(ch.Pin);prevTime=millis(); break;}
      // case 0: break;
       //case 0:{break;}
      
   }//switch
   
 }


    if ((!Btn && i == 0) || (millis()-  prevTime>10000)){ delay(500); break;}


  }//while
} //screen




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




