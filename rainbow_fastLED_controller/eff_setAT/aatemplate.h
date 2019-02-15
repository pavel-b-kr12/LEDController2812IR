// This is a simple non-blocking FastLED display sequence template.
void twinkle() {
  if (random8() < twinkrate) leds[random16(NUM_LEDS)] += ColorFromPalette(currentPalette, (randhue ? random8() : thishue), 255, currentBlending);
  fadeToBlackBy(leds, NUM_LEDS, thisfade);
} 


void ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  uint8_t secondHand = (millis() / 1000) % 10;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case 0: thisdelay = 10; randhue = 1; thissat=255; thisfade=8; twinkrate=150; break;  // You can change values here, one at a time , or altogether.
      case 5: thisdelay = 100; randhue = 0;  thishue=random8(); thisfade=2; twinkrate=20; break;
      case 10: break;
    }
  }
}


void Twinkle()
{

  ChangeMe();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  twinkle() ;

}
