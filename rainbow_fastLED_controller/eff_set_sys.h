// @@ "C:\_wr\_Arduino\__LEDaddr\rainbow_fastLED_controller\rainbow_fastLED_controller\eff_set_AT\fill_colours.h"

void waveSmooth()
{

}

void fillRange(NUM_LEDS_type p0,NUM_LEDS_type E, CRGB c) //#use or refactor out
{
	if(p0>NUM_LEDS-1)p0=NUM_LEDS-1;
	if(p0+E > NUM_LEDS-1)E=NUM_LEDS-p0;
	
	for(NUM_LEDS_type i=p0;i<E;i++)
	{
		NUM_LEDS_type N=p0+i;
		leds[N]=c;
	}
}

void splitModeEditor()
{
		//<div id="effLength" class="sett_item">splt parts</div>
		// <div id="indexOrBits" class="sett_item">select part № [0...splt parts]</div>
		// <a class="sender btn brown" href="sett?effFade=1">on</a>/
		// <a class="sender btn brown" href="sett?effFade=0">off</a>
	
	if(effFade==255)
	{
		fill_solid(leds, NUM_LEDS, gColor);
		return;
	}

	
	if(effLength<0) effLength=1;
	else
	if(effLength>NUM_LEDS/2) effLength=NUM_LEDS/2;
	
	if(indexOrBits>=effLength) indexOrBits=effLength-1;
	
	byte parts_E=effLength;
	
	NUM_LEDS_type partLEDs_E=NUM_LEDS/parts_E;
	
	CRGB c=CRGB::Black;
	if(effFade==1) c=gColor;
	else 
	if(effFade==0) c=CRGB::Black;
	
	if(effFade==250)
	{
		fill_solid(leds+1*partLEDs_E,partLEDs_E, c);
		return;
	}
	
	
	for(byte partN=0; partN<parts_E;partN++)
	{
		if(partN==indexOrBits) //fillRange(partN*partLEDs_E, partLEDs_E, c);
			fill_solid(leds+partN*partLEDs_E,partLEDs_E, c);
	}

}


void setColors() //! fix when set r g b will be implemented
{  
	gColor=CHSV(effSpeedH,effSpeed,effLength);
	gColorBg=CHSV(effLengthH,effFade,indexOrBits);
}

void setColors_fill()
{  
	setColors();
	fill_solid(leds, NUM_LEDS, gColor);
}

void setColors_fill_tstRange()
{  
	setColors();
	FastLED.clear();
	fill_solid(leds+0, map(effFade,0,255,1,NUM_LEDS), gColor);
}

void currentPal_mod_w_gColor() //show nothing only modify currentPalette
{  
	setColors();
	currentPalette[indexOrBits/16]=CHSV(gColor.r, gColor.g, gColor.b);
}
void currentPal_mod_w_gColor_Test() //from palette_pipette
{  
	currentPal_mod_w_gColor();
	
  	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		leds[i] =ColorFromPalette(currentPalette, map(i,0,NUM_LEDS,0,255), 255, (effLength>128)?LINEARBLEND:NOBLEND);
	}
}













void print_currentPalette()
{
	for (int i = 0; i < 16; ++i)
	{
		Serial.print(currentPalette[i].r);
		Serial.print(",");
		Serial.print(currentPalette[i].g);
		Serial.print(",");
		Serial.println(currentPalette[i].b);
	}
}