
int pos_txt    = mw;
int pass = 0;
const uint16_t colors_4matrix[] = { matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(0, 0, 255) };

String utf8rus(String source) //need glcdfont.c replace ?somewhere
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}

void text_test()
{
	//Serial.print(millis());Serial.print(" ");Serial.println();
	
	
  matrix->fillScreen(0);
  //matrix->setCursor(pos_txt, 0);
  matrix->setCursor(effLength-30, 0);

/*
  char Str1[256];
   
  for(int i=0;i<256;i++)
	  {
		  Str1[i]=char(i);
	  }

	  String mystring(Str1); //nw
	  
*/

  switch(indexOrBits/10)
  {
	  
	   //case 0: matrix->print(mystring); break;
	   //case 1: matrix->print(Str1); break;
	   
	   case 0:  matrix->print(utf8rus(String(char(i_eff/10)))); break; //char
	   case 1:  matrix->print(char(i_eff/10)); break; //char

	   //case 3:  matrix->print(String(i_eff/10)); break; //print number
	  
	  

	  //case 1: matrix->print(F("Howdy")); break;
	  case 3: matrix->print(F("Happy New Year")); break;
	  
	  //http://arduino.ru/forum/programmirovanie/rusifikatsiya-biblioteki-adafruit-gfx-i-vyvod-russkikh-bukv-na-displei-v-kodi#comment-136158
	  //http://arduino.ru/forum/programmirovanie/rusifikatsiya-biblioteki-adafruit-gfx-i-vyvod-russkikh-bukv-na-displei-v-kodi?page=8
	  case 4: matrix->print(utf8rus("Слава Богу за всё!")); break;
	  case 5: matrix->print(utf8rus(F("Слава Богу за всё!"))); break;
	 // case 3: matrix->print(utf8rus("Тест")); break;
	  case 6: matrix->print(R"(C HOBIdM roDo/\/\)"); break;
	  //case 3: matrix->print(F("Панки хой!╕")); break;
	 
	 //http://1337translate.blogspot.com/
	 //https://1337.me/
	  
  }
  
  /*
  if(--pos_txt < -36) { //anim
    pos_txt = matrix->width();
    if(++pass >= 3) pass = 0;
    //matrix->setTextColor(colors_4matrix[pass]); //this prevent colorize it. It just not changed
  }
*/
	for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
	{
		//if(leds[i].r!=0 &&leds[i].g!=0&&leds[i].b!=0) // !=CRGB::Black  comparison only with const var   end https://forum.arduino.cc/index.php?topic=385711.0
		
		//if(i>0 && i<NUM_LEDS-2)
		//if(leds[i].r+leds[i].g+leds[i].b!=leds[i+1].r+leds[i+1].g+leds[i+1].b )
			
		if(leds[i].r>10 || leds[i].g>10 || leds[i].b>10)
		{
			if(indexOrBits%2)
				leds[i]+=CHSV( gHue+ beatsin8(22,0,80),255,255);
			else
				leds[i]=CHSV( gHue+ beatsin8(22,0,80) +i%32*4 +i/32+i/4,255,255);
		}
	}

  delay(11);
}
