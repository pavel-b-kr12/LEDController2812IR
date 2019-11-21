//@@@ https://www.reddit.com/r/esp32/comments/dwlubl/how_to_increase_ap_max_connection/

const char* ssid = "ws2812";
const char* password = "0937002969";

#define returnToClient //to view current eff settings in HTML (in place of '?')

#ifdef use_ESP32
 #include <WiFi.h>
 #if defined(WiFi_ControlHTMLpage)
	 #include <WebServer.h>
	 WebServer server(80);
 #endif
#else
 #include <ESP8266WiFi.h>
  #if defined(WiFi_ControlHTMLpage)
	 #include <ESP8266WebServer.h>
	 ESP8266WebServer server(80);
  #endif
#endif


#if defined(WiFi_ControlHTMLpage)
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

String SendHTML()
{
#include "HTML_settings.h" //not work as .html , not work as R( #incl )
	return str;
}

//int get_sett_increment(String nm, int& ) //!

void handle_OnConnect() {
	server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
	server.send(404, "text/plain", "404");
}

void handle_sett() {
	//String arg = server.arg("effN");
	//if (arg.length() != 0) effN = arg.toInt();

	//Gets the value of the query parameter if available
	
	String arg = server.arg("effN");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effN_add();
		else
		if( val==0) effN_sub();
		else effN_set(val);
	}
	
	arg = server.arg("effSpeed");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effSpeed+=4;
		else
		if( val==0) effSpeed-=4;
		else effSpeed=val;
	}	
	
	arg = server.arg("effLength");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effLength+=4;
		else
		if( val==0) effLength-=2;
		else effLength=val;
	}	


	arg = server.arg("effSpeedH");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effSpeedH+=4;
		else
		if( val==0) effSpeedH-=4;
		else effSpeedH=val;
	}	
	
	arg = server.arg("effLengthH");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effLengthH+=4;
		else
		if( val==0) effLengthH-=2;
		else effLengthH=val;
	}
	
	arg = server.arg("effRGB");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effRGB+=1;
		else
		if( val==0) effRGB-=1;
		else effRGB=val;
	}		
	arg = server.arg("effFade");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) effFade+=4;
		else
		if( val==0) effFade-=1;
		else effFade=val;
	}		
	// byte gH;
	// byte gS;
	// byte gV;
	// CRGB gColor;
	// CRGB gColorBg;//! gHueBG == 0 ? White	== 255 ? black	
	arg = server.arg("gFade");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) gFade+=4;
		else
		if( val==0) gFade-=1;
		else gFade=val;
	}
	arg = server.arg("indexOrBits");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) indexOrBits+=1;
		else
		if( val==0) indexOrBits-=1;
		else indexOrBits=val;
	}	
	arg = server.arg("gDelay");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) gDelay+=4;
		else
		if( val==0) gDelay-=2;
		else gDelay=val;
		if(gDelay<6) gDelay=6; //##
	}
	arg = server.arg("gBrightness");	
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		if( val==1) gBrightness+=10;
		else
		if( val==0) gBrightness-=2;
		else gBrightness=val;
	}	
	//NUM_LEDS

	#ifdef save_load_enable
	arg = server.arg("s");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		save(val);
	}	
	
	arg = server.arg("l");
	if(arg.length() != 0)
	{
		int val=arg.toInt();
		load(val);
	}
	#endif	
	
	byte n=NUM_LEDS; //for ESP32
	#ifdef returnToClient
	server.send(200, "text/html", 
	
	"effN="+(String)effN+
	",effSpeed="+(String)effSpeed+
	",effSpeedH="+(String)effSpeedH+
	",effLength="+(String)effLength+
	",effLengthH="+(String)effLengthH+
	",effRGB="+(String)effRGB+
	",effFade="+(String)effFade+
	// "gH;
	// "gS;
	// "gV;
	//",gColor="+(String)
	//",gColorBg="+(String)
	",gFade="+(String)gFade+
	",indexOrBits="+(String)indexOrBits+
	",gDelay="+(String)gDelay+
	",gBrightness="+(String)gBrightness+
	",NUM_LEDS="+(String)n
	
	); //';' not working as separator, it became ','
	#endif
}


void handle_p() {
	bPause=!bPause;
	server.send(200, "text/html", "effN="+(String)effN); 
}


#ifdef WiFi_ControlHTMLpage_switch_p
#define LED_onBoard_p		2 //HTML server status //ESP32 = 2
//bool LED_onBoard_active=false;
bool bServerOn=false; // ##release## false so it not affect/ed by possible(?) net problems
long nextCanCheckBtn_t=1000;
#endif

void setupHTML() {
	WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(100);

	server.on("/", handle_OnConnect);
	server.on("/sett", handle_sett);
	server.on("/p", handle_p);
	server.onNotFound(handle_NotFound);
	
	//Serial.println("HTTP server start");

	#ifdef WiFi_ControlHTMLpage_switch_p
		pinMode(WiFi_ControlHTMLpage_switch_p, INPUT_PULLUP);
		pinMode(LED_onBoard_p,OUTPUT);
		if(bServerOn)
	#endif
		server.begin();
	
}


void loopHTML()
{
	#ifdef WiFi_ControlHTMLpage_switch_p
	if(millis()>nextCanCheckBtn_t)
	{
		nextCanCheckBtn_t=millis()+100;
		
		if( !digitalRead(WiFi_ControlHTMLpage_switch_p)  ) //btn pressed //wifi_softap_get_station_num()<=3 ||
		{
			bServerOn=!bServerOn;
			nextCanCheckBtn_t=millis()+1500;

			if(bServerOn)	server.begin();
			else			server.stop();
		}
		
		// light|blink LED based on bServerOn
			digitalWrite(LED_onBoard_p,bServerOn?HIGH:LOW); //light

		// if(bServerOn)
		// 	digitalWrite(LED_onBoard_p,LED_onBoard_active?HIGH:LOW);
		// else
		// 	digitalWrite(LED_onBoard_p,LOW);
		// LED_onBoard_active=!LED_onBoard_active; //blink

	}
	
	if(bServerOn)
	#endif
		server.handleClient();
}
#endif
//=========================================================================================


byte WiFi_chennel = 7; //change if byzy //! autoselect

#if defined(WiFi_SEND)
	#define NUM_CLIENTS		3
	byte Delay_WiFi=1; //1 is good for 3 CLIENTS Nodes @145*3 LEDs

	#if defined(Cube4MCU)
		#define packetBufferSize	NUM_LEDS_edge*3+4 //!!fix if not Cube
	#else
		#define packetBufferSize	NUM_LEDS*3+4
	#endif

	uint8_t packetBuffer[packetBufferSize];//[145*3+4];


	#include <WiFiClient.h> //? esp32

	#include <SPI.h>
	#include <WiFiUdp.h>


	unsigned int portServer = 8888;
	unsigned int portClient = 8888;
	WiFiUDP Udp;

	//IPAddress clientIP(192, 168, 4, 20);//239, 255, 255, 250);
	IPAddress ip_renders[NUM_CLIENTS];
#endif


void setup_wifi()
{
	WiFi.softAP(ssid, password, WiFi_chennel);

	#if defined(WiFi_SEND)
		Udp.begin(portServer);
		for(byte i=0;i<NUM_CLIENTS;i++)	ip_renders[i]=IPAddress(192, 168, 4, 10+i);
	#elif defined(enableUDP)
		Udp.begin(portServer); //???????????###### need this to work HTML
	#endif

	#if defined(WiFi_ControlHTMLpage)
		setupHTML();
	#endif
}

#if defined( WiFi_SEND)
byte ilByte=0;
void send_LEDs_over_WiFi()
{
	//int led_i=0;
	for(byte edge=0;edge<3;edge++)
	{
		#ifdef WiFi_ControlHTMLpage_switch_p
		for(byte mcu=0;mcu< ( bServerOn?(NUM_CLIENTS-1): NUM_CLIENTS  ) ;mcu++)
		#else
		for(byte mcu=0;mcu< NUM_CLIENTS;mcu++)
		#endif
		{
			
			//if(anim_f==test_RF) //we not set effN at startup, but only anim_f   //not this because anim_f declared after this, so avoid predeclarations
			if(effN==244)  //test connection packet loses
			//
			{
				packetBuffer[0] = 255;
				packetBuffer[2]=ilByte;
			}
			else
			{
				packetBuffer[0] = mcu;
				packetBuffer[2] = effN;
			}
			
			packetBuffer[1]=edge;
			
			#if defined(Cube4MCU)
				memcpy8( &packetBuffer[3], &leds[mcu*3*NUM_LEDS_edge + edge*NUM_LEDS_edge], NUM_LEDS_edge*3 ); // array layout is leds[xMCU0[], yMCU0[], zMCU0[], xMCU1[] ....], so each 4th is axis
			#else
				memcpy8( &packetBuffer[3], &leds[0], NUM_LEDS*3 ); //! test, ! send leds without memcpy
			#endif
			//==
			// for(byte i=1;i<NUM_LEDS_edge+1;i++, led_i++)
			// {
			// packetBuffer[i*3]=leds[led_i].r;
			// packetBuffer[i*3+1]=leds[led_i].g;
			// packetBuffer[i*3+2]=leds[led_i].b;
			// }
			yield();
			
			Udp.beginPacket(ip_renders[mcu], portClient);
			Udp.write(packetBuffer,packetBufferSize);
			
			//Udp.write(packetBuffer,3);
			//Udp.write(&leds[mcu*3*NUM_LEDS_edge + edge*NUM_LEDS_edge], NUM_LEDS_edge*3); //!! tst direct send leds
			
			Udp.endPacket();
			
			
			// long t=millis();
			// Serial.println(t-last_got_t);
			// last_got_t=t;
			
			//delay(5);
			yield();
			delay(Delay_WiFi); //^
		}
		//Delay_WiFi=gDelay;
		yield();
		delay(Delay_WiFi);
	}
	ilByte++;
}
#endif
