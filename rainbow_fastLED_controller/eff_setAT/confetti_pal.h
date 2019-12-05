// Confetti flashes colours within a limited hue. It's been modified from Mark's original to support palettes and a few other variables. It's a simple, but great looking routine.

void confetti_pal_() {                                         // random colored speckles that blink in and fade smoothly

  fadeToBlackBy(leds, NUM_LEDS, effLength/16);                    // Low values = slower fade.
  int pos = random8or16(NUM_LEDS);                               // Pick an LED at random.
  leds[pos] = ColorFromPalette(currentPalette, thishue + random16(huediff)/4 , thisbri, LINEARBLEND);
  thishue = thishue + thisinc;                                // It increments here.
  
}


void confetti_pal_ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: targetPalette = OceanColors_p; thisinc=1; thishue=192; thissat=255; thisfade=2; huediff=255; break;  // You can change values here, one at a time , or altogether.
      case  5: targetPalette = LavaColors_p; thisinc=2; thishue=128; thisfade=8; huediff=64; break;
      case 10: targetPalette = ForestColors_p; thisinc=1; thishue=random16(255); thisfade=1; huediff=16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 15: break;                                         // Here's the matching 15 for the other one.
    }
  }
  
} 

// RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p


void confetti_pal () {
  
  confetti_pal_ChangeMe();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(100) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 8+effSpeed/8);
  }

  confetti_pal_();
}
