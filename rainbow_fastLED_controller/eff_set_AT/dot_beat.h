// Similar to dots by John Burroughs, but uses the FastLED beatsin8() function instead.
                                   
void dot_beat() {
	byte bpm=1+effSpeed/4;

	uint8_t inner = beatsin8(bpm, NUM_LEDS/4, NUM_LEDS/4*3);    // Move 1/4 to 3/4
	uint8_t outer = beatsin8(bpm, 0, NUM_LEDS-1);               // Move entire length
	uint8_t middle = beatsin8(bpm, NUM_LEDS/3, NUM_LEDS/3*2);   // Move 1/3 to 2/3

	leds[middle] = CRGB::Purple;
	leds[inner] = CRGB::Blue;
	leds[outer] = CRGB::Aqua;

	nscale8(leds,NUM_LEDS,effLength); //255-thisfade	// Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
} 

byte NrStart=5;
byte NrEnd=15;
byte NgStart=20;
byte NgEnd=30;
byte NbStart=40;
byte NbEnd=50;
//CRGBSet ledSet(leds, NUM_LEDS); //https://github.com/FastLED/FastLED/wiki/RGBSet-Reference

void dot_beat_area() {
	byte bpm=4+effSpeed/8;

	NrStart=beatsin8(bpm, 0, NrEnd);
	NrEnd=beatsin8(bpm, NrStart, (NgStart+effLength/16)%NUM_LEDS);
	
	NgStart=beatsin8(bpm+2, NrEnd, NgEnd);
	NgEnd=beatsin8(bpm+2, NgStart, (NbStart+effLength/16)%NUM_LEDS);
	
		
	NbStart=beatsin8(bpm+3, NgEnd, (NbEnd-effLength/16)%NUM_LEDS);
	NbEnd=beatsin8(bpm+3, NbStart, NUM_LEDS-1);
	
	fadeToBlackBy(leds,NUM_LEDS,11);
	
	for(int i=0;i<NUM_LEDS;i++)
	{
		if(i>NrStart && i<NrEnd)	leds[i].r=255;
		if(i>NgStart && i<NgEnd)	leds[i].g=255;
		if(i>NbStart && i<NbEnd)	leds[i].b=255;
	}
	
	//for(CRGB & pixel : ledSet(NrStart%NUM_LEDS,NrEnd-1)) { pixel.r=255; } 
	//for(CRGB & pixel : ledSet(NgStart%NUM_LEDS,NgEnd-1)) { pixel.g=255; } 
	//for(CRGB & pixel : ledSet(NbStart%NUM_LEDS,NbEnd-1)) { pixel.b=255; } 


	// = CRGB::Black;
	
	// ledSet(NrStart,NrEnd)=CRGB::Red; //255; //
	// ledSet(NgStart,NgEnd).g=255;
	//ledSet(NbStart,NbEnd).b=255;

	// leds[middle] = CRGB::Purple;
	// leds[inner] = CRGB::Blue;
	// leds[outer] = CRGB::Aqua;

	//nscale8(leds,NUM_LEDS,effLength); //255-thisfade	// Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);
} 