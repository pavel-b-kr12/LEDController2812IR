
void PWM_Dimmer()
{
	#define segmentsE	pwm_vsE	
	/*
	byte pwmN=0;
	
	int loop_d= oSaveObjDimmers[pwmN].loop_d;
	// int PWM_m= oSaveObjDimmers[pwmN].PWM_m; //TODO
	// int PWM_M= oSaveObjDimmers[pwmN].PWM_M;
	
	//no adj NUM of segments
	
	loop_d=(1+effLength)*100; //loop time
	
	long time=millis()%loop_d; //0....10000
	
	
	
	
	int seg_d=loop_d/segmentsE; //200
	float seg_t01= ( time%seg_d ) /(float)seg_d; //%  0...1

	
	byte segNow=time/seg_d;
	byte segNext=(segNow<segmentsE-1)?(segNow+1):0;
	int PW0= (int)mapfloat01(seg_t01,(float)oSaveObjDimmers[pwmN].pwm_vs[segNow], (float)oSaveObjDimmers[pwmN].pwm_vs[segNext]);   //seg_t01*PWM_v_M;//seg_t01*PWM_v_M;//saw //(((float)time)/loop_d)*PWM_v_M;
	PW0=constrain(PW0,PWM_v_m,PWM_v_M); //to avoid IR2101 burn it can't be 100%
	
	
	
	//analogWrite(PWM_pin0,PW0);
	//analogWrite(PWM_pin1,PW1);
	
	if(indexOrBits>=20 && indexOrBits<20+segmentsE)
		oSaveObjDimmers[pwmN].pwm_vs[indexOrBits-20]=effFade*16;
	switch(indexOrBits)
	{
		case 11: bPWM_Dimmer=true; break;
		case 0: bPWM_Dimmer=false; break;
		case 26: 
			for(byte s=0;s<segmentsE;s++)
			{
				oSaveObjDimmers[pwmN].pwm_vs[s]=effFade*16;
			}
		break;
		
	}
	
	
	//--------------------------------- debug output to LEDs
	
	fill_solid(leds, NUM_LEDS, CHSV( 0,0, map(PW0,PWM_v_m,PWM_v_M,0,255)) ); //fill to PW
	
	leds[NUM_LEDS/segmentsE*segNow+NUM_LEDS/segmentsE/2]=CHSV(10,255,255);
	leds[NUM_LEDS/segmentsE*segNext+NUM_LEDS/segmentsE/2]=CHSV(40,255,255);
	
	
	//show time pos in loop
	NUM_LEDS_type x=constrain(map(time, 0, loop_d, 0, NUM_LEDS-1), 0, NUM_LEDS-1);//time pos marker
	leds[x]= CHSV(seg_t01*160,255,255);
	
	for(byte s=1;s<segmentsE;s++) //show seg borders
		leds[NUM_LEDS/segmentsE*s]= CHSV(0,0,155);
	
*/

FastLED.clear();

		
for(byte pwmN=0;pwmN<PWM_E;pwmN++)
{
//------------copy from dimmer //!
		int loop_d= oSaveObjDimmers[pwmN].loop_d;	//eg 1000
		long loop_time=millis()%loop_d;	//eg 0....1000
		
		//-----------calc  segNow, segNow_start, segNow_end
		byte segNow=0;
		int segNow_start=0;
		int segNow_end=0;
		int v_start=0;  //! TODO v_start is pwm_vs[segNow]
		int v_end=oSaveObjDimmers[pwmN].pwm_vs[segmentsE-1];
		while(true)
		{
			segNow_start=segNow_end;
			v_start=v_end;
			if(segNow==segmentsE)
			{
				segNow_end=loop_d;
				//v_end=oSaveObjDimmers[pwmN].pwm_vs[0];
				v_end=v_start;
				break;
			}
			segNow_end=oSaveObjDimmers[pwmN].pwm_ts[segNow]*100; //! *100
			v_end=oSaveObjDimmers[pwmN].pwm_vs[segNow];
			if(loop_time > segNow_end)
				segNow++;
			else break;
		}
		byte segLast=segNow>0?segNow-1:segmentsE-1;
		//-----------
		int PW0= map(loop_time,
		segNow_start,
		segNow_end,
		v_start,
		v_end
		);
		PW0=constrain(PW0,PWM_v_m,PWM_v_M);
//------------

	#define LEDsPerPWM	NUM_LEDS/PWM_E
	#define LEDsPerSeg	LEDsPerPWM/segmentsE
	
	for(byte seg=0;seg<segmentsE;seg++)
	for (NUM_LEDS_type i = 0; i < LEDsPerSeg; ++i)
	{
		NUM_LEDS_type li=pwmN*LEDsPerPWM + LEDsPerSeg*seg +i;
		
		
		if(i<2)
			leds[li]=CHSV(0,0,PW0/8); //now PWM
		else
		{
			byte seg_last=seg==0?segmentsE-1:seg-1;
			leds[li]=CHSV(0,0,map(i,0,LEDsPerSeg, oSaveObjDimmers[pwmN].pwm_vs[seg_last], oSaveObjDimmers[pwmN].pwm_vs[seg] )/5); //draw saved data
		}
		
		if(seg==segNow) leds[li]+=CRGB(44,0,0); //current seg
		
	}
	
	leds[ constrain(map(loop_time,0,loop_d, pwmN*LEDsPerPWM, (pwmN+1)*LEDsPerPWM),0, NUM_LEDS-1)]+=CRGB(255,0,0); //now
	
}

if(millis()/200%2) leds[pwm_p_selected]+=CRGB::Blue;

		for(byte p=0;p<16;p++)
		{	
			int mask = 1 << p; // gets the 6th bit
			if ((PWM_ps_enabled & mask) != 0) {
						leds[p]+=CRGB(77,33,11);
			} else {
						leds[p]=CRGB::Blue;
			}

		}
	
}