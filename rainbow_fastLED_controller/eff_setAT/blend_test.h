CRGB endclr;
CRGB midclr;

void cycle() {
  fill_gradient_RGB(leds, 0, endclr, NUM_LEDS/2, midclr);
  fill_gradient_RGB(leds, NUM_LEDS/2+1, midclr, NUM_LEDS, endclr);
}

void blend_test(){ 
//currentBlending=effLength<127?NOBLEND : LINEARBLEND;
//10+effSpeed/8

  uint8_t speed = beatsin8(6,0,255);
  endclr = blend(CRGB::Aqua, CRGB::Orange, speed);
  midclr = blend(CRGB::Orange, CRGB::Aqua, speed);
  cycle();
}

