/* easing
 *
 * By: Andrew Tuline
 *
 * Date: August, 2015
 *
 * This boring display demonstrates the easing capability of FastLED. The Red LED starts out slow, speeds up and then slows down when it gets to the end.
 *
 * It uses uint8_t variables and may not work correctly on longer strands . . as noted by GitHub user fahrvergnuunen.
 *
 * easeOutVal = ease8InOutQuad(easeInVal);                       // Start with easeInVal at 0 and then go to 255 for the full easing.
 * ledNum = lerp8by8(0, NUM_LEDS, easeOutVal);                   // Map it to the number of LED's you have.
 *
 * Reference:
 * 
 * https://github.com/FastLED/FastLED/wiki/High-performance-math
 * 
 * 
 * Ideas:
 *  - Ease from 128 to 255 to throw something in the air
 *  - Ease from 255 to 128 and reverse direction for it to fall back.
 *  - Reduce the lerp8 value after each cycle to simulate a bouncing ball.
 *
 */

void easing_test() {

  static uint8_t easeOutVal = 0;
  static uint8_t easeInVal  = 0;
  static uint8_t lerpVal    = 0;

  easeOutVal = ease8InOutQuad(easeInVal);                     // Start with easeInVal at 0 and then go to 255 for the full easing.
  easeInVal++;

  lerpVal = lerp8by8(0, NUM_LEDS, easeOutVal);                // Map it to the number of LED's you have.

  leds[lerpVal] = CHSV((easeInVal-easeOutVal)*2,255,255); //CRGB::Red;
  fadeToBlackBy(leds, NUM_LEDS, effLength/2);                          // 8 bit, 1 = slow fade, 255 = fast fade
  
}