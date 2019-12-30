//#define WIDTH 32
//#define bMatrixZigZag 0
//#define HEIGHT 8

// **************** НАСТРОЙКИ ****************
#define MIRR_V 0          // отразить текст по вертикали (0 / 1)
#define MIRR_H 0          // отразить текст по горизонтали (0 / 1)

#define TEXT_HEIGHT 0     // высота, на которой бежит текст (от низа матрицы)
#define LET_WIDTH 5       // ширина буквы шрифта
#define LET_HEIGHT 8      // высота буквы шрифта
#define SPACE 1           // пробел



// **************** НАСТРОЙКА МАТРИЦЫ ****************
#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)

#else
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif
// получить номер пикселя в ленте по координатам
uint16_t getPixelNumber(int8_t x, int8_t y) {
  if ((THIS_Y % 2 == 0) || !bMatrixZigZag) {               // если чётная строка
    return (THIS_Y * _WIDTH + THIS_X);
  } else {                                              // если нечётная строка
    return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
  }
}

// интерпретатор кода символа в массиве fontHEX (для Arduino IDE 1.8.* и выше)
uint8_t getFont(uint8_t font, uint8_t row) {
  font = font - '0' + 16;   // перевод код символа из таблицы ASCII в номер согласно нумерации массива
  if (font <= 90)	return pgm_read_byte(&(fontHEX[font][row]));     // для английских букв и символов
	else if (font >= 112 && font <= 159) { //rus
					return pgm_read_byte(&(fontHEX[font - 17][row]));
  } else if (font >= 96 && font <= 111) {
					return pgm_read_byte(&(fontHEX[font + 47][row]));
  }
					return 0;
}


void drawLetter(uint8_t letter_i, uint8_t letter, int16_t text_offset, CRGB color) {
  int8_t start_pos = 0, finish_pos = LET_WIDTH;
  int8_t LH = LET_HEIGHT;
  if (LH > HEIGHT) LH = HEIGHT;
  int8_t text_offset_y = (HEIGHT - LH) / 2;     // по центру матрицы по высоте
  
								  CRGB letterColor;
								  if (color.r == 0 && color.g==0&& color.b==0) letterColor = CHSV(byte(text_offset * 10), 255, 255);
								  else if (color.r == 1 && color.g==1&& color.b==1) letterColor = CHSV(byte(letter_i * 30), 255, 255);
								  else letterColor = color;

  if (text_offset < -LET_WIDTH || text_offset > WIDTH) return;
  if (text_offset < 0) start_pos = -text_offset;
  if (text_offset > (WIDTH - LET_WIDTH)) finish_pos = WIDTH - text_offset;

  for (int8_t i = start_pos; i < finish_pos; i++)
  {
    int thisByte;
    if (MIRR_V) thisByte = getFont((int8_t)letter, LET_WIDTH - 1 - i);
    else thisByte = getFont((int8_t)letter, i);

    for (int8_t j = 0; j < LH; j++)
	{
      boolean thisBit;

      if (MIRR_H) thisBit = thisByte & (1 << j);
      else thisBit = thisByte & (1 << (LH - 1 - j));

	  	// #ifdef textMATRIX_overlay //!
			// if(bTextOverlay) 
		// #endif
      // рисуем столбец (i - горизонтальная позиция, j - вертикальная)
      if (thisBit) leds[getPixelNumber(text_offset + i, text_offset_y + TEXT_HEIGHT + j)] = letterColor;
    }
  }
}


void fillString(String text, CRGB color) {
		int text_len=(LET_WIDTH + SPACE)*text.length()		-LET_WIDTH*12; //!?? LET_WIDTH*16  why need 
					text_offset=0-(millis()/110)%text_len;	//-effLength	 //!?? why need 0 (otherwice only 3 letters show and balack)		
  // if (loadingFlag) {
    // text_offset = WIDTH;   // перемотка в правый край
    // loadingFlag = false;    
// #if (SMOOTH_CHANGE == 1)
    // loadingFlag = modeCode == MC_TEXT && fadeMode < 2 ;
// #else
    // loadingFlag = false;        
// #endif
    // modeCode = MC_TEXT;
    // fullTextFlag = false;
  // }
  
  //if (scrollTimer.isReady()) {
  //if (millis()/100%20==0) //renew or scroll text
	  {
    byte i = 0, j = 0;
    while (text[i] != '\0') {
      if ((byte)text[i] > 191) {    // работаем с русскими буквами //?
        i++;
      } else
		{
			drawLetter(j, text[i], text_offset + j * (LET_WIDTH + SPACE), color);
			i++;
			j++;
		}
    }
    // fullTextFlag = false;

	
    ////// text_offset--;

    // if (text_offset < -j * (LET_WIDTH + SPACE)) {    // строка убежала  //##!!! text_offset = WIDTH; 	   or %text_w
      // text_offset = WIDTH + 3;
      /* fullTextFlag = true;*/
    // }
  }
}

