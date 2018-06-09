#include "mbed.h"
#include "constants.h"

Ticker sample_ticker;

DigitalOut led1(LED1);
int counter;
AnalogIn I(A0);
AnalogIn Q(A1);
AnalogOut out(PA_4);
double Iarray[256];
double Qarray[256];
double AFarray[256];
int Ibias, Qbias;


void accumulate(double x[], int length)
{
    for (int i =length; i<0; i--) {
        x[i] = x[i+1];
    }
}


double firfilter(double w[], double x[], int LEN)
{
    float y=0.0; //will contain your result
    for (int i=0; i<LEN; i++) {
        y = y + w[i]*x[i];
    }
    return y;
}

void sample()
{
    counter++;
    if(counter > 600) {
        led1 = !led1;
        counter = 0;
    }

    accumulate(Iarray,255);
    accumulate(Qarray,255);
    double Itemp = I.read();
    double Qtemp = Q.read();

    Iarray[0]=atan(Itemp - Ibias);
    Qarray[0]=atan(Qtemp - Qbias);


    accumulate(AFarray,255);

    AFarray[0]= ((Qarray[0]*Iarray[1])-(Iarray[0]*Qarray[1]))/((Iarray[0]*Iarray[0])-(Qarray[0]*Qarray[0]));
    double out_value = 0;
    out_value = firfilter(FIR_BPF, AFarray, 256);

    out.write(out_value);



}

int main()
{
     Ibias = I.read();
    Qbias = Q.read();
    // Init the ticker with the address of the function (sample) to be attached and the interval (100 ms)
    sample_ticker.attach(&sample, 0.000125); //8KHz sampling rate, may  not be optimal, could be needing 24KHz or so?

    while (true) {
        // Do other things...
    }
}




