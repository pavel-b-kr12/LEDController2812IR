int text_offset = WIDTH;

#include "fonts.h" 
#include "runningText.h" 



void text_test_arr_RU()
{
	colorWaves_pal();
	
									//if(millis()%10000%2)	text_offset = WIDTH;
								text_offset=-effLength*4+10-millis()/50%250;
									
	FastLED.clear();
	fillString("ЙЦук+QWer 12@", CHSV(44,222,255));//gHue //color 1/2/c
	//case 0: fillString("Йц Qw яч_+%;$#2*", CHSV(gHue,beatsin8(11,0,111),255)); break;
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		if(leds[i].r>10 || leds[i].g>10 || leds[i].b>10)
		{
			if(indexOrBits%3==0)
				leds[i]+=CHSV( gHue+ beatsin8(22,0,80),255,255);
			else
				if(indexOrBits%3==1)
					leds[i]=CHSV( gHue+ beatsin8(22,0,80) +i%32*4 +i/32+i/4,255,255);
		}
		
		if(indexOrBits>10) //blur
		{
			float avg_k=(float)effFade/300;
			leds[i].r=leds[(i-1)%NUM_LEDS].r*avg_k+leds[i].r*(1-avg_k)+leds[(i+1)%NUM_LEDS].r*avg_k;
			leds[i].g=leds[(i-1)%NUM_LEDS].g*avg_k+leds[i].g*(1-avg_k)+leds[(i+1)%NUM_LEDS].g*avg_k;
			leds[i].b=leds[(i-1)%NUM_LEDS].b*avg_k+leds[i].b*(1-avg_k)+leds[(i+1)%NUM_LEDS].b*avg_k;
		}
	}
	
	FastLED.show();
}

void text_arr_RU_greetings()
{
	text_offset=-effLength*4+10-millis()/50%350;
	
	FastLED.clear();
	
	switch (indexOrBits/10%4)
	{
	 case 0: fillString("З Новим роком! :) С новым годом! : Happy New Year", CHSV(gHue,beatsin8(11),255)); break;	// Happy New Year  Нарру пеш уеаг!
	 case 1: fillString("Любовi й миру ! Всяких благ ! ", CHSV(0,0,255));break;
	 case 2: fillString("Усiх благ!", CHSV(155,111,255));break;
	 case 3: fillString("З Рiздвом Христовим! С Рождеством вас! : Merry Christmas! :) ", CHSV(111,111,255));break;  //Merry Christmas Меггу СНг1$тма$$
	 case 4: fillString(":) lol . Be happy 8)    @  ", CHSV(44,255,255));break;
	}
	
	// Good morning, Good afternoon, or Good evening
	//good day
	//проходи не задерживайтся
	
	FastLED.show();
}

