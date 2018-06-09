  #include "mbed.h"
  #include "ms5611.h" 
 
  ms5611 ms(D14, D15);                        // i2c pins used
  //ms5611 ms(p9, p10, ms5611::CSBpin_0);      // NEW!! with rev 7. User can set polarity of CSB pin
  //ms5611 ms(p9, p10, ms5611::CSBpin_1);
 
  Serial pc(USBTX, USBRX);                   // local terminal interface
 
 
  int main (void) {
      pc.baud(9600);                        // set up USB serial speed
 
      // set up the ms5611
      pc.printf("\n\nInitializing the MS5611..\n");
      ms.cmd_reset();
      pc.printf("Ready\n");
 
      while(1) {
          double Temp = ms.calcTemp();                         //calculate press and temp, then returns current temperature in degC
          double Press = ms.calcPressure();                    //calculate press and temp, then returns current pressure in mb
          double GetPress = ms.getPressure();                  //returns current pressure in mb. Does no calculations.  Ususally done after calcTemp()
          double Altitude = ms.getAltitudeFT(1013.25);         //enter pressure at sea level in mb, returns altitude in feet
          double PressSeaLvlFT = ms.getSeaLevelBaroFT(327.2);  //enter known altitude in feet, returns sea level pressure in mb
          double PressSeaLvlM = ms.getAltitudeFT(99.73);       //enter known altitude in meters, returns seal level pressure in mb
 
          pc.printf("Temp: %.2f degC\n", Temp);    
          pc.printf("Barometer: %.1f mB  %.3f in/Hg\n", Press, Press * 0.0295301);
          pc.printf("Alt: %.1f ft\n", Altitude);
          pc.printf("Sea_Lvl: %.1f ft   %.2f m\n", PressSeaLvlFT, PressSeaLvlM);
          wait(2.0);
      }
  }