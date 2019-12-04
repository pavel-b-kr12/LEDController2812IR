//// Параметры эффектов
// Шаг разгорания звезды
#define RGB_ST_ADD_STEP        6//16
// Шаг угасания звезды
#define RGB_ST_DEC_STEP        1
// Период между тактами анимации, мс
#define RGB_ST_d          20

uint16_t rgb_stars_start()
{
	// Зажигаем новую цветную звезду, медленно гася все светодиоды
	DotPos = random8or16(NUM_LEDS); // Позиция звезды

	color1=CHSV(random8(),random8(),50); //start color
	color2=CHSV(random8(),random8(),255); //end color

	blend_amount=0;

	return (256 / RGB_ST_ADD_STEP) + 1; 
}

// Функция, реализующая очередной шаг анимации. Возвращает период до следующего шага
int16_t rgb_stars_tick()
{
	fadeToBlackBy(leds, NUM_LEDS,RGB_ST_DEC_STEP);
	
	 blend_amount=qadd8 (blend_amount,RGB_ST_ADD_STEP);
	// Зажигаем новую цветную звезду, медленно гася все светодиоды
	leds[DotPos]=blend(color1, color2, blend_amount);  //StepChangeColor((uint8_t *)&color2, (uint8_t *)&color1, RGB_ST_ADD_STEP);
	
	leds[DotPos2]+=CHSV(DotPos*11,200,30);
	if(random8()>254) DotPos2= random8or16(NUM_LEDS);
	
	leds[(DotPos2*DotPos)%NUM_LEDS]+=CHSV(DotPos*11,(DotPos2*DotPos)%4*64,50);
	
	
	// leds[0]=color1;
	// leds[1]=color2;
	// leds[2]=blend(color1, color2, blend_amount);
	// leds[3]=leds[DotPos2];
	return RGB_ST_d;
}