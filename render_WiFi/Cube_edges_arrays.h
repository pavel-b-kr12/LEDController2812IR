	//CRGBArray<NUM_LEDS_edge*3> leds_;
	// CRGB ledsX[NUM_LEDS_edge];
	// CRGB ledsY[NUM_LEDS_edge];
	// CRGB ledsZ[NUM_LEDS_edge];

	//direction from corner
	CRGBSet ledsXdirect(leds, 0, NUM_LEDS_edge);
	CRGBSet ledsYdirect(leds, NUM_LEDS_edge+1, NUM_LEDS_edge*2); //!?tst +1
	CRGBSet ledsZdirect(leds, NUM_LEDS_edge*2+1, NUM_LEDS_edge*3);
	//same direction fro all MCU
	#if MCU_N==0
		CRGBSet ledsX(leds, 0, NUM_LEDS_edge);
		CRGBSet ledsY(leds, NUM_LEDS_edge+1, NUM_LEDS_edge*2);
		CRGBSet ledsZ(leds, NUM_LEDS_edge*2+1, NUM_LEDS_edge*3);
	#elif  MCU_N==1
		CRGBSet ledsX(leds, NUM_LEDS_edge, 0);
		CRGBSet ledsY(leds, NUM_LEDS_edge*2,  NUM_LEDS_edge+1);
		CRGBSet ledsZ(leds, NUM_LEDS_edge*2+1, NUM_LEDS_edge*3);
	#elif  MCU_N==2
		CRGBSet ledsX(leds, NUM_LEDS_edge, 0);
		CRGBSet ledsY(leds, NUM_LEDS_edge+1, NUM_LEDS_edge*2);
		CRGBSet ledsZ(leds, NUM_LEDS_edge*3,  NUM_LEDS_edge*2+1);
	#elif  MCU_N==3
		CRGBSet ledsX(leds, 0, NUM_LEDS_edge);
		CRGBSet ledsY(leds, NUM_LEDS_edge*2,  NUM_LEDS_edge+1);
		CRGBSet ledsZ(leds, NUM_LEDS_edge*3,  NUM_LEDS_edge*2+1);
	#endif
// #else
// 	CRGB leds[gNUM_LEDS]; //!! del +1