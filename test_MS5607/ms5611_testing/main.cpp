
/** Software routines to access the Measurement Specialties' MS5611-01BA03 
 *  Variometer Module using the I2C bus option.  The MS5611 is a 24 bit 
 *  temperature and pressure transducer for high accuracy Barometer and 
 *  Altimeter applications.  It also includes compensation coefficients
 *  stored within the device. 
 * 
 *  Code adapted from Measurement Specialties:
 *  "AN520 C-code example for MS56xx, MS57xx (except analog sensor), and 
 *  MS58xx series pressure sensors"
 *
 *  Note: AN520 has not been updated for use with the MS5611.  Changes
 *  were necessary to "calcPT()" in order to correct scaling of 
 *  pressure readings.
 * 
 *  Features:
 *          Altitude resolution to 10cm
 *          Fast conversion down to 1 ms
 *          Low power, 1 μA (standby < 0.15 μA)
 *          QFN package 5.0 x 3.0 x 1.0 mm^3
 *          Supply voltage 1.8 to 3.6 V
 *          Integrated digital pressure sensor (24 bit DeltaSigma ADC)
 *          Operating range: 10 to 1200 mbar, -40 to +85 °C
 *          I2C and SPI interface up to 20 MHz
 *          No external components (Internal oscillator)
 *          Excellent long term stability
 *
 * @code */
  #include "mbed.h"
  #include "ms5611.h" 
 
  //ms5611 ms(p9, p10);                        // i2c pins used
  ms5611 ms(D14, D15, ms5611::CSBpin_0);      // NEW!! with rev 7. User can set polarity of CSB pin
  //ms5611 ms(p9, p10, ms5611::CSBpin_1);
 
  Serial pc(USBTX, USBRX);                   // local terminal interface
 
 
  int main (void) {
      pc.baud(9600);                        // set up USB serial speed
 
      // set up the ms5611
      pc.printf("\n\nInitializing the MS5611..\n");
      ms.cmd_reset();
      pc.printf("Ready\n");
 
      while(1) {
         // double Temp = ms.calcTemp();                         //calculate press and temp, then returns current temperature in degC
        //  double Press = ms.calcPressure();                    //calculate press and temp, then returns current pressure in mb
       //   double GetPress = ms.getPressure();                  //returns current pressure in mb. Does no calculations.  Ususally done after calcTemp()
       //   double Altitude = ms.getAltitudeFT(1013.25);         //enter pressure at sea level in mb, returns altitude in feet
       //   double PressSeaLvlFT = ms.getSeaLevelBaroM(327.2);  //enter known altitude in feet, returns sea level pressure in mb
        //  double PressSeaLvlM = ms.getAltitudeFT(99.73);       //enter known altitude in meters, returns seal level pressure in mb
 
          pc.printf("Temp: %.2f degC\n", ms.calcTemp());    
          pc.printf("Barometer: %.1f mB \n", ms.calcPressure());
         // pc.printf("Alt: %.1f ft\n", Altitude);
          //pc.printf("Sea_Lvl: %.1f ft   %.2f m\n", PressSeaLvlFT, PressSeaLvlM);
          pc.printf("\n\n\n\n");
          wait(2.0);
      }
  }
 
 