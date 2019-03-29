
#ifdef SerialControl
//## SET_UPD_Display saveAfter2s();

	#define msgN_m			232

	#define msg_getLeds		232

	#define msg_gDelay		234
	#define msg_effFade		235
	#define msg_gColorR		236
	#define msg_gColorG		237
	#define msg_gColorB		238
	#define msg_indexOrBits	239
	#define msg_NUM_LEDS	240

	#define messageEffN		241
	#define messageSpeed	242
	#define messageLength	243
	#define messageRGB		244
	#define messageSpeedH	245
	#define messageLengthH	246
	#define messageBright	247
	#define messageAction	248
	#define messageSave		249
	//#define messageLoad		250
	#define messageClear	251
	#define messagePause	252
	#define messageReset	253
	#define msgprint		254
 #ifdef tstFPS
	#define msgprintPX		255
#endif
	#define msgN_M			255


byte mesageRecState=0;
byte msgLast=0;
void setValueFromMsg(byte msgType, byte value)
{
	#ifdef tst2
	Serial.print(msgType);Serial.print(" msg ");Serial.println(value);
	#endif
								
	bool bNeedUpdDisplay=true;
	switch(msgType)   //!opt simple array from 0
	{
		case messageEffN:
			//effN=value;
			//change_slot(effN);
		 effN_set(value);
		break;
		case messageSpeed:
		 effSpeed=value;
		break;
		case messageLength:
		 effLength=value;
		break;
		case messageRGB:
		 effRGB=value;
		break;
		case messageSpeedH:
		 effSpeedH =value;
		break;
		case messageLengthH:
		  effLengthH=value;
		break;

		case msg_gDelay:
		  gDelay=value;
		break;
		case msg_effFade:
		  effFade=value;
		break;
		case msg_gColorR:
		  gColor.r=value;
		break;
		case msg_gColorG:
		  gColor.g=value;
		break;
		case msg_gColorB:
		  gColor.b=value;
		break;
		case msg_indexOrBits:
		  indexOrBits=value;
		break;
		case msg_NUM_LEDS:
			#ifdef NUM_LEDS_adjustable
			#if gNUM_LEDS>255
		  		NUM_LEDS=value*8;
		  	#else
		  		NUM_LEDS=value;
		  	#endif	
		  		NUM_LEDS_set();
		  	#endif
		break;

		case messageBright:
		 FastLED.setBrightness( value ); 
					 #if gNUM_LEDS<256 //!? otherwise crash when often change
					 	FastLED.show();
					 #endif
		 gBrightness=value;
		break;


		case messageSave:
		#ifdef save_load_enable
		 save(value);
		#endif
		break;
		// case messageLoad:
		//  load(value);
		// break;
		case messageClear:
		 FastLED.clear();
		 FastLED.show();
		break;
		case messagePause:
		 bPause=!bPause; //return from LED_anim() //!! nw
		break;
		case messageReset:
		 if(value==0)
		  resetSetiings_and_change_slot();//!
		 else change_slot(effN);
		break;
		case messageAction:
		 switch(value) //! btn
		 {
		 	case 0: flashLEDs(); FastLED.show(); break;
		 	case 1: invertLEDs(); FastLED.show(); delay(10); break;

		 	case 2: 
		 	for(byte i = 0; i < 10; ++i)
		 	{
		 		addGlitter(255);
		 	}
		 	FastLED.show();
		 	break;
		 	
		 	case 3: flashAndBackLEDs(); break;
		 	case 4: scroll1cycle_continued(); break;
		 	case 5: scroll1cycle_continuedRev(); break;
		 	case 6: fadeOut_continued(); break;
		 	case 7: moveOut_continued(); break;
		 	case 8: offPixel_continued(); break;
		 }
		break;


		case msgprint:
			print_currentPalette();
		break;

		#ifdef tstFPS
		case msgprintPX:
			bPrintPixels=!bPrintPixels;
		break;

		case msg_getLeds:
{
		NUM_LEDS_type i=0;
		while (Serial.available()) 
	 	{ 
	 		i++;
	 		if(i<NUM_LEDS)
	 		{
		 	 leds[i].r = Serial.read();
		 	 if(Serial.available())
		 	 leds[i].g = Serial.read();
		 	if(Serial.available())
		 	 leds[i].b = Serial.read();
		 	}
		 	else			Serial.read();
	 	}
	 	FastLED.show();
	 	bPause=true;
}
		break;

		
		#endif


		default:
		bNeedUpdDisplay=false;
		break;
	}
	if(bNeedUpdDisplay) SET_UPD_Display
}

unsigned long SerialControlStateExpare_t=0;
#endif



void checkSerial()
{
	#ifdef SerialControl
	 while (Serial.available()) 
	 { 

	 	 byte msg = Serial.read();
						#ifdef tst2
							Serial.println(msg);
						#endif
		if(millis()>SerialControlStateExpare_t)
		{
			mesageRecState=0;
		}
		SerialControlStateExpare_t=millis()+50;

		if(mesageRecState==0)
		{
			if( msg>=msgN_m &&  msg<= msgN_M ) //got msg type
			{
				mesageRecState=1;					//Serial.println("state:");Serial.println(mesageRecState);
				msgLast=msg;
			}
			//else msgLast=0;
		}
		else
		if(mesageRecState==1) //wait msg type confirm
		{
			if( msg==msgLast )
			{
				mesageRecState=2;					//Serial.println("state:");Serial.println(mesageRecState);
			}
			else 
			{
				if( msg>=msgN_m &&  msg<= msgN_M ) //got msg type
				{
					mesageRecState=1;				//Serial.println("state:");Serial.println(mesageRecState);
					msgLast=msg;
				}
				else
				{
					mesageRecState=0;
				}
			}
		}
		else
		{
			setValueFromMsg(msgLast,msg);
			mesageRecState=0;
		}
	 }
	#endif

	#ifdef SerialSelect
	  if (Serial.available() > 0) {
			effN_set(Serial.parseInt()); 			//Serial.println(effN);
			
			#ifdef tst
					Serial.println(effN);
			#endif
			while (Serial.available()) Serial.read(); // clear ser buff
		}
	#endif
}