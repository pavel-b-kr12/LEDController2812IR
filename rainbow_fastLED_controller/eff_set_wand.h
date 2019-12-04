NUM_LEDS_type getXfrom_float01(float x)
{
	return (NUM_LEDS_type)(x*(NUM_LEDS-1));
}

long t_last=0;
void moveOutAll_w_effSpeed()
{
	if(effSpeed>2)
	{
		int s=((int)effSpeed-128);

		byte spd=abs(s); //lower is faster
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

			
			//moveOutAll();
		}

	}
}

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
bool bMove=false;
bool bFire=false;
bool bFireToCold=false;
bool bPlasma=false;
bool bMove_out_anim=false;

#define move_sw 0
#define flash 1
#define glitter 2
#define fire_start 3
#define fire_stop 4
#define fire_toCold_start 5
#define plasma_start 6
#define plasma_stop 7
#define move_out_anim 8

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

byte checkInput() //!!debounce
{
	//if(!digitalRead(btn1))
	if(indexOrBits<11) 
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
			if(millis()-bbtn1_on_t>1500)
			{
				bbtn1_pressing_long=true;//! have to be cleared in code that use it
			}

		}
	}
	else
	{
		if(bbtn1)
		{

			bbtn1=false;
			bbtn1_pressing_long=false;
			if(millis()-bbtn1_on_t>1500)
			{
				bbtn1_click=true; //! have to be cleared in code that use it
			}
			else
			{
				bbtn1_click_short=true;//! have to be cleared in code that use it
			}
		}
		else
		{

		}
	}




	//if(!digitalRead(btn2))
	if(indexOrBits>111 && indexOrBits<122)
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
			if(millis()-bbtn2_on_t>1500)
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
		else
		{

		}
	}




	//if(!digitalRead(btn2))
	if(indexOrBits>244)
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
		else
		{

		}
	}




	return 0;

}

bool bGlitter=false;
bool bFade=true;
bool bFireHot=true;
byte effHue=0;

bool bStartAnim=false;
long Anim_dt=3000;
long Anim_start_t=0;
void kit_wand()
{
	byte btnAction=checkInput();

	if(bbtn2_onpress)
	{

		bbtn2_onpress=false;

		bPlasma=false;
		bFire=false;  gDelay=5;
		bFade=false;

		effHue=0;
	}
	if(bbtn2_click_short)
	{
		bbtn2_click_short=false;

		bFire=false;
		bPlasma=false;

		
		clear_leds();
	}
	if(bbtn2_pressing_long)
	{
		bbtn2_pressing_long=false;

		bPlasma=true; bStartAnim=true; Anim_dt=5000;
		effHue++;
	}



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

	}
	if(bbtn3_pressing_long)
	{
		bbtn3_pressing_long=false;

		bPlasma=false;
		
		bFade=false;

		bFire=true; gDelay=22; 
 		currentPalette=HeatColors_p;
	}




	// if(bbtn1_click_short || bbtn1_click)
	// {
	// 	bFire=false; gDelay=5;
	// }

	

	if(bFade) fadeToBlackBy(leds, NUM_LEDS, effFade/16);


	if(bPlasma)
	{
		if(bStartAnim)
		{
			bStartAnim=false;
			//currentPalette=OceanColors_p;
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
				leds[i].fadeToBlackBy( constrain(i*50*t_remain/Anim_dt ,1,222) ); 
			}
		}

	}
	else
	if(bFire)
	{
		if(bStartAnim)
		{
			bStartAnim=false;
			bFireHot=!bFireHot;
			effHue=0;
			Anim_start_t=millis();

		}

		
		long t_remain= Anim_dt-(millis()-Anim_start_t);
		if(t_remain>0)
		{
			if(bFireHot)
				effHue=map(t_remain,Anim_dt,0, 255, 160);
			else
				effHue=map(t_remain,Anim_dt,0, 160, 255);
		}

		//leds[0]=CHSV( effLengthH+beatsin8(effSpeed/16,0,80,0,effSpeedH)+beatsin8(effSpeed/8+16,0,55) ,beatsin8(effSpeed/8+4)/2+beatsin8(effSpeed/8+6)/2, beatsin8(effSpeed/8+6)/2+beatsin8(effSpeed/4+5)/2)  ;
		//moveOutAll_w_effSpeed();

		effSpeedH=effHue;
		Fire();
	}
	else //no eff
	{
		if(bMove) moveOutAll_w_effSpeed();
	}


	if(bbtn1_click_short)
	{
		bbtn1_click_short=false; //so wait next

			//flash
			fill_solid( leds, NUM_LEDS, CRGB::White); 
			FastLED.show();
			delay(10);
			clear_leds(); //! or return prev colors
			FastLED.show();
	}

	if(bbtn1_pressing_long) //bGlitter
	{
		bbtn1_pressing_long=false;

		if(!bPlasma && !bFire)	bFade=true;

		float randX01=((float)random16())/65535.;
		if(!bPlasma && !bFire)
		{
		 	randX01=randX01*randX01*randX01;//sqrt(randX01);
		 	for(byte g=0;g<10;g++)
			{
				float randX01t=((float)random16())/65535.;
				NUM_LEDS_type xt=getXfrom_float01(randX01);
				CRGB ct=leds[xt];
				leds[xt]=CRGB::White;
				FastLED.show();
				leds[xt]=ct;

			}
		}
		 NUM_LEDS_type x=getXfrom_float01(randX01);
		//CRGB ct=leds[x];
		leds[x]=CRGB::White;


	}

/*
	switch(btnAction)
	{
		case move_sw:
		{
			bMove=!bMove;
		}
		break;


		case fire_start:
		{
			bFire=true;
		}
		break;
		case fire_stop:
		{
			bFire=false;
		}
		break;
		case fire_toCold_start:
		{
			bFireToCold=true;
			effStart_t=millis();
		}
		break;
		case plasma_start:
		{
			bPlasma=true;
			bFire=false;
			effStart_t=millis();
		}
		break;
		case plasma_stop:
		{
			bPlasma=false;
		}
		break;
		case move_out_anim:
		{
			bMove_out_anim=true;
			bFire=false;
			bPlasma=false;
			effStart_t=millis();
		}
		break;
	}
	*/

}
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
		FastLED.show();delay(1);
		leds[x]=ct;
	}

	if(indexOrBits%2)
	{ //pow-rand distribution
		float randX01=((float)random16())/65535.;
		randX01=randX01*randX01*randX01;//sqrt(randX01);
		 NUM_LEDS_type x=getXfrom_float01(randX01);
		//CRGB ct=leds[x];
		leds[x]=CRGB::White;
		//FastLED.show();delay(1);
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