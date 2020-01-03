//!! init with i_eff==0 cause glitch after overflow


// to case rename, reorder or disable|enable use: https://github.com/pavel-b-kr12/switch_case_reName_reOrder
//to skip in renumbering del word 'case'
//https://tio.run/##Vc3BasMwDAbgc/UUxieHrFnZbjEuvfQwGGa0YztsO5hMKwbHDZYCGaWvvixOB9suQr/4JDW0bMiPxMnHgyADGwkg9egji@CIrVlpILPDLrgGFQi6ArGRr@9lLaeuNWsQJxBC5AVrHlwiVG315EKP1b4LnpWsZfGyeiv0zD6UXc@HC5HzCRaXN1bDIiH3KQpbTiuzPueCgfCfLctfexn88Wco9PicPOO9j6hoSl/Hjv0x0njd1/tPYmyrRxy42uGhDy5thy4hURZ5hIP@QXeRb2@@AQ




//!			mark for testing or need fix (buton color in GUI)
//:)		mark best
//:/		experiental, legasy and other stuff that can be skipped
//oo		effect related to (circular) stripe ring
//168 328	mark to generate include resticted to memory

//multiplicative value means there is division in effect

//case effN_off:anim_f=nodo; FastLED.clear(); break; //---ALL OFF //not168

//case 1:anim_f=fillAll; gColor=CRGB::White;	break; //---ALL ON
   

//case 11:anim_f=fillStriped;			effSpeed=0;		effLength=10; indexOrBits=88; gColor=CRGB::White; gColorBg=CRGB::Black;  break; //:)
//case 14:anim_f=fillStripedFillRainbow;	effSpeed=38;	effLength=73;	effSpeedH=110;	effLengthH=57;	effFade=178;    effRGB=12;	indexOrBits=88; break; //:)
	//case 14:anim_f=fillStripedFillRainbow;	effSpeed=176;	effLength=22;	effSpeedH=214;	effLengthH=24;	effFade=88;    effRGB=12;	indexOrBits=80; break;


case 11:anim_f=fillStriped;			effSpeed=18;		effLength=22; indexOrBits=88; gColor=CRGB::White; gColorBg=CRGB::Black; effRGB=9; break; //:) //cu //!!!! effRGB not printed in pde
case 12:anim_f=fillStriped;			effSpeed=6;	/*0;6;255*/	 effLength=10;/*0;255*/ 	effFade=178;    indexOrBits=131;	gDelay=10; effRGB=9; break;
case 13:anim_f=fillStripedInvert;			effSpeed=0;		effLength=10; indexOrBits=88; gColor=CRGB::White; gColorBg=CRGB::Black; break; //!
case 14:anim_f=fillStripedFillRainbow;	effSpeed=70;	effLength=70;	gColor=CRGB::White; break;
case 15:anim_f=fillStripedFillRainbow;	effSpeed=70;	effLength=70;	gColor=CRGB::White;	effRGB=14; break; //not168 not328
case 16:anim_f=fillStripedFillRainbow;				effSpeed=56;	effLength=35; effSpeedH=186;		effLengthH=29; break; //not168 not328
case 17:anim_f=fillByPalette;				currentPalette=ForestColors_p; break;
case 18:anim_f=fillByPalettesBlend_moving;	currentPalette=ForestColors_p; break;
case 19:anim_f=rainbow;					gDelay=6;		effLengthH=8;break;
case 20:anim_f=rainbowConfetti;			gDelay=4;		effLengthH=14;	effFade=16;break;
case 21:anim_f=rainbowWithGlitter;		effSpeed=20;	effLengthH=14; effFade=50; gColor=CRGB::White;  break;
case 22:anim_f=rainbowWithGlitter;		effSpeed=15;	effLength=125;	effLengthH=2;effFade=70; 	gColor=CRGB(255,255,255);	indexOrBits=141;	gDelay=4; break; //cu
//15 11 217 9
//15 5 71 7
case 23:anim_f=rainbow_beat;			effSpeed=4;		effLength=14;break;

case 24:anim_f=randomBlinkRainbow; break; //this uses FastLED.show(); so can't view in plotPX
case 25:anim_f=randomBlinkRainbowFade;	effSpeed=99;	effLength=155; break;

case 26:anim_f=rainbowSpawn_moveFromStartWithSeparators; break; //!		//not168 not328
case 27:anim_f=rainbowSpawn_moveFromStartWithSeparatorsB; break; //!	//not168 not328

//case 28:anim_f=rainbow_fade;			effSpeed=13;	effLength=14; break;	//Hue on all or rare LEDs 	//not168 	//!!freeze esp32 8266 300 800	
//case 29:anim_f=rainbow_fade;			effSpeed=28;	effLength=3;		effRGB=12; break;	//not168				//!!freeze esp32 8266 300 800

case 30:anim_f=rainbow_fill_slow;		effSpeed=10;	effLength=1; break; //---RAINBOW LOOP // slow rainbow fill with shift //not big
case 31:anim_f=rainbow_fill_slow;		effSpeed=10;	effLength=1;		effRGB=16; break;
case 32:anim_f=rainbow_vertical; break; //---VERITCAL RAINBOW (circular)	//not168 not328 //not big

case 33:anim_f=rainbow_beat;			effSpeed=130;	effLength=1; break;	//here and there
case 34:anim_f=rainbow_beat;			effSpeed=82;	effLength=150; break;	//:)

case 35:anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=5; break;
case 36:anim_f=rainbowSegments_shift;	effSpeed=2;		effLength=26; break;
case 37:anim_f=rainbowSegments_shift;	effSpeed=40;	effLength=11; break;

case 38:anim_f=rainbowSegments_shiftSin; break; //i_eff_continued	//not168 not328
case 39:anim_f=rainbowSegments2; break;							//not168 not328

//! ret btn check case 40:anim_f=rainbowCycle; 			effSpeed=44; 	effLength=1;	break;
case 41:anim_f=rainbowCycle;			effSpeed=35;	effLength=59;	break;

case 42:anim_f=sinelon;				effSpeed=10; 	effLength=28; break;		//:) //moving, fade
case 43:anim_f=bpm;					effSpeed=3;		effLength=62; break;		//:) //move here-there
case 44:anim_f=juggle;					effSpeed=20;	effLength=32; break;	//:) 	//multiple moving, fade
case 45:anim_f=spawnPixel_moveAll;		effSpeed=55;	effLength=6; break;

case 46:anim_f=fillFadeChangeAll;		effLength=237; break;			//flash over effLength	//not168
case 47:anim_f=fillFadeChangeAll_beat8;	effSpeed=30; effLength=200; break;	//flash over effLength
case 48:anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=22;	break;	//! //flash under effLength // effLength = 22 , so it can change color
case 49:anim_f=fillFadeChangeAll_beatsin8;	effSpeed=20; effLength=127; break;	//flash under effLength

case 50:anim_f=fadeEvenUneven;			effSpeed=25;	effLength=114;	break;	//:) 
case 51:anim_f=fadeEvenUnevenDif;		effSpeed=16;	effLength=30;	break;	//:) 	//effLength is speed

//============================ random
case 52:anim_f=confetti;				effSpeed=45;	effLength=6; break;
case 53:anim_f=confetti;				effSpeed=178;	effLength=8; break;		//:/	//not168 not328
case 54:anim_f=confetti_move;						effSpeed=45; break;
case 55:anim_f=confetti_moveRemainFirstAdd;			effSpeed=2;		effLength=161; break;
case 56:anim_f=confetti_moveRemainFirstBlend;		effSpeed=11;	effLength=98; break;	//not168 not328
case 57:anim_f=confetti_moveRemainFirstBlendByPos;	effSpeed=33;	effLength=240; break;	//not168 not328

case 58:anim_f=random_burst;			effSpeed=84;	effLength=120; break;	//:/			//not168 not328
case 59:anim_f=random_color_pop; break;											//:/ //fast 	//not168 not328

case 60:anim_f=randomBlink; effLength=3; gColor=CRGB::White; break; 	//not168 not328
case 61: anim_f=Sparkle;	gColor=CRGB(255,255,255);	break;						//! Sparkle // случайные вспышки	//not168 not328
case 62: anim_f=SnowSparkle; gColor=CRGB(10,10,10); effLength=random8();	break;	//!! SnowSparkle with background	//not168 not328
case 63: anim_f=SnowSparkle_changeBG; gColor=CRGB(10,10,10);effLength=8; effFade=1;	break;	//!! SnowSparkle with background	//not168 not328

case 64:anim_f=flicker; break;	//:/	// random_burst	//not168 not328


case 65:anim_f=color_bounce;			effSpeed=16;	effFade=62; break;		//---CYLON v1 moving LED
case 66:anim_f=color_bounc_HueByPos;	effSpeed=6;		effFade=42; break;		// hue by pos //!! faster for big
case 67:anim_f=color_bounc_HueByPos;	effSpeed=45;	effFade=255; break;

case 68:anim_f=color_bounce_multiple;	effSpeed=16;	effFade=17; break;	//not168

case 69:anim_f=color_bounceFADE; 		effSpeed=0;		effFade=33; break;	//CYLON v2 moving LED group	//effSpeed effLength - are COLORS //not168
case 70:anim_f=color_bounceFADE;		effSpeed=44;	effFade=1; break;		//not168

//case 71:anim_f=CylonBounce; 			effSpeed=96;	effFade=65; break;	//!!fix cube crush	//moving group	//not168

case 72: anim_f=movers;		effFade=80; break;

case 73:anim_f=RunningLights; effSpeed=123; break; //!!	//not168 not328
case 74:anim_f=meadow; effSpeed=123; break;
#ifdef eff_setX
case 75: anim_f=movers_f;	effFade=80; break;			//not168 not328
case 76:anim_f=meadow_cow; effSpeed=123; effLength=22; break; //!!	//not168 not328
#endif

case 77:anim_f=ems_lightsONE;		thishue = 0; break;			//---POLICE LIGHTS SINGLE 	//not168 not328 //not big
case 78:anim_f=ems_lightsALL;		 break;			//---POLICE LIGHTS SOLID //cycle around	//not168 not328 //not big
case 79:anim_f=ems_lightsSTROBE;	 break;			//!fix cube nwp //:) //---EMERGECNY STROBE //! palette 	//not168

////case 80:anim_f=color_loop_vardelay;	effSpeed=255;	effLength=255; break;	//!fix possible crash //<126 switch colorize	//not168 not328

#ifdef Cube4MCU
case 81:anim_f=CubeCornersLight;				 break;					//not168 not328
case 82:anim_f=CubeTest;				 break;					//not168 not328
//case 83:anim_f=CubeTest2;				 break;					//not168 not328


case 84:anim_f=matrixCube2; clear_leds();	break;		// random 	//not168 not328 //:) //cu
case 85:anim_f=matrixCube; clear_leds();	break;		// random 	//not168 not328
#endif
case 86:anim_f=Matrix;	break;		// random 	//not168 not328 //not big
////case 87:anim_f=rwb_march;	break;		//!slo		//---MARCH RWB COLORS moving (circular) //<125 <200	switch colorize 	//not168 not328 //not big
case 88:anim_f=random_march;	break;	//!slo	 //---MARCH RANDOM COLORS random 	//not168 not328

case 89:anim_f=movingBlendRGB;			effSpeed=169;	effLength=127; break; //:)
case 90:anim_f=movingBlendRGB_A;		effSpeed=136;	effLength=132; break; //!fix blink 	//not168 not328

case 91:anim_f=rgb_propeller;	break; //!! RGB пропеллер //---RGB PROPELLER 

case 92:anim_f=LinesOpposit;	effSpeed=18;	effLength=29;		effFade=252;    gColor=CRGB(112,255,255);		gDelay=0; break; //!


case 93:anim_f=kitt; effLength=20*16; break;		//---KITT random blink //!gDelay 	//not168 not328

////case 94:anim_f=NewKITT;	break;					 // NewKITT (circular) //!fix ret, possible crash 	//not168 not328

case 95:anim_f=rule30;	break;	//:/ //---CELL AUTO - RULE 30 (RED)		//!slo 	//not168 not328

//TwinkleRandom(20, gDelay, 1); break;								
////case 96:anim_f=rainbow_vertical; break; //!!255 //to center symmetry	// rainbowTwinkle 0-all, 1-random 1 //slow fill, shift 	//not168 not328


//!action case 97: Strobe(10, 5, 0); gColor=CRGB(255,255,255);	break;
////case 98:anim_f=Strobe; gColor=CRGB(255,255,255); 	effSpeed=5*16; break;	//:/ 	//not168 not328

case 99:anim_f=pulse_one_color_all;	thishue = 0; break;		//:/	//---PULSE COLOR BRIGHTNESS single color	//not168 not328
case 100:anim_f=pulse_one_color_all_rev;	thishue = 0; break;	//:/	//---PULSE COLOR SATURATION	//not168 not328

// case 101:anim_f=fade_vertical;	thishue = 180; break;		//:/ //! //---VERTICAL SOMETHING (circular) bright change	//not168 not328

case 102:anim_f=radiation;	thishue = 95; break;		//:/ //---RADIATION SYMBOL	//not168 not328

case 103:anim_f=white_temps; break;	//:/	//not168 not328

////case 104:anim_f=pop_horizontal;	break;		//!fix 255 		//---POP LEFT/RIGHT moving LED	//not168 not328
////case 105:anim_f=quad_bright_curve;		effSpeed=0;	effLength=17; break;	//:/		//---QUADRATIC BRIGHTNESS CURVE / полумесяц	//not168 not328
case 106:anim_f=flame; break; //!fix big
case 107:anim_f=Fire; 					effSpeed=22; effLength=75; break;			//:)	//! R-G swap 	//not168	//not168 not328 //!fix big


////case 108:anim_f=pacman;	break;	//fix move			 //not168 not328
case 109:anim_f=candycane;	effSpeed=34;	effLength=11;	effSpeedH=1;	effLengthH=255;	gColor=CRGB::White; indexOrBits=0;	gDelay=0; break; //!fix рывки //not168 not328 //!fix big
////case 110:anim_f=all_color_transition; break;				//not168 not328 //#setX
case 111:anim_f=move_newColor_toAndFrom_center; break;	//!			//not168 not328
case 112:anim_f=mover_lim_mark;	effFade=122;    gColor=CRGB(205,157,178);	indexOrBits=123;	gDelay=8; break; //:)			//not168 not328
case 113:anim_f=mover_lim_mark;	effSpeed=252;	effFade=239;   	indexOrBits=221;	gDelay=8; break;//:)	//not168 not328

////case 114:anim_f=BouncingColoredBalls;	effSpeed=16; effLength=3; break;	//!! ret, ballColors   possible crash // прыгающие мячики	//not168 not328
////case 115: //BouncingBalls(0xff, 0, 0, 3); break;					//fix ret	//not168 not328

////116:	break;					//---MARCH STRIP NOW CCW //strip_march_ccw(); break; //!		// move current ccw	//not168 not328
////117:	break;				//---MARCH STRIP NOW CCW//strip_march_cw(); break;	//!		// move current cw	//not168 not328
////case 118: anim_f=colorWipe; gColor=0;	break;	// colorWipe colorWipe(0x00, 0xff, 0x00, gDelay); //!fix re 	//not168 not328
//case 119: anim_f=move_to_center_RGBSet; gDelay=5; break;	//! //not168 not328


//case 120: anim_f=theaterChase; gColor=CRGB(255, 0, 0); gDelay=20; break;	//! theaterChase //бегущие каждые 3 (NUM_LEDS ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)	//not168 not328
// case 121: anim_f=theaterChaseRainbow;	break;	//! //fix ret	//бегущие каждые 3 радуга (NUM_LEDS ДОЛЖНО БЫТЬ КРАТНО 3)	//not168 not328



case 122:anim_f=Twinkle; twinkrate=100;gDelay=10;thisfade=8;thishue=50;thissat=255;thisbri=255;randhue=1;gDelay=0; break; //:/ //demonstrates blend two animations running at same time	//not168 not328

case 114:anim_f=pride;effSpeed=127;	effLength=128; effLengthH=128; break;

case 116:anim_f=colorTwinkles;	effSpeed=16*5; effFade=40; effLength=155; effLengthH=128; gColorBg = CRGB::Black;	break; // n=indexOrBits/10  0==rnd
case 117:anim_f=fire_pal_hot;	effSpeed=49;effLength=60;	break;
case 118:anim_f=fire_pal_cold;	effSpeed=49;effLength=60;	break;


case 123:anim_f=confetti2;		effSpeed = 8; thishue = 50; inc1 = 1; thissat = 100; thisbri = 255; huediff = 256; break;	//not168 not328
case 124:anim_f=confetti2_demo;		 gDelay=5; break;
case 125:anim_f=confetti_pal; 	effSpeed=(24-10)*10;	effLength = 8*8; thishue = 50; inc1 = 1; thissat = 100; thisbri = 255; huediff = 256; gDelay = 5; currentPalette=HeatColors_p; break; //! crash
case 126:anim_f=dot_beat;				effSpeed=99;	effLength=243;	effRGB=13; break;
case 127:anim_f=dot_beat_area;			effSpeed=65;	effLength=173; break; //:)
case 128:anim_f=fill_grad;					break;
case 129:anim_f=inoise8_fire;	effSpeed=64;		effLength=140; gDelay=5;				break;	//not168 not328
case 130:anim_f=inoise8_mover; xscale=effLength/4; yscale=effLength/4; effSpeed=80; maxChanges=24; posX=random16(12345); currentPalette=LavaColors_p; targetPalette=OceanColors_p; gDelay=5;break;//:)
case 131:anim_f=inoise8_pal;	xscale = 30; yscale = 30; maxChanges = 24; posX = random16(12345); currentPalette = CRGBPalette16(CRGB::Black); targetPalette=OceanColors_p; gDelay=0;break;//:)
case 132:anim_f=juggle_pal;	thisfade=2;thishue=0; thissat=255; thisbri=255; thisbeat=5;numdots=4;inc1=16;currentPalette=CRGBPalette16(CRGB::Black);targetPalette=RainbowColors_p;gDelay=0; break; //:)
case 133:anim_f=lightnings;		effSpeed=160;			break; //!spd	//not168 not328
case 134:anim_f=matrix_pal_demo; effLength=255/10*9;	thissat = 255; gDelay =  50; thisdir =   0; thisbri = 255; bgH = 0; currentBlending = LINEARBLEND;	palIndex = 95;bHuerot =0;break;//not168 not328
case 135:anim_f=matrix_ray;		effLength=24*2; currentPalette = LavaColors_p; targetPalette = LavaColors_p;    currentBlending = LINEARBLEND;		gDelay=0;	break; //:/	//not168 not328
case 136:anim_f=noise16_1;		effSpeed = 24*2; effLength=100;  currentPalette = PartyColors_p;  gDelay=5; 		break; //:)
case 137:anim_f=noise16_2;		maxChanges = 24;  currentPalette = PartyColors_p;  	gDelay=0;		break;	//not168 not328
case 138:anim_f=noise16_3;		maxChanges = 24;  currentPalette = PartyColors_p;  	gDelay=0; 		break;	//not168 not328
case 139:anim_f=one_sine_pal;	effSpeedH = 32; effLength = 192; bgH = 0; currentPalette = LavaColors_p;  maxChanges = 24;  gDelay = 0; 		break; //!(g same)	//not168 not328
case 140:anim_f=one_sine_pal_demo;	gDelay = 30; maxChanges = 24; 	thishue = 0;	bgH = 0; bgHinc = 0;		break;	//not168 not328
case 141:anim_f=palettecrossfade;	effLength=24*2-8;	gDelay = 20;  targetPalette=PartyColors_p;	break;//:)
case 142:anim_f=plasma;		effSpeed=60; effLength=16*3;		currentPalette = OceanColors_p;	gDelay = 0; break; //:)
case 143:anim_f=rainbow_beat2;		effSpeed=171;	effLength=10*5; break; //:/	//not168 not328
case 144:anim_f=rainbow_march;				effSpeed=155;		effLength=73; gDelay = 5; break;	//not168 not328
case 145:anim_f=rainbow_march_demo;	gDelay = 40;  thishue = 0; HueRot_incr = 1; inc1 = 1;  thisdir = 0; 				break;	//not168 not328
////case 146:anim_f=ripple_pal;		 effLength=thisfade = 128; gDelay = 0;   currentBlending = LINEARBLEND;	 maxChanges = 24; 		break; //! longer, brighter	//not168 not328
case 147:anim_f=Ripples;		effLength=160; currentPalette = OceanColors_p; targetPalette = OceanColors_p; gDelay = 40; 			break; //:)	//not168 not328
case 148:anim_f=sawtooth;		effSpeed=60;		effLength=255;  currentPalette = PartyColors_p; targetPalette = LavaColors_p; currentBlending = LINEARBLEND; gDelay = 0;break; //:/	//not168 not328
case 149:anim_f=serendipitous;	effSpeed=32;effLength=32;	currentBlending = LINEARBLEND; maxChanges = 24; 		gDelay = 0; 	break; //! @g	//not168 not328
case 150:anim_f=sinelon2;		 effLength=thisfade =   32; effSpeed=0;  thissat = 255;  thisbri = 255;         thishue =   0;	currentBlending = LINEARBLEND; gDelay = 20;	break; //:/	//not168 not328
case 151:anim_f=three_sin_demo;			three_sin_reset();	gDelay = 0;		break;
case 152:anim_f=three_sin_pal_demo;		effSpeed=0;	gDelay = 5;	currentPalette =CRGBPalette16(CRGB::Black); targetPalette =PartyColors_p;	maxChanges = 24;	break; //:)	//not168 not328
case 153:anim_f=two_sin_pal_demo;		gDelay = 0;	currentPalette = RainbowColors_p;  targetPalette = RainbowColors_p;  currentBlending = LINEARBLEND; two_sin_resetvars();	break; //:)


//case 154:anim_f=blur_try;		currentBlending=LINEARBLEND;		break; //:/ //! crash	//not168 not328
case 155:anim_f=easing_test;	effFade=22; effLength=2*4; break;	//not168 not328
case 156:anim_f=blend_test;					break;	//not168 not328
//case 157:anim_f=every_n_example;		currentPalette = PartyColors_p; currentBlending = LINEARBLEND;   			break; //:) //! change pal, color VS speed, fade w colorization	//not168 not328
case 158:anim_f=every_n_exampleMulti;	currentPalette = PartyColors_p; currentBlending = LINEARBLEND;   			break; //! timer2
//case 159:anim_f=every_n_exampleC;		currentPalette = PartyColors_p; currentBlending = LINEARBLEND;   			break; //!! change pal, color VS speed, fade w colorization	//not168 not328
case 160:anim_f=fill_colours;		 thishue = 0; inc1 = 15;			break;	//not168 not328
case 161:anim_f=animationA;		 currentPalette = RainbowColors_p; targetPalette = ForestColors_p;  currentBlending = LINEARBLEND; 			break;	//not168 not328



//######
case 162:anim_f=confetti_density;	effSpeed=4;	effLength=1;	effSpeedH=105;	effLengthH=171;	effFade=10;  break;	//not168 not328





//============================================================================================================================== test
#ifdef eff_setX 
//case 163:anim_f=setColors;				gDelay = 20; 	break;	//not168 not328
case 164:anim_f=setColors_fill;	effSpeed=143;	effLength=254;	effSpeedH=39;	effLengthH=171;	gDelay=20; break;
case 165:anim_f=setColors_fill_tstRange;	effSpeedH=31;	effSpeed=255; effLength=255;	effFade=35;	gDelay=20; break; //HSV , len %255
case 166:anim_f=currentPal_mod_w_gColor;		gDelay = 20; 	break;	//not168 not328 //show nothing only modify currentPalette
case 167:anim_f=currentPal_mod_w_gColor_Test;	gDelay = 20;	break;	//not168 not328
case 168:anim_f=splitModeEditor;	effLength=20; indexOrBits=0; effFade=0;	gDelay = 20;	break;	//not168 not328


//! //not168 not328
//case 169:anim_f=testPower;					effSpeed=10;	effLength=24;	break;	//:/	//E, setBrightness	//not168 not328
//case 170:anim_f=test_gDelay;				effSpeed=40;					break;	//:/	//not168 not328
case 171:anim_f=palette_pipette;		effFade=129;						break;	//:) //dynamic pallete creator //effFade>128 to edit
case 172:anim_f=test_palettes;												break;
case 173:anim_f=test_gradient;												break;
case 174:anim_f=test_blend;											 		break;
case 175:anim_f=test_easing;												break;//!



case 176:anim_f=test_RAWcolorMath; break;//!	//:/	//not168 not328
177:anim_f=iterateRAWint; break;			//:/	//not168 not328

//case 178:anim_f=cubic_PointerArr_test; break;				//!		//not168 not328
//case 179:anim_f=cubic_test; break;				//!		//not168 not328
case 180:anim_f=cubic_fill_edges; break;				//!		//not168 not328
case 181:anim_f=fill_segments_anim;	effSpeed=51;	effLength=5;	effSpeedH=2;	effLengthH=151;	indexOrBits=92;	 break;
case 182:anim_f=fill_segments_anim;	effSpeed=24;	effLength=9;	effSpeedH=23;	effLengthH=151;	indexOrBits=220; break;

//=========================== sample
case 183:anim_f=blendB;	break;//!
case 184:anim_f=draw_sample;	effSpeed=13;	effLength=1;	effSpeedH=118;	effLengthH=35;	effFade=1;    indexOrBits=1;	break;
#endif

//case 185:anim_f=painter_moving;	break; //! //not168 //not328 //@@@##
//case 186:anim_f=painter_H_by_Speed_moving;	break; //! //not168 //not328
//case 187:anim_f=painter_beat_moving;	break; //! //not168 //not328
//case 188:anim_f=painterBlend_moving;	break; //! //not168 //not328


//============================================================================================================================== react on sound music
#ifdef sound_p
case 189:anim_f=soundmems_H_V;	gDelay=0;	  break; //! need delay >10ms //! fade
case 190:anim_f=soundmems_pal;	currentBlending = LINEARBLEND; gDelay=10;	  break;
case 191:anim_f=soundmems_noise;	currentPalette=OceanColors_p;targetPalette=LavaColors_p; xscale = 30;  yscale = 30;	  break; 
case 192:anim_f=mus_random_mov;	effSpeed=15;	effLength=253;	effSpeedH=9;	effLengthH=16;	effFade=252; gColor=CRGB(255,218,255);indexOrBits=133;gDelay=0; currentPalette=RainbowColors_p; break;
case 193:anim_f=mus_random_mov;	effSpeed=15;	effLength=111;	effSpeedH=9;	effLengthH=16;	effFade=252; gColor=CRGB(255,218,255);indexOrBits=122;gDelay=0; currentPalette=LavaColors_p; break;
case 194:anim_f=soundmems_wave;	 gDelay=0;	effFade=16;	currentPalette = OceanColors_p;    currentBlending = LINEARBLEND;  break;
case 195:anim_f=soundmems_wave;	effSpeed=169;	effLength=122;	effSpeedH=187;	effLengthH=149;	effFade=16;    gColor=CRGB(255,218,255);	indexOrBits=200;	gDelay=0; break;
case 196:anim_f=soundmems_peak_ripple;	effLength=13; gDelay=0;	  break; //step=-1;

case 197:anim_f=soundmems_fire;	xscale=20 ;yscale=3  ;	  break;


case 198:anim_f=mus_arduinoFFT;	effSpeed=86;	effLength=51;	effSpeedH=99;	effLengthH=11;	effFade=23;   gDelay=0; break;
case 199:anim_f=mus_arduinoFFT;	effSpeed=96;	effLength=79;	effSpeedH=14;	effLengthH=11;	effFade=98;    gColor=CRGB(0,0,0);	indexOrBits=0;	gDelay=0; break;
case 200:anim_f=mus_arduinoFFT;	effSpeed=95;	effLength=96;	effSpeedH=124;	effLengthH=12;	effFade=228;    gColor=CRGB(0,0,0);	indexOrBits=2;	gDelay=0; break;
//201:anim_f=mus_arduinoFFT;	effSpeed=50;	effLength=56;	effSpeedH=46;	effLengthH=5;	effFade=243;   indexOrBits=175;	break;
#endif



case 202:anim_f=firework1000;	effSpeed=45;	effLength=70;	effSpeedH=28;	effLengthH=148;	effFade=55; 	gDelay=10; break;
case 203:anim_f=oppositeWavesBlend; effLength=22; effLengthH=133; break;// sub eff: indexOrBits/10


case 204:anim_f=wave_adj;	effSpeed=168;	effLength=128;	effSpeedH=148;	effLengthH=221;	indexOrBits=10; break;
case 115:anim_f=colorWaves_pal;	effSpeed=127; effLength=60; currentPalette=LavaColors_p; targetPalette=OceanColors_p; break; //! start black pal
case 205:anim_f=wave_H;		break; //:)
case 206:anim_f=wave_H;	effSpeed=32;	effLength=99;	effSpeedH=157;	effLengthH=140;	effFade=118;    indexOrBits=27;	effRGB=9; break;
case 207:anim_f=wave_H;	effSpeed=32;	effLength=99;	effSpeedH=157;	effLengthH=140;	effFade=118;    indexOrBits=27;	effRGB=17; break;
case 208:anim_f=gen_wave_H_moveAll;	effSpeed=20;	effLength=152;	effSpeedH=123;	effLengthH=70;	effFade=109;    indexOrBits=104;	gDelay=10; break;
//case 209:anim_f=gen_wave_H_moveAll_blinkRand;	break;
case 210:anim_f=gen_wave_H_moveAll_blinkRand;	effSpeed=161;	effLength=74;	effSpeedH=151;	effLengthH=167;	effFade=245;    indexOrBits=54; gDelay=30; break;
case 211:anim_f=gen_wave_H_v2_moveAll_blinkRand;	effSpeed=5;	effLength=181;	effSpeedH=7;	effLengthH=58;	effFade=100;    gColor=CRGB(146,0,0);	indexOrBits=19;	gDelay=10; break;
case 212:anim_f=sin_bright_wave;	thishue = 180; break;	//:/ //oo //!fix 	//not168 not328
case 213:anim_f=eff_sin_R_G_B;	effSpeed=127;	effLength=14;		effLengthH=37;	 break;	//not168 not328
case 214:anim_f=eff_sin_R_G_B;	effSpeed=37;	effLength=3;		effLengthH=3; break;	//not168 not328
case 215:anim_f=eff_sin_R_G_B;	effSpeed=37;	effLength=85;		effLengthH=4; break;	//not168 not328
case 216:anim_f=waveSmooth;	break;
case 217:anim_f=beatWave; effSpeed=(24-10)*10;	currentPalette = RainbowColors_p;  break;  // combines coloured wave values from several beatsin8() functions
case 218:anim_f=blendwave;		effLength=1;	break; //:/ //! //uses beats, blend and the fill gradient functions to blend a couple of waves together	//not168 not328
case 219:anim_f=weveByledSet;		effLength=1;	break; //!! TODO

//==============================================================================================================================


#ifdef MATRIX_ROWS
case 219:anim_f=matrix_test;	effFade=1; break;		//not168 not328 //!! combine w
#endif
#ifdef NUMMATRIX
case 220:anim_f=text_test;	break;		//not168 not328
#endif
#ifdef MATRIXfonth
case 221:anim_f=text_test_arr_RU;	break;		//not168 not328
case 222:anim_f=text_arr_RU_greetings;	break;		//not168 not328
#endif
#ifdef textMATRIX_overlay
case 223:anim_f=text_overlay_switch; /*in anim_f bTextOverlay=indexOrBits%2;  OR  bTextOverlay=!bTextOverlay;*/	break;		//not168 not328
#endif

case 224:anim_f=kit_MK;	break;		//not168 not328 //!! combine thease kits
// 224:anim_f=DemoReel101; indexOrBits=5; gDelay=5;  break;// indexOrBits/4==0 demo //!!
// 225:anim_f=kit_wand;	effSpeed=187;	effLength=128;		effFade=126;   	indexOrBits=141; break;


//======
case 226:anim_f=ems_lightsALL;		effSpeed=3;		effLength=82;	effRGB=17; break;		//not168 not328
case 227:anim_f=fillStriped;		effSpeed=45;	effLength=186;	effRGB=8; break;		//not168 not328
case 228:anim_f=fadeEvenUneven;		effSpeed=84;	effLength=70;	effRGB=2; break; //!	//not168 not328
////#setX case 229:anim_f=test_easing;		 gColor=CRGB(141,0,1);	indexOrBits=93;	 break;			//not168 not328

#ifdef ClothSuit
 case 230:anim_f=ClothKit; 	break;//gColor=CRGB(255,255,255);
#endif


case 231:anim_f=fillStriped;	effSpeed=55;	effLength=71;	effSpeedH=1;	effLengthH=4;	effFade=0;    gColor=CRGB(255,255,255);	indexOrBits=88;	break;
case 232:anim_f=fillStriped;	effSpeed=20;	effLength=102;	effSpeedH=120;	effLengthH=79;	effFade=21;    gColor=CRGB(255,255,255);	indexOrBits=88;	gDelay=0; break; //:\ bw
case 233:anim_f=fillStriped;	effSpeed=15;	effLength=125;	effSpeedH=31;	effLengthH=2;	effFade=70;    gColor=CRGB(255,255,255);	indexOrBits=141;	gDelay=0; break;
//======


case 234:anim_f=random_len_cell_1;				 break;					//not168 not328
case 235:anim_f=random_len_cell_seemless;		 break;			//:)	//not168 not328

case 236:anim_f=fillRange_anim;		 break;			//!!	//not168 not328


#ifdef PWM_enabled
case 237: anim_f=PWM_Dimmer; bPWM_Dimmer=!bPWM_Dimmer;  effLength=50; gDelay=40; break;
#endif
#ifdef PinSequencer_enabled
case 238: anim_f=PinSequencer;  break;
#endif
#ifdef mode_switch_enabled
case 239: anim_f=mode_switch;  break;//toggle PWM_Dimmer, PinSequencer if it defined 
#endif

#ifdef remap_LEDs

//fillStriped is placeholder for name parsing TODO another get name method for this case 
// 240: anim_f=fillStriped; bMap_type=(bMap_type==0)?indexOrBits%241:0;			 break; //toggle sw  //not168 not328 //!! TODO parce name is USB app
case 240:  bMap_type=(bMap_type==0)?bMap_type_matrix_zigZag_h:0; break;
case 241:  bMap_type=(bMap_type==0)?bMap_type_matrix_spiral_cw:0; break;
case 242:  bMap_type=(bMap_type==0)?bMap_type_matrix_labyrinth_cw:0; break;
case 243:  bMap_type=(bMap_type==0)?bMap_type_mirror_half:0; break;
case 244:  bMap_type=(bMap_type==0)?bMap_type_history:0; break; //!!TODO
#endif

case 245:	anim_f=nodo;	 break; //not168 not328 //TODO fix last item not appear in USB app

#if defined(WiFi_SEND)
//case 247:	anim_f=test_RF;	 break;			//not168 not328
#endif

// case 248:anim_f=demo_modeA; break;			 //! short
// case 249:anim_f=demo_modeB; break;			 //! long



//eff sw with actions @ transition
//!! eff-blur-eff



//max N is 240-248