


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
  fill_solid(leds, NUM_LEDS, CHSV(thishue,thissat,i_eff%255));

  if(i_eff%255 > effLength) //flash over effLength
  {
    thishue=random8();
    thissat=random8();
  }
}
void fillFadeChangeAll_beat8()
{
  thisbri=beat8(effSpeed);
  fill_solid(leds, NUM_LEDS, CHSV(thishue,thissat,thisbri));

  //if(i_eff%255 > effLength)  //other eff
  if(thisbri > effLength) //flash above effLength
  {
    thishue=gHue;
    thissat=random8();
  }
}

void fillFadeChangeAll_beatsin8()
{
  thisbri=beatsin8(effSpeed,0); //!
  fill_solid(leds, NUM_LEDS, CHSV(thishue,thissat,thisbri));

  if(thisbri <effLength) //flash under effLength
  {
    thishue=random8();
    thissat=random8();
  }
}

//------------------------------------------------------------------------------

void fadeEvenUneven()
{
  thisbri=beatsin8(effSpeed,0,255);
  byte thisbri2=beatsin8(effSpeed,0,255,0,effLength); //w phase offset

  if(thisbri<4)
  {
    if(random8()<32)  thishue= gHue;
  }
  else
  if(thisbri2<4)
  {
    if(random8()<32)  thishue= random8();
  }

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
      leds[i] =i%2?
      CHSV(thishue,255,thisbri): 
      CHSV(thishue,255,thisbri2);
  }
}
void fadeEvenUnevenDif()
{
  if(i_eff%500==0) thishue= gHue;

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    if(i%2)
    {
      leds[i] = CHSV(thishue,255,beatsin8(effLength+effSpeed/4,0));
    }
    else
      leds[i] = CHSV(thishue+gHue,255,beatsin8(effLength,127));
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
	posX=( 
		beatsin8(5) + 
		beatsin8(1+effSpeed/32)-
		beatsin8(1+effSpeedH/16, 0, 1+NUM_LEDS/effLength)
		) % NUM_LEDS;

	//pant at pos 
	leds[posX]=CHSV(colorize_sw_indexOrBits(),255,effLengthH>200?
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

	thishue=abs(posX_last-N)*16;
	if(i_eff%2)
	posX_last=N;

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

		leds[N]=CHSV(colorize_sw_indexOrBits(),255,bv?255:0);
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
	posX=( 
		beatsin8(2) + 
		beatsin8(3+effSpeed/32)+
		beatsin8(effSpeedH/16, 0, 2+NUM_LEDS/effLength)
		) % NUM_LEDS;

	if(thisdir)
		leds[posX]=CHSV(colorize_sw_indexOrBits(),255,255);
	else
		leds[posX]=leds[posX]- CRGB(122,122,122); //CRGB(2,2,3);

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
 if(indexOrBits%2==0 && leds[posX].r!=255) leds[posX]=0;


 	NUM_LEDS_type lim_M=beatsin8(3+effSpeed/64, NUM_LEDS/2+1, NUM_LEDS-2);
 	NUM_LEDS_type lim_m=beatsin8(2+effSpeed/64, 2, NUM_LEDS/2-1);

 	if(leds[lim_M].r!=255) leds[lim_M]=CRGB(0,111,0);
 	if(leds[lim_m].r!=255) leds[lim_m]=CRGB(0,111,111);

 	if(posX>=lim_M)
 	{
 	 thisdir =false;  thishue=255;
 	 leds[lim_M]=CRGB::Red;
 	}
 	else
 	if(posX<=lim_m)
 	{
 	 thisdir =true;   thishue=255;
 	  leds[lim_m]=CRGB::Red;
 	}
 	//else
 	{
 		posX+=thisdir?1:-1;  thishue-=2; //! map(time_from_bounce, 0, 1000, 255,0)

		if(indexOrBits<128)
		 leds[posX]=CHSV(thishue,255,255);
		else
		 leds[posX]= ColorFromPalette(HeatColors_p, thishue, map(thishue,255,0,255,100), LINEARBLEND);
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
//-------------------------------------
void fillRange_anim() //!! rollover
{
	leds[0]=gColor;
	
	if(millis()/1000%2) //freeze on 2nd circle
	{
		leds[0]=gColor;
		
		if(thisdir)
		{
			pos1+=1;
			bool b=pos1<pos2;
			if(b!=thisdir)
			{
				thisdir=b;
				gColor=CHSV(random8(),255,255); // change color at 0 length
			}
		}
		else
		{
			pos2+=1;
			bool b=!((pos2-pos1)<random(10,30));
			if(b!=thisdir)
			{
				thisdir=b;
				//gColor=CHSV(random8(),255,255);
				gColor.r-=CRGB(40,20,15);  				// fade gColor at max length
			}
		}


		for(NUM_LEDS_type i=pos1%NUM_LEDS;i<pos2%NUM_LEDS;i++)
		{
			leds[i%NUM_LEDS]=gColor;
			if(i==pos2-1)
				leds[i%NUM_LEDS]+=CRGB(50,30,20); //head
			
			
			Serial.print(pos1);Serial.print(" ");
			Serial.print(pos2);Serial.print(" ");
			Serial.print(i);Serial.print(" ");
			Serial.println();
		} 

	}
	else
	{ //cell

		if(i_eff==0)
		{
			pos1=0;
			pos2=10;
			FastLED.clear();
			leds[0]=CRGB(0,0,255);
			//leds[0]=CRGB(0,0,255);
		}

		for(NUM_LEDS_type j=0;j<NUM_LEDS;j++) //?? reverse loop cause  ?Soft WDT reset
		{
			NUM_LEDS_type i=NUM_LEDS-1-j;
			Serial.println(i);
			
		
			if(leds[i].b==255)
			{
				leds[(i+1)%NUM_LEDS].b=254;
				leds[(i+1)%NUM_LEDS].r=200;
				
			}
			else if(leds[i].b>220)
			{
				leds[i].b--;
				leds[(i+1)%NUM_LEDS]=leds[i];
				leds[i].r=0; //move head
			}
			else
			{
				
				if(leds[(i-1)%NUM_LEDS].b!=0)
					leds[i].b--;
				else
				{
					if(leds[(i+1)%NUM_LEDS].r==0)
						leds[i]=0; //off end
					else
					{
						leds[(i+1)%NUM_LEDS]=0;
						leds[(i+2)%NUM_LEDS].b=255;
						
					}
				}
			}
	

		}
		
	}
}

//-------------------------------------!!
NUM_LEDS_type xx1=0;
NUM_LEDS_type xx2=10;
NUM_LEDS_type xx3=20;
NUM_LEDS_type xx4=40;
void movers()
{
	fadeToBlackBy(leds, NUM_LEDS, 55);//1+effFade/4);
	
	leds[xx1]+=CRGB(255,0,0);
	leds[xx2]+=CRGB(0,255,0);
	leds[xx3]+=CRGB(0,0,255);
	leds[xx4]+=CHSV(0,0,random8());
	
	xx1=xx1<NUM_LEDS-1?xx1+1:0;
	xx2=xx2>0?xx2-1:NUM_LEDS-1;
	xx3=beatsin8(12, 0 , NUM_LEDS-1);
	xx4=constrain(beatsin8(33, xx1 , xx2),0, NUM_LEDS-1);
}


void roll01(float *v)
{
	if(*v>=1) *v-=1;
	else if(*v<0) *v+=1;
}

NUM_LEDS_type f01toPos(float f)
{
	return constrain((NUM_LEDS_type)(f*NUM_LEDS),0,NUM_LEDS-1);
}

void meadow() //!sett
{
	//if(indexOrBits<200)
	{
		if(i_eff==0)
		for(NUM_LEDS_type i=0; i<NUM_LEDS;i++)
		{
				leds[i].r=50;
				leds[i].b=sin8(i*255/NUM_LEDS);
		}
		
		for(NUM_LEDS_type i=0; i<NUM_LEDS;i++)
		{
			if(indexOrBits%2)
			{
				if(random8()>i)
					leds[i].r++;
				if(pow(random8(),1.5)>pow(i,1.5))
					leds[i].b++;
			}else
			{
				if(random8()>100)
					leds[i].r++;
				if(random8()>100)
					leds[i].b++;
			}
		}
	
	}
	
	for(NUM_LEDS_type i=0; i<NUM_LEDS;i++)
	{
		if(random8()>100)
			leds[i].g++;
	}
}

#ifdef eff_setX
float xx1f=0;
float xx2f=0.10;
float xx3f=0.20;
float xx4f=0.40;
float xx41f=0.40;
#define LED_SIZE_f01	(1./(float)NUM_LEDS)
void movers_f()
{
	fadeToBlackBy(leds, NUM_LEDS, 1+effFade/16);//1+effFade/4);
	
	xx1f+=LED_SIZE_f01*.2;
	xx2f-=LED_SIZE_f01*.33;
	xx3f+=   LED_SIZE_f01*(((float)beatsin8(12))/255. -0.5);  //! opt cast at end
	//xx4f+=((float)beatsin8(11, (NUM_LEDS_type)(xx4f*NUM_LEDS) , (NUM_LEDS_type)((xx2f-xx4f)*NUM_LEDS)))*0.08;
	
	float beat01 =((float)beatsin8(12)/256.);
	xx4f+= ((xx1f-xx4f))*0.01*beat01+((xx2f-xx4f))*0.01*(1-beat01);
	xx41f+= 1/((xx1f-xx41f))*0.005*beat01+1/((xx2f-xx41f))*0.005*(1-beat01);
	
	roll01(&xx1f);
	roll01(&xx2f);
	roll01(&xx3f);
	roll01(&xx4f);
	roll01(&xx41f);
	
	float blend=0;
	float xx1fN=xx1f*NUM_LEDS;
	 blend=xx1fN-(NUM_LEDS_type)xx1fN;
		leds[constrain(((NUM_LEDS_type)(xx1fN)),0,NUM_LEDS-1)]+=CRGB(255*(1-blend)/2,0,0);
	if(xx1fN<NUM_LEDS-1)
		leds[constrain(((NUM_LEDS_type)(xx1fN+1)),0,NUM_LEDS-1)]+=CRGB(255*(blend)/2,0,0);
	
	leds[constrain((NUM_LEDS_type)(xx2f*NUM_LEDS),0,NUM_LEDS-1)]+=CRGB(0,255/2,0);
	leds[constrain((NUM_LEDS_type)(xx3f*NUM_LEDS),0,NUM_LEDS-1)]+=CRGB(0,0,255/2);
	
	leds[constrain((NUM_LEDS_type)(xx4f*NUM_LEDS),0,NUM_LEDS-1)]+=CHSV(0,0,10+random8()/2);
	leds[constrain((NUM_LEDS_type)(xx41f*NUM_LEDS),0,NUM_LEDS-1)]+=CHSV(30,random8()/2,155);
	
	
	//mapfloat01
}


float cow_m=100;
float xx1f_last,xx1f_last1=0;

void meadow_cow()
{
	NUM_LEDS_type pos=f01toPos(xx1f);
		if(pos!=pos_last1)
		{
			leds[pos_last1].r=0;
			pos_last=pos_last1;
			pos_last1=pos;
			leds[pos].r=cow_m;
		
		}
		else
		
		
	
	if(i_eff==0)
	{
		xx1f=0.5;
		xx1f_last=0.5;
		for(NUM_LEDS_type i=0; i<NUM_LEDS;i++)
		{
			//if(random8()>100)
				leds[i].g=100;
		}
	}
	
	for(NUM_LEDS_type i=0; i<NUM_LEDS;i++)
	{
		//if(random8()>100)
		if(i_eff%(122+effSpeed)==0)
		{
			leds[i].g++;
		}	
		
		if(i_eff%(1+effSpeed/2)==0)
		{		
			byte pos_dif=pos-i;
			if(abs(pos_dif)>5)
			{
				if(leds[i].r>0)
				{
					leds[i].r--;
					leds[i].g++;
				}
				
			}
			if(leds[i].g==255) leds[i].g=244;
		}
	}
	
	//if(indexOrBits>200)
	{
		
		
		//leds[pos].r=150+cow_m;
		
		/*
		float blend=0;
		float xx1fN=xx1f*NUM_LEDS;
		 blend=xx1fN-(NUM_LEDS_type)xx1fN;
			leds[constrain(((NUM_LEDS_type)(xx1fN)),0,NUM_LEDS-1)].r=cow_m*(1-blend)/2;
		if(xx1fN<NUM_LEDS-1)
			leds[constrain(((NUM_LEDS_type)(xx1fN+1)),0,NUM_LEDS-1)].r=cow_m*(blend)/2;
		*/
		

		
		//EVERY_N_SECONDS(20)
		{
			if(leds[pos].g>0)
			{
				leds[pos].g-=2;
				cow_m++;
				if(cow_m>250)
				{
					cow_m=245;
					
					if(leds[pos_last].r <250) leds[pos_last].r += 1;
				}
			}
		}
		
		//if(random8()>100)
		{
			/*
			float diff=xx1f_last1-xx1f;
			
			if(diff>LED_SIZE_f01*4 || diff< -LED_SIZE_f01*4)
			{
				xx1f_last=xx1f_last1;
				xx1f_last1=xx1f;
			}
			*/
			float d=LED_SIZE_f01*(200+(255-leds[pos].g))/450/(1+effSpeed);
			xx1f+=d;
			cow_m-=d;
			if(cow_m<2+d) cow_m=2+d;
		}
		roll01(&xx1f);
	}
}

#endif