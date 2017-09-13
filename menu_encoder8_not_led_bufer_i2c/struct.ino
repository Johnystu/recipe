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
