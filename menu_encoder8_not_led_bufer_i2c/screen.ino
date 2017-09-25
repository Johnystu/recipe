void screen_recipe(struct program& prg){
  byte old_i = i; // для возврата в предыдущий рецепт
  i=0; //начало позиции меню
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
      
    display.setCursor(0,0);
 
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

      start_recipe(prg);

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
    if ((!Btn && i == 0) || (millis()-  prevTime>10000)){  display.clear();  i=old_i; break;}


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
      
    display.setCursor(0,0);

    if (i == -1){i=4;}

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
 
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      display.clear(); 
      }
      
    display.setCursor(0,0);


    if (i == -1){i=3;}


    display.println(ch.ch_name);
    display.println();

    if (i == 1) {display.print("=>");}
    display.print("K=");
    display.print(EEPROM_uint_read(ch.K));
    display.println("mSec");    
  
    if (i == 2) {display.print("=>");}
    display.print("V=");
    display.print(EEPROM.read(ch.V));
    display.println(" ml");

    
    if (i == 3) {display.print("=>");}
    display.print("Pin=");
    display.println(EEPROM.read(ch.Pin));

    if (i == 4) {display.print("=>");}
    display.print("Run test: ");
    display.print(EEPROM.read(ch.V));
    display.println(" ml"); 
  
    display.println();  
    
    if (i == 0) {display.print("=>");}
    display.print("EXIT");
    display.println(i);
    if (i == 5){i=0;}
    
    //display.display();

   if (!Btn){
     switch (i){

       case 1:{delay(500); ch.correction(); break;}
       case 2:{write_value_analog(ch.V); break;}
       case 3:{write_value_analog(ch.Pin); break;}
       case 4:{ch.start(); break;}
    
     }//switch
  prevTime=millis(); 
 }

    if ((!Btn && i == 0) || (millis()-  prevTime>10000)){ delay(500); break;}

  }//while
} //screen





