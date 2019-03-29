
#include "arduinoFFT.h"
arduinoFFT FFT = arduinoFFT();

const uint16_t samplesE = 256; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 10000; //Hz, must be less than 10000 due to ADC

//unsigned int sampling_period_us=round(1000000*(1.0/samplingFrequency));
unsigned long microseconds;

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samplesE];
double vReal_avg[samplesE];
double vImag[samplesE];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void mus_arduinoFFT()
{
	unsigned int sampling_period_us=effSpeed;
  double samplingFrequency =effLength*32;
  float avg_k=map(effFade,0,256,0,25)/256.;

  for(int i=0; i<samplesE; i++)
  {
      microseconds = micros();    //Overflows after around 70 minutes!

      vReal[i] = analogRead(sound_p);
      vImag[i] = 0;
      while(micros() < (microseconds + sampling_period_us)){
        //empty loop
      }
  }
												//yield();
  FFT.Windowing(vReal, samplesE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(vReal, vImag, samplesE, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samplesE); /* Compute magnitudes */
  double x = FFT.MajorPeak(vReal, samplesE, samplingFrequency);
  
  for (uint16_t i = 0; i < samplesE; i++)
  {
    if(indexOrBits<64)
	  	leds[i*(NUM_LEDS-1)/samplesE]=CHSV(vReal[i],255,255);
    else if(indexOrBits<128)
    {
      vReal_avg[i]=vReal_avg[i]*(1-avg_k)+vReal[i]*avg_k;
      leds[i*(NUM_LEDS-1)/samplesE]=CHSV(vReal_avg[i],255,255);
    }
    else
    {
      vReal_avg[i]=vReal_avg[i]*(1-avg_k)+vReal[i]*avg_k;

      leds[i*(NUM_LEDS-1)/samplesE]=CHSV(128+(vReal_avg[i]-vReal[i])*(effLengthH/10.),255,255);
    }
  }
  leds[0]=CHSV((int)x%256,255,255);
}


