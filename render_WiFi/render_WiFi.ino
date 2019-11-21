const byte MCU_N = 3;
const byte WiFi_chennel = 7; //change if byzy //! autoselect


//#define tst
#ifdef tst
	bool bSerPrint=true;
#endif
#define edge_tst	1 //print only this edge info

#define gBrightness	255


const uint16_t NUM_LEDS_edge  = 145;
const uint16_t  NUM_LEDS_mcu = NUM_LEDS_edge*3;//300*3//145*3	//1800/4


#include "FastLED.h"
CRGB leds[NUM_LEDS_mcu];

#define Cube4MCU
#ifdef Cube4MCU
	#define CubeXp		2
	#define CubeYp		3
	#define CubeZp		4 //tst kit

	#include "Cube_edges_arrays.h"
#else
	#define LEDp		4
#endif

#define BUFF_SIZEudp	NUM_LEDS_edge*3+4 //packetBuffer


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP Udp;
const char* ssid = "c82_tst";
const char* password = "12345678900";

unsigned int portServer = 8888;
unsigned int portClient = 8888;

#define packetBufferSize	NUM_LEDS_edge*3+4
char packetBuffer[packetBufferSize];//[145*3+4];





//-----------------------------------------------------

#define MODE_DEMO				0
#define MODE_SETTINGS_CONTROL	1
#define MODE_RECIEVE_LEDs		2
byte control_mode=0;

void (*anim_f)();
long change_mode_Demo_next_t=0;
long change_mode_Demo_next_dt=5000;


byte eff_N=0;
void eff_next()
{
	eff_N++;
	change_mode(eff_N);
}


void fillCornersGrad()
{
	//Serial.println("fillCorners");
	
	for(int i=0;i<NUM_LEDS_edge;i++)
	{
		byte b=map(i,0,NUM_LEDS_edge,255,0);
		ledsX[i]=CHSV(MCU_N*50+0,255,b);
		ledsY[i]=CHSV(MCU_N*50+7,255,b);
		ledsZ[i]=CHSV(MCU_N*50+14,255,b);
	}
}

void fillCornersGrad_flash_notSync()
{
	//Serial.println("fillCorners");
	byte	r=random8();
	if(random8()>250)
	for(int i=0;i<NUM_LEDS_edge/8;i++)
	{
		byte b=map(i,0,NUM_LEDS_edge/8,255,50);
		ledsX[i]=CHSV(r,110,b);
		ledsY[i]=CHSV(r,110,b);
		ledsZ[i]=CHSV(r,110,b);
	}
	else FastLED.clear();
}


void moveOutAllRemainFirst()
{
	for(int i = NUM_LEDS_edge-1; i >0 ; i--) 
	{
		ledsX[i]=ledsX[i-1];
		ledsY[i]=ledsY[i-1];
		ledsZ[i]=ledsZ[i-1];
	}
}
void moveAll() //cyclic
{
	// CRGB t=leds[NUM_LEDS-1];
	// moveOutAllRemainFirst();
	// leds[0]=t;
}
void moveOutAll()
{
	moveOutAllRemainFirst();
	ledsX[0]=0;
	ledsY[0]=0;
	ledsZ[0]=0;
}

void fillCorners_spawnSeparators_move()
{			//Serial.println("fillCorners_spawnSeparators_move");
	moveOutAll();
	
	byte r=random8();
	byte b=r>200?255:0;
	
	ledsX[0]=CHSV(50+MCU_N*40+random8(10),255,b);
	ledsY[0]=CHSV(50+MCU_N*40+random8(10),255,b);
	ledsZ[0]=CHSV(50+MCU_N*40+random8(10),255,b);

}

//! прямые выходят  move axis, щбратные осям - входят. В начале вспышка

//! mover seeder

//!cell multiple rand hitters

//cell multiple rand hitters colorize by speed. Incr speed on hit




void testRGB()
{
	FastLED.clear();

	
	for(int i=0;i<NUM_LEDS_edge-10;i+=10)
	{
		ledsX[i+0]=CRGB(255,0,0);
		ledsY[i+1]=CRGB(0,255,0);
		ledsZ[i+2]=CRGB(0,0,255);
	}
	
	ledsX[4]=CRGB(255,255,255);
	ledsY[4]=CRGB(255,255,255);
	ledsZ[4]=CRGB(255,255,255);
}
void test1MoveFromCorner()
{			//Serial.println("test1MoveFromCorner");
	moveOutAll();
	
	EVERY_N_MILLISECONDS(500)
	{
		ledsX[0]=CRGB(255,0,0);
		ledsY[0]=CRGB(0,255,0);
		ledsZ[0]=CRGB(0,0,255);
	}
}




//-----------------------------------------------------

void change_mode(byte N)
{
	//Serial.println("ch");
	switch(N)
	{
	case 0:	anim_f=testRGB; change_mode_Demo_next_dt=1500;	break;
	case 1:	anim_f=moveOutAll; change_mode_Demo_next_dt=500;	break;
	case 2:	anim_f=test1MoveFromCorner; change_mode_Demo_next_dt=5000;	break;
	case 3:	anim_f=moveOutAll; change_mode_Demo_next_dt=500;	break;
	case 4:	anim_f=fillCornersGrad; change_mode_Demo_next_dt=5000;	break;
	case 5:	anim_f=moveOutAll; change_mode_Demo_next_dt=500;	break;
	case 6:	anim_f=fillCornersGrad_flash_notSync; change_mode_Demo_next_dt=5000;	break;
	case 7:	anim_f=moveOutAll; change_mode_Demo_next_dt=500;	break;
	case 8:	anim_f=fillCorners_spawnSeparators_move; change_mode_Demo_next_dt=5000;	break;

	default:	eff_N=0;change_mode(eff_N);	break;
	}
	//Serial.println("ch ed");
}

//-----------------------------------------------------


void setup()
{

	WiFi.begin(ssid, password,WiFi_chennel);//! choose chennel by server SSID save  https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/scan-examples.html
	WiFi.mode(WIFI_STA);
	WiFi.config(IPAddress(192, 168, 4, 10+MCU_N), IPAddress(192, 168, 4, 1), IPAddress (255, 255, 255, 0)); //this, server , Subnet
	Udp.begin(portClient); //localPort
	// #ifdef use_ESP_WiFi_off
	// 	WiFi.mode( WIFI_OFF );
	// 	WiFi.forceSleepBegin();
	// #endif

#if defined(tst)
	Serial.begin(1000000);
#endif

 #ifdef Cube4MCU

	FastLED.addLeds<WS2812B, CubeXp, GRB>(ledsX,NUM_LEDS_edge);
	FastLED.addLeds<WS2812B, CubeYp, GRB>(ledsY,NUM_LEDS_edge);
	FastLED.addLeds<WS2812B, CubeZp, GRB>(ledsZ,NUM_LEDS_edge);
	//== //!^
	// FastLED.addLeds<WS2812B, CubeXp, GRB>(leds, 0, NUM_LEDS_edge);
	// FastLED.addLeds<WS2812B, CubeYp, GRB>(leds, NUM_LEDS_edge, NUM_LEDS_edge);
	// FastLED.addLeds<WS2812B, CubeZp, GRB>(leds, NUM_LEDS_edge*2, NUM_LEDS_edge);
	// #if defined(tst)
		// Serial.print("cube edge of: ");	Serial.println(NUM_LEDS_edge);
	// #endif
 #else
	FastLED.addLeds<WS2812B, LEDp, GRB>(leds, NUM_LEDS_mcu);
 #endif


#if defined(tst)
	
	Serial.print("wifi render:");	Serial.println(MCU_N);
	
	FastLED.setBrightness( gBrightness );
	FastLED.clear();
	
	ledsX[0]=CRGB(255,255,255);
	ledsY[0]=CRGB(255,255,255);
	ledsX[0]=CRGB(255,255,255);
	ledsX[1]=CRGB(255,0,0);
	ledsY[2]=CRGB(0,255,0);
	ledsZ[3]=CRGB(0,0,255);
	FastLED[0].showLeds(gBrightness);
	FastLED[1].showLeds(gBrightness);
	FastLED[2].showLeds(gBrightness);
	FastLED.show();
	delay(1000);
	
	// for(int i=0;i<NUM_LEDS_mcu;i+=5)
	// {
		// leds[i]=CRGB::Yellow;
		// FastLED.show();
		// delay(10);
		// leds[i]=CRGB::Gray;
		// FastLED[0].showLeds(gBrightness);
		// FastLED[1].showLeds(gBrightness);
		// FastLED[2].showLeds(gBrightness);
		// delay(10);
	// }
	// delay(1000);
	// FastLED.clear();
	

	

	//for(int edge=0;edge<3;edge++)
	{
		for(int i=0;i<NUM_LEDS_edge;i++)
		{
			byte b=map(i,0,NUM_LEDS_edge,255,0);
			byte s=i%2?55:255;
			
			ledsX[i]=CHSV(0,s,b);
			ledsY[i]=CHSV(80,s,b);
			ledsZ[i]=CHSV(160,s,b);
			FastLED.show();
			delay(10);
		}
	}
	delay(2000);
	FastLED.clear();
#endif

	anim_f=testRGB;
	
	//Serial.print("run:");	Serial.println();
}




long last_got_t=0;
bool bPause_SendPixels_to_Serial=true;
byte ilByte_from_server_last=0;

long switch_to_DEMO_dt=1000;
long switch_to_DEMO_at_t=0;

byte tst_pos=0;

byte il=0;
byte il_serv_last=0;

void loop()
{

	int packetSize = Udp.parsePacket();
	if (packetSize>0)
	{
		//Serial.print(packetSize); Serial.print(" "); Serial.println(control_mode);
		if (packetSize>1 && packetSize<=20) //got settings
		{
			switch_to_DEMO_at_t=millis()+switch_to_DEMO_dt;
			control_mode=MODE_SETTINGS_CONTROL;
			
			int len = Udp.read(packetBuffer, packetBufferSize); //##packetSize
			

			//int server_msg_N=packetBuffer[1];
			
			//anim_f
			
		}
		else
		if (packetSize>20)
		{
			switch_to_DEMO_at_t=millis()+switch_to_DEMO_dt;
			control_mode=MODE_RECIEVE_LEDs;
			
			int len = Udp.read(packetBuffer, BUFF_SIZEudp); //1800*3+
			if(len<BUFF_SIZEudp) return;
			//if (len > 0) packetBuffer[len-1] = 0;//!?
			
			byte mcu=packetBuffer[0]; 
			
			
			byte edge=packetBuffer[1];
			
			if(mcu<8) //not the test mode						
			{							
				if(edge<3)
				{
					memcpy8( &leds[NUM_LEDS_edge*edge], &packetBuffer[3], NUM_LEDS_edge*3); //!!tst direct assign to CRGBSet without memcpy
					
					/*
					//---------------------
					FastLED.clear();
					if(edge==1) //test edge
					{
						byte ilByte_from_server=packetBuffer[2];	Serial.println(ilByte_from_server);
						if( ilByte_from_server==ilByte_from_server_last+1)
						{ //detect lost packets
							tst_pos++; if(tst_pos>NUM_LEDS_edge-1) tst_pos=0;
							ledsY[tst_pos]=CRGB::Green;
							//Serial.print(ilByte_from_server-ilByte_from_server_last); Serial.print(" ");
						}
						else if( ilByte_from_server>ilByte_from_server_last+1)
						{
							if(tst_pos==0) tst_pos=NUM_LEDS_edge-1;
							else tst_pos--; 
							ledsY[tst_pos]=CHSV( map(ilByte_from_server-(ilByte_from_server_last+1),1,5,80,0) ,255,255);
							
							//Serial.println(ilByte_from_server-ilByte_from_server_last);
						}
						
						ilByte_from_server_last=ilByte_from_server;			
					}
					*/
					
					//long t=millis();
					//leds[1]=CHSV((t-last_got_t)*32,255,255);
					//Serial.println(t-last_got_t);
					//last_got_t=t;
					//---------------------
					FastLED[edge].showLeds(gBrightness); //https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
				}
				//else error
			}
			else{//test mode	
				
				byte il_serv=packetBuffer[2];

				if(edge==edge_tst)
				{
					#ifdef tst
					if(bSerPrint)
					{			
						// Serial.print(bGood); Serial.print(" "); 
						// Serial.print(packetSize); Serial.print(" "); 
						// Serial.print(BUFF_SIZEudp); Serial.print(" ");      
						// Serial.print(len); Serial.print(" "); 
						
						//Serial.print(edge); Serial.print(" ");
						Serial.print(il_serv); Serial.print(" "); 
						Serial.println(il_serv-(il_serv_last+1));
					}
					#endif
					
					//if(bLed)
					{
						fadeToBlackBy(ledsZ, NUM_LEDS_edge, 30);
						if(il_serv<NUM_LEDS_edge)
						{
							//FastLED.clear();
							
							for(byte i=il_serv_last+1;i<il_serv;i++)
							{
								//leds[edge*NUM_LEDS_edge+i]=CRGB(  111 , 0 ,222);
								//==
								ledsZ[i]==CRGB(  111 , 0 ,222);
							}

							bool bGood=(il_serv==(il_serv_last+1));
							ledsZ[il_serv]=bGood?CRGB(  0 , 255 ,0): CRGB(  255 , 0 ,0);
							//FastLED.show();
							
						}
						FastLED[edge].showLeds(gBrightness);
					}

					il_serv_last=il_serv;
				}
				
			}
			
			//---------------------------------------------------- print LEDs
			//print_LEDs();
		}
		
	}
	
	else //packetSize<   == no packet or error
	{
		if(control_mode==MODE_DEMO)
		{
			if(millis()>change_mode_Demo_next_t)
			{
				eff_next();
				change_mode_Demo_next_t=millis()+change_mode_Demo_next_dt;
				//Serial.println(eff_N);
			}

			anim_f();
			yield();
			
			FastLED[0].showLeds(gBrightness);
			FastLED[1].showLeds(gBrightness);
			FastLED[2].showLeds(gBrightness);
			//FastLED.show();
		}
		else
		{
			//!! && not bPause
			if(millis()>switch_to_DEMO_at_t) //possible loss of connection, so show demo
			{
				control_mode=MODE_DEMO;
			}

			//!! switch to demo timeout
		}
		
	}

	
}


void print_LEDs()
{
	//sw pause
	if(Serial.available()>0)
	{
		if(Serial.read()=='p')	bPause_SendPixels_to_Serial=!bPause_SendPixels_to_Serial;

		while(Serial.available()>0) Serial.read();
	}
	if(bPause_SendPixels_to_Serial) return;
	
	
	#define NUM_LEDS	NUM_LEDS_mcu
	
	#define PRINT__			Serial.write(111);Serial.write(166);Serial.write(77);//header
	#define PRINT_leds		Serial.write(133);
	#define PRINT_totall	Serial.write(122);
	#define PRINT_settings	Serial.write(99);
	uint8_t *p;
	PRINT__
	//if(bPrintPixels)
	{
		PRINT_leds

		uint16_t fps=LEDS.getFPS();
		p = (uint8_t*) &fps;
		Serial.write(p,2);

		uint16_t size=NUM_LEDS*3; //! NUM_LEDS range
		p = (uint8_t*) &size;
		Serial.write(p,2);
		Serial.write((uint8_t*)leds, size);
	}
}