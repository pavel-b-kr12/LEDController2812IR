bool bPause=false;
byte gDelay=20;

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
#include "eff_setB.h"

#ifdef eff_setX
	#include "eff_setX.h"
#endif

#ifndef saveMem
void nodo()
{

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
	if(chen==1 ||chen==4||chen==5)		leds[i].r=0; 
	if(chen==2 ||chen==5||chen==6)		leds[i].g=0;
	if(chen==3 ||chen==6||chen==4)		leds[i].b=0; 
}

long anim_next_t=0;
long animHue_next_t=0;
byte gDelayH=20;

void LED_anim()
{
	if(bPause) return; //!! ifdef 

//EVERY_N_MILLISECONDS(  )  //not working when argument changed
//  EVERY_N_MILLIS_I(thistimer, gDelay) { //!test
// thistimer.setPeriod(thisdelay);

if(millis()>anim_next_t)
{
    anim_next_t=millis()+gDelay;
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
			leds[i].b=leds[i].b/8;
	#endif

	FastLED.show();
	i_eff++;	//if(i_eff>effLength) i_eff=0; //!!!#  i_eff%effLength   i_eff_M_is_effLength
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
