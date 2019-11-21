/* lightnings
 *
 * By: Daniel Wilson
 *
 * Modified by: Andrew Tuline
 *
 * Date: January, 2017
 *
 * Lightnings is a program that lets you make an LED strip look like a 1D cloud of lightning.
 * I wouldn't use this code in conjunction with any controls because it uses those nasty blocking delays which I haven't bothered to remove.
 *
 */


void lightnings() {
	uint8_t frequency = 80+effSpeed;                                       // controls the interval between strikes
	uint8_t flashes = 1+effLength/16;                                          //the upper limit of flashes per strike
	unsigned int dimmer = 1;

  uint8_t ledstart = random8or16(NUM_LEDS);                               //  starting location of flash
  uint8_t ledlen = random8or16(NUM_LEDS-ledstart);                        //  length of flash (not to go beyond NUM_LEDS-1)
  
  for (int flashCounter = 0; flashCounter < random8(3,flashes); flashCounter++) {
    if(flashCounter == 0) dimmer = 5;                         // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1,3);                               // return strokes are brighter than the leader
    
    fill_solid(leds+ledstart,ledlen,CHSV(255, 0, 255/dimmer));
    FastLED.show();                       // Show a section of LED's
    delay(random8(4,10));                                     // each flash only lasts 4-10 milliseconds
    fill_solid(leds+ledstart,ledlen,CHSV(255,0,0));           // Clear the section of LED's
    FastLED.show();
    
    if (flashCounter == 0) delay (150);                       // longer delay until next flash after the leader
    
    delay(50+random8(100));                                   // shorter delay between strokes  
  }
	  
  delay(frequency*4); //because gDelay is byte
  gDelay=(random8(frequency));                              // delay between strikes

} 