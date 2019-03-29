
/* soundmems_wave
 *
 * By: Andrew Tuline
 * 
 * Wave adapted from: Stefan Petrick
 *
 * Date: February, 2017
 *
 * Basic code to read from the Sparkfun INMP401 microphone, and create waves based on sampled input. This does NOT include sensitivity adjustment.
 * 
 * My hardware setup:
 * 
 * Arduino Nano & Addressable LED strips
 *  - Powered by USB power bank 
 *  - APA102 or WS2812 data connected to pin 12.
 *  - APA102 clock connected to pin 11.
 *  - 5V on APA102 or WS2812 connected to 5V on Nano (good for short strips).
 *  - Gnd to Gnd on Nano.
 * 
 * 
 * Sparkfun MEMS microphone
 *  - Vcc on microphone is connected to 3.3V on Nano.
 *  - AREF on Nano connected to 3.3V on Nano.
 *  - Mic out connected to A5.
 *  - Gnd to Gnd on Nano.
 * 
 * Note: If you are using a microphone powered by the 3.3V signal, such as the Sparkfun MEMS microphone, then connect 3.3V to the AREF pin.
 * 
 */


void soundmemsW() {                                            // Quick and dirty sampling of the microphone.
  
  int tmp = analogRead(sound_p) - effLengthH - DC_OFFSET;
  sample = abs(tmp);
  
}  // soundmems()


void sndwaveW() {
  
  leds[NUM_LEDS/2] = ColorFromPalette(currentPalette, sample, sample*2, currentBlending); // Put the sample into the center
  
  for (int i = NUM_LEDS - 1; i > NUM_LEDS/2; i--) {       //move to the left      // Copy to the left, and let the fade do the rest.
    leds[i] = leds[i - 1];
  }

  for (int i = 0; i < NUM_LEDS/2; i++) {                  // move to the right    // Copy to the right, and let the fade to the rest.
    leds[i] = leds[i + 1];
  }
  
} // sndwave()

void soundmems_wave()
{
  EVERY_N_SECONDS(5) {                                        // Change the palette every 5 seconds.
    for (int i = 0; i < 16; i++) {
      targetPalette[i] = CHSV(random8(), 255, 255);
    }
  }
  
  EVERY_N_MILLISECONDS(100) {                                 // AWESOME palette blending capability once they do change.
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  EVERY_N_MILLIS_I(thistimer,20) {                            // For fun, let's make the animation have a variable rate.
    uint8_t timeval = beatsin8(10,20,50);                     // Use a sinewave for the line below. Could also use peak/beat detection.
    thistimer.setPeriod(timeval);                             // Allows you to change how often this routine runs.
    fadeToBlackBy(leds, NUM_LEDS, effFade);                        // 1 = slow, 255 = fast fade. Depending on the faderate, the LED's further away will fade out.
    sndwaveW();
    soundmemsW();
  }
} // loop()




