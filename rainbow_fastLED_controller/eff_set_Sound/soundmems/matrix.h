gD=30

void matrix11() {                                                                 // A 'Matrix' like display using sampleavg for brightness. Also add glitter based on peaks (and not sampleavg).

// Persistent local variables
  static uint8_t thishue=0;


  leds[0] = ColorFromPalette(currentPalette, thishue++, sampleavg, LINEARBLEND);
  
  for (int i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];

  addGlitter(sampleavg/2);                                                      // Add glitter based on sampleavg. By Andrew Tuline.
  
} 


void matrix12() {                                                  // A 'Matrix' like display using sampleavg for brightness.



  if (thisdir == 1) {
      leds[0] = ColorFromPalette(currentPalette, millis(), sampleavg, currentBlending); 
  } else {
      leds[NUM_LEDS-1] = ColorFromPalette( currentPalette, millis(), sampleavg, currentBlending);
  }

  if (thisdir == 1) {
    for (int i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (int i = 0; i < NUM_LEDS-1 ; i++ ) leds[i] = leds[i+1];
  }

} 