void eeprom_str_adr()
{
   
  prg1.ch1.K = 10;
  prg1.ch1.V = 12;
  prg1.ch1.Pin = 14;
  prg1.ch1.ch_name ="  PH DOWN  ";
  
  prg1.ch2.K = 16;
  prg1.ch2.V = 18;
  prg1.ch2.Pin = 20;
  prg1.ch2.ch_name ="  GREEN  ";
  
  prg1.ch3.K = 22;
  prg1.ch3.V = 24;
  prg1.ch3.Pin = 26;
  prg1.ch3.ch_name ="  BLACK  ";
  
  prg1.ch4.K = 28;
  prg1.ch4.V = 30;
  prg1.ch4.Pin = 31;
  prg1.ch4.ch_name ="  RED  ";
  
  prg1.Start = false;
  prg1.Stop = true;
  prg1.RCP_Name = "5 10 15";
     
}

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
