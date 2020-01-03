//!! clear btn


void clear_msg_buffer(int E)
{
    for (int i=0; i<E; i++) //clear
    {
      msg_buffer[i*3]=0;
      msg_buffer[i*3+1]=0;
      msg_buffer[i*3+2]=0;
	}
}

//HSV to RGB  use colorMode(HSB, 255);  or https://docs.oracle.com/javase/8/docs/api/java/awt/Color.html#RGBtoHSB-int-int-int-float:A-
//!opt colorHSV=CHSV(
void msg_buffer_colorSetHSV(int pos, color c)
{
	msg_buffer[pos*3]= c >> 16 & 0xFF;
	msg_buffer[pos*3+1]= c >> 8 & 0xFF;
	msg_buffer[pos*3+2]= c >> 0 & 0xFF;
}
void msg_buffer_colorAddHSV(int pos, color c)
{
	msg_buffer[pos*3]+= c >> 16 & 0xFF;
	msg_buffer[pos*3+1]+= c >> 8 & 0xFF;
	msg_buffer[pos*3+2]+= c >> 0 & 0xFF;
}
void msg_buffer_colorIfAddHSV(int pos, color c)
{
	int r=msg_buffer[pos*3]+c >> 16 & 0xFF;
	if(r<255)
	msg_buffer[pos*3]=r;

	int g=msg_buffer[pos*3+1]+c >> 8 & 0xFF;
	if(g<255)
	msg_buffer[pos*3+1]= g;

	int b=msg_buffer[pos*3+2]+c >> 0 & 0xFF;
	if(b<255)
	msg_buffer[pos*3+2]+= c >> 0 & 0xFF;
}
void msg_buffer_colorQAdd8HSV(int pos, color c)
{
	msg_buffer[pos*3]+= c >> 16 & 0xFF;
	if(msg_buffer[pos*3]>255) msg_buffer[pos*3]=255;
	msg_buffer[pos*3+1]+=  c >> 8 & 0xFF;
	if(msg_buffer[pos*3+1]>255) msg_buffer[pos*3+1]=255;
	msg_buffer[pos*3+2]+=  c >> 0 & 0xFF ;
	if(msg_buffer[pos*3+2]>255) msg_buffer[pos*3+2]=255;
}

void rollover_msg_buffer(int E) //as in FastLED
{
    for (int i=0; i<E; i++) //clear
    {
      msg_buffer[i*3]%=256;
      msg_buffer[i*3+1]%=256;
      msg_buffer[i*3+2]%=256;
	}
}

int blur_(int ir_l, int ir, int ir_r, int speedH, int effFade, int lengthH, int length_ )
{
  return (int)(
  400*msg_buffer[ir_l]*speedH/(speedH+effFade+lengthH)/(200+length_)+  ///length_*10
  400*msg_buffer[ir]*effFade/(speedH+effFade+lengthH)/(200+length_)+
  400*msg_buffer[ir_r]*lengthH/(speedH+effFade+lengthH)/(200+length_)
  );
  
	// msg_buffer[ig]=(int)(msg_buffer[ig_l]*0.2+msg_buffer[ig]*0.8); 
	// msg_buffer[ib]=(int)(msg_buffer[ib_l]*0.2+msg_buffer[ib]*0.8);
	
	  /* //int
	  msg_buffer[ir]=(msg_buffer[ir_l]+msg_buffer[ir]+msg_buffer[ir_r])/3; //blur
	  msg_buffer[ig]=(msg_buffer[ig_l]+msg_buffer[ig]+msg_buffer[ig_r])/3; //blur
	  msg_buffer[ib]=(msg_buffer[ib_l]+msg_buffer[ib]+msg_buffer[ib_r])/3; //blur
	  */
}

void fadeAll(int f)
{
	int NUM_LEDS_sim=settingsVals.get("NUM_LEDS").value;
	int NUM_LEDS_sim_arr_size=NUM_LEDS_sim*3;
	for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++,ir+=3,ig+=3,ib+=3) 
	{
		int c=msg_buffer[ir];
		msg_buffer[ir]=(c>f)?c-f:0; //odd row

		c=msg_buffer[ig];
		msg_buffer[ig]=(c>f)?c-f:0;
	  
		c=msg_buffer[ib];
		msg_buffer[ib]=(c>f)?c-f:0;
	}
}

void fadeAll_move_matrix(int ff, int rowE, int matrixW)
{
	for (int r=0; r<rowE; r++) 
	{
		int f=ff;
		for (int xx=matrixW-1; xx>0; xx--) 
		{
			//if(c==r) msg_buffer[(r*matrixW+c)*3]=255;

			int x=r*matrixW+xx;

			int c=0;
													f=f+(int)random(-2,2);
			c=msg_buffer[(x-1)*3+0];
			msg_buffer[x*3+0] = (f==0) ? c: ( (c>f)?c-f:0 );

			c=msg_buffer[(x-1)*3+1];
			msg_buffer[x*3+1] = (f==0) ? c: ( (c>f)?c-f:0 );

			c=msg_buffer[(x-1)*3+2];
			msg_buffer[x*3+2] = (f==0) ? c: ( (c>f)?c-f:0 );
		}
	}
}

void swap_led(int n, int n1)
{
	swap_led_ch(n*3, n1*3); //r
	swap_led_ch(n*3+1, n1*3+1); //g
	swap_led_ch(n*3+2, n1*3+2); //b
}
void swap_led_ch(int n, int n1)
{
	int t=msg_buffer[n];
	msg_buffer[n]=msg_buffer[n1];
	msg_buffer[n1]=t;
}

void flip_zigZag_matrix(int rowE, int matrixW)
{
	if(bFlipArr_sim_to_zigZag_matrix)
	{
		//println(millis());
				// msg_buffer[0*3+1]=255;
				// msg_buffer[8*3]=255;
				// msg_buffer[16*3+1]=255;
				// msg_buffer[24*3]=255;
		//flip odd row due zig-zag connection //also plot b_matrix_arr_is_zigZag=true by default
		for (int r=0; r<rowE; r++) 
		{
		  for (int xx=0; xx<matrixW/2; xx++) 
		  {
			if(r%2==1)
			{
				swap_led(r*matrixW+xx, (r+1)*matrixW-xx-1);
			}
		  }
		}
	}
}

int pos=0;
float pos_f=0;
int pos_last=0;
int store=0;
boolean bclear_msg_buffer_now=false;
void sim()
{
    int NUM_LEDS_sim=settingsVals.get("NUM_LEDS").value;
    int NUM_LEDS_sim_arr_size=NUM_LEDS_sim*3;
    if(plotPX==null) plotPX_create();

	if(bclear_msg_buffer_now) 
	{
		clear_msg_buffer(NUM_LEDS_sim);
		bclear_msg_buffer_now=false;
	}
//------------- effect  eff_set2.h eff_sin

                                    if(myPort==null) bSendSimDataToMCU = false;
                                    if(bSendSimDataToMCU)
                                    {
                                      myPort.write(232);
                                      myPort.write(232);
                                    }


    int matrixW=plotPX.matrix_leds_per_row;
    int rowE=plotPX.matrix_leds_per_col;  

	int effN=settingsVals.get("effN").valueSlider.getValueI();
	int speed=settingsVals.get("speed").valueSlider.getValueI();
	int speedH=settingsVals.get("speedH").valueSlider.getValueI();
	int length_=settingsVals.get("length").valueSlider.getValueI();
	int lengthH=settingsVals.get("lengthH").valueSlider.getValueI();
	int RGB_=settingsVals.get("RGB").valueSlider.getValueI();
	int effFade=settingsVals.get("effFade").valueSlider.getValueI();
	int gColorH=settingsVals.get("gColorH").valueSlider.getValueI();
	int gColorS=settingsVals.get("gColorS").valueSlider.getValueI();
	int gColorV=settingsVals.get("gColorV").valueSlider.getValueI();
	int indexOrBits=settingsVals.get("indexOrBits").valueSlider.getValueI();
	int gDelay=settingsVals.get("gDelay").valueSlider.getValueI();
	int gBrightness=settingsVals.get("gBrightness").valueSlider.getValueI();
	
	int effSpeed=speed;
	int effSpeedH=speedH;
	int effLength=length_;
	int effLengthH=lengthH;
	int effRGB=RGB_;
	
	
	flip_zigZag_matrix(rowE, matrixW);
      
    switch(effN)
    {
	
      
      case 0:
      {
        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++,ir+=3,ig+=3,ib+=3) 
        {
          msg_buffer[ir]=ir%2 *255; //odd row
          msg_buffer[ig]++;
          msg_buffer[ib]=(int)(sin(ib*4)*255);
        }
      }
      break;  
	 case 1:
	{
		colorMode(HSB, 255);
		
		int fade=effFade;
		int spd=effSpeed;
		int len=effLength;
		int len2=effLengthH;
		
		if(indexOrBits==1) //  /10%10==0)
		{
			 fade=11;
			 spd=125;//153 //131
			 len=146; //116 // 109
			 len2=48; //66 // 33
		}
		if(indexOrBits==3) //  /10%10==0)
		{
			 fade=0;
			 spd=131;
			 len=109;
			 len2=33;
		}
		
		/*
		
		
		for(int i=0;i<14;i++)
		{
		 pos_f+=1/(1+pos_f%NUM_LEDS_sim/2);
		 msg_buffer_colorAddHSV((int)(pos_f%NUM_LEDS_sim), color(millis()/10%256,211,255));
		
			if(indexOrBits%2==1)
			{
			 pos_f+=1/(1+(pos_f+10)%NUM_LEDS_sim/2);
			 msg_buffer_colorAddHSV((int)((pos_f+10)%NUM_LEDS_sim), color(millis()/31%256,211,255));
			}
		}
		*/
		 fadeAll(5+fade);
		for(int x=0;x<NUM_LEDS_sim;x++)
		{
			float tt=(float)millis()/(160) ;//(float)millis()/(120+effLength/4);
			
			if(indexOrBits%4==1)
			msg_buffer_colorIfAddHSV(x, 
				color(millis()/10%256,255,
				sin(	pow((float)((float)NUM_LEDS_sim*len/240+(float)x*spd/240)/NUM_LEDS_sim,(8+len2)/8)*3.14*10	-	tt	)	*111)); //,(float)(2+len2)/8)*3.14*10
			else
				if(indexOrBits%4==2)
						msg_buffer_colorQAdd8HSV(x, 
				color(millis()/10%256,255,
				sin(	pow((float)((float)NUM_LEDS_sim*len/240+(float)x*spd/240)/NUM_LEDS_sim,(8+len2)/8)*3.14*10	-	tt	)	*111));
			else
							if(indexOrBits%4==3)
						msg_buffer_colorIfAddHSV(x, 
				color(millis()/10%256,255,
				sin(	pow((float)((float)NUM_LEDS_sim*len/240+(float)x*spd/240)/NUM_LEDS_sim,(8+len2)/8)*3.14*10	-	tt	)	*111));
			else
			msg_buffer_colorAddHSV(x, color(millis()/10%256,255,sin(x+millis()/len)*effSpeedH));
		}
		colorMode(RGB, 255);
	}
	break;
	case 24:
	{
		colorMode(HSB, 255);
		
		int fade=effFade;
		int spd=effSpeedH;
		
		if(indexOrBits%2==1)
		{
			// fade=239;
			// spd=13;
		}
		
		fadeAll(1+fade);
		for(int i=0;i<14;i++)
		{
		 pos_f+=1/(1+pos_f%NUM_LEDS_sim/2);
		 msg_buffer_colorAddHSV((int)(pos_f%NUM_LEDS_sim), color(millis()/10%256,211,255));
		
			if(indexOrBits%2==1)
			{
			 pos_f+=1/(1+(pos_f+10)%NUM_LEDS_sim/2);
			 msg_buffer_colorAddHSV((int)((pos_f+10)%NUM_LEDS_sim), color(millis()/31%256,211,255));
			}
		}
		 
		// for(int x=0;x<NUM_LEDS_sim;x++)
		// {
			// msg_buffer_colorAddHSV(x, color(millis()/10,spd,255));
		// }
		colorMode(RGB, 255);
	}
	break;
	
	case 23:
	{
		colorMode(HSB, 255);
		
		int fade=effFade;
		int spd=effSpeedH;
		
		if(indexOrBits%2==1)
		{
			// fade=239;
			// spd=13;
		}
		
		fadeAll(1+fade);
		for(int i=0;i<10;i++)
		{
		 pos++;
		 
		 msg_buffer_colorAddHSV((int)pow((float)(pos%pow(NUM_LEDS_sim,1.3)),0.7), color(millis()/10,222,255));
		}
		 
		// for(int x=0;x<NUM_LEDS_sim;x++)
		// {
			// msg_buffer_colorAddHSV(x, color(millis()/10,spd,255));
		// }
		colorMode(RGB, 255);
	}
	break;
	
	case 22:
	{
		colorMode(HSB, 255);
		
		int fade=effFade;
		int spd=effSpeedH;
		
		if(indexOrBits%2==1)
		{
			fade=239;
			spd=13;
		}
		
		fadeAll(1+fade);
		 pos++;
		 
		 msg_buffer_colorAddHSV(pos%NUM_LEDS_sim, color(millis()/10,222,255));
		 
		 
		for(int x=0;x<NUM_LEDS_sim;x++)
		{
			msg_buffer_colorAddHSV(x, color(millis()/10,spd,255));
		}
		colorMode(RGB, 255);
	}
	break;	  

      case 21: //mover by split dir
      { //TODO add colors w & wo overflow
			int cType=indexOrBits;
			bFlipArr_sim_to_zigZag_matrix=indexOrBits/20%2==1;
			
		  boolean dir=true;
		  boolean bHueRot=effFade%2==0;
		  int leds_per_seg=indexOrBits/10%2==0? (14+effLengthH): (1+millis()/300%5+effLengthH);
		  colorMode(HSB, 255);
		  pos++;
		  //if(pos==NUM_LEDS_sim-1) pos=0;
			  
			fadeAll(1+effFade);
			
		  for(int x=0, seg=0;x<NUM_LEDS_sim;seg++)
		  {
			  for(int sx=0;sx<leds_per_seg && x<NUM_LEDS_sim; sx++, x++)
			  {
				  int Hadd=bHueRot?millis()/(1+effSpeed):0;
				  switch(cType%5)
				  {
					  case 0: //:)
					  if(pos%NUM_LEDS_sim==x) //!! good look only if flip_zigZag_matrix bFlipArr_sim_to_zigZag_matrix
					  {
						  color c = color((seg*31+Hadd)%256, (255)%256, (128+millis()/2%256/2)%256); //HSV
						  msg_buffer_colorSetHSV(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx-1), c);
					  }
					  break;
					  case 1:
					  if(pos%NUM_LEDS_sim==(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx)))
					  {
						  color c = color((seg*(11+effLength)+Hadd)%256, 255, 255); //HSV
						  msg_buffer_colorSetHSV(x, c); //dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx-1)
					  }
					  break;
					  case 3:
					  if(pos%NUM_LEDS_sim%(1+sx)+seg*sx+millis()/10%NUM_LEDS_sim==seg*leds_per_seg+sx)
					  {
						  color c = color((seg*31+Hadd)%256, (255)%256, (128+millis()/2%256/2)%256); //HSV
						  msg_buffer_colorSetHSV(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx+3), c);
					  }
					  break;
					  case 4: //:)
					  if(pos%NUM_LEDS_sim%(1+sx)+seg*leds_per_seg==seg*leds_per_seg+sx)
					  {
						  color c = color((seg*31+Hadd)%256, (255)%256, (128+millis()/2%256/2)%256); //HSV
						  msg_buffer_colorSetHSV(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx-1), c);
					  }
					  break;
					  case 5:
					  if(pos%NUM_LEDS_sim==(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx+1)))
					  {
						  color c = color((seg*(11+effLength)+Hadd)%256, (255)%256, (128+millis()/8%256/2)%256); //HSV
						  msg_buffer_colorSetHSV(dir? (seg*leds_per_seg+sx) : ((seg+1)*leds_per_seg-sx+1), c);
					  }
					  break;

				  }
			  }
			  dir=!dir;
		  }
		  colorMode(RGB, 255);
	  }
	  break;
	  
      case 2:
      {
        for (int i=0; i<NUM_LEDS_sim_arr_size; i++) 
          msg_buffer[i]=i/3/matrixW%2 *255; //odd px
      }
      break;

      case 3:
      {
        for (int r=0; r<rowE; r++) 
        {
          for (int c=0; c<matrixW; c++) 
          {
              //if(c==r) msg_buffer[(r*matrixW+c)*3]=255;
            msg_buffer[(r*matrixW+c)*3 +1]=r*16;
            msg_buffer[(r*matrixW+c)*3]=(int) (  (float)c/matrixW*255 );

            // switch(r)
            // {
            //   case 0:
               
            //   break;
            // }
            

          }
        }
      }
      break;

      case 4:
      {
        for (int r=0; r<rowE; r++) 
        {
          for (int c=0; c<matrixW; c++) 
          {
            if(c==r) msg_buffer[(r*matrixW+c)*3]=255;

            // switch(r)
            // {
            //   case 0:
               
            //   break;
            // }
            

          }
        }
      }
      break;
      
      case 5: //:)   !!blend @ sin time
      {

        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          msg_buffer[ir]+=1+random(millis()/2000%3==0?i:33)/22;
          msg_buffer[ig]+=1+random(millis()/2000%3==0?i:33)/22;
          msg_buffer[ib]+=1+random(millis()/2000%3==0?i:33)/22;
        }
        
        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          int ir_l=ir-3; if(ir_l<0)ir_l+=NUM_LEDS_sim_arr_size;
          int ig_l=ig-3; if(ig_l<0)ig_l+=NUM_LEDS_sim_arr_size;
          int ib_l=ib-3; if(ib_l<0)ib_l+=NUM_LEDS_sim_arr_size;
          
          int ir_r=ir+3; if(ir_r>NUM_LEDS_sim_arr_size)ir_r=0;
          int ig_r=ig+3; if(ig_r>NUM_LEDS_sim_arr_size)ig_r+=1;
          int ib_r=ib+3; if(ib_r>NUM_LEDS_sim_arr_size)ib_r+=2;
          
          if(millis()/2000%2==0) //color
          {
          msg_buffer[ir]=(int)(msg_buffer[ir_l]*0.1+msg_buffer[ir]*0.8+msg_buffer[ir_r]*0.1); //blur
          msg_buffer[ig]=(int)(msg_buffer[ig_l]*0.1+msg_buffer[ig]*0.8+msg_buffer[ig_r]*0.1); 
          msg_buffer[ib]=(int)(msg_buffer[ib_l]*0.1+msg_buffer[ib]*0.8+msg_buffer[ib_r]*0.1); 
          }
          else //bw
          {
          msg_buffer[ir]=(int)(msg_buffer[ir_l]*0.1+msg_buffer[ir]*0.8+msg_buffer[ir_r]*0.1); //blur
          msg_buffer[ig]=(int)(msg_buffer[ig_l]*0.1+msg_buffer[ir]*0.8+msg_buffer[ir_r]*0.1); 
          msg_buffer[ib]=(int)(msg_buffer[ib_l]*0.1+msg_buffer[ir]*0.8+msg_buffer[ir_r]*0.1); 
          }
        }
        
      }
      break;
	  
	  case 6:
      {
		 //	effSpeed=0;	effLength=8;	effSpeedH=14;	effLengthH=1;	effFade=28;    gColor=CRGB(1,1,1);	indexOrBits=1;	gDelay=1; break;

        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          //msg_buffer[ir]=i%2*255 ;//+(int)(random(1)*255); //odd row
          msg_buffer[ir]+=3+random(10)*speed/44;
         // msg_buffer[ig]+=3+random(44)/22;
         // msg_buffer[ib]+=3+random(44)/22;
          //msg_buffer[ib]=(int)(sin(ib)*255);
        }
        
        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          int ir_l=ir-3; if(ir_l<0)ir_l+=NUM_LEDS_sim_arr_size;
          int ig_l=ig-3; if(ig_l<0)ig_l+=NUM_LEDS_sim_arr_size;
          int ib_l=ib-3; if(ib_l<0)ib_l+=NUM_LEDS_sim_arr_size;
          
          int ir_r=ir+3; if(ir_r>NUM_LEDS_sim_arr_size)ir_r=0;
          int ig_r=ig+3; if(ig_r>NUM_LEDS_sim_arr_size)ig_r+=1;
          int ib_r=ib+3; if(ib_r>NUM_LEDS_sim_arr_size)ib_r+=2;
          

          msg_buffer[ir]=(int)(
              msg_buffer[ir_l]*speedH/(speedH+effFade+lengthH)/length_*10+
              msg_buffer[ir]*effFade/(speedH+effFade+lengthH)/length_*10+
              msg_buffer[ir_r]*lengthH/(speedH+effFade+lengthH)/length_ *10); //blur
         // msg_buffer[ig]=(int)(msg_buffer[ig_l]*0.2+msg_buffer[ig]*0.8); 
        //  msg_buffer[ib]=(int)(msg_buffer[ib_l]*0.2+msg_buffer[ib]*0.8); 
          
        /* //int
          msg_buffer[ir]=(msg_buffer[ir_l]+msg_buffer[ir]+msg_buffer[ir_r])/3; //blur
          msg_buffer[ig]=(msg_buffer[ig_l]+msg_buffer[ig]+msg_buffer[ig_r])/3; //blur
          msg_buffer[ib]=(msg_buffer[ib_l]+msg_buffer[ib]+msg_buffer[ib_r])/3; //blur
          */
          
        }
        
      }
      break;
	  
	  case 7: //length_=200
      {
		 //	effSpeed=0;	effLength=8;	effSpeedH=14;	effLengthH=1;	effFade=28;    gColor=CRGB(1,1,1);	indexOrBits=1;	gDelay=1; break;
		 //	effSpeed=4;	effLength=100;	effSpeedH=0;	effLengthH=1;	effFade=0;    gColor=CRGB(1,1,1);	indexOrBits=1;	gDelay=1; break;
		 // effSpeed=3;	effLength=193;	effSpeedH=139;	effLengthH=1;	effFade=74;    gColor=CRGB(1,1,1);	indexOrBits=1;	gDelay=1; break;

        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          //msg_buffer[ir]=i%2*255 ;//+(int)(random(1)*255); //odd row
          msg_buffer[ir]+=3+random(44)*speed/44;
          msg_buffer[ig]+=3+random(44)*speed/44;
          msg_buffer[ib]+=3+random(44)*speed/44;
          //msg_buffer[ib]=(int)(sin(ib)*255);
        }
        
        for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++, ir+=3,ig+=3,ib+=3) 
        {
          int ir_l=ir-3; if(ir_l<0)ir_l+=NUM_LEDS_sim_arr_size;
          int ig_l=ig-3; if(ig_l<0)ig_l+=NUM_LEDS_sim_arr_size;
          int ib_l=ib-3; if(ib_l<0)ib_l+=NUM_LEDS_sim_arr_size;
          
          int ir_r=ir+3; if(ir_r>NUM_LEDS_sim_arr_size)ir_r=0;
          int ig_r=ig+3; if(ig_r>NUM_LEDS_sim_arr_size)ig_r+=1;
          int ib_r=ib+3; if(ib_r>NUM_LEDS_sim_arr_size)ib_r+=2;
          


          msg_buffer[ir]=blur_(ir_l,ir,ir_r,  speedH,  effFade,  lengthH,  length_);
          msg_buffer[ig]=blur_(ig_l,ig,ig_r,  speedH,  effFade,  lengthH,  length_);
          msg_buffer[ib]=blur_(ib_l,ib,ib_r,  speedH,  effFade,  lengthH,  length_);

          
        }
        
      }
      break;

      case 8: //:) //!use
	  { //fire gen rand 
	  //bclear_msg_buffer_now=true;
		//fadeAll_move_matrix(21, rowE, matrixW);
		////fadeAll_move_matrix((int)random(17,24), rowE, matrixW); //дерганное от ранлома
		fadeAll_move_matrix(11+mouseX/200, rowE, matrixW);
		//fadeAll(25);
		
		
	    for (int ro=0; ro<rowE; ro++) 
        {
			for (int c=0; c<matrixW; c++) 
			{
				//if(c==ro) msg_buffer[(ro*matrixW+c)*3]=255;
						if(c>0) break;
				
				
					int heatRnd=(int)random(50,255);
					int heat=(int)(noise((float)ro,(float)millis()/200)*255);
					heat=(int)( heat*(1-mouseY/width)+heatRnd*mouseY/width);
					
					int r= heat*2; if(r>255) r=255; 
					if(heat>220) r-=heat/10;
					
					int g= heat*2-200;  g=  constrain(g,0,255);
					if(heat>220) g-=heat/10;
					
					int b= heat*2-300;  b=  constrain(b,0,255);
					

				msg_buffer[(ro*matrixW+c)*3+0]=r;
				msg_buffer[(ro*matrixW+c)*3+1]=g;
				msg_buffer[(ro*matrixW+c)*3+2]=b;
				/*
					int heat=(int)random(50,255);
					int heatHi=(int)random(heat);
					
				msg_buffer[(ro*matrixW+c)*3+0]=heat;
				msg_buffer[(ro*matrixW+c)*3+1]=heatHi;
				msg_buffer[(ro*matrixW+c)*3+2]=heatHi;
				*/
			}
        }
		
/*
        for (int ro=0; ro<rowE; ro++) 
        {
			for (int c=0; c<matrixW; c++) 
			{
				//if(c==ro) msg_buffer[(ro*matrixW+c)*3]=255;

				msg_buffer[(ro*matrixW+c)*3+0]=(int) ((float)r/rowE*255);
				msg_buffer[(ro*matrixW+c)*3+1]=(int) ( (float)c/matrixW*255 );
				msg_buffer[(ro*matrixW+c)*3+2]=0;
			}
        }*/
	  }
      break;
	  
	  	case 11: //cow
		{
			effFade=220+effFade;
			length_=20+length_;
			
			if((msg_buffer[pos*3+1]<2) || random(1)>0.8 )
			{
				pos_last=pos;
				pos++;
				if(pos==NUM_LEDS_sim-1) pos=0;
				store--;
				msg_buffer[pos_last*3]=0;
				msg_buffer[pos*3]=255;
			}
			
			for(int i=0;i<1+length_;i++)
			{
				if(msg_buffer[pos*3+1]>0)
				{
					msg_buffer[pos*3+1]--;
					store++;
					if(store==255)
					{
						store-=44;
						msg_buffer[pos_last*3]+=22;
					}
				}
				else break;
			}
			
			for (int i=0,ir=0,ig=1,ib=2; ir<NUM_LEDS_sim_arr_size; i++,ir+=3,ig+=3,ib+=3) 
			{
			  if(msg_buffer[ir]!=0)
			  {
				  msg_buffer[ir]--;
				  msg_buffer[ig]++;
			  }
			  if(random(1)>(float)effFade/255)
				msg_buffer[ig]+=random(2);
			  
			  //msg_buffer[ib];
			}
		}
      break;
	  
	  //==================================== texture generators (not for stripe)
	  case 100: //mover by split dir
      {
		  int cType=indexOrBits;

		  boolean dir=true;
		  int leds_per_seg=16;
		  colorMode(HSB, 255);
		  for(int pos=0, h=0;pos<NUM_LEDS_sim;h++)
		  {
			  for(int sx=0;sx<leds_per_seg && pos<NUM_LEDS_sim; sx++, pos++)
			  {
				  color c = color((h*31)%256, millis()%256, millis()*11%256); //HSV
				  switch(cType)
				  {
					  case 0:
					  c = color((h*31)%256, millis()%256, millis()*11%256); //HSV
					  break;
					  case 1:
					  c = color((h*31)%256, (millis()/10)%256, (millis()*11+pos)%256); //HSV
					  break;
					  case 2:
					  c = color((h*effSpeed)%256, (millis()/effLength)%256, (millis()*effLengthH+pos)%256); //HSV
					  break;
				  }
				  msg_buffer_colorSetHSV(pos, c);
			  }
			  dir=!dir;
		  }
		  colorMode(RGB, 255);
	  }
	  break;

	//==================================== 
      default:
        for (int i=0; i<NUM_LEDS_sim_arr_size; i++) 
        {
          msg_buffer[i]=(int) ( (sin(i/1.+millis()/1000.) +1) *255);
        }
      break;
    }

	rollover_msg_buffer(NUM_LEDS_sim);
	
	
	      fill(0, 255, 0);
      text(msg_buffer[0], mouseX+20, mouseY+80);
      text(msg_buffer[1], mouseX+20, mouseY+100);
      text(msg_buffer[2], mouseX+20, mouseY+120);
	  
	flip_zigZag_matrix(rowE, matrixW);


    if(bSendSimDataToMCU) 
      for (int i=0; i<NUM_LEDS_sim_arr_size; i++)
        myPort.write(((int)msg_buffer[i])%255);

    
//-------------
    if(bDrawLEDs_PXHistory_enabled)
    {  
      plotPX.push(msg_buffer, NUM_LEDS_sim_arr_size);
      bplotPX=true;
      bDraw_plotPX_until_t=millis()+10000;
    }
    if(bDraw_plot_RGB_pow)
    {
      plotR.push(plotPX.rE); plotR.tik();
      plotG.push(plotPX.gE); plotG.tik();
      plotB.push(plotPX.bE); plotB.tik();
    }
    // bDrawFPSnow=rec_fps;//!!
    // plotFPS.push(bDrawFPSnow); //plotFPS.push(((float)bDrawFPSnow)/10.);
    // bDrawFPS_until_t=millis()+1000;


    bDrawPownow=plotPX.rE+plotPX.gE+plotPX.bE;
    plot_pow.push(bDrawPownow);
    bDrawPow_until_t=millis()+1000; //!! move to push
	



  }
