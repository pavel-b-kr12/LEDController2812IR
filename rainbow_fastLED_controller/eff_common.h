/*
randomBlink

*/
//fill_solid( leds, NUM_LEDS, CRGB(50,0,200)); 

void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
	for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ )
	{
		leds[i] = CHSV(ahue, thissat, 255);
	}
}

void moveAll() //cyclic
{
	CRGB t=leds[NUM_LEDS-1];
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
	}
	leds[0]=t;
}

void addGlitter(byte chanceOfGlitter)
{
	if(random8() < chanceOfGlitter) {
		leds[ random16(NUM_LEDS) ] += CRGB::White;
	}
}

void invertLEDs()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i].r = 255 - leds[i].r;
		leds[i].g = 255 - leds[i].g;
		leds[i].b = 255 - leds[i].b;
	}
}

void flashLEDs()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]=CRGB::White;
	}
	FastLED.show(); delay(effLength); //! length
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]=0;
	}
	FastLED.show();
}

void flashAndBackLEDs()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]+=90;
	}
	FastLED.show(); delay(30);  //! length
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]-=90;
	}
	FastLED.show(); delay(10);
}

void fadeOut_continued()
{
	for(unsigned long t = millis()+4000; millis() < t; )
	{
		fadeToBlackBy(leds, NUM_LEDS, 3);
		FastLED.show(); delay(4);
	}
}
void offPixel_continued()
{
	for(unsigned long t = millis()+4500; millis() < t; )
	{
		//leds[random8(NUM_LEDS)]=CRGB::Black;

		NUM_LEDS_type N=random8(NUM_LEDS);
		if(leds[N]!=CRGB(0x000000)) //http://forum.arduino.cc/index.php?topic=385711.0
		{
			leds[N]=CRGB::Black;
			FastLED.show(); delay(3500/NUM_LEDS);
		}
	}
}

void moveOut_continued()
{
	leds[0]=CRGB::Black;
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
		{
			leds[i]=leds[i-1];
		}
		FastLED.show(); delay(map(effSpeed,0,255,25,1));
	}
}
