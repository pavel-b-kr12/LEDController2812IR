byte aDelay=0;
byte gDelayH=20;

#ifndef saveMem
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0	, 0	, 0xff},
};
#endif


#ifndef saveMem
CRGB ledsX_[gNUM_LEDS];//!opt	 //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
//int ledsX_[NUM_LEDS][3];
#endif

#include "eff__variables.h"

void (*anim_f)();
void (*anim_f_last)();

#include "UTILITY_FXNS.h"


#include "common_f.h" 
#include "eff_common.h" //independent functions, no need any var
#include "eff_set_sys.h"

#include "LED_EFFECT_FUNCTIONS.h"
#include "eff_setFastLED.h"
#include "eff_setA.h"
#include "eff_setB.h"
#include "eff_set_Wave.h"
#include "eff_set2.h"
#include "eff_set_cel.h"
#include "eff_set_interactive.h"


#ifdef WiFi_SEND
	void test_RF(){ fill_rainbow( leds, NUM_LEDS, i_eff, NUM_LEDS); } //# ifdef  wifi
#endif

#ifdef Cube4MCU
	#include "eff_set_Cube.h"
#endif


 int step = -1;
#ifdef sound_p
#define MIC_PIN sound_p
#define DC_OFFSET  0                                          // DC offset in mic signal - if unusure, leave 0
unsigned int sample = 0;

//uint16_t loops = 0;                                                             // Our loops per second counter.

// Global sound variables used in other routines.
uint16_t oldsample = 0;                                                         // Previous sample is used for peak detection and for 'on the fly' values.
bool     samplepeak = 0;                                                        // The oldsample is well above the average, and is a 'peak'.
uint16_t sampleavg = 0;                                                         // Average of the last 64 samples.



#include "eff_set_Sound\mus_random_mov.h"

#include "eff_set_Sound\soundmems_peak_ripple.h"
#include "eff_set_Sound\soundmems_wave.h"
 
#include "eff_set_Sound\mus_arduinoFFT.h"

#include "eff_set_Sound\soundmems\_soundmems.h"
#include "eff_set_Sound\soundmems\soundmems_fire.h"

#include "eff_set_Sound\soundmems_noise.h"
#include "eff_set_Sound\soundmems_pal.h"
#endif

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

#include "eff_set_3\fire.h"
#include "eff_set_3\firework1000.h"

#ifdef MATRIX_ROWS //!!##
 #include "eff_matrix.h"
#endif
#ifdef NUMMATRIX
 #include "eff_set_matrix_text.h"
#endif
#ifdef MATRIXfonth
 #include "eff_set_matrix_RU_font.h"
#endif

#ifdef PWM_enabled
#include "eff_set_PWM_Dimmer.h"
#endif
#ifdef PinSequencer_enabled
#include "eff_set_PinSequencer.h"
#endif
#ifdef mode_switch_enabled
#include "eff_mode_switch.h"
#endif



#include "eff_set_wand.h" //it uses effect from above includes //! include?

#include "eff_kit_DemoReel100m.h"

#ifdef eff_setX
	#include "eff_setX.h"
	#include "eff_set_Edges.h"
#endif



//------------------------snd
//#include "eff_setAT\fht_log.h" //for atm328
//#include "eff_setAT\fht_log_ripple.h"



#ifdef remap_LEDs
	byte bMap_type=0;
	#define bMap_type_matrix_			241 //! have to be in sync with gui.pde / btn_matrix_zigZag_h_click  and HTML_settings.htm
	#define bMap_type_matrix_zigZag_h	242
	#define bMap_type_matrix_spiral_cw	243
	#define bMap_type_matrix_labyrinth_cw	244
	#define bMap_type_mirror_half	245
	#define bMap_type_history	246 // every n ms shift matrix rows and fill 1st with LEDs
	#ifdef MATRIX_ROWS

	#endif
	bool bSwapLEDs=false;
	CRGB leds_out[NUM_LEDS];
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
	#ifdef ESP32_HTML_NO_RENDER
		gDelay=random8(5,20);
	#else
		gDelay=random8(0,30);
	#endif

	bCurrentEff_IsRandom_AndNotSlotN=true;
#if defined(tst) || defined(SerialControl)|| defined(SerialSelect)|| defined(LCD2004_i2c)|| defined(keypad1602)
	display_upd();
#endif
}

byte effNt=0;
void change_slot(byte effSlot)
	{
		#ifdef off_change_slot_After2min
			if(millis()>2*60*1000) return;
		#endif

	effRGB=0;
	gDelay=5; //!tst //0 good always when #define gDelayMore to avoid serial bandwidth bug
	idex=0; idex16 = 0;
	thissat = 255;
	thisdir = 0;
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
		#include switch_slot_FILE_H

//this N related to button in USB app
#define effN_off 10 //clear, nodo()
	
#define effN_random_endless 248 //endless while press btn --
#define effN_random 249 
#define effN_animate_to_slot1 251
#define effN_animate_SW 252 

#ifdef demo_enable
#define effN_random_demo_animated_SW 250  //effN_animate_SW & effN_random_demo_SW
#define effN_predefined_show_seq 253
#define effN_random_demo_fast_SW 254 
#define effN_random_demo_SW 255 //del to disable
#endif



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
			#ifdef default_effN_Random
			randomSet();
			#else
			FastLED.clear();
								anim_f=fillStriped; //## if not defined default_effN_Random  is NULL
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
  
											if(!anim_f) anim_f = fillStriped;


	if(anim_f!=anim_f_last) //!
	{
		#ifndef saveMem
		 if(effN>=240 &&effN<=245) //!!!upd  //this slots does not change eff, but have to be named for USB app, so temporary solution
		 {
		 	anim_f=anim_f_last;
		 }
		 else
		#endif
		anim_f_last=anim_f;
		//if(anim_f!=animEffContinueRandomShow && anim_f!=animEffContinue)	anim_f_last=anim_f; //for animate settings

		i_eff=0; //strart effect from 0 counter
		
		//saveAfter2s(); // need after eff changed global options - so it will save in slot 0
	}


				// #ifdef tst2
				//	Serial.print("slot changed"); 
				//	Serial.print(anim_f==NULL); 

				//	Serial.println(effSlot);
				// #endif
}



long animHue_next_t=0;

void DisableChennel(int i, byte chen) //!! move to file
{
	if(chen==1 ||chen==4||chen==5)	leds[i].r=0; 
	if(chen==2 ||chen==5||chen==6)	leds[i].g=0;
	if(chen==3 ||chen==6||chen==4)	leds[i].b=0; 
}
void re_effRGB()
{
	if(effRGB!=0)  //!! move to file
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
			if(effRGB==17)
			{
				//! fadeToBlackBy(leds, NUM_LEDS, 16);
				addGlitter(20);
			}
			else
			if(effRGB==18)
			{
				addGlitter(effLength/16);
			}
			else
			if(effRGB==19)
			{
				fadeToBlackBy(leds, NUM_LEDS, effLength/32);
				addGlitter(effLength/16);
			}
			else
			if(effRGB==20)
			{
				addGlitterBlack(effLength/4);
			}
			//!confetti
			//! black separators, 
			//! black separators moving 
			//! gFade
		}
	}
}


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

		uint8_t *p;
						// PRINT__
						// PRINT_tst
						// Serial.write(sizeof("bPrintPixels: ")+3);
						// Serial.print("bPrintPixels: ");			Serial.println(bPrintPixels);

		PRINT__ //do not serial.print debug stuff inside

		if(bPrintPixels) //! move to  loop end, after anim and post proc
		{
			#ifdef gDelayMore
				anim_next_t+=gDelayMore;
			#endif
												
			PRINT_leds

			#if defined(LEDs_RENDER)
				uint16_t fps=LEDS.getFPS();
			#else
				uint16_t fps=0; //!!//#
			#endif
			p = (uint8_t*) &fps;
			Serial.write(p,2);


			uint16_t size=NUM_LEDS*3; //! NUM_LEDS range
			p = (uint8_t*) &size;
			Serial.write(p,2);
			Serial.write((uint8_t*)leds, size);
		}
		else //if(i_eff%4==0)  //print only FPS and totall power
		{
			PRINT_totall

			#if defined(LEDs_RENDER)
				uint16_t fps=LEDS.getFPS();
			#else
				uint16_t fps=0; //!!//#
			#endif
			p = (uint8_t*) &fps;
			Serial.write(p,2);


			//#include "power_mgt.h" //? nw as FastLED.calculate_unscaled_power_mW		http://fastled.io/docs/3.1/power__mgt_8cpp_source.html
			//Serial.println(calculate_unscaled_power_mW (leds, NUM_LEDS)); //* FastLED.getBrightness()/256  this done in GUI
			const CRGB* firstled = &(leds[0]);
			uint8_t* p = (uint8_t*)(firstled);
			uint16_t count = NUM_LEDS*3;
			uint32_t totall=0;

			while(count)
			{ // This loop might benefit from an AVR assembly version -MEK
				totall += *p++;
				count--;
			}
			totall/=256; //!
			p = (uint8_t*) &totall;
			Serial.write(p,2);
		}

	#endif
#ifndef only1eff
	if(banimate) //## define
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
									 #ifdef tst2
										Serial.print(anim_f==NULL);	Serial.print("NUM_LEDS: "); Serial.print(NUM_LEDS);	Serial.print(" gNUM_LEDS: ");Serial.println(gNUM_LEDS);
									 #endif
	#ifdef MATRIX_ROWS
		if(bSwapLEDs)
		{
			bSwapLEDs=false;
			memcpy8( &leds_out[0],	&leds[0], NUM_LEDS*3 ); //!!opt TODO avoid douple copy and copy at all
		}
	#endif
#endif
	anim_f();

//#ifndef only1eff
//--------------------------------------------------------------- post processing
re_effRGB();

//#endif



#ifdef remap_LEDs
#ifdef MATRIX_ROWS
	#define LEDs_per_row NUM_LEDS/MATRIX_ROWS
#endif

 switch(bMap_type)
 {
 	#ifdef MATRIX_ROWS
	case bMap_type_matrix_zigZag_h: //@ https://github.com/FastLED/FastLED/blob/master/examples/XYMatrix/XYMatrix.ino
		{
			for(byte row=1;row<MATRIX_ROWS; row+=2) //reverse odd rows
			{
				NUM_LEDS_type len=LEDs_per_row/2;
				NUM_LEDS_type x0=row*LEDs_per_row;
				NUM_LEDS_type x9=(row+1)*LEDs_per_row-1;
				
				for(NUM_LEDS_type x=0; x<len; x++)
				{
					CRGB c=leds[x0+x];
					leds[x0+x]=leds[x9-x];
					leds[x9-x]=c;
				}
				//##TODO if !bMapInPlace memcpy8( &leds_out[0],	&leds[0], NUM_LEDS*3 );
			}
		}
								// leds[0]=CRGB::Blue;
								// leds[1]=CRGB::Blue;
	break;
	case bMap_type_matrix_spiral_cw:
		{																	memset(leds_out, 0, NUM_LEDS * 3); //clear
			NUM_LEDS_type matrix_px_per_row=NUM_LEDS/MATRIX_ROWS;
			for(NUM_LEDS_type i=0, spiralCurrentSquareN=0, i_Square=0;i< NUM_LEDS; i++,i_Square++) //reverse odd rows
			{
				NUM_LEDS_type px_per_Square_side=matrix_px_per_row-1-spiralCurrentSquareN*2;
				NUM_LEDS_type col_s=0, row_s=0;

				if (i_Square<px_per_Square_side)
				{
					col_s=i_Square +spiralCurrentSquareN;
			 		row_s=0+spiralCurrentSquareN;

				}
				else
				if (i_Square<px_per_Square_side*2)
				{
					col_s=matrix_px_per_row-1 -spiralCurrentSquareN;
			 		row_s=i_Square%px_per_Square_side +spiralCurrentSquareN;

				}
				else
				if (i_Square<px_per_Square_side*3)
				{
					col_s=matrix_px_per_row-1-i_Square%px_per_Square_side -spiralCurrentSquareN;
			 		row_s=matrix_px_per_row-1 -spiralCurrentSquareN;

				}
				else
				if (i_Square<px_per_Square_side*4)
				{
					col_s=0 +spiralCurrentSquareN;
			 		row_s=matrix_px_per_row-1-i_Square%px_per_Square_side -spiralCurrentSquareN;
			 		if(i_Square==px_per_Square_side*4-1) 
			 		{
			 			spiralCurrentSquareN++;
i_Square=-1;
			 		}
				}
				else continue; //? why can't 'break' it stop on 4th size start

				{
					#ifndef bZigZag
						leds_out[row_s*LEDs_per_row+col_s]=leds[i];
					#else
						NUM_LEDS_type ii;
						if(row_s%2)
						{
							ii=LEDs_per_row-1-col_s;
						}
						else ii=col_s;

						leds_out[row_s*LEDs_per_row+ii]=leds[i];
					#endif
				}

			}
			bSwapLEDs=true;
			memcpy8( &leds[0],	&leds_out[0], NUM_LEDS*3 );
		}
								// leds[0]=CRGB::Red;
								// leds[1]=CRGB::Red;
	break;

	case bMap_type_matrix_labyrinth_cw:
		{
			memset(leds_out, 0, NUM_LEDS * 3); //clear


			NUM_LEDS_type matrix_px_per_row=NUM_LEDS/MATRIX_ROWS;
			for(NUM_LEDS_type i=0, spiralCurrentSquareN=0, i_Square=0;i< NUM_LEDS; i++) //reverse odd rows
			{
				if(spiralCurrentSquareN*2 > matrix_px_per_row-1) break;
				NUM_LEDS_type px_per_Square_side=matrix_px_per_row-1-spiralCurrentSquareN*2;

				NUM_LEDS_type col_s=0, row_s=0;

				if (i_Square<px_per_Square_side)
				{
					col_s=i_Square +spiralCurrentSquareN;
			 		row_s=0+spiralCurrentSquareN;
			 		i_Square++;
				}
				else
				if (i_Square<px_per_Square_side*2)
				{
					col_s=matrix_px_per_row-1 -spiralCurrentSquareN;
			 		row_s=i_Square%px_per_Square_side +spiralCurrentSquareN;
			 		i_Square++;
				}
				else
				if (i_Square<px_per_Square_side*3)
				{
					col_s=matrix_px_per_row-1-i_Square%px_per_Square_side -spiralCurrentSquareN;
			 		row_s=matrix_px_per_row-1 -spiralCurrentSquareN;
			 		i_Square++;
				}
				else
				if (i_Square<px_per_Square_side*4-1)
				{
					col_s=0 +spiralCurrentSquareN;
			 		row_s=matrix_px_per_row-1-i_Square%px_per_Square_side -spiralCurrentSquareN;
			 		i_Square++;
				}
				else
				if (i_Square==px_per_Square_side*4-1)
				{
					col_s=0 +spiralCurrentSquareN+1;
					row_s=matrix_px_per_row-1-(i_Square-1)%px_per_Square_side -spiralCurrentSquareN;

			 		{
			 			spiralCurrentSquareN+=2;
			 			i_Square=0;
			 			//i_Square=-1; //-1 because it ++ in for and have to be 0 at start of next square //can't because unsigned
			 		}

				}
				else break;

				{
					#ifndef bZigZag
						leds_out[row_s*LEDs_per_row+col_s]=leds[i];
					#else
						NUM_LEDS_type ii;
						if(row_s%2)
						{
							ii=LEDs_per_row-1-col_s;
						}
						else ii=col_s;

						leds_out[row_s*LEDs_per_row+ii]=leds[i];

					#endif
				}


			}
			bSwapLEDs=true;
			memcpy8( &leds[0],	&leds_out[0], NUM_LEDS*3 );
		}
								// leds[0]=CRGB::Red;
								// leds[1]=CRGB::Red;
	break;


	#endif

	case bMap_type_mirror_half:
		{
			NUM_LEDS_type E=NUM_LEDS/2;
			NUM_LEDS_type x0=E;
			NUM_LEDS_type x9=NUM_LEDS-1;

			for(NUM_LEDS_type x=0; x<E/2; x++) //reverse last half
			{
				CRGB c=leds[x0+x];
				leds[x0+x]=leds[x9-x];
				leds[x9-x]=c;
			}
		}
								// leds[0]=CRGB::Black;
								// leds[1]=CRGB::Black;
	break;

 }
#endif

	#ifdef BlueFilter
		for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)		leds[i].b=leds[i].b/8;
	#endif
	//--------------------------------------------------------------- 

	#if defined(LEDs_RENDER)
		#ifndef NUMMATRIX
			FastLED_show_DIRECTION //dir FastLED.show(); dir
		#else
			matrix->show();
		#endif
		//!! show_at_max_brightness_for_power();
		// Serial.println(LEDp); Serial.println(leds[0].r); 
	#endif
	#if defined(WiFi_SEND)
		send_LEDs_over_WiFi();
	#endif

	i_eff++;	//if(i_eff>effLength) i_eff=0; //!!!#  i_eff%effLength	i_eff_M_is_effLength
} //anim_f(); EVERY_N_MILLISECONDS
else
{
	//! https://github.com/FastLED/FastLED/wiki/FastLED-Temporal-Dithering
}

//EVERY_N_MILLISECONDS( 20 )
//{
if(millis()>animHue_next_t)
{
	animHue_next_t=millis()+gDelayH;
	gHue+=effSpeed/2; //TODO move to each eff or iEff

	#ifdef demo_enable //no show for this hardware
	if(brandom_demo && millis()>randomShow_next_effN_sw_t)
	{
						#ifdef tst2
						Serial.println("brandom_demo");
						#endif
		randomShow_next_effN_sw_t=millis()+random8(random_demo_sw_speed_td_m, random_demo_sw_speed_td_M)*1000;
		randomSet();
	}
	#endif
}
	
}
