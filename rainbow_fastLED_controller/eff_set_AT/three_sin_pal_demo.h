/* three_sin_pal_demo
 *
 * By: Andrew Tuline
 *
 * Date: March, 2015
 *
 * 3 sine waves, one for each colour. I didn't take this far, but you could change the beat frequency and so on. . .
 *
 */


void three_sin_beatsin8_reset()
{
 wave1=0;                                                  // Current phase is calculated.
 wave2=0;
 wave3=0;

 lvl1 = 80;                                            // Any result below this value is displayed as 0.
 lvl2 = 80;
 lvl3 = 80;

 mul1 = 7;                                            // Frequency, thus the distance between waves
 mul2 = 6;
 mul3 = 5;
}

void three_sin_beatsin8() {
  
  wave1 += beatsin8(8+effSpeed/16,-4,4);
  wave2 += beatsin8(13+effSpeed/16,-2,2);
  wave3 += beatsin8(10+effSpeed/16,-3, 3);

  for (int k=0; k<NUM_LEDS; k++) {
    uint8_t tmp = sin8(mul1*k + wave1) + sin8(mul1*k + wave2) + sin8(mul1*k + wave3);
    leds[k] = ColorFromPalette(currentPalette, tmp, 255);
  }
  
}

void three_sin_beatsin8_ChangeMe() {
  
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if( lastSecond != secondHand) {
    lastSecond = secondHand;
    CRGB p = CHSV( HUE_PURPLE, 255, 255);
    CRGB g = CHSV( HUE_GREEN, 255, 255);
    CRGB u = CHSV( HUE_BLUE, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;

    switch(secondHand) {
      case  0: targetPalette = RainbowColors_p; break;
      case  5: targetPalette = CRGBPalette16( u,u,b,b, p,p,b,b, u,u,b,b, p,p,b,b); break;
      case 10: targetPalette = OceanColors_p; break;
      case 15: targetPalette = CloudColors_p; break;
      case 20: targetPalette = LavaColors_p; break;
      case 25: targetPalette = ForestColors_p; break;
      case 30: targetPalette = PartyColors_p; break;
      case 35: targetPalette = CRGBPalette16( b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); break;
      case 40: targetPalette = CRGBPalette16( u,u,u,w, u,u,u,w, u,u,u,w, u,u,u,w); break;
      case 45: targetPalette = CRGBPalette16( u,p,u,w, p,u,u,w, u,g,u,w, u,p,u,w); break;
      case 50: targetPalette = CloudColors_p; break;
      case 55: targetPalette = CRGBPalette16( u,u,u,w, u,u,p,p, u,p,p,p, u,p,p,w); break;
      case 60: break;
    }
  }
  
}

void three_sin_pal_demo () {
	three_sin_beatsin8_ChangeMe();

	nblendPaletteTowardPalette( currentPalette, targetPalette, maxChanges);
	EVERY_N_MILLISECONDS(20)
	three_sin_beatsin8(); 
}