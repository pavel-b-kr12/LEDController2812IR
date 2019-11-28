/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void btn3_L_click1(GButton source, GEvent event) { //_CODE_:btn3_L:695180:
																		//source.setText(event.toString());
 sub(mode);
} //_CODE_:btn3_L:695180:

public void btn3_M_click1(GButton source, GEvent event) { //_CODE_:btn3_M:752428:
 mode++;
 modeChanged();
} //_CODE_:btn3_M:752428:

public void btn3_R_click1(GButton source, GEvent event) { //_CODE_:btn3_R:996531:
 add(mode);
} //_CODE_:btn3_R:996531:

public void btn5_select_click1(GButton source, GEvent event) { //_CODE_:btn5_select:761800:
 mode++;
 modeChanged();
} //_CODE_:btn5_select:761800:

public void btn5_L_click1(GButton source, GEvent event) { //_CODE_:btn5_L:982726:
	 settingsVals.get("effN").sub();
} //_CODE_:btn5_L:982726:

public void btn5_R_click1(GButton source, GEvent event) { //_CODE_:btn5_R:411550:
	settingsVals.get("effN").add();
} //_CODE_:btn5_R:411550:

public void btn5_U_click1(GButton source, GEvent event) { //_CODE_:btn5_U:960811:
	add(mode);
} //_CODE_:btn5_U:960811:

public void btn5_D_click1(GButton source, GEvent event) { //_CODE_:btn5_D:718469:
	sub(mode);
} //_CODE_:btn5_D:718469:

public void button_pause_click1(GButton source, GEvent event) { //_CODE_:button_pause:209227:
	//changeValue(valNm.effN, effN_PAUSE);
	SendMsg(settingsVals.get("pause").message_code, 0);                //println(settingsVals.get("pause").message_code);
} //_CODE_:button_pause:209227:

public void button_clear_click1(GButton source, GEvent event) { //_CODE_:button_clear:383723:
	SendMsg(settingsVals.get("clear").message_code, 0);
} //_CODE_:button_clear:383723:

public void slider_effN_change1(GSlider source, GEvent event) { //_CODE_:slider_effN:684540:
  if(bDebugPrint){
																																				print("slider event, skip: ");
																																				//println(event.getType()); //alvays == VALUE_STEADY
																																				println(bSkipEvent);
  }
	if(bSkipEvent) return;
	settingsVals.get("effN").setValue(source.getValueI());
} //_CODE_:slider_effN:684540:

public void slider_speed_change1(GSlider source, GEvent event) { //_CODE_:slider_speed:516221:
	if(bSkipEvent) return;
	settingsVals.get("speed").setValue(source.getValueI());
} //_CODE_:slider_speed:516221:

public void slider_length_change1(GSlider source, GEvent event) { //_CODE_:slider_length:285255:
	if(bSkipEvent) return;
	settingsVals.get("length").setValue(source.getValueI());
} //_CODE_:slider_length:285255:

public void slider_RGB_change1(GSlider source, GEvent event) { //_CODE_:slider_RGB:881653:
	if(bSkipEvent) return;
	settingsVals.get("RGB").setValue(source.getValueI());
} //_CODE_:slider_RGB:881653:

public void button_action_click1(GButton source, GEvent event) { //_CODE_:button_action:399269:
	SendMsg(settingsVals.get("action").message_code, settingsVals.get("action").value);
} //_CODE_:button_action:399269:

public void button_reset_click1(GButton source, GEvent event) { //_CODE_:button_reset:971502:
		 SendMsg(settingsVals.get("reset").message_code, settingsVals.get("reset").value); // 0 - effN  //!! 1 - changeMode     
} //_CODE_:button_reset:971502:

public void button_effNsub_click1(GButton source, GEvent event) { //_CODE_:button_effNsub:404447:
 settingsVals.get("effN").sub();
} //_CODE_:button_effNsub:404447:

public void button_effNAdd_click1(GButton source, GEvent event) { //_CODE_:button_effNAdd:715775:
 settingsVals.get("effN").add();
} //_CODE_:button_effNAdd:715775:

public void slider_brightness_change1(GSlider source, GEvent event) { //_CODE_:slider_brightness:412375:
  if(bSkipEvent) return;
	settingsVals.get("gBrightness").setValue(source.getValueI());
} //_CODE_:slider_brightness:412375:

public void slider_speedH_change1(GSlider source, GEvent event) { //_CODE_:slider_speedH:696558:
	if(bSkipEvent) return;
	settingsVals.get("speedH").setValue(source.getValueI());
} //_CODE_:slider_speedH:696558:

public void slider_lengthH_change1(GSlider source, GEvent event) { //_CODE_:slider_lengthH:778964:
	if(bSkipEvent) return;
	settingsVals.get("lengthH").setValue(source.getValueI());
} //_CODE_:slider_lengthH:778964:

public void slider_action_change(GSlider source, GEvent event) { //_CODE_:slider_action:268497:
	if(bSkipEvent) return;
	//changeValue(valNm.messageAction, source.getValueI());
	int val=source.getValueI();
	button_action.setText("Action:"+val +":"+actionNm[val]);
	settingsVals.get("action").value=val;
	//settingsVals.get("action").setValue(val);
} //_CODE_:slider_action:268497:

public void button_disconnect_click(GButton source, GEvent event) { //_CODE_:button_disconnect:619813:
	if(bConnected==2)  DisableSerial();
	else EnableSerial();
} //_CODE_:button_disconnect:619813:

public void effN_random_click(GButton source, GEvent event) { //_CODE_:effN_random:685529:
	settingsVals.get("effN").setValue(249);
} //_CODE_:effN_random:685529:

public void effN_animate_click(GButton source, GEvent event) { //_CODE_:effN_animate:489976:
	settingsVals.get("effN").setValue(251);
} //_CODE_:effN_animate:489976:

public void effN_animate_continue_click(GButton source, GEvent event) { //_CODE_:effN_animate_continue:596472:
	settingsVals.get("effN").setValue(252);
} //_CODE_:effN_animate_continue:596472:

public void effN_demoRandom_click(GButton source, GEvent event) { //_CODE_:effN_demoRandom:428271:
	settingsVals.get("effN").setValue(255);
} //_CODE_:effN_demoRandom:428271:

public void effN_demoRandom_fast_click(GButton source, GEvent event) { //_CODE_:effN_demoRandom_fast:936050:
	settingsVals.get("effN").setValue(254);
} //_CODE_:effN_demoRandom_fast:936050:

public void button_effN_seq_click(GButton source, GEvent event) { //_CODE_:button_effN_seq:471653:
	settingsVals.get("effN").setValue(253);
} //_CODE_:button_effN_seq:471653:

public void button_animateRandom_click1(GButton source, GEvent event) { //_CODE_:button_animateRandom:917506:
	settingsVals.get("effN").setValue(250);
} //_CODE_:button_animateRandom:917506:

public void button_codeGen_click(GButton source, GEvent event) { //_CODE_:button_codeGen:274298:
	int effN=settingsVals.get("effN").valueSlider.getValueI(); //!fix values has to be setted by Serial, not only slider pos. Bus seems it has not //settingsVals.get("effN").value
	
	String s="case "+
	Integer.toString(effN)+ 
	":anim_f="+EffNms[effN]+";"+
  printVal("effSpeed","speed",-1)+
  printVal("effLength","length",-1)+
  printVal("effSpeedH","speedH",-1)+
  printVal("effLengthH","lengthH",-1)+
  printVal("effFade","effFade",-1)+
  "    gColor=CRGB("+
     Integer.toString(settingsVals.get("gColorH").valueSlider.getValueI())+","+
     Integer.toString(settingsVals.get("gColorS").valueSlider.getValueI())+","+
     Integer.toString(settingsVals.get("gColorV").valueSlider.getValueI())+
  ");"+

	// ";    gColorBg="+   Integer.toString(settingsVals.get("gColorH").valueSlider.getValueI())+
	//printVal("gFade","gFade",-1)+
	printVal("indexOrBits","indexOrBits",-1)+

	printVal("gDelay","gDelay", 5);
	//printVal("gBrightness","gBrightness")+
	//printVal("NUM_LEDS","NUM_LEDS")+
	printVal("effRGB","RGB", 0);
	s+=" break;";

	copyToClipboard(s);
} //_CODE_:button_codeGen:274298:

public void slider_gDelay_change1(GSlider source, GEvent event) { //_CODE_:slider_gDelay:330218:
	if(bSkipEvent) return;
	settingsVals.get("gDelay").setValue(source.getValueI());
} //_CODE_:slider_gDelay:330218:

public void slider_effFade_change(GSlider source, GEvent event) { //_CODE_:slider_effFade:371226:
	if(bSkipEvent) return;
	settingsVals.get("effFade").setValue(source.getValueI());
} //_CODE_:slider_effFade:371226:

public void slider_indexOrBits_change(GSlider source, GEvent event) { //_CODE_:slider_indexOrBits:366592:
	if(bSkipEvent) return;
	settingsVals.get("indexOrBits").setValue(source.getValueI());
} //_CODE_:slider_indexOrBits:366592:

public void slider_gColorH_change(GSlider source, GEvent event) { //_CODE_:slider_gColorH:600066:
	if(bSkipEvent) return;
	settingsVals.get("gColorH").setValue(source.getValueI());
} //_CODE_:slider_gColorH:600066:

public void slider_gColorS_change(GSlider source, GEvent event) { //_CODE_:slider_gColorS:910166:
	if(bSkipEvent) return;
	settingsVals.get("gColorS").setValue(source.getValueI());
} //_CODE_:slider_gColorS:910166:

public void slider_gColorV_change(GSlider source, GEvent event) { //_CODE_:slider_gColorV:320268:
	if(bSkipEvent) return;
	settingsVals.get("gColorV").setValue(source.getValueI());
} //_CODE_:slider_gColorV:320268:

public void NUM_LEDS_change(GSlider source, GEvent event) { //_CODE_:slider_NUM_LEDS:783871:
	if(bSkipEvent) return;
	settingsVals.get("NUM_LEDS").setValue(source.getValueI());
} //_CODE_:slider_NUM_LEDS:783871:

public void button_msgprint_click(GButton source, GEvent event) { //_CODE_:button_msgprint:899288:
	SendMsg(settingsVals.get("msgprint").message_code, 0);
	println("CRGBPalette16 currentPalette = CRGBPalette16(");

} //_CODE_:button_msgprint:899288:

public void button_sim_click(GButton source, GEvent event) { //_CODE_:button_sim:689176:
  bSim_set(!bSim);
} //_CODE_:button_sim:689176:

public void btn_copy_switch_nms_click(GButton source, GEvent event) { //_CODE_:btn_copy_switch_nms:419833:
  
String s="const linksNames =[";
boolean bNotFirts=false;
  for(int i=0;i<255;i++)
  {
    if(EffNmsQuality[i]==null || EffNmsQuality[i]>2) continue; //skip bugged and boring: 1 = all, all-1 = best, +1 - not interesting, +2 buggy //TODO GUI
     String  nm= EffNms[i];

     if(nm!=null)
     {
      if(bNotFirts) 
      {
        s+=",";
      } else bNotFirts=true;
      s+="['"+nm+"',"+Integer.toString(i)+"]";
     }
  }
    s+="];";

  copyToClipboard(s);
} //_CODE_:btn_copy_switch_nms:419833:

public void btn_matrix_zigZag_h_click(GButton source, GEvent event) { //_CODE_:btn_matrix_zigZag_h:353002:
    set_bbtn_matrix_state(242);
} //_CODE_:btn_matrix_zigZag_h:353002:

public void btn_matrix_spiral_cw_click(GButton source, GEvent event) { //_CODE_:btn_matrix_spiral_cw:495934:
  set_bbtn_matrix_state(243);
  
} //_CODE_:btn_matrix_spiral_cw:495934:

public void btn_labyrinth_cw_click(GButton source, GEvent event) { //_CODE_:btn_labyrinth_cw:373886:
  set_bbtn_matrix_state(244);
} //_CODE_:btn_labyrinth_cw:373886:

public void btn_mirror_half_click(GButton source, GEvent event) { //_CODE_:btn_mirror_half:261892:
  set_bbtn_matrix_state(245);
} //_CODE_:btn_mirror_half:261892:

public void btn_history_click(GButton source, GEvent event) { //_CODE_:btn_history:509443:
  set_bbtn_matrix_state(246);
} //_CODE_:btn_history:509443:

public void checkbox_LEDs_customGeom_cl(GCheckbox source, GEvent event) { //_CODE_:checkbox_LEDs_customGeom:713840:
  if(plotPX!=null)
  {
    plotPX.bDrawLEDs_customGeometry_paint=source.isSelected(); //!bDrawLEDs_customGeometry_paint;
    if(plotPX.bDrawLEDs_customGeometry_paint)  plotPX.DrawLEDs_currentPoint=0;
    else
    {
      plotPX.DrawLEDs_save(plotPX.DrawLEDs_currentPoint);
    }
  }
  //!!TODO gen btns as files, change text draw / save
} //_CODE_:checkbox_LEDs_customGeom:713840:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  btn3_L = new GButton(this, 20, 110, 80, 30);
  btn3_L.setText("L");
  btn3_L.addEventHandler(this, "btn3_L_click1");
  btn3_M = new GButton(this, 110, 110, 130, 30);
  btn3_M.setText("Mode");
  btn3_M.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn3_M.addEventHandler(this, "btn3_M_click1");
  btn3_R = new GButton(this, 250, 110, 80, 30);
  btn3_R.setText("R");
  btn3_R.addEventHandler(this, "btn3_R_click1");
  btn5_select = new GButton(this, 20, 40, 130, 30);
  btn5_select.setText("Select Mode");
  btn5_select.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn5_select.addEventHandler(this, "btn5_select_click1");
  btn5_L = new GButton(this, 160, 40, 80, 30);
  btn5_L.setText("L");
  btn5_L.addEventHandler(this, "btn5_L_click1");
  btn5_R = new GButton(this, 250, 40, 80, 30);
  btn5_R.setText("R");
  btn5_R.addEventHandler(this, "btn5_R_click1");
  btn5_U = new GButton(this, 200, 10, 80, 30);
  btn5_U.setText("U");
  btn5_U.addEventHandler(this, "btn5_U_click1");
  btn5_D = new GButton(this, 200, 70, 80, 30);
  btn5_D.setText("D");
  btn5_D.addEventHandler(this, "btn5_D_click1");
  button_pause = new GButton(this, 510, 130, 70, 30);
  button_pause.setText("pause");
  button_pause.addEventHandler(this, "button_pause_click1");
  button_clear = new GButton(this, 510, 100, 70, 20);
  button_clear.setText("clear");
  button_clear.addEventHandler(this, "button_clear_click1");
  slider_effN = new GSlider(this, 150, 260, 430, 40, 10.0);
  slider_effN.setLimits(1, 0, 255);
  slider_effN.setNbrTicks(26);
  slider_effN.setNumberFormat(G4P.INTEGER, 0);
  slider_effN.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  slider_effN.setOpaque(false);
  slider_effN.addEventHandler(this, "slider_effN_change1");
  slider_speed = new GSlider(this, 20, 290, 560, 40, 10.0);
  slider_speed.setLimits(1, 0, 180);
  slider_speed.setNbrTicks(18);
  slider_speed.setNumberFormat(G4P.INTEGER, 0);
  slider_speed.setOpaque(false);
  slider_speed.addEventHandler(this, "slider_speed_change1");
  slider_length = new GSlider(this, 20, 320, 560, 40, 10.0);
  slider_length.setShowValue(true);
  slider_length.setLimits(1, 1, 255);
  slider_length.setNbrTicks(26);
  slider_length.setNumberFormat(G4P.INTEGER, 0);
  slider_length.setOpaque(false);
  slider_length.addEventHandler(this, "slider_length_change1");
  slider_RGB = new GSlider(this, 20, 500, 480, 50, 10.0);
  slider_RGB.setLimits(0, 0, 8);
  slider_RGB.setNbrTicks(9);
  slider_RGB.setStickToTicks(true);
  slider_RGB.setNumberFormat(G4P.INTEGER, 0);
  slider_RGB.setOpaque(false);
  slider_RGB.addEventHandler(this, "slider_RGB_change1");
  button_action = new GButton(this, 320, 170, 260, 30);
  button_action.setText("Action");
  button_action.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  button_action.addEventHandler(this, "button_action_click1");
  button_reset = new GButton(this, 430, 100, 70, 20);
  button_reset.setText("Reset");
  button_reset.addEventHandler(this, "button_reset_click1");
  button_effNsub = new GButton(this, 70, 270, 30, 20);
  button_effNsub.setText("-");
  button_effNsub.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button_effNsub.addEventHandler(this, "button_effNsub_click1");
  button_effNAdd = new GButton(this, 110, 270, 30, 20);
  button_effNAdd.setText("+");
  button_effNAdd.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button_effNAdd.addEventHandler(this, "button_effNAdd_click1");
  slider_brightness = new GSlider(this, 671, 10, 490, 41, 10.0);
  slider_brightness.setRotation(PI/2, GControlMode.CORNER);
  slider_brightness.setLimits(33, 255, 1);
  slider_brightness.setNumberFormat(G4P.INTEGER, 0);
  slider_brightness.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  slider_brightness.setOpaque(true);
  slider_brightness.addEventHandler(this, "slider_brightness_change1");
  slider_speedH = new GSlider(this, 20, 350, 480, 40, 10.0);
  slider_speedH.setLimits(1, 0, 255);
  slider_speedH.setNumberFormat(G4P.INTEGER, 0);
  slider_speedH.setOpaque(false);
  slider_speedH.addEventHandler(this, "slider_speedH_change1");
  slider_lengthH = new GSlider(this, 20, 380, 480, 40, 10.0);
  slider_lengthH.setLimits(44, 1, 240);
  slider_lengthH.setNumberFormat(G4P.INTEGER, 0);
  slider_lengthH.setOpaque(false);
  slider_lengthH.addEventHandler(this, "slider_lengthH_change1");
  label_effN = new GLabel(this, 530, 280, 50, 20);
  label_effN.setText("eff №");
  label_effN.setOpaque(false);
  label_speed = new GLabel(this, 540, 310, 50, 20);
  label_speed.setText("speed");
  label_speed.setOpaque(false);
  label_length = new GLabel(this, 540, 340, 50, 20);
  label_length.setText("length");
  label_length.setOpaque(false);
  label_RGB = new GLabel(this, 510, 500, 80, 20);
  label_RGB.setText("R       G       B");
  label_RGB.setOpaque(false);
  label_speedH = new GLabel(this, 420, 370, 60, 20);
  label_speedH.setText("speed H");
  label_speedH.setOpaque(false);
  label_lengthH = new GLabel(this, 420, 400, 60, 20);
  label_lengthH.setText("length H");
  label_lengthH.setOpaque(false);
  label_brightness = new GLabel(this, 620, 500, 60, 20);
  label_brightness.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_brightness.setText("brightness");
  label_brightness.setOpaque(false);
  label_effN_val = new GLabel(this, 20, 270, 40, 20);
  label_effN_val.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_effN_val.setText("1");
  label_effN_val.setOpaque(false);
  slider_action = new GSlider(this, 629, 10, 250, 40, 10.0);
  slider_action.setRotation(PI/2, GControlMode.CORNER);
  slider_action.setLimits(0, 0, 5);
  slider_action.setStickToTicks(true);
  slider_action.setNumberFormat(G4P.INTEGER, 0);
  slider_action.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  slider_action.setOpaque(false);
  slider_action.addEventHandler(this, "slider_action_change");
  label_SerialSpeed = new GLabel(this, 500, 10, 80, 20);
  label_SerialSpeed.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_SerialSpeed.setText("0");
  label_SerialSpeed.setTextItalic();
  label_SerialSpeed.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  label_SerialSpeed.setOpaque(false);
  button_disconnect = new GButton(this, 500, 40, 80, 20);
  button_disconnect.setText("disconnect");
  button_disconnect.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  button_disconnect.addEventHandler(this, "button_disconnect_click");
  effN_random = new GButton(this, 320, 240, 60, 20);
  effN_random.setText("random");
  effN_random.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  effN_random.addEventHandler(this, "effN_random_click");
  effN_animate = new GButton(this, 390, 210, 80, 20);
  effN_animate.setText("animate to 1");
  effN_animate.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  effN_animate.addEventHandler(this, "effN_animate_click");
  effN_animate_continue = new GButton(this, 320, 210, 60, 20);
  effN_animate_continue.setText("animate");
  effN_animate_continue.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  effN_animate_continue.addEventHandler(this, "effN_animate_continue_click");
  effN_demoRandom = new GButton(this, 510, 240, 70, 20);
  effN_demoRandom.setText("demo rand");
  effN_demoRandom.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  effN_demoRandom.addEventHandler(this, "effN_demoRandom_click");
  effN_demoRandom_fast = new GButton(this, 390, 240, 110, 20);
  effN_demoRandom_fast.setText("demo random fast");
  effN_demoRandom_fast.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  effN_demoRandom_fast.addEventHandler(this, "effN_demoRandom_fast_click");
  button_effN_seq = new GButton(this, 270, 240, 40, 20);
  button_effN_seq.setText("seq");
  button_effN_seq.setLocalColorScheme(GCScheme.SCHEME_8);
  button_effN_seq.addEventHandler(this, "button_effN_seq_click");
  button_animateRandom = new GButton(this, 480, 210, 100, 20);
  button_animateRandom.setText("animate random");
  button_animateRandom.setLocalColorScheme(GCScheme.GREEN_SCHEME);
  button_animateRandom.addEventHandler(this, "button_animateRandom_click1");
  button_codeGen = new GButton(this, 400, 70, 180, 20);
  button_codeGen.setText("generate case for switch(mode)");
  button_codeGen.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  button_codeGen.addEventHandler(this, "button_codeGen_click");
  label_instruction1 = new GLabel(this, 610, 544, 90, 10);
  label_instruction1.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_instruction1.setText("need fix");
  label_instruction1.setTextBold();
  label_instruction1.setLocalColorScheme(GCScheme.RED_SCHEME);
  label_instruction1.setOpaque(true);
  label_instruction2 = new GLabel(this, 610, 560, 90, 10);
  label_instruction2.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_instruction2.setText("best");
  label_instruction2.setTextBold();
  label_instruction2.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  label_instruction2.setOpaque(true);
  label_instruction3 = new GLabel(this, 610, 576, 90, 12);
  label_instruction3.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_instruction3.setText("less interesting");
  label_instruction3.setOpaque(false);
  slider_gDelay = new GSlider(this, 630, 260, 240, 40, 10.0);
  slider_gDelay.setRotation(PI/2, GControlMode.CORNER);
  slider_gDelay.setLimits(0.5, 0.0, 1.0);
  slider_gDelay.setNumberFormat(G4P.DECIMAL, 2);
  slider_gDelay.setOpaque(false);
  slider_gDelay.addEventHandler(this, "slider_gDelay_change1");
  slider_effFade = new GSlider(this, 20, 410, 480, 40, 10.0);
  slider_effFade.setLimits(0.5, 0.0, 1.0);
  slider_effFade.setNumberFormat(G4P.DECIMAL, 2);
  slider_effFade.setOpaque(false);
  slider_effFade.addEventHandler(this, "slider_effFade_change");
  slider_indexOrBits = new GSlider(this, 20, 440, 480, 40, 10.0);
  slider_indexOrBits.setLimits(0.5, 0.0, 1.0);
  slider_indexOrBits.setNumberFormat(G4P.DECIMAL, 2);
  slider_indexOrBits.setOpaque(false);
  slider_indexOrBits.addEventHandler(this, "slider_indexOrBits_change");
  slider_gColorH = new GSlider(this, 530, 390, 110, 30, 10.0);
  slider_gColorH.setRotation(PI/2, GControlMode.CORNER);
  slider_gColorH.setLimits(0.5, 0.0, 1.0);
  slider_gColorH.setNumberFormat(G4P.DECIMAL, 2);
  slider_gColorH.setOpaque(false);
  slider_gColorH.addEventHandler(this, "slider_gColorH_change");
  slider_gColorS = new GSlider(this, 560, 390, 110, 30, 10.0);
  slider_gColorS.setRotation(PI/2, GControlMode.CORNER);
  slider_gColorS.setLimits(0.5, 0.0, 1.0);
  slider_gColorS.setNumberFormat(G4P.DECIMAL, 2);
  slider_gColorS.setOpaque(false);
  slider_gColorS.addEventHandler(this, "slider_gColorS_change");
  slider_gColorV = new GSlider(this, 590, 390, 110, 30, 10.0);
  slider_gColorV.setRotation(PI/2, GControlMode.CORNER);
  slider_gColorV.setLimits(0.5, 0.0, 1.0);
  slider_gColorV.setNumberFormat(G4P.DECIMAL, 2);
  slider_gColorV.setOpaque(false);
  slider_gColorV.addEventHandler(this, "slider_gColorV_change");
  slider_NUM_LEDS = new GSlider(this, 20, 470, 480, 40, 10.0);
  slider_NUM_LEDS.setLimits(0.5, 0.0, 1.0);
  slider_NUM_LEDS.setNumberFormat(G4P.DECIMAL, 2);
  slider_NUM_LEDS.setOpaque(false);
  slider_NUM_LEDS.addEventHandler(this, "NUM_LEDS_change");
  button_msgprint = new GButton(this, 380, 40, 80, 20);
  button_msgprint.setText("print palette");
  button_msgprint.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  button_msgprint.addEventHandler(this, "button_msgprint_click");
  label_gDelay = new GLabel(this, 590, 500, 40, 20);
  label_gDelay.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_gDelay.setText("gD");
  label_gDelay.setOpaque(false);
  button_sim = new GButton(this, 380, 10, 40, 20);
  button_sim.setText("sim");
  button_sim.setTextItalic();
  button_sim.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  button_sim.addEventHandler(this, "button_sim_click");
  btn_copy_switch_nms = new GButton(this, 350, 70, 40, 20);
  btn_copy_switch_nms.setText("list");
  btn_copy_switch_nms.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  btn_copy_switch_nms.addEventHandler(this, "btn_copy_switch_nms_click");
  btn_matrix_zigZag_h = new GButton(this, 20, 210, 50, 20);
  btn_matrix_zigZag_h.setText("zig-zag");
  btn_matrix_zigZag_h.setTextItalic();
  btn_matrix_zigZag_h.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn_matrix_zigZag_h.addEventHandler(this, "btn_matrix_zigZag_h_click");
  btn_matrix_spiral_cw = new GButton(this, 80, 210, 60, 20);
  btn_matrix_spiral_cw.setText("spiral");
  btn_matrix_spiral_cw.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn_matrix_spiral_cw.addEventHandler(this, "btn_matrix_spiral_cw_click");
  btn_labyrinth_cw = new GButton(this, 150, 210, 60, 20);
  btn_labyrinth_cw.setText("labyrinth");
  btn_labyrinth_cw.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn_labyrinth_cw.addEventHandler(this, "btn_labyrinth_cw_click");
  btn_mirror_half = new GButton(this, 220, 210, 50, 20);
  btn_mirror_half.setText("mirror");
  btn_mirror_half.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn_mirror_half.addEventHandler(this, "btn_mirror_half_click");
  btn_history = new GButton(this, 280, 210, 30, 20);
  btn_history.setText("hist");
  btn_history.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn_history.addEventHandler(this, "btn_history_click");
  label_matrix = new GLabel(this, 20, 190, 140, 20);
  label_matrix.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_matrix.setText("matrix map type toggle:");
  label_matrix.setTextItalic();
  label_matrix.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  label_matrix.setOpaque(false);
  checkbox_LEDs_customGeom = new GCheckbox(this, 490, 590, 210, 20);
  checkbox_LEDs_customGeom.setIconAlign(GAlign.LEFT, GAlign.MIDDLE);
  checkbox_LEDs_customGeom.setText("F3 = draw LEDs (mouse, ctrl, shift)");
  checkbox_LEDs_customGeom.setOpaque(false);
  checkbox_LEDs_customGeom.addEventHandler(this, "checkbox_LEDs_customGeom_cl");
}

// Variable declarations 
// autogenerated do not edit
GButton btn3_L; 
GButton btn3_M; 
GButton btn3_R; 
GButton btn5_select; 
GButton btn5_L; 
GButton btn5_R; 
GButton btn5_U; 
GButton btn5_D; 
GButton button_pause; 
GButton button_clear; 
GSlider slider_effN; 
GSlider slider_speed; 
GSlider slider_length; 
GSlider slider_RGB; 
GButton button_action; 
GButton button_reset; 
GButton button_effNsub; 
GButton button_effNAdd; 
GSlider slider_brightness; 
GSlider slider_speedH; 
GSlider slider_lengthH; 
GLabel label_effN; 
GLabel label_speed; 
GLabel label_length; 
GLabel label_RGB; 
GLabel label_speedH; 
GLabel label_lengthH; 
GLabel label_brightness; 
GLabel label_effN_val; 
GSlider slider_action; 
GLabel label_SerialSpeed; 
GButton button_disconnect; 
GButton effN_random; 
GButton effN_animate; 
GButton effN_animate_continue; 
GButton effN_demoRandom; 
GButton effN_demoRandom_fast; 
GButton button_effN_seq; 
GButton button_animateRandom; 
GButton button_codeGen; 
GLabel label_instruction1; 
GLabel label_instruction2; 
GLabel label_instruction3; 
GSlider slider_gDelay; 
GSlider slider_effFade; 
GSlider slider_indexOrBits; 
GSlider slider_gColorH; 
GSlider slider_gColorS; 
GSlider slider_gColorV; 
GSlider slider_NUM_LEDS; 
GButton button_msgprint; 
GLabel label_gDelay; 
GButton button_sim; 
GButton btn_copy_switch_nms; 
GButton btn_matrix_zigZag_h; 
GButton btn_matrix_spiral_cw; 
GButton btn_labyrinth_cw; 
GButton btn_mirror_half; 
GButton btn_history; 
GLabel label_matrix; 
GCheckbox checkbox_LEDs_customGeom; 
