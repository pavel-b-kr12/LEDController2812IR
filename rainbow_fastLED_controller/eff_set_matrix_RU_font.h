#include "fonts.h" 
#include "runningText.h" 
void text_test_arr_RU()
{
	FastLED.clear();
	fillString("ЙЦувввонононитьсимивапвq1я№7@", CHSV(44,222,255));//gHue //color 1/2/c
	
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