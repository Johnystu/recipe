void start_ch (byte V, byte K, byte Pin, const String &Name)
{
  startTime_ch = millis();
  stopTime_ch = startTime_ch + ((V / K) * 1000);
 
  display.clear();
  display.setCursor(0,0);
  display.print("Ch "); 
  display.println(Name);

// // display.println(startTime_ch);
// // display.println(stopTime_ch);
  display.print("V = ");
  display.println(V);
//  display.print("K = ");
//  display.println(K);
  display.print("Pin = ");
  display.println(Pin);
  byte line[20]={};
  while(1){

    digitalWrite(Pin, HIGH);

    display.setCursor(0,10);
    display.print((stopTime_ch - millis())/1000);
 //   display.
    if (millis() > stopTime_ch) {digitalWrite(Pin, LOW); break;}
    
  } 

}


void start_recipe(struct program &prg)  {

    if (prg.Start && !prg.IsRun){

      prg.IsRun = 1;  
//      start_ch(EEPROM.read(prg.ch1.V), EEPROM.read(prg.ch1.K), EEPROM.read(prg.ch1.Pin), str[1]); 
//      start_ch(EEPROM.read(prg.ch2.V), EEPROM.read(prg.ch2.K), EEPROM.read(prg.ch2.Pin), str[2]); 
//      start_ch(EEPROM.read(prg.ch3.V), EEPROM.read(prg.ch3.K), EEPROM.read(prg.ch3.Pin), str[3]); 
//      start_ch(EEPROM.read(prg.ch4.V), EEPROM.read(prg.ch4.K), EEPROM.read(prg.ch4.Pin), str[4]); 
      prg.start();
      prg.IsRun = 0; 
      prg.Start = 0;
      prg.Stop = 1;
    
    

  }

}
    
