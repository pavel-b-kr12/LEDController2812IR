/* inoise8_mover
 *
 * By: Andrew Tuline
 *
 * Date: February, 2017
 *
 * We've used sine waves and counting to move pixels around a strand. In this case, I'm using Perlin Noise to move a pixel up and down the strand.
 * 
 * The advantage here is that it provides random natural movement without requiring lots of fancy math by joe programmer.
 */
 
 //! settings fade maxChanges
void inoise8_mover_() {
xscale = effLength/4; yscale = effLength/8;
//xscale = effLength/4; yscale = effLength/4;
//xscale = 30; yscale = 30;

  uint8_t locn = inoise8(xscale, idex16+yscale) % 256;          // Get a new pixel location from moving noise.
  uint8_t pixlen = map(locn,0,255,0,NUM_LEDS-1);                // Map that to the length of the strand.
  leds[pixlen] = ColorFromPalette(currentPalette, locn, 255, LINEARBLEND);   // Use that value for both the location as well as the palette index colour for the pixel.

  idex16 += beatsin8(2+effSpeed/4,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.                                             
}

void inoise8_mover() {
	nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);

	inoise8_mover_();                                          // Update the LED array with noise at the new location
	fadeToBlackBy(leds, NUM_LEDS, 4);     

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
	targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
}