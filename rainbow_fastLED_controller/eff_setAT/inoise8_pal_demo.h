/* inoise8_pal_demo
 *
 * By: Andrew Tuline
 *
 * Date: August, 2016
 *
 * This short sketch demonstrates some of the functions of FastLED, including:
 *
 * Perlin noise
 * Palettes
 * Palette blending
 * Alternatives to blocking delays
 * Beats (and not the Dr. Dre kind, but rather the sinewave kind)
 *
 * Refer to the FastLED noise.h and lib8tion.h routines for more information on these functions.
 * 
 */
 
void inoise8_pal_() {
  
  for(int i = 0; i < NUM_LEDS; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i*xscale, idex16+i*yscale) % 255;                // Get a value from the noise function. I'm using both x and y axis.
    leds[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  byte bpm=(effSpeed-127)/4; //10
  bpm=2+abs(bpm);
  byte add=beatsin8(bpm,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
  idex16 += (effSpeed<128)?add:-add;
                                                                           // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
}

void inoise8_pal() {
// EVERY_N_MILLISECONDS(10) { 
	//maxChanges=effLength/8; //!@@@
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    inoise8_pal_();                                                            // Update the LED array with noise at the new location
// }
 
  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
}

CRGBPalette16 PaletterRnd_frost()
{
	return CRGBPalette16(
	CHSV(random(130,190), random(0,255), random(188,255)), 
	CHSV(random(120,200), random(0,128), random(30,128)), 
	CHSV(random(110,190), random(0,255), random(133,255)), 
	CHSV(random(110,200), random(128,255), random(0,255))
	// CHSV(random8(170,210), random8(128,255), random8(155,255)), 
	// CHSV(random8(150,220), random8(0,255), random8(0,128)), 
	// CHSV(random8(140,220), random8(122,255), random8(133,255)), 
	// CHSV(random8(140,210), random8(0,255), random8(0,255))
	);
}
void inoise8_pal_frost() {
// EVERY_N_MILLISECONDS(10) { 
	maxChanges=effLength/8; //!
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    inoise8_pal_();                                                            // Update the LED array with noise at the new location
// }
 
  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette=PaletterRnd_frost();
	
  }
}  