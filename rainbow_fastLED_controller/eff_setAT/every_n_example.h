/* every_n_example
 *
 * By: Andrew Tuline
 * 
 * Date: February, 2017
 *
 * This demonstrates how to use the EVERY_N_MILLISECONS function with a variable timer.
 * 
 * It just moves an active LED up the strip in accordance with a timer that changes as a sine wave.
 *
 */

void every_n_example() {
 
  EVERY_N_MILLIS_I(thisTimer,100) {                           // This only sets the Initial timer delay. To change this value, you need to use thisTimer.setPeriod(); You could also call it thatTimer and so on.
    uint8_t timeval = beatsin8(10,4,10+effSpeed/2);                     // Create/modify a variable based on the beastsin8() function.
    thisTimer.setPeriod(timeval);                             // Use that as our update timer value.
    idex = (idex+1) % NUM_LEDS;                       // A simple routine to just move the active LED UP the strip.
    leds[idex] = ColorFromPalette(currentPalette, idex, 255, currentBlending);     // Pick a slightly rotating colour from the Palette
  }

	if(effFade>2)
	fadeToBlackBy(leds, NUM_LEDS, effFade);                           // Leave a nice comet trail behind.
}


int thatTimer;
void every_n_exampleMulti() {
 
  EVERY_N_MILLIS_I(thisTimer,100) {                           // This only sets the Initial timer delay. To change this value, you need to use thisTimer.setPeriod(); You could also call it thatTimer and so on.
    uint8_t timeval = beatsin8(10,4,10+effSpeed/2);                     // Create/modify a variable based on the beastsin8() function.
    thisTimer.setPeriod(timeval);                             // Use that as our update timer value.
    idex = (idex+1) % NUM_LEDS;                       // A simple routine to just move the active LED UP the strip.
    leds[idex] = ColorFromPalette(currentPalette, idex, 255, currentBlending);     // Pick a slightly rotating colour from the Palette
  }

  if(effSpeed>60)
    EVERY_N_MILLIS_I(thisTimer,100) //#? thisTimer
	{ 
		uint8_t timeval = beatsin8(20,2,6+effSpeed/2);
		thisTimer.setPeriod(timeval); 
		idex16 = (idex16+1) % NUM_LEDS;
		leds[idex16] = ColorFromPalette(ForestColors_p, idex16, 255, currentBlending);
	}
  
	if(effFade>2)
	fadeToBlackBy(leds, NUM_LEDS, effFade);                           // Leave a nice comet trail behind.
}