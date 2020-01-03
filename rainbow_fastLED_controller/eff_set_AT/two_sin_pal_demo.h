/* two_sin_pal_demo
 *
 * By: Andrew Tuline
 *
 * Date: July, 2015
 *
 * Two moving waves of different colours, consisting of palettes. The cool thing about this routine is that there are lot of configurable items without requiring a lot of complex code.
 * It uses sine waves to create 'bars' and not lengthy/complex 'marching' code with nasty delay statements.
  *
 * With a few potentiometers or other inputs, you could change several values:
 *
 *  - Change the width of each wave
 *  - Change the speed
 *  - Change the direction
 *  - Change the overall frequency
 *  - Change the colour of each wave or even change the hue rotation speed.
 *  - You could even get real funky and have different frequencies and phase changes for the waves. Epilepsy alert!
 *
 * I've got codes that does this and it makes for an awesome interactive display for youth.
 *
 */

// Most of these variables can be mucked around with. Better yet, add some form of variable input or routine to change them on the fly. 1970's here I come. . 

uint8_t thathue;                                              // You can change the starting hue for other wave.
//uint8_t HueRot_incr;                                              // You can change how quickly the hue rotates for this wave. Currently 0.
uint8_t thatrot;                                              // You can change how quickly the hue rotates for the other wave. Currently 0.
uint8_t allsat;                                               // I like 'em fully saturated with colour.
uint8_t thatdir;
uint8_t alldir;                                               // You can change direction.
//int8_t effSpeed;                                             // You can change the speed.
int8_t thatspeed;                                             // You can change the speed.
// allfreq;                                              // You can change the frequency, thus overall width of bars.
int thisphase;                                                // Phase change value gets calculated.
int thatphase;                                                // Phase change value gets calculated.
// thiscutoff;                                           // You can change the cutoff value to display this wave. Lower value = longer wave.
uint8_t thatcutoff;                                           // You can change the cutoff value to display that wave. Lower value = longer wave.

// Also, RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p

void two_sin_() {

    thisdir ? thisphase += beatsin8(effSpeed, 2, 10) : thisphase -= beatsin8(effSpeed, 2, 10); //!check this that
    thatdir ? thatphase += beatsin8(effSpeed, 2, 10) : thatphase -= beatsin8(thatspeed, 2, 10);
    thishue += HueRot_incr;                                        // Hue rotation is fun for thiswave.
    thathue += thatrot;                                        // It's also fun for thatwave.
  
  for (int k=0; k<NUM_LEDS-1; k++) {
    int thisbri = qsuba(cubicwave8((k*allfreq)+thisphase), thiscutoff);      // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    int thatbright = qsuba(cubicwave8((k*allfreq)+128+thatphase), thatcutoff);  // This wave is 180 degrees out of phase (with the value of 128).

    leds[k] = ColorFromPalette(currentPalette, thishue, thisbri, currentBlending);
    leds[k] += ColorFromPalette(targetPalette, thathue, thatbright, currentBlending);
  }
     nscale8(leds,NUM_LEDS,thisfade);
}

void two_sin_resetvars() {                       // Reset the variable back to the beginning.

  thishue = 0;                          // You can change the starting hue value for the first wave.
  thathue = 140;                        // You can change the starting hue for other wave.
  HueRot_incr = 1;                          // You can change how quickly the hue rotates for this wave. Currently 0.
  thatrot = 1;                          // You can change how quickly the hue rotates for the other wave. Currently 0.
  allsat = 255;                         // I like 'em fully saturated with colour.
  thisdir = 0;                          // Change the direction of the first wave.
  thatdir = 0;                          // Change the direction of the other wave.
  alldir = 0;                           // You can change direction.
  effSpeed = 4;                        // You can change the speed, and use negative values.
  thatspeed = 4;                        // You can change the speed, and use negative values.
  allfreq = 32;                         // You can change the frequency, thus overall width of bars.
  thisphase = 0;                        // Phase change value gets calculated.
  thatphase = 0;                        // Phase change value gets calculated.
  thiscutoff = 192;                     // You can change the cutoff value to display this wave. Lower value = longer wave.
  thatcutoff = 192;                     // You can change the cutoff value to display that wave. Lower value = longer wave.
  //gDelay = 10;                       // You can change the delay. Also you can change the allspeed variable above.
  thisfade = 192;                        // How quickly we fade.
  
}

// RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, ForestColors_p, and PartyColors_p.
void two_sin_ChangeMe() {

  uint8_t secondHand = (millis() / 1000) % 60;                // Increase this if you want a longer demo.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: HueRot_incr = 1; thatrot = 1; currentPalette=PartyColors_p; targetPalette=PartyColors_p; break;
      case  5: HueRot_incr = 0; thatdir = 1; thatspeed = -4; currentPalette=ForestColors_p; targetPalette=OceanColors_p; break;
      case 10: thatrot = 0; currentPalette=PartyColors_p; targetPalette=RainbowColors_p; break;
      case 15: allfreq = 16; thisdir = 1; thathue = 128; break;
      case 20: thiscutoff = 96; thatcutoff = 240; break;
      case 25: thiscutoff = 96; thatdir = 0; thatcutoff = 96; HueRot_incr = 1; break;
      case 30: effSpeed= -4; thisdir = 0; thatspeed= -4; break;
      case 35: thiscutoff = 128; thatcutoff = 128; break;
      case 40: effSpeed = 3; break;
      case 45: effSpeed = 3; thatspeed = -3; break;
      case 50: effSpeed = 2; thatcutoff = 96; thiscutoff = 224; thatspeed = 3; break;
      case 55: two_sin_resetvars(); break;
      case 60: break;
    }
  }
} 


void two_sin_pal_demo() {
	two_sin_ChangeMe();
	EVERY_N_MILLISECONDS(10)
	two_sin_();
} 