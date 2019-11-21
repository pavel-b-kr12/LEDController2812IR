/* ripple_pal
 *
 * By: Balázs Suhajda
 * 
 * Modified by: Andrew Tuline
 * 
 * Date: Oct, 2014
 *
 * A cool ripple effect for an LED strip that's been re-written and optimized from the Neopixel version https://gist.github.com/suhajdab/9716635
 *
 */

//gColor                                              // Ripple colour is randomized.
                                             
#define maxsteps 16                                           // Case statement wouldn't allow a variable.

void ripple() {
thisfade=effLength;
byte myfade=255-effSpeed;

  fadeToBlackBy(leds, NUM_LEDS, thisfade);                             // 8 bit, 1 = slow, 255 = fast
  
  switch (step) {

    case -1:                                                          // Initialize ripple variables.
      idex = random8or16(NUM_LEDS-1); // Center of the current ripple.
      gColor = random8();
      step = 0;
      break;

    case 0:
      leds[idex] = ColorFromPalette(currentPalette, gColor, myfade, currentBlending);
      
      step ++;
      break;

    case maxsteps:                                                    // At the end of the ripples.
      step = -1;
      break;

    default:                                                          // Middle of the ripples.
      leds[(idex + step + NUM_LEDS) % NUM_LEDS] += ColorFromPalette(currentPalette, gColor, myfade/step*2, currentBlending);       // Simple wrap from Marc Miller
      leds[(idex - step + NUM_LEDS) % NUM_LEDS] += ColorFromPalette(currentPalette, gColor, myfade/step*2, currentBlending);
      step ++;                                                         // Next step.
      break;  
  } // switch step
  
}

void ripple_pal () {

  EVERY_N_MILLISECONDS(100) {
    
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(3) {
      targetPalette = CRGBPalette16(CHSV(random8(), 255, 32), CHSV(random8(), random8(64)+192, 255), CHSV(random8(), 255, 32), CHSV(random8(), 255, 255)); 
  }
  
	EVERY_N_MILLISECONDS(60)
  ripple();
}