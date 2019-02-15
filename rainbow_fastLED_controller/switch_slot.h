 	//!		mark for testing (buton color in GUI)
	//:)	mark best
	//:/	mark experiental, legasy and other stuff that can be skipped
	//oo	effect related to (circular) stripe ring

 	#ifndef saveMem
    case effN_off: anim_f=nodo; FastLED.clear(); break; //---ALL OFF
    #endif
    //case 1: anim_f=fillAll; gColor=CRGB::White;  break; //---ALL ON
    case 11: anim_f=fillStriped;			effSpeed=0;		effLength=10; gColor=CRGB::White; gColorBg=CRGB::Black; break; //:)
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

	case 22: anim_f=rainbow_fill_slow;			effSpeed=10;	effLength=1; break; //---RAINBOW LOOP // slow rainbow fill with shift
	//case 12: anim_f=rainbow_vertical; break; //---VERITCAL RAINBOW (circular)
	
	
	case 23: anim_f=rainbow_beat;			effSpeed=130;	effLength=1; break;	//here and there
	case 24: anim_f=rainbow_beat;			effSpeed=82;	effLength=150; break;	//:)
	
	case 25: anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=5; break;
	case 26: anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=26; break;
	case 27: anim_f=rainbowSegments_shift;	effSpeed=40;	effLength=11; break;
	
	case 28: anim_f=rainbowSegments_shiftSin; break; //i_eff_continued
	//case 29: anim_f=rainbowSegments2; break;

	case 29: anim_f=rainbowCycle; 			effSpeed=44; 	effLength=1;	break;
	case 30: anim_f=rainbowCycle;			effSpeed=35;	effLength=59;	break;

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
	case 61: anim_f=movingBlendRGB;  		effSpeed=169;	effLength=127; break;
	case 62: anim_f=movingBlendRGB_A;		effSpeed=136;	effLength=132; break;

	case 70: anim_f=rgb_propeller;  break; //!! RGB пропеллер //---RGB PROPELLER 
	case 71: anim_f=kitt; effLength=20*16; break;       //---KITT random blink
#ifndef saveMem
	case 72: anim_f=NewKITT;  break;                     // NewKITT (circular) //!fix

	case 73: anim_f=rule30;  break;  //:/ //---CELL AUTO - RULE 30 (RED)      //!slo
#endif
	//TwinkleRandom(20, thisdelay, 1); break;                                
	case 74: anim_f=rainbow_vertical; break; //:/	// rainbowTwinkle 0-all, 1-random 1 //slow fill, shift
	case 75: anim_f=randomBlink; effLength=3; break;

	//!action case 79: Strobe(10, 5, 0); gColor=CRGB(255,255,255);  break;
	case 79: anim_f=Strobe; gColor=CRGB(255,255,255); 	effSpeed=5*16; break;	//:/
#ifndef saveMem
    case 80: anim_f=pulse_one_color_all;  thishue = 0; break;        //---PULSE COLOR BRIGHTNESS single color
    case 81: anim_f=pulse_one_color_all_rev;  thishue = 0; break;    //---PULSE COLOR SATURATION

    case 82: anim_f=fade_vertical;  thishue = 180; break;      //:/ //! //---VERTICAL SOMETHING (circular) bright change

    case 83: anim_f=radiation;  thishue = 95; break;      //:/ //---RADIATION SYMBOL

    case 84: anim_f=white_temps; break;	//:/
    case 85: anim_f=sin_bright_wave;  thishue = 180; break;   //:/	//---SIN WAVE BRIGHTNESS //fix 
    //case 86: anim_f=pop_horizontal;  break;      //!fix 		//---POP LEFT/RIGHT moving LED
    case 87: anim_f=quad_bright_curve;		effSpeed=0;	effLength=17; break;  //:/		//---QUADRATIC BRIGHTNESS CURVE / полумесяц
    case 88: anim_f=flame; break;
    case 89: anim_f=Fire; 			effSpeed=22; effLength=75; break;          //:)  //! R-G swap

    //case 89: anim_f=pacman;  break;    //fix move                 //---PACMAN
    case 90: anim_f=BouncingColoredBalls;			effSpeed=16; effLength=3; break;    //!! ret, ballColors // прыгающие мячики
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

    case 101: anim_f=Twinkle;					break;
    case 102: anim_f=beatWave;					break;



    

//==============================================================================================================================
#ifdef eff_setX
	case 160: anim_f=testPower;					effSpeed=10;	effLength=24; break;	//:/	//E, setBrightness
	case 161: anim_f=test_gDelay;				effSpeed=40;	 break;	//:/
	case 165: anim_f=iterateRAWint; break;	//:/
#endif

//==============================================================================================================================
	case 211: anim_f=fillStriped;				effSpeed=45;	effLength=186;	effDisableChennel=8;	break;
	case 239: anim_f=fadeEvenUneven;			effSpeed=84;		effLength=70;		effDisableChennel=2; break; //!

//max N is 240