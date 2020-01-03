/* juggle_pal
 *
 * Originally by: Mark Kriegsman
 * Modified By: Andrew Tuline
 *
 * Date: February, 2015
 *
 * Juggle just moves some balls back and forth. A single ball could be a Cylon effect. I've added several variables to this simple routine.
 *
 */

//uint8_t   numdots =   4;                                     // Number of dots in use.
//uint8_t   inc1 =  16;                                     // Incremental change in hue between each dot.

void juggle_pal_() {                                           // Several colored dots, weaving in and out of sync with each other

  fadeToBlackBy(leds, NUM_LEDS, 1+effLength/16);
  
  for( int i = 0; i < numdots; i++) {
    leds[beatsin16(thisbeat+i+numdots,0,NUM_LEDS)] += ColorFromPalette(currentPalette, thishue , thisbri, LINEARBLEND);    // Munge the values and pick a colour from the palette
    thishue += inc1;
  }
  
} 

void juggle_pal_ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 30;                // IMPORTANT!!! Change '30' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: numdots = 1; thisbeat = 20; inc1 = 16; thisfade = 2; thishue = 0; break;                  // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; thisbeat = 10; inc1 = 16; thisfade = 8; thishue = 128; break;
      case 20: numdots = 8; thisbeat =  3; inc1 =  0; thisfade = 8; thishue=random8(); break;           // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }

}
  
void juggle_pal() {

  EVERY_N_MILLISECONDS(100) {                                 // AWESOME palette blending capability provided as required.
    nblendPaletteTowardPalette(currentPalette, targetPalette, 8+effSpeed/8);   
  }
 
  juggle_pal_ChangeMe();
  juggle_pal_();

}