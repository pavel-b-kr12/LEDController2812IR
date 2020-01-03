/* rainbow_march_demo
 *
 * By: Andrew Tuline
 * Date: March, 2015
 *
 * Rainbow marching up the strand. Pretty basic, but oh so popular, and we get a few options as well. No 'wheel' routine required.
 */

void rainbow_march_() {                                        // The fill_rainbow call doesn't support brightness levels. You would need to change the max_bright value.
  
  if (thisdir == 0) thishue += HueRot_incr; else thishue-= HueRot_incr;  // I could use signed math, but 'thisdir' works with other routines.
  fill_rainbow(leds, NUM_LEDS, thishue, Hue_inc);            // I don't change Hue_inc on the fly as it's too fast near the end of the strip.
  
}

void rainbow_marchChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 60;                // Change '60' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.

  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: thisdir= 0; HueRot_incr=1; Hue_inc=5; break;
      case  5: thisdir=-1; Hue_inc=10; break;
      case 10: thisdir= 0; HueRot_incr=5; break;
      case 15: thisdir=-1; HueRot_incr=5; Hue_inc=20; break;
      case 20: thisdir= 0; Hue_inc=30; break;
      case 25: thisdir= 0; Hue_inc=2; HueRot_incr=5; break;
      case 30: break;
    }
  }
  
}

void rainbow_march_demo () {

	rainbow_marchChangeMe();

	rainbow_march_();

}