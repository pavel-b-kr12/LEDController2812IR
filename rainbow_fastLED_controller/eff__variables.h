uint8_t gHue = 0;

//int il;
long i_eff=0;//! tst

byte thisstep = 10;



unsigned long randomShow_next_effN_sw_t=0;

//=============================== variables to be reused in effects 
//---if effect is multistages
byte eff_stage_i=0; //have to be set 0 at i_eff==0 or at  switch(eff_stage_i) default:{if(millis()>eff_stage_next_t){eff_stage_i=0;}}  in each effect that need eff_stage. 
long eff_stage_next_t=0; 
//---

byte		twinkrate = 100; // The higher the value, the lower the number of twinkles.
byte		thisfade =	  8; // How quickly does it fade? Lower = slower fade rate.
//nscale					 // Trail behind the LED's. Lower => faster fade.
byte		thishue =	 50; // Starting hue.
byte		thissat =	255; // The saturation, where 255 = brilliant colours.
byte		thisbri =	255; // Brightness of a sequence.
bool		randhue =	  1; // Do we want random colours all the time? 1 = yes.
uint8_t		thisinc =	  1; // Incremental value for rotating hues
int			huediff =	256; // Range of random #'s to use for hue


uint8_t bgH;
uint8_t bgHinc = 0;
uint8_t bgbri = 0;                                        // Brightness of background colour

uint8_t deltahue = 15; // Hue change between pixels.
uint8_t xscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint8_t yscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
uint8_t maxChanges = 24;            //! set every time or not chane                          // Value for blending between palettes.
uint8_t thisbeat;
uint8_t huerot;
uint8_t palIndex;


uint8_t thiscutoff = 128;
uint8_t allfreq = 32;


uint8_t   numdots =   4;                                     // Number of dots in use.
uint8_t   thisdiff =  16;                                     // Incremental change in hue between each dot.



int8_t thisrot = 1;                                           // Hue rotation speed. Includes direction.
bool thisdir = 0;  // I use a direction variable instead of signed math so I can use it in multiple routines. //-SWITCH FOR COLOR BOUNCE (0-1)

int wave1=0;                                                  // Current phase is calculated.
int wave2=0;
int wave3=0;

uint8_t inc1 = 2;                                             // Phase shift. Keep it low, as this is the speed at which the waves move.
uint8_t inc2 = 1;
uint8_t inc3 = -2;

uint8_t lvl1 = 80;                                            // Any result below this value is displayed as 0.
uint8_t lvl2 = 80;
uint8_t lvl3 = 80;

uint8_t mul1 = 20;                                            // Frequency, thus the distance between waves
uint8_t mul2 = 25;
uint8_t mul3 = 22;


//static int16_t randStatic;

NUM_LEDS_type idex = 0;		//-LED INDEX (0 to NUM_LEDS-1
uint16_t idex16 = 0;
NUM_LEDS_type idex_last = 0;
float idex_f = 0;
byte ihue = 0;
byte ibright = 0;
byte isat = 0;
float tcount = 0.0;		  //-INC VAR FOR SIN LOOPS
byte lcount = 0;			  //-ANOTHER COUNTING VAR

// Palette definitions
CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType	currentBlending; //currentBlending = LINEARBLEND;                  // NOBLEND or LINEARBLEND

int pos1,pos2; //x
float pos_f;