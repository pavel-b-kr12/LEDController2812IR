void rainbow_march() {     // The fill_rainbow call doesn't support brightness levels.

	switch(indexOrBits%5)
	{
		case 0: thishue = millis()*(256-effSpeed)/512; break;
		case 1: thishue = (millis()/16)%(256-effSpeed); break;             // To change the rate, add a beat or something to the result. 'gDelay' must be a fixed value.
		case 2: thishue = beat8(20+effSpeed/8);       break;                                 // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
		case 3: thishue = beatsin8(50,30,127+effLengthH/2);   break;                            // This can change speeds on the fly. You can also add these to each other.
		case 4: thishue = gHue; break; // (gHue incr w effSpeed)
	}
	if(indexOrBits>128)
	{
		EVERY_N_SECONDS(10)
		indexOrBits = random8(129,255);
	}
	
	fill_rainbow(leds, NUM_LEDS, thishue, effLength);            // Use FastLED's fill_rainbow routine.
}