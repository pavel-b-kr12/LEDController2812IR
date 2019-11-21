//TODO 

#include "arduinoFFT.h"
arduinoFFT FFT = arduinoFFT();

const uint16_t samplesE = 64; // >NUM_LEDS nw with this code   //This value MUST ALWAYS be a power of 2
double samplingFrequency = 3000; //Hz, must be less than 10000 due to ADC

//unsigned int sampling_period_us=round(1000000*(1.0/samplingFrequency));
//unsigned long microseconds;

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samplesE];
double vImag[samplesE];

double vImag_avg[samplesE/2];
double vReal_avg[samplesE/2];
double vReal_avg_m[samplesE/2];
double vReal_avg_slow[samplesE/2];


#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

float vol_avg=0;
float vol_m=80;
float vol_M=90;

/*
effSpeed - avgE
effFade - avg_k
effSpeedH - (noise) sub
effLengthH - hue colorise mult

*/

		void setSegment(NUM_LEDS_type i, NUM_LEDS_type w, NUM_LEDS_type val)
		{
			if(val==255) val=0; //! del

			val%=256;
			for (int j = 0; j < w; ++j)
			{
				if(i*w+j>NUM_LEDS-1) continue; //!del

				byte b=val/8;
				if(val>(1+1.0*j/w*effLengthH))
				{
					b=255;
				}

				  leds[i*w+j]=CHSV(val,255,b);
				
			}
		}



void mus_arduinoFFT()
{
	//unsigned int sampling_period_us=effSpeed;
  //samplingFrequency = map(effSpeed,1,255,1000,6000); //not affect at all
  float avg_k=map(		effFade		,0,256,10,200)/1000.; // 0.05;		map(effFade,0,256,1,25)/256.
  float vol=0;

  byte avgE= map(		effSpeed		,0,255,10,40)*2;

  for(int i=0; i<samplesE; i++)
  {
      //microseconds = micros();    //Overflows after around 70 minutes!

      //vReal[i] = analogRead(sound_p) +analogRead(sound_p)+analogRead(sound_p);//+analogRead(sound_p);

  	vReal[i] = 0;
		
		for(int j=0; j<avgE; j++) //16 = 20ms @ ESP32 11bit // 16 = 5ms @ ESP32 10bit 
		{
			//vReal[i]+=analogRead(ADCp)/64;
			//vReal[i]+= adc1_get_raw(ADC1_CHANNEL_3);///8;
			vReal[i]+=analogRead(sound_p);
		}
		vReal[i]/=(avgE/2);

		//if(indexOrBits<32)		vReal[i]-=vol_avg; //not affect
		//vReal[i]-=effLength/2.;

      vImag[i] = 0;
      vol+=vReal[i];
      //while(micros() < (microseconds + sampling_period_us)){
        //empty loop
      //}

  }

  vol=vol/samplesE;
  if(vol_avg<1) vol_avg=vol;
  else vol_avg=vol_avg*(1-avg_k)+vol*avg_k;

  if(vol<vol_m) vol_m=vol;
  if(vol>vol_M) vol_M=vol;

												//yield();
  FFT.Windowing(vReal, samplesE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(vReal, vImag, samplesE, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samplesE); /* Compute magnitudes */
  double x = FFT.MajorPeak(vReal, samplesE, samplingFrequency);
  
  for (uint16_t i = 1; i < samplesE/3 && i<(NUM_LEDS-1)/3 ; i++)  //i>samplesE/2 is mirrored part
  {
   // leds[i]=CHSV(vImag[i],255,b);

    if(samplesE/3+i< NUM_LEDS-1)
    {
      vImag_avg[i]=vImag_avg[i]*(1-avg_k)+vImag[i]*avg_k;

      vReal_avg[i]=vReal_avg[i]*(1-avg_k)+vReal[i]*avg_k;

      if( vReal_avg_m[i]<0.01 || vReal_avg[i]< vReal_avg_m[i])      vReal_avg_m[i]=vReal_avg[i];  //min
      float vol_m_add_avg_k=map(		effLength		,0,256,10,200)/1000.;
      vReal_avg_m[i]=vReal_avg_m[i]*(1-vol_m_add_avg_k)+vReal_avg[i]*vol_m_add_avg_k;

      vReal_avg_slow[i]=vReal_avg_slow[i]*(1-avg_k)+vReal_avg[i]*avg_k;

      //float vReal_i_rel=abs(vReal[i]-vol_m)-		effSpeedH		/2.;
      float vReal_i_rel=abs(vReal_avg[i]-vReal_avg_m[i])-		effSpeedH;
			byte b=constrain( vReal_i_rel*vReal_i_rel/2,0,255);
      
			 if(indexOrBits<200)
			 {
	      leds[i]=CHSV(128+(vImag_avg[i])*(		effLengthH		/100.),255,b);
	      //leds[samplesE/3+i]=CHSV(128+(vReal_avg[i]-vReal[i])*(		effLengthH		/20.),255,b);
	      leds[samplesE/3+i]=CHSV(128+(vReal_avg[i]-vReal[i])*(		effLengthH		/100.),255,b);
	      leds[samplesE/3*2+i]=CHSV(128+(vReal_avg[i]-vReal_avg_slow[i])*(		effLengthH		/100.),255,b);
    	}
    	else
    	{

    	}
//# - old

    /*
    if(indexOrBits<64)
	  	leds[i]=CHSV(vReal[i],255,255); //!! interpolate bilinear  //leds[i*(NUM_LEDS-1)/samplesE]
    else if(indexOrBits<128)
    {
      vReal_avg[i]=vReal_avg[i]*(1-avg_k)+vReal[i]*avg_k;
      leds[i]=CHSV(vReal_avg[i],255,255);
    }
    else
    {
      vReal_avg[i]=vReal_avg[i]*(1-avg_k)+vReal[i]*avg_k;

      leds[i]=CHSV(128+(vReal_avg[i]-vReal[i])*(effLengthH/10.),255,255);
    }
	*/
  }
}

	if(indexOrBits>200)
	{
		for (int i = 0; i < 12; ++i)
		{
			byte ii=map(i,0, 11, 1, samplesE/3);
			setSegment(i,NUM_LEDS/12, abs(vReal_avg[ii]-vReal[ii])  );
		}

	}


  byte volRelative=map(vol,vol_m,vol_M,0,255);
  leds[0]=CHSV(((uint16_t)x/2)%256,255,255);
  leds[1]=CHSV(((uint16_t)x/2)%256,255,255);
  leds[2]=CHSV(volRelative,255,255);
  leds[3]=CHSV(volRelative,255,255);
  leds[4]=CHSV((int)vol_avg/4%256,255,255);
  leds[5]=CHSV((int)vol_avg/4%256,255,255);
  leds[6]=CHSV((int)vol_m%256,255,255);
  leds[7]=CHSV((int)vol_m%256,255,255);
  leds[8]=CHSV((int)vol_M%256,255,255);
  leds[9]=CHSV((int)vol_M%256,255,255);
}