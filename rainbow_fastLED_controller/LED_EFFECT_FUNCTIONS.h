/* break long eff with input check:
#if defined(SerialSelect) || defined(SerialControl)
  checkSerial();
#endif
#ifdef IRkeypad
EVERY_N_MILLISECONDS( 40 )
{
  if (IRLremote.receiving()) return;
}
#endif
*/

//effN, spd, , length, , RGB, , time to from start to end value
// void animEff(byte N, byte spd0, byte spd9, byte length0,byte length9, byte chennels0,byte chennels9, byte time_d) //!!
// {

// }

// spd, , length, , RGB, , time to from start to end value, time to do 
// void animEffContinue(byte spd0, byte spd9, byte length0,byte length9, byte chennels0,byte chennels9, byte time1Cycle_d, byte time_d)
// {

	
// }


void fillStriped()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    // leds[i] = (
    //   ((byte)(i+i_eff/(effSpeed+1)))
    //   %effLength<(1+effLength2)
    //   )? gColor:gColorBg;

    leds[i] = beat8 (effSpeed,i*effLength)<88 ? gColor:gColorBg;
  }
}

void fillStripedFillRainbow()
{
  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    // leds[i] = (
    //   ((byte)(i+i_eff/(effSpeed+1)))
    //   %effLength<(1+effLength2)
    //   )? gColor:gColorBg;

    leds[i] = beat8 (effSpeed,i*effLength)<127 ? gColor:CHSV(beat8 (effSpeed,i*effLength),255,255);
  }
}

//------------------------------------------------------------------------------ fill fade
void fillFadeChangeAll()
{

  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,i_eff%255));

  if(i_eff%255 > effLength) //flash over effLength
  {
    ihue=random8();
    isat=random8();
  }
}
void fillFadeChangeAll_beat8()
{
  ibright=beat8(effSpeed);
  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,ibright));

  //if(i_eff%255 > effLength)  //other eff
  if(ibright > effLength) //flash above effLength
  {
    ihue=gHue;
    isat=random8();
  }
}

void fillFadeChangeAll_beatsin8()
{
  ibright=beatsin8(effSpeed,0);
  fill_solid(leds, NUM_LEDS, CHSV(ihue,isat,ibright));

  if(ibright <effLength) //flash under effLength
  {
    ihue=random8();
    isat=random8();
  }
}

//! BrightWave on pre=generated

//! Bright off from sides to central point 
//------------------------------------------------------------------------------

void fadeEvenUneven()
{
  ibright=beatsin8(effSpeed,0,255);
  byte ibright2=beatsin8(effSpeed,0,255,0,effLength);

  if(ibright<4)
  {
    if(random8()<32)  ihue= gHue;
  }
  else
  if(ibright2<4)
  {
    if(random8()<32)  thishue= random8();
  }

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
      leds[i] =i%2?
      CHSV(ihue,255,ibright): 
      CHSV(thishue,255,ibright2);
  }
}
void fadeEvenUnevenDif()
{
  if(i_eff%500==0) ihue= gHue;

  for(NUM_LEDS_type i=0;i<NUM_LEDS;i++)
  {
    if(i%2)
    {
      leds[i] = CHSV(ihue,255,beatsin8(effLength+effSpeed/4,0));
    }
    else
      leds[i] = CHSV(ihue+gHue,255,beatsin8(effLength,127));
  }
}


//! встречные столбы с разной частотой. Перекрытие цвета

//------------------------LED EFFECT FUNCTIONS------------------------


void random_burst() {                         //-m4-RANDOM INDEX/COLOR
  for(NUM_LEDS_type i=0;i<effSpeed/4+1;i++)
  {
	  leds[random(0, NUM_LEDS)] = CHSV(random(0, 255), thissat, random8()<effLength?255:0);
  }
  
  // for(NUM_LEDS_type i=0;i<effLength/10;i++)
  // {
	// leds[random(0, NUM_LEDS)] = CHSV(ihue, thissat, 0);
  // }
}

#ifndef saveMem
void bounce()
{
  if (bouncedirection == 0)
  {
    idex ++;
    if (idex == NUM_LEDS) {
      bouncedirection = 1;
      idex --;
    }
  }
  if (bouncedirection == 1) 
  {
    idex --;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
}
void color_bounce() {                        //-m5-BOUNCE COLOR (SINGLE LED)
  bounce();

  leds[idex] = CHSV(gHue, 255, 255);
  leds[idex/2] = CHSV(gHue+80, 255, 255);
  leds[idex/3] = CHSV(gHue+160, 255, 255);

  if(effSpeed>50)
  {
    leds[idex_last] = 0;
    leds[idex_last/2] = 0;
    leds[idex_last/3] = 0;

    idex_last=idex;
  }
  else
    fadeToBlackBy(leds, NUM_LEDS, effLength); //!! effSpeed affect gHue   make speedH separate
}

void color_bounc_HueByPos() {  //! differ with idex VS gHue  so can combine with prev eff (colorize option or effLength2)
  bounce();

  leds[idex] = CHSV(idex*effLength/16, 255, 255);   //!opt effLength/16
  leds[idex/2] = CHSV(idex*effLength/16+80, 255, 255);
  leds[idex/3] = CHSV(idex*effLength/16+160, 255, 255);

  if(effSpeed>60)
  {
    leds[idex_last] = 0;
    leds[idex_last/2] = 0;
    leds[idex_last/3] = 0;

    idex_last=idex;
  }
  else
    fadeToBlackBy(leds, NUM_LEDS, effSpeed);
}

void color_bounce_multiple() { //! move it far than NUM_LEDS
  bounce();

  for(byte i = 0; (i < effLength) && (i < NUM_LEDS); i++)
  {
    leds[idex/(1+i)] = CHSV(gHue+i*60, 255, 255);
  }

  if(effSpeed>80)
  {
    for(byte i = 0; (i < effLength) && (i < NUM_LEDS) ; i++)
    {
      leds[idex/(1+i)] = 0;
    }

    idex_last=idex;
  }
  else
    fadeToBlackBy(leds, NUM_LEDS, effSpeed); //!! effSpeed affect gHue   make speedH separate
}

#endif
CHSV lerpFadeReturn(byte n)
{
 return CHSV(lerp8by8(thishue,effSpeed,n), thissat, n);
}
void color_bounceFADE() {                    //-m6-BOUNCE COLOR (SIMPLE MULTI-LED FADE)
  bounce();
  thishue=effLength;

  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    if (i == idex) {
      leds[i] =lerpFadeReturn(255);
    }
    else if (i == iL1) {
      leds[i] = lerpFadeReturn( 150);
    }
    else if (i == iL2) {
      leds[i] = lerpFadeReturn( 80);
    }
    else if (i == iL3) {
      leds[i] = lerpFadeReturn( 20);
    }
    else if (i == iR1) {
      leds[i] = lerpFadeReturn( 150);
    }
    else if (i == iR2) {
      leds[i] = lerpFadeReturn( 80);
    }
    else if (i == iR3) {
      leds[i] = lerpFadeReturn( 20);
    }
    else {
      leds[i] = 0;
    }
  }
}

#ifndef saveMem

void ems_lightsONE() {                    //-m7-EMERGENCY LIGHTS (TWO COLOR SINGLE LED)
  idex++;
  if (idex >= NUM_LEDS) idex = 0;
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    if (i == idexR) {
      leds[i] = CHSV(thishue, 255, 255);
    }
    else if (i == idexB) {
      leds[i] = CHSV(thathue, 255, 255);
    }
    else {
      if(effSpeed>155 || i%(2+effLength/16)!=0) leds[i] = 0; //! black every i%(2  but if different Hue - (i+1)%(2 - so it fill different LEDs
    }
  }
  if(effSpeed<=155) fadeToBlackBy(leds, NUM_LEDS, effSpeed);
}

void ems_lightsALL() {                  //-m8-EMERGENCY LIGHTS (TWO COLOR SOLID)
  idex++;
  thishue=effLength;
  if (idex >= NUM_LEDS) idex = 0;
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;
  leds[idexR] = CHSV(thishue, 255, 255);
  leds[idexB] = CHSV(thathue, 255, 255);
}

void flicker() {                          //-m9-FLICKER EFFECT
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i] = CHSV(thishue, 255, random_bright);
    }
    FastLED.show();
    delay(random_delay); //!! if(random_delay>5) IR
  }
}
#endif

void pulse_one_color_all() {              //-m10-PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR  //! speed up
  if (bouncedirection == 0)
  {
    ibright++;
    if (ibright >= 255)
    {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1)
  {
    ibright --;
    if (ibright <= 1)
    {
      bouncedirection = 0;
    }
  }
  for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
    leds[i] = CHSV(thishue, 255, ibright);
  }
}

void pulse_one_color_all_rev() {           //-m11-PULSE SATURATION ON ALL LEDS TO ONE COLOR  //! speed up
  if (bouncedirection == 0)
  {
    isat++;
    if (isat >= 255)
    {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1)
  {
    isat --;
    if (isat <= 1)
    {
      bouncedirection = 0;
    }
  }
  for(NUM_LEDS_type idex = 0 ; idex < NUM_LEDS; idex++ ) {
    leds[idex] = CHSV(thishue, isat, 255);
  }
}

void fade_vertical() {                    //-m12-FADE 'UP' THE LOOP //! speed up
  idex++;
  if (idex > CENTER_TOP_INDEX) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 246)    ibright = 0;

  leds[idexA] = CHSV(thishue, 255, ibright);
  leds[idexB] = CHSV(thishue, 255, ibright);
}

void random_red() {                       //QUICK 'N DIRTY RANDOMIZE TO GET CELL AUTOMATA STARTED
  int temprand;
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0; leds[i].g = 0;
  }
}

#ifndef saveMem
void rule30() {                          //-m13-1D CELLULAR AUTOMATA - RULE 30 (RED FOR NOW)
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  NUM_LEDS_type iCW;
  NUM_LEDS_type iCCW;
  int y = 100;
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
}

void random_march() {                   //-m14-RANDOM MARCH CCW
  copy_led_array();
  NUM_LEDS_type iCCW;

  if(effLength<10) leds[0] = CHSV(random8(), 255, 255);
  else 
  leds[0] = CHSV(gHue*64/effLength, 255, 255);

  for(NUM_LEDS_type idex = 1; idex < NUM_LEDS ; idex++ ) {
    iCCW = adjacent_ccw(idex);
    leds[idex].r = ledsX[iCCW][0];
    leds[idex].g = ledsX[iCCW][1];
    leds[idex].b = ledsX[iCCW][2];
  }
  delay(effSpeed/8);
}

void rwb_march() {                    //-m15-R,W,B MARCH CCW
  copy_led_array();
  NUM_LEDS_type iCCW;
  idex++;
  if (idex > 2)   idex = 0;

  switch (idex) {
    case 0:
      leds[0]=effLength<10 ? CHSV(0,255,255) : CHSV((effLength<200? effLength : gHue)+idex*80 ,255,255);
      break;
    case 1:
      leds[0]=effLength<10 ? CHSV(0,0,255) : CHSV((effLength<200? effLength : gHue)+idex*80,255,255);
      break;
    case 2:
       leds[0]=effLength<10 ? CHSV(180,255,255)  : CHSV((effLength<200? effLength : gHue)+idex*80,255,255);
      break;
  }
  for(NUM_LEDS_type i = 1; i < NUM_LEDS; i++ ) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  delay(effSpeed/8); //!!
}

byte colorize()
{
  if(effLength>250) return idex; //* //! lerp cColor bgColor
  else
  if(effLength<5)   return gHue; //*
  else              return effLength;
}
void rgb_propeller() {                           //-m27-RGB PROPELLER
  idex++;
  thishue=colorize();

  NUM_LEDS_type ghue = (thishue + 80) % 255;
  NUM_LEDS_type bhue = (thishue + 160) % 255;
  NUM_LEDS_type N3  = NUM_LEDS_type(NUM_LEDS / 3);
  //NUM_LEDS_type N6  = NUM_LEDS_type(NUM_LEDS / 6);
  NUM_LEDS_type N12 = NUM_LEDS_type(NUM_LEDS / 12);
  for(NUM_LEDS_type i = 0; i < N3; i++ ) {
    NUM_LEDS_type j0 = (idex + i + NUM_LEDS - N12) % NUM_LEDS;
    NUM_LEDS_type j1 = (j0 + N3) % NUM_LEDS;
    NUM_LEDS_type j2 = (j1 + N3) % NUM_LEDS;
    leds[j0] = CHSV(thishue, 255, 255);
    leds[j1] = CHSV(ghue, 255, 255);
    leds[j2] = CHSV(bhue, 255, 255);
  }
  delay(effSpeed/8);//!!
}

void radiation() {                   //-m16-SORT OF RADIATION SYMBOLISH- //!fix nwp  https://github.com/4tronix/SmartBadge/blob/master/Demo.ino
  NUM_LEDS_type N3  = NUM_LEDS_type(NUM_LEDS / 3);
  NUM_LEDS_type N6  = NUM_LEDS_type(NUM_LEDS / 6);
  NUM_LEDS_type N12 = NUM_LEDS_type(NUM_LEDS / 12);
  for(NUM_LEDS_type i = 0; i < N6; i++ ) {    //-HACKY, I KNOW...
    tcount = tcount + .02;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = byte(sin(tcount) * 255);
    NUM_LEDS_type j0 = (i + NUM_LEDS - N12) % NUM_LEDS;
    NUM_LEDS_type j1 = (j0 + N3) % NUM_LEDS;
    NUM_LEDS_type j2 = (j1 + N3) % NUM_LEDS;
    leds[j0] = CHSV(thishue, 255, ibright);
    leds[j1] = CHSV(thishue, 255, ibright);
    leds[j2] = CHSV(thishue, 255, ibright);
  }
}

void candycane() //!
{
  idex++;
  byte thisbri=255;
  //NUM_LEDS_type N3  = NUM_LEDS_type(NUM_LEDS/3);
  NUM_LEDS_type N6  = NUM_LEDS_type(NUM_LEDS/6);  
  NUM_LEDS_type N12 = NUM_LEDS_type(NUM_LEDS/12);  
  for(int i = 0; i < N6; i++ ) {
    NUM_LEDS_type j0 = (idex + i + NUM_LEDS - N12) % NUM_LEDS;
    NUM_LEDS_type j1 = (j0+N6) % NUM_LEDS;
    NUM_LEDS_type j2 = (j1+N6) % NUM_LEDS;
    NUM_LEDS_type j3 = (j2+N6) % NUM_LEDS;
    NUM_LEDS_type j4 = (j3+N6) % NUM_LEDS;
    NUM_LEDS_type j5 = (j4+N6) % NUM_LEDS;
    leds[j0] = CRGB(255, 255, 255).nscale8_video(thisbri*.75);
    leds[j1] = CRGB(255, 0, 0).nscale8_video(thisbri);
    leds[j2] = CRGB(255, 255, 255).nscale8_video(thisbri*.75);
    leds[j3] = CRGB(255, 0, 0).nscale8_video(thisbri);
    leds[j4] = CRGB(255, 255, 255).nscale8_video(thisbri*.75);
    leds[j5] = CRGB(255, 0, 0).nscale8_video(thisbri);   
  }
}

void color_loop_vardelay() {                    //-m17-COLOR LOOP (SINGLE LED) w/ VARIABLE DELAY
  idex++;
  if (idex > NUM_LEDS) {
    idex = 0;
  }
  int di = abs(CENTER_TOP_INDEX - idex);
  int t = constrain((100 / di), 5, 100);
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ )
  {
    if (i == idex) {
      leds[i] = CHSV(0, 255, 255);
    }
    else {
      leds[i].r =effSpeed>126 ? idex : 0;
      leds[i].g =effLength>126 ? t : 0;
      leds[i].b = 0;
    }
  }
  delay(t);
}

void white_temps() {                            //-m18-SHOW A SAMPLE OF BLACK BODY RADIATION COLOR TEMPERATURES
  int N9 = NUM_LEDS_type(NUM_LEDS / 9);
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    if (i >= 0 && i < N9) {
      leds[i].r = 255;  //-CANDLE - 1900
      leds[i].g = 147;
      leds[i].b = 41;
    }
    if (i >= N9 && i < N9 * 2) {
      leds[i].r = 255;  //-40W TUNG - 2600
      leds[i].g = 197;
      leds[i].b = 143;
    }
    if (i >= N9 * 2 && i < N9 * 3) {
      leds[i].r = 255;  //-100W TUNG - 2850
      leds[i].g = 214;
      leds[i].b = 170;
    }
    if (i >= N9 * 3 && i < N9 * 4) {
      leds[i].r = 255;  //-HALOGEN - 3200
      leds[i].g = 241;
      leds[i].b = 224;
    }
    if (i >= N9 * 4 && i < N9 * 5) {
      leds[i].r = 255;  //-CARBON ARC - 5200
      leds[i].g = 250;
      leds[i].b = 244;
    }
    if (i >= N9 * 5 && i < N9 * 6) {
      leds[i].r = 255;  //-HIGH NOON SUN - 5400
      leds[i].g = 255;
      leds[i].b = 251;
    }
    if (i >= N9 * 6 && i < N9 * 7) {
      leds[i].r = 255;  //-DIRECT SUN - 6000
      leds[i].g = 255;
      leds[i].b = 255;
    }
    if (i >= N9 * 7 && i < N9 * 8) {
      leds[i].r = 201;  //-OVERCAST SKY - 7000
      leds[i].g = 226;
      leds[i].b = 255;
    }
    if (i >= N9 * 8 && i < NUM_LEDS) {
      leds[i].r = 64;  //-CLEAR BLUE SKY - 20000
      leds[i].g = 156;
      leds[i].b = 255;
    }
  }
}
#endif

void sin_bright_wave() {
    tcount = tcount + .1;
    if (tcount > 3.14) {
      tcount = 0.0;
    }
    ibright = byte(sin(tcount) * 255);
    leds[i_eff%NUM_LEDS] = CHSV(thishue, 255, ibright);
}

void pop_horizontal() {        //-m20-POP FROM LEFT TO RIGHT UP THE RING
  NUM_LEDS_type ix;
  if (bouncedirection == 0) {
    bouncedirection = 1;
    ix = idex;
  }
  else if (bouncedirection == 1) {
    bouncedirection = 0;
    ix = horizontal_index(idex);
    idex++;
    if (idex > CENTER_TOP_INDEX) {
      idex = 0;
    }
  }
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    if (i == ix) {
        idex=i; thishue=colorize();
      leds[i] = CHSV(thishue, 255, 255);
    }
    else {
      leds[i]=0;
    }
  }
}

void quad_bright_curve() {      //-m21-QUADRATIC BRIGHTNESS CURVER

  NUM_LEDS_type ax;
  for(NUM_LEDS_type x = 0; x < NUM_LEDS; x++ ) {
    if (x <= CENTER_TOP_INDEX) {
      ax = x;
    }
    else if (x > CENTER_TOP_INDEX) {
      ax = NUM_LEDS - x;
    }
    byte a = 1;
    byte b = 1;
    byte c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c; //-ax2+bx+c
    int hquad = -(CENTER_TOP_INDEX * CENTER_TOP_INDEX * a) + (CENTER_TOP_INDEX * b) + c;
    ibright = byte((float(iquad) / float(hquad)) * 255);

    idex=x;
    thishue=colorize();
    leds[(x+effSpeed)%NUM_LEDS] = CHSV(thishue, 255, ibright);
  }
}

void flame() {                                    //-m22-FLAMEISH EFFECT
  int idelay = random(0, 15);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(CENTER_TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for(NUM_LEDS_type i = 0; i <= CENTER_TOP_INDEX; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, 255, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(ihue, 255, 255);
    leds[CENTER_TOP_INDEX].r = 255; leds[CENTER_TOP_INDEX].g = 255; leds[CENTER_TOP_INDEX].b = 255;
    FastLED.show();
    delay(idelay); //!!
  }
}


void pacman() {                                  //-m24-REALLY TERRIBLE PACMAN CHOMPING EFFECT
//!! re
  int s = NUM_LEDS_type(NUM_LEDS / 2);
  lcount++;
  if (lcount > 5) {
    lcount = 0;
  }
  if (lcount == 0) {
    for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i]=CRGB(255, 255, 0);
    }
  }
  if (lcount == 1 || lcount == 5) {
    for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i]=CRGB(255, 255, 0);
    }
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
  }
  if (lcount == 2 || lcount == 4) {
    for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i]=CRGB(255, 255, 0);
    }
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
  }
  if (lcount == 3) {
    for(NUM_LEDS_type i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i]=CRGB(255, 255, 0);
    }
    leds[s - 2].r = 0; leds[s - 2].g = 0; leds[s - 2].b = 0;
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
    leds[s + 2].r = 0; leds[s + 2].g = 0; leds[s + 2].b = 0;
  }
}

void ems_lightsSTROBE() {                  //-m26-EMERGENCY LIGHTS (STROBE LEFT/RIGHT)
  int thishue = effLength;
  int thathue = (thishue + 160) % 255;
  for(byte x = 0 ; x < 5; x++ ) {
    for(NUM_LEDS_type i = 0 ; i < CENTER_TOP_INDEX; i++ ) {
      leds[i] = CHSV(thishue, 255, 255);
    }
    FastLED.show(); delay(effSpeed/32);
    FastLED.clear();
    FastLED.show(); delay(effSpeed/32);
  }
  for(byte x = 0 ; x < 5; x++ ) {
    for(NUM_LEDS_type i = CENTER_TOP_INDEX ; i < NUM_LEDS; i++ ) {
      leds[i] = CHSV(thathue, 255, 255);
    }
    FastLED.show(); delay(effSpeed/32);
    FastLED.clear();
    FastLED.show(); delay(effSpeed/32);
  }
}


void kitt() {                                     //-m28-KNIGHT INDUSTIES 2000
  idex = random(0, CENTER_TOP_INDEX);
  thishue=colorize(); //use idex

  for(NUM_LEDS_type i = 0; i < idex; i++ ) {
    leds[CENTER_TOP_INDEX + i] = CHSV(thishue, 255, 255);
    leds[CENTER_TOP_INDEX - i] = CHSV(thishue, 255, 255);
    FastLED.show();
    delay(effSpeed/16 / idex);
  }
  for(NUM_LEDS_type i = idex; i > 0; i-- ) {
    leds[CENTER_TOP_INDEX + i] = CHSV(thishue, 255, 0);
    leds[CENTER_TOP_INDEX - i] = CHSV(thishue, 255, 0);
    FastLED.show();
    delay(effSpeed/16 / idex);
  }
}
#ifndef saveMem
void matrix() {                                   //-m29-ONE LINE MATRIX
  byte rand = random8(0, 100);

  if(effLength<125) thishue = effLength*2;
  else 
    if(effLength<200) thishue = gHue*effSpeed/16; //!tst //gHue*(effLength-124)/16;
  else 
  { //single color batch
    if(rand<90)
    thishue +=2*(1+effSpeed)/16;
  }

  
  if (rand > 90) {
    leds[0] = CHSV(thishue, 255, 255);
  }
  else {
    leds[0] = CHSV(thishue, 255, 0);
  }
  copy_led_array();
  for(NUM_LEDS_type i = 1; i < NUM_LEDS; i++ ) {
    leds[i].r = ledsX[i - 1].r;
    leds[i].g = ledsX[i - 1].g;
    leds[i].b = ledsX[i - 1].b;
  }
}

void strip_march_cw() {                        //-m50-MARCH STRIP CW
  copy_led_array();
  int iCW;
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    iCW = adjacent_cw(i);
    leds[i].r = ledsX[iCW][0];
    leds[i].g = ledsX[iCW][1];
    leds[i].b = ledsX[iCW][2];
  }
}

void strip_march_ccw() {                        //-m51-MARCH STRIP CCW
  copy_led_array();
  int iCCW;
  for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++ ) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
}
#endif

//!! move 1 rev, mode, move, move
// move d move d move d



//----------------------------- fill
// void colorWipe(byte red, byte green, byte blue) {
//     leds[i_eff]=CRGB(red, green, blue);
// }
void colorWipe() //!
{
  leds[i_eff]=CHSV(effSpeed,effLength,255);
}

//==================================== moving

void CylonBounce(byte red, byte green, byte blue, byte EyeSize, byte SpeedDelay, byte ReturnDelay) { //!! compare speed

  for(NUM_LEDS_type i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
    FastLED.clear();
    leds[i]=CRGB(red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i+j]=CRGB( red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB( red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);

    #if defined(SerialSelect) || defined(SerialControl)
    checkSerial();
    #endif
  }

  delay(ReturnDelay);
  
  
  #ifdef IRkeypad //!
	EVERY_N_MILLISECONDS( 40 )
	{
	if (IRLremote.receiving()) return;
	}
	#endif

  for(NUM_LEDS_type i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    FastLED.clear();
    leds[i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i + j]=CRGB(red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB( red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);

    #if defined(SerialSelect) || defined(SerialControl)
    checkSerial();
    #endif
  }

  delay(ReturnDelay);
}
void CylonBounce()
{
  CylonBounce(255, 255, 255, effLength/16, effSpeed/16, 4);
}

//---------------------------------
void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    leds[Pixel]=CRGB( 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    leds[Pixel]=CRGB( 255, heatramp, 0);
  } else {                               // coolest
    leds[Pixel]=CRGB( heatramp, 0, 0);
  }

   //!!
  // byte t=leds[Pixel].g;
   //leds[Pixel].r= leds[Pixel].g;
  // leds[Pixel].g= t;

}

void Fire() {
  byte Cooling=effSpeed;
  byte Sparking=effLength;

  static byte heat[NUM_LEDS];
  byte cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    byte y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }
}


//-------------------------------newKITT---------------------------------------

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(NUM_LEDS_type i = ((NUM_LEDS - EyeSize) / 2); i >= 0; i--) {
    FastLED.clear();

    leds[i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i + j]=CRGB( red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB(red / 10, green / 10, blue / 10);

    leds[NUM_LEDS - i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[NUM_LEDS - i - j]=CRGB( red, green, blue);
    }
    leds[NUM_LEDS - i - EyeSize - 1]=CRGB( red / 10, green / 10, blue / 10);

    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(NUM_LEDS_type i = 0; i <= ((NUM_LEDS - EyeSize) / 2); i++) {
    FastLED.clear();

    leds[i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i + j]=CRGB( red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB( red / 10, green / 10, blue / 10);

    leds[NUM_LEDS - i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[NUM_LEDS - i - j]=CRGB( red, green, blue);
    }
    leds[NUM_LEDS - i - EyeSize - 1]=CRGB( red / 10, green / 10, blue / 10);

    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(NUM_LEDS_type i = 0; i < NUM_LEDS - EyeSize - 2; i++) {
	FastLED.clear();
    leds[i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i + j]=CRGB( red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB( red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(NUM_LEDS_type i = NUM_LEDS - EyeSize - 2; i > 0; i--) {
    FastLED.clear();
    leds[i]=CRGB( red / 10, green / 10, blue / 10);
    for(byte j = 1; j <= EyeSize; j++) {
      leds[i + j]=CRGB( red, green, blue);
    }
    leds[i + EyeSize + 1]=CRGB( red / 10, green / 10, blue / 10);
    FastLED.show();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {  //!!fix crash //chech input
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
      #if defined(SerialSelect) || defined(SerialControl)
    checkSerial();
    #endif
    #ifdef IRkeypad //!
  EVERY_N_MILLISECONDS( 40 )
  {
  if (IRLremote.receiving()) return;
  }
  #endif
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}
void NewKITT()
{
   CRGB c =CHSV(effLength,255,255);
   NewKITT(c.r, c.g, c.b, 8, 10+effSpeed/8, 10+effSpeed/8); //! crash at (serial) updates

  //NewKITT(255, 255, 188, 8, 10, 10);
}


//-------------------------------newKITT---------------------------------------


//-------------------------------TwinkleRandom---------------------------------------
// void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
//  // FastLED.clear();

//  // for(NUM_LEDS_type i = 0; i < Count; i++) {
//     leds[random(NUM_LEDS)]=CRGB( random(0, 255), random(0, 255), random(0, 255));
//     // FastLED.show();
//     // delay(SpeedDelay);
//     // if (OnlyOne) {
//       // FastLED.clear();
//     // }
//   //}
// }

//-------------------------------RunningLights---------------------------------------
void RunningLights(byte red, byte green, byte blue) { //!
    for(NUM_LEDS_type i = 0; i < NUM_LEDS; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //leds[i]=CRGB(level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      leds[i]=CRGB(
        sin8(i + i_eff*11/effSpeed)*red/255,
        sin8(i + i_eff*14/effSpeed)*green/255,
        sin8(i + i_eff*17/effSpeed)*blue/255
        )  ;

               //  leds[i]=CRGB( ((sin8(i + i_eff*100/effSpeed) * 127 + 128) / 255)*red,
               // ((sin8(i + i_eff*113/effSpeed) * 127 + 128) / 255)*green,
               // ((sin8(i + i_eff*145/effSpeed) * 127 + 128) / 255)*blue); //!  *gColor
    }

  // // int Position=0;
  // // for(int i=0; i<NUM_LEDS*2; i++)
  // // {
  // //    Position++; // = 0; //Position + Rate;
  //     for(NUM_LEDS_type i=0; i<NUM_LEDS; i++) {
  //       leds[i]=CRGB(
  //         ((sin(i+i_eff*22/effSpeed) * 127 + 128)/255)*red,
  //         ((sin(i+i_eff*46/effSpeed) * 127 + 128)/255)*green,
  //         ((sin(i+i_eff*57/effSpeed) * 127 + 128)/255)*blue
  //         );
  //     }
  // //    showStrip();
  // //     delay(effSpeed/16);
  // // }

/*
 int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
}
*/
}
void RunningLights()
{
  RunningLights(255, 255,255);
}

//-------------------------------Sparkle---------------------------------------
void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  leds[Pixel]=CRGB( red, green, blue);
  FastLED.show();
  delay(SpeedDelay);
  leds[Pixel]=CRGB( 0, 0, 0);
}

//-------------------------------SnowSparkle---------------------------------------
void SnowSparkle(int SparkleDelay, int SpeedDelay) {
  fillAll();

  int Pixel = random(NUM_LEDS);
  leds[Pixel]=CRGB::White;
  FastLED.show();
  delay(SparkleDelay);
  leds[Pixel]=gColor;
  FastLED.show();
  delay(SpeedDelay);
}

//-------------------------------theaterChase---------------------------------------
void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  //for(byte j = 0; j < 10; j++) { //do 10 cycles of chasing
    for(byte q = 0; q < 3; q++) {
      for(NUM_LEDS_type i = 0; i < NUM_LEDS; i = i + 3) {
        leds[i + q]=CRGB( red, green, blue);  //turn every third pixel on
      }
      FastLED.show();
      delay(SpeedDelay);
      for(NUM_LEDS_type i = 0; i < NUM_LEDS; i = i + 3) {
        leds[i + q]=CRGB( 0, 0, 0);    //turn every third pixel off
      }
    }
  //}
}

//-------------------------------theaterChaseRainbow---------------------------------------
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;

  for(NUM_LEDS_type j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for(byte q = 0; q < 3; q++) {
      for(NUM_LEDS_type i = 0; i < NUM_LEDS; i = i + 3) {
        c = Wheel( (i + j) % 255);
        leds[i + q]=CRGB( *c, *(c + 1), *(c + 2)); //turn every third pixel on
      }
      FastLED.show();
      delay(SpeedDelay);
      for(NUM_LEDS_type i = 0; i < NUM_LEDS; i = i + 3) {
        leds[i + q]=CRGB( 0, 0, 0);    //turn every third pixel off
      }
    }
	
	#ifdef IRkeypad //!
	EVERY_N_MILLISECONDS( 40 )
	{
	if (IRLremote.receiving()) return;
	}
	#endif
  }
}

//-------------------------------Strobe---------------------------------------
void Strobe(int StrobeCount, int FlashDelay, int endDelay) {
  for(byte j = 0; j < StrobeCount; j++) {
    fillAll();
    FastLED.show();
    delay(FlashDelay);
    FastLED.clear();
    FastLED.show();
    delay(FlashDelay);
  }
  delay(endDelay);
}
void Strobe()
{
  Strobe(10, effSpeed/16, effSpeed/16);
}
//-------------------------------BouncingBalls---------------------------------------
void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  unsigned long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for(byte i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

  while (true)
	{
    for(byte i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for(byte i = 0 ; i < BallCount ; i++) {
      leds[Position[i]]=CRGB( red, green, blue);
    }
    FastLED.show();
    FastLED.clear();
	
	#ifdef IRkeypad //!
	EVERY_N_MILLISECONDS( 20 )
	{
	if (IRLremote.receiving()) return;
	}
	#endif
  }
}

//-------------------------------BouncingColoredBalls---------------------------------------
 #ifndef saveMem
void BouncingColoredBallsSim(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  unsigned long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for(byte i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

 unsigned long stop_t=millis()+5000;
  while (millis()<stop_t)  //! ret
  {
    for(byte i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for(byte i = 0 ; i < BallCount ; i++) {
      leds[Position[i]]=CRGB( colors[i][0], colors[i][1], colors[i][2]); //!opt CRGB
    }
    FastLED.show();
    FastLED.clear();
	
	#ifdef IRkeypad //!
	EVERY_N_MILLISECONDS( 30 )
	{
	if (IRLremote.receiving()) return;
	}
	#endif
 
  }
}

void BouncingColoredBalls()
{
 BouncingColoredBallsSim(effLength, ballColors);
}
#endif
//=========================================
#ifdef adjType_LDR
byte ambientLight_map()
{
  return map(analogRead(adj_pot),10,1000,255,22);
}
#endif
