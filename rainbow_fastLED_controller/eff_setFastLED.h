//CRGBArray<NUM_LEDS> ledSet;
CRGBSet ledSet(leds, NUM_LEDS);
void move_to_center_RGBSet()//@
{
	for(int i = 0; i < NUM_LEDS/2; i++)
	{   
		// fade everything out
		ledSet.fadeToBlackBy(effFade);

		// let's set an led value
		leds[i] = CHSV(posX++,255,255);

		// now, let's first 20 leds to the top 20 leds, 
		ledSet(NUM_LEDS/2,NUM_LEDS-1) = ledSet(NUM_LEDS/2 - 1 ,0);

	}
}