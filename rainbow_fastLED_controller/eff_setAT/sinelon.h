/* sinelon
 *
 * By: Mark Kriegsman
 *
 * Modified by: Andrew Tuline
 *
 * Date: February 2015
 *
 * This uses the built in beat in FastLED to move a dot back and forth. In this case, it uses two beats added together for more randomness.
 *
 */


void sinelon_() {                                              // a colored dot sweeping back and forth, with fading trails
	uint8_t thisbeat =  20+effSpeed/16;                                       // Beats per minute for first part of dot.
	uint8_t thatbeat =  25+effSpeed/16;                                       // Combined the above with this one.
	thisfade=effLength;

	fadeToBlackBy( leds, NUM_LEDS, thisfade);
	int pos1 = beatsin16(thisbeat,0,NUM_LEDS);
	int pos2 = beatsin16(thatbeat,0,NUM_LEDS);

	leds[(pos1+pos2)/2] += ColorFromPalette(currentPalette, thishue++, thisbri, currentBlending);
}

void sinelon2 () {

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

    sinelon_();
} 