#include "mbed.h"
#include "DHT.h"
#include "ms5611.h"
#include "WakeUp.h"

Serial pc(USBTX, USBRX); // serieport USB
DigitalOut myled(LED1); // lysdiode
Serial wlan(D8,D2);     // Seriedata WLAN.

ms5611 ms(D14, D15, ms5611::CSBpin_0); // initialiserer trykk og temp sensor.
DHT sensor(D7,AM2302); // initialiserer tempratur og humiditet sensor.

int delayms = 5500000; // tiden vi er i sleep i ms.

int main()
{
    int err;
    wait(5); // vent 5 sek.
    pc.printf("\r\nDHT Test program");
    pc.printf("\r\n******************\r\n");
    wlan.printf("AT+CWMODE=3\r\n");
    wlan.printf("AT+CWJAP=\"NETGEAR49\",\"wateryplanet286\"\r\n");
    wait(5); // vent 5 sek så vi får koblet til nettverket og får IP adresse
    WakeUp::calibrate(); // kalibrer RTC så timer interrupt starter.

    ms.cmd_reset(); // start trykksensor.

    while (1) {
        myled = 1;
        err = sensor.readData();
        if (err == 0) { 
            pc.printf("\nTemperature is %4.1f C \r\n",sensor.ReadTemperature(CELCIUS));
            pc.printf("Humidity is %4.1f \r\n",sensor.ReadHumidity());
            pc.printf("Temp: %.2f degC\n", ms.calcTemp());
            pc.printf("Barometer: %.1f mB \n", ms.calcPressure());
            wlan.printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\", 80\r\n");
            pc.printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\", 80\r\n");
            wait(3); // må vente på DNS her, tar noen ganger ca 2 sek.
            wlan.printf("GET /update?key=*notpublishingprivatekey*&field1=%4.1f&field2=%4.1f&field3=%4.1f\r\n",sensor.ReadTemperature(CELCIUS),sensor.ReadHumidity(),ms.calcPressure());
            pc.printf("GET /update?key=*notpublishingprivatekey*&field1=%4.1f&field2=%4.1f&field3=%4.1f\r\n",sensor.ReadTemperature(CELCIUS),sensor.ReadHumidity(),ms.calcPressure());
            wait(2); // overfører sensordata til thingverse.
            
            while(wlan.readable()) {
                pc.putc(wlan.getc());
                myled = 0;
            }
            
            WakeUp::set_ms(delayms); 
            sleep();
            

        } else {
            pc.printf("\r\nErr %i \n",err);
            WakeUp::set_ms(5000); 
            sleep(); // vent 5 sec før vi prøver i gjen.
        }
    }
}