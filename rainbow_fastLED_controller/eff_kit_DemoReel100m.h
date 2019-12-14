/*	//=========================================== Uncomment 2 sections and rename to .ino to run it separately ====================
#include <FastLED.h>

#define random8or16	random8

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    4
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    150
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
*/

void rainbow2();
void rainbow2anim();
void rainbowWithGlitter2();
void confetti3();
void sinelon3();
void juggle2();
void juggle2();
void bpm2();

void eff_fade_d();

void move_p1();
void rgb_firework_tick();
void rgb_rainbow_tick();
void rgb_stars_tick();

void wavesOppositePos();
void wavesOppositePosM();

void addGlitter2(fract8 N);
void nextPattern();
void selectPattern(byte N);

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {
	rainbow2, eff_fade_d, rainbowWithGlitter2, eff_fade_d, confetti3, sinelon3,  bpm2, juggle2,
	eff_fade_d, 
	move_p1,
	move_p1,
	move_p1, eff_fade_d, 
	rgb_firework_tick, eff_fade_d, 
	rgb_rainbow_tick, eff_fade_d,
	rgb_stars_tick, eff_fade_d,
	wavesOppositePosM,
	wavesOppositePos,
	eff_fade_d
 };




uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t rgb_effects_stage=0;
uint16_t effects_i; //eff countdown
byte fade=20;
/* //=========================================== Uncomment 2 sections and rename to .ino to run it separately ====================
byte indexOrBits=0;

void moveOutAllRemainFirst()
{
	for(byte i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
	}
}

void setup() {
  delay(1000);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}



void loop()
{
 DemoReel101();

  FastLED.show();  

  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
*/
byte gHue2 = 0; // rotating "base color" used by many of the patterns
  
long pattern_il = 0; //++ every anim //! use

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


int gHue2incr=1;

long nextPattern_t=10000;
byte eff_stage2=0;
void DemoReel101()
{
	//EVERY_N_MILLISECONDS( 10 ) 
	{
		gPatterns[gCurrentPatternNumber]();
		effects_i++;
	}
																				//if(
	EVERY_N_MILLISECONDS( 20 ) { gHue2+=gHue2incr; } // slowly cycle the "base color" through the rainbow

	if(millis()>nextPattern_t) nextPattern();
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  pattern_il=0;
  effects_i=0;
  
  eff_stage2++;
  
  if(gPatterns[gCurrentPatternNumber]== eff_fade_d) nextPattern_t=millis()+2000;
  else
  if(gPatterns[gCurrentPatternNumber]== rgb_stars_tick) nextPattern_t=millis()+18000;
  else
  if(gPatterns[gCurrentPatternNumber]== rgb_rainbow_tick) nextPattern_t=millis()+18000;
  else nextPattern_t=millis()+10000;
}
void selectPattern(byte N)
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (N) % ARRAY_SIZE( gPatterns);
}


static uint16_t var1, var2, var3;
static uint16_t DotPos;
static uint16_t DotPos2;
static CRGB color1, color2;


byte blend_amount=0;
uint16_t eff_stage;
int eff_ticks=0;
  
byte FADER_iM=122;
int eff_ticksM=11;


void rainbow2() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue2, 7);
}

void rainbowWithGlitter2() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow2();
  addGlitter2(80);
}

void addGlitter2( fract8 chanceOfGlitter) 
{
  //if( random8() < chanceOfGlitter)
  {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti3() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue2 + random8(64), 200, 255);
}

void sinelon3()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue2, 255, 192);
}

void bpm2()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue2+(i*2), beat-gHue2+(i*10));
  }
}

void juggle2() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void fillBetween(uint16_t x1, uint16_t x2, byte h)
{
	uint16_t m1=x1<x2?x1:x2;
	uint16_t M1=x1>x2?x1:x2;
	
	for(uint16_t i=m1;i<M1;i++)
	{
		leds[i%NUM_LEDS]+=CHSV(h, 255,222);
	}
}
void fillBetween_mM(uint16_t m, uint16_t M, byte h)
{
	for(uint16_t i=m;i<M;i++)
	{
		leds[i%NUM_LEDS]+=CHSV(h, 255,222);
	}
}
void fillBetween2(uint16_t var1, uint16_t var1_last, byte h)
{
	int xd=var1-var1_last;
	if(xd>1)
		fillBetween_mM(var1_last, var1, h);					
	else 
	if(xd<-1)
		fillBetween_mM(var1+1, var1_last+1, h);
}
uint16_t var1_last=0;
uint16_t var2_last=0;
void wavesOppositePos()
{
	fadeToBlackBy(leds, NUM_LEDS, 3);
	
	var1_last=var1;
	var2_last=var2;
	var1=beatsin8(15,0,NUM_LEDS-1,NUM_LEDS/4,NUM_LEDS/4);
	var2=beatsin8(15,0,NUM_LEDS-1,NUM_LEDS/4,NUM_LEDS/4);
	
	
	leds[var1]+=CHSV(millis()/100, 255,255);
	leds[NUM_LEDS-1-var2]+=CHSV(millis()/100+180, 255,255);
	
	fillBetween2(var1,var1_last,(millis()/100)%256);
	fillBetween2(var2_last,var2,(millis()/100)%256);
													//Serial.println();Serial.println(var1);Serial.println(var1_last);
	//fillBetween(var2_last, var2, (millis()/100+180)%256);
}
void wavesOppositePosM()
{
	fadeToBlackBy(leds, NUM_LEDS, 4);
	
	var1++; if(var1>NUM_LEDS-1) var1=0;
	//var2--; if(var2>NUM_LEDS-1) var2=NUM_LEDS-1;
	
	leds[var1]+=CHSV(millis()/100, 255,255);
	leds[NUM_LEDS-1-var1]+=CHSV(millis()/100+180, 255,255);
}



#define move_p1_FADEOUT   5

void move_p1()
{
	byte h=0;
  switch(eff_stage2%3)
  {
	  case 0:
	  {
		fadeToBlackBy(leds, NUM_LEDS,move_p1_FADEOUT);
		h=(millis()<1000)?effects_i/100:millis()/2000*33;
		leds[DotPos]= CHSV(h,255,255);
		DotPos++;
		DotPos=DotPos%NUM_LEDS;

	  }
	  break;
	  case 1:
	  {
		fadeToBlackBy(leds, NUM_LEDS,move_p1_FADEOUT/2);
		leds[DotPos]= CHSV(gHue2,255,255);
		DotPos++;
		DotPos=DotPos%NUM_LEDS;
	  }
	  break;
	  case 2:
	  {
		fadeToBlackBy(leds, NUM_LEDS,move_p1_FADEOUT);
		h=(millis()<1000)?effects_i/512:millis()/2000*33;
		leds[DotPos]= CHSV(effects_i/512,sin8(effects_i*5*(1+millis()/4000%2)),qadd8(20,sin8(effects_i*(1+millis()/4000%2))));
		DotPos++;
		DotPos=DotPos%NUM_LEDS;
	  }
	  break;
  }
}

#include "eff_kit_DemoReel100m\rgb_firework.h"
#include "eff_kit_DemoReel100m\rgb_stars.h"
#include "eff_kit_DemoReel100m\rgb_rainbow.h"

void eff_fade_d()
{
	fadeToBlackBy(leds, NUM_LEDS, 1);
}


