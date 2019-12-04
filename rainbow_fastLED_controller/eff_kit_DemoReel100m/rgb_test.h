// Шаг плавного гашения светодиодов
#define RGB_TST_FADEOUT_STEP   5

void rgb_test_tick()
{
	byte h=0;
  switch(eff_stage%4)
  {
	  // бегущая точка с плавным fade-out
	  case 0:
	  case 2:
	  {
		fadeToBlackBy(leds, NUM_LEDS,RGB_TST_FADEOUT_STEP);
		h=(millis()<1000)?effects_i/100:millis()/2000*33;
		leds[DotPos]= CHSV(h,255,255);
		DotPos++;
		DotPos=DotPos%NUM_LEDS;

	  }
	  break;
	  case 1:
	  {
		fadeToBlackBy(leds, NUM_LEDS,RGB_TST_FADEOUT_STEP);
		leds[DotPos]= CHSV(gHue2,255,255);
		DotPos++;
		DotPos=DotPos%NUM_LEDS;
	  }
	  break;
	  case 3:
	  {
		fadeToBlackBy(leds, NUM_LEDS,RGB_TST_FADEOUT_STEP);
		h=(millis()<1000)?effects_i/512:millis()/2000*33;
		leds[DotPos]= CHSV(effects_i/512,sin8(effects_i*5*eff_stage),qadd8(20,sin8(effects_i*eff_stage)));
		DotPos++;
		DotPos=DotPos%NUM_LEDS;
	  }
	  break;
  }

}
