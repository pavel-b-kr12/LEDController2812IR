


void fillStriped()
{
	if(effFade<100) fadeToBlackBy(leds, NUM_LEDS, effFade/4);

	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		// leds[i] = (
		//   ((byte)(i+i_eff/(effSpeed+1)))
		//   %effLength<(1+effLength2)
		//   )? gColor:gColorBg;
		bool bDraw=beat8 (effSpeed,i*effLength)<indexOrBits;
		if(bDraw) leds[i] = gColor;
		else
		if(effFade>200)  leds[i] = gColorBg;
	}
}

void fillStripedInvert()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    if( beat8 (effSpeed,i*effLength)<indexOrBits ) leds[i] = CRGB(255,255,255)-leds[i];
  }
}

void fillStripedFillRainbow()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    leds[i] = beat8 (effSpeed,i*effLength)<127 ? gColor:CHSV(beat8 (effSpeedH,i*effLengthH),255,255);
  }
}


void fillByPalette()
{
  #ifdef eff_setX
  set_currentPalette(indexOrBits/4);
  #endif
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    leds[i] = ColorFromPalette(currentPalette, beat8 (i*effLength+i_eff/effSpeed,NUM_LEDS-1),255,(effFade>128)?LINEARBLEND:NOBLEND);
  }
}

void fillByPalettesBlend_moving()
{
  #ifdef eff_setX
  set_currentPalette(indexOrBits/4);
  #endif
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    leds[i] =blend(
    // ColorFromPalette(currentPalette, beat8 (effSpeed,i_eff*effLength/8),255,(indexOrBits>128)?LINEARBLEND:NOBLEND),
    // ColorFromPalette(LavaColors_p, beat8 (effSpeed,i_eff*effLength/8),255,(indexOrBits>128)?LINEARBLEND:NOBLEND),
     ColorFromPalette(currentPalette, i+i_eff,255,(effFade>128)?LINEARBLEND:NOBLEND),
     ColorFromPalette(LavaColors_p, i+i_eff/4,255,(effFade>128)?LINEARBLEND:NOBLEND),
      sin8(i*4)
      );
  }
}

//------------------------------------------------------------------------------ fill fade
void fillFadeChangeAll()
{
  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,i_eff%255));

  if(i_eff%255 > effLength) //flash over effLength
  {
    ihue=random8();
    isat=random8();
  }
}
void fillFadeChangeAll_beat8()
{
  ibright=beat8(effSpeed);
  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,ibright));

  //if(i_eff%255 > effLength)  //other eff
  if(ibright > effLength) //flash above effLength
  {
    ihue=gHue;
    isat=random8();
  }
}

void fillFadeChangeAll_beatsin8()
{
  ibright=beatsin8(effSpeed,0); //!
  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,ibright));

  if(ibright <effLength) //flash under effLength
  {
    ihue=random8();
    isat=random8();
  }
}

//------------------------------------------------------------------------------

void fadeEvenUneven()
{
  ibright=beatsin8(effSpeed,0,255);
  byte ibright2=beatsin8(effSpeed,0,255,0,effLength); //w phase offset

  if(ibright<4)
  {
    if(random8()<32)  ihue= gHue;
  }
  else
  if(ibright2<4)
  {
    if(random8()<32)  thishue= random8();
  }

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
      leds[i] =i%2?
      CHSV(ihue,255,ibright): 
      CHSV(thishue,255,ibright2);
  }
}
void fadeEvenUnevenDif()
{
  if(i_eff%500==0) ihue= gHue;

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    if(i%2)
    {
      leds[i] = CHSV(ihue,255,beatsin8(effLength+effSpeed/4,0));
    }
    else
      leds[i] = CHSV(ihue+gHue,255,beatsin8(effLength,127));
  }
}

//------------------------------------------------------------------------------

void LinesOpposit()
{
	fadeToBlackBy(leds, NUM_LEDS, effFade/4);
	
	NUM_LEDS_type valL=qsuba (beatsin8(2+effSpeed,0,NUM_LEDS),NUM_LEDS*0.3);
	NUM_LEDS_type valR=NUM_LEDS-qsuba (beatsin8(3+effSpeed,10,NUM_LEDS),effLength);

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
  	if(i<valL) leds[i] =gColor;

  	if(i>valR) leds[i] +=CHSV(gHue,255,255); //already qadd8 inside
  }

  	EVERY_N_SECONDS(5)
  	{
  		gColor=CHSV(random8(),random8(4)*63,255);
  	}

	
}


//! встречные столбы с разной частотой. Перекрытие цвета




//! BrightWave on pre=generated

//! Bright off from sides to central point 

//------------------------------------------------------------------------------

void painter_moving()
{
	// move pos for paint
	idex=( 
		beatsin8(5) + 
		beatsin8(1+effSpeed/32)-
		beatsin8(1+effSpeedH/16, 0, 1+NUM_LEDS/effLength)
		) % NUM_LEDS;

	//pant at pos 
	leds[idex]=CHSV(colorize(),255,effLengthH>200?
	 255:
	 //or not paint
	 (
	  (beatsin8(2+effSpeed/32) + beatsin8(1+effSpeed/64) ) > ((millis()/256)%128) ) ? 255 : 0 
	   //! add also bright fading from star paint pos
	 );
}

void painter_H_by_Speed_moving()
{
	NUM_LEDS_type	N=( 
		beatsin8(4) + 
		beatsin8(3+effSpeed/16)-
		beatsin8(effSpeedH/4, 0, 2+NUM_LEDS/effLength)
		) % NUM_LEDS;

	thishue=abs(idex_last-N)*16;
	if(i_eff%2)
	idex_last=N;

	fadeToBlackBy(leds, NUM_LEDS, effFade/32);

	leds[N]=CHSV(thishue,255,255);


}


void painter_beat_moving() //##crash
{

	int t= (millis()/10)%256;
	if(t>wave1 || t<2) //random nex start or stop drawing
	{
		wave1=t+random8()*2;
		thisdir=!thisdir; //now draw or not 

	}


	NUM_LEDS_type	N=( 
		beatsin8(4) - 
		beatsin8(3+effSpeed/16)+
		beatsin8(1+effSpeedH/4, 0, 2+NUM_LEDS/effLength)
		) % NUM_LEDS;

    if(!thisdir) {leds[N]=0; return; }

		bool bv = beatsin8(10+effSpeed/4)<effLength;

		leds[N]=CHSV(colorize(),255,bv?255:0);
}

void painterBlend_moving()
{
	byte t= (millis()/10)%256;
	if(t>wave1|| t<4) //random nex start or stop drawing
	{
		wave1=t+random8()*2;
		thisdir=!thisdir; //now draw or not 
	}

	//if(!thisdir) {leds[N]=0; return; }


	// move pos for paint
	idex=( 
		beatsin8(2) + 
		beatsin8(3+effSpeed/32)+
		beatsin8(effSpeedH/16, 0, 2+NUM_LEDS/effLength)
		) % NUM_LEDS;

	if(thisdir)
		leds[idex]=CHSV(colorize(),255,255);
	else
		leds[idex]=leds[idex]- CRGB(122,122,122); //CRGB(2,2,3);

}




void move_newColor_toAndFrom_center()
{
	if(i_eff%(4+effLength)==0)
	{
		thisdir=!thisdir;

		if(thisdir)
		{
			leds[0]=CHSV(random8(),255,255);
			leds[NUM_LEDS-1]=leds[0];
		}
		else 
		{
			leds[NUM_LEDS/2]=CHSV(random8(),255,255);
			leds[NUM_LEDS/2-1]=CHSV(random8(),255,255);
		}
	}



	if(thisdir)
		move_toCenter_RemainFirst();
	else
		move_fromCenter_RemainFirst();
}

void mover_lim_mark()
{

 	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
  	if(leds[i].r==255) leds[i].nscale8(255);
  	else leds[i].nscale8(effFade);
  }
 if(indexOrBits%2==0 && leds[idex].r!=255) leds[idex]=0;


 	NUM_LEDS_type lim_M=beatsin8(3+effSpeed/64, NUM_LEDS/2+1, NUM_LEDS-2);
 	NUM_LEDS_type lim_m=beatsin8(2+effSpeed/64, 2, NUM_LEDS/2-1);

 	if(leds[lim_M].r!=255) leds[lim_M]=CRGB(0,111,0);
 	if(leds[lim_m].r!=255) leds[lim_m]=CRGB(0,111,111);

 	if(idex>=lim_M)
 	{
 	 thisdir =false;  thishue=255;
 	 leds[lim_M]=CRGB::Red;
 	}
 	else
 	if(idex<=lim_m)
 	{
 	 thisdir =true;   thishue=255;
 	  leds[lim_m]=CRGB::Red;
 	}
 	//else
 	{
 		idex+=thisdir?1:-1;  thishue-=2; //! map(time_from_bounce, 0, 1000, 255,0)

    if(indexOrBits<128)
 		 leds[idex]=CHSV(thishue,255,255);
    else
     leds[idex]= ColorFromPalette(HeatColors_p, thishue, map(thishue,255,0,255,100), LINEARBLEND);
 	}

}


void eff_sin_R_G_B() //!!fix not as in sim
{
	for (NUM_LEDS_type i=0; i<NUM_LEDS; i++)
	{
		//msg_buffer[i]=(int) ( (sin(i/1.+millis()/1000.) +1) *255);

		leds[i].r= (sin8(i*3*effSpeed+millis()/effLength));
		leds[i].g= (sin8(i*3*effSpeed+effLength+millis()/effLengthH));
		leds[i].b= (sin8(i*3*effSpeed+effLength*2+millis()/effLengthH));

	}
}