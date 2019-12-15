/* palettecrossfade
 *
 * By: Mark Kriegsman
 * 
 * Modified by: Andrew Tuline
 *
 * Date: October, 2016
 *
 * This example by Mark Kriegsman (and modified by Andrew) shows how to cross-fade 
 * between different color palettes using the function nblendPaletteTowardPalette.
 *
 * The basic idea is that you always have a "current palette" that you're
 * pulling colors from with ColorFromPalette, and you have a "target palette"
 * which is the 'next' palette that you want to get to.
 *
 * After that, implementation is relatively simple: just periodically call:
 * 
 *   nblendPaletteTowardPalette(currentPalette, targetPalette);
 *   
 * If the current palette is not yet equal to the target palette, this 
 * function will make a few small changes to the current palette to make
 * it slightly more like the target.  Over time, the current palette will
 * come to be equal to the target.
 * There's no need to test the current and target for equality; it's safe
 * to keep calling nblendPaletteTowardPalette even after current reaches target.
 * For faster blending, call nblendPaletteTowardPalette twice per loop.
 * 
 */

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), 255);
    colorIndex += 3;
  }

}
 
void ChangePalettePeriodically() {
  
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  
  if(lastSecond != secondHand) {
    lastSecond = secondHand;
    CRGB p = CHSV(HUE_PURPLE, 255, 255);
    CRGB g = CHSV(HUE_GREEN, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;
    if(secondHand ==  0)  { targetPalette = RainbowColors_p; }
    if(secondHand == 10)  { targetPalette = CRGBPalette16(g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
    if(secondHand == 20)  { targetPalette = CRGBPalette16(b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); }
    if(secondHand == 30)  { targetPalette = LavaColors_p; }
    if(secondHand == 40)  { targetPalette = CloudColors_p; }
    if(secondHand == 50)  { targetPalette = PartyColors_p; }
  }
  
}
 
void palettecrossfade() {
  
  ChangePalettePeriodically();
 
  // nblendPaletteTowardPalette() will crossfade current palette slowly toward the target palette.
  //
  // Each time that nblendPaletteTowardPalette is called, small changes
  // are made to currentPalette to bring it closer to matching targetPalette.
  // You can control how many changes are made in each call:
  //   - the default of 24 is a good balance
  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  //   - "0" means do not change the currentPalette at all; freeze

  EVERY_N_MILLISECONDS(100) {
    maxChanges = 8+effLength/8; //24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  static uint8_t startIndex = 0;
  startIndex += 1;                                 // motion speed
  FillLEDsFromPaletteColors(startIndex);
}