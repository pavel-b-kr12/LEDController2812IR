
bool bLEDsMirror=false; //##!! TODO leds is draw bufer. before show copy to show-buffer (and do matrix op, itcs if need)

void mode_switch()
{
	bLEDsMirror=indexOrBits%2;
	//TODO
	/*
	bTextOverlay
	bMap_type
	bPWM_Dimmer
	
	rgbEff
	rgbEff probability in random
	
	random len
	
	
	gColor
	gColorBg
	Palette sw
	
	*/
	
	/*
	incr mode: multiple anim() adds to LEDs
	*/
	
	/*
	split stripe to independant segs:
	
	set NUM_LEDS
	
	for()
	{
		choose eff
		anim()  wo show
		copy LEDs, NUM_LEDS to show-buff
	}
	show show-buff
	
	set NUM_LEDS to gNUM_LEDS
	
	*/

	
	// fill_solid(leds, NUM_LEDS, CHSV(indexOrBits<128?indexOrBits:gHue,effLength,effFade));
	// leds[x]=CRGB::Red;
}
