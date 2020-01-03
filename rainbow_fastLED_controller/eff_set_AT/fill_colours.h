/* fill_colours
 *
 * By: Andrew Tuline
 * Date: July, 2015
 *
 * This example provides ways of filling the strand with colours such as:
 *
 * - fill_solid for a single colour across the entire strip
 * - fill_gradient for one or more colours across the section of, or the entire strip
 * - fill_rainbow for a whole enchalada of colours across sections of, or the entire the strip
 *
 * In order to keep the code simple, you will only see the last colour definition. Uncomment the one you want to see.
 * 
 * http://fastled.io/docs/3.1/group___colorutils.html
 * https://github.com/FastLED/FastLED/wiki/Pixel-reference#predefined-colors-list
 *
 */

void fill_colours () {                                                // Several different ways to fill the strand with a solid colour.

// Colours defined for below
long firstval = 0xff00ff;
CRGB rgbval(50,0,500);
CHSV hsvval(100,255,200);
uint8_t startpos = 0;
int endpos = NUM_LEDS-1;


// fill_solid section 
//  fill_solid(leds,NUM_LEDS, firstval);                        // A 'long' RGB value
//  fill_solid(leds, NUM_LEDS, CRGB::HotPink);                  // https://github.com/FastLED/FastLED/wiki/Pixel-reference#predefined-colors-list
//  fill_solid(leds, NUM_LEDS, rgbval);                         // 8 bit values inside the colour definition
//  fill_solid(leds, NUM_LEDS, hsvval);                         // 8 bit values inside the colour definition

  fill_solid(leds, 5, rgbval);
  fill_solid(leds+5,5, CRGB::Green);
  fill_solid(leds+10,5, hsvval);

// fill_gradient section
//  fill_gradient_RGB(leds, startpos, 0x000011, endpos, 0x110000);   // You can mix and match long values and CRGB values. Remember, endpos goes up to NUM_LEDS-1
//  fill_gradient_RGB(leds, NUM_LEDS, CRGB(50,0,200), CRGB(80,200,240));  // up to 4 CRGB (or long) values

//FORWARD_HUES, BACKWARD_HUES, SHORTEST_HUES, LONGEST_HUES
//  fill_gradient(leds, startpos, CHSV(50, 255,255) , endpos, CHSV(150,255,255), SHORTEST_HUES);
//  fill_gradient(leds, NUM_LEDS, CHSV(50, 255,255), CHSV(100,255,255), LONGEST_HUES);    // up to 4 CHSV values

// fill_rainbow section
//  fill_rainbow(leds, NUM_LEDS, thishue, Hue_inc);            // Use FastLED's fill_rainbow routine.
//  fill_solid(leds,NUM_LEDS,0);                                // Clear the strip for. . . 
//  fill_rainbow(leds+1, NUM_LEDS-2, thishue, Hue_inc);        // One pixel border at each end.

}
