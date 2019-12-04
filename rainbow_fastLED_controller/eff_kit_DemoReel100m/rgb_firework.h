#define RGB_FW_STEP_NUM                3

//// Параметры эффектов
// Яркость цветной точки
#define RGB_FW_DOT_BRIGHTNESS          50
// Степень линейного замедления движения цветной точки (в мс/шаг движения)
#define RGB_FW_DOT_SLOWDOWN            2 //2
// Ширина шлейфа от цветной бегущей точки (скорость потухания точек)
#define RGB_FW_DOTSNUM_FADING          (NUM_LEDS / 8)
// Радиус белой вспышки в "салюте"
#define RGB_FW_FLASH_RADIUS            20
// Величина обратная скорости появления вспышки (период в мс)
#define RGB_FW_FLASH_PERIOD            5
// Яркость белой вспышки
#define RGB_FW_FLASH_BRIGHTNESS        255
// Шаг "ряби" при затухании вспышки
#define RGB_FW_NOISE_STEP              10
// Шаг затухания ленты
#define RGB_FW_FADEOUT_STEP            1
// Период затухания в мс
#define RGB_FW_FADEOUT_PERIOD          6

long fly_end_t;
long fly_0_t;

void rgb_firework_tick()
{
  switch(eff_stage)
  {
	 case 0:
	  {
	   // Начальная позиция цветной точки
		DotPos = 0;
		
		// Докуда будет бежать цветная точка
		fly_0_t=millis();
		fly_end_t=millis()+800+random8()*4;
		//var2 = (NUM_LEDS / 4) + (random8or16() % (NUM_LEDS - RGB_FW_FLASH_RADIUS - (NUM_LEDS / 4)	-2));
		
		// Выбираем случайный цвет
		color1.r = 0; color1.g = 0; color1.b = 0; 
		switch (random8() % 6)
		{
		  case 0: 
			color1.r = RGB_FW_DOT_BRIGHTNESS; 
			break;
		  case 1: 
			color1.g = RGB_FW_DOT_BRIGHTNESS; 
			break;
		  case 2: 
			color1.b = RGB_FW_DOT_BRIGHTNESS; 
			break;
		  case 3: 
			color1.r = color1.g = RGB_FW_DOT_BRIGHTNESS; 
			break;
		  case 4: 
			color1.r = color1.b = RGB_FW_DOT_BRIGHTNESS; 
			break;
		  case 5: 
			color1.g = color1.b = RGB_FW_DOT_BRIGHTNESS; 
			break;
		}
						
		eff_stage++;
	  }
	  break;
	  
	   // Летит цветная точка
	  case 1:
	  {
		fadeToBlackBy(leds, NUM_LEDS,2);//RGB_FW_DOT_BRIGHTNESS / RGB_FW_DOTSNUM_FADING
		  
		if(millis()/1024%2)
		{
		  for(byte i=0;i<3;i++)
			if(random8()> map(DotPos, 0, NUM_LEDS, 0, 255)) DotPos++; // slowdown
		
		DotPos=constrain(  DotPos,0,NUM_LEDS-1); //! slowdown     DotPos
		}
		else
		{
			DotPos=constrain(  map(millis(),fly_0_t,fly_end_t,0,NUM_LEDS-10),0,NUM_LEDS-1); 
		}
		  
		leds[DotPos]=color1;
		
							// fill_solid(leds,NUM_LEDS,color1);
		
		if(10+random8()> map(DotPos,0,NUM_LEDS-10, 400, 5))
		{
			eff_stage++;
			var1=0;
		}
	  }
	  break;
	  
	  case 2:
	  {

		for(byte i=0;i<random8(4);i++)
		{
		// Вспышка разжигается вперёд
		CRGB c= 
		(millis()/1024%2)?
		CHSV(random8(),RGB_FW_FLASH_BRIGHTNESS,RGB_FW_FLASH_BRIGHTNESS):
		CHSV(
		(millis()/1224%2)?random8():gHue2,
		(millis()/1224%2)?random8()/8:(128+random8(133)),
		random8()>100?RGB_FW_FLASH_BRIGHTNESS:random8()
		);
		
		leds[(DotPos+var1)%NUM_LEDS]+=c;//    ledstrip_add_3color(DotPos + var1,
		// Вспышка разжигается назад
		leds[(DotPos-var1)%NUM_LEDS]+=c;//    ledstrip_add_3color(DotPos - var1, 

		var1++;
		if(var1>RGB_FW_FLASH_RADIUS)
		{
			eff_stage++;
			eff_ticks=0;
		}
		}
	  }
	  break;
	  case 3:  // Затухание вспышки
	  {
		// Делаем небольшую рябь при затухании вспышки
		int Val = DotPos - RGB_FW_FLASH_RADIUS + 1 + (rand() % ((RGB_FW_FLASH_RADIUS * 2) - 1));
		if (rand() & 1)
			leds[Val%NUM_LEDS]+=CRGB(RGB_FW_NOISE_STEP,RGB_FW_NOISE_STEP,RGB_FW_NOISE_STEP);//      ledstrip_add_3color(Val, RGB_FW_NOISE_STEP, RGB_FW_NOISE_STEP, RGB_FW_NOISE_STEP);
		else
			leds[Val%NUM_LEDS]-=CRGB(RGB_FW_NOISE_STEP,RGB_FW_NOISE_STEP,RGB_FW_NOISE_STEP);//      ledstrip_dec_3color(Val, RGB_FW_NOISE_STEP, RGB_FW_NOISE_STEP, RGB_FW_NOISE_STEP);

		// Плавное затухвание всех светодиодов
		fadeToBlackBy(leds, NUM_LEDS,RGB_FW_FADEOUT_STEP);

		eff_ticks++;
		if(eff_ticks>220)  
		{
			if(random8()>250)	eff_stage++;
		}
	  }
	  break;
	  
	  default:
	  eff_stage=0;
	   break;
	  
  }
  
  gHue2++;
}
