

void cubic_fill_edges()
{

	byte leds_per_edge=NUM_LEDS/12;




	for (int j = 0; j < 12; ++j)
	{

		if(indexOrBits<128)
		{
			for (int i = 0; i < leds_per_edge; ++i) //edges same color
			{
				if(millis()/(4+effSpeed*4)%12!=j) //skip one edge every effSpeed*4 ms
				leds[j*leds_per_edge+i]=CHSV(j*12*effLengthH+millis()/(20+effSpeedH),255,255);
			}
		}
		else //corners same color
		{
			if(j==0 || j== 4 || j== 8)
				h=0;
			else
			if(j==1 || j== 5 || j== 10)
				h=60;
			else
			if(j==2 || j== 7 || j== 9)
				h=120;
			else
			if(j==3 || j== 6 || j== 11)
				h=180;


			for (int i = 0; i < leds_per_edge; ++i)
			{
				leds[j*leds_per_edge+i]=CHSV(h,255,255);
			}
		}
	}



}


void fill_segments_anim()
{
	byte segmentE;
	NUM_LEDS_type leds_per_segment;
	//if(indexOrBits==0)
	{
		leds_per_segment=4+effLength;
		segmentE=NUM_LEDS/leds_per_segment;
	}

	byte leds_to_fill=beatsin8(1+effSpeed,1,leds_per_segment); //! anim max, so it not filled full every time
	for (int j = 0; j < segmentE; ++j)
	for (int i = 0; i < leds_to_fill; ++i)
	{
		if(indexOrBits<128)
			leds[j*leds_per_segment+i]=CHSV(j*12*effLengthH/12+millis()/(20+effSpeedH),255,255);
		else
			leds[j*leds_to_fill+i]=CHSV(j*12*effLengthH/12+millis()/(20+effSpeedH),255,255);
	}
}

void cubic_test()
{
	if(i_eff==0)
	{
		posX=0; 
		set_currentPalette(posX);
	}


	for (int i = 0; i < NUM_LEDS/12; ++i)
	{
		leds[i]=ColorFromPalette(currentPalette,map(i,0,NUM_LEDS/12,0,255),255,(effFade>128)?LINEARBLEND:NOBLEND);

		leds[i+NUM_LEDS/12]=leds[i];
		leds[i+NUM_LEDS/12*2]=leds[i];
		leds[i+NUM_LEDS/12*3]=leds[i];
		leds[-i+NUM_LEDS/12*4]=leds[i];


		//memcpy8(temp, leds, sizeof(leds));                            // Copy values from temp to leds
	}


	EVERY_N_SECONDS(1)	currentPalette_scroll();

	EVERY_N_SECONDS(16)
	{
	 posX++;
	 set_currentPalette(posX);
	}
}



//------------------------------------------------------------------------------------ https://github.com/FastLED/FastLED/wiki/RGBSet-Reference



/*

CRGBSet ledsX00(ledsRef(0				,NUM_LEDS/12-1), NUM_LEDS/12);
CRGBSet ledsX01(ledsRef(NUM_LEDS/12*1,NUM_LEDS/12*2-1), NUM_LEDS/12);
CRGBSet ledsX10(ledsRef(NUM_LEDS/12*2,NUM_LEDS/12*3-1), NUM_LEDS/12);
CRGBSet ledsX11(ledsRef(NUM_LEDS/12*3,NUM_LEDS/12*4-1), NUM_LEDS/12);

CRGBSet ledsY00(ledsRef(NUM_LEDS/12*4,NUM_LEDS/12*5-1), NUM_LEDS/12);
CRGBSet ledsY01(ledsRef(NUM_LEDS/12*5,NUM_LEDS/12*6-1), NUM_LEDS/12);
CRGBSet ledsY10(ledsRef(NUM_LEDS/12*6,NUM_LEDS/12*7-1), NUM_LEDS/12);
CRGBSet ledsY11(ledsRef(NUM_LEDS/12*7,NUM_LEDS/12*8-1), NUM_LEDS/12);

CRGBSet ledsZ00(ledsRef(NUM_LEDS/12*8,NUM_LEDS/12*9-1), NUM_LEDS/12);
CRGBSet ledsZ01(ledsRef(NUM_LEDS/12*9,NUM_LEDS/12*10-1), NUM_LEDS/12);
CRGBSet ledsZ10(ledsRef(NUM_LEDS/12*10,NUM_LEDS/12*11-1), NUM_LEDS/12);
CRGBSet ledsZ11(ledsRef(NUM_LEDS/12*11,NUM_LEDS/12*12-1), NUM_LEDS/12);


CRGBSet ledsXY0(ledsRef(0,NUM_LEDS/6), NUM_LEDS/6);
*/


/*
CRGBSet ledsCorner000(ledsRef(0,3), 3);
CRGBSet ledsCorner100(ledsRef(0,3), 3);
CRGBSet ledsCorner010(ledsRef(0,3), 3);
CRGBSet ledsCorner001(ledsRef(0,3), 3);
CRGBSet ledsCorner011(ledsRef(0,3), 3);
CRGBSet ledsCorner110(ledsRef(0,3), 3);
CRGBSet ledsCorner101(ledsRef(0,3), 3);
CRGBSet ledsCorner111(ledsRef(0,3), 3);
*/
//struct CRGB * ledsCorners[] ={ledsCorner000, ledsCorner100, ledsCorner010, ledsCorner001, ledsCorner011, ledsCorner110, ledsCorner101, ledsCorner111};
//https://gist.github.com/chemdoc77/25d8b91d28f37c87aaadcd9ff02f8c78

CRGB *ledsCorners[8][3]; 

//NUM_LEDS_type cornersLEDsN[2][2][2];

NUM_LEDS_type cornersLEDsN[3][4]; //[x,y,z][N of start]

//cubic_CRGBSet_test
void cubic_PointerArr_test()
{

	
	if(i_eff==0)
	{

		byte _end=NUM_LEDS/12-1;
		
		for (int xyz = 0; xyz < 3; ++xyz)
		for (int i = 0; i < 4; ++i)
		{
			cornersLEDsN[xyz][i]= NUM_LEDS/12*3*xyz + NUM_LEDS/12*i;
		}
		

		//x=0		y=0		z=0
		ledsCorners[0][0]=&leds[cornersLEDsN[0][0]];
		ledsCorners[0][1]=&leds[cornersLEDsN[1][0]];
		ledsCorners[0][2]=&leds[cornersLEDsN[2][0]];

		//x=0end	y=1		z=1
		ledsCorners[1][0]=&leds[cornersLEDsN[0][0]+_end];
		ledsCorners[1][1]=&leds[cornersLEDsN[1][1]];
		ledsCorners[1][2]=&leds[cornersLEDsN[2][1]];

		//x=1end	y=3		z=1end
		ledsCorners[2][0]=&leds[cornersLEDsN[0][1]+_end];
		ledsCorners[2][1]=&leds[cornersLEDsN[1][3]];
		ledsCorners[2][2]=&leds[cornersLEDsN[2][1]+_end];

		//...



		byte corner_i=0;
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				for (int z = 0; z < 2; z++,corner_i++)
				{
					//ledsCorners[corner_i]=&leds[
				}
			}
		}

	}

	if(indexOrBits>128) 
	{
		
		fill_gradient_RGB(ledsX00,0, ledsX00[0], NUM_LEDS/12-1, ledsX00[NUM_LEDS/12-1]);
	}
	else
	if(indexOrBits>64) 
	{
		for (uint8_t i=1; i<NUM_LEDS/12-1; i++)
		{
			ledsX00[i] =blend(ledsX00[0], CRGB::Black, map(i,0,NUM_LEDS/12/2,0,255));
			ledsX00[i] =blend(CRGB::Black, ledsX00[NUM_LEDS/12-1], map(i,NUM_LEDS/12/2,NUM_LEDS/12,0,255));
		}
	}
	else //changing 
		for (uint8_t i=1; i<NUM_LEDS/12-1; i++)
		{
			ledsX00[i] = beatsin8(effSpeed/16,1,NUM_LEDS/12-1)>i ?  ledsX00[0]: ledsX00[NUM_LEDS/12-1];
		}



	EVERY_N_SECONDS(1)
	{
		for (uint8_t corner=0; corner<8; corner++)
		{
			CRGB cCorner=CHSV(random8(),255,255);
			for (uint8_t i=0; i<3; i++)
			{
				if(ledsCorners[corner][i]!=NULL)
				*(ledsCorners[corner][i])=cCorner;
			}
		}
	}

}
