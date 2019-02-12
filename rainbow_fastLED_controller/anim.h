bool bPause=false;

#ifndef saveMem
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff},
};
#endif

byte BOTTOM_INDEX = 0;
NUM_LEDS_type CENTER_TOP_INDEX = byte(NUM_LEDS / 2);
byte EVENODD = NUM_LEDS % 2;

#ifndef saveMem
CRGB ledsX[NUM_LEDS];//!opt     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
//int ledsX[NUM_LEDS][3];
#endif
//byte thisdelay = 20;          //-FX LOOPS DELAY VAR
byte thisstep = 10;           //-FX LOOPS DELAY VAR
byte thishue = 0;             //-FX LOOPS DELAY VAR
byte thissat = 255;           //-FX LOOPS DELAY VAR

NUM_LEDS_type idex = 0;       //-LED INDEX (0 to NUM_LEDS-1
NUM_LEDS_type idex_last = 0;  //-LED INDEX (0 to NUM_LEDS-1
byte ihue = 0;                //-HUE (0-255)
byte ibright = 0;             //-BRIGHTNESS (0-255)
byte isat = 0;                //-SATURATION (0-255)
bool bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
byte lcount = 0;              //-ANOTHER COUNTING VAR

void (*anim_f)();
void (*anim_f_last)();

#include "UTILITY_FXNS.h"
#include "LED_EFFECT_FUNCTIONS.h"
#include "eff_setA.h"

#ifndef saveMem
void nodo()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
  	leds[i] =millis()*effSpeed*4+i*effLength*4;  // i*(int)(millis()/2000);
  }
  FastLED.show();

} //! ifdef tst && serial  -> sendall data, EEPROM
#endif

void change_mode(byte);

void randomSet()
{
#ifdef tst2
Serial.println("randomSet");
#endif
	//anim_f=randomEff;
   
   //effN=random8(1,250);
	realEffN=random8(11,90);
   change_mode(realEffN); //!! random8 range
   
	effSpeed=random8(1,90); //40
	effLength=random8(5,120); //60
	effLength2=random8(5,120); //60
	effDisableChennel=random8(0,effDisableChennel_M);
	effSpeedH=random8(1,90);
	effLengthH=random8(1,90);
		thishue=random8();
	//thisdelay=random8(2,30);

	bCurrentEff_IsRandom_AndNotSlotN=true;
}

byte effNt=0;
void change_mode(byte newmode)
{
effDisableChennel=0;

idex=0;
thissat = 255;
bouncedirection = 0;
			#ifdef tst2
				Serial.print("newmode="); Serial.println(newmode);
			#endif
bCurrentEff_IsRandom_AndNotSlotN=false;
 if(newmode<=9)
 {
 	//effNt=effN; 
 	load(newmode); 
 	//effN=effNt;
 }
 else
  switch (newmode) {
  	#ifndef saveMem
    case effN_off: anim_f=nodo; fillBlack(); break; //---ALL OFF
    #endif
    //case 1: anim_f=fillAll; gColor=CRGB::White;  break; //---ALL ON
    case 11: anim_f=fillStriped;			effSpeed=0;		effLength=10; gColor=CRGB::White; gColorBg=CRGB::Black; break;
    case 12: anim_f=fillStripedFillRainbow; effSpeed=70; 	effLength=70; gColor=CRGB::White; break;
	case 13: anim_f=rainbow;				effSpeed=6;		effLength=8; break;
	case 14: anim_f=rainbowConfetti;		effSpeed=4;		effLength=14;break;
	case 15: anim_f=rainbowWithGlitter;		effSpeed=20;	effLength=14;break;
	//15 11 217 9
	//15 5 71 7
	case 16: anim_f=rainbow_beat;			effSpeed=4;		effLength=14;break;

	case 17: anim_f=randomBlinkRainbow; break;
	case 18: anim_f=randomBlinkRainbowFade;	effSpeed=99;	effLength=155; break;

	case 19: anim_f=rainbowSpawn_moveFromStartWithSeparators; break; //!
	case 20: anim_f=rainbowSpawn_moveFromStartWithSeparatorsB; break; //!
#ifndef saveMem
	case 21: anim_f=rainbow_fade;			effSpeed=13;	effLength=14; break;	//Hue on all or rare LEDs
#endif

	case 22: anim_f=rainbow_loop;			effSpeed=10;	effLength=1; break; //---RAINBOW LOOP // slow rainbow fill with shift
	//case 12: anim_f=rainbow_vertical; break; //---VERITCAL RAINBOW (circular)
	
	
	case 23: anim_f=rainbow_beat;			effSpeed=130;	effLength=1; break; //here and there
	case 24: anim_f=rainbow_beat;			effSpeed=82;	effLength=150; break; //here and there
	
	case 25: anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=5; break;
	case 26: anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=26; break;
	case 27: anim_f=rainbowSegments_shift;	effSpeed=40;	effLength=11; break;
	
	case 28: anim_f=rainbowSegments_shiftSin; break; //i_eff_continued
	//case 29: anim_f=rainbowSegments2; break;

	case 30: anim_f=rainbowCycle; 			effSpeed=44; 	effLength=1;break;      // rainbowCycle

	case 31: anim_f=sinelon;				effSpeed=10; 	effLength=28; break;	//moving, fade
	case 32: anim_f=bpm;					effSpeed=3;		effLength=62; break;	//move here-there
	case 33: anim_f=juggle;					effSpeed=20;	effLength=32; break;	//multiple moving, fade
	case 34: anim_f=spawnPixel_moveAll;		effSpeed=55;	effLength=6; break;

#ifndef saveMem
	case 35: anim_f=fillFadeChangeAll;		effLength=237; break;			//flash over effLength
#endif
	case 36: anim_f=fillFadeChangeAll_beat8;	effSpeed=30; effLength=200; break;	//flash over effLength
	case 37: anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=22;  break;	//flash under effLength // effLength = 22 , so it can change color
	case 38: anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=127; break;	//flash under effLength

	case 39: anim_f=fadeEvenUneven;			effSpeed=25;	effLength=114;  break;
	case 40: anim_f=fadeEvenUnevenDif;		effSpeed=16;	effLength=30;  break;	//effLength is speed
	
	
	
	//------- random
	case 41: anim_f=confetti;				effSpeed=45;	effLength=6; break;
	case 42: anim_f=confetti;				effSpeed=178;	effLength=8; break;
	case 44: anim_f=random_color_pop; break;										//fast ---RANDOM COLOR POP 
	case 43: anim_f=random_burst;			effSpeed=84;	effLength=120; break;	//---RANDOM BURST
	

#ifndef saveMem
	case 46: anim_f=flicker; break;		//---STRIP FLICKER random
#endif

	case 47: anim_f=color_bounce;			effSpeed=16;	effLength=62; break;        //---CYLON v1 moving LED
	case 48: anim_f=color_bounc_HueByPos;	effSpeed=6;		effLength=42; break;        // hue by pos
	case 49: anim_f=color_bounc_HueByPos;	effSpeed=45;	effLength=255; break;
#ifndef saveMem
	case 50: anim_f=color_bounce_multiple;	effSpeed=16;	effLength=17; break;

	case 51: anim_f=color_bounceFADE; 		effSpeed=0;		effLength=33; break;         //---CYLON v2 moving LED group	//effSpeed effLength - are colors
	case 52: anim_f=CylonBounce; 			effSpeed=96;	effLength=65; break;		//moving group
#endif
	case 53: anim_f=RunningLights; effSpeed=123; break; //!!
#ifndef saveMem
	case 54: anim_f=ems_lightsONE;		thishue = 0; break;			//---POLICE LIGHTS SINGLE
	case 55: anim_f=ems_lightsALL;		 break;			//---POLICE LIGHTS SOLID //cycle around
	case 56: anim_f=ems_lightsSTROBE;	 break;			//---EMERGECNY STROBE

	case 57: anim_f=color_loop_vardelay;	effSpeed=255;	effLength=255; break;	//<126 switch colorize

	case 58: anim_f=matrix;  break;       //---MATRIX RAIN  random
	case 59: anim_f=rwb_march;  break;      //!slo      //---MARCH RWB COLORS moving (circular) //<125 <200  switch colorize
	case 60: anim_f=random_march;  break;    //!slo     //---MARCH RANDOM COLORS random

#endif
	case 70: anim_f=rgb_propeller;  break; //!! RGB пропеллер //---RGB PROPELLER 
	case 71: anim_f=kitt; effLength=20*16; break;       //---KITT random blink
#ifndef saveMem
	case 72: anim_f=NewKITT;  break;                     // NewKITT (circular) //!fix

	case 73: anim_f=rule30;  break;  //---CELL AUTO - RULE 30 (RED)      //!slo
#endif
	//TwinkleRandom(20, thisdelay, 1); break;                                
	case 74: anim_f=rainbow_vertical; break; // rainbowTwinkle 0-all, 1-random 1 //slow fill, shift
	case 75: anim_f=randomBlink; effLength=3; break;

	//!action case 79: Strobe(10, 5, 0); gColor=CRGB(255,255,255);  break;
	case 79: anim_f=Strobe; gColor=CRGB(255,255,255); 	effSpeed=5*16; break;
#ifndef saveMem
    case 80: anim_f=pulse_one_color_all;  thishue = 0; break;        //---PULSE COLOR BRIGHTNESS single color
    case 81: anim_f=pulse_one_color_all_rev;  thishue = 0; break;    //---PULSE COLOR SATURATION

    case 82: anim_f=fade_vertical;  thishue = 180; break;      //---VERTICAL SOMETHING (circular) bright change

    case 83: anim_f=radiation;  thishue = 95; break;       //---RADIATION SYMBOL
  
    case 84: anim_f=white_temps; break;
    case 85: anim_f=sin_bright_wave;  thishue = 180; break;   //---SIN WAVE BRIGHTNESS //fix 
    //case 86: anim_f=pop_horizontal;  break;      //!fix 		//---POP LEFT/RIGHT moving LED
    case 87: anim_f=quad_bright_curve;		effSpeed=0;	effLength=17; break;  		//---QUADRATIC BRIGHTNESS CURVE / полумесяц
    case 88: anim_f=flame; break;
    case 89: anim_f=Fire; 			effSpeed=22; effLength=75; break;          // Fire  //! R-G swap

    

    //case 89: anim_f=pacman;  break;    //fix move                 //---PACMAN
    //case 90: anim_f=BouncingColoredBalls;			effSpeed=16; effLength=3; break;    //!! ret, ballColors // прыгающие мячики
		//  case 98: //BouncingBalls(0xff, 0, 0, 3); break;                   //fix ret

	// case 91:  break;                    //---MARCH STRIP NOW CCW //strip_march_ccw(); break; //!       // move current ccw
	// case 92:  break;                    //---MARCH STRIP NOW CCW//strip_march_cw(); break;   //!       // move current cw
	//case 93: colorWipe(thisdelay); gColor=CRB(0,0,0);  break;   // colorWipe //colorWipe(0x00, 0xff, 0x00, thisdelay); //!fix re 

	//case 94: Sparkle(thisdelay);gColor=CRB(255,255,255);  break;                      // Sparkle // случайные вспышки
	//case 95: SnowSparkle(thisdelay, random(100, 1000)); gColor=CRB(10,10,10);   break;  //!! SnowSparkle wuth background
	//case 96: theaterChase(0xff, 0, 0, thisdelay); break;  // theaterChase //бегущие каждые 3 (NUM_LEDS ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)
	//case 97: //theaterChaseRainbow(thisdelay);  break;   // theaterChaseRainbow //fix ret  //бегущие каждые 3 радуга (NUM_LEDS ДОЛЖНО БЫТЬ КРАТНО 3)


	// case 888: anim_f=demo_modeA; break;             // short
	// case 889: anim_f=demo_modeB; break;             // long

	//effN, spd, , length, , RGB, , time to from start to end value
	//case 100: animEff(2, 0,255, 7,7, 0,0, 15); break;

	//effN, spd, , length, , RGB, , time to from start to end value, time to do 
	//case 101: animEffContinue(2, 11,11, 2,55, 0,0, 5, 18); break;
  
  #endif

	case 111: anim_f=fillStriped;				effSpeed=45;	effLength=186;	effDisableChennel=8;	break;

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
		random_demo_sw_speed_td_m=(newmode<effN_random_demo_SW)?1: ( 2+effLength/32 ); //*1000
		random_demo_sw_speed_td_M=(newmode<effN_random_demo_SW)?6: ( 8+effLength/4 ); 
		// random_demo_sw_speed_td_m=8+effLength/32; //*1000
		// random_demo_sw_speed_td_M=10+effLength/4; 
		randomSet();
	}
  break;
  #endif
  
   case effN_random:
   default: //randomEff //##
	randomSet();
  		 //FastLED.clear();
   		//effN =0;
   break;
  
 //!   #ifndef saveMem
 //    case 111: one_color_all(255, 0, 0); LEDS.show(); break; //---ALL RED
 //    case 112: one_color_all(0, 255, 0); LEDS.show(); break; //---ALL GREEN
 //    case 113: one_color_all(0, 0, 255); LEDS.show(); break; //---ALL BLUE
 //    case 114: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
 //    case 115: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
 //    case 116: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
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
	if(chen==1 ||chen==4||chen==5)
		leds[i].r=0; 
	if(chen==2 ||chen==5||chen==6)
		leds[i].g=0;
	if(chen==3 ||chen==6||chen==4)
		leds[i].b=0; 
}

void LED_anim()
{
	if(bPause) return; //!! ifdef 

EVERY_N_MILLISECONDS( 20 ) //anim_d //+thisdelay
{
	if(banimate)
	{
		effSpeed=beatsin8(4, effSpeed_last/4, effSpeed_last>55?255:(15+effSpeed_last*4) ); //! speed
		effLength=beatsin8(3, 1+effLength_last/4, effLength_last>55?255:(15+effLength_last*4) );
		

		//effSpeed=beatsin8(3, 0, 150 );
  		//effLength=beatsin8(2, 2, 180 );

		//! if(effDisableChennel>0 && effDisableChennel<7) nextSW_t=millis()+10;  else +30
		EVERY_N_MILLISECONDS( 20000 )
		{
			effDisableChennel=random8(0,effDisableChennel_M);
			//effDisableChennel++;
			//if(effDisableChennel>effDisableChennel_M) effDisableChennel=0;
		}
		//effDisableChennel= beatsin8(1, 0, 16);
	}

anim_f();

if(effDisableChennel!=0)
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		if(effDisableChennel==7) DisableChennel(i, 3+(i_eff/16)%3);
		else if(effDisableChennel==8) DisableChennel(i, (i/4)%6);
		else if(effDisableChennel==9) DisableChennel(i, ((i+millis()/(512-effSpeed))/4)%6);
		//else if(effDisableChennel==10)  //! dis each 3rd
		//
		else if(effDisableChennel<=6) DisableChennel(i, effDisableChennel); //0..6  10..16
		else if(effDisableChennel>=10 && effDisableChennel<=16)
		{
		 	DisableChennel(i, effDisableChennel-10); //0..6  10..16
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
 {
 	leds[i].b=leds[i].b/10;
 }
#endif

FastLED.show();
i_eff++;	//if(i_eff>effLength) i_eff=0; //!!!#  i_eff%effLength   i_eff_M_is_effLength
} //anim_f(); EVERY_N_MILLISECONDS

EVERY_N_MILLISECONDS( 20 ) //anim_d
{
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
