float gravity = -.004; // m/s/s
//!! settings gravity

#if NUM_LEDS<61
 #define NUM_SPARKS NUM_LEDS / 2
#elif NUM_LEDS<300
 #define NUM_SPARKS 10+ NUM_LEDS / 16 //!! tst
#else
 #define NUM_SPARKS 22+ NUM_LEDS / 32 //NUM_LEDS / 2 // max number (could be NUM_LEDS / 2);
#endif
//#define NUM_SPARKS NUM_LEDS / 2 // max number (could be NUM_LEDS / 2);

float sparkPos[NUM_SPARKS];
float sparkVel[NUM_SPARKS];
float sparkCol[NUM_SPARKS];
#define flarePos	pos_f


float dying_gravity;
float c1=120; //temp
float c2=50;

float flareVel;
byte flare_eff_i=0;
#define	nSparks	numdots

void flare() { //Send up a flare
	if(flare_eff_i>0) //this do after 1st show()
	{
		flarePos += flareVel;
		flareVel += gravity;
		thisbri *= .985;
	}
FastLED.clear();  //!! fade

if (flareVel >=0.05)// -.2)// launch 
	{ 
    // sparks
    for (int i = 0; i < 5; i++) {
      sparkPos[i] += sparkVel[i];
      sparkPos[i] = constrain(sparkPos[i], 0, 120);
      sparkVel[i] += gravity;
      sparkCol[i] += -.8;
      sparkCol[i] = constrain(sparkCol[i], 0, 255);
      leds[int(sparkPos[i])] = HeatColor(sparkCol[i]);
      leds[int(sparkPos[i])] %= 50; // reduce brightness to 50/255
    }
    
    // flare
    leds[int(flarePos)] = CHSV(0, 0, int(thisbri * 255));

  }
  else{ eff_stage_i++;}
  flare_eff_i++;
}


NUM_LEDS_type flash_x=0;
NUM_LEDS_type sparkPos_lovest_i=0;
NUM_LEDS_type sparkPos_highest_i=0;

/*
 * Explode!
 * 
 * Explosion happens where the flare ended.
 * Size is proportional to the height.
 */
 
void explodeLoop() {
 fadeToBlackBy(leds, NUM_LEDS, 2+effLengthH/4);																									
//FastLED.clear();
  if(sparkCol[0] > c2/128*3) { // as long as our known spark is lit, work with all the sparks
    
    for (int i = 0; i < nSparks; i++)
	{ 
      sparkPos[i] += sparkVel[i]*(0.5+float(effSpeed)/32); 
      sparkPos[i] = constrain(sparkPos[i], 0, NUM_LEDS-1); 
	  sparkVel[i]=sparkVel[i]*(1-float(effLength)/255/20); //air brake
      sparkVel[i] += dying_gravity; 
      sparkCol[i] *= 0.999-float(effFade)/256./10.; //0.99
      sparkCol[i] = constrain(sparkCol[i], 0, 255); // red cross dissolve 
	  
	  if(indexOrBits>150) //debug show arrays
	  {
		  switch(indexOrBits/10%6)
		  {
		   case 0: leds[i]=CHSV((int)sparkPos[i],255,255); break;
		   case 1: leds[i]=CHSV((int)sparkVel[i],255,255); break;
		   case 2: leds[i]=CHSV((int)sparkCol[i],255,255); break;
		   case 3: leds[i]=HeatColor(sparkCol[i]); break;
		   default: leds[int(sparkPos[i])]=HeatColor(sparkCol[i]); break;
		  }
	  }
	  else
	  {
		CRGB c=0;
		if(sparkCol[i] > c1) { // fade white to yellow
			c= CRGB(255, 255, (255 * (sparkCol[i] - c1)) / (255 - c1));
		}
		else if (sparkCol[i] < c2) { // fade from red to black
			c = CRGB((255 * sparkCol[i]) / c2, 0, 0);
		}
		else { // fade from yellow to red
			c = CRGB(255, (255 * (sparkCol[i] - c2)) / (c1 - c2), 0);
		}
		
		//if(millis()/11800%2)
		//	leds[int(sparkPos[i])]=c;
		//else 
			leds[int(sparkPos[i])]+=c;
	  }
    }
    dying_gravity *= .995; // as sparks burn out they fall slower


	//glitter between sparks
	if(flash_x!=0) //do not off point more than once
	{
		leds[flash_x]=0;//CRGB(99,99,99);
		flash_x=0;
	}
	if(millis()/10000%2 &&   random8()< (sparkCol[0] - c2/128*3))
	{
	flash_x=random8or16( int(sparkPos[sparkPos_lovest_i]),int(sparkPos[sparkPos_highest_i]));
	leds[flash_x]=CRGB::White;
	}

  }
  else
  {
	  eff_stage_i++;
	  eff_stage_next_t=millis();//!!+random16(1000, 4000);
  }
}



void firework1000() {  
  
  switch(eff_stage_i)
  {
	case 0: //  flare init
	{
		flarePos = 0;
		flareVel = float(random16(50, 90)) / 100; // trial and error to get reasonable range
		thisbri = 1;
		eff_stage_i++;
		flare_eff_i=0;
		
		 for (int i = 0; i < 5; i++) { 
			sparkPos[i] = 0;
			sparkVel[i] = (float(random8()) / 255) * (flareVel / 5); // random around 20% of flare velocity 
			sparkCol[i] = sparkVel[i] * 1000; 
			sparkCol[i] = constrain(sparkCol[i], 0, 255);
		 } 
	}
	break;
	case 1: // send up flare
	{
		flare();
	}
	break;
	case 2:   // explode init
	{
		  nSparks = flarePos / 2; // works out to look about right
										  if(nSparks>NUM_LEDS/2)nSparks=NUM_LEDS/2; //for case where NUM_LEDS is adjustable
										  if(nSparks>NUM_SPARKS)nSparks=NUM_SPARKS;
		  
		  float sparkPos_lovest_f=1;
		   float sparkPos_highest_f=-1;
		  
		  // initialize sparks
		  for (int i = 0; i < nSparks; i++) { 
			sparkPos[i] = flarePos;
			sparkVel[i] = (float(random16(0, 20000)) / 10000.0) - 1.0; // from -1 to 1 
			if(sparkVel[i]>sparkPos_highest_f)  //save i of points that will be lowest and highest because of velosity
			{
				sparkPos_highest_f=sparkVel[i];
				sparkPos_highest_i=i;
				
			}
			else
			if(sparkVel[i]<sparkPos_lovest_f) 
			{
				sparkPos_lovest_f=sparkVel[i];
				sparkPos_lovest_i=i;
				
			}
				int cc=sparkVel[i]* 500;
			sparkCol[i] = millis()/1000%2?abs(cc):random8(100,255); // set colors before scaling velocity to keep them bright 
			sparkCol[i] = constrain(sparkCol[i], 0, 255); 
			sparkVel[i] *= flarePos / NUM_LEDS; // proportional to height 
		  } 
		  sparkCol[0] = 255; // this will be our known spark 
		   dying_gravity = gravity; 
		   c1=220; 
		   c2=50; 
		eff_stage_i++;
	}
	break;
	
	case 3:   // explode
	{
		explodeLoop();
	}
	break;
	
	default:{if(millis()>eff_stage_next_t){eff_stage_i=0;}}
	break;
  }
}
//2F report has bug of formatting and also abs() usage  http://www.anirama.com/1000leds/1d-fireworks/