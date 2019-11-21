NUM_LEDS_type get_i_next(NUM_LEDS_type i)
{
	if(i==NUM_LEDS-1) return 0;
	return i+1;
}
NUM_LEDS_type get_i_prev(NUM_LEDS_type i)
{
	if(i==NUM_LEDS-1) return 0;
	return i+1;
}

void random_len_cell_1()
{

	fadeToBlackBy(leds, NUM_LEDS, effFade);

	EVERY_N_MILLISECONDS(500)
	if(random8()<effSpeed) leds[random8or16(NUM_LEDS-1)] = CRGB(0,0,255);


	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		if(leds[i].b==(255-effLength/16)) leds[i]= CRGB(0,255,0);
		else 
		{
			if(leds[i].b>leds[i].r)
			{
			leds[i].b--;

			NUM_LEDS_type i_next=get_i_prev(i);
			if(leds[i_next].b<= (255-effLength/16) ) 
			 		leds[i_next].b=leds[i].b;
			}
		}

		
		if(leds[i].g==255-effLength/16) leds[i]= CRGB(0,255,0);
		else
		{
			NUM_LEDS_type i_next=get_i_prev(i);
			if(leds[i_next].g>=255-effLength/16)  		leds[i].g==0;
		}

	}

	}


void random_len_cell_seemless()
{

	fadeToBlackBy(leds, NUM_LEDS, effFade);

	EVERY_N_MILLISECONDS(500)
	if(random8()<effSpeed) leds[random8or16(NUM_LEDS-1)] = CRGB(0,0,255);


	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		if(leds[i].b==(255-effLength/16)) leds[i]= CRGB(0,255,0);
		else 
		{
			leds[i].b--;

			NUM_LEDS_type i_next=get_i_next(i);
			if(leds[i_next].b<=255-effLength/16)  		leds[i_next].b=leds[i].b;
		}

		
		if(leds[i].g==255-effLength/16) leds[i]= CRGB(0,255,0);
		else
		{
			NUM_LEDS_type i_next=get_i_next(i);
			if(leds[i_next].g>=255-effLength/16)  		leds[i].g==0;
		}

	}

}