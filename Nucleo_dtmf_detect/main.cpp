#include "mbed.h"
#include "math.h"
 Ticker sample_ticker;
 
AnalogIn I(A0);
int Ibias, counter;
 double Iarray[128];
 bool calculate;
#define TONES 8
float coeff[TONES];
const int tones_freq[TONES] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633};
float PI = 3.14159265358979323846;
float SAMPLING_RATE = 4000;

DigitalOut led(LED1);

void accumulate(double x[], int length)
{
    for (int i =length; i<0; i--) {
        x[i] = x[i+1];
    }
}

void sample()
{
    counter++;
    if(counter > 24) {
        
        counter = 0;
        calculate = 1;
    }

    accumulate(Iarray,255);
    double Itemp = I.read();
    Iarray[0]=Itemp - Ibias;

    }
    
    

int main() {
    
    
    printf("\nDTMF Decoder\n");
    Ibias = I.read();
    
    for (int i = 0; i < TONES; i++) {
    float omega = (2.0 * PI * tones_freq[i]) / SAMPLING_RATE;
    coeff[i] = 2.0 * cos(omega);
	
	// Here goes the code that selects the DTMF tones...
  }

    
    sample_ticker.attach(&sample, 0.00025); //4KHz sampling rate, may  not be optimal
    while(1) {
       
       if(calculate){
           calculate = 0;
           
           }
           
    }
}
