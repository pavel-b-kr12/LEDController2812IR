#define saveFormat_currentVersion	56 //invalidate old saves

#ifndef use_EEPROMex
	#include <EEPROM.h>
#else
	#include <EEPROMex.h>
	// #ifdef tst
	// 	setMaxAllowedWrites(40);
	// #endif
#endif

const byte EEPROM_saved_flag_addr=0;

const byte save_addr_start = 4;

void saveAfter2s();


void save(byte N) //to slot N 0...9
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

	#ifndef use_EEPROMex		//https://arduino.stackexchange.com/questions/25945/how-to-read-and-write-eeprom-in-esp8266
				//!! if(EEPROM.readInt(EEPROM_saved_flag_addr)!=saveFormat_currentVersion)	EEPROM.updateInt(EEPROM_saved_flag_addr, saveFormat_currentVersion);
		EEPROM.begin(512);
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

			#ifdef tst
			Serial.println(effSpeed);		Serial.println(effLength);		Serial.println(effRGB);
			#endif
}

void load(byte N)
{
		#ifdef tst
											Serial.print("load slot:"); Serial.print(N);			if(N>9)  {Serial.println("!! >9"); return; }
		#endif

	#ifndef use_EEPROMex
		EEPROM.begin(512);
		byte vers=0;	EEPROM.get(EEPROM_saved_flag_addr,vers);
											#ifdef tst
												Serial.print(" ver:"); Serial.println(vers); //##
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
		{
			effN = EEPROM.readByte(save_addr_start+N*5); //!!  change_slot(effN);  before other opt apply, but SET_UPD_Display after all
			if(effN<10) effN+=10; //return; //0-9 is slots, bot not effects //this for update old wrighten, normally it can't occur
			change_slot(effN);
			effSpeed=EEPROM.readByte(save_addr_start+N*5+1);
			effLength=EEPROM.readByte(save_addr_start+N*5+2);
			effRGB=EEPROM.readByte(save_addr_start+N*5+3);
		}
	#endif
		#ifdef tst
		Serial.print(" effN: "); Serial.println(effN);	Serial.println(effSpeed);	Serial.println(effLength);	Serial.println(effRGB);
		#endif

	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;
	
	//SET_UPD_Display
}

bool bNeedSave=false;
unsigned long nextCanSave_t=0;
unsigned long nextCanChangeByIr=0; //!opt combine with other

void saveAfter2s() //for slot 0
{
	 // if(bNeedSave && SaveSlot!=N && SaveSlot>0) save(SaveSlot);
	
	 // effSpeed_toSave=effSpeed;
	 // effLength_toSave=effLength;
	 // effN_toSave=effN;
	 // effRGB_toSave=effRGB;
	
	bNeedSave=true;
	nextCanSave_t=millis()+4000;
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