void rainbow() 
{
    fill_rainbow( leds, NUM_LEDS, gHue, effLengthH); //255/NUM_LEDS/effLength  //!opt /2 //! use  effSpeedH
}

void rainbowConfetti() 
{
    rainbow();
	// Dim a color by ~6% (16/256ths), eventually fading to full black.
	fadeToBlackBy(leds, NUM_LEDS, effFade);
	leds[random8or16(NUM_LEDS)]=CRGB(random8(),255,255);
	//if (!leds[n]) { leds[n] += CHSV( random8(), 255, 255); }
}
void rainbowWithGlitter() //!
{
  rainbow();                                                  // Built-in FastLED rainbow, plus some random sparkly glitter.
  addGlitter(effFade);
} 

//-------------------------------------------------------

void rainbowCycle() {
  byte *c;
  uint16_t i, j;

  for(j = 0; j < 256 * 1; j++) { // 1 cycles of all colors on wheel
    for(i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 *effLength/8 / NUM_LEDS) + j) & 255);
      leds[i]=CRGB( *c, *(c + 1), *(c + 2));
    }
    FastLED.show();
    delay(effSpeed/8);
  
  //!  if btn
  #if defined(SerialSelect) || defined(SerialControl)
    checkSerial();
  #endif
  #ifdef IRkeypad //!
  EVERY_N_MILLISECONDS( 40 )
  {
  if (IRLremote.receiving()) return;
  }
  #endif
  }
}
//-------------------------------------------------------

void randomBlink()
{
  //fadeall();
  fadeToBlackBy(leds, NUM_LEDS, effSpeed/8);
  byte M=random8(0,effLength); //! sin/saw distribution
  for(NUM_LEDS_type i=0;i<M;i++)
  {
    leds[random8or16(NUM_LEDS)] = gColor;
  }
}

void Add_random_rainbow_pxel()
{
  NUM_LEDS_type N=random8or16(NUM_LEDS);
  leds[N]=CHSV(N+i_eff*effLength,255,255); //! fix this not produce rainbow
}
void randomBlinkRainbow()
{
  //! up brightness
  for(byte i = 0; i < 1 || i <effSpeed/32; ++i)
  {
     Add_random_rainbow_pxel();
  }
  
  #ifdef LEDs_RENDER
  FastLED.show();
  delay(4);
  FastLED.clear();
  FastLED.show();
  //delay(6);
  #endif
}
void randomBlinkRainbowFade()
{
  byte t=random8(180);
  if(t<effSpeed)
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)  //!! fadeToBlackBy
  {
      leds[i].nscale8(223); //253
  }
  
  if(t<effLength)
  {
    Add_random_rainbow_pxel();
  }
}
/* save mem
CRGB ledsTmp[NUM_LEDS];

void randomBlinkRainbow()
{
  //! up brightness
  fill_rainbow( ledsTmp, NUM_LEDS, gHue, effLength);
  byte N=random8or16(0,NUM_LEDS-1);
  leds[N]=ledsTmp[N];
  N=random8or16(0,NUM_LEDS-1);
  leds[N]=ledsTmp[N];
  N=random8or16(0,NUM_LEDS-1);
  leds[N]=ledsTmp[N];
  FastLED.show();
  delay(4);
  FastLED.clear();
  FastLED.show();
  delay(6);
}

void randomBlinkRainbowFade()
{
  byte t=random8();
  if(t<99)
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++) 
  {
      leds[i].nscale8(253); 
  }
  
 
  if(t<44)
  {
	  fill_rainbow( ledsTmp, NUM_LEDS, gHue, effLength);
	  byte N=random8or16(0,NUM_LEDS-1);
	  leds[N]=ledsTmp[N];
  }
}
*/

void rainbow_beat()
{
  uint8_t beatA = beatsin8(effSpeed, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(effLength, 0, 255); //! effSpeed2
  fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 8);            // Use FastLED's fill_rainbow routine.
} // rainbow_beat()

//---------------------------------------------------- //!
#ifndef saveMem
void rainbow_fade() //Hue on all or rare LEDs
{
  ihue+=effSpeed/4+1;

  for(byte idex = 0 ; idex < NUM_LEDS; idex++ ) {
    if(effLength>50 || (effLength>=10 && idex%effLength>8) || (effLength<10 && idex%effLength==0))
    {
      leds[idex] = CHSV(ihue, 255, 255);
    }
  }
}
#endif
void rainbow_fill_slow() {
  idex++;
  ihue += effSpeed;
  if (idex >= NUM_LEDS)    idex = 0;

  if(effLength>50 || (effLength>=10 && idex%effLength>8) || (effLength<10 && idex%effLength==0))
  {
    leds[idex] = CHSV(ihue, 255, 255);
  }
}

void rainbow_vertical() {                        //-m23-RAINBOW 'UP' THE LOOP
  idex++;
  if (idex > CENTER_TOP_INDEX) {
    idex = 0;
  }

  int idexA = idex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(gHue, 255, 255);
  leds[idexB] = CHSV(gHue, 255, 255);
}

//----------------------------------------------------

void rainbowSegments_shift() //##
{
    fill_rainbow( leds, NUM_LEDS, gHue, effLength); //255/NUM_LEDS/effLength
	
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		if((i+millis()/100)%effLength>effLength/2)
		leds[i] = CRGB::Black; //! Black, inverse, blink, different gHue shift or direction
	}
}
void rainbowSegments_shiftSin() //##
{
    fill_rainbow( leds, NUM_LEDS, gHue, NUM_LEDS/effLength); //255/NUM_LEDS/effLength
	
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		if((i+beatsin8(effLength, 0, effLength))%effLength>effLength/2)
		leds[i] = CRGB::Black; //! Black, inverse, blink, different gHue shift or direction
	}
}

void rainbowSegments2() 
{
    fill_rainbow( leds, NUM_LEDS, gHue, 255/NUM_LEDS/effLength); //255/NUM_LEDS/effLength
	
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i+=((i+beatsin8(effLength, 0, effLength))%effLength>effLength/2)?1:effLength/2)
	{
		leds[i] = CRGB::Black;
	}
}

void  rainbowSpawn_moveFromStartWithSeparators()
{
	//if(i_eff%abs(NUM_LEDS/2-effSpeed) == 0)
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		//leds[i].nscale8(253); 
	}
	
	leds[0] =CHSV(gHue,255,
			//((i_eff+beatsin8(effLength, 0, effLength))%(effLength/2)>effLength/8)
			((i_eff+beatsin8(effSpeed/8, 0, effLength))%effLength>effLength/4)
			?0   //black separators
			:255
			);
}

void  rainbowSpawn_moveFromStartWithSeparatorsB()
{
  //if(i_eff%abs(NUM_LEDS/2-effSpeed) == 0)
  for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
  {
    leds[i]=leds[i-1];
    //leds[i].nscale8(253); 
  }
  
  byte state=i_eff%effLength;
  if(state<2) leds[0]=CRGB::Black;
  else
    if(state==2||state==(effLength-1)) leds[0]=CHSV(gHue/16,255,255);
  else
    {
      leds[0]=CHSV(gHue,255,255);
      leds[0].r=1-leds[0].r;
      leds[0].g=1-leds[0].g;
      leds[0].b=1-leds[0].b;
    }
}

// void dropDivided() //!!
// {
//   White

//   rnd - rnd inv

//   move in dif dirr
// }

void spawnPixel_moveAll() //!
{
	if(effSpeed>20 || i_eff%(11-effSpeed/2) == 0)
	{
  	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) //! move all
  	{
  		leds[i]=leds[i-1];
  		//leds[i].nscale8(253); 
  	}
	}
	
	if(i_eff%effLength==0)
	{
		leds[0]=CHSV(random8(7)*32,255,255);
	}
}

//----------------------------------------------------

void random_burst() {                         //-m4-RANDOM INDEX/COLOR
  for(NUM_LEDS_type i=0;i<effSpeed/4+1;i++)
  {
    leds[random(0, NUM_LEDS)] = CHSV(random8(), gColor.g, random8()<effLength?255:0);
  }
  
  // for(NUM_LEDS_type i=0;i<effLength/10;i++)
  // {
  // leds[random(0, NUM_LEDS)] = CHSV(ihue, thissat, 0);
  // }
}

void confetti() {                                             // Random colored speckles that blink in and fade smoothly.
  fadeToBlackBy(leds, NUM_LEDS, effSpeed);
  for(byte i = 0; i < effLength; i++)
  {
      NUM_LEDS_type pos = random16(NUM_LEDS);
      leds[pos] += CHSV(gHue + random8(64), 200, 255);
  }
  
}
void confetti_move() {
  EVERY_N_MILLISECONDS(40)
  {
	moveOutAll();
	//moveOutAllRemainFirst(); //! with blend blend
  }
  thishue++;
  
  fadeToBlackBy(leds, NUM_LEDS, effSpeed);
  for(byte i = 0; i < 1+effSpeed/64; i++)
  {
      NUM_LEDS_type pos = random16(NUM_LEDS);
      leds[pos] = CHSV(thishue + random8(effLength/2), 200, 255); 
      //leds[pos] += CHSV(thishue + random8(effLength/4), 200, 255); 
  }
}
void confetti_moveRemainFirstAdd() {                                             // Random colored speckles that blink in and fade smoothly.
  EVERY_N_MILLISECONDS(40)
  {
	//moveOutAll();
	moveOutAllRemainFirst(); //! with blend blend
  }
  thishue++;
  
  fadeToBlackBy(leds, NUM_LEDS, effSpeed);
  for(byte i = 0; i < 1+effSpeed/64; i++)
  {
      NUM_LEDS_type pos = random16(NUM_LEDS);
      //leds[pos] = CHSV(thishue + random8(effLength/4), 200, 255); 
      leds[pos] += CHSV(thishue + random8(effLength/4), 200, 255); 
      //leds[pos] =blend(leds[pos], CHSV(thishue + random8(effLength/4), 200, 255), sin8(i_eff));   
  }
}
void confetti_moveRemainFirstBlend() {                                             // Random colored speckles that blink in and fade smoothly.
  EVERY_N_MILLISECONDS(40)
  {
	//moveOutAll();
	moveOutAllRemainFirst(); //! with blend blend
  }
  thishue++;
  
  fadeToBlackBy(leds, NUM_LEDS, effSpeed/8);
  for(byte i = 0; i < 1+effSpeed/64; i++)
  {
      NUM_LEDS_type pos = random16(NUM_LEDS);
      //leds[pos] = CHSV(thishue + random8(effLength/4), 200, 255); 
      //leds[pos] += CHSV(thishue + random8(effLength/4), 200, 255); 
	  CRGB colNew=CHSV(thishue + random8(beatsin8(4)), 200, 255); //effLength<6?effLength*20: effLength/4
	  if(pos==0) leds[pos]=colNew;
	  else
      leds[pos] =blend(leds[pos], colNew, (effLength<6)?sin8(i_eff):effLength);
  }
}
void confetti_moveRemainFirstBlendByPos() {                                             // Random colored speckles that blink in and fade smoothly.
  EVERY_N_MILLISECONDS(40)
  {
	//moveOutAll();
	moveOutAllRemainFirst(); //! with blend blend
  }
  thishue++;
  
  fadeToBlackBy(leds, NUM_LEDS, effSpeed/8);
  for(byte i = 0; i < 1+effSpeed/64; i++)
  {
	NUM_LEDS_type pos = random16(NUM_LEDS);
	//leds[pos] = CHSV(thishue + random8(effLength/4), 200, 255); 
	//leds[pos] += CHSV(thishue + random8(effLength/4), 200, 255); 
	CRGB colNew=CHSV(thishue + random8(effLength/4) , 200, 255); //+pos/16
	if(pos==0)
		leds[pos]=colNew;
	else
		leds[pos]=blend(leds[pos], colNew, map(pos,0,NUM_LEDS,8,128));
  }
}


void confetti_density() {                                             // Random colored speckles that blink in and fade smoothly.
	fadeToBlackBy(leds, NUM_LEDS, effFade);
	for(byte i = 0; i < effSpeed; i++)
	{
		NUM_LEDS_type pos = random16(NUM_LEDS);
		if(random8()>sin8(pos*effSpeedH/32+indexOrBits)*128/effLengthH)
			leds[pos] += CHSV(gHue + random8(effLength), 200, 255);
	}

}

void random_color_pop() {                         //-m25-RANDOM COLOR POP
  //clear();
  leds[idex]=0;
  idex =random8or16(NUM_LEDS);
  leds[idex] = CHSV(random8(), 255, 255);
}

void sinelon() {                                              // A colored dot sweeping back and forth, with fading trails.

  fadeToBlackBy(leds, NUM_LEDS, effLength);
  NUM_LEDS_type pos = beatsin16(effSpeed,0,NUM_LEDS-1);
  leds[pos] += CHSV(gHue, 255, 192);
  
} // sinelon()

void bpm() {                                                  // Colored stripes pulsing at a defined Beats-Per-Minute.

  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(effLength, 64, 255);
  
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10)); //! effSpeedH
  }
} // bpm()

void juggle() {                                               // Eight colored dots, weaving in and out of sync with each other.

  fadeToBlackBy(leds, NUM_LEDS, effSpeed);
  byte dothue = 0;
  
  for(NUM_LEDS_type i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS-1)] |= CHSV(dothue, 200, 255);
    dothue += effLength;
  }
  
} // juggle() https://www.youtube.com/watch?v=L-G_-l9GzOk

