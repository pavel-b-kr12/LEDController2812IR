		//168: saveMem, NUM_LEDS 150
		//328: saveMem, NUM_LEDS 330
		//#if defined(_AVR_ATmega168__) //now work
//#define saveMem
		//#endif
		//#ifndef saveMem //so use this instead of
		//#if !defined(_AVR_ATmega168__)
		//#endif
//#define legacy_pinout

#define LEDpCustom				2 //this redefine any. del to use reference hardware schematics

#ifdef saveMem
	#define NUM_LEDS 			144 //60
	#define NUM_LEDS_type byte
#else
	#define NUM_LEDS 			60 //300  //1024
     //!   if NUM_LEDS>255
	#define NUM_LEDS_type 		byte //int //>255 NUM_LEDS  for(NUM_LEDS_type i=0; i<NUM_LEDS  //! fix random8(NUM_LEDS), effLength and other

	#define eff_setX
#endif

#define demo_enable

//#define tst
// tst2  //detailed print of functions call
//#define BlueFilter
#define tst_BRIGHTNESS 		77 // to dimm AND see good colors use lower voltage but not software brightness
#ifdef tst
	#define tst_POW_LIM	1000 //!? nw
#endif


 byte random_demo_sw_speed_td_m=2; //s  //!!
 byte random_demo_sw_speed_td_M=12;

//#define ESP
#ifdef ESP
#define FASTLED_ESP8266_RAW_PIN_ORDER
#endif

//#define keypad1602 //free D0..3, D11..13, A1..  http://wiki.keyestudio.com/Ks0256_keyestudio_LCD1602_Expansion_Shield
											//https://www.dfrobot.com/wiki/index.php/Arduino_LCD_KeyPad_Shield_(SKU:_DFR0009)
//#define IRkeypad	//3*7, ask me about support other types
//#define key5x		//all main options has button //!! nw
//#define key3x		//central btn switch mode (settings). Side btns are +-, i.e. effN, speed, length, gamma
#define SerialControl //USB protocol for external GUI //! TODO software for android
//v0.7 define only one of Serial
//#define SerialSelect //enter effect № in terminal
//#define LCD2004_i2c						//A4 A5

#define SerialSpeed		115200 //57600

//#define LEDp  								11 //6 if matrix keypad

//#define adj_pot								A0
#ifdef adj_pot
 #define adjType_LDR
#endif


#ifdef IRkeypad
	#define IR_mode_sw_p 					2 //! btn (IR save while press) //! LRD at start => toggle this with LDR
	#define IRp 							3
	#ifdef legacy_pinout
		#define IR_mode_sw_p 				A4 //! switch effN+- speed+  || length+- RGB+    VS switch 
		#define IRp 						6
	#endif
	
	#include "PinChangeInterrupt.h"
	#include "IRLremote.h"
	CNec IRLremote; // Choose the IR protocol of your remote
	//CPanasonic IRLremote;
	//CHashIR IRLremote;
	//#define IRLremote Sony12

	bool bIR_mode=false;
	
	int IRcommand_last=0;
#endif

#ifdef key3x
	#define LEDp  							11
	#define btnAdd							A1
	#define btnSelectMode					A2
	#define btnSub							A3
#endif

#ifdef key5x
	#define btnSpeedAdd 				2
	#define btnSpeedSub 				3 //!del, add EffSub
	#define btnEffNAdd 					4
	#define btnEffLengthAdd				5
	#define btnEffDisableChennel		7 //GRB RG GB BG R G B
		//A5 //смещение каналов R-G-B вдлину  
		//A6  //смещение hue вдлину 
		
/*
Выводы для варианта без IRkeypad:
6 - на ленту
 кнопки к GND:
2,3 - скорость
5 - ширина //TODO new eff
7 - выбор каналов цвета
4 - номер эффекта
A3 - сброс настроек эффектов

A0 - яркость, влияет при старте. резистор к GND

*/
#endif


//!  #ifdef keypad || 3btn
#define effN_OPTION					0 //min
#define effSpeed_OPTION				1
#define effLength_OPTION			2
#define effDisableChennel_OPTION	3
#define brightness_OPTION			4 //max
byte LCDoption_selected=effN_OPTION;
#ifdef keypad1602
	#define LEDp  					11
	#include <LiquidCrystal.h>
	#include "keypad1602.h"
	#endif
#ifdef LCD2004_i2c
	#include <Wire.h> 
	#include <LiquidCrystal_I2C.h>
	LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif


//this N related to button in USB app
#define effN_off 10 //clear, nodo()
#define effN_random_endless 248 //endless while press btn --
#define effN_random 249 
#define effN_animate_to_slot1 251
#define effN_animate_SW 252 

#ifdef demo_enable
#define effN_random_demo_animated_SW 250  //effN_animate_SW & effN_random_demo_SW
#define effN_predefined_show_seq 253
#define effN_random_demo_fast_SW 254 
#define effN_random_demo_SW 255 //del to disable

bool brandom_demo=false;
#endif
bool banimate=false;

//#define btnReset_p		A3 //resetSetiings_and_change_slot()

//#include "Arduino.h"                                          // FastLED library.
//#include "C:\Users\asd\Documents\Arduino\hardware\WAV\avr\cores\lgt8f\hooks.c"      //! wemos-Xi FastLED library.
#include "FastLED.h"
CRGB leds[NUM_LEDS];
//=========================================================================

byte effN=			0; // = eff SLOT at start
byte effSpeed=1; //EVERY_N_MILLISECONDS( 20 ) gHue+=effSpeed;
	byte effSpeed_last=1; //for animate eff
byte effLength=16;
	byte effLength_last=16;
byte effLength2=4;//!!
byte effDisableChennel=0; //1 => disable R, 2 => disable G ,  7 => fast cycle diferent //!! tst
#define effDisableChennel_M	17
byte effSpeedH=1; //!!
byte effLengthH=16;
CRGB gColorBg=CRGB::Black; //! gHueBG == 0 ? White   == 255 ? black

//=========================================================================
bool bCurrentEff_IsRandom_AndNotSlotN=false;
byte realEffN=10;

#ifndef saveMem
#endif

byte anim_d=50;
uint8_t gHue = 0;

//int il;
int i_eff=0;


// #ifdef adjType_LDR
 // byte ambientLight;
// #endif

void load(byte);
void checkSerial();
#include "anim.h"

//============================================= display LCD
//bool bNeed_display_upd=false;

void display_upd()
{
	//bNeed_display_upd=false;
	
	#ifdef keypad1602
		#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
 	//!! draw constant at setup
  EVERY_N_MILLISECONDS( 220 )
  {
	lcd.setCursor(0,0); lcd.print("eff"); 	lcd_print_selectedOption(effN_OPTION); //№
	lcd.setCursor(4,0); lcd.print("   ");
	lcd.setCursor(4,0); lcd.print(effN); 
	 
	lcd.setCursor(8,0); lcd.print("spd");	lcd_print_selectedOption(effSpeed_OPTION);
	lcd.setCursor(12,0); lcd.print("   ");
	lcd.setCursor(12,0); lcd.print(effSpeed);
	 
	lcd.setCursor(0,1); lcd.print("len");	lcd_print_selectedOption(effLength_OPTION);
	lcd.setCursor(4,1); lcd.print("   ");
	lcd.setCursor(4,1); lcd.print(effLength);
	
	lcd.setCursor(8,1); lcd.print("RGB");	lcd_print_selectedOption(effDisableChennel_OPTION);
	lcd.setCursor(12,1); lcd.print("   ");
	lcd.setCursor(12,1); lcd.print(effDisableChennel);
  }
	#endif

  #ifdef LCD2004_i2c
	#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
  
  EVERY_N_MILLISECONDS( 400 )
  {
   lcd.setCursor(0,0);
   lcd.print(effN);				lcd.print("  ");	lcd.setCursor(6,0); lcd.print("eff N"); 
   lcd.setCursor(0,1);
   lcd.print(effSpeed);			lcd.print("  ");  	lcd.setCursor(6,1); lcd.print(" speed");
   lcd.setCursor(0,2);
   lcd.print(effLength); 		lcd.print("  ");	lcd.setCursor(6,2);lcd.print("length"); 
   lcd.setCursor(0,3);
   lcd.print(effDisableChennel); lcd.print("  ");	lcd.setCursor(6,3); lcd.print(" RGBs");
   //lcd.print(anim_d);lcd.print("  ");
  }
  #endif
  
  #ifdef SerialSelect
  		#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
   #endif

  #ifdef SerialControl
	#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
  #endif
  
  #if defined(tst) || defined(SerialControl) //this refurn values to GUI
	Serial.print(effN); Serial.print(" ");
	Serial.print(effSpeed); Serial.print(" ");
	Serial.print(effLength); Serial.print(" ");
	Serial.print(effDisableChennel); Serial.print(" ");
	Serial.println();
  #endif
  
  #ifndef SET_UPD_Display
	#define SET_UPD_Display
  #endif
}
//=============================================================================================
#include <EEPROMex.h>
const int EEPROM_saved_flag_addr=0;
const byte effN_addr = 4; 
const byte effSpeed_addr = 5; 
const byte effLength_addr = 6; 
const byte effDisableChennel_addr = 7; 
//const byte preset0_addr = 8; 

// byte effN_toSave;
// byte effSpeed_toSave;
// byte effLength_toSave;
// byte effDisableChennel_toSave;

void saveAfter2s();

void resetSetiings_and_change_slot() //! or changeEff(effN)
{
	effN=10;
	effSpeed=1;
	effLength=16;
	effDisableChennel=0;
	change_slot(effN);
	SET_UPD_Display //saveAfter2s();

	// #ifdef demo_enable
	// brandom_demo=false;
	// #endif
	// banimate=false;
}

bool bIRcommandRepeated=false;

void save(byte N)
{
	byte effNum=bCurrentEff_IsRandom_AndNotSlotN?realEffN:effN;

	#ifdef tst
	Serial.print("save slot: "); Serial.print(N); Serial.print(" effN: ");Serial.println(effNum);
	if(effNum<11 || effNum==240 || N>9) 
	{
		Serial.println("no save");
		return; //!opt del
	}
	#endif

	//if(effN<10) return; //0-9 is slots, bot not effects //this for update old wrighten, normally it can't occur
	if(EEPROM.readInt(EEPROM_saved_flag_addr)!=55)	EEPROM.updateInt(EEPROM_saved_flag_addr, 55);
	
	EEPROM.updateByte(effN_addr+N*5, effNum);
	EEPROM.updateByte(effSpeed_addr+N*5, effSpeed);
	EEPROM.updateByte(effLength_addr+N*5, effLength);
	EEPROM.updateByte(effDisableChennel_addr+N*5, effDisableChennel);
	
		#ifdef tst
		Serial.println(effSpeed);
		Serial.println(effLength);
		Serial.println(effDisableChennel);
		#endif
}
void load(byte N)
{
		#ifdef tst
											Serial.print("load slot:"); Serial.print(N);
											if(N>9)  {Serial.println("!!!!! >9"); return; }
		#endif
	int saved=EEPROM.readInt(EEPROM_saved_flag_addr);
	if(saved!=55) resetSetiings_and_change_slot();
	else
	{
		effN = EEPROM.readByte(effN_addr+N*5); //!!  change_slot(effN);  before other opt apply, but SET_UPD_Display after all
		if(effN<10) effN+=10; //return; //0-9 is slots, bot not effects //this for update old wrighten, normally it can't occur
		change_slot(effN);
		effSpeed=EEPROM.readByte(effSpeed_addr+N*5);
		effLength=EEPROM.readByte(effLength_addr+N*5);
		effDisableChennel=EEPROM.readByte(effDisableChennel_addr+N*5);
	}
	
	#ifdef tst
	Serial.print(" effN: ");Serial.println(effN);
	Serial.println(effSpeed);
	Serial.println(effLength);
	Serial.println(effDisableChennel);
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
	 // effDisableChennel_toSave=effDisableChennel;
	
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
//=============================================================================================

void  effN_set(byte N)
{
	#ifdef tst2
	Serial.print("effN_set:"); Serial.println(N);
	#endif
				
	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;

	 if(N<=9)
	 {
	 	load(N); 
	 }
	 else 
	 {
	 	effN = N;
		change_slot(effN);
		SET_UPD_Display 
	}
	//saveAfter2s(); //this can only called by Serial, so not need auto save
}
void  effN_add()
{						
	effN++;
	#ifdef tst2
	Serial.print("effN_add:"); Serial.println(effN);
	#endif

	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;

	change_slot(effN);
	SET_UPD_Display saveAfter2s(); 
}
void  effN_sub()
{
	effN--;
	#ifdef tst2
	Serial.print("effN_sub:"); Serial.println(effN);
	#endif

	#ifdef demo_enable
	brandom_demo=false;
	#endif
	banimate=false;

	change_slot(effN);
	SET_UPD_Display saveAfter2s();
}

// #ifdef SerialControl
// void  effSpeed_set(byte value)
// {
// 	effSpeed = value;
// 	SET_UPD_Display
// 	saveAfter2s(); 
// }
// #endif
void  effSpeed_add()
{
      effSpeed+=(effSpeed<12)?1:4; 
	  //if(effSpeed>55) effSpeed=0;
	  if(effSpeed>100) effSpeed+=10;
	  SET_UPD_Display saveAfter2s();
}
void  effSpeed_sub()
{
      effSpeed-=(effSpeed<15)?1:4; 
	  //if(effSpeed>200) effSpeed=50;
	  if(effSpeed>100) effSpeed-=20;
	  SET_UPD_Display saveAfter2s();
}

// #ifdef SerialControl
// void  effLength_set(byte value)
// {
// 	effLength = value;
// 	SET_UPD_Display
// 	saveAfter2s(); 
// }
// #endif
void  effLength_add()
{
	if(effLength<10) effLength++;
	else
	if(effLength<50) effLength+=5;
	else effLength+=10;

	if(effLength==0) effLength=NUM_LEDS;

	  SET_UPD_Display saveAfter2s();
}
void  effLength_sub()
{
	if(effLength==1) effLength=NUM_LEDS;
	else
    if(effLength<10) effLength--;
	else
	if(effLength<50) effLength-=5;
	else effLength-=20;
	  SET_UPD_Display saveAfter2s();
}
	  
void  effDisableChennel_add()
{
		effDisableChennel++;
		if(effDisableChennel>effDisableChennel_M) effDisableChennel=0;
		SET_UPD_Display saveAfter2s();
}

//--------- for keypad, 3btn
void LCDoption_selected_add()
{
	LCDoption_selected++;
	//#define LCDoption_selected_M
	//if(LCDoption_selected>LCDoption_selected_M)LCDoption_selected=0;
	SET_UPD_Display
}
void switch_LCDoption_selected_value_add()
{
		 switch(LCDoption_selected)
		 {
			default: LCDoption_selected=0; //min
			case effN_OPTION:
			 effN_add();
			break;
			
			case effSpeed_OPTION:
			 effSpeed_add();
			break;		
			
			case effLength_OPTION:
			 effLength_add();
			break;	
			
			case effDisableChennel_OPTION:
			 effDisableChennel_add();
			break;
			
			case brightness_OPTION: //!
				//FastLED.setBrightness( tst_BRIGHTNESS ); //!! save BRIGHTNESS
			break;
		 }
}

void switch_LCDoption_selected_value_sub()
{
	#ifdef tst2
	Serial.print("switch_LCDoption_selected:"); Serial.println(LCDoption_selected);
	#endif

     switch(LCDoption_selected)
		 {
			case effN_OPTION:
			 effN_sub();
			break;
			
			case effSpeed_OPTION:
			 effSpeed_sub();
			break;		
			
			case effLength_OPTION:
			 effLength_sub();
			break;	
			
			 case effDisableChennel_OPTION:
					//ambientLight_map(); FastLED.show(); //!
			 // effDisableChennel_sub();
			 break;
			 
			case brightness_OPTION:
			default:
			 LCDoption_selected=brightness_OPTION; //max

				//FastLED.setBrightness( tst_BRIGHTNESS ); //! save BRIGHTNESS
			break;
		 }
}

//=========================================================================
void setup()
{
#ifdef LEDpCustom
	#define LEDp	LEDpCustom
#endif

#ifdef ESP
  FastLED.addLeds<WS2812B, 14>(leds, NUM_LEDS);//D5 6 7 8
#else
  //Nano   9 7 5 3 *2* 4 6 8 10
  FastLED.addLeds<WS2812B, LEDp, GRB>(leds, NUM_LEDS);
#endif
FastLED.clear();
FastLED.show();

#ifdef keypad1602
 pinMode(A0, INPUT_PULLUP);	//for situation of shield not connected (if keypad1602 defined but not connected something run effSub)
 lcd.begin(16, 2);
#endif

//---------------------------------------------------------
#ifdef adj_pot
 pinMode(adj_pot,INPUT_PULLUP); delay(2);
#ifdef adjType_LDR
 FastLED.setBrightness(ambientLight_map()); FastLED.show();	//! every n ms
#else
 if(analogRead(adj_pot)<900) FastLED.setBrightness( map(analogRead(adj_pot),0,1023, 22, 255) ); //! every n ms
#endif
#endif

#ifdef tst_BRIGHTNESS
	FastLED.setBrightness( tst_BRIGHTNESS );
#endif
//---------------------------------------------------------

#if defined(tst) || defined(SerialSelect) || defined(SerialControl)
Serial.begin(SerialSpeed);
#include "version.h"
#endif

  #ifdef tst_POW_LIM
  FastLED.setMaxPowerInVoltsAndMilliamps(5,tst_POW_LIM); //! tst
  #endif
  
#ifdef tst
	//Serial.println(F("test"));
	#ifdef LDR
	
	#endif
#endif

#ifdef IRkeypad
pinMode(IR_mode_sw_p, INPUT_PULLUP);
#endif

#ifdef key3x
 	pinMode(btnAdd, INPUT_PULLUP);
	pinMode(btnSub, INPUT_PULLUP);
	pinMode(btnSelectMode, INPUT_PULLUP);
#endif

#ifdef key5x
	pinMode(btnSpeedAdd, INPUT_PULLUP);
	pinMode(btnSpeedSub, INPUT_PULLUP);
	pinMode(btnEffNAdd, INPUT_PULLUP);
	pinMode(btnEffLengthAdd, INPUT_PULLUP);
	pinMode(btnEffDisableChennel, INPUT_PULLUP);
	
	//pinMode(btnReset_p, INPUT_PULLUP); //!
#endif

#ifdef LCD2004_i2c
  lcd.init();	  lcd.init(); //!tst if only one init is enough
  // Print a message to the LCD.
  lcd.backlight();
  // lcd.setCursor(3,0);
  // lcd.setCursor(2,1);
  // lcd.setCursor(0,2);
  // lcd.print(""); 
  // lcd.setCursor(2,3);
#endif

delay(1);

//if(!digitalRead(btnReset_p))	resetSetiings_and_change_slot(); else //!
load(effN);

#ifdef IRkeypad
if(!digitalRead(IR_mode_sw_p))
{
	bIR_mode=true;
  
	#ifdef tst
		Serial.println(F("IR save mode"));
		//pinMode(LED_BUILTIN, OUTPUT);
	#endif

	if (!IRLremote.begin(IRp)) 
	{
		#ifdef tst
		Serial.println(F("invalid IR pin"));
		#endif
	}
}
#endif

  #ifdef tst
  leds[0] = CRGB::White;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Green;
  leds[3] = CRGB::Blue;
  FastLED.show();
  delay(300);
  FastLED.clear();
  FastLED.show();
  #endif
}
 
//=============================================================================================
#include "SerialControl.h"

void loop()
{
#if defined(SerialSelect) || defined(SerialControl)
	checkSerial();
#endif
	
#ifdef IRkeypad
if(bIR_mode)
{
	if (!IRLremote.receiving()) {  // Check if we are currently receiving data
		LED_anim();
		saveIfNeed();
	}
 
  if (IRLremote.available()) // Check if new IR protocol data is available
  {
	  int IRcommand=IRLremote.read().command; 
	  	#ifdef tst
			digitalWrite(LED_BUILTIN, HIGH);
			Serial.println(IRcommand, HEX);
			digitalWrite(LED_BUILTIN, LOW);
				//auto data = IRLremote.read();
			    // Serial.print(F("Address: 0x"));
				// Serial.println(data.address, HEX);
				// Serial.print(F("IRcommand: 0x"));
				// Serial.println(data.command, HEX);
				// Serial.println();
		#endif
/*  IR 3*7 key
45 46 47
44 40 43
7 15 9
16 19 D
c 18 5e
8 1c 5a
42 52 4a 
*/
	  
	  if(IRcommand==0x00) //same as  (data.address==0xFF00)
	  {
		  bIRcommandRepeated= true;
		  IRcommand = IRcommand_last; //##
	  }
	  else
	  {
		  bIRcommandRepeated= (IRcommand == IRcommand_last);
		  
		  if(!bIRcommandRepeated)
		  {
			IRcommand_last = IRcommand;
			  
			switch(IRcommand)
				{
				  //-------------- 1 2 3
				  case 0xC:			save_load_preset(1);				  break;
				  case 0x18:		save_load_preset(2);				  break;
				  case 0x5E:		save_load_preset(3);				  break;
				  //-------------- 4 5 6
				  case 0x8:			save_load_preset(4);				  break;
				  case 0x1C:		save_load_preset(5);				  break;
				  case 0x5A:		save_load_preset(6);				  break;
				  //-------------- 7 8 9
				  case 0x42:		save_load_preset(7);				  break;
				  case 0x52:		save_load_preset(8);				  break;
				  case 0x4A:		save_load_preset(9);				  break;
				  default: break;
				  }
		  }
	  }
	#ifdef tst2
Serial.print("IRcommand:"); Serial.println(IRcommand);
	#endif
	  					
    switch(IRcommand)
    {
	  //-------------- CH- CH CH+
      case 0x45:		if(millis()<nextCanChangeByIr) break;
	  effLength_sub();
      break;

      case 0x46:		if(millis()<nextCanChangeByIr) break;
	  effDisableChennel_add();
      break;
	  
      case 0x47:		if(millis()<nextCanChangeByIr) break;
	  effLength_add();
      break;
	  //-------------- |<< >>| >||
      case 0x44:		if(millis()<nextCanChangeByIr) break;
	  effN_sub();
      break;

      case 0x40:		if(millis()<nextCanChangeByIr) break;
		effN_add();
      break;
	  
      case 0x43:		if(millis()<nextCanChangeByIr) break;
	  bPause=!bPause;//pause anim
      break;
	  //-------------- - + EQ
      case 0x7:			if(millis()<nextCanChangeByIr) break;
	  effSpeed_sub();
      break;
	  
      case 0x15:		if(millis()<nextCanChangeByIr) break;
	  effSpeed_add();
      break;
	  
      case 0x9:
											
	  
      break;
	  //-------------- 0 100 200
      case 0x16:
	  change_slot(); //clear off
	  saveAfter2s(); SET_UPD_Display
      break;
	  
      case 0x19:
		resetSetiings_and_change_slot();
      break;
	  
      case 0xD:
										//!! autopaly 
      break;
	  
      default:
      break;
    }
  }
}
else
{
	LED_anim();
}
#else
	LED_anim();
	saveIfNeed(); //^
#endif
	
#ifdef keypad1602
EVERY_N_MILLISECONDS( 220 )
{
 switch (read_LCD_buttons())
 {
	case btnRIGHT:
     {
		effN_add();
     break;
     }
	case btnLEFT:
     {
		effN_sub();						
     break;
     }
	case btnUP:
     {
		switch_LCDoption_selected_value_add();
     break;
     }
	case btnDOWN:
     {
		 switch_LCDoption_selected_value_sub();
     break;
     }
	case btnSELECT:
     {
		 LCDoption_selected_add();
		 break;
     }
     // case btnNONE:
     // {
     // 
     // break;
     // }
 }
}
#else
 
  EVERY_N_MILLISECONDS( 180 )
  {
 #ifdef key3x
	if(!digitalRead(btnAdd))
	{
		switch_LCDoption_selected_value_add();
	}
    else
	if(!digitalRead(btnSub))
	{
		switch_LCDoption_selected_value_sub();
	}
    else
	if(!digitalRead(btnSelectMode))
	{ //!!! also flash
		LCDoption_selected_add();
	}

 #elif defined (key5x)
    if(!digitalRead(btnSpeedAdd))
    {
      //anim_d-=5;//nw
		effSpeed_add();					
    }
    else
    if(!digitalRead(btnSpeedSub)) 
    {
      //anim_d+=5;
		effSpeed_sub();					
    }
    else
    if(!digitalRead(btnEffNAdd))
	{
		effN_add();						
	}
    else
    if(!digitalRead(btnEffLengthAdd))
    {
		effLength_add();				
    }
	else
    if(!digitalRead(btnEffDisableChennel))
    {
		effDisableChennel_add();		
    }
	#endif
  }
 
#endif

	
//============================================= display LCD
  //#if defined (keypad1602) || defined (LCD2004_i2c) || defined (SerialControl)  || defined (tst) 
//	if(bNeed_display_upd) display_upd();
 // #endif
//=============================================
 // il++;
}
