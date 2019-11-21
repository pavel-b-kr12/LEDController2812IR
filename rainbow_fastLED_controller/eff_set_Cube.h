 #define k_fade_edge	255/NUM_LEDS_edge-0.05 //1.7

byte eff_t_stage=0;
CRGB leds4edges[NUM_LEDS_edge*4];

void part_march_cube()
{
	for(byte corner_i=0;corner_i<4;corner_i++)
	{
		for(byte axi=0;axi<3;axi++)
		{
			//for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
			{
				moveOutAllRemainFirst_ret_last(0+NUM_LEDS_edge*(corner_i*3+axi),(NUM_LEDS_edge-1)+NUM_LEDS_edge*(corner_i*3+axi));//!? -1 
				leds[0+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(90*axi, (millis()/100%2==0 )? 255:0, 255); //color of 0..4|all LEDs to edges
			}
		}
	}
}
void part_h_move_cube()
{
	CRGB c=i_eff%20<4? gColor: (i_eff/32%8<2? CRGB::Black: leds[4]);

	leds[NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + 0]=c;
	leds[NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1]=c;
	leds[NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0]=c;
	leds[NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1]=c;


	moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + 0, NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1);
	moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1, NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1);
	moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0,NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0+ NUM_LEDS_edge-1);
	moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1,NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1);
}
void part_bottom_fill_cube()
{
	for(int i=0;i<NUM_LEDS_edge;i++)
	{
		leds[0+i]=								ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*0+i,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
		leds[NUM_LEDS_edge*3*2+i]=				ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*1 +NUM_LEDS_edge-i-1,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
		leds[NUM_LEDS_edge*3*2+NUM_LEDS_edge*2+i]=ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*2+i,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
		leds[0+ NUM_LEDS_edge*2+i]=				ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*3 +NUM_LEDS_edge-i-1,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
	}
}
void CubeCornersLight()
{
	if(i_eff>20 && random8()> (eff_t_stage<9?220:250) )
	{
		eff_t_stage++;
		i_eff=0;
	}

	switch(eff_t_stage)
	{
		case 0:	part_march_cube();		break;
		case 1: eff_t_stage++; gColor=CRGB::Red;		break;
		case 2: part_h_move_cube();		break;
		case 3:	part_bottom_fill_cube(); eff_t_stage++; gColor=leds[2]; break;
		case 4: part_h_move_cube();		break;

		case 5:	part_march_cube();		break;
		case 6: eff_t_stage++; gColor=CRGB::Red;		break;
		case 7: part_h_move_cube();		break;
		case 8:	part_bottom_fill_cube(); eff_t_stage++; gColor=leds[2]; break;
		case 9: part_h_move_cube();		break;

		case 10: part_march_cube();		break;
		case 11: eff_t_stage++; gColor=CRGB::Red;		break;
		case 12: part_h_move_cube();		break;
		case 13: part_bottom_fill_cube(); eff_t_stage++; gColor=leds[2]; break;
		case 14: part_h_move_cube();		break;
		case 15: part_march_cube();		break;

		case 16:
		default:
		eff_t_stage=0;
		 	break;
	}
}



//return 1st pixel position in leds. N is axis number . 
//the anticlockwise is:
//x 0 3 2 1
//y 0 1 2 3
//z 0 2 1 3
//but it can be changed in render MCUs
//!! so this now is RAW order, and have to be changed
NUM_LEDS_type xx0(byte N)
{
	return NUM_LEDS_edge*4*N;
}
NUM_LEDS_type yy0(byte N)
{
	return NUM_LEDS_edge*4*N+NUM_LEDS_edge;
}
NUM_LEDS_type zz0(byte N)
{
	return NUM_LEDS_edge*4*N+NUM_LEDS_edge*2;
}


void mapEdge(CRGB ledsTmp[], byte edge_i, NUM_LEDS_type start, bool bForward) //#use
{
	/*
	//map ledsTmp[NUM_LEDS_edge*4] to circle in front of cube, in contr clockwise dir:

	mapEdge(ledsTmp, 0, leds, x[0][0], x[0][1] ); //(from, to,  start, end) . where: z|y|z is axis[4 edges in each axis][0|1 is start|end pixel]
	mapEdge(ledsTmp, 1, leds, y[1][0], y[1][1] );
	mapEdge(ledsTmp, 2, leds, x[3][1], x[3][0] );
	mapEdge(ledsTmp, 3, leds, y[0][1], y[0][0] );

	or
	mapEdge(ledsTmp, 0, xx[0], true); //(from, to,  start, end) . where: z|y|z is axis[4 edges in each axis][0|1 is start|end pixel]
	mapEdge(ledsTmp, 1, yy[1], true );
	mapEdge(ledsTmp, 2, xx[3], false );
	mapEdge(ledsTmp, 3, yy[0], false );

	*/


	for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
	{
		leds[start+i]=ledsTmp[bForward?i:(NUM_LEDS_edge-1-i)];
	}
					
}




void fillC1(byte c)
{
			clear_leds();
			for(NUM_LEDS_type i=0;i<NUM_LEDS/2;i++)
			{
				leds[i]=CHSV(c*10,255,255);
			}
}

void CubeTest2()
{
	//clear_leds();
	/*
	for(byte corner_i=0;corner_i<4;corner_i++)
	{
		for(byte axi=0;axi<3;axi++)
		{
			for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
			{
				leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(55*corner_i+i_eff/8, i==0?0:255, 255-i%2*k_fade_edge*(i_eff%128)/128*2  ); //color of corners, fading to end of each edge
			}
		}
	}*/

	for(byte corner_i=0;corner_i<4;corner_i++)
	{
		for(byte axi=0;axi<3;axi++)
		{
			//for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
			{
				moveOutAllRemainFirst_ret_last(0+NUM_LEDS_edge*(corner_i*3+axi),(NUM_LEDS_edge-1)+NUM_LEDS_edge*(corner_i*3+axi));//!? -1 
				leds[0+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(90*axi, (millis()/100%2==0 )? 255:0, 255); //color of 0..4|all LEDs to edges
			}
		}
	}
}





//long effStart_t=0; //TODO fade end of axis
void CubeTest()
{		gDelay=30; 

	//fill_rainbow (leds, NUM_LEDS, 0, 1);

	eff_t_stage = indexOrBits==0 ? (millis() / 1000) % 32: indexOrBits;                // Increase this if you want a longer demo.

																			if(millis()>20000 && random8()>250) {anim_f=CubeCornersLight; gDelay=10;}

	switch (eff_t_stage)
	{
		case 0:
			clear_leds(); //? true need

			for(byte corner_i=0;corner_i<4;corner_i++)
			{
				for(byte axi=0;axi<3;axi++)
				{
					for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
					{
						leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=ColorFromPalette(RainbowColors_p, map(corner_i,0,3,0,190), 255, LINEARBLEND); //color of corners
					}
				}
			}
		break;

		case 3:
			clear_leds(); //? true need

			for(byte corner_i=0;corner_i<4;corner_i++)
			{
				for(byte axi=0;axi<3;axi++)
				{
					for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
					{
						leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(55*corner_i, 255, 255-i*k_fade_edge*(i_eff%512)/512  ); //color of corners, fading to end of each edge
					}
				}
			}
		break;

		case 10: 
			//clear_leds();
			for(byte corner_i=0;corner_i<4;corner_i++)
			{
				for(byte axi=0;axi<3;axi++)
				{
					for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
					{
						leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(90*axi, 255, 255); //color of LEDs to axis
					}
				}
			}
		break;

		case 12: 
			//clear_leds();
		{
			float k= k_fade_edge*sin8((float)millis()/(1+effFade))/255.0;
			for(byte corner_i=0;corner_i<4;corner_i++)
			{
				for(byte axi=0;axi<3;axi++)
				{
					for(NUM_LEDS_type i=0;i<NUM_LEDS_edge;i++)
					{
						leds[i+NUM_LEDS_edge*(corner_i*3+axi)]=CHSV(90*axi, 255, 255-i*k ) ; // /256  color of LEDs to axis, fading to end of each edge, anim to t
					}
				}
			}
		}
		break;


		case 18:
		
		 //bottom rainbow. Last seg bug
			fill_rainbow( leds4edges, NUM_LEDS_edge*4, gHue/2, 1);

			memcpy8( &leds[0],									&leds4edges[NUM_LEDS_edge*0], NUM_LEDS_edge*3 );

			for(byte i=0;i<NUM_LEDS_edge;i++) //memcpy8( &(leds[NUM_LEDS_edge*3*2+ NUM_LEDS_edge*2]),	&leds4edges[NUM_LEDS_edge*1], NUM_LEDS_edge*3 ); //reverse
			{
				leds[NUM_LEDS_edge*3*2+ NUM_LEDS_edge*3  -i-1]=leds4edges[NUM_LEDS_edge*3 -i-1];
			}
			

			memcpy8( &(leds[NUM_LEDS_edge*3*2+ NUM_LEDS_edge*0]),	&leds4edges[NUM_LEDS_edge*2], NUM_LEDS_edge*3 );

			//memcpy8( &(leds[0+ NUM_LEDS_edge*2]), 					&leds4edges[NUM_LEDS_edge*3], NUM_LEDS_edge*3 );//reverse
			for(byte i=0;i<NUM_LEDS_edge;i++) 
			{
				leds[0+ NUM_LEDS_edge*2+i]=leds4edges[NUM_LEDS_edge*2 +i]; //leds4edges[NUM_LEDS_edge*3 -i-1]; //it should be like this but..
			}
		
			
		break;


		case 22:
			for(int i=0;i<NUM_LEDS_edge;i++)
			{
				leds[0+i]=								ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*0+i,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
				leds[NUM_LEDS_edge*3*2+i]=				ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*1 +NUM_LEDS_edge-i-1,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
				leds[NUM_LEDS_edge*3*2+NUM_LEDS_edge*2+i]=ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*2+i,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
				leds[0+ NUM_LEDS_edge*2+i]=				ColorFromPalette(RainbowColors_p, map(NUM_LEDS_edge*3 +NUM_LEDS_edge-i-1,0,NUM_LEDS_edge*4,0,255), 255, LINEARBLEND);
			}
			
		break;


		case 25:
			//for(byte i=0;i<NUM_LEDS_edge;i++)
			{
				CRGB c=i_eff%20<4? CRGB::Red:CRGB::Black;

				leds[NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + 0]=c;
				leds[NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1]=c;
				leds[NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0]=c;
				leds[NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1]=c;


				moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + 0, NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1);
				moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1, NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1);
				moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0,NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0+ NUM_LEDS_edge-1);
				moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1,NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1);

				//rotation bottom, eventually appear red Y:
				// moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + 0, NUM_LEDS_edge*3*0+ NUM_LEDS_edge*1 + NUM_LEDS_edge);
				// moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1- NUM_LEDS_edge, NUM_LEDS_edge*3*1+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1);
				// moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0,NUM_LEDS_edge*3*2+ NUM_LEDS_edge*1 + 0+ NUM_LEDS_edge);
				// moveOutAllRemainFirst_ret_last(NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1- NUM_LEDS_edge,NUM_LEDS_edge*3*3+ NUM_LEDS_edge*1 + NUM_LEDS_edge-1);

			}

    }
}