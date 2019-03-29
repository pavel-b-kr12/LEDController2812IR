
void soundmems_pal_() {

  int n;
  n = analogRead(MIC_PIN);                                    // Raw reading from mic
  n = qsuba(abs(n-effLength*2), 10);                                  // Center on zero and get rid of low level noise
  CRGB newcolour = ColorFromPalette(currentPalette, constrain(n,0,255), constrain(n,0,255), currentBlending);
  nblend(leds[0], newcolour, 128);
  
  for (int i = NUM_LEDS-1; i>0; i--) {
    leds[i] = leds[i-1];
  }
  
} // soundmems()


void soundmems_pal() {

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    
    for (int i = 0; i < 16; i++) {
      targetPalette[i] = CHSV(random8(), 255, 255);
    }
  }
  
  EVERY_N_MILLISECONDS(100) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, 24);
  }
  
  soundmems_pal_();
}

void soundmems_H_V() // Basic code to read from the Sparkfun INMP401 microphone and display CHSV output.
{

  int n;
  n = analogRead(MIC_PIN);
  n = qsuba(abs(n-effLength*2), effLengthH);
//  Serial.println(n);
  nblend(leds[0], CHSV(n,255,n), 128);
  for (int i = NUM_LEDS-1; i>0; i--) {
    leds[i] = leds[i-1];
  }

}




