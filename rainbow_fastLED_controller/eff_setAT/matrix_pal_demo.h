#ifdef Cube4MCU
void matrixCube2()
{
	for(byte corner_i=0;corner_i<4;corner_i++)
	{
		for(byte axi=0;axi<3;axi++)
		{
			//for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
			{
				if(axi==1)
				{
				
				byte s=random8();
				byte b=random8();
				
				NUM_LEDS_type x= NUM_LEDS_edge*(corner_i*3+axi);
				NUM_LEDS_type x9=NUM_LEDS_edge*(corner_i*3+axi) +(NUM_LEDS_edge-1);
				
				if(corner_i==0 || corner_i==2)
				{
					moveOutAllRemainFirst_ret_last(x9,x);//!? -1 
					leds[x9]=CHSV(110+i_eff/64%16, s>100?255:s*2, b>240?b: b>200?b/4:0);
				}
				else
				if(corner_i==1 || corner_i==3)
				{
					moveOutAllRemainFirst_ret_last(x,x9);//!? -1 
					leds[x]=CHSV(110+i_eff/64%16, s>100?255:s*2, b>240?b: b>200?b/4:0);
				}


				
				
				}
				
				else
				{
					if(corner_i==1 || corner_i==3) //top
					{
						for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
						{
							leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=
							CHSV(140+beatsin8(3+effSpeedH, 0, 30)+beatsin8(1+effSpeedH*3, 0, 10)+sin8(millis()/32+i)/16 ,
							188,
							126+ beatsin8(2+effSpeedH*2, 0, 32)+sin8(millis()/64+i)/8); 
						}
					}
				}
					
				
			}
		}
	}

}

void matrixCube() //TODO
{
	for(byte corner_i=0;corner_i<4;corner_i++)
	{
		for(byte axi=0;axi<3;axi++)
		{
			//for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
			{
				if(corner_i==1 || corner_i==3)
				{
					moveOutAllRemainFirst_ret_last(0+NUM_LEDS_edge*(corner_i*3+axi),(NUM_LEDS_edge-1)+NUM_LEDS_edge*(corner_i*3+axi));//!? -1 
					leds[0+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(110+i_eff/64%20, 255, random8()>220?255:0);
				}
				else
				{
					moveOutAllRemainFirst_ret_last((NUM_LEDS_edge-1)+NUM_LEDS_edge*(corner_i*3+axi),0+NUM_LEDS_edge*(corner_i*3+axi));//!? -1 
					leds[NUM_LEDS_edge-1+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(100+i_eff/64%20, 255, (millis()/100%16<2 )? 255:0);
				}
			}
		}
	}

}
#endif
void Matrix() {                                   //-m29-ONE LINE MATRIX
  byte rand = random8(0, 100);

  if(effLength<125) thishue = effLength*2;
  else 
    if(effLength<200) thishue = gHue*effSpeed/16; //!tst //gHue*(effLength-124)/16;
  else 
  { //single color batch
    if(rand<90)
    thishue +=2*(1+effSpeed)/16;
  }

  leds[0] = CHSV(thishue, 255, rand > 90 ? 255 : 0);

  copy_led_array();
  for(NUM_LEDS_type i = 1; i < NUM_LEDS; i++ ) {
    leds[i] = ledsX_[i - 1];
  }
}

/* -------------------------------- matrix_pal_demo
 *
 * Originally By: funkboxing LED
 *
 * Modified a LOT by: Andrew Tuline
 *
 * Date: July, 2015
 * 
 * Various coloured characters going up/down the strand, a la 'The Matrix'. This highly modified version uses non-blocking
 * delays as well as colorPalette lookups and other variables such as direction, speed and background colours.
 *
 */

//huerot =   0;                                     // Does the hue rotate? 1 = yes

void matrix_() {                                               // One line matrix

  if (huerot) palIndex++;
  
  if (random8() > effLength) {
    if (thisdir == 0)
      leds[0] = ColorFromPalette(currentPalette, palIndex, thisbri, currentBlending); 
    else
      leds[NUM_LEDS-1] = ColorFromPalette( currentPalette, palIndex, thisbri, currentBlending);
  } else {
    if (thisdir == 0)
      leds[0] = CHSV(bgH, thissat, bgbri); 
    else
      leds[NUM_LEDS-1] = CHSV(bgH, thissat, bgbri);
  }

  if (thisdir == 0) {
    for (NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (NUM_LEDS_type i = 0; i < NUM_LEDS-1 ; i++ ) leds[i] = leds[i+1];
  }
  
} 


// Also RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.

void matrix_ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 25;                // Change '25' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.

  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: 	gDelay=50; palIndex=95; bgH=140; bgbri=4; huerot=0; break;
      case  5: targetPalette = OceanColors_p; thisdir=1; bgbri=0; huerot=1; break;
      case 10: targetPalette = LavaColors_p; gDelay=30; palIndex=0; bgH=50; bgbri=8; huerot=0; break;
      case 15: targetPalette = ForestColors_p; gDelay=80; bgbri = 16; bgH=96; palIndex=random8(); break;
      case 20: palIndex=random8(); huerot=1; break;
      case 25: break;
    }
  }

} 


void matrix_pal_demo () {

  matrix_ChangeMe();

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  matrix_();

}