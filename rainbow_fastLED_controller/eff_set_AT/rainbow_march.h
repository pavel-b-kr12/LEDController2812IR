/* rainbow_march

By: Andrew Tuline

Date: Nov, 2014

Updated: June, 2018

Update:

1.1 Remove original delay and added EVERY_N_MILLISECONDS
1.2 Remove EVERY_N_MILLISECONDS and use millis() for timing. Also demonstrate beat8 and beatsin8.


Description

Rainbow marching up the strand. Very basic, but oh so popular. Oh look, we don't need to add a 'wheel' routine.

If you want something really funky, try generating sequences with palettes, especially palettes you can change on the flly.

*/

void rainbow_march() {     // The fill_rainbow call doesn't support brightness levels.

  //uint8_t thishue = (millis()/8)%(256-effSpeed);             // To change the rate, add a beat or something to the result. 'gDelay' must be a fixed value.
  uint8_t thishue = millis()*(256-effSpeed)/256;
   
// thishue = beat8(50);                                       // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
// thishue = beatsin8(50,0,255);                              // This can change speeds on the fly. You can also add these to each other.
  
  fill_rainbow(leds, NUM_LEDS, thishue, effLength);            // Use FastLED's fill_rainbow routine.
}