#define saveFormat_currentVersion	62 //invalidate old version saves

#ifndef use_EEPROMex
	#include <EEPROM.h>
#else //! this part is not updated to more settings, so need fix if need to use
	#include <EEPROMex.h>
	// #ifdef tst
	// 	setMaxAllowedWrites(40);
	// #endif
#endif

const byte EEPROM_saved_flag_addr=0;

const byte save_addr_start = 4;

void saveAfter2s();


void save(byte N) //to slot N 0...9 // 10*19b
{
	byte effNum=bCurrentEff_IsRandom_AndNotSlotN?realEffN:effN;
							#ifdef tst
								Serial.print("save slot: "); Serial.print(N); Serial.print(" effN: "); Serial.println(effNum);
								if(effNum<11 || effNum==240 || N>9) 
								{
									Serial.println("no save ifdef tst");	return; //!opt del
								}
							#endif

	//if(effN<10) return; //0-9 is slots, bot not effects //this for update old written, normally it can't occur

	#ifndef use_EEPROMex		//https://arduino-esp8266.readthedocs.io/en/latest/libraries.html?highlight=eeprom%20
		EEPROM.begin(512); 		//https://arduino.stackexchange.com/questions/25945/how-to-read-and-write-eeprom-in-esp8266
		EEPROM.put(EEPROM_saved_flag_addr,saveFormat_currentVersion); //this update if different
							#ifdef tst2
								EEPROM.commit();
								Serial.print("save ver:");  Serial.print(saveFormat_currentVersion);
								Serial.print(" size: ");  Serial.print(sizeof(oostr));
								byte vers=0;	EEPROM.get(EEPROM_saved_flag_addr,vers);
								Serial.print(" check ver: "); Serial.println(vers);
							#endif
		EEPROM.put(save_addr_start+N*sizeof(SaveObj),oostr);
		EEPROM.commit();
		EEPROM.end();
	#else
		if(EEPROM.readInt(EEPROM_saved_flag_addr)!=saveFormat_currentVersion)	EEPROM.updateInt(EEPROM_saved_flag_addr, saveFormat_currentVersion);

		EEPROM.updateByte(save_addr_start+N*5, effNum);
		EEPROM.updateByte(save_addr_start+N*5+1, effSpeed);
		EEPROM.updateByte(save_addr_start+N*5+2, effLength);
		EEPROM.updateByte(save_addr_start+N*5+3, effRGB);
	#endif
}

void load(byte N)
{
																																//Serial.println("l");
		#ifdef tst
											Serial.print("load slot:"); Serial.print(N);			if(N>9)  {Serial.println("!! >9"); return; }
		#endif

	#ifndef use_EEPROMex //for ESP8266 ESP32
		EEPROM.begin(512);
		byte vers=0;	EEPROM.get(EEPROM_saved_flag_addr,vers);
											#ifdef tst
												Serial.print(" ver:"); Serial.println(vers); //##
												Serial.print(" NUM_LEDS:"); Serial.println(NUM_LEDS);Serial.println(gNUM_LEDS);
											#endif
		if(vers!=saveFormat_currentVersion) resetSetiings_and_change_slot();
		else
		{	
			EEPROM.get(save_addr_start+N*sizeof(SaveObj),oostr);

			if(effN<10) effN+=10;
			change_slot(effN);
		}
		EEPROM.end();
	#else
																									
		if(EEPROM.readInt(EEPROM_saved_flag_addr)!=saveFormat_currentVersion) resetSetiings_and_change_slot(); //check compatible saved before
		else
		{																							//Serial.println("read");
			effN = EEPROM.readByte(save_addr_start+N*5); //!!  change_slot(effN);  before other opt apply, but SET_UPD_Display after all
			if(effN<10) effN+=10; //return; //0-9 is slots, bot not effects //this for update old wrighten, normally it can't occur
			change_slot(effN);
			effSpeed=EEPROM.readByte(save_addr_start+N*5+1);
			effLength=EEPROM.readByte(save_addr_start+N*5+2);
			effRGB=EEPROM.readByte(save_addr_start+N*5+3);
		}
	#endif

	if(effLength==0) effLength=1;
	if(effLengthH==0) effLengthH=1;
	#if defined(SerialControl) && defined(NUM_LEDS_adjustable)
		NUM_LEDS_setup();
	#endif

	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;
	
	if(gBrightness>1) FastLED.setBrightness( gBrightness );  delay(20);//## fix why is it == 1

	//setBrightness_gBrightness //## fix is 1 or 0
	//SET_UPD_Display
}

bool bNeedSave=false;
unsigned long nextCanSave_t=0;
unsigned long nextCanChangeByIr=0; //!opt combine with other

void saveAfter2s() //for slot 0
{
	bNeedSave=true;
	nextCanSave_t=millis()+6000;
	#ifdef IRkeypad
	nextCanChangeByIr=millis()+300;
	#endif
}

void saveIfNeed()
{
	if(bNeedSave && millis()>nextCanSave_t)
	{
		save(0);
		bNeedSave=false;
	}
}

#ifdef IRkeypad
void save_load_preset(byte N)
{
	if(bIRcommandRepeated) return; //!! load

	if(!digitalRead(IR_mode_sw_p)) //##doc //mode switch at start toggle IRmode enable, after start switch  save\load mode
	{
		save(N);
	}
	else
	{
		load(N);
	}
}
#endif



#ifdef PWM_enabled
#if defined(use_ESP8266) || defined(use_ESP32)
void savePWM()
{
	int addr_start= save_addr_start+10*sizeof(SaveObj)+10;
	
	EEPROM.put(addr_start,oSaveObjDimmers);
	EEPROM.commit();
	EEPROM.end();
}
void loadPWM()
{
	int addr_start= save_addr_start+10*sizeof(SaveObj)+10;
	EEPROM.begin(512);
	EEPROM.get(addr_start,oSaveObjDimmers);
	EEPROM.end();
}
#endif
#endif