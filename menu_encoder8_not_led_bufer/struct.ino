void eeprom_str_adr()
{
   
  prg[0].ch1.K = 10;
  prg[0].ch1.V = 12;
  prg[0].ch1.Pin = 14;
  prg[0].ch1.ch_name = str[1];
  
  prg[0].ch2.K = 16;
  prg[0].ch2.V = 18;
  prg[0].ch2.Pin = 20;
  prg[0].ch2.ch_name = str[2];
  
  prg[0].ch3.K = 22;
  prg[0].ch3.V = 24;
  prg[0].ch3.Pin = 26;
  prg[0].ch3.ch_name = str[3];
  
  prg[0].ch4.K = 28;
  prg[0].ch4.V = 30;
  prg[0].ch4.Pin = 32;
  prg[0].ch4.ch_name = str[4];
  
  prg[0].RCP_Name = "RCP 1";
     
     
  prg[1].ch1.K = 34;
  prg[1].ch1.V = 36;
  prg[1].ch1.Pin = 38;
  prg[1].ch1.ch_name = str[1];
  
  prg[1].ch2.K = 40;
  prg[1].ch2.V = 42;
  prg[1].ch2.Pin = 44;
  prg[1].ch2.ch_name = str[2];
  
  prg[1].ch3.K = 46;
  prg[1].ch3.V = 48;
  prg[1].ch3.Pin = 50;
  prg[1].ch3.ch_name = str[3];
  
  prg[1].ch4.K = 52;
  prg[1].ch4.V = 54;
  prg[1].ch4.Pin = 56;
  prg[1].ch4.ch_name = str[4];
  
  prg[1].RCP_Name = "recipe 2";   
 
  prg[2].ch1.K = 58;
  prg[2].ch1.V = 60;
  prg[2].ch1.Pin = 62;
  prg[2].ch1.ch_name = str[1];
  
  prg[2].ch2.K = 64;
  prg[2].ch2.V = 66;
  prg[2].ch2.Pin = 68;
  prg[2].ch2.ch_name = str[2];
  
  prg[2].ch3.K = 70;
  prg[2].ch3.V = 72;
  prg[2].ch3.Pin = 74;
  prg[2].ch3.ch_name = str[3];
  
  prg[2].ch4.K = 76;
  prg[2].ch4.V = 78;
  prg[2].ch4.Pin = 80;
  prg[2].ch4.ch_name = str[4];
  
  prg[2].RCP_Name = "recipe 3";
     
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
