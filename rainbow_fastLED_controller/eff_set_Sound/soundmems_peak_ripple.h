
// Samples
#define NSAMPLES 64
unsigned int samplearray[NSAMPLES];
unsigned long samplesum = 0;


int samplecount = 0;


unsigned long oldtime = 0;
unsigned long newtime = 0;


#define maxsteps 16                                           // Case statement wouldn't allow a variable.
int peakspersec = 0;
int peakcount = 0;


void soundmems2() {                                            // Rolling average counter - means we don't have to go through an array each time.

  newtime = millis();
  int tmp = analogRead(sound_p) - 512;
  sample = abs(tmp);

  int potin = effLength;

  samplesum = samplesum + sample - samplearray[samplecount];  // Add the new sample and remove the oldest sample in the array 
  sampleavg = samplesum / NSAMPLES;                           // Get an average

  //Serial.println(sampleavg);

  
  samplearray[samplecount] = sample;                          // Update oldest sample in the array with new sample
  samplecount = (samplecount + 1) % NSAMPLES;                 // Update the counter for the array

  if (newtime > (oldtime + 200)) digitalWrite(13, LOW);       // Turn the LED off 200ms after the last peak.

  if ((sample > (sampleavg + potin)) && (newtime > (oldtime + effLength)) ) { // Check for a peak, which is 30 > the average, but wait at least 60ms for another.
    step = -1;
    peakcount++;
    oldtime = newtime;
  }
  
}  // soundmems()



void rippleSnd() {
  fadeToBlackBy(leds, NUM_LEDS, effFade);                          // 8 bit, 1 = slow, 255 = fast
  
  switch (step) {

    case -1:                                                  // Initialize ripple variables.
      idex = random(NUM_LEDS); //center
      ihue = (peakspersec*10) % 255;                        // More peaks/s = higher the hue colour.
      step = 0;
      break;

    case 0:
      leds[idex] = CHSV(ihue, 255, 255);                  // Display the first pixel of the ripple.
      step ++;
      break;

    case maxsteps:                                            // At the end of the ripples.
      // step = -1;
      break;

    default:                                                  // Middle of the ripples.
      leds[(idex + step + NUM_LEDS) % NUM_LEDS] += CHSV(ihue, 255, 255/step*2);       // Simple wrap from Marc Miller.
      leds[(idex - step + NUM_LEDS) % NUM_LEDS] += CHSV(ihue, 255, 255/step*2);
      step ++;                                                // Next step.
      break;  
  } // switch step
  
} // ripple()

void soundmems_peak_ripple() {

  EVERY_N_MILLISECONDS(1000) {
    peakspersec = peakcount;                                  // Count the peaks per second. This value will become the foreground hue.
    peakcount = 0;                                            // Reset the counter every second.
  }

  soundmems2();

  EVERY_N_MILLISECONDS(20) {
   rippleSnd();
  }


} 
