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

// String SendHTML()
// {
// #include "HTML_settings.h" //not work as .html , not work as R( #incl )
	// return str;
// }

//int get_sett_increment(String nm, int& ) //!

void handle_OnConnect() {

	#include "HTML_settings.h" //not work as .html , not work as R( #incl )
	server.send(200, "text/html", str); 
	//@https://esp8266.ru/forum/threads/kak-otpravit-ot-http-servera-web-server-na-esp8266-html-otvet-v-brauzer-kompjutera-fajlom.3136/
	//https://gist.github.com/spacehuhn/6c89594ad0edbdb0aad60541b72b2388
	//https://stackoverflow.com/questions/16348031/disable-scrolling-when-touch-moving-certain-element


//nw (not send 2nd part
/* split str with	
	)HTM";
const String str2=R"HTM(
*/
	// server.setContentLength(str.length() + str2.length());
	// server.send(200,"text/html",str);       //Initial send includes the header
	// server.sendContent(str2);              //Any subsequent sends use this function
}

void handle_NotFound(){
	server.send(404, "text/plain", "404");
}
#ifdef PWM_enabled
int PWM_ps_enabled=0;
void handle_pwm() {
	/*
	if (server.hasHeader("User-Agent")) {
    Serial.println(server.header("User-Agent"));
	//Mozilla/5.0 (Linux; Android 4.4.2; V8 Build/KOT49H) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/30.0.0.0 Mobile Safari/537.36
  }
  */

 

	String arg = server.arg("pp");
	if(arg.length() != 0)
	{
								//Serial.print(arg);Serial.print(" ");Serial.println();
		
		int val=arg.toInt();
		PWM_ps_enabled=val;

		for(byte p=0;p<16;p++)
		{	
			int mask = 1 << p; // gets the 6th bit

			if ((val & mask) != 0) {
				//!! enable
						leds[p]=CRGB::Orange;
				//enable PWM // bit is set
			} else {
						leds[p]=CRGB::Blue;
				//off PWM // bit is not set
			}
						FastLED.show(); anim_next_t=millis()+500;
		}
	}
	
	arg =server.arg("pv"); //"5v0t14v1023t16v1013t43v92t55v33t96T98"; // //pv=5v0t14v1023t16v1013t43v92t55v33t96T98
	if(arg.length() != 0)
	{
								//Serial.print(arg);Serial.print(" ");Serial.println();
		byte i0=arg.indexOf('v');
		byte pn=atoi(arg.substring(0,i0).c_str());//atoi ret 0 on error      stoi exeption
					if(pn>NUM_DIGITAL_PINS) return;
		pwm_p_selected=pn;
		
					//Serial.println(pwm_p_selected);

		byte iT=arg.indexOf('T')+1;

					//Serial.println(arg.substring(iT));

		byte pwm_N=255;//N of obj in list
		for(byte i=0;i<PWM_E;i++)
		{
			if(dimmers_ps[i]==pwm_p_selected)
			{
				pwm_N=i;												//Serial.println("loop_d ");  Serial.println(oSaveObjDimmers[pwm_N].loop_d);
				oSaveObjDimmers[pwm_N].loop_d=atoi(arg.substring(iT).c_str())*100; //10x, so 100 is 10sec for
																		// Serial.println("loop_d now: ");  Serial.println(oSaveObjDimmers[pwm_N].loop_d);
			}
		}
		

		for(byte i=0, ns_v=i0, ns_t=11;i<pwm_vsE && ns_v<iT-1;i++) //or only ns_v<iT-1  so we can set new NUM of Points 
		{
			ns_t= arg.indexOf('t',ns_v);
			uint16_t v=atoi(arg.substring(ns_v+1,ns_t).c_str());

			if(ns_t>iT-5)
				ns_v=iT-1;
			else	ns_v= arg.indexOf('v',ns_t);
			uint16_t t=atoi(arg.substring(ns_t+1,ns_v).c_str());
			
			if(pwm_N<17) //obj available in list, can be saved
			{ 
				oSaveObjDimmers[pwm_N].pwm_vs[i]=v;
					//Serial.print("ns_t");Serial.print(" ");
					//Serial.print(ns_t);Serial.print(" ");
					// Serial.print(arg.substring(ns_v,ns_t));Serial.print(" ");
					// Serial.print(pwm_vs[i]);Serial.print(" ");
				oSaveObjDimmers[pwm_N].pwm_ts[i]=t;
					//Serial.print("ns_v");Serial.print(" ");
					//Serial.print(ns_v);Serial.print(" ");
					// Serial.print(arg.substring(ns_t,ns_v));Serial.print(" ");
					// Serial.print(pwm_vs[i]);Serial.print(" ");
					// Serial.println();
					
					leds[60+i]=CHSV(oSaveObjDimmers[pwm_N].pwm_ts[i],255,255);
					leds[80+i]=CHSV(oSaveObjDimmers[pwm_N].pwm_vs[i]/4,255,255);
							// Serial.print(v);Serial.print("v set ");
							// Serial.print(t);Serial.print("t set ");Serial.println();
			}
			else //only set PWM
			{
				if(i==0)
				{
							//Serial.print(v);Serial.print(" ");Serial.println();
					// if(v==0) //##  digitalPinHasPWM   supportsDigitalInput  https://arduino.stackexchange.com/questions/33383/how-to-detect-pinout-at-run-time
						// digitalWrite(pwm_p_selected,0);
					// else
					//if( digitalPinHasPWM(pwm_p_selected))
						// alanogWrite(pwm_p_selected, constrain(v,0,1020));//0...1020
				}
			}
		}
					
					leds[(20+pwm_p_selected)%NUM_LEDS]+=CRGB::Yellow;
					leds[(40+oSaveObjDimmers[pwm_N].loop_d/4)%NUM_LEDS]+=CRGB::Green;
					FastLED.show(); anim_next_t=millis()+500;

						//Serial.print(pwm_p_selected);Serial.print("sel, ");Serial.println();
						//Serial.print(oSaveObjDimmers[pwm_N].loop_d);Serial.print("ld, ");Serial.println();
				saveDimmer(0);
	}
	// server.send(200, "text/html",
}
#endif
void handle_pin_sequencer() {
	
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


#ifdef WiFi_ControlHTMLpage_switch_p //switch WiFi with btn
#define LED_onBoard_p		2 //HTML server status //ESP32 = 2
//bool LED_onBoard_active=false;
bool bServerOn=false; // ##release## false so it not affect/ed by possible(?) net problems
long nextCanCheckBtn_t=1000;
#elif defined(offWiFiAfter2min) //switch WiFi off automatically
bool bServerOn=true;
#endif

void setupHTML() {
	WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(100);

	server.on("/", handle_OnConnect);
	server.on("/sett", handle_sett);
	#ifdef PWM_enabled
	server.on("/pwm", handle_pwm); //! add alias dimmer
	#endif
	#ifdef PinSequencer_enabled
	server.on("/pin_sequencer", handle_pin_sequencer); //! renm blink
	#endif
	server.on("/p", handle_p);
	server.onNotFound(handle_NotFound);
	
			// const char * headerkeys[] = {"User-Agent", "Cookie"} ;
			// size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
			// server.collectHeaders(headerkeys, headerkeyssize );
	
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

	if(bServerOn) server.handleClient();
	#elif defined( offWiFiAfter2min)
		if(bServerOn)
		{
			if(millis()<2*60*1000) server.handleClient();
			else
			{
				 server.stop();
				 bServerOn=false;
			}
		}
	#else
		server.handleClient();
	#endif
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
		Udp.begin(portServer); //???????????###### need this to work HTML on ESP(? don't remember waht MCU) 
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
