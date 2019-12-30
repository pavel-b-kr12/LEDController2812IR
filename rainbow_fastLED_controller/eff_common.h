
	  // CHSV hsv=rgb2hsv_approximate(leds[Pixel]);
	  // hsv.h+=effLengthH;
	  // leds[Pixel]=hsv;
	  
unsigned int crc32b(unsigned char *message) {
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (message[i] != 0) {
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}


unsigned int crc2b(int message) {
   int i, j;
   unsigned int byte, crc, mask;

   crc = 0xFFFFFFFF;

      byte = message%256;            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }



      byte = message/256;            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }


   return ~crc;
}




void clear_leds()
{
	memset(leds, 0, NUM_LEDS * 3);
	//FastLED.clear(true);

	// for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	// {
	// 	leds[i]=0;
	// }
}
/*
add new

			leds[0]=moveOutAllRemainFirst_ret_last__all_bRight(true);
			
			for (int i = 0; i< NUM_LEDS; i++)
			{
				leds[i].nscale8(250);
			}
leds[0]+=CHSV(random8(33)+aVal*80,255,random8(4)*60);







      if (strobe_bright > 0)
        for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(STROBE_COLOR*aVal, STROBE_SAT+255*aVal, strobe_bright);
      else
        for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(EMPTY_COLOR*aVal, 255*aVal, EMPTY_BRIGHT);
      break;


*/

/*
randomBlink

*/

//fill_solid( leds, NUM_LEDS, CRGB(50,0,200)); 

/*
// Dim a color by 25% (64/256ths)
  // eventually fading to full black
  leds[i].fadeToBlackBy( 64 );

  // Reduce color to 75% (192/256ths) of its previous value
  // eventually fading to full black
  leds[i].nscale8( 192);
  
  
  
  leds[i].maximizeBrightness();  // Adjust brightness to maximum possible while keeping the same hue. //###
  
  ##обесцвечивающийся радужный mover
  ## цветное движущиеся окно
*/


void moveOutAllRemainFirst()
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
	}
}
void moveAll() //cyclic
{
	CRGB t=leds[NUM_LEDS-1];
	moveOutAllRemainFirst();
	leds[0]=t;
}
// ==

/*
void moveRightMemset() {
for (int i=0; i<NUM_LEDS; i++) {
CRGB last_led = leds[NUM_LEDS-1];
memmove( &leds[1], &leds[0], (NUM_LEDS-1)*sizeof(CRGB));
leds[0] = last_led;
FastLED.show();
delay(300);
}
}
*/
/*
int ar[]={1,2,3,4,5};
   int n=sizeof(ar)/sizeof(ar[0]);
   r_left(ar,n);

void r_left(int *a,int n) 
{ 
  int tmp=a[0];
  memmove(a,a+1,sizeof(int)*(n-1));
  a[n-1]=tmp;
} 
//rotate right
void r_right(int *a,int n) 
{ 
    int tmp=a[n-1];
    memmove(a+1,a,sizeof(int)*(n-1));
    a[0]=tmp;
 } 
*/

// leds[0]=moveOutAllRemainFirst_ret_last__all_bRight(true);  //cyclic right
CRGB moveOutAllRemainFirst_ret_last(NUM_LEDS_type x0, NUM_LEDS_type x9) //##use //move in forward dir
{
	//if x9 not [0..NUM_LEDS-1]
	
	CRGB t9=leds[x9];
	CRGB t0=leds[x0];
	int bs=sizeof(CRGB)*(abs(x9-x0));
	if(x9>x0)
	{
		memmove(&leds[x0+1],&leds[x0],bs);
		leds[x0]=t0;
	}
	else
	{
		memmove(&leds[x9],&leds[x9+1],bs);
		leds[x0]=t0;
	}
	
	/*
	byte direction=x0<x9 ? 1 : -1;
	for(NUM_LEDS_type i = x9; i != x0; i-=direction) 
	{
		if(i<0 || i> NUM_LEDS-1) break;
		leds[i]=leds[i-direction];
	}
	*/
	
	/*
 
	if(x0<x9)
	{
		for(NUM_LEDS_type i = x9; i != x0; i-=direction) 
		{
			if(i<0 || i> NUM_LEDS-1) break;
			leds[i]=leds[i-direction];
		}
	}
	*/
	
	return t9;
}
CRGB moveOutAllRemainFirst_ret_last__all_Right()
{
	return moveOutAllRemainFirst_ret_last(0, NUM_LEDS-1);
}
CRGB moveOutAllRemainFirst_ret_last__all_Left()
{
	return moveOutAllRemainFirst_ret_last(NUM_LEDS-1, 0);
}

CRGB moveOutAllRemainFirst_ret_lastRev(NUM_LEDS_type x0, NUM_LEDS_type x9) //##use //move in forward dir
{
	//if x9 not [0..NUM_LEDS-1]
	
	CRGB t=leds[x0];
	
	for(NUM_LEDS_type i = x0; i < x9; i++) 
	{
		if(i<0 || i> NUM_LEDS-1) break;
		leds[i]=leds[i+1];
	}

	return t;

}



void moveOutAll()
{
	moveOutAllRemainFirst();
	leds[0]=0;
}
	
void moveOutAll_fade()
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[i].nscale8(253);
	}
}
void moveOutAll_fadeN() //!tst
{
	for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[i].nscale8(map(i,0,NUM_LEDS,0,255));
	}
}


void move_toCenter_RemainFirst()
{
	for(NUM_LEDS_type i = NUM_LEDS/2-1; i >0 ; i--) 
	{
		leds[i]=leds[i-1];
		leds[NUM_LEDS-i-1]=leds[NUM_LEDS-i];
	}
}
void move_fromCenter_RemainFirst()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS/2-2 ; i++) 
	{
		leds[i]=leds[i+1];
		leds[NUM_LEDS-i-1]=leds[NUM_LEDS-i-2];
	}
}
// void move_segments_RemainFirst() //!
// {
// 	byte segments=
// 	for(NUM_LEDS_type i = NUM_LEDS/segments-1; i >0 ; i--) 
// 	{
// 		leds[i]=leds[i-1];
// 		leds[i+NUM_LEDS/2]=leds[i-1+NUM_LEDS/2];
// 	}
// }




long t_last=0;
void moveOutAll_w_speed(byte speed)  //close to 128 is faster
{
	if(speed>2)
	{
		int s=((int)speed-128);
		#ifdef reversemoveOutAll
		s=-s;
		#endif

		byte spd=abs(s); //lower is faster
		#ifdef USBShow
		spd/=2;
		#endif
		if(spd<3) s=0; //no move

		while(millis()-t_last > spd )
		{
			if((millis()-t_last)/ (1+spd) >10) //after big pause do not need to scroll
			{
				t_last=millis();
			}
			else
			{
				t_last+=spd;
			}

			if(s>0)
			{
				moveOutAllRemainFirst_ret_last__all_Right();
				leds[0]=0;
			}
			else if(s<0)
			{
				moveOutAllRemainFirst_ret_last__all_Left();
				leds[NUM_LEDS-1]=0;
			}
		}
	}	
}
void moveOutAll_w_effSpeed()
{
 moveOutAll_w_speed(effSpeed);
}


void addGlitter(byte chanceOfGlitter)
{
	#if NUM_LEDS > 400
	for(byte i=0;i<10;i++)
	#endif
	if(random8() < chanceOfGlitter) {
		leds[ random8or16(NUM_LEDS) ] += gColor;
	}
}
void addGlitterBlack(byte chanceOfGlitter)
{
	if(random8() < chanceOfGlitter) {
		leds[ random8or16(NUM_LEDS) ] = 0;
	}
}

// void addGlitterByBG(byte chanceOfGlitter, byte V)
// {
// 	if(random8() < chanceOfGlitter) {
// 		leds[ random16(NUM_LEDS) ] = gColorBg.nscale8(V);
// 	}
// }

void invertLEDs()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i].r = 255 - leds[i].r;
		leds[i].g = 255 - leds[i].g;
		leds[i].b = 255 - leds[i].b;
	}
}

void flashLEDs_d_effL()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]=CRGB::White;
	}
	FastLED.show(); delay(effLength); //! length
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]=0;
	}
	FastLED.show();
}

void flashAndBackLEDs_d40()
{
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]+=90;
	}
	FastLED.show(); delay(30);  //! length
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		leds[i]-=90;
	}
	FastLED.show(); delay(10);
}

void fadeOut_continued()
{
	for(unsigned long t = millis()+4000; millis() < t; )
	{
		fadeToBlackBy(leds, NUM_LEDS, 3);
		FastLED.show(); delay(4);
	}
}
void offPixel_continued()
{
	for(unsigned long t = millis()+4500; millis() < t; )
	{
		//leds[random8or16(NUM_LEDS)]=CRGB::Black;

		NUM_LEDS_type N=random8or16(NUM_LEDS);
		if(leds[N]!=CRGB(0x000000)) //http://forum.arduino.cc/index.php?topic=385711.0
		{
			leds[N]=CRGB::Black;
			FastLED.show(); delay(3500/NUM_LEDS);
		}
	}
}

void scroll1cycle_continued()
{
	for(NUM_LEDS_type j = 0; j < NUM_LEDS; j++)
	{
		CRGB led0=leds[0];

		for(NUM_LEDS_type i = 0; i < NUM_LEDS-1; i++)
		{
			leds[i]=leds[i+1];
		}
		leds[NUM_LEDS-1]=led0;
		FastLED.show(); 
		delay(abs(NUM_LEDS/2-j)/4); //start and stop slower  //! || beatsin
	}
}

void scroll1cycle_continuedRev()
{
	for(NUM_LEDS_type j = 0; j < NUM_LEDS; j++)
	{
		CRGB led_last=leds[NUM_LEDS-1];

		for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--)
		{
			leds[i]=leds[i-1];
		}
		leds[0]=led_last;
		FastLED.show(); 
		delay(abs(NUM_LEDS/2-j)/2); //start and stop slower  //! || beatsin
	}
}
void moveOut_continued()
{
	leds[0]=CRGB::Black;
	for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++)
	{
		for(NUM_LEDS_type i = NUM_LEDS-1; i >0 ; i--) 
		{
			leds[i]=leds[i-1];
		}
		FastLED.show(); delay(map(effSpeed,0,255,25,1));
	}
}
