/* one_sine_pal_demo
 *
 * By: Andrew Tuline
 *
 * Date: January, 2017
 * 
 * This takes my one_sine_pal program and demonstrates some of the different variables in a demo loop.
 * 
 * Forget using delay() statements or counting pixels up and down the strand of LED's. This example demonstrates just a bit of what can be done using basic high school math
 * by using a simple sinewave.
 * 
 * You can use a sine wave to go back and forth up a strand of LED's. You can shift the phase of a sine wave to move along a strand. You can clip the top of that sine wave
 * to just display a certain value (or greater). You can add palettes to that sine wave so that you aren't stuck with CHSV values and so on.
 * 
 * It shows that you don't neeed a pile of for loops, delays or counting pixels in order to come up with decent animations.
 * 
 */

// thisrot = 1;                                          // You can change how quickly the hue rotates for this wave.
// effSpeed = 8;                                         // You can change the speed of the wave, and use negative values.
// allfreq = 32;                                         // You can change the frequency, thus distance between bars.
// thiscutoff = 128;                                     // You can change the cutoff value to display this wave. Lower value = longer wave.
// bgbri = 0;                                        // Brightness of background colour

void one_sine_pal_(uint8_t colorIndex)
{
  idex16 += effSpeed/16;                                                     // You can change direction and speed individually.
  
   for (int k=0; k<NUM_LEDS; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
    int thisbri = qsuba(cubicwave8((k*allfreq)+idex16), thiscutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    leds[k] = CHSV(bgH, 255, bgbri);                                     // First set a background colour, but fully saturated.
    leds[k] += ColorFromPalette(currentPalette, colorIndex + k, thisbri, currentBlending);
    colorIndex += thisrot;
  }

  bgH += bgHinc;                                                                    // You can change the background colour or remove this and leave it fixed.
}

void SetupRandomColorPalette()
{
targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
} 

void SetupSimilarColorPalette() {
static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line, i.e. baseC+random8(0,5) for the hue.
targetPalette = CRGBPalette16(CHSV(baseC+random8(0,10), 255, random8(128,255)), CHSV(baseC+random8(0,10), 255, random8(128,255)), CHSV(baseC+random8(0,10), 192, random8(128,255)), CHSV(baseC+random8(0,10), 255, random8(128,255)));
}

void one_sine_pal_ChangeMe()
{
  uint8_t secondHand = (millis() / 1000) % 60;                // Increase this if you want a longer demo.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.  
  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: break;
      case  5: targetPalette=RainbowColors_p; bgH=0; bgbri=32; bgHinc=1; thisrot=1; gDelay=10; effSpeed=-4; allfreq=16; thiscutoff=128; currentBlending=NOBLEND; break;
      case 10: targetPalette=ForestColors_p; effSpeed = 12; thisrot = 0; effSpeed = 12; gDelay = 10; thiscutoff=128; allfreq=64; bgH = 50; bgbri=15; currentBlending=LINEARBLEND; break;
      case 15: SetupRandomColorPalette(); thisrot = 2; effSpeed = 16; break;
      case 20: targetPalette=LavaColors_p; effSpeed = 4; break; allfreq = 16; bgH=50; break;
      case 25: thiscutoff = 96; effSpeed = -4; thiscutoff = 224; bgH=20; bgbri=8; break;
      case 30: SetupRandomColorPalette(); thiscutoff = 96; thisrot = 1; break;
      case 35: targetPalette = OceanColors_p; break;
      case 40: SetupSimilarColorPalette(); thiscutoff = 128; break;
      case 45: SetupSimilarColorPalette(); effSpeed = 3; break;
      case 50: targetPalette = PartyColors_p; break;
      case 55: break;
      case 60: break;
    }
  }
} 


void one_sine_pal_demo () {

  one_sine_pal_ChangeMe();

  EVERY_N_MILLISECONDS(100) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

    thishue += thisrot;                                    // Motion speed
    one_sine_pal_(thishue);

} 