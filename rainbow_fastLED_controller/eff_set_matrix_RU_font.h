#if defined(MATRIXfonth)
int text_offset = WIDTH;

#include "fonts.h" 
#include "runningText.h" 

byte text_sett_speed=40; //1...
byte text_sett_blur=0;
byte text_sett_eff=0;
void text_sett() //! random demo have to upd thay
{
	text_sett_blur= (indexOrBits%16==15)? effFade: 0;
	text_sett_eff=indexOrBits;
	text_sett_speed=5+effSpeed;
}

void text_postProcessEff()
{
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		
		if(leds[i].r>10 || leds[i].g>10 || leds[i].b>10)
		{
			if(text_sett_eff%3==0)
				leds[i]+=CHSV( gHue+ beatsin8(22,0,80),255,255);
			else
				if(text_sett_eff%3==1)
					leds[i]=CHSV( gHue+ beatsin8(22,0,80) +i%32*4 +i/32+i/4,255,255);
		}
		
		if(text_sett_blur!=0) //blur
		{
			float avg_k=(float)text_sett_blur/300;
			leds[i].r=leds[(i-1)%NUM_LEDS].r*avg_k+leds[i].r*(1-avg_k)+leds[(i+1)%NUM_LEDS].r*avg_k;
			leds[i].g=leds[(i-1)%NUM_LEDS].g*avg_k+leds[i].g*(1-avg_k)+leds[(i+1)%NUM_LEDS].g*avg_k;
			leds[i].b=leds[(i-1)%NUM_LEDS].b*avg_k+leds[i].b*(1-avg_k)+leds[(i+1)%NUM_LEDS].b*avg_k;
		}
	}
}


void text_test_arr_RU()
{
	#ifndef standalone
	if(anim_f==text_test_arr_RU) //this eff
	{
		text_sett();
		colorWaves_pal();
		FastLED.clear(); //clear if this eff selected (but not drawn as overlay)
	}
	else
	#endif
		fadeToBlackBy(leds, NUM_LEDS, 16);
	
	//text_offset=-millis()/text_sett_speed%250;
									
	
	fillString("+QWer АБвгд | 1|2|3|@-_.||", CHSV(44,222,255));//gHue //color 1/2/c
	//case 0: fillString("Йц Qw яч_+%;$#2*", CHSV(gHue,beatsin8(11,0,111),255)); break;

	text_postProcessEff();
}

void text_arr_RU_greetings()
{
	#ifndef standalone
	if(anim_f==text_arr_RU_greetings) //this eff
	{
		text_sett();
		// #ifdef textMATRIX_overlay
		// if(!bTextOverlay)			//this is not need because anim_f== this eff
		// #endif
		FastLED.clear(); //clear if this eff selected (but not drawn as overlay)
	}
	else 
	#endif
	{
		//!!TODO if text will be drawn now, also smooth fade, contour more fade
		fadeToBlackBy(leds, NUM_LEDS, qadd8(70,effFade/2)); //!! clean prev text  //dimm bg
		
	}

	//! TODO text from right wo leading spaces
	fillString("     З Новим роком! 2020 :) С новым годом! : Happy New Year 2020", CHSV(millis()/100,beatsin8(6),255)); //Нарру пеш уеаг!
	// switch (indexOrBits/10%5)
	// {
	 // case 0: fillString("     З Новим роком! :) С новым годом! : Happy New Year", CHSV(gHue,beatsin8(11),255)); break; 
	 // case 1: fillString("     Любовi й миру ! Всяких благ ! ", CHSV(0,0,255));break;
	 // case 2: fillString("     Усiх благ!", CHSV(155,111,255));break;
	 // case 3: fillString("     З Рiздвом Христовим! С Рождеством вас! : Merry Christmas! :) ", CHSV(111,111,255));break;  //Merry Christmas Меггу СНг1$тма$$
	 // case 4: fillString("     :) lol . Be happy 8)   . .. ...", CHSV(44,255,255));break;
	 // case 5: fillString("     Universal controller 2812 pavel.b.kr12", CHSV(44,255,255));break;
	 //case 6: fillString("     Слава Богу за всё", CHSV(111,255,255));break;
	// }
	/*
	Good morning, Good afternoon, Good evening
	good day
	в буХту заходИ, ищИ причАл
	панки хой!
	проходи не задерживайтся
	*/
	
	#ifndef standalone
									if(anim_f==text_arr_RU_greetings) //this eff
	#endif
	#ifdef standalone
	if(millis()/5000%2)
	#endif
	text_postProcessEff();
}

#ifdef textMATRIX_overlay
void text_overlay_switch()
{
	bTextOverlay=indexOrBits%2;
	
	if(bTextOverlay)
	{
		text_sett();
	}
}
#endif

#endif