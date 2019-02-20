 //This uses beats, blend and the fill gradient functions to blend a couple of waves together. Again, try making changes to this and see how it looks.
void blendwave() {

  byte speed = beatsin8(1+effSpeed/2,0,255);

  gColor = blend(CHSV(beatsin8(3,0,255),255,255), CHSV(beatsin8(4,0,255),255,255), speed);
  gColorBg = blend(CHSV(beatsin8(4,0,255),255,255), CHSV(beatsin8(3,0,255),255,255), speed);

  uint8_t loc1 = beatsin8(10,0,NUM_LEDS-1);
  //uint8_t loc2 = effLength;
  
  if(effLength<20)
  fill_gradient_RGB(leds, 0, gColorBg, loc1, gColor);
  else
  fill_gradient_RGB(leds, loc1, gColorBg, lerp8by8(0,NUM_LEDS-1,effLength), gColor);
}