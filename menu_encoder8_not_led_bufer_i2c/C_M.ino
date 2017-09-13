void start_recipe(struct program &prg)  {

  if (prg.Start && !prg.IsRun){

      prg.IsRun = 1; 
      
      prg.start();
      
      prg.IsRun = 0; 
      prg.Start = 0;
      prg.Stop = 1;
  }

}
    
