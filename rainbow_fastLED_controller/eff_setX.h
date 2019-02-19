
void testPower()
{
	FastLED.clear();
	fill_solid(leds, (effSpeed)%NUM_LEDS, CRGB::White); //60 LEDs => 40mA +32mA/LED @4.5v  . Or 2x less @3v
	//FastLED.setBrightness( effLength ); 
}

void test_gDelay()
{
	FastLED.clear();
	gDelay=effSpeed;

	byte t=millis()%256;
	if(t>thissat) 	ibright=t-thissat;
	else 			ibright=255-thissat+t;

	thissat=t;

	leds[idex] =CHSV(ibright*16,255,50+gDelay); 

	idex++;	if(idex>=NUM_LEDS) idex=0;
}

void palette_pipette()
{
	
}

void test_palettes()
{
	
}

void test_gradient()
{
	
}

void test_blend()
{
	
}

void test_easing()
{
	
}

void test_RAWcolorMath()
{
	
}



void iterateRAWint()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
  	leds[i] =millis()*effSpeed*4+i*effLength*4;  // i*(int)(millis()/2000);
  }
}

