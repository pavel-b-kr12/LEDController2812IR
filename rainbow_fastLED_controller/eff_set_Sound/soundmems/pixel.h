#ifndef PIXEL_H
#define PIXEL_H

gD=0

void pixel() {

// Persistent local variable
  static uint16_t currLED;                                                      // Persistent local value to count the current LED location.

  currLED = (currLED+1)	% (NUM_LEDS);                                           // Cycle through all the LED's. By Andrew Tuline.

  CRGB newcolour = ColorFromPalette(currentPalette, oldsample, oldsample, currentBlending);   // Colour of the LED will be based on oldsample, while brightness is based on sampleavg.
  nblend(leds[currLED], newcolour, 192);                                        // Blend the old value and the new value for a gradual transitioning.

} // pixel()

#endif
