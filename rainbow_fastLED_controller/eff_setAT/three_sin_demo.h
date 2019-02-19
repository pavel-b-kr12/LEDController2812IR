/* three_sin demo

By: Andrew Tuline

Date: March, 2015

3 sine waves, one for each colour. I didn't take this far.

*/
void three_sin_reset()
{
 wave1=0;                                                  // Current phase is calculated.
 wave2=0;
 wave3=0;

 inc1 = 2;                                             // Phase shift. Keep it low, as this is the speed at which the waves move.
 inc2 = 1;
 inc3 = -2;

 lvl1 = 80;                                            // Any result below this value is displayed as 0.
 lvl2 = 80;
 lvl3 = 80;

 mul1 = 20;                                            // Frequency, thus the distance between waves
 mul2 = 25;
 mul3 = 22;
}


void three_sin_() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k=0; k<NUM_LEDS; k++) {
    leds[k].r = qsub8(sin8(mul1*k + wave1/128), lvl1);        // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2*k + wave2/128), lvl2);        // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3*k + wave3/128), lvl3);        // A fixed frequency, variable phase sine wave with lowered level
  }
}

void three_sin_ChangeMe() {
  uint8_t secondHand = (millis() / 1000) % 30;                // Increase this and add more options below if you want a longer demo.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  
  if(lastSecond != secondHand) {                              // You can change variables, but remember to set them back in the next demo, or they will stay as is.
    lastSecond = secondHand;
    switch(secondHand) {
      case 0: aDelay = 25; mul1 = 20; mul2 = 25; mul3 = 22; lvl1 = 80; lvl2 = 80; lvl3 = 80; inc1 = 1; inc2 = 1; inc3 = -1; break;
      case 10: mul1 = 5; mul2 = 8; mul3 = 7; break;
      case 20: aDelay = 40; lvl1 = 220; lvl2 = 220; lvl3 = 220; break;
      case 30: break;
    }
  }
}

void three_sin_demo () {
	three_sin_ChangeMe();
	EVERY_N_MILLISECONDS(aDelay)
	three_sin_();                                              // Improved method of using non-blocking delay
}