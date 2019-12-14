#define USBShow
#define reversemoveOutAll

//known issues: pressing both btn2&&btn3 will lead fire to "long" state (seems moving do not off). Need do it again to revert

NUM_LEDS_type getXfrom_float01(float x)
{
	return (NUM_LEDS_type)(x*(NUM_LEDS-1));
}

long t_last=0;
void moveOutAll_w_effSpeed() //close to 128 is faster
{				//Serial.println(effSpeed);
	if(effSpeed>2)
	{
		int s=((int)effSpeed-128);
		#ifdef reversemoveOutAll
		s=-s;
		#endif

		byte spd=abs(s); //lower is faster
		#ifdef USBShow
		spd/=2;
		#endif
		if(spd<3) s=0; //no move

		while(millis()-t_last > spd )
		{
			if((millis()-t_last)/ (1+spd) >10) //after big pause do not need to scroll
			{
				t_last=millis();
			}
			else
			{
				t_last+=spd;
			}

			if(s>0)
			{
				moveOutAllRemainFirst_ret_last__all_Right();
				leds[0]=0;
			}
			else if(s<0)
			{
				moveOutAllRemainFirst_ret_last__all_Left();
				leds[NUM_LEDS-1]=0;
			}
		}
	}
}
//moveOutAll();

//int kit_wand_moveSpeed=0;


/*
btn2 (floor micro switch or optic) - toggle sw1|sw2
btn1 fast ckick = flash     pressing= glitter

flash 							встряска || btn1 fast click
rnd glitter						btn1 pressing
//rnd spawn at start glitter
move 							sw2
fade 							
growing to plasma				btn2 press sw1, pressing1 
clear							btn2 onpress sw2 
fire 							xyz to top star eff
 fire to cold					btn1 press, pressing, off (finish eff faster)	
*/
bool kit_wand_sw=false;
bool bMove=false; //btn3		short click
bool bFire=false; //btn3		long pressing
bool bPlasma=false; //btn2		long click

bool bWaveByGen=true; //sw on btn1	short click
//#define fireworkEnable //!!fix
#ifdef fireworkEnable
bool bOffNow=true; //(after btn2 short click before any other run)   now all eff off, btn2 short click run firework
bool bFirework=false;
#endif
bool bGlitter=false; //btn1		pressing,  short flashes on long pressing
bool bFade=true;	// btn2 	short click && btn1 pressing				sw

byte effHue=0;

bool bStartAnim=false;	 // btn3	short click && bFire					this change bFireHot or plasma over time of  Anim_dt
long Anim_dt=3330;
long Anim_start_t=0;
long wave_start_t=0;
bool bFireHot=false;


long bbtn1_on_t=0;
bool bbtn1=false;
bool bbtn1_pressing_long=false;
bool bbtn1_click=false;
bool bbtn1_click_short=false;

long bbtn2_on_t=0;
bool bbtn2=false;
bool bbtn2_onpress=false;
bool bbtn2_sw=false;
bool bbtn2_pressing_long=false;
bool bbtn2_click=false;
bool bbtn2_click_short=false;


long bbtn3_on_t=0;
bool bbtn3=false;
bool bbtn3_onpress=false;
bool bbtn3_sw=false;
bool bbtn3_pressing_long=false;
bool bbtn3_click=false;
bool bbtn3_click_short=false;


bool bVerticalNow=false;

/*
in 		short click 	press

btn1  flash, glitter								встряска
btn2  off, eff1
btn3  sw move (when fire sw it fireT), fire
*/

int bbtn1_pressing_d=0;
byte checkInput() //!!debounce
{
	#ifdef btn0
	if(!digitalRead(btn0))
	#else
	if(indexOrBits<11) 
	#endif
	{
		if(!bbtn1)
		{
			//onpress
			bbtn1=true;
			bbtn1_pressing_long=false;
			bbtn1_on_t=millis();
		}
		else
		{
			if(millis()-bbtn1_on_t>2500)
			{
				bbtn1_pressing_long=true;//! have to be cleared in code that use it
			}
				bbtn1_pressing_d=millis()-bbtn1_on_t;
		}
	}
	else
	{
		if(bbtn1)
		{

			bbtn1=false;
			bbtn1_pressing_long=false;
			if(millis()-bbtn1_on_t>600) // click_short or long
			{
				bbtn1_click=true; //! have to be cleared in code that use it
			}
			else
			{
				bbtn1_click_short=true;//! have to be cleared in code that use it
					bbtn1_pressing_d=millis()-bbtn1_on_t;
			}
		}
		else		{		}
	}
//--------------------------------------------
	#ifdef btn1
	if(!digitalRead(btn1))
	#else
	if(indexOrBits>111 && indexOrBits<122) 
	#endif
	{
		if(!bbtn2)
		{
			//onpress
			bbtn2=true;
			bbtn2_onpress=true;//! have to be cleared in code that use it
			bbtn2_sw=!bbtn2_sw;
			bbtn2_pressing_long=false;
			bbtn2_on_t=millis();
		}
		else
		{
			if(millis()-bbtn2_on_t>2500) //long press is longer than click, so we can start effect without show pressing effect
			{
				bbtn2_pressing_long=true;//! have to be cleared in code that use it
			}
		}
	}
	else
	{
		if(bbtn2)
		{

			bbtn2=false;
			bbtn2_pressing_long=false;
			if(millis()-bbtn2_on_t>1500)
			{
				bbtn2_click=true; //! have to be cleared in code that use it
			}
			else
			{
				bbtn2_click_short=true;//! have to be cleared in code that use it
			}
		}
		else		{		}
	}
//-------------------------------------------------------

	#ifdef btn2
	if(!digitalRead(btn2))
	#else
	if(indexOrBits>240) 
	#endif
	{
		if(!bbtn3)
		{
			//onpress
			bbtn3=true;
			bbtn3_onpress=true;//! have to be cleared in code that use it
			bbtn3_sw=!bbtn3_sw;
			bbtn3_pressing_long=false;
			bbtn3_on_t=millis();
		}
		else
		{
			if(millis()-bbtn3_on_t>1500)
			{
				bbtn3_pressing_long=true;//! have to be cleared in code that use it
			}
		}
	}
	else
	{
		if(bbtn3)
		{

			bbtn3=false;
			bbtn3_pressing_long=false;
			if(millis()-bbtn3_on_t>1500)
			{
				bbtn3_click=true; //! have to be cleared in code that use it
			}
			else
			{
				bbtn3_click_short=true;//! have to be cleared in code that use it
			}
		}
		else		{		}
	}
	return 0;
}



void kit_wand()
{
	
	// ------------------ all btn
	#if defined(btn0) && defined(btn1) && defined(btn2)
	if((!digitalRead(btn0)) && (!digitalRead(btn1)) && (!digitalRead(btn2))) ////if(bbtn1 && bbtn2 && bbtn3)
	#else
	if(indexOrBits==B111)
	#endif
	{
		byte t1=effSpeed;
		byte t2=effLength;
		byte t3=effSpeedH;
		byte t4=effLengthH;
		byte t5=effFade;
		byte t6=indexOrBits;
		byte t7=effRGB;


		effSpeed=38;	effLength=73;	effSpeedH=110;	effLengthH=57;	effFade=178;    effRGB=12;	indexOrBits=88; gColor=CRGB(255,255,255);

		fillStripedFillRainbow();
		#ifdef standalone
		re_effRGB();
		#endif
		
		FastLED_show_DIRECTION
		
		//restore state/ also (otherwice?) it lead to some different state and eff1 behave in different way. I can't find reason;
		effSpeed=t1;
		effLength=t2;
		effSpeedH=t3;
		effLengthH=t4;
		effFade=t5;
		indexOrBits=t6;
		effRGB=t7;
		/*
							 effSpeed=177; //cooling
							 effLength=122;//sparkling
							// effSpeed=122; //cooling
							// effLength=255;//sparkling
							effFade=0; //as it rewrites
							indexOrBits=141;
							gDelay=0;
		*/
		return;
	}
	
	
	byte btnAction=checkInput();
	// #ifdef debugSerial
	// Serial.print(btnAction);Serial.print(" ");
	// Serial.print(bbtn1_click_short);Serial.print(" ");
	// Serial.print(bbtn1_pressing_long);Serial.print(" ");
	// Serial.print(bbtn2_onpress);Serial.print(" ");
	// Serial.print(bbtn2_click_short);Serial.print(" ");
	// Serial.print(bbtn2_pressing_long);Serial.print(" ");
	// Serial.print(bbtn3_click_short);Serial.print(" ");
	// Serial.print(bbtn3_pressing_long);Serial.print(" ");
	// Serial.print(" b: ");Serial.print(" ");
	// Serial.print(bPlasma);Serial.print(" ");
	// Serial.print(bFade);Serial.print(" ");
	// Serial.print(bFire);Serial.print(" ");
	// Serial.print(bMove);Serial.print(" ");
	// Serial.println();
	// #endif

	if(bFade && effFade>0) fadeToBlackBy(leds, NUM_LEDS, effFade/8);
	
	//---------------------------------- bbtn2

	if(bbtn2_click_short)
	{
		bbtn2_click_short=false;

		bFire=false;
		bPlasma=false;
		if(bbtn1) bFade=!bFade;   //

		
		clear_leds();
		
		#ifdef fireworkEnable
		if(bOffNow)
		{
			bOffNow=false;
			bFirework=true;
		}
		else
		{
			bOffNow=true;
			bFirework=false;
		}
		#endif
	}else
	if(bbtn2_click)
	{
		bbtn2_click=false;
		
		#ifdef fireworkEnable
		bOffNow=false;
		#endif
		wave_start_t=0;

		bPlasma=true; bStartAnim=true; Anim_dt=5000;
		effHue++; //?
	}

	else
	if(bbtn2_pressing_long)
	{
		bbtn2_pressing_long=false;
		#ifdef fireworkEnable
		bOffNow=false;
		#endif
			if(!bMove) //no  bMove == effect,  if bMove == move all out
			{
	
			effLength=67; effLengthH=133;

			if(wave_start_t==0) //1st prees untill click
			{
				wave_start_t=millis(); // so we starting at same pos
				pos1=NUM_LEDS/2-2;
				pos2=NUM_LEDS/2+2;
			}

			uint16_t it=(millis()-wave_start_t)/10;
			//if(millis()/1000%10<4)
			if(!bWaveByGen)
			{
				 //!2 can find maximum from function
				byte sizeMul=5;
				FastLED.clear();
				for (NUM_LEDS_type i = 0; i < NUM_LEDS; ++i)
				{
					uint16_t f_pos1=(i*sizeMul+(it*(effLength/8)) -sizeMul*72)%(256*sizeMul); //?! overfliw  //sizeMul*256==totall   so we move it to 72px ==72/256*total
					if(f_pos1>255) f_pos1=0;
					//constrain((i*4-255*4+255  +(it*effLength/8)%NUM_LEDS),0,255 ); //constrain((i*4+it*effLength/8)%1024,0,255);
					

					int b1=triwave8(f_pos1 );
					
					//b1=b1*b1/256;
					//b1=constrain(b1*
					
					
					uint16_t f_pos2=(i*sizeMul-(it*(effLength/8)) +122)%(256*sizeMul);
					if(f_pos2>255) f_pos2=0;
					//constrain((i*4-255*4+255  +(it*effLength/8)%NUM_LEDS),0,255 ); //constrain((i*4+it*effLength/8)%1024,0,255);
					int b2=triwave8(f_pos2);
					
					//b2=b2*b2/256;
					//leds[i]=CHSV( it*(1+(effLengthH/16))/100,255,b1);
					//leds[i]+=CHSV( 30*(it*(1+(effLengthH/16))/2000)+it*(1+(effLengthH/16))/100,255,b2);	

					//if mirror  both += so it not overwrite
					leds[i]+=CHSV( it/4 +20,255,b1);
					leds[NUM_LEDS-1-i]+=CHSV( it/4 +120,255,b1); //mirror
					//leds[i]+=CHSV( it/10 +150,255,b2);  //if not mirror but independent

					if(b1>253)
					{
						pos1=i; //max
						pos2=NUM_LEDS-1-i; //mirror
					}
					//if(b2>253) pos2=i; //if not mirror but independent
				}
			}
			else
			{
				//--------------------------  waves v gen
																							bFade=true;
				for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
					leds[i].fadeToBlackBy( 1+effFade/16 );

				if(pos1==NUM_LEDS-1)pos1=0;
				else pos1++;

				if(pos2==0) pos2=NUM_LEDS-1;
				else  pos2--;
					
				byte h1=0;
				byte h2=122;
				if(effSpeedH>50 && effSpeedH<150) 
				{
					h1=it/10;
					h2=150+it/6;
				}
				else
				if(effSpeedH>150)
				{
					h1=it/5;
					h1=it/3;
				}
				
				leds[pos1]+=CHSV( h1,millis()/4000%2?255:(it)%2*255,255);//
				leds[pos2]+=CHSV( h2,255,millis()/4000%2?255:(it)%2*255);//
			}
			//------------------- glitter between pos
			

			int diff_l=pos1-pos2;
			diff_l=abs(diff_l);
			if(diff_l<90)
			{
				if(pos1<pos2)
					leds[random8or16(pos1,pos2)]=CRGB::White;
				else
					leds[random8or16(pos2,pos1)]=CRGB::White;
			}
		} //eff

		//effHue++; //!
	
	} //bbtn2_pressing_long
	else
	if(bbtn2_onpress)
	{
		bbtn2_onpress=false;

		bPlasma=false;
		bFire=false;  gDelay=1;
		//bFade=false;

		effHue=0;
	}

			//=========================================================================


	if(bbtn3_click_short)
	{
		bbtn3_click_short=false;

		if(bFire)
		{
		   bStartAnim=true;  // if( millis()>Fire_sw_H_anim_end_t) Fire_sw_H_anim_end_t=millis()+Fire_sw_H_anim_dt;
		   Anim_dt=3000;
		}
		else
		{
			bMove=!bMove;
		}
	}else
	if(bbtn3_pressing_long)
	{
		bbtn3_pressing_long=false;
		#ifdef fireworkEnable
		bOffNow=false;
		#endif
		bPlasma=false;
		bFade=false;

		bFire=true; gDelay=1; 
 		currentPalette=HeatColors_p;
	}


//===========================================================================
	
	

	if(bPlasma)
	{
		#ifdef fireworkEnable
		bOffNow=false;
		#endif
		
		#ifdef standalone
		effSpeed=187;
		effLength=128;		
		effFade=0; //anyway it rewrites, so off
		indexOrBits=141;
		#endif
		if(bStartAnim)
		{
			bStartAnim=false;
			//currentPalette=OceanColors_p; //!!
			if(millis()-Anim_start_t>Anim_dt*1.5)
			{
			targetPalette=PaletterRnd_frost();
			currentPalette=PaletterRnd_frost();
			}

			Anim_start_t=millis();
		}

		//plasma();
		inoise8_pal_frost();


		long t_remain= Anim_dt-(millis()-Anim_start_t);
		if(t_remain>0)
		{
			for(NUM_LEDS_type i=constrain(map(t_remain,Anim_dt,0,0,NUM_LEDS),0,NUM_LEDS)  ;i<NUM_LEDS;i++)
			{
				leds[i].fadeToBlackBy( constrain(i*50*t_remain/Anim_dt ,1,255) ); 
			}
		}
	}
	else
	if(bFire)
	{
		#ifdef fireworkEnable
		bOffNow=false;
		#endif
		#ifdef standalone
		 effSpeed=177; //cooling
		 effLength=122;//sparkling
		// effSpeed=122; //cooling
		// effLength=255;//sparkling
		effFade=0; //as it rewrites
		indexOrBits=141;
		gDelay=0;
		#endif
		
		byte hueCold=150;
		byte hueHot=0;
		if(bStartAnim)
		{
			bStartAnim=false;
			bFireHot=!bFireHot;
			Anim_start_t=millis();
		}
		
		long t_remain= Anim_dt-(millis()-Anim_start_t);
		if(t_remain>0)
		{
			if(bFireHot)
				effHue=map(t_remain,Anim_dt,0, hueCold, hueHot);
			else
				effHue=map(t_remain,Anim_dt,0, hueHot, hueCold);
			
			//Serial.println(effHue);
		}
		else
		{
			//Serial.println(effHue);
			effHue=bFireHot?hueHot:hueCold;
		}
		//leds[0]=CHSV( effLengthH+beatsin8(effSpeed/16,0,80,0,effSpeedH)+beatsin8(effSpeed/8+16,0,55) ,beatsin8(effSpeed/8+4)/2+beatsin8(effSpeed/8+6)/2, beatsin8(effSpeed/8+6)/2+beatsin8(effSpeed/4+5)/2)  ;
		//moveOutAll_w_effSpeed();
		effSpeedH=effHue;
		Fire(); // delay(10);
	}
			#ifdef fireworkEnable
			else
			if(bFirework)  //bOffNow
			{
				effSpeed=45;	effLength=70;	effSpeedH=28;	effLengthH=148;	effFade=55; 
				firework1000();
			}
			#endif
	else //no eff
	{
		//#ifdef standalone
		
		 if(bbtn1)
		{
			effSpeed=128+59; //reverse  //for snow
		}
		else //for btn2 move out
		if(bbtn2)
		{
			effSpeed=128+18; //close to 128 is faster
		}
		// effLength=128;		effFade=126;   	indexOrBits=141;
		effLength=128;		effFade=155;   	indexOrBits=141;
		
		//#endif
		gDelay=0;
		if(bMove)
		{
			//Serial.println(bFire);
			//if(!bFire)
				moveOutAll_w_effSpeed(); //!!this affect fire but how?
		}
	}

//------------------- bbtn1
	if(bbtn1_click_short)
	{
		bbtn1_click_short=false; //so wait next
		bWaveByGen=!bWaveByGen;
		
			//flash
			//fill_solid( leds, NUM_LEDS, CHSV(50, map(bbtn1_pressing_d,0,500,0,255) ,255) );  //saturation @ t
			//fill_solid( leds, NUM_LEDS, CHSV(map(bbtn1_pressing_d,10,450,0,190), 255 ,255) );    //hue @ t
			//fill_solid( leds, NUM_LEDS, CHSV(map(bbtn1_pressing_d,30,450,0,190), constrain( map(bbtn1_pressing_d/2,30/2,100/2,0,255),0,255 ) ,255) );
			
			byte sat=0;
			if(bbtn1_pressing_d>140)
				sat=constrain( map(bbtn1_pressing_d,30,190,0,255),0,255 );

			byte hue=map(bbtn1_pressing_d,110,600,0,190);
			fill_solid( leds, NUM_LEDS, CHSV(hue, sat ,255) );

			#ifndef USBShow
			//FastLED.setBrightness( 255 ); //this is buggy if often switch
			#endif
			FastLED_show_DIRECTION
			delay(10);
			//!  if(bFade)
			#ifndef USBShow
			clear_leds(); //! or return prev colors
			//FastLED.setBrightness( gBrightness );
			FastLED_show_DIRECTION
			#endif
			
	}	else
	if(bbtn1_pressing_long) //bGlitter
	{
		bbtn1_pressing_long=false;

		if(!bPlasma && !bFire)	bFade=true;

		float randX01=0;
		if(!bPlasma && !bFire) //probability density
		{
		 	effFade=222;
		 	for(byte g=0;g<3;g++)
			{
				float randX01t=((float)random16())/65535.;
				randX01t=randX01t*randX01t*randX01t;//sqrt(randX01t);
				NUM_LEDS_type xt=getXfrom_float01(randX01t);
				if(effSpeed<128) xt=NUM_LEDS-xt; // reverse stripe dir
				CRGB ct=leds[xt];
				leds[xt]=CRGB::White;
				FastLED_show_DIRECTION
				leds[xt]=ct; //off for short blinks
			}
		}
		else
		{
		 randX01=((float)random16())/65535.;
		 NUM_LEDS_type x=getXfrom_float01(randX01);
		 //CRGB ct=leds[x];
		 leds[x]=CRGB::White;
		}
	}	else
	if(bbtn1)
	{
		float randX01=((float)random16())/65535.;
		 NUM_LEDS_type x=getXfrom_float01(randX01);
		 //CRGB ct=leds[x];
		 leds[x]=CRGB::White;
		
/*		
		 byte sat=0;
		 if(bbtn1_pressing_d>80)
			 sat=constrain( map(bbtn1_pressing_d,80,1500,0,255),0,255 );
		 
		 byte hue=map(bbtn1_pressing_d,80,4500,0,190);
		 
		 
		fill_solid( leds, NUM_LEDS, CHSV(hue, sat ,255) );
						
		Serial.print(bbtn1_pressing_d);Serial.print(" ");
		Serial.print( map(bbtn1_pressing_d,80,1500,0,255));Serial.print(" ");
		Serial.print(sat);Serial.print(" ");
		Serial.print(hue);Serial.print(" ");
		Serial.println();
		*/
	}
	
	
	//!?
	if(bFire)
	{
		leds[NUM_LEDS]=0;
	}
	

	#ifndef standalone
	FastLED_show_DIRECTION //##
	#endif
	
}













//===========================================================================================
//random_burst inoise8_pal confetti fillByPalette
void kit_wand_test()
{
	if(effFade>15) fadeToBlackBy(leds, NUM_LEDS, effFade/16);

	if(indexOrBits<128)
	{ //rgb rand
		NUM_LEDS_type rand=random16();
		NUM_LEDS_type x=getXfrom_float01((float)rand/65535.);
		leds[random8or16(NUM_LEDS)]=CHSV(x,255,255);
		CRGB ct=leds[x];
		leds[x]=CRGB::White;
		FastLED_show_DIRECTION
		leds[x]=ct;
	}

	if(indexOrBits%2)
	{ //pow-rand distribution
		float randX01=((float)random16())/65535.;
		randX01=randX01*randX01*randX01;//sqrt(randX01);
		 NUM_LEDS_type x=getXfrom_float01(randX01);
		//CRGB ct=leds[x];
		leds[x]=CRGB::White;
		FastLED_show_DIRECTION
		//leds[x]=ct;
	}

	moveOutAll_w_effSpeed();
	
/*
for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
{


bool bDraw=beat8 (effSpeed,i*effLength)<indexOrBits;
	if(bDraw) leds[i] = gColor;
	else
	if(effFade>200)  leds[i] = gColorBg;


void fillStripedInvert()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    if( beat8 (effSpeed,i*effLength)<indexOrBits ) leds[i] = CRGB(255,255,255)-leds[i];
  }
}
*/

}