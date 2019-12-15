//A rainbow moving back and forth

void rainbow_beat2() {
  
  uint8_t beatA = beatsin8(5+effSpeed/8, 0, 255);  // 17                    // Starting hue
  uint8_t beatB = beatsin8(4+effSpeed/16, 0, 255); // 13
  fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, effLength/4);

} 