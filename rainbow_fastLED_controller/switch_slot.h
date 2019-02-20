// to case rename, reorder or disable|enable use: https://github.com/pavel-b-kr12/switch_case_reName_reOrder

//!			mark for testing or need fix (buton color in GUI)
//:)		mark best
//:/		experiental, legasy and other stuff that can be skipped
//oo		effect related to (circular) stripe ring
//168 328	mark to generate include resticted to memory

//multiplicative value means there is division in effect

case effN_off:anim_f=nodo; FastLED.clear(); break; //---ALL OFF //not168

//case 1:anim_f=fillAll; gColor=CRGB::White;	break; //---ALL ON

case 11:anim_f=fillStriped;			effSpeed=0;		effLength=10; gColor=CRGB::White; gColorBg=CRGB::Black; break; //:)
case 12:anim_f=fillStripedFillRainbow; effSpeed=70; 	effLength=70; gColor=CRGB::White; break;
case 13:anim_f=fillStripedFillRainbow;				effSpeed=70;		effLength=70;		effRGB=14; break; //not168 not328
case 14:anim_f=rainbow;				effSpeed=6;		effLength=8; break;
case 15:anim_f=rainbowConfetti;		effSpeed=4;		effLength=14;break;
case 16:anim_f=rainbowWithGlitter;		effSpeed=20;	effLength=14;break;
//15 11 217 9
//15 5 71 7
case 17:anim_f=rainbow_beat;			effSpeed=4;		effLength=14;break;

case 18:anim_f=randomBlinkRainbow; break;
case 19:anim_f=randomBlinkRainbowFade;	effSpeed=99;	effLength=155; break;

case 20:anim_f=rainbowSpawn_moveFromStartWithSeparators; break; //!		//not168 not328
case 21:anim_f=rainbowSpawn_moveFromStartWithSeparatorsB; break; //!	//not168 not328

case 22:anim_f=rainbow_fade;			effSpeed=13;	effLength=14; break;	//Hue on all or rare LEDs 	//not168
case 23:anim_f=rainbow_fade;			effSpeed=28;	effLength=3;		effRGB=12; break;	//not168

case 24:anim_f=rainbow_fill_slow;		effSpeed=10;	effLength=1; break; //---RAINBOW LOOP // slow rainbow fill with shift
case 25:anim_f=rainbow_fill_slow;		effSpeed=10;	effLength=1;		effRGB=16; break;
case 26:anim_f=rainbow_vertical; break; //---VERITCAL RAINBOW (circular)	//not168 not328

case 27:anim_f=rainbow_beat;			effSpeed=130;	effLength=1; break;	//here and there
case 28:anim_f=rainbow_beat;			effSpeed=82;	effLength=150; break;	//:)

case 29:anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=5; break;
case 30:anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=26; break;
case 31:anim_f=rainbowSegments_shift;	effSpeed=40;	effLength=11; break;

case 32:anim_f=rainbowSegments_shiftSin; break; //i_eff_continued	//not168 not328
case 33:anim_f=rainbowSegments2; break;							//not168 not328

case 34:anim_f=rainbowCycle; 			effSpeed=44; 	effLength=1;	break;
case 35:anim_f=rainbowCycle;			effSpeed=35;	effLength=59;	break;

case 36:anim_f=sinelon;				effSpeed=10; 	effLength=28; break;		//:) //moving, fade
case 37:anim_f=bpm;					effSpeed=3;		effLength=62; break;		//:) //move here-there
case 38:anim_f=juggle;					effSpeed=20;	effLength=32; break;	//:) 	//multiple moving, fade
case 39:anim_f=spawnPixel_moveAll;		effSpeed=55;	effLength=6; break;

case 40:anim_f=fillFadeChangeAll;		effLength=237; break;			//flash over effLength	//not168
case 41:anim_f=fillFadeChangeAll_beat8;	effSpeed=30; effLength=200; break;	//flash over effLength
case 42:anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=22;	break;	//flash under effLength // effLength = 22 , so it can change color
case 43:anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=127; break;	//flash under effLength

case 44:anim_f=fadeEvenUneven;			effSpeed=25;	effLength=114;	break;	//:) 
case 45:anim_f=fadeEvenUnevenDif;		effSpeed=16;	effLength=30;	break;	//:) 	//effLength is speed

//============================ random
case 46:anim_f=confetti;				effSpeed=45;	effLength=6; break;
case 47:anim_f=confetti;				effSpeed=178;	effLength=8; break;		//:/	//not168 not328
case 48:anim_f=confetti_move;						effSpeed=45; break;
case 49:anim_f=confetti_moveRemainFirstAdd;			effSpeed=2;		effLength=161; break;
case 50:anim_f=confetti_moveRemainFirstBlend;		effSpeed=11;	effLength=98; break;	//not168 not328
case 51:anim_f=confetti_moveRemainFirstBlendByPos;	effSpeed=33;	effLength=240; break;	//not168 not328

case 52:anim_f=random_burst;			effSpeed=84;	effLength=120; break;	//:/			//not168 not328
case 53:anim_f=random_color_pop; break;											//:/ //fast 	//not168 not328


case 54:anim_f=flicker; break;	//:/	// random_burst	//not168 not328

case 55:anim_f=color_bounce;			effSpeed=16;	effLength=62; break;		//---CYLON v1 moving LED
case 56:anim_f=color_bounc_HueByPos;	effSpeed=6;		effLength=42; break;		// hue by pos
case 57:anim_f=color_bounc_HueByPos;	effSpeed=45;	effLength=255; break;

case 58:anim_f=color_bounce_multiple;	effSpeed=16;	effLength=17; break;	//not168

case 59:anim_f=color_bounceFADE; 		effSpeed=0;		effLength=33; break;	//CYLON v2 moving LED group	//effSpeed effLength - are COLORS //not168
case 60:anim_f=color_bounceFADE;		effSpeed=44;	effLength=1; break;		//not168

case 61:anim_f=CylonBounce; 			effSpeed=96;	effLength=65; break;		//moving group	//not168

case 62:anim_f=RunningLights; effSpeed=123; break; //!!	//not168 not328

case 63:anim_f=ems_lightsONE;		thishue = 0; break;			//---POLICE LIGHTS SINGLE 	//not168 not328
case 64:anim_f=ems_lightsALL;		 break;			//---POLICE LIGHTS SOLID //cycle around	//not168 not328
case 65:anim_f=ems_lightsSTROBE;	 break;			//:) //---EMERGECNY STROBE //! palette 	//not168

case 66:anim_f=color_loop_vardelay;	effSpeed=255;	effLength=255; break;	//<126 switch colorize	//not168 not328

case 67:anim_f=matrix;	break;		// random 	//not168 not328
case 68:anim_f=rwb_march;	break;		//!slo		//---MARCH RWB COLORS moving (circular) //<125 <200	switch colorize 	//not168 not328
case 69:anim_f=random_march;	break;	//!slo	 //---MARCH RANDOM COLORS random 	//not168 not328

case 70:anim_f=movingBlendRGB;			effSpeed=169;	effLength=127; break; //:)
case 71:anim_f=movingBlendRGB_A;		effSpeed=136;	effLength=132; break; //!fix blink 	//not168 not328

case 72:anim_f=rgb_propeller;	break; //!! RGB пропеллер //---RGB PROPELLER 
case 73:anim_f=kitt; effLength=20*16; break;		//---KITT random blink //!gDelay 	//not168 not328

case 74:anim_f=NewKITT;	break;					 // NewKITT (circular) //!fix 	//not168 not328

case 75:anim_f=rule30;	break;	//:/ //---CELL AUTO - RULE 30 (RED)		//!slo 	//not168 not328

//TwinkleRandom(20, gDelay, 1); break;								
case 76:anim_f=rainbow_vertical; break; //to center symmetry	// rainbowTwinkle 0-all, 1-random 1 //slow fill, shift 	//not168 not328
case 77:anim_f=randomBlink; effLength=3; break; 	//not168 not328

//!action case 79: Strobe(10, 5, 0); gColor=CRGB(255,255,255);	break;
case 80:anim_f=Strobe; gColor=CRGB(255,255,255); 	effSpeed=5*16; break;	//:/ 	//not168 not328

case 81:anim_f=pulse_one_color_all;	thishue = 0; break;		//:/	//---PULSE COLOR BRIGHTNESS single color	//not168 not328
case 82:anim_f=pulse_one_color_all_rev;	thishue = 0; break;	//:/	//---PULSE COLOR SATURATION	//not168 not328

case 83:anim_f=fade_vertical;	thishue = 180; break;		//:/ //! //---VERTICAL SOMETHING (circular) bright change	//not168 not328

case 84:anim_f=radiation;	thishue = 95; break;		//:/ //---RADIATION SYMBOL	//not168 not328

case 85:anim_f=white_temps; break;	//:/	//not168 not328
case 86:anim_f=sin_bright_wave;	thishue = 180; break;	//:/ //oo //!fix 	//not168 not328
case 87:anim_f=pop_horizontal;	break;		//!fix 		//---POP LEFT/RIGHT moving LED	//not168 not328
case 88:anim_f=quad_bright_curve;		effSpeed=0;	effLength=17; break;	//:/		//---QUADRATIC BRIGHTNESS CURVE / полумесяц	//not168 not328
case 89:anim_f=flame; break;
case 90:anim_f=Fire; 					effSpeed=22; effLength=75; break;			//:)	//! R-G swap 	//not168	//not168 not328

case 91:anim_f=pacman;	break;	//fix move				 //---PACMAN	//not168 not328
case 92:anim_f=BouncingColoredBalls;	effSpeed=16; effLength=3; break;	//!! ret, ballColors // прыгающие мячики	//not168 not328
case 98: //BouncingBalls(0xff, 0, 0, 3); break;					//fix ret	//not168 not328

//case 99:	break;					//---MARCH STRIP NOW CCW //strip_march_ccw(); break; //!		// move current ccw	//not168 not328
//case 100:	break;				//---MARCH STRIP NOW CCW//strip_march_cw(); break;	//!		// move current cw	//not168 not328
case 101: anim_f=colorWipe; gColor=0;	break;	// colorWipe colorWipe(0x00, 0xff, 0x00, gDelay); //!fix re 	//not168 not328

case 102: anim_f=Sparkle;	gColor=CRGB(255,255,255);	break;						//! Sparkle // случайные вспышки	//not168 not328
case 103: anim_f=SnowSparkle; gColor=CRGB(10,10,10); effLength=random8();	break;	//!! SnowSparkle wuth background	//not168 not328
//case 104: theaterChase(0xff, 0, 0, gDelay); break;	//! theaterChase //бегущие каждые 3 (NUM_LEDS ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)	//not168 not328
//case 105: //theaterChaseRainbow(gDelay);	break;	//! theaterChaseRainbow //fix ret	//бегущие каждые 3 радуга (NUM_LEDS ДОЛЖНО БЫТЬ КРАТНО 3)	//not168 not328


case 108:anim_f=Twinkle; twinkrate=100;gDelay=10;thisfade=8;thishue=50;thissat=255;thisbri=255;randhue=1;gDelay=0; maxChanges = 24; break; //:/ //demonstrates how to blend between two animations running at same time	//not168 not328
case 109:anim_f=beatWave; effSpeed=(24-10)*10;	currentPalette = RainbowColors_p;  break;  // combines coloured wave values from several beatsin8() functions
case 110:anim_f=blendwave;		effLength=1;	break; //:/ //! //uses beats, blend and the fill gradient functions to blend a couple of waves together	//not168 not328
case 111:anim_f=confetti2;		effSpeed = 8; thishue = 50; thisinc = 1; thissat = 100; thisbri = 255; huediff = 256; break;	//not168 not328
case 112:anim_f=confetti2_demo;		 gDelay = 5; break;
case 113:anim_f=confetti_pal; 	effSpeed=(24-10)*10;	effLength = 8*8; thishue = 50; thisinc = 1; thissat = 100; thisbri = 255; huediff = 256; gDelay = 5; currentPalette=HeatColors_p; break; //! crash
case 114:anim_f=dot_beat;				effSpeed=99;	effLength=243;	effRGB=13; break;
case 115:anim_f=dot_beat_area;			effSpeed=65;	effLength=173; break; //:)
case 116:anim_f=fill_grad;					break;
case 117:anim_f=inoise8_fire;	effSpeed=64;		effLength=140; gDelay=5;				break;	//not168 not328
case 118:anim_f=inoise8_mover; xscale = effLength/4; yscale = effLength/4; effSpeed=80; maxChanges = 24; idex = random16(12345); currentPalette=LavaColors_p; targetPalette=OceanColors_p; gDelay=5; break;//:)
case 119:anim_f=inoise8_pal;	xscale = 30; yscale = 30; maxChanges = 24; idex = random16(12345); currentPalette = CRGBPalette16(CRGB::Black); targetPalette=OceanColors_p; gDelay=0;	break;//:)
case 120:anim_f=juggle_pal;	thisfade = 2;thishue = 0; thissat = 255; thisbri = 255; thisbeat = 5; numdots = 4;thisdiff = 16; currentPalette = CRGBPalette16(CRGB::Black); targetPalette = RainbowColors_p; gDelay=0; break; //:)
case 121:anim_f=lightnings;		effSpeed=160;			break; //!spd	//not168 not328
case 122:anim_f=matrix_pal_demo; effLength=255/10*9;	thissat = 255; gDelay =  50; thisdir =   0; thisbri = 255; bgH = 0; currentBlending = LINEARBLEND;	palIndex =  95;huerot =   0;	break;	//not168 not328
case 123:anim_f=matrix_ray;		effLength=24*2; currentPalette = LavaColors_p; targetPalette = LavaColors_p;    currentBlending = LINEARBLEND;		gDelay=0;	break; //:/	//not168 not328
case 124:anim_f=noise16_1;		effSpeed = 24*2; effLength=100;  currentPalette = PartyColors_p;  gDelay=5; 		break; //:)
case 125:anim_f=noise16_2;		maxChanges = 24;  currentPalette = PartyColors_p;  	gDelay=0;		break;	//not168 not328
case 126:anim_f=noise16_3;		maxChanges = 24;  currentPalette = PartyColors_p;  	gDelay=0; 		break;	//not168 not328
case 127:anim_f=one_sine_pal;	allfreq = 32; thiscutoff = 192; bgH = 0; currentPalette = LavaColors_p;  maxChanges = 24;  gDelay = 0; 		break; //!(g same)	//not168 not328
case 128:anim_f=one_sine_pal_demo;	gDelay = 30; maxChanges = 24; 	thishue = 0;	bgH = 0; bgHinc = 0;		break;	//not168 not328
case 129:anim_f=palettecrossfade;	effLength=24*2-8;	gDelay = 20;  targetPalette=PartyColors_p;	break;//:)
case 130:anim_f=plasma;		effSpeed=60; effLength=16*3;		currentPalette = OceanColors_p;	gDelay = 0; break; //:)
case 131:anim_f=rainbow_beat2;		effSpeed=171;	effLength=10*5; break; //:/	//not168 not328
case 132:anim_f=rainbow_march;				effSpeed=155;		effLength=73; gDelay = 5; break;	//not168 not328
case 133:anim_f=rainbow_march_demo;	gDelay = 40;  thishue = 0; thisrot = 1; deltahue = 1;  thisdir = 0; 				break;	//not168 not328
case 134:anim_f=ripple_pal;		 effLength=thisfade = 128; gDelay = 0;   currentBlending = LINEARBLEND;	 maxChanges = 24; 		break; //! longer, brighter	//not168 not328
case 135:anim_f=Ripples;		effLength=160; currentPalette = OceanColors_p; targetPalette = OceanColors_p; gDelay = 40; 			break; //:)	//not168 not328
case 136:anim_f=sawtooth;		effSpeed=60;		effLength=255;  currentPalette = PartyColors_p; targetPalette = LavaColors_p;    currentBlending = LINEARBLEND; 	gDelay = 0;		break; //:/	//not168 not328
case 137:anim_f=serendipitous;	effSpeed=32;effLength=32;	currentBlending = LINEARBLEND; maxChanges = 24; 		gDelay = 0; 	break; //! @g	//not168 not328
case 138:anim_f=sinelon2;		 effLength=thisfade =   32; effSpeed=0;  thissat = 255;  thisbri = 255;         thishue =   0;	currentBlending = LINEARBLEND; gDelay = 20;			break; //:/	//not168 not328
case 139:anim_f=three_sin_demo;			three_sin_reset();	gDelay = 0;		break;
case 140:anim_f=three_sin_pal_demo;		effSpeed=0;	gDelay = 5;	currentPalette =CRGBPalette16(CRGB::Black); targetPalette =PartyColors_p;	maxChanges = 24;	break; //:)	//not168 not328
case 141:anim_f=two_sin_pal_demo;		gDelay = 0;	currentPalette = RainbowColors_p;  targetPalette = RainbowColors_p;  currentBlending = LINEARBLEND; two_sin_resetvars();	break; //:)


case 142:anim_f=blur_try;		currentBlending=LINEARBLEND;		break; //:/ //! crash	//not168 not328
case 143:anim_f=easing_test;	effLength=44; break;	//not168 not328
case 144:anim_f=blend_test;					break;	//not168 not328
case 145:anim_f=every_n_example;		currentPalette = PartyColors_p; currentBlending = LINEARBLEND;   			break; //:) //! change pal, color VS speed, fade w colorization	//not168 not328
//case 146:anim_f=every_n_exampleC;		currentPalette = PartyColors_p; currentBlending = LINEARBLEND;   			break; //! change pal, color VS speed, fade w colorization	//not168 not328
case 147:anim_f=fill_colours;		 thishue = 0; deltahue = 15;			break;	//not168 not328
case 148:anim_f=animationA;		 currentPalette = RainbowColors_p; targetPalette = ForestColors_p;  currentBlending = LINEARBLEND; 			break;	//not168 not328
case 149:anim_f=nodo;					break;	//not168 not328
case 150:anim_f=nodo;					break;	//not168 not328
case 151:anim_f=nodo;					break;	//not168 not328
case 152:anim_f=nodo;					break;	//not168 not328
case 153:anim_f=nodo;					break;	//not168 not328


//==============================================================================================================================
#ifdef eff_setX
case 160:anim_f=testPower;					effSpeed=10;	effLength=24;	 break;	//:/	//E, setBrightness	//not168 not328
case 161:anim_f=test_gDelay;				effSpeed=40;					 break;	//:/	//not168 not328
case 162:anim_f=palette_pipette;											 break;	//:) //dynamic pallete creator
case 163:anim_f=test_palettes;											 break;
case 164:anim_f=test_gradient;											 break;
case 165:anim_f=test_blend;											 break;
case 166:anim_f=test_easing;											 break;


case 170:anim_f=test_RAWcolorMath; break;	//:/	//not168 not328
case 171:anim_f=iterateRAWint; break;	//:/	//not168 not328
#endif

//==============================================================================================================================
case 205:anim_f=ems_lightsALL;				effSpeed=3;		effLength=82;		effRGB=17; break;	//not168 not328
case 211:anim_f=fillStriped;				effSpeed=45;	effLength=186;	effRGB=8;	break;		//not168 not328
case 212:anim_f=fadeEvenUneven;			effSpeed=84;		effLength=70;		effRGB=2; break; //!	//not168 not328


// case 241:anim_f=demo_modeA; break;			 //! short
// case 242:anim_f=demo_modeB; break;			 //! long


//effN, spd, , length, , RGB, , time to from start to end value
//case 243: animEff(2, 0,255, 7,7, 0,0, 15); break; //!
//effN, spd, , length, , RGB, , time to from start to end value, time to do 
//case 244: animEffContinue(2, 11,11, 2,55, 0,0, 5, 18); break; //!



//max N is 240
