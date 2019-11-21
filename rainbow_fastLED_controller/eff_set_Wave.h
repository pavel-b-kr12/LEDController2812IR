//http://fastled.io/docs/3.1/group__lib8tion.html


void wave_H() //!fix разрыв
{
	fill_solid(leds, NUM_LEDS, CHSV(indexOrBits<250?indexOrBits:gHue,effLength,effFade)); //bg

	//idex_f+=effSpeed/50.+0.01;

	idex=map(beat8or16(effSpeed),0,255,0,NUM_LEDS-1);

	for(NUM_LEDS_type i=0;i<effLengthH;i++)
	{
		NUM_LEDS_type x=(idex+i)%NUM_LEDS;
		leds[x]=CHSV(indexOrBits<250?indexOrBits:gHue +effSpeedH,255,	sin8(i*255/effLengthH));
	}
}

void gen_wave_H_moveAll() //!fix разрыв
{
	moveOutAllRemainFirst();

	idex16+=1+effSpeed/32;//beat8or16(effLength);
	idex16%=NUM_LEDS;
	//idex_f+=effLength/50.+0.01;

	byte val=255;
	switch(indexOrBits%4)
	{
		case 0: val= sin8(idex16*255/effLengthH); break;
		case 1: val= random8(0, sin8(idex*255/effLengthH) ); break;
		case 2: val= idex16%(2560/effLengthH); break;

	}
	
	leds[0]=CHSV(effSpeedH + ( indexOrBits<250?effSpeedH:gHue/16 ) ,255,	val);
}


void gen_wave_H_moveAll_blinkRand() //!fix разрыв
{
	moveOutAllRemainFirst();

	//idex16=beat8or16(effSpeed);
	//idex_f+=effSpeed/50.+0.01;

	byte val=255;
	switch((indexOrBits/4+1)%6)
	{
		case 0: val= gHue; break;
		case 1: 
			idex16=beat8or16(effLength); 
			val= idex16;
		break;
		case 2:
			idex16++;
			val= sin8(idex16*255/effLength);
		break;
		case 3:
			idex16++;
			val= random8(0, sin8(idex16*255/effLength) );
		break;
		case 4:
			idex16++;
			val= idex16%(2560/effLength);
		break;
		case 5:
			idex16++;
			if(idex16%256<125) val=idex16*255/effLength;
			else val=255;
		break;
	}
	
	leds[0]=CHSV(effSpeedH + ( indexOrBits<250?effSpeedH:gHue/16 ) ,255,	val);


	if(effLength<128)
	{
		//blinkSaveCodedB();
		//	void blinkSaveCodedB() //to common TODO test range
	{
		// if(val<10)
		// {
		// 	leds[0].b=0;
		// }
		// else
			leds[0].b=1+leds[0].b/10; //code wave to ch B


		for(NUM_LEDS_type i=1;i<NUM_LEDS-1;i++) //^ -1 why this need
		{ //# not as expected, but not bad
			if(leds[i].b>0)
			{
				byte chanseBlink=random8(122+effFade/2); //25*2

				if(leds[i].b<26)
				{
					if(chanseBlink<leds[i].b)
					{
						leds[i].r=255;
						leds[i].g=255;
						leds[i].b=220+leds[i].b;
					}
				}
				else
				{
					if(chanseBlink*2>-220+leds[i].b)
					{
						leds[i].r=0;
						leds[i].g=0;
						leds[i].b=-220+leds[i].b;
					}
				}
			}
		}
	}
	}
}


void gen_wave_H_v2_moveAll_blinkRand() //!fix разрыв
{

	moveOutAllRemainFirst();
	byte val=0;
	switch((indexOrBits/10)%5)
	{
		case 0: val= gHue; break;
		case 1: val= sin8(millis()/(1+effSpeed));  break; //leds[210]=CRGB::Blue;
		case 2: val= triwave8(millis()/(1+effSpeed)); break;
		case 3: val= millis()/(1+effSpeed);  break; //leds[210]=CRGB::Red;
		case 4: val= 255-(byte)(millis()/(1+effSpeed));  break;
	}
	//val=val*beatsin8(1+effLength/2,128,255)/255;


	leds[0]=CHSV(gColor.r + gHue/(1+effLengthH ) ,88,	val);
	leds[0] .fadeToBlackBy( beatsin8(40+effLength,0,1+effSpeedH*0.9) );

	if( i_eff%(1+effFade/32)<2 )
	for (int i = 20; i < NUM_LEDS; ++i)
	{
		 leds[i].fadeToBlackBy( 1 );
	}


	// 	if(effLength<128)
	// {
	// 	blinkSaveCodedB();
	// }
}

/*
попроще, и посложнее
youtu.be/uwffJtgg3BI
youtube.com/watch?v=fBmtSmy2CPQ
вариаций много. Может выбрать по этим видео, указав на время. Могу снять видео с реальной рентой или дать ему "макет"
*/