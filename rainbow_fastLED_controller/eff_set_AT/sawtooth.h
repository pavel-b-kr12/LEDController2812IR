// Creating a sawtooth pattern using millis and bpm. It runs at about 440 fps with the configuration below on an Arduino Nano.

void sawtooth() //change H every new
{

	int bpm = effSpeed;
	int ms_per_beat = 60000/bpm;                                // 500ms per beat, where 60,000 = 60 seconds * 1000 ms 
	int ms_per_led = 60000/bpm/NUM_LEDS;

	int cur_led = ((millis() % ms_per_beat) / ms_per_led)%(NUM_LEDS);     // Using millis to count up the strand, with %NUM_LEDS at the end as a safety factor.

	if (cur_led == 0)
		fill_solid(leds, NUM_LEDS, CRGB::Black);
	else
		leds[cur_led] = ColorFromPalette(currentPalette, effLength>200?cur_led:effLength, 255, currentBlending);    // I prefer to use palettes instead of CHSV or CRGB assignments.

}