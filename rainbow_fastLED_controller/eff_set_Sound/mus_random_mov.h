float a_avg;
int accumulator=0;
void mus_random_mov() //@@
{

	byte a=qadd8( analogRead(sound_p), analogRead(sound_p) )-effLengthH; //! fix when level will be good (now I got <128)
	if(i_eff==0) a_avg=a;
	else
	{
		float avg_k=effLength/256.0;
		a_avg=a_avg*(1-avg_k)+a*avg_k;

	}

	leds[random8or16(NUM_LEDS)]=   ColorFromPalette(currentPalette, a, qadd8(50,abs(a_avg-a)*20), LINEARBLEND); 

	if(abs(a_avg-a)>100) invertLEDs(); 
	else
	if(abs(a_avg-a)>50 &&random8()>220) flashLEDs_d_effL();

	accumulator+=a;
	int accumulator_lim=effSpeed*8;
	if(accumulator>accumulator_lim)
	{
	 moveOutAll();
	 accumulator-=accumulator_lim;
	}

	fadeToBlackBy(leds, NUM_LEDS, effFade/4);

	//##ifdef tst
	if(indexOrBits>128)
	{
		leds[0]=CHSV(a,255,255);
		leds[1]=CHSV(a,255,255);
		leds[NUM_LEDS/4]=CHSV(a_avg,255,255);
		leds[NUM_LEDS/4+1]=CHSV(a_avg,255,255);
		leds[NUM_LEDS/2]=CHSV(qadd8(50,abs(a_avg-a)*20),255,255);
		leds[NUM_LEDS/2+1]=CHSV(qadd8(50,abs(a_avg-a)*20),255,255);
	}
	//#endif
}