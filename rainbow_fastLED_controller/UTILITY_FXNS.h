// Use qsuba for smooth pixel colouring and qsubd for non-smooth pixel colouring
#define qsubd(x, b) ((x>b)?b:0)                               // Clip. . . . A digital unsigned subtraction macro. if result <0, then x=0. Otherwise, x=b.
#define qsuba(x, b) ((x>b)?x-b:0)                             // Level shift. . . Unsigned subtraction macro. if result <0, then x=0. Otherwise x=x-b.


void fillAll_(byte r, byte g, byte b) {
  fill_solid(leds, NUM_LEDS, CRGB(r,g,b)); 
  //FastLED.show();
}

void fillAll()
{
 fill_solid(leds, NUM_LEDS, gColor); 
}

// void fadeall(){ 
  // for(int i = 0; i < NUM_LEDS; i++)  leds[i].nscale8(250); 
// }
//fadeToBlackBy(leds, NUM_LEDS, effFade);

byte colorize_sw_indexOrBits()
{
  if(indexOrBits>200)	return posX; //* //! lerp cColor gColorBg
  if(indexOrBits>150)	return sin8(posX*effLength); //*
  if(indexOrBits>120)	return gHue; //*
  if(indexOrBits>100)	return gColor.r; //*
  if(indexOrBits>60)	return beatsin8(effSpeed); //*
  if(indexOrBits>30)	return beatsin8(effLength); //*
  if(indexOrBits>10)	return gColor.r+random8(effLength); //*
  else					return random8();
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}

NUM_LEDS_type oppositeLEDinCircle(NUM_LEDS_type i)
{
  return (i<NUM_LEDS/2)? (i+NUM_LEDS/2) : (i-NUM_LEDS/2);
}

//------------------------------------- UTILITY FXNS --------------------------------------
//---SET THE COLOR OF A SINGLE RGB LED
// void set_color_led(int adex, int cred, int cgrn, int cblu) {
  // leds[adex].setRGB( cred, cgrn, cblu);  //compile down into exactly the same number of machine instructions. 
  /// leds[i]=CRGB(255, 255, 0);  //leds[i]=CHSV(255, 255, 0); 
    // leds[Pixel].r = red;
  // leds[Pixel].g = green;
  // leds[Pixel].b = blue;
// }

//---FIND INDEX OF HORIZONAL OPPOSITE LED
int horizontal_index(int i) {
  //-ONLY WORKS WITH INDEX < TOPINDEX
  if (i == BOTTOM_INDEX) {
    return BOTTOM_INDEX;
  }
  if (i == CENTER_TOP_INDEX && EVENODD == 1) {
    return CENTER_TOP_INDEX + 1;
  }
  if (i == CENTER_TOP_INDEX && EVENODD == 0) {
    return CENTER_TOP_INDEX;
  }
  return NUM_LEDS - i;
}

//---FIND INDEX OF ANTIPODAL OPPOSITE LED
int antipodal_index(int i) {
  int iN = i + CENTER_TOP_INDEX;
  if (i >= CENTER_TOP_INDEX) {
    iN = ( i + CENTER_TOP_INDEX ) % NUM_LEDS;
  }
  return iN;
}

//---FIND ADJACENT INDEX CLOCKWISE
int adjacent_cw(int i) {
  if (i < NUM_LEDS - 1)
    return  i + 1;
  else 
    return  0;
}

//---FIND ADJACENT INDEX COUNTER-CLOCKWISE
int adjacent_ccw(int i) {
  if (i > 0)
     return i - 1;
  else
    return NUM_LEDS - 1;
}

#ifndef saveMem
void copy_led_array() {
	memmove( &ledsX_[0], &leds[0], NUM_LEDS * sizeof( CRGB) ); // // Copy NUM_LEDS led colors from leds[src .. src+NUM_LEDS] to ledsX_[dest .. dest+NUM_LEDS]
  // for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
  //   ledsX_[i][0] = leds[i].r;
  //   ledsX_[i][1] = leds[i].g;
  //   ledsX_[i][2] = leds[i].b;
  // }
}
#endif
