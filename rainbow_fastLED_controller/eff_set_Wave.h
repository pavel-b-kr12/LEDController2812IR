//http://fastled.io/docs/3.1/group__lib8tion.html
//https://github.com/FastLED/FastLED/wiki/FastLED-Wave-Functions

byte wave_function(NUM_LEDS_type v_arg, byte wave_type)
{
	byte v;
	switch(wave_type) //!opt   to function ptr
	{
		case 0: v = sin8( v_arg ); break;
		case 1: v = sin8( v_arg ); v=v*v/255; break;
		case 2: v = sin8( v_arg ); v=(NUM_LEDS_type)(pow(((float)v)/255.,0.5)*255); break;

		case 3: v = triwave8( v_arg ); break;
		case 4: v = quadwave8( v_arg ); break;
		case 5: v = cubicwave8( v_arg ); break;
		
		case 6: v= gHue; break;
		case 9: v= v_arg;  break;
		case 10:v= 255-(byte)v_arg;  break;
		#define wave_function_MM	11 //so x%wave_function_MM == max case N
	}
	return v;
}

 //!! TODO use wave_function
 
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
	byte val= wave_function( millis()/(1+effSpeed), (indexOrBits/10%wave_function_MM) );

	//val=val*beatsin8(1+effLength/2,128,255)/255;

	leds[0]=CHSV(gColor.r + gHue/(1+effLengthH ) ,88,	val);
	leds[0] .fadeToBlackBy( beatsin8(40+effLength,0,1+effSpeedH*0.9) );

	if( i_eff%(1+effFade/32)<2 ) 
	for (NUM_LEDS_type i = 20; i < NUM_LEDS; ++i) //fade one side of stripe
	{
		 leds[i].fadeToBlackBy( 1 );
	}

	// 	if(effLength<128)
	// {
	// 	blinkSaveCodedB();
	// }
}


long millis_last=0;
float posX_f=0;

uint16_t td=0;
uint32_t t_anim_last=0;


void wave_adj()
{
	if(indexOrBits<100)
	{ //glitch-free smooth settings adj (but not time-precise due to incriment)
		float dx=((millis()-millis_last) )*(effSpeed/128.-1.);
		posX_f+=dx;
		
		millis_last=millis();
		
		if(indexOrBits/11%2)
		{ //draw all
			for (NUM_LEDS_type i = 0; i < NUM_LEDS; ++i)
			{
				int v_arg=(NUM_LEDS_type)posX_f + i*effLength/16;
				byte v=wave_function(v_arg, indexOrBits%wave_function_MM);
				
				byte mul=effFade/16;
				if(mul>1)
				{ //increase wave steep
					
					if(effFade%3)
					{ //overflow
						v*=mul;
						v-=mul/2;
					}
					else
					{
						v=qsub8(v,256-256/mul)*mul; //!! tst change to adj accordingly w effFade
					}
					//!! bWaveB_pow
				}
				leds[i]=CHSV(effLengthH+ (sin8(millis()/200)/10-12), effSpeedH, v ); 
			}
		}
		else
		{ //gen-move (draw first)
			//moveOutAllRemainFirst();
			moveOutAll_w_speed(effSpeedH);
			
			leds[effSpeedH>128?0:NUM_LEDS-1]=CHSV(wave_function((NUM_LEDS_type)posX_f, indexOrBits%wave_function_MM),255,wave_function((NUM_LEDS_type)(posX_f*2), millis()/1000%wave_function_MM));
		}
	}
	else
	{
		float k_len=135;
		float k_len2=175;
		
		#ifdef standalone
		bool bAnimHPurple=	!digitalRead(btn3_p);
		bool bAnimHViolet=	!digitalRead(btn4_p);
		bool bWaveB_pow=	!digitalRead(btn2_p);
		bool bFadeEnd=		!digitalRead(btn_p);
		#else
		bool bAnimHPurple=	indexOrBits/10==11;
		bool bAnimHViolet=	indexOrBits/10==12;
		bool bWaveB_pow=	indexOrBits%3==0;
		bool bFadeEnd=effFade%2;
		#endif
		
		 for(NUM_LEDS_type i =0;i<NUM_LEDS;i++)
		 {
			 /*
			float t=millis();
			float t1=t/150;
			float t1b=t/150*k_len2/k_len;
			float t2=t/100;
			float t2b=t/100;
			float t3=t/4;
			float t3b=t/4;
			 
			//leds[i]=( triwave8(i+millis()/8 )*sin8(millis()/100) + triwave8(i+millis()/8 )*cos8(millis()/100) )/1024;  //nwp
			leds[i]=CHSV(190+sin8((byte)t1)/16, 205+sin8((byte)t2)/16, triwave8(i*8-(byte)t3 ) );
			leds2[i]=CHSV(190+sin8((byte)t1b)/16, 205+sin8((byte)t2b)/16, triwave8(i*8-(byte)t3b ) );
			*/

			byte b=0;

			b=triwave8(i*8-millis()/4 ) ;

			#ifdef standalone
			byte b1=triwave8((int)(i*8.0*k_len/k_len2)-millis()/4 );
			#endif
			byte h=211+sin8(millis()/200)/8; //as from violet to purple over 235ms*255 =1 min

			if(bAnimHPurple)
			{
				h=190+sin8(millis()/150)/16; //as violet
			}
			else
			if(bAnimHViolet)
			{
				h=230+sin8(millis()/150)/32; //as violet
			}
			
			if(bWaveB_pow)
			{
				b=b*b/255;
				#ifdef standalone
				b1=b1*b1/255;
				#endif
			}
			
			
			leds [i]=CHSV(h, 215+sin8(millis()/200)/16, b );
			#ifdef standalone
			leds2[i]=CHSV(h, 215+sin8(millis()/200)/16,  b1);
			#endif
		 }
		 //i_eff++;
			
			if(bFadeEnd) //fade far end
			{
				//if( i_eff%(1+millis()/200%60)<2 )
				{
					for (int i = 30; i < NUM_LEDS; ++i)
					{
						 //leds[i].fadeToBlackBy( i );
						 leds[i].fadeToBlackBy( map(i, 30,NUM_LEDS, 1, 250)  );
						 #ifdef standalone
						 leds2[i].fadeToBlackBy( map(i, 30,NUM_LEDS, 1, 250)  );
						 #endif
					}
				}
			}
	
		
	}
}


void oppositeWavesBlend()
{
	//beatsin8(24,0,NUM_LEDS-1);
	//beatsin8(24,NUM_LEDS-1,0);
	//triwave8(24,0,NUM_LEDS-1);
	//i_eff%NUM_LEDS
	
	uint16_t it=millis()/10;
	
	 if(pos1==NUM_LEDS-1)pos1=0;
		else pos1++;
	
	 if(pos2==0) pos2=NUM_LEDS-1;
		else  pos2--;
	
			//		// leds[i].fadeToBlackBy( 1 );
	for (NUM_LEDS_type i = 0; i < NUM_LEDS; ++i) //fade one side of stripe
	{

		switch(indexOrBits/10)
		{
		case 0:
		leds[i]=CHSV( it*(1+(effLengthH/16))/100,255,triwave8(i+it*effLength/8));
		leds[i]+=CHSV( 30*(it*(1+(effLengthH/16))/2000)+it*(1+(effLengthH/16))/100,255,triwave8(i-it*effLength/8));
		break;

		case 1:
			leds[i]=CHSV( (i+it*(1+(effLengthH/16))/100)%255 + ((NUM_LEDS-i)+it*(1+(effLengthH/16))/100)%255,255,triwave8((i+it*effLength/8)*255/NUM_LEDS)); //1
		break;
		case 2:
			leds[i]=CHSV( (i+it*(1+(effLengthH/16))/100)%255 + ((NUM_LEDS-i)+it*(1+(effLengthH/16))/100)%255,255,triwave8((i+it*effLength/8)*255/NUM_LEDS)+triwave8((NUM_LEDS-i+it*effLength/8)*255/NUM_LEDS)); //:)
		break;
		case 3:
			leds[i]=CHSV(
			sin8((i+it*effLength/256)*255/NUM_LEDS) +
			sin8((i-it*effLengthH/256)*255/NUM_LEDS)
			,255,255); // triwave8((i+it*(1+(effLengthH/16))/100)%255 )+ triwave8(((NUM_LEDS-i)-it*(1+(effLengthH/16))/100)%255)
		break;			
		case 4:
			leds[i]=CHSV( (i+it*(1+effLengthH/8)/100)%255 * ((NUM_LEDS-i)+it*(1+(effLengthH/16))/100)%255,255,triwave8((i+it*effLength/32)*255/NUM_LEDS)); //:) when slow
		break;

		case 5: //+
		{
		uint16_t b1=sin8((i+it*(effLength/16))*255/NUM_LEDS);
		b1=b1*b1/256;
		uint16_t b2=sin8(((NUM_LEDS/2+i)-it*(effLength/16))*255/NUM_LEDS);
		b2=b2*b2/256;
		byte h1=it/(10+effLengthH);
		leds[i]=CHSV( h1,255,		b1); //fix crack
		leds[i]+=CHSV(h1+60+sin8(it/100)/4,255,	b2);
		}
		break;
		
		case 6: //==5
		{
		uint16_t b1=sin8((i+it*(effLength/16))*255/NUM_LEDS);
		b1=b1*b1/256;
		uint16_t b2=sin8(((NUM_LEDS/2+i)-it*(effLength/16))*255/NUM_LEDS);
		b2=b2*b2/256;
		byte h1=it/(10+effLengthH);
		leds[i]=CHSV( h1  + h1+60+sin8(it/100)/4,255,		b1+b2); //fix crack
		}
		break;
		
		 
		case 7: //oposite
		leds[i]=CHSV(
		it*(1+(effLengthH/16))/100  +  30*(it*(1+(effLengthH/16))/2000)+it*(1+(effLengthH/16))/100,
		255 ,
		sin8((i-it*effLength/8)*255/NUM_LEDS*2)+sin8((NUM_LEDS/2+i-it*effLength/8)*255/NUM_LEDS*2)/256
		);
		break;
				 
		case 8: //one dir
		leds[i]=CHSV(
		it*(1+(effLengthH/16))/100  +  30*(it*(1+(effLengthH/16))/2000)+it*(1+(effLengthH/16))/100,
		255 ,
		sin8((i+it*effLength/8)*255/NUM_LEDS*2)+sin8((NUM_LEDS/2+i+it*(effLength/13))*255/NUM_LEDS*2)/256
		);
		break;

		case 9: //+
		leds[i]=CHSV( 
		it*(1+(effLengthH/16))/100
		+30*(it*(1+effLengthH/8)/2000)+it*(1+effLengthH/8)/100,
		255,
		qadd8( beatsin8(effLength/3,0,255,0,i)/2,beatsin8(effLength/4,255,0,NUM_LEDS/2-i)/2)
		);

		//nwae
		// leds[i]=CHSV( it/100,255,beatsin8(24,0,255));
		// leds[i]+=CHSV( 30*(it/2000)+it/100,255,beatsin8(24,255,0));
		break;
		
		case 10: //:)
		{
			leds[i].fadeToBlackBy( 1+effFade/16 );
			byte h1=0;
			byte h2=122;
			if(effSpeedH>50 && effSpeedH<150) 
			{
				h1=it/100;
				h2=150+it/50;
			}
			else
			if(effSpeedH>150)
			{
				h1=i+it/5;
				h1=it/3;
			}
				
			if(i==pos1) leds[i]+=CHSV( h1,millis()/4000%2?255:(i_eff+i)%2*255,255);//
			if(i==pos2) leds[i]+=CHSV( h2,255,millis()/4000%2?255:(i_eff+i)%2*255);//
		}
		break;
		
		case 11:
		
		break;
		
		/*
		case 9:
		leds[i]=CHSV( it*(1+(effLengthH/16))/100,255, (i+it*(effLength/8))%128);
		leds[i]+=CHSV( 30*(it*(1+(effLengthH/16))/2000)+it*(1+(effLengthH/16))/100,255,(i-it*(effLength/8))%128);
		break;

		case 10:
		leds[i]=CHSV(
		it*(1+(effLengthH/16))/100  +   (NUM_LEDS/2-it)*(1+(effLengthH/16))/100,
		255,
		it*effLength/8%128 +(NUM_LEDS/2-i-it*effLength/8)%128
		)
		+
		CHSV(
		it*(1+(effLengthH/16))/100  +   (NUM_LEDS/2-it)*(1+(effLengthH/16))/100,
		255,
		it*effLength/8%128 +(i-it*effLength/8)%128
		)
		;

		 break;
		 
		 		case 11:
		leds[i]=CHSV(
		i+it*(1+(effLengthH/16))/100  +   (NUM_LEDS-it)*(1+(effLengthH/16))/100,
		255,
		NUM_LEDS-i+it*effLength/8%128 +(-it*effLength/8)%128
		);

		 break;
		 */

		}
	}
}

/*
попроще, и посложнее
youtu.be/uwffJtgg3BI
youtube.com/watch?v=fBmtSmy2CPQ
*/