#define fireLengthX2 //double length

// Gradient palette "bb_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds9/tn/bb.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

// CRGBPalette16 fire_p(
  // CRGB(  0,  0,  0),
  // CRGB(128,  0,  0),
  // CRGB(255,128,  0),
  // CRGB(255,255,128)
 
  // );
  DEFINE_GRADIENT_PALETTE( fire_p_ ) {
  0,     0,  0,  0,   //black
128,   255,  0,  0,   //red
224,   255,255,  20,   //bright yellow
255,   222,222,255 }; //full white
CRGBPalette16 fire_p = fire_p_;

  DEFINE_GRADIENT_PALETTE( fireCold_p_ ) { //mysterious cold fire
  0,     0,  0,  0,   //black
128,   66,  0,  188,   //red
224,   0,222,  255,   //bright yellow
255,   33,255,255 }; //full white
CRGBPalette16 fireCold_p = fireCold_p_;

//leds[i] = ColorFromPalette( myPal, heatindex); // normal palette access

//@use float v wo artefacts https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
  typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6; 

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

  
  
void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

   //if(effLengthH>10)
  // {
	  // CHSV hsv=rgb2hsv_approximate(leds[Pixel]);  //not good-looking way adj hue
	  // hsv.h+=effLengthH;
	  // leds[Pixel]=hsv;
	  /*
	  	switch(effLengthH/10)
		{
			
			// case 2: currentPalette=HeatColors_p; break;
			// case 3: 
			
				// currentPalette=OceanColors_p;
				// currentPalette[0] = CHSV( map(15,0,15,180,0), 255, 0);
				// currentPalette[1] = CHSV( map(15,0,15,180,0), 255, 20);
				// currentPalette[2] = CHSV( map(15,0,15,180,0), 255, 60);
				
			 // break;
			
			case 4: 
				for( int i = 0; i < 16; i++) {
					currentPalette[i] = CHSV( map(i,0,15,0,70), 				i<10?255: map(i,10,15,255,80),	 i<3?  map(i,0,3,0,255) :255 ); //127+i*8
				}
				currentPalette[0] = CHSV( map(15,0,15,0,60), 255, 0);
			break;
			case 5: 
			
				for( int i = 0; i < 16; i++) {
					currentPalette[i] = CHSV( map(i,0,15,250,160)+effSpeedH,	i<5?255: map(i,5,15,255,0), 	i<4?  map(i,0,4,0,255) :255);
				}
				
				//currentPalette[15] = CHSV( map(15,0,15,180,0), 255, 0);
			break;
		}
		*/
		
		//leds[Pixel] = ColorFromPalette(currentPalette, effSpeedH>30?temperature:heatramp,255,LINEARBLEND);
		//leds[Pixel] = ColorFromPalette(currentPalette, heatramp,255,LINEARBLEND);
   //}else
   {

 CRGB c, c1;
 #define fireSW //normal | animate hue | normal cold
#ifdef fireSW
	if(effSpeedH>140 && effSpeedH<151)
		c=ColorFromPalette(fireCold_p, temperature, 255, LINEARBLEND);
	else
#endif
	{
		c=ColorFromPalette(fire_p, temperature, 255, LINEARBLEND); //? is need ", 255, LINEARBLEND" //! fire_p HeatColors_p
#ifdef fireSW	
	if(effSpeedH>252 || effSpeedH<5) //normal fire
	{}
	else //anim hue
#endif
	{
		
		
	//else
		//c1=CHSV(effSpeedH+ constrain(map(temperature,0,211,0,60),0,60), temperature>200?0: map(temperature,0,200,200,0) ,temperature>100?255:map(temperature,0,100,0,255));
  

 
	  // if ( t192 > 0x80) {                    // hottest
		// c=CRGB( 255, 255, heatramp);
	  // } else if ( t192 > 0x40 ) {            // middle
		// c=CRGB( 255, heatramp, 0);
	  // } else {                               // coolest
		// c=CRGB( heatramp, 0, 0);
	  // }
		// if ( t192 > 0x80) {                    // hottest
		// c1=CRGB( heatramp, 255, 255);
	  // } else if ( t192 > 0x40 ) {            // middle
		// c1=CRGB( heatramp, 255, 0);
	  // } else {                               // coolest
		// c1=CRGB( 0, 0, heatramp);
	  // }
  
  
		//leds[Pixel]=blend(c,c1,map(effSpeedH,150,255,0,255));

		//CHSV hsv=rgb2hsv_approximate(c);
		//hsv.h+=effSpeedH;
		//leds[Pixel]= hsv;
		RgbColor rgb;
		rgb.r=c.r;
		rgb.g=c.g;
		rgb.b=c.b;
		HsvColor hsv = RgbToHsv(rgb);
		hsv.h+=effSpeedH;
		c=CHSV(hsv.h,hsv.s,hsv.v);
	}
	}
	
	#ifdef fireLengthX2
		if(Pixel*2<NUM_LEDS)
		{
			leds[Pixel*2]= c;
			if(Pixel>0)
			{
				leds[Pixel*2-1]=CRGB(  leds[Pixel*2-2].r/2+leds[Pixel*2].r/2,
					leds[Pixel*2-2].g/2+leds[Pixel*2].g/2 ,
					leds[Pixel*2-2].b/2+leds[Pixel*2].b/2 
					);
			}
		}
	#endif
 
 
  
	// CHSV hsv=rgb2hsv_approximate(ColorFromPalette(fire_p, heatramp ));// |temperature
	// hsv.h+=effSpeedH;
	// leds[Pixel]=hsv;




	   // blend(  
	   // CHSV(map(heatramp,0,255,0,60),map(heatramp,0,255,255,0),heatramp>100?255:map(heatramp,0,100,0,255)),
	   // CHSV(effSpeedH+map(temperature,0,255,0,60),map(temperature,0,255,255,0),temperature>100?255:map(temperature,0,100,0,255)),
	   // effSpeedH);
	   
	   /*
	   //change R-B by effSpeedH but not not full B, but purple
     if ( t192 > 0x80) {                    // hottest
    leds[Pixel]=CRGB( constrain(
map( effSpeedH,0,255, 255,heatramp), 255,heatramp), 255, constrain(map( effSpeedH,0,255, heatramp,255),  heatramp,255));
  } else if ( t192 > 0x40 ) {            // middle
    leds[Pixel]=CRGB( 255-effSpeedH, heatramp, effSpeedH);
  } else {                               // coolest
    leds[Pixel]=CRGB( constrain( map( effSpeedH,0,255, heatramp,255), 0,heatramp), 0, constrain( map( effSpeedH,0,255, 0,heatramp),0, heatramp) );
  }
  */
  
  // figure out which third of the spectrum we're in:
  /*
  if ( t192 > 0x80) {                    // hottest
    leds[Pixel]=CRGB( 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    leds[Pixel]=CRGB( 255, heatramp, 0);
  } else {                               // coolest
    leds[Pixel]=CRGB( heatramp, 0, 0);
  }
*/
   }
   //!!
  // byte t=leds[Pixel].g;
   //leds[Pixel].r= leds[Pixel].g;
  // leds[Pixel].g= t;
  
}

void Fire() {
  byte Cooling=effSpeed;
  byte Sparking=effLength;
  //look "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.

  static byte heat[gNUM_LEDS];
  byte cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
   // cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    cooldown = random(0, (((Cooling+sin8(millis()/16)/8) * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
   // heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	heat[k] = (heat[k - 1]*0.1 + heat[k - 2]*0.9); //less diffusion
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
if ( random8() < Sparking ) {
//if ( random8() < Sparking+sin8(millis()/12)/8 ) {
    byte y = random(7);
   // heat[y] = qadd8(heat[y] , random(11, 88)); //qadd becaus arr is bytes
    heat[y] = qadd8(heat[y] , random(166, 255)); //qadd becaus arr is bytes
    //heat[y] = random(160,255);
  }


  // Step 4.  Convert heat to LED colors
#ifdef fireLengthX2
	for ( int j = 0; j < NUM_LEDS/2; j++) //2x
#else
	for ( int j = 0; j < NUM_LEDS; j++)
#endif
	{
		setPixelHeatColor(j, heat[j] );
	}

}