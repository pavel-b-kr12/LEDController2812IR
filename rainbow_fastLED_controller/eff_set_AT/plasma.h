/* Plasma
 *
 * By: Andrew Tuline
 * 
 * Date: July, 2017
 *
 * This demonstrates 2D sinusoids in 1D using 16 bit math.
 * 
 * It runs at about 450 fps on an Arduino Nano with 60 APA102's. That would be FAST.
 * 
 * https://www.bidouille.org/prog/plasma
 * http://lodev.org/cgtutor/plasma.html
 * 
 */
void plasma_() {                                                 // This is the heart of this program. Sure is short. . . and fast.
if(indexOrBits%4<2) //!!!
{
  int thisPhase = beatsin8(3+effSpeed/16,-64,64);                           // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(4+effSpeed/12,-64,64); //! 

  for (int k=0; k<NUM_LEDS; k++) {                              // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;           // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisbri = qsuba(colorIndex, beatsin8(4+effLength/16,0,96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    leds[k] = ColorFromPalette(currentPalette, colorIndex, thisbri, LINEARBLEND);  // Let's now add the foreground colour.
  }
  
}
else //original
{
  if(indexOrBits%2)
  {
  int thisPhase = beatsin8(6,-64,64);                           // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7,-64,64);

  for (int k=0; k<NUM_LEDS; k++) {                              // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;           // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisbri = qsuba(colorIndex, beatsin8(7,0,96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    leds[k] = ColorFromPalette(currentPalette, colorIndex, thisbri, LINEARBLEND);  // Let's now add the foreground colour.
  }
  }
}
}

void plasma () {

  EVERY_N_MILLISECONDS(20) {                                  // FastLED based non-blocking delay to update/display the sequence.
    plasma_();
  }

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  EVERY_N_SECONDS(4) {                                 // Change the target palette to a random one every 5 seconds.
    uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(baseC+random8(32), 192, random8(128,255)), CHSV(baseC+random8(32), 255, random8(128,255)), CHSV(baseC+random8(32), 192, random8(128,255)), CHSV(baseC+random8(32), 255, random8(128,255)));
  }
}