void eeprom_str_adr()
{
  int eeprom_number = 10;
  for (byte y=0; y <= count_recipe-1; y++){
    
    prg[y].RCP_Name = recipe_name[y];
 
    for (byte x=0; x<= count_channel-1; x++){
      
      prg[y].ch[x].K = eeprom_number;
      eeprom_number = eeprom_number + 2;
      
      prg[y].ch[x].V = eeprom_number;
      eeprom_number = eeprom_number + 2;
      
      prg[y].ch[x].Pin = eeprom_number;
      eeprom_number = eeprom_number + 2;
      
      prg[y].ch[x].ch_name = channel_name[x];
      

      }

   } 
 
 
 
  
//  prg[0].ch[0].K = 10;
//  prg[0].ch[0].V = 12;
//  prg[0].ch[0].Pin = 14;
//  prg[0].ch[0].ch_name = str[0];
//  
//  prg[0].ch[1].K = 16;
//  prg[0].ch[1].V = 18;
//  prg[0].ch[1].Pin = 20;
//  prg[0].ch[1].ch_name = str[1];
//  
//  prg[0].ch[2].K = 22;
//  prg[0].ch[2].V = 24;
//  prg[0].ch[2].Pin = 26;
//  prg[0].ch[2].ch_name = str[2];
//  
//  prg[0].ch[3].K = 28;
//  prg[0].ch[3].V = 30;
//  prg[0].ch[3].Pin = 32;
//  prg[0].ch[3].ch_name = str[3];
//  
//  prg[0].RCP_Name = "RCP 1";
//     
//     
//  prg[1].ch[0].K = 34;
//  prg[1].ch[0].V = 36;
//  prg[1].ch[0].Pin = 38;
//  prg[1].ch[0].ch_name = str[0];
//  
//  prg[1].ch[1].K = 40;
//  prg[1].ch[1].V = 42;
//  prg[1].ch[1].Pin = 44;
//  prg[1].ch[1].ch_name = str[1];
//  
//  prg[1].ch[2].K = 46;
//  prg[1].ch[2].V = 48;
//  prg[1].ch[2].Pin = 50;
//  prg[1].ch[2].ch_name = str[2];
//  
//  prg[1].ch[3].K = 52;
//  prg[1].ch[3].V = 54;
//  prg[1].ch[3].Pin = 56;
//  prg[1].ch[3].ch_name = str[3];
//  
//  prg[1].RCP_Name = "recipe 2";   
// 
//  prg[2].ch[0].K = 58;
//  prg[2].ch[0].V = 60;
//  prg[2].ch[0].Pin = 62;
//  prg[2].ch[0].ch_name = str[0];
//  
//  prg[2].ch[1].K = 64;
//  prg[2].ch[1].V = 66;
//  prg[2].ch[1].Pin = 68;
//  prg[2].ch[1].ch_name = str[1];
//  
//  prg[2].ch[2].K = 70;
//  prg[2].ch[2].V = 72;
//  prg[2].ch[2].Pin = 74;
//  prg[2].ch[2].ch_name = str[2];
//  
//  prg[2].ch[3].K = 76;
//  prg[2].ch[3].V = 78;
//  prg[2].ch[3].Pin = 80;
//  prg[2].ch[3].ch_name = str[3];
//  
//  prg[2].RCP_Name = "recipe 3";
     
}
void initialization()
{
  prg[1].Start = false;
  prg[1].Stop = true;
  prg[1].IsRun = false;

};
//void structures(byte n) //разложить байт на биты
//{
//
//  byte r_byte; //байт для записи значения из eeproom
//  r_byte = EEPROM.read(r[n].PAR.EEPROM_ADR); //запихнули сюда прочитанный байт из eeproom
//  r[n].CS.MODE = bitRead(r_byte, 1); //читаем первый бит
//  r[n].CS.CONTROL = bitRead(r_byte, 2);  //читаем второй бит
//  r[n].CS.INTERLOCK = bitRead(r_byte, 3);  //
//
//}
