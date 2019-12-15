/* fill_grad
 *
 * By: Andrew Tuline
 *
 * Date: August, 2015
 *
 * Here's a simple method to blend between a couple of colours across a strand of LED's.
 *
 * It uses FastLED's:
 *
 * - fill_gradient() function to blend between two colours.
 * - beatsin8() to provide a time based smooth varying input to blend().
 *
 * An issue when using the fill_gradient is which way you want the gradient to sweep around the colour wheel. Options are:
 *
 * FORWARD_HUES: hue always goes clockwise
 * BACKWARD_HUES: hue always goes counter-clockwise
 * SHORTEST_HUES: hue goes whichever way is shortest and is the DEFAULT
 * LONGEST_HUES: hue goes whichever way is longest
 *
 * When the start and end colours are animated, the sweep will flip in the other direction at certain points, thus causing a disruption of the smooth gradient.
 * 
 * This routine demonstrates one method to animate the start/end hues and to ensure the fill_gradient remains consistently smooth.
 *
 */


void fill_grad() {
  
  uint8_t starthue = beatsin8(7, 0, effLength);
  uint8_t endhue = beatsin8(9, effSpeed, 255);
  
  if (starthue < endhue) {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), FORWARD_HUES);    // If we don't have this, the colour fill will flip around. 
  } else {
    fill_gradient(leds, NUM_LEDS, CHSV(starthue,255,255), CHSV(endhue,255,255), BACKWARD_HUES);
  }
  
} 