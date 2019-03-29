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

void moveOutAllRemainFirst()
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
	}
}
void moveAll() //cyclic
{
	CRGB t=leds[NUM_LEDS-1];
	moveOutAllRemainFirst();
	leds[0]=t;
}
void moveOutAll()
{
	moveOutAllRemainFirst();
	leds[0]=0;
}
	
void moveOutAll_fade()
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[i].nscale8(253);
	}
}
void moveOutAll_fadeN() //!tst
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[i].nscale8(map(i,0,NUM_LEDS,0,255));
	}
}


void move_toCenter_RemainFirst()
{
	for(NUM_LEDS_type i = NUM_LEDS/2-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[NUM_LEDS-i-1]=leds[NUM_LEDS-i];
	}
}
void move_fromCenter_RemainFirst()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS/2-2 ; i++) 
	{
		leds[i]=leds[i+1];
		leds[NUM_LEDS-i-1]=leds[NUM_LEDS-i-2];
	}
}
// void move_segments_RemainFirst() //!
// {
// 	byte segments=
// 	for(NUM_LEDS_type i = NUM_LEDS/segments-1; i >0 ; i--) 
// 	{
// 		leds[i]=leds[i-1];
// 		leds[i+NUM_LEDS/2]=leds[i-1+NUM_LEDS/2];
// 	}
// }





void addGlitter(byte chanceOfGlitter)
{
	if(random8() < chanceOfGlitter) {
		leds[ random16(NUM_LEDS) ] += gColor;
	}
}
void addGlitterBlack(byte chanceOfGlitter)
{
	if(random8() < chanceOfGlitter) {
		leds[ random16(NUM_LEDS) ] = 0;
	}
}

// void addGlitterByBG(byte chanceOfGlitter, byte V)
// {
// 	if(random8() < chanceOfGlitter) {
// 		leds[ random16(NUM_LEDS) ] = gColorBg.nscale8(V);
// 	}
// }

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

void scroll1cycle_continued()
{
	for(NUM_LEDS_type j = 0; j < NUM_LEDS; j++)
	{
		CRGB led0=leds[0];

		for(NUM_LEDS_type i = 0; i < NUM_LEDS-1; i++)
		{
			leds[i]=leds[i+1];
		}
		leds[NUM_LEDS-1]=led0;
		FastLED.show(); 
		delay(abs(NUM_LEDS/2-j)/4); //start and stop slower  //! || beatsin
	}
}

void scroll1cycle_continuedRev()
{
	for(NUM_LEDS_type j = 0; j < NUM_LEDS; j++)
	{
		CRGB led_last=leds[NUM_LEDS-1];

		for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--)
		{
			leds[i]=leds[i-1];
		}
		leds[0]=led_last;
		FastLED.show(); 
		delay(abs(NUM_LEDS/2-j)/2); //start and stop slower  //! || beatsin
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