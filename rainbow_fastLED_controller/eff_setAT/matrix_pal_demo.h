/* matrix_pal_demo
 *
 * Originally By: funkboxing LED
 *
 * Modified a LOT by: Andrew Tuline
 *
 * Date: July, 2015
 * 
 * Various coloured characters going up/down the strand, a la 'The Matrix'. This highly modified version uses non-blocking
 * delays as well as colorPalette lookups and other variables such as direction, speed and background colours.
 *
 */

//huerot =   0;                                     // Does the hue rotate? 1 = yes

void matrix_() {                                               // One line matrix

  if (huerot) palIndex++;
  
  if (random8() > effLength) {
    if (thisdir == 0)
      leds[0] = ColorFromPalette(currentPalette, palIndex, thisbri, currentBlending); 
    else
      leds[NUM_LEDS-1] = ColorFromPalette( currentPalette, palIndex, thisbri, currentBlending);
  } else {
    if (thisdir == 0)
      leds[0] = CHSV(bgH, thissat, bgbri); 
    else
      leds[NUM_LEDS-1] = CHSV(bgH, thissat, bgbri);
  }

  if (thisdir == 0) {
    for (NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (NUM_LEDS_type i = 0; i < NUM_LEDS-1 ; i++ ) leds[i] = leds[i+1];
  }
  
} 


// Also RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.

void matrix_ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 25;                // Change '25' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.

  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: 	gDelay=50; palIndex=95; bgH=140; bgbri=4; huerot=0; break;
      case  5: targetPalette = OceanColors_p; thisdir=1; bgbri=0; huerot=1; break;
      case 10: targetPalette = LavaColors_p; gDelay=30; palIndex=0; bgH=50; bgbri=8; huerot=0; break;
      case 15: targetPalette = ForestColors_p; gDelay=80; bgbri = 16; bgH=96; palIndex=random8(); break;
      case 20: palIndex=random8(); huerot=1; break;
      case 25: break;
    }
  }

} 


void matrix_pal_demo () {

  matrix_ChangeMe();

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  matrix_();

}