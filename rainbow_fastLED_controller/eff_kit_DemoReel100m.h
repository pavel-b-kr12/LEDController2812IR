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
void sinelon3m();
void juggle2();
void juggle2();
void bpm2();

void rgb_effects();

void addGlitter2(fract8 N);
void nextPattern();
void selectPattern(byte N);

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rgb_effects, rainbow2, confetti3, sinelon3, juggle2, bpm2, rainbow2anim,sinelon3m };//

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
  delay(3000); // 3 second d for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}



void loop()
{
 DemoReel101();
   // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a d to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 
  
}
*/
byte gHue2 = 0; // rotating "base color" used by many of the patterns
  
long pattern_il = 0; //++ every anim //! use

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))



void rgb_effects_stage_set(byte v)
{
  if(v==rgb_effects_stage) return;

	rgb_effects_stage=v;
	effects_i=0;
	
	if(v==0) nextPattern();
}

void rgb_effects_stage_setNext()
{
	rgb_effects_stage_set(rgb_effects_stage+1);
}

int gHue2incr=1;
void DemoReel101()
{
  // Call the current pattern function once, updating the 'leds' array
  EVERY_N_MILLISECONDS( 10 ) 
  {
	gPatterns[gCurrentPatternNumber]();
	
	if(millis()/2100%6==1 &&rgb_effects_stage!=2 &&rgb_effects_stage!=6) addGlitter2(millis()/220%50);
  }
																				//if(millis()<2000) indexOrBits=0;

  // do some periodic updates
  EVERY_N_MILLISECONDS( 15 ) { gHue2+=gHue2incr; } // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS(5333)
  {
	  gHue2incr=random8(3)-1;
  }

  // if(indexOrBits<4)
  // {
	  EVERY_N_SECONDS( 4 ) {
		  if(gCurrentPatternNumber>0 || (random8()>120 &&rgb_effects_stage>6)) nextPattern();
	  } // change patterns periodically
  // }
  // else
  // {
	  // selectPattern(indexOrBits/10);
	  
	  // if(effFade>4)
	  // {
		  // rgb_effects_stage_set(effFade/10);
	  // }
  // }
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  pattern_il=0;
}
void selectPattern(byte N)
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (N) % ARRAY_SIZE( gPatterns);
}



void rainbow2() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue2, 7);
}

byte divB=7;
byte speedB=7;
void rainbow2anim() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue2 -beatsin8(speedB,0,255),divB);
  EVERY_N_MILLISECONDS(4555)
  {
	  divB=random8(3,20);
	  speedB=random8(6,20);
  }
}

void rainbowWithGlitter2() 
{
  // built-in FastLED rainbow2, plus some random sparkly glitter
  rainbow2();
  addGlitter2(50+millis()/100%50);
}

void addGlitter2( fract8 chanceOfGlitter) 
{
	for(byte i=0;i<4;i++)
  if( random8() < chanceOfGlitter) {
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
void sinelon3m()
{
	EVERY_N_MILLISECONDS(1555)
  {
	  fade=random8(0,20);
  }
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, fade);

  leds[ (beatsin16( 13, 0, NUM_LEDS-1 )+beatsin16( 15, 0, NUM_LEDS-1 ))/2] += CHSV( gHue2, 255, 192);
  leds[ beatsin16( 11, 0, NUM_LEDS-1 )] += CHSV( gHue2+60, random8(), 192);
  leds[ beatsin16( 9, 0, NUM_LEDS-1 )] += CHSV( gHue2+120+random8()/16, 255, random8());
  leds[ beatsin16( 7, 0, NUM_LEDS-1 )] += CHSV( random8(), 255, 255);
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


#define FADER_STEP      1
#define FADER_PERIOD    10


#define Stars_cycles           5 //30

// Счётчики стадий алгоритмов
static uint16_t var1, var2, var3;
static uint16_t DotPos;
static uint16_t DotPos2;
static CRGB color1, color2;
     

byte blend_amount=0;
uint16_t eff_stage;
int eff_ticks=0;
  
byte FADER_iM=122;
int eff_ticksM=11;
	 
#include "eff_kit_DemoReel100m\rgb_test.h"
#include "eff_kit_DemoReel100m\rgb_firework.h"
#include "eff_kit_DemoReel100m\rgb_stars.h"
#include "eff_kit_DemoReel100m\rgb_rainbow.h"

void eff_fade_d()
{
	fadeToBlackBy(leds, NUM_LEDS,FADER_STEP);
	
	if(effects_i==FADER_iM)
	{
		rgb_effects_stage_setNext();
		return;
	}
	effects_i++;
}
  
void rgb_effects(void)
{
	if(pattern_il==0) rgb_effects_stage=0; //after select this eff
	pattern_il++;
	
	switch(rgb_effects_stage)
	{
		case 0:
		{
			if(effects_i==0)
			{
				eff_ticks=0;
			}
			
			EVERY_N_MILLISECONDS(2222) eff_stage++;
			eff_ticks++;
			//-----------
			rgb_test_tick();
			//-----------
			delay(10);
			
			effects_i++;
			if(effects_i>100*15)
			{
				rgb_effects_stage_setNext();
				break;
			}
		}
		break;
	
		case 1: eff_fade_d(); break; // Плавное затухание всех светодиодов 

		// Анимация САЛЮТ
		case 2:
		{
			if(effects_i==0)
			{
				eff_stage = 0;
				eff_ticks=0;
			}
			
			//-----------
			rgb_firework_tick();
			//-----------
			delay(5);
			

			effects_i++;
			if(effects_i==1000)
			{
				rgb_effects_stage_setNext();
				break;
			}
		}
		break;

		case 3: eff_fade_d(); break; // Плавное затухание всех светодиодов
		
		// Анимация РАДУГА
		case 4:
		{
			if(effects_i==0)
			{
				eff_stage = 0;
				eff_ticks=0;
			}
			
			eff_ticks++;
			//-----------
			rgb_rainbow_tick();
			//-----------
			delay(10);
			
			effects_i++;
			if(effects_i>100*30) rgb_effects_stage_setNext();
		}
		break;
		
		case 5: eff_fade_d(); break; // Плавное затухание всех светодиодов

		// Анимация ЗВЁЗДЫ
		case 6:
		{
			if(effects_i==0)
			{
				eff_stage = 0;
				eff_ticks=0;
			}

			rgb_stars_tick();

			delay(10);

			effects_i++;
			if(effects_i>100*60) rgb_effects_stage_setNext();
		}
		break;
		
		case 7: eff_fade_d(); break; // Плавное затухание всех светодиодов
		
		default:
		{
			// leds[30]=CRGB::White;
			// leds[33]=CRGB::White;
			// leds[36]=CRGB::White;
			rgb_effects_stage_set(0);
		}
		break;
	}
  
  //if(effects_i<5)
  // {
	// leds[120]=CRGB::White;
	// leds[122]=CHSV(effects_i,255,255);
	// leds[124]=CHSV(eff_ticks,255,255);
	// leds[126]=CHSV(eff_stage*20,255,255);
	// leds[128]=CHSV(pattern_il/10,255,255);
	// leds[(130+rgb_effects_stage)%NUM_LEDS]=CRGB::Red;
	// leds[(132+rgb_effects_stage)%NUM_LEDS]=CRGB::Green;
  // }
  
}