// @ttt https://github.com/FastLED/FastLED/blob/master/colorutils.cpp

void testPower()
{
	FastLED.clear();
	fill_solid(leds, (effSpeed)%NUM_LEDS, CRGB(effLength,effLength,effLength)); //60 LEDs => 40mA +32mA/LED @4.5v  . Or 2x less @3v
	//FastLED.setBrightness( effLength ); 
}

void test_gDelay()
{
	FastLED.clear();
	gDelay=effSpeed;

	byte t=millis()%256;
	if(t>thissat) 	ibright=t-thissat;
	else 			ibright=255-thissat+t;

	thissat=t;

	leds[idex] =CHSV(ibright*16,255,50+gDelay); 

	idex++;	if(idex>=NUM_LEDS) idex=0;
}

void test_setTemperature() //http://fastled.io/docs/3.1/group___color_enums.html     FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
{
	FastLED.setTemperature(gColor);
}
void test_showColor()
{
	FastLED.showColor(gColor,effLength);
}
void test_fill_gradient_RGB()
{
	//if(effLength>=NUM_LEDS) effLength=NUM_LEDS-1;
	fill_gradient_RGB(leds, effLength, gColor, effLengthH, CHSV(gHue,255,25));
}
void test_setCorrection() //adj color before
{
	FastLED.setCorrection(gColor);
}
//====================================================================================

void targetPalette_set_Random()
{
    for( int i = 0; i < 16; i++) {
        targetPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes, using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used to set them up.
void targetPalette_set_Striped_BlackAndWhite()
{
    // 'black out' all 16 palette entries...
    fill_solid( targetPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    targetPalette[0] = CRGB::White;
    targetPalette[4] = CRGB::White;
    targetPalette[8] = CRGB::White;
    targetPalette[12] = CRGB::White;
}
void targetPalette_set_Striped_Random()
{
    fill_solid( targetPalette, 16, CRGB::Black);
    for (int i = 0; i < 8; i+=2)
    {
    	 targetPalette[i] =  CHSV( random8(), 255, 255);
    }
}

void targetPalette_set_PurpleAndGreen()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    targetPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

void currentPalette_scroll()
{
	CRGB c0=currentPalette[0];
	for (int i = 0; i < 15; ++i)
	{
	 	currentPalette[i]=currentPalette[i+1];
	}
	currentPalette[15]=c0;
}



//###
// Here's some random palette generators that I used with a single strand.
void SetupRandom16Palette() {
  for (int i = 0; i < 16; i++) targetPalette[i] = CHSV(random8(), random8(192,255), random8(128,255));
}

void SetupRandom4Palette() {
   targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, 255));
}

void SetupSimilar4Palette() {
  thishue=random8();                                                                    // This one picks a random hue for you.
  targetPalette = CRGBPalette16(CHSV(thishue+random8(32), 255, random8(128,255)),
                              CHSV(thishue+random8(32), 255, random8(192,255)),
                              CHSV(thishue+random8(32), 192, random8(192,255)),
                              CHSV(thishue+random8(32), 255, random8(128,255)));
}

void SetupMySimilar4Palette() {                                                         // This one allows you to select your own hue in advance.
  targetPalette = CRGBPalette16(CHSV(thishue+random8(32), 255, random8(128,255)),
                              CHSV(thishue+random8(32), 255, random8(192,255)),
                              CHSV(thishue+random8(32), 192, random8(192,255)),
                              CHSV(thishue+random8(32), 255, random8(128,255)));
}





byte currentPaletteN=255;
void set_currentPalette(byte i)  //0...15
{
	if(i==currentPaletteN) return;
	currentPaletteN=i;
	switch(i)
	{
		case 0: 
		default:
		targetPalette_set_Random();  break;

		case 1: currentPalette=CloudColors_p;  break;
		case 2: currentPalette=LavaColors_p;  break;
		case 3: currentPalette=OceanColors_p;  break;
		case 4: currentPalette=ForestColors_p;  break;
		case 5: currentPalette=RainbowColors_p;  break;
		case 6: currentPalette=RainbowStripeColors_p;  break;
		case 7: currentPalette=PartyColors_p;  break;
		case 8: currentPalette=HeatColors_p;  break;
		//case 9: currentPalette=Rainbow_gp;  break; //!? start crash from v0.99 or 98 ?

		case 10: targetPalette_set_Striped_BlackAndWhite();  break;
		case 11: targetPalette_set_Striped_Random();  break;
		case 12: targetPalette_set_PurpleAndGreen();  break;
		
		//# case 12: SetupRandom16Palette();  break;
		// case 12: SetupRandom4Palette();  break;
		// case 12: SetupSimilar4Palette();  break;
		// case 12: SetupMySimilar4Palette();  break;

						  // currentPalette = CRGBPalette16(
  //                                  CRGB::Black, CRGB::Black, CRGB::Black, CHSV(effSpeed, 255,4),
  //                                  CHSV(effLength, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,                                   
  //                                  CRGB::DarkOrange,CRGB::Orange, CRGB::Orange, CRGB::Orange,
  //                                  CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);
	}
	currentPalette=targetPalette;
}

//if(effFade>128)  indexOrBits -- choose pos  , set to gColor
//else if effSpeed<50  scroll
void palette_pipette() //## crash at indexOrBits>
{
	EVERY_N_MILLISECONDS(30)
	{
		byte i=indexOrBits/8;

		if(effFade>128)
		{
			if(i<16 )
			{
				currentPalette[i]=CHSV(gColor.r, gColor.g,gColor.b);
			}
			else
			{
				set_currentPalette(i-17); //0...15
			}
		}
		else
		{
			if(effSpeed!=idex)
			{
				idex=effSpeed;
				if(effSpeed<50) currentPalette_scroll();
			}
		}
	}
	
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		leds[i] =ColorFromPalette(currentPalette, map(i,0,NUM_LEDS,0,255), 255, (effLength>128)?LINEARBLEND:NOBLEND);
	}
}  // https://github.com/FastLED/FastLED/blob/master/examples/ColorPalette/ColorPalette.ino

//leds[map(effLength,0,255,0,NUM_LEDS-1)]
void test_palettes()
{
	set_currentPalette(indexOrBits/10);

	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		leds[i] =ColorFromPalette(currentPalette, map(i,0,NUM_LEDS,0,255), 255, (effLength>128)?LINEARBLEND:NOBLEND); //((millis()/2000)%2==0)?LINEARBLEND:NOBLEND  //NOBLEND == более резкие переходы
	}
}
//====================================================================================

void test_gradient() 				//PROGMEM https://github.com/FastLED/FastLED/wiki/Gradient-color-palettes  //https://gist.github.com/kriegsman/8281905786e8b2632aeb
{

	if(indexOrBits<99)
	gColor=CHSV(gColor.r, gColor.g,gColor.b);
	else
	if(indexOrBits>155)
	gColorBg=CHSV(gColor.r, gColor.g,gColor.b);

	fill_gradient_RGB (leds, NUM_LEDS, gColor, gColorBg);
}

void test_blend()
{
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		leds[i] =blend(CRGB::Black, CHSV(gColor.r,gColor.g,gColor.b), map(i,0,NUM_LEDS,0,255)); //!!scale8 //CHSV(map(i,0,NUM_LEDS,0,200),255,255)
	}
}

void test_easing()
{
	byte easeOutVal=0;
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		switch(indexOrBits/10)
		{
			case 0: easeOutVal = ease8InOutQuad(i);  break;
			case 1: easeOutVal = ease8InOutCubic(i);  break;
			case 2: easeOutVal = ease8InOutApprox(i);  break;

			case 3: easeOutVal = triwave8(i);  break;
			case 4: easeOutVal = quadwave8(i);  break;
			case 5: easeOutVal = cubicwave8(i);  break;
			case 6: easeOutVal = sin8(i);  break;
			case 7: easeOutVal = squarewave8(i);  break;

			case 8: easeOutVal = beat8(i);  break;
			case 9: easeOutVal = beatsin8(i);  break;
		}
		leds[i] = CHSV(gColor.r,gColor.g,easeOutVal);
	}

//lerpVal = lerp8by8(0, NUM_LEDS, easeOutVal); 

// lerp8by8 (uint8_t a, uint8_t b, fract8 frac)

//	https://github.com/FastLED/FastLED/wiki/FastLED-Wave-Functions
//	https://easings.net/
}



void test_RAWcolorMath() //!
{
	leds[0] =gColor;
	for(NUM_LEDS_type i=1;i<NUM_LEDS/2;i++)
	{
		leds[i] =gColor/i;
		leds[i+NUM_LEDS/2-1] =gColor%i;
	}

	//leds.raw[0..3]
}

void iterateRAWint()
{
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		leds[i] =millis()*effSpeed*4+i*effLength*4;  // i*(int)(millis()/2000);
	}
}




void blendB()
{ 
	uint8_t speed = beatsin8(2+effSpeed/16,0,255);
	gColor = blend(CRGB::Aqua, CRGB::Orange, speed);
	gColorBg = blend(CRGB::Orange, CRGB::Aqua, speed);
	fill_gradient_RGB(leds, 0, gColor, NUM_LEDS/2, gColorBg);
	fill_gradient_RGB(leds, NUM_LEDS/2+1, gColorBg, NUM_LEDS, gColor);
}








void moveRightMemset() {
    for (int i=0; i<NUM_LEDS; i++) {
    CRGB last_led = leds[NUM_LEDS-1];
    memmove( &leds[1], &leds[0], (NUM_LEDS-1)*sizeof(CRGB));
    leds[0] = last_led;
    FastLED.show();
    delay(300);
    }
} 




//-------------------------------------------- color_transition
const byte MINIMUM_BRIGHTNESS[] = {
  50, //Red
  50, //Green
  20 //Blue
};

CRGB colSrc, colDst;

unsigned long transitionStart, transitionPos;

void randomColor(CRGB &col)
{
  for (idex = 0; idex < 3; idex++)
    col.raw[idex] = MINIMUM_BRIGHTNESS[idex] + random(256 - MINIMUM_BRIGHTNESS[idex]);
}

void all_color_transition()
{
	if(i_eff==0)
	{
	  randomSeed(analogRead(A0));
	  randomColor(colSrc);
	  randomColor(colDst);
	  transitionStart = millis();
	}

	unsigned long loopMs = millis();
  transitionPos = loopMs - transitionStart;
  if (transitionPos >= effSpeed*32)
  {
    //done
    memcpy(&colSrc, &colDst, sizeof(colDst)); //copy dst to src
    memcpy(&leds[0], &colDst, sizeof(colDst)); //set current color
    randomColor(colDst); //new dst
    transitionStart = loopMs;
  }
  else
  {
  	for (int i = 0; i < NUM_LEDS; ++i)
    //in progress
    for (idex = 0; idex < 3; idex++)
      leds[i].raw[idex] = map(transitionPos, 0, effSpeed*64-1, colSrc.raw[idex], colDst.raw[idex]);
  }

  //Here "colCur" is the current CRGB value of the transition
}

/*

CRGB colSrc[gNUM_LEDS+1], colDst[gNUM_LEDS+1];

unsigned long transitionStart, transitionPos;

void randomColor(CRGB &col[])
{
 for (int i = 0; i < NUM_LEDS; ++i)
  for (idex = 0; idex < 3; idex++)
    col[i].raw[idex] = MINIMUM_BRIGHTNESS[idex] + random(256 - MINIMUM_BRIGHTNESS[idex]);
}

void color_transition()
{
	if(i_eff==0)
	{
	  randomSeed(analogRead(A0));
	  randomColor(colSrc);
	  randomColor(colDst);
	  transitionStart = millis();
	}

	unsigned long loopMs = millis();
  transitionPos = loopMs - transitionStart;
  if (transitionPos >= effSpeed*64)
  {
    //done
    memcpy(colSrc, colDst, sizeof(colDst)); //copy dst to src
    memcpy(leds, colDst, sizeof(colDst)); //set current color
    randomColor(colDst); //new dst
    transitionStart = loopMs;
  }
  else
  {
  	for (int i = 0; i < NUM_LEDS; ++i)
    //in progress
    for (idex = 0; idex < 3; idex++)
      leds[i].raw[idex] = map(transitionPos, 0, effSpeed*64-1, colSrc[i].raw[idex], colDst[i].raw[idex]);
  }

  //Here "colCur" is the current CRGB value of the transition
}

*/
//--------------------------------------------