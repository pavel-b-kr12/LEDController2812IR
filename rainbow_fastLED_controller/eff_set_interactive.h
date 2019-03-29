void draw_sample()
{
	if(i_eff%(effSpeed/4+1)==0)
	{	
	fadeToBlackBy(leds, NUM_LEDS, effFade);
	moveOutAll();
	}

	// for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	// {

	// }

	leds[map8(indexOrBits,0,NUM_LEDS)] =
	CRGB(
	gColor.r+i_eff/(1+effSpeedH),
	gColor.g+ beatsin8(1+effLengthH,0,255),
	gColor.b+ i_eff/(1+effLength)
	); //!   = h,s, bitsin(v)   		//map8( in, rangeStart, rangeEnd)  == map( in, 0, 255, rangeStart, rangeEnd);
	
}