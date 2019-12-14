

void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
	for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ )
	{
		leds[i] = CHSV(ahue, thissat, 255);
	}
}
