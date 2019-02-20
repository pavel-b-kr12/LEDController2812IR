bool bPause=false;

byte aDelay=0;
byte gDelayH=20;

#ifndef saveMem
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0	, 0	, 0xff},
};
#endif

byte BOTTOM_INDEX = 0;
NUM_LEDS_type CENTER_TOP_INDEX = byte(NUM_LEDS / 2);
byte EVENODD = NUM_LEDS % 2;

#ifndef saveMem
CRGB ledsX[NUM_LEDS];//!opt	 //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
//int ledsX[NUM_LEDS][3];
#endif
//byte gDelay = 20;
byte thisstep = 10;



unsigned long randomShow_next_effN_sw_t=0;

// Define variables used by the sequences.
byte		twinkrate = 100; // The higher the value, the lower the number of twinkles.
byte		thisfade =	  8; // How quickly does it fade? Lower = slower fade rate.
//nscale 					 // Trail behind the LED's. Lower => faster fade.
byte		thishue =	 50; // Starting hue.
byte		thissat =	255; // The saturation, where 255 = brilliant colours.
byte		thisbri =	255; // Brightness of a sequence.
bool		randhue =	  1; // Do we want random colours all the time? 1 = yes.
uint8_t		thisinc =	  1; // Incremental value for rotating hues
int			huediff =	256; // Range of random #'s to use for hue


uint8_t bgH;
uint8_t bgHinc = 0;
uint8_t bgbri = 0;                                        // Brightness of background colour

uint8_t deltahue = 15; // Hue change between pixels.
uint16_t xscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint16_t yscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint8_t maxChanges = 24;                                      // Value for blending between palettes.
uint8_t thisbeat;
uint8_t huerot;
uint8_t palIndex;


uint8_t thiscutoff = 128;
uint8_t allfreq = 32;


uint8_t   numdots =   4;                                     // Number of dots in use.
uint8_t   thisdiff =  16;                                     // Incremental change in hue between each dot.



int8_t thisrot = 1;                                           // Hue rotation speed. Includes direction.
bool thisdir = 0;  // I use a direction variable instead of signed math so I can use it in multiple routines.


//! ifdef tri_sin
int wave1=0;                                                  // Current phase is calculated.
int wave2=0;
int wave3=0;

uint8_t inc1 = 2;                                             // Phase shift. Keep it low, as this is the speed at which the waves move.
uint8_t inc2 = 1;
uint8_t inc3 = -2;

uint8_t lvl1 = 80;                                            // Any result below this value is displayed as 0.
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;

uint8_t mul1 = 20;                                            // Frequency, thus the distance between waves
uint8_t mul2 = 25;
uint8_t mul3 = 22;
//


//static int16_t randStatic;

NUM_LEDS_type idex = 0;		//-LED INDEX (0 to NUM_LEDS-1
int idex16 = 0;
NUM_LEDS_type idex_last = 0;
byte ihue = 0;
byte ibright = 0;
byte isat = 0;
bool bouncedirection = 0;	 //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;		  //-INC VAR FOR SIN LOOPS
byte lcount = 0;			  //-ANOTHER COUNTING VAR

// Palette definitions
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType	currentBlending; //currentBlending = LINEARBLEND;                  // NOBLEND or LINEARBLEND

void (*anim_f)();
void (*anim_f_last)();

#include "UTILITY_FXNS.h"
#include "LED_EFFECT_FUNCTIONS.h"
#include "eff_setA.h"
#include "eff_setB.h"
#include "eff_setAT\aatemplate.h"
#include "eff_setAT\beatwave.h"
#include "eff_setAT\blend_test.h"
#include "eff_setAT\blendwave.h"
#include "eff_setAT\blur_try.h"
#include "eff_setAT\confetti2.h"
#include "eff_setAT\confetti_pal.h"
#include "eff_setAT\easing_test.h"
#include "eff_setAT\dot_beat.h"
#include "eff_setAT\every_n_example.h"
#include "eff_setAT\fill_colours.h"
#include "eff_setAT\fill_grad.h"
#include "eff_setAT\inoise8_fire.h"
#include "eff_setAT\inoise8_mover.h"
#include "eff_setAT\inoise8_pal_demo.h"
#include "eff_setAT\juggle_pal.h"
#include "eff_setAT\lightnings.h"
#include "eff_setAT\matrix_pal_demo.h"
#include "eff_setAT\matrix_ray.h"
#include "eff_setAT\mover.h"
#include "eff_setAT\noise16_1.h"
#include "eff_setAT\noise16_2.h"
#include "eff_setAT\noise16_3.h"
#include "eff_setAT\one_sine_pal.h"
#include "eff_setAT\one_sine_pal_demo.h"
#include "eff_setAT\palettecrossfade.h"
#include "eff_setAT\plasma.h"
#include "eff_setAT\rainbow_beat2.h"
#include "eff_setAT\rainbow_march.h"
#include "eff_setAT\rainbow_march_demo.h"
#include "eff_setAT\ripple_pal.h"
#include "eff_setAT\ripples.h"
#include "eff_setAT\sawtooth.h"
#include "eff_setAT\serendipitous.h"
#include "eff_setAT\sinelon.h"
#include "eff_setAT\three_sin_demo.h"
#include "eff_setAT\three_sin_pal_demo.h"
#include "eff_setAT\two_sin_pal_demo.h"

//------------------------snd
//#include "eff_setAT\fht_log.h"
//#include "eff_setAT\fht_log_ripple.h"

#ifdef eff_setX
	#include "eff_setX.h"
#endif

#ifndef saveMem
void nodo()
{

} //! ifdef tst && serial  -> sendall data, EEPROM
#endif

void change_slot(byte);

void randomSet()
{
#ifdef tst2
Serial.println("randomSet");
#endif
	//anim_f=randomEff;
	
	//effN=random8(1,250);
	realEffN=random8(11,144);
	change_slot(realEffN); //!! random8 range
	
	effSpeed=random8(1,90); //40
	effLength=random8(5,120); //60
	effLength2=random8(5,120); //60
	effRGB=random8(0,effRGB_M);
	effSpeedH=random8(1,90);
	effLengthH=random8(1,90);
		thishue=random8();
	gDelay=random8(2,30);

	bCurrentEff_IsRandom_AndNotSlotN=true;
}

byte effNt=0;
void change_slot(byte effSlot)
{
gDelay = 20;
effRGB=0;

idex=0; idex16 = 0;
thissat = 255;
bouncedirection = 0;
			#ifdef tst2
				Serial.print("slot:"); Serial.println(effSlot);
			#endif
bCurrentEff_IsRandom_AndNotSlotN=false;
 if(effSlot<=9)
 {
 	//effNt=effN;
 	#ifdef save_load_enable
 	load(effSlot); 
 	//effN=effNt;
 	#endif
 }
 else
  switch (effSlot) {
	#include "switch_slot.h"

  case effN_random_endless: //randomEff endless when press btn left 
	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;

	randomSet();
	effN++; //so we stay at same slot, when move left
  break;  

	case effN_animate_to_slot1: //animate settings from current to settings of slot 1
		#ifdef demo_enable
		brandom_demo=false;
		#endif
		banimate=false;

		if(!anim_f) anim_f = rainbow_beat;

		effSpeed_last=effSpeed;
  		effLength_last=effLength;
	break;

  case effN_animate_SW: 
 	banimate=true;
	#ifdef demo_enable
	brandom_demo=false;
	#endif

  	if(!anim_f) anim_f = fillStriped;

  	
  break;

  #ifdef demo_enable

  case effN_random_demo_animated_SW:
	if(brandom_demo && banimate) //! del
	{
		brandom_demo=false;
		banimate=false;
	}
	else
	{
		brandom_demo=true;
		banimate=true;

		random_demo_sw_speed_td_m=30;
		random_demo_sw_speed_td_M=120;
		//! * effSpeed 
		#ifdef tst
		random_demo_sw_speed_td_m=10;
		random_demo_sw_speed_td_M=20;
		#endif
	}
  break;

  case effN_predefined_show_seq:
  	brandom_demo=false;
  	banimate=false;
  break;

  case effN_random_demo_fast_SW:
  case effN_random_demo_SW: //! now not a SWich
	brandom_demo=true;
	banimate=false;
	//if( brandom_demo)
	{
		random_demo_sw_speed_td_m=(effSlot<effN_random_demo_SW)?1: ( 2+effLength/32 ); //*1000
		random_demo_sw_speed_td_M=(effSlot<effN_random_demo_SW)?6: ( 8+effLength/4 ); 
		// random_demo_sw_speed_td_m=8+effLength/32; //*1000
		// random_demo_sw_speed_td_M=10+effLength/4; 
		randomSet();
	}
  break;
  #endif
  
	case effN_random:
	default: //randomEff
		#ifdef default_effN_Randon
		randomSet();
		#else
  		FastLED.clear();
  		#endif
		//effN =0;
	break;
  
 //!	#ifndef saveMem
 //	case 111: one_color_all(255, 0, 0); LEDS.show(); break; //---ALL RED
 //	case 112: one_color_all(0, 255, 0); LEDS.show(); break; //---ALL GREEN
 //	case 113: one_color_all(0, 0, 255); LEDS.show(); break; //---ALL BLUE
 //	case 114: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
 //	case 115: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
 //	case 116: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
	// #endif
  }
  
	if(anim_f!=anim_f_last) //!
	{
		anim_f_last=anim_f;
		//if(anim_f!=animEffContinueRandomShow && anim_f!=animEffContinue)	anim_f_last=anim_f; //for animate settings

		i_eff=0; //strart effect from 0 counter
		
		//saveAfter2s(); // need after eff changed global options - so it will save in slot 0
	}
}

void DisableChennel(int i, byte chen)
{
	if(chen==1 ||chen==4||chen==5)		leds[i].r=0; 
	if(chen==2 ||chen==5||chen==6)		leds[i].g=0;
	if(chen==3 ||chen==6||chen==4)		leds[i].b=0; 
}

long anim_next_t=0;
long animHue_next_t=0;

void LED_anim()
{
	if(bPause) return; //!! ifdef 


//EVERY_N_MILLISECONDS(  )  //not working when argument changed
//  EVERY_N_MILLIS_I(thistimer, gDelay) { //!test
// thistimer.setPeriod(gDelay);

if(millis()>anim_next_t)
{
	anim_next_t=millis()+gDelay;

	#ifdef tstFPS
		if(i_eff%4==0) Serial.println(LEDS.getFPS());
	#endif

	if(banimate)
	{
		effSpeed=beatsin8(4, effSpeed_last/4, effSpeed_last>55?255:(15+effSpeed_last*4) ); //! speed
		effLength=beatsin8(3, 1+effLength_last/4, effLength_last>55?255:(15+effLength_last*4) );
		

		//effSpeed=beatsin8(3, 0, 150 );
  		//effLength=beatsin8(2, 2, 180 );

		//! if(effRGB>0 && effRGB<7) nextSW_t=millis()+10;  else +30
		EVERY_N_MILLISECONDS( 20000 )
		{
			effRGB=random8(0,effRGB_M);
			//effRGB++;
			//if(effRGB>effRGB_M) effRGB=0;
		}
		//effRGB= beatsin8(1, 0, 16);
	}
	// #ifdef tst2
	// 	Serial.println(anim_f==NULL);
	// #endif
	anim_f();

	if(effRGB!=0)
	{
		for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
		{
			if(effRGB==7) DisableChennel(i, 3+(i_eff/16)%3);
			else if(effRGB==8) DisableChennel(i, (i/4)%6);
			else if(effRGB==9) DisableChennel(i, ((i+millis()/(512-effSpeed))/4)%6);
			//else if(effRGB==10)  //! dis each 3rd
			//
			else if(effRGB<=6) DisableChennel(i, effRGB); //0..6  10..16
			else if(effRGB>=10 && effRGB<=16)
			{
			 	DisableChennel(i, effRGB-10); //0..6  10..16
			 	i++;
			}
			else
			{
				//! fadeToBlackBy(leds, NUM_LEDS, 16);
				addGlitter(20);
			}

			//!confetti
			//! black separators, 
			//! black separators moving 
		}
	}
	#ifdef BlueFilter
		for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
			leds[i].b=leds[i].b/8;
	#endif

	FastLED.show();
	i_eff++;	//if(i_eff>effLength) i_eff=0; //!!!#  i_eff%effLength	i_eff_M_is_effLength
} //anim_f(); EVERY_N_MILLISECONDS

//EVERY_N_MILLISECONDS( 20 )
//{
if(millis()>animHue_next_t)
{
	animHue_next_t=millis()+gDelayH;
	gHue+=effSpeed/2;

	#ifdef demo_enable //no show for this hardware
	if(brandom_demo && millis()>randomShow_next_effN_sw_t)
	{
		#ifdef tst2
		Serial.print("brandom_demo"); Serial.println();
		#endif
					
		randomShow_next_effN_sw_t=millis()+random8(random_demo_sw_speed_td_m, random_demo_sw_speed_td_M)*1000;
		randomSet();
	}
	#endif
}
	
}
