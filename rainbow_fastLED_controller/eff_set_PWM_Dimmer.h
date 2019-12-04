//@ https://randomnerdtutorials.com/esp8266-pwm-arduino-ide/

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapfloat01(float x, float out_min, float out_max)
{
 return (x) * (out_max - out_min)  + out_min;
}
/*
float lerpPrecission(float a, float b, float f) 
{
    return (a * (1.0 - f)) + (b * f);
}
float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}
inline uint16_t unsignedInterpolate(uint16_t a, uint16_t b, uint16_t position) {
    uint32_t r1;
    uint16_t r2;

      // Only one multiply, and one divide/shift right.  Shame about having to
      // cast to long int and back again.

    r1 = (uint32_t) position * (b-a);
    r2 = (r1 >> XY_TABLE_FRAC_BITS) + a;
    return r2;    
}
*/
	


void PWM_Dimmer()
{
	byte pin_N=0;
	
	int loop_d= oSaveObjDimmers[pin_N].loop_d;
	// int PWM_m= oSaveObjDimmers[pin_N].PWM_m; //TODO
	// int PWM_M= oSaveObjDimmers[pin_N].PWM_M;
	byte segE= oSaveObjDimmers[pin_N].segE;
	
	loop_d=(1+effLength)*100; //loop time
	
	long time=millis()%loop_d; //0....10000
	
	
	
	int seg_d=loop_d/segE; //200
	float seg_t01= ( time%seg_d ) /(float)seg_d; //%  0...1

	
	byte segNow=time/seg_d;
	byte segNext=(segNow<segE-1)?(segNow+1):0;
	int PW0= (int)mapfloat01(seg_t01,(float)oSaveObjDimmers[pin_N].vals[segNow], (float)oSaveObjDimmers[pin_N].vals[segNext]);   //seg_t01*PWM_sizeM;//seg_t01*PWM_sizeM;//saw //(((float)time)/loop_d)*PWM_sizeM;
	PW0=constrain(PW0,PWM_sizem,PWM_sizeM); //to avoid IR2101 burn it can't be 100%
	
	
	
	//analogWrite(PWM_pin0,PW0);
	//analogWrite(PWM_pin1,PW1);
	
	if(indexOrBits>=20 && indexOrBits<20+segE)
		oSaveObjDimmers[pin_N].vals[indexOrBits-20]=effFade*16;
	switch(indexOrBits)
	{
		case 11: bPWM_Dimmer=true; break;
		case 0: bPWM_Dimmer=false; break;
		case 26: 
			for(byte s=0;s<segE;s++)
			{
				oSaveObjDimmers[pin_N].vals[s]=effFade*16;
			}
		break;
		
	}
	
	
	//--------------------------------- debug output to LEDs
	
	fill_solid(leds, NUM_LEDS, CHSV( 0,0, map(PW0,PWM_sizem,PWM_sizeM,0,255)) ); //fill to PW
	
	leds[NUM_LEDS/segE*segNow+NUM_LEDS/segE/2]=CHSV(10,255,255);
	leds[NUM_LEDS/segE*segNext+NUM_LEDS/segE/2]=CHSV(40,255,255);
	
	
	//show time pos in loop
	NUM_LEDS_type x=constrain(map(time, 0, loop_d, 0, NUM_LEDS-1), 0, NUM_LEDS-1);//time pos marker
	leds[x]= CHSV(seg_t01*160,255,255);
	
	for(byte s=1;s<segE;s++) //show seg borders
		leds[NUM_LEDS/segE*s]= CHSV(0,0,155);
	


	
}