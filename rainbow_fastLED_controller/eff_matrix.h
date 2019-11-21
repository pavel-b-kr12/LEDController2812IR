#define leds_per_row NUM_LEDS/MATRIX_ROWS

NUM_LEDS_type pos_x=8;
NUM_LEDS_type pos_y=8;
byte dir=0;

NUM_LEDS_type getIndexFromMatrixZigZag(NUM_LEDS_type x, NUM_LEDS_type y)
{
	NUM_LEDS_type xxx=y%2==0 ? x : leds_per_row-1-x; //zig-zag matrix
	return y*leds_per_row+xxx;
}

byte i_effA;
void matrix_test()
{
	i_effA++;
					NUM_LEDS_type pos_x_old=pos_x;
					NUM_LEDS_type pos_y_old=pos_y;


	for(NUM_LEDS_type y=0, i=0;y<MATRIX_ROWS;y++)
	{
		for(NUM_LEDS_type x=0;x<leds_per_row;x++)
		{
			
			if(effLengthH<4) //old version
			{
				if(leds[getIndexFromMatrixZigZag(x,y)].b>0)
				{
					//leds[getIndexFromMatrixZigZag(x,y)].b--; //dim all
					leds[getIndexFromMatrixZigZag(x,y)].fadeToBlackBy((effLengthH<2)?1:2);
				}
				if(x==pos_x && y==pos_y)
				{
					switch(dir) //moving
					{
						case 4: dir=0;
						case 0: if(pos_x<leds_per_row-1)  pos_x++; else pos_x=0; break;

						case 1: if(pos_y<MATRIX_ROWS-1)  pos_y++; else pos_y=0; break;
						case 2: if(pos_x>0) pos_x--; else pos_x=leds_per_row-1; break;

						case 255: dir=3;
						case 3: if(pos_y>0) pos_y--; else pos_y=MATRIX_ROWS-1; break;
					}

					//if new pos is not old visited - change dir
					if(effLengthH<2)
					{
						if((leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b>50 && random8()<128) || random8()<5) dir+=(random8()/64-2);
					}
					else 
					{
						if(leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b>50 || random8()<5) dir+=random8()>128?1:-1;
					}

					if(dir>5) dir=3;
					else
					if(dir>3) dir=0;

					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b=255; //set new pos to Blue
					CRGB c=CHSV(i_eff*(effLengthH<2)?8:4,255,(effLengthH<2)?255:128); //and rg to rainbow circle
					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].r=c.r;
					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].g=c.g;

					leds[getIndexFromMatrixZigZag(x,y)].b=88; //dim old pos
				}
			}
			else
			if(effLengthH<32)
			{
				
				//if(leds[getIndexFromMatrixZigZag(x,y)].b>0)
				{
					//leds[getIndexFromMatrixZigZag(x,y)].b--; //dim all
					leds[getIndexFromMatrixZigZag(x,y)].fadeToBlackBy((effLengthH%2)?1:2);
				}



				if(x==pos_x_old && y==pos_y_old)
				{
					switch(dir) //moving
					{
						case 4: dir=0;
						case 0: if(pos_x<leds_per_row-1)  pos_x++; else pos_x=0; break;

						case 1: if(pos_y<MATRIX_ROWS-1)  pos_y++; else pos_y=0; break;
						case 2: if(pos_x>0) pos_x--; else pos_x=leds_per_row-1; break;

						case 255: dir=3;
						case 3: if(pos_y>0) pos_y--; else pos_y=MATRIX_ROWS-1; break;
					}

					//if new pos is not old visited - change dir
					if(effLengthH<8)
					{
						if((leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b>50) || random8()<5)
						{
						 	dir+=random8(3);
						 	if(random8()>16) 
						 	{
						 		pos_x=pos_x_old;
						 		pos_y=pos_y_old;
						 	}
						}
					}
					else
					if(effLengthH<16)
					{
						if((leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b>50 && random8()<128) || random8()<5)
						{
						 	dir+=(random8()/64-2);
						}
					}
					else 
					{
						if(leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b>50 || random8()<5) dir+=random8()>128?1:-1;
					}

					if(dir>5) dir=3;
					else
					if(dir>3) dir=0;

					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].b=255; //set new pos to Blue
					CRGB c;
					if(effLengthH%2)
					 c=CHSV(i_eff*(effLengthH<16)?8:4,255,(effLengthH<16)?255:128); //and rg to rainbow circle //for unknown reason i_eff not working here
					else
					 c=CHSV(i_effA*(1+effSpeedH/32),255,(effLengthH<16)?255:128); //and rg to rainbow circle
					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].r=c.r;
					leds[getIndexFromMatrixZigZag(pos_x,pos_y)].g=c.g;

					leds[getIndexFromMatrixZigZag(x,y)].b=88; //dim old pos
				}
			}
			else
			if(effLengthH<64)
			{
				int xx=(x-leds_per_row/2);
				int yy=(y-MATRIX_ROWS/2);
				//byte hue=sin8(xx*xx+yy*yy)*effFade;
				byte hue=sin8(sqrt(xx*xx+yy*yy))*effFade;
				byte b=255;
				if(hue<20) b=hue;
				else if(hue> 240) b=255-hue;
				if(b<255)b=0; //map(b, 0 ,effLength, 0, 255);

				leds[getIndexFromMatrixZigZag(x,y)]=CHSV(hue+millis()/(4+effSpeed),255,255-hue);
			}
			else
			if(effLengthH<155)
			{
				NUM_LEDS_type xc= abs(x-leds_per_row/2)*sin8(millis()/4);
				if(xc==0) xc=1;
				byte angle=atan( (y-MATRIX_ROWS/2)*cos8(millis()/4)/xc );

				leds[getIndexFromMatrixZigZag(x,y)]=CHSV(angle*(16+effFade/4),255,255);
			}
			else
			{
				if(x == millis()/32%(leds_per_row*5))
					leds[getIndexFromMatrixZigZag(x,y)]=CHSV(44,255, 255); //current Yellow
				else
				if(x == (millis()/32-1)%(leds_per_row*5))
					leds[getIndexFromMatrixZigZag(x,y)]=CHSV(44,255, 0); //prev black
				else
				if(random8()<5)
				{
					//noise type
					CRGB c;
					if(effLengthH<188)c=CHSV(0,0, 255);
					else
					if(effLengthH<200)c=CHSV(random8(),random8(), 122);
					else
					if(effLengthH<222)c=CHSV(0,255, 111);

					leds[getIndexFromMatrixZigZag(x,y)]+=c; //other noise
				}


			}


		}

	}
	
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{


	}
}