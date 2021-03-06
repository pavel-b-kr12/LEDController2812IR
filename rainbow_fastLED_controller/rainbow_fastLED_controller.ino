//============================================ global options that has higher priority and redefines of other definitions
#define SerialSpeed_redef 921600 //921600 for CP2102,     1000000 for CH340
//#define debugSerial //to disable other data send and allow Serial.print();Serial.print(" ");Serial.println();
//#define debugSerialMemoryHeap

//#define REVERSE_STRIPE //reverse array, show, reverse back (1ms @ 400LEDs). Also effects that show itself have to use FastLED_show_DIRECTION instead of FastLED.show 
//! have to be deleted after FastLED REVERSE functions will be available. 

//#define LEDp_redef				0
//#define startLoadEffN_redef 255//222//204// CubeTest	CubeCornersLight	mus_arduinoFFT	effN_test_RF setColors_fill	255=effN_random_demo_SW 254=demo fast

//============================================ global options, that can be redefined below in "hadrware kits" section
#define LEDchipType	WS2812B // WS2811
//#define tst_POW_LIM	1000

//#define textMATRIX_overlay //add text after anim_f. Use slot text_overlay_switch  bTextOverlay=!bTextOverlay   default = true 
//#define textMATRIX_overlay_substractTetAfterShow //!! 
//#define doubleDrawBuffers_AddPrevEff  //!!TODO draw to leds, copy leds to ledsTmp,  overlay add to leds, show leds, copy ledsTmp to leds
//#define doubleDrawBuffers_AddText		//!!

//#define BlueFilter

//#define offEffChangeAfter2min //### disable checkSerial(); IR, in, wifi  //e.g. for stability and sequrity
//#define off_change_slot_After2min //e.g. for stability and sequrity
			//#define offWiFiAfter2min //# test
//#define mode_switch_enabled // bLEDsMirror, ...
//#define use_ESP_WiFioff

			// #define PWM_pin0	 //don't forget disable LEDs_RENDER if uses same pins also PinSequencer pins
			// #define PWM_pin1
//#define PinSequencer_enabled //see defined pins at .h //##
//#define PinSequencer_pin0	 //don't forget disable LEDs_RENDER if uses same pins also PinSequencer pins
//#define PinSequencer_pin1


//#define saveMem //use on 168 and 328 to turn off some features. //!tst (may be outdated)
//#define legacy_pinout

// don't forget to change pins or disdable "#define LEDs_RENDER"  if not used, so it not affect serial or other stuff for different dev-boards


//#define LEDs_RENDER //show to connected LEDs stripe connected to this MCU 
//#define WiFi_SEND //send leds array to connected WiFis, also enables #define use_ESP
//#define WiFi_ControlHTMLpage
//#define SerialControl
//#define tstFPS //if defined, by  default: send only FPS, bPrintPixels=false; , You can enable Print in GUI
	//#define tst //debug.    use together with debugSerial to off send leds data
	//#define tst2  //detailed print of functions call
//#define SerialSpeed		921600 //1000000 921600 // 921600 is max for esp32 cp2102 //1M=250FPS@60LED //115200 =25FPS@60LED //57600
//#define sound_p					39//36 //A0 //esp32: 36==GPIO36=="VP"==14   39==GPIO39=="VN"


//@@ #define eff_setX
//#define effN_test_RF 244 //effect to show packet loss //also this number is in switch_slot.h


//============================================ hardware sets, choose one:
//#define ESP8266_SHOW
//#define ESP8266_SHOW_60x20m
//-------------------- ESP32  in arduino IDE select DOIT ESP32 devkit
//#define ESP32_SHOW_USBWiFi  
//#define ESP32_SHOW_USB
//#define ESP32_SHOW_WiFi
//#define ESP32_HTML_NO_RENDER //test on PC, control from USB app and WiFi HTML page
//------- ----------------------- test
//#define ESP32_SHOW_USB_test
									//#define ESP8266_SHOW_USB_test
//#define ESP8266_dimmer_test
//------- ----------------------- w keys and kits
//#define hadrware_3btn_ESP
//#define hadrware_3btn_nano
//#define hadrware_1btn_1pot_nano
//#define hadrware_nano328_demo
//#define ESP8266_DemoReel101_test	
//#define wandKit_debug_mega328

//#define Cube4MCU // ESP32 server ( see code of render nodes in render_WiFi folder )
//#define Cube3MCU_w_also_serverDraw //it also #define Cube4MCU  ,TODO probably have to split out. 
//#define Cube3MCU_12p

//#define ClothSuit_mirror


//------- ----------------------- matrix
//#define ESP8266_SHOW_MATRIX
//#define ESP8266_text8x32_test //adafruit GFX
//#define ESP8266_text_RU_8x32_MATRIX //font in array .h
#define ESP8266_text_RU_15x16_MATRIX //font in array .h
//------- -----------------------


#define FASTLED_ESP8266_RAW_PIN_ORDER //ifdef D2 on ESP == 4, othervice D2 is 2   //! may be better move to hardware kits



#define switch_slot_FILE_H "switch_slot.h" //contains slots №, slot mean effect + settings
//#define switch_slot_FILE_H "switch_slot_mega328.h"
//to use only this eff without switch_slot.h file:
//#define only1eff	case 214:anim_f=kit_wand;	effSpeed=187;	effLength=128;		effFade=126;   	indexOrBits=141; break;
//#define only1eff	case 214:anim_f=kit_MK; break;

//============================================ hadrware kits

#ifdef hadrware_3btn_nano
	#define SerialControl //thease 3 option eat 7% of atm328 program storage space
	#define SerialSpeed		1000000
	#define tstFPS
	
	//#define sound_p					A2 //25% of program and 25% of mem of atm328
	
	#define LEDs_RENDER
	#define gNUM_LEDS		256 //120
	#define NUM_LEDS_type	byte
	#define LEDp					4
	
	//#define key3x
	
			#define tst_BRIGHTNESS		66 
	#define default_effN_Random //!! nwp start USB app without this
	#define startLoadEffN 216
	
	//#define showSelectedOptionOnStipe //useful if no LCD to view what option is selected now
	//#define save_load_enable
#elif defined(hadrware_1btn_1pot_nano)
	#define SerialControl //thease 3 option eat 7% of atm328 program storage space
	#define SerialSpeed		1000000
	//#define tstFPS
	
	//#define sound_p					A2 //25% of program and 25% of mem of atm328
	
	#define LEDs_RENDER
	#define gNUM_LEDS		120
	#define NUM_LEDS_type	byte
	#define LEDp					2
	
	#define key1d1a
	#ifdef  key1d1a
		#define potAdd							A1
		#define btnSelectMode_p					3
		//#define btnSub							//# //12
	#endif
	
			#define tst_BRIGHTNESS		22 
	#define default_effN_Random
#elif defined(hadrware_nano328_demo)
	#undef switch_slot_FILE_H
	//#define switch_slot_FILE_H "switch_slot_old_Nano328.h"
	#define switch_slot_FILE_H "switch_slot_mega328.h"
	
	#define SerialControl //thease 3 option eat 7% of atm328 program storage space
	#define SerialSpeed		1000000
	#define tstFPS
	
	//#define sound_p					A2 //25% of program and 25% of mem of atm328
	
	#define LEDs_RENDER
	#define gNUM_LEDS		150
	#define NUM_LEDS_type	byte
	#define LEDp					6
	
			#define tst_BRIGHTNESS		122 
	#define default_effN_Random
	byte random_demo_sw_speed_td_m=3; //s
	byte random_demo_sw_speed_td_M=15;
	#define startLoadEffN  255
	
#elif hadrware_3btn_ESP
	#define use_ESP8266
	
	#define SerialControl //USB protocol for external GUI
	#define SerialSpeed		1000000//500000 //1M=250FPS@60LED //115200 =25FPS@60LED //57600
	#define tstFPS

		
	#define gNUM_LEDS 			300 //264
	#define NUM_LEDS_type 		uint16_t
	//#define eff_setX

	//#define NUM_LEDS_adjustable //now only in SerialControl // 1.6kb prog mem

	#define showSelectedOptionOnStipe //useful if no LCD to view what option is selected now

	#define save_load_enable //to EEPROM

	#define demo_enable
	#define default_effN_Random // switch default to randomSet() or FastLED.clear();

	#define LEDp_redef				2

	#define tst_BRIGHTNESS 		155 // to dimm AND see good colors use lower voltage but not software brightness
		//#define tst_POW_LIM	1000

	 byte random_demo_sw_speed_td_m=3; //s
	 byte random_demo_sw_speed_td_M=15;

	#define key3x		//central btn switch mode (settings). Side btns are +-, i.e. effN, speed, length, gamma
	
#elif defined(ESP32_HTML_NO_RENDER)
	#define use_ESP32
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	#define SerialSpeed		921600
	#define sound_p					39
// ADC2 pins cannot be used when Wi-Fi is used. So, if you’re using Wi-Fi and you’re having trouble getting the value from an ADC2 GPIO, you may consider using an ADC1 GPIO

	#define tstFPS
	//#define LEDs_RENDER
	#define gNUM_LEDS 			144// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	//#define save_load_enable
	//#define demo_enable
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=15;
	//#define LEDp							4
	#define gDelayMore	12	//if(bPrintPixels) anim_next_t+=gDelayMore; //adds to delay to avoid Serial send pixel data bug
							//otherwice it freeze on Serial overflow, I think. (start sending garbage after some time, then freeze)
							// have to be ~8 or bigger if not LEDs_RENDER and many pixels
#elif defined(ESP32_USBtest_NO_Render)
	#define use_ESP32
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	#define SerialSpeed		921600
	#define sound_p					39
	#define tstFPS
	//#define LEDs_RENDER
	#define gNUM_LEDS 			16*16// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	//#define save_load_enable
	#define demo_enable
	//#define LEDp					4 //36 nw
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=15;
						#define tst_BRIGHTNESS		25
#elif defined(ESP32_SHOW_USBWiFi)
	#define use_ESP32
	#define WiFi_ControlHTMLpage
	#define enableUDP

	#define SerialControl
	#define SerialSpeed		921600
	#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			16*16// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	#define demo_enable
	#define LEDp					4 //36 nw  //12-19,0,2,3,4,5,21,22,23  https://github.com/hpwit/fastled-esp32-16PINS   @ avoids flickering
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=15;
						#define tst_BRIGHTNESS		26

#elif defined(ESP32_SHOW_USB)
	#define use_ESP32
	//#define WiFi_ControlHTMLpage
	#define use_ESP_WiFioff
	#define SerialControl
	#define SerialSpeed		921600
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			800// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	#define demo_enable
	//#define LEDp					6 //36 nw
	#define MULTIPLE_PINS2 //4 5 13 14 (GPIO, marks on board)
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=15;
	#define default_effN_Random
						#define tst_BRIGHTNESS		88
	#define gDelayMore	25
#elif defined(ESP32_SHOW_USB_test)
	#define startLoadEffN 215
	#define use_ESP32
	//#define WiFi_ControlHTMLpage
	#define use_ESP_WiFioff
	#define SerialControl
	#define SerialSpeed		921600
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			120// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	//#define save_load_enable
	//#define demo_enable
	#define LEDp					4 //36 nw
	//#define MULTIPLE_PINS2 //4 5 13 14 (GPIO, marks on board)
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
	//#define default_effN_Random
						#define tst_BRIGHTNESS		25
	#define gDelayMore	5
#elif defined(ESP8266_SHOW_USB_test)
	#define startLoadEffN  68 //212//215 //63
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	//#define use_ESP_WiFioff
	#define SerialControl
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		144	//105// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	//#define save_load_enable
	//#define demo_enable
	#define LEDp					4 //36 nw
	//#define MULTIPLE_PINS2 //4 5 13 14 (GPIO, marks on board)
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
	//#define default_effN_Random
						#define tst_BRIGHTNESS		25
	#define gDelayMore	5
#elif defined(ESP8266_DemoReel101_test)
	#define startLoadEffN  214
	#define use_ESP8266
	//#define WiFi_ControlHTMLpage
	#define use_ESP_WiFioff
	#define SerialControl
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		180	//105// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		byte // uint16_t
	//#define save_load_enable
	//#define demo_enable
	#define LEDp					4 //36 nw
	//#define MULTIPLE_PINS2 //4 5 13 14 (GPIO, marks on board)
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
	//#define default_effN_Random
						#define tst_BRIGHTNESS		25
	//#define gDelayMore	5
#elif defined(wandKit_debug_mega328)
	#define startLoadEffN  214
	#define only1eff
	//#define off_change_slot_After2min //!!
	//#define use_ESP8266
	
	#define	btn0	9	
	#define	btn1	10	
	#define	btn2	11	
	
	//#define WiFi_ControlHTMLpage
	//#define use_ESP_WiFioff
	#define SerialControl
	#define SerialSpeed		1000000 //1000000
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		144//180	//105// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		byte // uint16_t
	//#define save_load_enable
	//#define demo_enable
	#define LEDp					4 //36 nw
	//#define MULTIPLE_PINS2 //4 5 13 14 (GPIO, marks on board)
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
	//#define default_effN_Random
						#define tst_BRIGHTNESS		255
	//#define gDelayMore	5
	

	// #define key3x
	// #ifdef  key3x
		 // #define btnAdd						7 //14=D5 on NODEMCU and D1 mini
		 // #define btnSelectMode_p			8 //12=D6
		 // #define btnSub						9 //13=D7
	// #endif
#elif defined(ESP8266_dimmer_test)
	#define PWM_enabled //see defined pins at .h //!
							//#define save_load_enable
				
	#define startLoadEffN  239 //235!//235//239//dimmer
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	#define SerialControl
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		144
	#define NUM_LEDS_type 		byte
	#define LEDp					4
						#define tst_BRIGHTNESS		33
	#define gDelayMore	5	

	//#define PWM_pin0	 //don't forget disable LEDs_RENDER if uses same pins also PinSequencer pins
	//#define PWM_pin1	
	bool bPWM_Dimmer=true; //enable output, toggled at select effect "PWM_Dimmer"
#elif defined(ESP8266_text8x32_test)
	#define mw 32
	#define mh 8
	#define NUMMATRIX (mw*mh)
	
	#define startLoadEffN  221
	#define use_ESP8266
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		NUMMATRIX
	#define NUM_LEDS_type 		uint16_t
	#define LEDp					4
						#define tst_BRIGHTNESS		33
	#define gDelayMore	5	

#elif defined(ESP8266_text_RU_8x32_MATRIX)
	#define MATRIXfonth
							//#define textMATRIX_overlay
	#define WIDTH	32
	#define HEIGHT	8
	#define bMatrixZigZag 1         // тип матрицы: 0 - зигзаг, 1 - параллельная
	#define CONNECTION_ANGLE 0//0//1    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
	#define STRIP_DIRECTION  1//1//3//(0 for USB view. TODO use STRIP_DIRECTION in USB app )    // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
	/* //for USB view w matrix_HORIZONTAL=true;
	#define CONNECTION_ANGLE 1 
	#define STRIP_DIRECTION  0
	*/
	
	#define startLoadEffN  222
	#define use_ESP8266
		#define use_ESP_WiFioff
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		WIDTH*HEIGHT
	#define NUM_LEDS_type 		uint16_t
	#define LEDp					4
						#define tst_BRIGHTNESS		33
	#define gDelayMore	5	

#elif defined(ESP8266_text_RU_15x16_MATRIX)
	#define MATRIXfonth
							//#define textMATRIX_overlay
	#define WIDTH	16
	#define HEIGHT	15
	#define bMatrixZigZag 1         // тип матрицы: 0 - зигзаг, 1 - параллельная
	#define CONNECTION_ANGLE 0//0//1    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
	#define STRIP_DIRECTION  1//1//3//(0 for USB view. TODO use STRIP_DIRECTION in USB app )    // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
	/* //for USB view w matrix_HORIZONTAL=true;
	#define CONNECTION_ANGLE 1 
	#define STRIP_DIRECTION  0
	*/
	
	#define startLoadEffN  222
	#define use_ESP8266
		#define use_ESP_WiFioff
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 		WIDTH*HEIGHT
	#define NUM_LEDS_type 		uint16_t
	#define LEDp					4
						#define tst_BRIGHTNESS		122
	#define gDelayMore	5	

	#define demo_enable
	byte random_demo_sw_speed_td_m=3;
	byte random_demo_sw_speed_td_M=15;
#elif defined(ESP32_SHOW_WiFi)
	#define use_ESP32

	#define WiFi_ControlHTMLpage
	#define enableUDP //?????????? HTML nw without UPD

	//#define sound_p					39
	#define LEDs_RENDER
	#define gNUM_LEDS 			800// 30 60 120 144 150 180 240 300 145*12
	
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	//#define demo_enable //?????????? HTML nw without
	//#define LEDp					4 //36 nw
	#define MULTIPLE_PINS4
	byte random_demo_sw_speed_td_m=4; //s  //!!
	byte random_demo_sw_speed_td_M=22;
						#define tst_BRIGHTNESS		255
	#define gDelayMore	10
	
#elif defined(ESP8266_SHOW)
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	#define SerialControl
	#define SerialSpeed		921600	//1000000 or 921600 for cp2102
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			300// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	#define demo_enable
	#define LEDp					4
	byte random_demo_sw_speed_td_m=5; //s  //!!
	byte random_demo_sw_speed_td_M=25;
						#define tst_BRIGHTNESS		200	
#elif defined(ClothSuit_mirror)
	#define startLoadEffN	230
	#define use_ESP8266
	//#define WiFi_ControlHTMLpage
	#define SerialControl
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			2400/3/2 //=400
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	//#define save_load_enable
	#define demo_enable
	#define LEDp					4
	byte random_demo_sw_speed_td_m=4; //s  //!!
	byte random_demo_sw_speed_td_M=22;
						#define tst_BRIGHTNESS		22
#elif defined(ESP8266_SHOW_60x20m)
	#define startLoadEffN 151 //setColors_fill
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	//#define WiFi_ControlHTMLpage_switch_p	5 //5=D1
	#define SerialControl
	#define SerialSpeed		1000000	//or 921600 for cp2102
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			60*20// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	//#define demo_enable
	#define LEDp					4
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
#elif defined(ESP8266_SHOW_60xBtn)
	#define startLoadEffN 151 //setColors_fill
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	#define WiFi_ControlHTMLpage_switch_p	5 //5=D1
	#define SerialControl
	#define SerialSpeed		1000000	//or 921600 for cp2102
	//#define sound_p					39
	#define tstFPS
	#define LEDs_RENDER
	#define gNUM_LEDS 			60// 30 60 120 144 150 180 240 300 145*12
	#define NUM_LEDS_type 		uint16_t //byte uint16_t
	#define save_load_enable
	//#define demo_enable
	#define LEDp					4
	//byte random_demo_sw_speed_td_m=2; //s  //!!
	//byte random_demo_sw_speed_td_M=15;
	#define key3x
	#ifdef  key3x
		#define btnAdd						14 //14=D5 on NODEMCU and D1 mini
		#define btnSelectMode_p				12 //12=D6
		#define btnSub						13 //13=D7
	#endif
	#define btnAct							15 //15=D8
						#define tst_BRIGHTNESS		88
#elif defined(ESP8266_SHOW_MATRIX)
	#define use_ESP8266
	#define WiFi_ControlHTMLpage
	#define SerialControl
	#define SerialSpeed		921600	//1000000 or 921600 for cp2102
	//#define sound_p					39
	#define tstFPS
		#define LEDs_RENDER
		#define gDelayMore	12
	#define gNUM_LEDS 			16*16// 30 60 120 144 150 180 240 300 145*12
	#define MATRIX_ROWS			16
	#define bMatrixZigZag //TODO

	#define NUM_LEDS_type 		uint16_t //byte uint16_t
		#define save_load_enable
	#define demo_enable
	#define LEDp					4
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=15;
						#define tst_BRIGHTNESS		28
	#define remap_LEDs //allow toggle and use bMap_type to map line of pixels to zig-zag, spiral, topology
#elif defined(Cube4MCU)
	#define use_ESP32
#define WiFi_SEND
#define WiFi_ControlHTMLpage
#define WiFi_ControlHTMLpage_switch_p	32	//GPIO32==IO32==Touch9			//touchRead(T9); th=~30

	//#define key3x
	#ifdef  key3x
		#define btnAdd							25
		#define btnSelectMode_p					27
		#define btnSub							//# //12
	#endif

				//#define SerialControl
				//#define tstFPS
	#define SerialSpeed		921600

	//#define sound_p					39

				// #define CubeXp	2
				// #define CubeYp	3
				// #define CubeZp	4

	#define NUM_LEDS_edge 		145//12//145//24//145
	#define NUM_LEDS_mcu 		NUM_LEDS_edge*3
	#define NUM_LEDSall 		NUM_LEDS_mcu*4
	#define gNUM_LEDS			NUM_LEDSall

	#define NUM_LEDS_type 		uint16_t
//#define save_load_enable
#define demo_enable
				//#define BlueFilter
				//#define tst_BRIGHTNESS 		33
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=12;

	//#define NUM_LEDS_adjustable //!del

	//#define server_render
	#ifdef server_render //server as 4th corner
		#define CubeXp		13 //36 nw
		#define CubeYp		12
		#define CubeZp		14
		#define LEDs_RENDER
	#endif

#elif defined(Cube3MCU_w_also_serverDraw)
	#define Cube4MCU
	#define use_ESP32
#define WiFi_SEND
#define WiFi_ControlHTMLpage
#define WiFi_ControlHTMLpage_switch_p	32	//GPIO32==IO32==Touch9			//touchRead(T9); th=~30

	//#define key3x
	// #ifdef  key3x
		// #define btnAdd							25
		// #define btnSelectMode_p					27
		// #define btnSub							//# //12
	// #endif

				//#define SerialControl
				//#define tstFPS
	#define SerialSpeed		921600

	//#define sound_p					39

				// #define CubeXp	2
				// #define CubeYp	3
				// #define CubeZp	4

	#define NUM_LEDS_edge 		145//12//145//24//145
	#define NUM_LEDS_mcu 		NUM_LEDS_edge*3
	#define NUM_LEDSall 		NUM_LEDS_mcu*4
	#define gNUM_LEDS			NUM_LEDSall

	#define NUM_LEDS_type 		uint16_t
#define save_load_enable
#define demo_enable
				//#define BlueFilter
				//#define tst_BRIGHTNESS 		22
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=12;

	//#define NUM_LEDS_adjustable //!del

	#define server_render
	#ifdef server_render //server as 4th corner
		#define CubeXp		13 //36 nw
		#define CubeYp		12
		#define CubeZp		14
		#define LEDs_RENDER
	#endif

#elif defined(Cube3MCU_12p)
	#define Cube4MCU
	#define use_ESP32
//#define WiFi_SEND
//#define WiFi_ControlHTMLpage
//#define WiFi_ControlHTMLpage_switch_p	32	//GPIO32==IO32==Touch9			//touchRead(T9); th=~30 //!! action btn

				//#define SerialControl
				//#define tstFPS
	#define SerialSpeed		921600

	//#define sound_p					39

	#define NUM_LEDS_edge 		145//12//145//24//145
	#define NUM_LEDS_mcu 		NUM_LEDS_edge*3
	#define NUM_LEDSall 		NUM_LEDS_mcu*4
	#define gNUM_LEDS			NUM_LEDSall

	#define NUM_LEDS_type 		uint16_t
#define save_load_enable
#define demo_enable
				//#define BlueFilter
				//#define tst_BRIGHTNESS 		22
	byte random_demo_sw_speed_td_m=2; //s  //!!
	byte random_demo_sw_speed_td_M=12;

	//#define NUM_LEDS_adjustable //!del

#define LEDs_RENDER
#define	MULTIPLE_PINS12

#else
	/*
	#define LEDp_redef				2//2  //this redefine any. del to use reference hardware schematics  //2 == D4 on NODEMCU v3 when FASTLED_ESP8266_RAW_PIN_ORDER

	//#define MULTIPLE_PINS //4
	//#define sound_p					A0 // enebles sound effects  //!fix used by keypad

	#ifdef saveMem
		#define gNUM_LEDS 			144 //60
		#define NUM_LEDS_type byte
	#else
		#define gNUM_LEDS 			180//144 //264//(1.67*2+1.05)*60 //300//1800//60 //300  //1024    //is a limit when adjustable or NUM_LEDS if not adjustable
		 //!	if NUM_LEDS>255
		#define NUM_LEDS_type 		uint16_t //byte uint16_t  //>255 NUM_LEDS  for(NUM_LEDS_type i=0; i<NUM_LEDS  //! fix random8(NUM_LEDS), effLength and other

		//#define eff_setX

		//#define NUM_LEDS_adjustable //now only in SerialControl // 1.6kb prog mem
		
		#define showSelectedOptionOnStipe //useful if no LCD to view what option is selected now
	#endif

	#define save_load_enable //to EEPROM

	#define demo_enable
	#define default_effN_Random // switch default to randomSet() or FastLED.clear();

	#define use_ESP8266

	#define tstFPS

	//#define tst
	//#define tst2  //detailed print of functions call
	//#define BlueFilter
	#define tst_BRIGHTNESS 		33 // to dimm AND see good colors use lower voltage but not software brightness
	#ifdef tst
		#define tst_POW_LIM	1000 //!? nw
	#endif

	 byte random_demo_sw_speed_td_m=2; //s  //!!
	 byte random_demo_sw_speed_td_M=12;


	//#define keypad1602 //free D0..3, D11..13, A1..  http://wiki.keyestudio.com/Ks0256_keyestudio_LCD1602_Expansion_Shield
												//https://www.dfrobot.com/wiki/index.php/Arduino_LCD_KeyPad_Shield_(SKU:_DFR0009)
	//#define IRkeypad	//3*7, ask me about support other types
	//#define key5x		//all main options has button //!! nw
	//#define key3x		//central btn switch mode (settings). Side btns are +-, i.e. effN, speed, length, gamma
	#define SerialControl //USB protocol for external GUI //! TODO software for android
	//v0.7 define only one of Serial
	//#define SerialSelect //enter effect № in terminal
	//#define LCD2004_i2c						//A4 A5

	//#define adj_pot								A0
	#ifdef adj_pot
	 #define adjType_LDR
	#endif
*/
#endif

#if defined(ClothSuit_mirror)
	#define ClothSuit
#endif

#ifdef debugSerial
 #undef tstFPS
 #undef SerialControl
#endif

//============================= redefine by global options that has higher priority
	#ifdef LEDp_redef
		#undef	LEDp
		#define LEDp	LEDp_redef
	#endif
	#ifdef startLoadEffN_redef
		#undef	startLoadEffN
		#define startLoadEffN	startLoadEffN_redef
	#endif
	#ifdef SerialSpeed_redef
		#undef	SerialSpeed
		#define	SerialSpeed	SerialSpeed_redef
	#endif
//============================================ sys constants

#if gNUM_LEDS<256 // NUM_LEDS_type==byte  //not working this way 2F##
	#define random8or16	random8
	#define beat8or16	beat8
#else
	#define random8or16	random16 //!!## random16 seems not working on ESP32
	#define beat8or16	beat16
#endif

#if defined( WiFi_SEND) || defined(WiFi_ControlHTMLpage)
 #ifndef use_ESP32
	#define use_ESP8266
 #endif
#endif

#ifdef IRkeypad
	#define IR_mode_sw_p 					2 //! btn (IR save while press) //! LRD at start => toggle this with LDR
	#define IRp 							3
	#ifdef legacy_pinout
		#define IR_mode_sw_p 				A4 //! switch effN+- speed+  || length+- RGB+	VS switch 
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
	/* //seted in each hardware option instead
	#ifdef use_ESP
		#define LEDp							D4
		#define btnAdd							D1
		#define btnSelectMode_p					D2
		#define btnSub							D3
	#else
		#define btnAdd							A1
		#define btnSelectMode_p					A2
		#define btnSub							A3
	#endif
	*/
	
#endif

#ifdef key5x
	#define btnSpeedAdd 				2
	#define btnSpeedSub 				3 //!del, add EffSub
	#define btnEffNAdd 					4
	#define btnEffLengthAdd				5
	#define btneffRGB		7 //GRB RG GB BG R G B
#endif


//!  #ifdef keypad || 3btn
#define effN_OPTION					0 //min
#define effSpeed_OPTION				1
#define effLength_OPTION			2
#define effRGB_OPTION	3
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


#ifdef demo_enable
	bool brandom_demo=false;
#endif
bool banimate=false;

//#define btnReset_p		A3 //resetSetiings_and_change_slot()


//=========================================================================

//#include "Arduino.h"										  // FastLED library.
//#include "C:\Users\asd\Documents\Arduino\hardware\WAV\avr\cores\lgt8f\hooks.c"	  //! wemos-Xi FastLED library.
#include "FastLED.h"
#ifndef NUMMATRIX
	CRGB leds[gNUM_LEDS+4]; //!!+4 tst del
#else
	#include <Adafruit_GFX.h>
	#include <FastLED_NeoMatrix.h>
	CRGB leds[gNUM_LEDS];

//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
//     arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
//     EACH MATRIX proceed in the same order, or alternate lines reverse
//     direction; pick one.
//   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
//     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
//     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
//   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
//     are arranged in horizontal rows or in vertical columns, respectively;
//     pick one or the other.
//   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
//     (tiles) in the OVERALL DISPLAY proceed in the same order for every
//     line, or alternate lines reverse direction; pick one.  When using
//     zig-zag order, the orientation of the matrices in alternate rows
//     will be rotated 180 degrees (this is normal -- simplifies wiring).
//   See example below for these values in action.

	FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(leds, mw, mh, 1, 1, NEO_MATRIX_TOP + NEO_MATRIX_LEFT+NEO_MATRIX_ROWS+ NEO_MATRIX_ZIGZAG);// NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT  ++ NEO_MATRIX_ROWS //LEDp??
#endif

#ifdef Cube4MCU
	//#define MCU_N	0

	// CRGB ledsX[NUM_LEDS_edge];
	// CRGB ledsY[NUM_LEDS_edge];
	// CRGB ledsZ[NUM_LEDS_edge];

	//	CRGBSet ledsRef(leds, gNUM_LEDS);

	//	CRGB *ledsXptr[NUM_LEDS_mcu]; 
	//	CRGB *ledsYptr[NUM_LEDS_mcu]; 
	//	CRGB *ledsZptr[NUM_LEDS_mcu]; 
	/*
	CRGB ledsX[NUM_LEDS_mcu];
	CRGB ledsY[NUM_LEDS_mcu];
	CRGB ledsZ[NUM_LEDS_mcu];
	*/
	#ifdef server_render
		//use server as 4th render node, same as in Cube_edges_arrays.h   MCU_N==3    shift by +NUM_LEDS_mcu*3
//		CRGBSet ledsX(leds, 0  +NUM_LEDS_mcu*3, NUM_LEDS_edge  +NUM_LEDS_mcu*3);
//		CRGBSet ledsY(leds, NUM_LEDS_edge*2  +NUM_LEDS_mcu*3,  NUM_LEDS_edge+1  +NUM_LEDS_mcu*3);
//		CRGBSet ledsZ(leds, NUM_LEDS_edge*3  +NUM_LEDS_mcu*3,  NUM_LEDS_edge*2+1  +NUM_LEDS_mcu*3);
	#endif

	void CubeLEDsFill_setup();
#endif


//=============================================================================================
#ifdef tstFPS
	bool bPrintPixels=false;
#endif

#if defined(LEDs_RENDER)
	#define setBrightness_gBrightness FastLED.setBrightness( gBrightness );
#else
	#define setBrightness_gBrightness // do nothing
#endif

//=========================================================================

struct SaveObj //# sizeof
{
	byte effN; // = eff SLOT at start
	byte effSpeed;
	byte effSpeedH; //! //EVERY_N_MILLISECONDS( 20 ) gHue+=effSpeed;
	byte effLength;
	byte effLengthH;
	byte effRGB;//post processing //1 => disable chennel R, 2 => disable G ,  7 => fast cycle diferent , //!comment other
	byte effFade;
	// byte gH;
	// byte gS;
	// byte gV;
	CRGB gColor; //# save , set
	CRGB gColorBg;//! gHueBG == 0 ? White	== 255 ? black
	byte gFade; //apply before eff
	byte indexOrBits;
	byte gDelay;
	byte gBrightness; //#
	NUM_LEDS_type NUM_LEDS; //work ifdef use_ESP to save progmem
};
struct SaveObj oostr;

#ifdef PWM_enabled
	#define PWM_E	2 //pins
	const int PWM_v_m=6;
	const int PWM_v_M=4090; //   max duty cycle for IR21xx driver https://electronics.stackexchange.com/questions/240090/ir2110-max-duty-cycle
	#define pwm_vsE	5 //points
	
	uint16_t pwm_vs[pwm_vsE]; //value 0...1023 //! may be better 255
	uint16_t pwm_ts[pwm_vsE]; //at time  10x
	byte pwm_p_selected=5; //! can del

	struct SaveObjDimmer
	{
		byte p; //pin
		uint16_t loop_d;  //ms   animation loop //0 is off
		//uint16_t PWM_m;
		//uint16_t PWM_M;
		//byte segE;
		uint16_t pwm_vs[pwm_vsE];
		uint16_t pwm_ts[pwm_vsE]; //! byte  int 1/255 parts of loop_d
	};
	
	byte dimmers_ps[PWM_E] ={16,5}; //!!
	SaveObjDimmer oSaveObjDimmers[PWM_E]= //oSaveObjDimmers[pwm_p_selected]
	{
		{
			16, //!!! pin
			5000, 
			//6, 4090, 5, 
			{0,4090,222,1111,0},
			{0,1000,2000,3000,4000}
		},
		{
			5, //!!! pin
			10000, 
			//6, 4090, 5, 
			{0,4090,2222,500,10},
			{0,100,1000,3000,6000}
		}
	};
#endif


#define effRGB_M	20
	byte effSpeed_last=1; //for animate eff
	byte effLength_last=16;
	byte effLength2=4;//!!

long anim_next_t=0; //to delay anim_f() and redraw assign millis()+XXX, dont use delay, because ESP watchdog reset, itc

byte BOTTOM_INDEX = 0;
NUM_LEDS_type CENTER_TOP_INDEX;
byte EVENODD;


//this because difficult to rename all to use struct
#define effN oostr.effN
#define effSpeed oostr.effSpeed
#define effSpeedH oostr.effSpeedH
#define effLength oostr.effLength
#define effLengthH oostr.effLengthH
#define effRGB oostr.effRGB
#define effFade oostr.effFade
#define gColor oostr.gColor
#define gColorBg oostr.gColorBg
#define gDelay oostr.gDelay
#define gFade oostr.gFade
#define indexOrBits oostr.indexOrBits
#define gBrightness oostr.gBrightness
#if defined(SerialControl) && defined(NUM_LEDS_adjustable)
	#define NUM_LEDS oostr.NUM_LEDS  //this eat 1.6kb of "program storage space" //? why 
#else
	#define NUM_LEDS gNUM_LEDS //make it constant to use min mem
#endif

	void NUM_LEDS_setup()
	{
		#if defined(SerialControl) && defined(NUM_LEDS_adjustable)
		if(NUM_LEDS<5) NUM_LEDS=5;
		else
		if(NUM_LEDS>gNUM_LEDS) NUM_LEDS=gNUM_LEDS;
		#endif
		
		CENTER_TOP_INDEX=NUM_LEDS / 2;
		EVENODD = NUM_LEDS % 2;
							#ifdef tst2
												Serial.print(" NUM_LEDS:"); Serial.println(NUM_LEDS);Serial.println(gNUM_LEDS);
							#endif					
	}

//=========================================================================
bool bCurrentEff_IsRandom_AndNotSlotN=false;
byte realEffN=10;

byte anim_d=50;

void re_effRGB();


// #ifdef adjType_LDR
 // byte ambientLight;
// #endif
#ifdef save_load_enable
void load(byte);
#endif
#ifdef PWM_enabled
void saveDimmer(byte);
void loadDimmer(byte);
#endif

#if defined(SerialSelect) || defined(SerialControl)
void checkSerial();
#endif

bool bPause=false;

#ifdef REVERSE_STRIPE
void fixArrayDir()
{
  NUM_LEDS_type i = NUM_LEDS - 1;
  NUM_LEDS_type j = 0;
  while(i > j)
  {
    CRGB temp = leds[i];
    leds[i] = leds[j];
    leds[j] = temp;
    i--;
    j++;
  }
 
  /*
	int* head = 0;
    int* tail = 0 + NUM_LEDS - 1;
    for (int i = 0; i < NUM_LEDS/2; ++i)
    {
        if (head < tail)
        {
            int tmp = *tail;
            *tail = *head;
            *head = tmp;

            head++; tail--;
        }
    }
	*/
}
#define FastLED_show_DIRECTION	fixArrayDir();FastLED.show();fixArrayDir();
#else
	#define FastLED_show_DIRECTION	FastLED.show();
#endif


//----------- return to GUI
#define PRINT__			Serial.write(111);Serial.write(166);Serial.write(77);//header
#define PRINT_leds		Serial.write(133);
#define PRINT_totall	Serial.write(122);
#define PRINT_tst	Serial.write(199);
#define PRINT_settings	Serial.write(99);
//----------- 

//============================================= display LCD or serial output (debug)
#if defined(tst) || defined(SerialControl)|| defined(SerialSelect)|| defined(LCD2004_i2c)|| defined(keypad1602) 
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
		
		lcd.setCursor(8,1); lcd.print("RGB");	lcd_print_selectedOption(effRGB_OPTION);
		lcd.setCursor(12,1); lcd.print("   ");
		lcd.setCursor(12,1); lcd.print(effRGB);
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
		lcd.print(effRGB); lcd.print("  ");	lcd.setCursor(6,3); lcd.print(" RGBs");
		//lcd.print(anim_d);lcd.print("  ");
	}
  #endif
  
  #ifdef SerialSelect
  		#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
	#endif

  #ifdef SerialControl
	#define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
  #endif


//-------------------------------------------------- this refurn values to GUI
  #if defined(tst) || defined(SerialControl)
		//!?? #define SET_UPD_Display	 /*bNeed_display_upd=true;*/ display_upd();
																					//Serial.println(NUM_LEDS);Serial.println(gNUM_LEDS);
	PRINT__
	PRINT_settings
	
	byte tmp=0;
	if(bCurrentEff_IsRandom_AndNotSlotN) //?same as effN>=254  //show current effN but not slot of random demo
	{
		tmp=effN;
		effN=realEffN;
	}
	
	Serial.write(sizeof(oostr));
	Serial.write((const uint8_t*)&oostr, sizeof(oostr));

	if(bCurrentEff_IsRandom_AndNotSlotN)
		effN=tmp;
	
	if(bPause)
	{
		uint8_t *p;
		PRINT__
		PRINT_leds

		uint16_t fps=LEDS.getFPS();
		p = (uint8_t*) &fps;
		Serial.write(p,2);


		uint16_t size=gNUM_LEDS*3;
		p = (uint8_t*) &size;
		Serial.write(p,2);
		Serial.write((const uint8_t*)leds, size);
	}
  #endif
	//#ifdef tst2
	// uint16_t size=gNUM_LEDS*3;
	// uint16_t fps=LEDS.getFPS();
	// Serial.println(size);Serial.println(size);
	// Serial.println(gNUM_LEDS);Serial.println(gNUM_LEDS);
	// Serial.println(fps);
	//#endif
}
#endif
  #ifndef SET_UPD_Display
	#define SET_UPD_Display
  #endif
void save(byte);

//=========================================================================
#if defined(use_ESP8266) || defined(use_ESP32)  //! fix other #ifdef use_ESP
	#ifdef use_ESP32
	#else
		#include "ESP8266WiFi.h"
	#endif

	#ifdef LEDs_RENDER
	  //#define FASTLED_ESP8266_RAW_PIN_ORDER
	#endif

	#if defined(WiFi_SEND) || defined(WiFi_ControlHTMLpage)
		#include "WiFi_server.h"
	#endif

#endif
//=============================================================================================

#include "anim.h"

void resetSetiings_and_change_slot() //! or changeEff(effN)
{
								#ifdef tst
								Serial.println("reset");
								#endif
	#ifdef NUM_LEDS_adjustable					
	NUM_LEDS=gNUM_LEDS;
	#endif
	effN=effN_off; // = eff SLOT at start
	effSpeed=4; //also is incr for gHue in anim.h
	effSpeed_last=1; //for animate eff
	effSpeedH=1; //! //EVERY_N_MILLISECONDS( 20 ) gHue+=effSpeed;
	effLength=NUM_LEDS/4+1;
	effLength_last=4;
	effLength2=4;//!!
	effLengthH=NUM_LEDS/4+1;
	effRGB=0;
	#define effRGB_M	17
	effFade=0;
	gColor=CRGB::White;
	gColorBg=CRGB::Black;
	#ifdef ESP32_HTML_NO_RENDER
	gDelay=5;
	#else
	gDelay=0;
	#endif
	gFade=0;


	change_slot(effN);
	SET_UPD_Display //saveAfter2s();

	// #ifdef demo_enable
	// brandom_demo=false;
	// #endif
	// banimate=false;
}

#ifdef IRkeypad
bool bIRcommandRepeated=false;
#endif
#if defined(save_load_enable) || defined(PWM_enabled)
	#include "save_load.h"
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

	 if(N<=9) //!
	 {
	 	#ifdef save_load_enable
	 	load(N);
	 	#endif
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
	SET_UPD_Display
	#ifdef save_load_enable
	saveAfter2s();
	#endif
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
	SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
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
	SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
}
void  effSpeed_sub()
{
	effSpeed-=(effSpeed<15)?1:4; 
	//if(effSpeed>200) effSpeed=50;
	if(effSpeed>100) effSpeed-=20;
	SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
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

	  SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
}
void  effLength_sub()
{
	if(effLength==1) effLength=NUM_LEDS;
	else
	if(effLength<10) effLength--;
	else
	if(effLength<50) effLength-=5;
	else effLength-=20;
	  SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
}
	  
void  effRGB_add()
{
	effRGB++;
	if(effRGB>effRGB_M) effRGB=0;
	SET_UPD_Display
	#ifdef save_load_enable
	 saveAfter2s();
	#endif
}

//--------- for keypad, 3btn
void LCDoption_selected_add()
{
	LCDoption_selected++;
	#ifdef showSelectedOptionOnStipe //##
		FastLED.clear();
		switch(LCDoption_selected)
		 {
			case effSpeed_OPTION:
			{
				int M=map(effSpeed,0,255,0,NUM_LEDS);
				for(int i = 0; i < M; ++i)
				{
					leds[i].b=255;
					delay(5);
					leds[i].b=0;
				}
			}
			break;		
			
			case effLength_OPTION:
			{
				int M=map(effLength,0,255,0,NUM_LEDS);
				for(int i = 0; i < M; ++i)
				{
					leds[i].g=255;
					delay(5);
				}
			}
			break;	
			
			case effRGB_OPTION:
			{
				int M=effRGB;
				for(int i = 0; i < M; ++i)
				{
					leds[i]=CHSV(i*10,255,255);
				}
				delay(50);
			}
			break;
			
			case brightness_OPTION: //!
			{
				int M=map(gBrightness,0,255,0,NUM_LEDS);
				for(int i = 0; i < M; ++i)
				{
					leds[i]=CRGB::White;
				}
				delay(40);
			}
			break;
		 }
	#endif
	//#define LCDoption_selected_M
	//if(LCDoption_selected>LCDoption_selected_M)LCDoption_selected=0;
	SET_UPD_Display
	#ifdef tst2
	Serial.print("LCDoption_selected_add:"); Serial.println(LCDoption_selected);
	#endif
}
void switch_LCDoption_selected_value_add()
{
	#ifdef tst2
	Serial.print("switch_LCDoption_selected_value_add:"); Serial.println(LCDoption_selected);
	#endif
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
			
			case effRGB_OPTION:
			 effRGB_add();
			break;
			
			case brightness_OPTION: //!
				gBrightness+=5;
				setBrightness_gBrightness  //!! save BRIGHTNESS
			break;
		 }
	#ifdef tst2
	Serial.print(":"); Serial.println(LCDoption_selected);
	#endif
}


void switch_LCDoption_selected_value_sub()
{
	#ifdef tst2
	Serial.print("switch_LCDoption_selected_value_sub:"); Serial.println(LCDoption_selected);
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
			
			 case effRGB_OPTION:
					//ambientLight_map(); FastLED.show(); //!
			 // effRGB_sub();
			 break;
			 
			case brightness_OPTION:
				gBrightness-=5;
				setBrightness_gBrightness
			break;
			default:
			 LCDoption_selected=brightness_OPTION; //max
			break;
		 }
	#ifdef tst2
	Serial.print(":"); Serial.println(LCDoption_selected);
	#endif
}


#if defined(keypad1602) || defined(key3x) || defined(key1d1a)
 #define enableInputRead
#endif

#ifdef enableInputRead
	#ifdef key1d1a
		int potAdd_a2x_avg;
		int potAdd_a2x_avg_old;
		const int rangeA_M_off=1500; // !!fix ESP   //  from 1024*2 because 2*analogRead
		const int rangeA_m=rangeA_M_off*0.12, rangeA_M=rangeA_M_off*0.9;
		int rangeOut_m=80, rangeOut_M=180; //current, changing while pot be moved out of rangeA

		byte btnFlag=0; //
		byte aVal_old=0;

		long nextCan_effN_change_t=0;
	#endif

	long nextCanInputRead_t=0;
#endif
	
//=========================================================================
void setup()
{


	#if defined( WiFi_SEND) || defined(WiFi_ControlHTMLpage)
		setup_wifi();
	#elif  defined(use_ESP_WiFioff)
		#ifdef use_ESP32 //@ https://github.com/espressif/arduino-esp32/issues/1306
		  //Wifi is disabled by default //@@ https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/   //? With "WiFi.mode( WIFI_MODE_NULL);" The current compsuntion is the same.
		  //!!
		  //#include <WiFi.h> //! test size, test power
			//btStop(); //https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiBlueToothSwitch/WiFiBlueToothSwitch.ino
		#else
			WiFi.mode( WIFI_OFF );
			WiFi.forceSleepBegin();
		#endif

	#endif

	#if defined(tst) || defined(SerialSelect) || defined(SerialControl)
	delay(800);
	#else
	delay(99);
	#endif


	#ifdef Cube4MCU
	//TODO  CubeLEDsFill_setup(); //ptr arrs
	#endif
	#ifdef LEDs_RENDER
		#if defined(MULTIPLE_PINS2) //pins 12-19,0,2,3,4,5,21,22,23
			FastLED.addLeds<LEDchipType, 4, GRB>(leds, 0, gNUM_LEDS/2);
			FastLED.addLeds<LEDchipType, 5, GRB>(leds, gNUM_LEDS/2,gNUM_LEDS/2);
		#elif defined(MULTIPLE_PINS4)
			FastLED.addLeds<LEDchipType, 4, GRB>(leds, 0, gNUM_LEDS/4);
			FastLED.addLeds<LEDchipType, 5, GRB>(leds, gNUM_LEDS/4,gNUM_LEDS/4);
			FastLED.addLeds<LEDchipType, 13, GRB>(leds, gNUM_LEDS/4*2,gNUM_LEDS/4);
			FastLED.addLeds<LEDchipType, 14, GRB>(leds, gNUM_LEDS/4*3,gNUM_LEDS/4);
		#elif defined(MULTIPLE_PINS8)
			FastLED.addLeds<LEDchipType, 2, GRB>(leds, 0, gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 3, GRB>(leds, gNUM_LEDS/8,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 4, GRB>(leds, gNUM_LEDS/8*2,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 5, GRB>(leds, gNUM_LEDS/8*3,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 13, GRB>(leds, gNUM_LEDS/8*4,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 14, GRB>(leds, gNUM_LEDS/8*5,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 15, GRB>(leds, gNUM_LEDS/8*6,gNUM_LEDS/8);
			FastLED.addLeds<LEDchipType, 16, GRB>(leds, gNUM_LEDS/8*7,gNUM_LEDS/8);
		#elif defined(MULTIPLE_PINS12)
				// FastLED.addLeds<LEDchipType, 2, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 3, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 4, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 5, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 6, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 21, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 22, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 23, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 12, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 13, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 14, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
				// FastLED.addLeds<LEDchipType, 15, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);

			FastLED.addLeds<LEDchipType, 23, GRB>(leds, gNUM_LEDS/12*0,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 22, GRB>(leds, gNUM_LEDS/12*1,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 3, GRB>(leds, gNUM_LEDS/12*2,gNUM_LEDS/12);

			FastLED.addLeds<LEDchipType, 21, GRB>(leds, gNUM_LEDS/12*3,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 19, GRB>(leds, gNUM_LEDS/12*4,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 18, GRB>(leds, gNUM_LEDS/12*5,gNUM_LEDS/12);

			FastLED.addLeds<LEDchipType, 5, GRB>(leds, gNUM_LEDS/12*6,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 17, GRB>(leds, gNUM_LEDS/12*7,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 16, GRB>(leds, gNUM_LEDS/12*8,gNUM_LEDS/12);

			FastLED.addLeds<LEDchipType, 4, GRB>(leds, gNUM_LEDS/12*9,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 2, GRB>(leds, gNUM_LEDS/12*10,gNUM_LEDS/12);
			FastLED.addLeds<LEDchipType, 2, GRB>(leds, gNUM_LEDS/12*11,gNUM_LEDS/12);



		#elif defined(server_render) //use server as 4th render node Cube
			FastLED.addLeds<LEDchipType, CubeXp, GRB>(leds,NUM_LEDS_mcu*3, NUM_LEDS_edge);
			FastLED.addLeds<LEDchipType, CubeYp, GRB>(leds,NUM_LEDS_mcu*3+NUM_LEDS_edge,NUM_LEDS_edge); //w:4,5, 12 13 14 16 32 33  nw: 6, 11, 15,  31 34..37
			FastLED.addLeds<LEDchipType, CubeZp, GRB>(leds,NUM_LEDS_mcu*3+NUM_LEDS_edge*2,NUM_LEDS_edge);
			// FastLED.addLeds<LEDchipType, CubeXp, GRB>(ledsX,NUM_LEDS_edge);
			// FastLED.addLeds<LEDchipType, CubeYp, GRB>(ledsY,NUM_LEDS_edge); //w:12 13 14 16 32 33  nw: 11, 15,  31 34..37
			// FastLED.addLeds<LEDchipType, CubeZp, GRB>(ledsZ,NUM_LEDS_edge);
		#else

			FastLED.addLeds<LEDchipType, LEDp, GRB>(leds, gNUM_LEDS);

		#endif
		// #endif

		#ifdef tstFPS
			FastLED.countFPS(1); //nFrames = 25
			FastLED.clear();
			FastLED.show();
		#endif
		#ifdef NUMMATRIX //##!!
			matrix->begin();
			matrix->setTextWrap(false);
			matrix->setBrightness(40);
			//matrix->setTextColor(colors[0]);
		#endif

	#endif


	#ifdef keypad1602
	 pinMode(A0, INPUT_PULLUP);	//for situation of shield not connected (if keypad1602 defined but not connected something run effSub)
	 lcd.begin(16, 2);
	#endif

	//---------------------------------------------------------
	#if defined(LEDs_RENDER)
		#if defined(adj_pot) && defined(LEDs_RENDER)
				 pinMode(adj_pot,INPUT_PULLUP); delay(2);
				#if defined(adjType_LDR) 
				 FastLED.setBrightness(ambientLight_map()); //! every n ms
				#else
				 if(analogRead(adj_pot)<900) FastLED.setBrightness( map(analogRead(adj_pot),0,1023, 22, 255) ); //! every n ms
				#endif
		#endif

		#if defined(tst_BRIGHTNESS)
			FastLED.setBrightness( tst_BRIGHTNESS );
		#endif
	#endif
	//---------------------------------------------------------

	#if defined(tst) || defined(SerialSelect) || defined(SerialControl)  || defined(debugSerial)
		Serial.begin(SerialSpeed);
		#ifdef debugSerial
			Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
			Serial.print( F("Boot Vers: ") ); Serial.println(system_get_boot_version());
			Serial.print( F("CPU: ") ); Serial.println(system_get_cpu_freq());
			Serial.print( F("SDK: ") ); Serial.println(system_get_sdk_version());
			Serial.print( F("Chip ID: ") ); Serial.println(system_get_chip_id());
			Serial.print( F("Flash ID: ") ); Serial.println(spi_flash_get_id());
			Serial.print( F("Flash Size: ") ); Serial.println(ESP.getFlashChipRealSize());
			Serial.print( F("Vcc: ") ); Serial.println(ESP.getVcc());
			Serial.println();
			Serial.setDebugOutput(true);
		#endif
	#endif

	  #ifdef tst_POW_LIM
	  	FastLED.setMaxPowerInVoltsAndMilliamps(5,tst_POW_LIM); //! tst
	  #endif
	  
	#ifdef tst
		//Serial.println(F("test"));
		#ifdef LDR
		#endif
	#endif



					 #define btnAdd						7 //14=D5 on NODEMCU and D1 mini //###
					 #define btnSelectMode_p			8 //12=D6
					 #define btnSub						9 //13=D7

	#ifdef btn0
	 	pinMode(btn0, INPUT_PULLUP);
	#endif
	#ifdef btn1
	 	pinMode(btn1, INPUT_PULLUP);
	#endif
	#ifdef btn2
	 	pinMode(btn2, INPUT_PULLUP);
	#endif
	
	#ifdef key3x
	 	pinMode(btnAdd, INPUT_PULLUP);
		pinMode(btnSub, INPUT_PULLUP);
		pinMode(btnSelectMode_p, INPUT_PULLUP);
	#endif
	#ifdef key1d1a
		pinMode(potAdd, INPUT);
		
		pinMode(btnSelectMode_p, INPUT); //touch hi == not change jampers on module|IC
		potAdd_a2x_avg=analogRead(potAdd)+analogRead(potAdd) -20;
	#endif

	#ifdef key5x
		pinMode(btnSpeedAdd, INPUT_PULLUP);
		pinMode(btnSpeedSub, INPUT_PULLUP);
		pinMode(btnEffNAdd, INPUT_PULLUP);
		pinMode(btnEffLengthAdd, INPUT_PULLUP);
		pinMode(btneffRGB, INPUT_PULLUP);
		
		//pinMode(btnReset_p, INPUT_PULLUP); //!
	#endif

	#ifdef LCD2004_i2c
	  lcd.init();	  lcd.init(); //!tst if only one init is enough
	  lcd.backlight();
	  // lcd.setCursor(3,0);
	  // lcd.setCursor(2,1);
	  // lcd.setCursor(0,2);
	  // lcd.print(""); 
	  // lcd.setCursor(2,3);
	#endif

	delay(1);


	//if(!digitalRead(btnReset_p))	resetSetiings_and_change_slot(); else //!
	#ifdef startLoadEffN
		effN_set(startLoadEffN);
		//change_slot(startLoadEffN); //not set effN, only set anim_f and settings, so not affect navigation next/prev
		//SET_UPD_Display 
	#else
		#ifdef save_load_enable
		load(effN);
		#else
		effN_set(11); //11 //so anim_f != null //# tst
		NUM_LEDS_setup();
		#endif
	#endif

	#ifdef PWM_enabled
		loadDimmer(0);
	#endif


	#ifdef IRkeypad
	pinMode(IR_mode_sw_p, INPUT_PULLUP);

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
			Serial.println(F("no IR pin"));
			#endif
		}
	}
	#endif

	#if defined(tst) && defined(LEDs_RENDER)
		leds[0] = CRGB::White;
		leds[1] = CRGB::Red;
		leds[2] = CRGB::Green;
		leds[3] = CRGB::Blue;
		FastLED.show();
		delay(300);
		FastLED.clear();
		FastLED.show();
	#endif

	//display_upd
	#if defined(tst) || defined(SerialControl)|| defined(SerialSelect)|| defined(LCD2004_i2c)|| defined(keypad1602) 
		display_upd();
	#endif
}
 
//=============================================================================================
#include "SerialControl.h"

#ifdef WiFi_ControlHTMLpage
	long loopHTML_next_t=50; //d at startup
	byte loopHTML_handleClient_d=5;//20;
#endif



//@ https://randomnerdtutorials.com/esp8266-pwm-arduino-ide/

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapfloat01(float x, float out_min, float out_max)
{
 return x * (out_max - out_min) + out_min;
}
/*
float lerpPrecission(float a, float b, float f) 
{
    return (a * (1.0 - f)) + (b * f);
}
float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}
inline uint16_t unsignedInterpolate(uint16_t a, uint16_t b, uint16_t position) {
    uint32_t r1;
    uint16_t r2;

      // Only one multiply, and one divide/shift right.  Shame about having to
      // cast to long int and back again.

    r1 = (uint32_t) position * (b-a);
    r2 = (r1 >> XY_TABLE_FRAC_BITS) + a;
    return r2;    
}
*/


void loop()
{
	#ifdef WiFi_ControlHTMLpage
	if(millis()>loopHTML_next_t)
	{
		loopHTML_next_t=millis()+loopHTML_handleClient_d; //!tst
		loopHTML(); //now it only call handleClient()
	}
	#endif

	#if defined(SerialSelect) || defined(SerialControl)
		checkSerial();
	#endif
	
#ifdef PWM_enabled
	//TODO switch_slot_PWM()
	#define segmentsE	pwm_vsE	
	/*
if(indexOrBits%2) 
{//fixed seg length (do NOT use use pwm_ts) , so seg_d=loop_d/segmentsE

	for(byte pwmN=0;pwmN<PWM_E;pwmN++)
	{
		int loop_d= oSaveObjDimmers[pwmN].loop_d; //length eg 1000	 		//long loop_d=(1+effLength)*100;

		//no adj NUM of segments

		long loop_time=millis()%loop_d; //eg 0....1000
		

		int seg_d=loop_d/segmentsE; //eg 200
		float seg_t01= ( loop_time%seg_d ) /(float)seg_d; //%  0...1

		byte segNow=loop_time/seg_d;
		byte segNext=(segNow<segmentsE-1)?(segNow+1):0;
		int PW0= (int)mapfloat01(seg_t01,(float)oSaveObjDimmers[pwmN].pwm_vs[segNow], (float)oSaveObjDimmers[pwmN].pwm_vs[segNext]);   //seg_t01*PWM_v_M;//seg_t01*PWM_v_M;//saw //(((float)time)/loop_d)*PWM_v_M;
		PW0=constrain(PW0,PWM_v_m,PWM_v_M); //to avoid IR2101 burn it can't be 100%

		//analogWrite(dimmers_ps[pwmN] ,PW0);

				if(pwmN==0)
					EVERY_N_MILLISECONDS(40)
					{
						Serial.print(0);Serial.print(" ");
						Serial.print(1020);Serial.print(" ");
						Serial.print(segNow*100);Serial.print(" ");
						Serial.print(segmentsE*100);Serial.print(" ");
						Serial.println(PW0);
					}
	}
}
else*/
{ //  seg length use pwm_ts
	for(byte pwmN=0;pwmN<PWM_E;pwmN++)
	{
		int loop_d= oSaveObjDimmers[pwmN].loop_d;	//eg 1000
		long loop_time=millis()%loop_d;	//eg 0....1000
		
		//-----------calc  segNow, segNow_start, segNow_end
		byte segNow=0;
		int segNow_start=0;
		int segNow_end=0;
		int v_start=0;  //! TODO v_start is pwm_vs[segNow]
		int v_end=oSaveObjDimmers[pwmN].pwm_vs[segmentsE-1];
		while(true)
		{
			segNow_start=segNow_end;
			v_start=v_end;
			if(segNow==segmentsE)
			{
				segNow_end=loop_d;
				//v_end=oSaveObjDimmers[pwmN].pwm_vs[0];
				v_end=v_start;
				break;
			}
			segNow_end=oSaveObjDimmers[pwmN].pwm_ts[segNow]*100; //! *100
			v_end=oSaveObjDimmers[pwmN].pwm_vs[segNow];
			if(loop_time > segNow_end)
				segNow++;
			else break;
		}
		byte segLast=segNow>0?segNow-1:segmentsE-1;
		//-----------
		int PW0= map(loop_time,
		segNow_start,
		segNow_end,
		v_start,
		v_end
		);
		PW0=constrain(PW0,PWM_v_m,PWM_v_M);
		//analogWrite(dimmers_ps[pwmN] ,PW0);
		//-----------
/*
if(pwmN==0)
{
	EVERY_N_MILLISECONDS(50)
	{
		Serial.print(0);Serial.print(" ");
		Serial.print(1020);Serial.print(" ");
		Serial.print(v_start);Serial.print(" ");
		Serial.print(v_end);Serial.print(" ");
		Serial.print(1050+segNow*50);Serial.print(" ");
		Serial.print(1050+0*50);Serial.print(" ");
		Serial.print(1050+segmentsE*50);Serial.print(" ");
		Serial.println(PW0);
	}
}
*/
	}
}
#endif

#ifndef IRkeypad
	LED_anim();
	#ifdef save_load_enable
	 saveIfNeed(); //^
	#endif
#endif
#ifdef IRkeypad
if(bIR_mode)
{
	if (!IRLremote.receiving()) {  // Check if we are currently receiving data
		LED_anim();
		#ifdef save_load_enable
		 saveIfNeed();
		#endif
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
			#ifdef save_load_enable
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
		  #endif
	  
	  					
	switch(IRcommand)
	{
	  //-------------- CH- CH CH+
	  case 0x45:		if(millis()<nextCanChangeByIr) break;
	  effLength_sub();
	  break;

	  case 0x46:		if(millis()<nextCanChangeByIr) break;
	  effRGB_add();
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
	  #ifdef save_load_enable
	  saveAfter2s();
	  #endif
	  SET_UPD_Display
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
  } //if (IRLremote.available())
}//if(bIR_mode)
else
{
	LED_anim();
}
#endif

#ifdef enableInputRead
//========================== btn on keypads
#if defined(key3x) || defined(key5x)
fill_solid( leds, NUM_LEDS/8, CRGB::Blue); FastLED.show(); delay(1000);
#endif


if(millis()>nextCanInputRead_t)
{
 
#ifdef keypad1602
 nextCanInputRead_t=millis()+220;
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
#endif

		//#if defined(key3x) || defined(key5x) || defined(key1d1a)
 #ifdef key3x
	nextCanInputRead_t=millis()+180;
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
	if(!digitalRead(btnSelectMode_p))
	{ //##!!! also flash
		LCDoption_selected_add();
	}
 #elif defined (key5x)
	nextCanInputRead_t=millis()+180;
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
	if(!digitalRead(btneffRGB))
	{
		effRGB_add();		
	}
 #elif defined (key1d1a)
	
nextCanInputRead_t=millis()+25;

/*
Serial.print(btnFlag); Serial.print(" ");
Serial.print(LCDoption_selected); Serial.print(" ");
Serial.print(effN); Serial.print(" ");
Serial.println();
*/
//----------------------- btn single, double, long press with indication, and pos marks of selected value
if(digitalRead(btnSelectMode_p)) // touch btn pressed
{
						if(btnFlag==0) //TODO every 8th px
						{
							fill_solid( leds, NUM_LEDS/8, CRGB::White); FastLED.show(); delay(10);
						}else
						if(btnFlag==1)
						{
							fill_solid( leds, NUM_LEDS/8, CRGB::Yellow); FastLED.show(); delay(10);
						}else
						if(btnFlag==6)
						{
							fill_solid( leds, NUM_LEDS/8, CRGB::Blue); FastLED.show(); delay(10);
						}else
						if(btnFlag==70)
						{
							fill_solid( leds, NUM_LEDS/8, CRGB::Green); FastLED.show(); delay(10);
						}
	if(btnFlag<99 )
	{
		btnFlag++;
		if(btnFlag>70) //long pressing
		{
			btnFlag=20;
			//if((millis()/16)%8==0 )	
			{
				effN_add();
					leds[0]=CRGB::Green;
					FastLED.show(); delay(10);
					leds[0]=CRGB::Black;
					FastLED.show();
			}
		}
	}
	else
	if(btnFlag>=100 && btnFlag<=103) btnFlag=110;
}
else
{
	switch(btnFlag)
	{
		case 0: break; // no press before
		case 1: //short click
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			btnFlag=100; //wait for next
		break; 
		
		case 100:
		case 101:
		case 102:
		case 103:
		btnFlag++;
		break;  //wait for next a tick more
		
		case 104: //very single click (end)
			btnFlag=0;
							LCDoption_selected_add();
							
							fill_solid( leds, NUM_LEDS, CRGB::Yellow);
							leds[LCDoption_selected]=CRGB::Red;
							FastLED.show(); delay(500);
							// leds[0]=CRGB::Yellow;
							// FastLED.show(); delay(5);
							// leds[0]=CRGB::Black;
							// FastLED.show();
		break; 
		
		case 110: //double click
		{
			btnFlag=0;
							fill_solid( leds, 8, CRGB::Black); FastLED.show(); 

							// FastLED.show(); delay(5);
							// leds[0]=CRGB::Black;
							// leds[1]=CRGB::Black;
							// FastLED.show();
							byte rnd=5+random8(5);
																	leds[rnd]=CRGB::Red;
																	leds[rnd+1]=CRGB::Red;
																	FastLED.show(); delay(50);
							ActionRunWaitEnd(rnd);
							//ActionRunWaitEnd(random8(9));
		}
		break;
		
		default: //7...99 //long click
			btnFlag=0;
			effN_add();
							fill_solid( leds, NUM_LEDS, CRGB::Blue);
							leds[effN/4]=CRGB::Red;
							FastLED.show();  delay(50);
							// leds[0]=CRGB::Blue;
							// leds[1]=CRGB::Blue;
							// FastLED.show(); delay(5);
							// leds[0]=CRGB::Black;
							// leds[1]=CRGB::Black;
							// FastLED.show();
		break;
	}
}
#endif //key1d1a

} //if(millis()>nextCanInputRead_t)
	

#if defined (key1d1a) //this is better working when always read. But will try to fix and move it right after btn read in key1d1a
//else //pot
{

int a =analogRead(potAdd)+analogRead(potAdd)	-60; if(a<0) a=0; 
potAdd_a2x_avg_old=potAdd_a2x_avg;
potAdd_a2x_avg = potAdd_a2x_avg*0.9+a*0.1;

byte aVal;

	if(a>rangeA_M_off) //out immidiately
	{
		goto potAdd_outOffRange_skipChanges;
	}
	else
	{
		aVal_old=aVal;
		
		
		// -------------------- ranged
		{
		if(potAdd_a2x_avg>rangeA_m && potAdd_a2x_avg<rangeA_M) //senter region linear map to value
		{
			
		}
		else //border area act like joystick, moving range and value
		{
			if(potAdd_a2x_avg<rangeA_m)
			{
				byte change=(rangeA_m-potAdd_a2x_avg)/64;
				if(change>3) change=3;
				
				if(rangeOut_m>change)
				{
					rangeOut_m-= change;
					rangeOut_M-= change;
				}
				else
				{
					rangeOut_m=0;
					rangeOut_M= 100; //rangeOut_M-= (change-rangeOut_m)
				}
			}
			else
			if(potAdd_a2x_avg>rangeA_M)
			{
				byte change=(potAdd_a2x_avg-rangeA_M)/64;
				if(change>5) change=5;
				if( rangeOut_M<(255-change))
				{
					rangeOut_m+= change;
					rangeOut_M+= change;
				}
				else 
				{
					rangeOut_M=255; //!
					rangeOut_m=155;//rangeOut_m+=(255-rangeOut_M);
				}
			}
		}
	
		//float val= map(potAdd_a2x_avg, rangeA_m,rangeA_M, rangeOut_m, rangeOut_M);
		aVal= map(potAdd_a2x_avg, 0,rangeA_M_off, rangeOut_m, rangeOut_M);	//if(val<0) val=0;
	}
	
	// -------------------- simple, slow at start
	//aVal=map(potAdd_a2x_avg,0,rangeA_M_off, 0, 253);
	// -------------------- 
	
	if(aVal!=aVal_old)
	{
		leds[aVal/4]=CRGB::Red;			FastLED.show(); delay(10);
		
		switch(LCDoption_selected)
		{
			
			case effN_OPTION:
			{
				//effN=map(potAdd_a2x_avg,40,rangeA_M_off, 10, 240);
				
				byte val=10+aVal/16;
				if(effN!=val)
				{
					effN=val;
														leds[aVal/4]=CRGB::Red;			FastLED.show(); delay(10);
									
					if(millis()>nextCan_effN_change_t)
					//if(potAdd_a2x_avg_old==potAdd_a2x_avg)
					{
														leds[aVal/4+1]=CRGB::Red;			FastLED.show(); delay(10);
					
					#ifdef demo_enable
					brandom_demo=false;
					#endif
					banimate=false;

					change_slot(effN);
					nextCan_effN_change_t=millis()+800;
					//nextCanInputRead_t=millis()+200;//!! nextCanPotRead
					}
				}
			}
			break;
			
			case effSpeed_OPTION:
			 effSpeed=aVal;
			 //nextCanInputRead_t=millis()+10;
			break;		
			
			case effLength_OPTION:
			 effLength=aVal;
			 //nextCanInputRead_t=millis()+10;
			 
							if( (millis()/5000)%2==0 ) effFade=aVal;
			break;	
			
			case effRGB_OPTION:
			 effRGB=aVal/16;
			 //nextCanInputRead_t=millis()+50;
			break;
			
			case brightness_OPTION:
				gBrightness=aVal>10?aVal:2; //!!##
				//nextCanInputRead_t=millis()+30;
				setBrightness_gBrightness  //!!^ save BRIGHTNESS
			break;
			
			default: LCDoption_selected=0; //min
		}
	}
	//if(rangeNow<20) nextCanInputRead_t+=300; //! TODO slower upd when avg val slower changing, or increase avg_k
	potAdd_outOffRange_skipChanges:
	;
	}
} //pot
#endif

#endif
//============================================= display LCD
  //#if defined (keypad1602) || defined (LCD2004_i2c) || defined (SerialControl)  || defined (tst) 
//	if(bNeed_display_upd) display_upd();
 // #endif
//=============================================
 // il++;
 
	#ifdef debugSerialMemoryHeap
		EVERY_N_SECONDS(1) {
		  Serial.print( F("Heap: ") ); Serial.println(system_get_free_heap_size());
		}
	#endif
}