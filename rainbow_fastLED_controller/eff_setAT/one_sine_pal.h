/* one_sine_pal
 *
 * By: Andrew Tuline
 *
 * Date: January, 2017
 * 
 * Forget using delay() statements or counting pixels up and down the strand of LED's. This example demonstrates just a bit of what can be done using basic high school math
 * by using a simple sinewave.
 * 
 * You can use a sine wave to go back and forth up a strand of LED's. You can shift the phase of a sine wave to move along a strand. You can clip the top of that sine wave
 * to just display a certain value (or greater). You can add palettes to that sine wave so that you aren't stuck with CHSV values and so on.
 * 
 * It shows that you don't neeed a pile of for loops, delays or counting pixels in order to come up with a decent animation.
 * 
 */

// effSpeed = 8;                                         // You can change the speed of the wave, and use negative values.
// allfreq = 32;                                         // You can change the frequency, thus distance between bars.
// thiscutoff = 192;                                     // You can change the cutoff value to display this wave. Lower value = longer wave.

void one_sine_pal(uint8_t colorIndex) {
  idex16 += effSpeed/16;                                                     // You can change direction and speed individually.
  
  for (int k=0; k<NUM_LEDS-1; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
    int thisbri = qsubd(cubicwave8((k*allfreq)+idex16), thiscutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    leds[k] = CHSV(bgH, 255, bgbri);                                     // First set a background colour, but fully saturated.
    leds[k] += ColorFromPalette( currentPalette, colorIndex, thisbri, LINEARBLEND);    // Let's now add the foreground colour.
    colorIndex +=3;
  }
  
  bgH++;
  
}

void one_sine_pal () {
	EVERY_N_SECONDS(30)
	one_sine_pal(millis()>>4);

  EVERY_N_MILLISECONDS(100) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
  
}