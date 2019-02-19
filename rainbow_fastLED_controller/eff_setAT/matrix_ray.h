/* matrix_ray
 *
 * By: Andrew Tuline
 *
 * Date: January, 2018
 * 
 * 
 * This is a mishmash of the Matrix code as well as my one_sine code. The idea was to send out variable pulse width modulated sine wave at various speeds/frequencies, along with palette rotating colours.
 *  
 * It makes good use of a variable EVERY_N_MILLIS function call as well as beatsin8().
 * 
 * As usual, I don't use blocking delays, nested for loops or even floating point. Also, the code is kept as short as possible, variables defined as small and localized as possible.
 * As a result, I get about 450fps on the configuration below.
 * 
 * The advantage of this routine over my one_sine routine is that I can change the frequency on the fly without causing jittering.
 * 
 */


void matrix_ray_(uint8_t colorIndex) {                                                 // Send a PWM'd sinewave instead of a random happening of LED's down the strand.
                                                     
  static int thisphase = 0;                                                           // Phase change value gets calculated. Static means to assign that value only once.
  // thiscutoff;                                                                 // You can change the cutoff value to display this wave. Lower value = longer wave.

  thisphase += beatsin8(1,20, 50);                                                    // You can change direction and speed individually.
  thiscutoff = beatsin8(50,164,248);                                                  // This variable is used for the PWM of the lighting with the qsubd command below.
  
  int thisbri = qsubd(cubicwave8(thisphase), thiscutoff);                          // It's PWM time. qsubd sets a minimum value called thiscutoff. If < thiscutoff, then thisbri = 0. Otherwise, thisbri = thiscutoff.
 
  if (thisdir == 0) {                                                                 // Depending on the direction, we'll put that brightness in one end of the array. Andrew Tuline wrote this.
    leds[0] = ColorFromPalette(currentPalette, colorIndex, thisbri, currentBlending); 
    memmove(leds+1, leds, (NUM_LEDS-1)*3);                                            // Oh look, the FastLED method of copying LED values up/down the strand.
  } else {
    leds[NUM_LEDS-1] = ColorFromPalette( currentPalette, colorIndex, thisbri, currentBlending);
    memmove(leds, leds+1, (NUM_LEDS-1)*3);    
  }

}

 
void matrix_ray () {
  
   //                                                          // This section changes the delay, which adjusts how fast the 'rays' are travelling down the length of the strand.
  // EVERY_N_MILLIS_I(thisTimer,100) {                           // This only sets the Initial timer delay. To change this value, you need to use thisTimer.setPeriod(); You could also call it thatTimer and so on.
    // uint8_t timeval = beatsin8(10,20,50);                     // Create/modify a variable based on the beastsin8() function.
    gDelay= beatsin8(10,effSpeed/8,effSpeed/2);
	// thisTimer.setPeriod(timeval);                             // Use that as our update timer value.

    matrix_ray_(millis()>>4);                                  // This is the main function that's called. We could have not passed the millis()>>4, but it's a quick example of passing an argument.
  // }

  EVERY_N_MILLISECONDS(100) {                                 // Fixed rate of a palette blending capability.
    nblendPaletteTowardPalette(currentPalette, targetPalette, 8+effLength/4); //maxChanges = 24;  //! effLength seems no affect
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

} 