
#ifdef SerialControl
//## SET_UPD_Display saveAfter2s();
	#define msgN_m			241
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
	#define msgN_M			253
		
	 	
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
			//change_mode(effN);
		 effN_set(value);
		break;
		case messageSpeed:
		 effSpeed=value;
		break;
		case messageLength:
		 effLength=value;
		break;
		case messageRGB:
		 effDisableChennel=value;
		break;
		case messageSpeedH:
		 // =value;
		break;
		case messageLengthH:
		  //=value;
		break;
		case messageBright:
		 FastLED.setBrightness( value ); FastLED.show();
		 //!! save tst_BRIGHTNESS=value;
		break;
		case messageSave:
		 save(value);
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
		  resetSetiings_and_change_mode();//!
		 else change_mode(effN);
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

		 	case 4: fadeOut_continued(); break;
		 	case 5: moveOut_continued(); break;
		 	case 6: offPixel_continued(); break;
		 }
		break;

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

	 	 byte msg = Serial.read();						//Serial.println(msg);
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
			effN_set(Serial.parseInt()); //Serial.println(effN);
			
			#ifdef tst
					Serial.println(effN);
			#endif
			while (Serial.available()) Serial.read(); // clear ser buff
		}
	#endif
}