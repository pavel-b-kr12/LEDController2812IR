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


int pos=0;
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
    int rowE=plotPX.matrix_rowsE;  

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
		
      case 2:
      {
        for (int i=0; i<NUM_LEDS_sim_arr_size; i++) 
          msg_buffer[i]=i/3/matrixW%2 *255; //odd row
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
	  
	  	case 10: //cow
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
	  

    if(bFlipArr_sim_to_zigZag_matrix)
    {
                // msg_buffer[0*3+1]=255;
                // msg_buffer[8*3]=255;
                // msg_buffer[16*3+1]=255;
                // msg_buffer[24*3]=255;
        //flip odd row due zig-zag connection //also plot b_matrix_arr_is_zigZag=true by default
        for (int r=0; r<rowE; r++) 
        {
          for (int c=0; c<matrixW/2; c++) 
          {
            if(r%2==1)
            {
               int t=msg_buffer[(r*matrixW+c)*3];
               msg_buffer[(r*matrixW+c)*3]=msg_buffer[((r+1)*matrixW-c-1)*3];
               msg_buffer[((r+1)*matrixW-c-1)*3]=t;
            }
          }
        }
    }
    
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
