/* inoise8_fire
 *
 * By: Andrew Tuline
 * Date: January, 2017
 *
 * This super short sketch (just two lines to the algorithm) displays fire thanks to FastLED's Perlin Noise function and Palettes.
 *
 * It needs some tweaking in order to work across a wide range of NUM_LED values, but looks pretty good at 60.
 * 
 */

void inoise8_fire() {
	uint32_t xscale = 2+effLength/8;//20;                                          // How far apart they are
	uint32_t yscale = 1+effSpeed/32;//3;                                           // How fast they move

  currentPalette = CRGBPalette16(
                                   CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255,4),
                                   CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,                                   
                                   CRGB::DarkOrange,CRGB::Orange, CRGB::Orange, CRGB::Orange,
                                   CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

  for(int i = 0; i < NUM_LEDS; i++) {
    posX = inoise8(i*xscale,millis()*yscale*NUM_LEDS/255);                                           // X location is constant, but we move along the Y at the rate of millis()
    leds[i] = ColorFromPalette(currentPalette, min(i*(posX)>>6, 255), i*255/NUM_LEDS, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }                                                                                                   // The higher the value of i => the higher up the palette index (see palette definition).
                                                                                                      // Also, the higher the value of i => the brighter the LED.
}