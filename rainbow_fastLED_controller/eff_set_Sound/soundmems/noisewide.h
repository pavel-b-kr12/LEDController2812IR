gD = 10

void noisewide() {


  uint8_t tempsamp = constrain(sampleavg/2,0,NUM_LEDS/2);

  memset(leds, 0, NUM_LEDS * 3);                                // Quick clearing of the LED's.
  
  for (int i=0; i<tempsamp; i++) {

    uint8_t index = inoise8(i*sampleavg+millis(), 5000+i*sampleavg); 
//        index = inoise8(i*20,millis()*3*NUM_LEDS/255); 

    leds[NUM_LEDS/2-i] = ColorFromPalette(currentPalette, index, sampleavg, currentBlending);
    leds[NUM_LEDS/2+i] = ColorFromPalette(currentPalette, index, sampleavg, currentBlending);

  }
  
} 


void noisewideG() {

// Local definitions
  #define GRAVITY 5

// Persistent local variables
  static uint8_t topLED;
  static int gravityCounter = 0;

// Temporary local variables
  uint8_t tempsamp = constrain(sampleavg/2,0,NUM_LEDS/2);                       // Keep the sample from overflowing.


  fadeToBlackBy(leds, NUM_LEDS, 160);
    
  for (int i=0; i<tempsamp; i++) {
    uint8_t index = inoise8(i*sampleavg+millis(), 5000+i*sampleavg); 
    leds[NUM_LEDS/2-i] = ColorFromPalette(currentPalette, index, sampleavg, currentBlending);
    leds[NUM_LEDS/2+i] = ColorFromPalette(currentPalette, index, sampleavg, currentBlending);
  }

  if (tempsamp >= topLED)
    topLED = tempsamp;
  else if (gravityCounter % GRAVITY == 0)
    topLED--;

  if (topLED > 0) {
    leds[NUM_LEDS/2-topLED] = ColorFromPalette(currentPalette, millis(), 255, LINEARBLEND);                       // LED falls when the volume goes down.
    leds[topLED+NUM_LEDS/2] = ColorFromPalette(currentPalette, millis(), 255, LINEARBLEND);                       // LED falls when the volume goes down.
  }
  
  gravityCounter = (gravityCounter + 1) % GRAVITY;
    
}