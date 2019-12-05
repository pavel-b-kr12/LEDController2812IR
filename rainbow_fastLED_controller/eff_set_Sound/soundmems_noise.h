/* soundmems_noise
 *
 * By: Andrew Tuline
 * 
 * Date: February, 2017
 *
 * Another sound reactive routine that works with Perlin noise.
 * 
 * Again, I'm using the Sparkfun INMP401 microphone.
 *
 */
 


static int16_t xdist;                                          // A random number for our noise generator.
static int16_t ydist;



void soundmems_noise_()
{                                            // Rolling average counter - means we don't have to go through an array each time.

  int tmp = analogRead(MIC_PIN) - 512;
  sample = abs(tmp);

  samplesum += sample - samplearray[samplecount];             // Add the new sample and remove the oldest sample in the array 
  sampleavg = samplesum / NSAMPLES;                           // Get an average
  samplearray[samplecount] = sample;                          // Update oldest sample in the array with new sample
  samplecount = (samplecount + 1) % NSAMPLES;                 // Update the counter for the array

}


void fillnoise8() {                                           // Add Perlin noise with modifiers from the soundmems routine.

  if (sampleavg >NUM_LEDS) sampleavg = NUM_LEDS;

  
  for (int i= (NUM_LEDS-sampleavg)/2; i<(NUM_LEDS+sampleavg)/2; i++) {          // The louder the sound, the wider the soundbar.
    
    uint8_t index = inoise8(i*sampleavg+xdist, ydist+i*sampleavg);               // Get a value from the noise function. I'm using both x and y axis.
//      uint8_t index = inoise8(i*xscale, dist+i*yscale) % 255;                 // Get a value from the noise function. I'm using both x and y axis.

 
 
    leds[i] = ColorFromPalette(currentPalette, index, sampleavg, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }

  xdist=xdist+beatsin8(5,0,3);
  ydist=ydist+beatsin8(4,0,3);
 
                                                                          
} // fillnoise8()



void sndwave() {                                              // Shifting pixels from the center to the left and right.
  
  for (int i = NUM_LEDS - 1; i > NUM_LEDS/2; i--) {           // Move to the right , and let the fade do the rest.
    leds[i] = leds[i - 1];
  }

  for (int i = 0; i < NUM_LEDS/2; i++) {                      // Move to the left, and let the fade to the rest.
    leds[i] = leds[i + 1];
  }
  
}

void soundmems_noise() {

  EVERY_N_MILLISECONDS(10) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
    fillnoise8();                                             // Update the LED array with noise based on sound input
    fadeToBlackBy(leds, NUM_LEDS, 1);                         // 8 bit, 1 = slow, 255 = fast
    sndwave();                                                // Move the pixels to the left/right.
  }
 
  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
  

  soundmems_noise_();                                                // Sample the sound.

} 
