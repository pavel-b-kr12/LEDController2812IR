/* aanimations
 *
 * By: Can't recall where I found this.
 * 
 * Modified by: Andrew Tuline
 *
 * Date: January, 2017
 *
 * This sketch demonstrates how to blend between two animations running at the same time.
 * 
 */


// have 3 independent CRGBs - 2 for the sources and one for the output

//CRGB leds2[NUM_LEDS];


void animationA_() {                                             // running red stripe.
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t red = (millis() / 5) + (i * 12);                    // speed, length
    if (red > 128) red = 0;
	leds[i] = ColorFromPalette(currentPalette, red, red, currentBlending);
  }
} 


/* void animationA_() {                                             // running red stripe.
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t red = (millis() / 10) + (i * 12);                    // speed, length
    if (red > 128) red = 0;
    leds2[i] = CRGB(red, 0, 0);
  }
}
*/


void animationA() {

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
  
  animationA_();                                               // render the first animation into leds2   
}
