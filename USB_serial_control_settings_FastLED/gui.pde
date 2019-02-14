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
																																				//println("slider event");
																																				//println(event.getType());
																																				//println(bSkipEvent);
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
	settingsVals.get("bright").setValue(source.getValueI());
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
	if(bConnected==2)
	{
		myPort.clear();
		myPort.stop();
		myPort=null;
		bConnected=0;
		button_disconnect.setText("Connect");
	}
	else
	{
		bConnected=1;
		button_disconnect.setText("Disonnect");
	}
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

// copyToClipboard(
// 	"case 1"+
// 	Integer.toString(settingsVals.get("effN").value)+
// 	": anim_f=??;				effSpeed="+
// 	Integer.toString(settingsVals.get("speed").value)+
// 	";	effLength="+
// 	Integer.toString(settingsVals.get("length").value)+
// 	";	RGB="+
// 	Integer.toString(settingsVals.get("RGB").value)+
// 	";	break;"
// );
copyToClipboard(
	"	case "+
	Integer.toString(settingsVals.get("effN").valueSlider.getValueI())+  //!fix values has to be setted by Serial, not only slider pos. Bus seems it has not
	": anim_f=??;				effSpeed="+
	Integer.toString(settingsVals.get("speed").valueSlider.getValueI())+
	";		effLength="+
	Integer.toString(settingsVals.get("length").valueSlider.getValueI())+
	";		effDisableChennel="+
	Integer.toString(settingsVals.get("RGB").valueSlider.getValueI())+
	"; break;"
);

} //_CODE_:button_codeGen:274298:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  btn3_L = new GButton(this, 20, 130, 80, 30);
  btn3_L.setText("L");
  btn3_L.addEventHandler(this, "btn3_L_click1");
  btn3_M = new GButton(this, 110, 130, 130, 30);
  btn3_M.setText("Mode");
  btn3_M.setLocalColorScheme(GCScheme.CYAN_SCHEME);
  btn3_M.addEventHandler(this, "btn3_M_click1");
  btn3_R = new GButton(this, 250, 130, 80, 30);
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
  button_pause = new GButton(this, 200, 200, 80, 30);
  button_pause.setText("pause");
  button_pause.addEventHandler(this, "button_pause_click1");
  button_clear = new GButton(this, 110, 200, 80, 30);
  button_clear.setText("clear");
  button_clear.addEventHandler(this, "button_clear_click1");
  slider_effN = new GSlider(this, 20, 260, 560, 40, 10.0);
  slider_effN.setShowValue(true);
  slider_effN.setLimits(1, 0, 255);
  slider_effN.setNbrTicks(26);
  slider_effN.setNumberFormat(G4P.INTEGER, 0);
  slider_effN.setOpaque(false);
  slider_effN.addEventHandler(this, "slider_effN_change1");
  slider_speed = new GSlider(this, 20, 300, 560, 40, 10.0);
  slider_speed.setShowValue(true);
  slider_speed.setLimits(1, 0, 180);
  slider_speed.setNbrTicks(18);
  slider_speed.setNumberFormat(G4P.INTEGER, 0);
  slider_speed.setOpaque(false);
  slider_speed.addEventHandler(this, "slider_speed_change1");
  slider_length = new GSlider(this, 20, 340, 560, 40, 10.0);
  slider_length.setShowValue(true);
  slider_length.setLimits(1, 1, 255);
  slider_length.setNbrTicks(26);
  slider_length.setNumberFormat(G4P.INTEGER, 0);
  slider_length.setOpaque(false);
  slider_length.addEventHandler(this, "slider_length_change1");
  slider_RGB = new GSlider(this, 20, 380, 460, 50, 10.0);
  slider_RGB.setShowValue(true);
  slider_RGB.setLimits(0, 0, 8);
  slider_RGB.setNbrTicks(9);
  slider_RGB.setStickToTicks(true);
  slider_RGB.setNumberFormat(G4P.INTEGER, 0);
  slider_RGB.setOpaque(false);
  slider_RGB.addEventHandler(this, "slider_RGB_change1");
  button_action = new GButton(this, 410, 160, 170, 30);
  button_action.setText("Action");
  button_action.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  button_action.addEventHandler(this, "button_action_click1");
  button_reset = new GButton(this, 20, 200, 80, 30);
  button_reset.setText("Reset");
  button_reset.addEventHandler(this, "button_reset_click1");
  button_effNsub = new GButton(this, 70, 240, 30, 20);
  button_effNsub.setText("-");
  button_effNsub.addEventHandler(this, "button_effNsub_click1");
  button_effNAdd = new GButton(this, 110, 240, 30, 20);
  button_effNAdd.setText("+");
  button_effNAdd.addEventHandler(this, "button_effNAdd_click1");
  slider_brightness = new GSlider(this, 671, 10, 490, 41, 10.0);
  slider_brightness.setShowValue(true);
  slider_brightness.setRotation(PI/2, GControlMode.CORNER);
  slider_brightness.setLimits(33, 255, 1);
  slider_brightness.setNumberFormat(G4P.INTEGER, 0);
  slider_brightness.setLocalColorScheme(GCScheme.GOLD_SCHEME);
  slider_brightness.setOpaque(true);
  slider_brightness.addEventHandler(this, "slider_brightness_change1");
  slider_speedH = new GSlider(this, 20, 430, 560, 40, 10.0);
  slider_speedH.setShowValue(true);
  slider_speedH.setLimits(1, 0, 255);
  slider_speedH.setNumberFormat(G4P.INTEGER, 0);
  slider_speedH.setOpaque(false);
  slider_speedH.addEventHandler(this, "slider_speedH_change1");
  slider_lengthH = new GSlider(this, 20, 470, 560, 40, 10.0);
  slider_lengthH.setShowValue(true);
  slider_lengthH.setLimits(44, 1, 240);
  slider_lengthH.setNumberFormat(G4P.INTEGER, 0);
  slider_lengthH.setOpaque(false);
  slider_lengthH.addEventHandler(this, "slider_lengthH_change1");
  label_effN = new GLabel(this, 580, 270, 50, 20);
  label_effN.setText("eff №");
  label_effN.setOpaque(false);
  label_speed = new GLabel(this, 580, 310, 50, 20);
  label_speed.setText("speed");
  label_speed.setOpaque(false);
  label_length = new GLabel(this, 580, 350, 50, 20);
  label_length.setText("length");
  label_length.setOpaque(false);
  label_RGB = new GLabel(this, 580, 396, 50, 20);
  label_RGB.setText("RGB");
  label_RGB.setOpaque(false);
  label_speedH = new GLabel(this, 580, 440, 60, 20);
  label_speedH.setText("speed H");
  label_speedH.setOpaque(false);
  label_lengthH = new GLabel(this, 580, 480, 60, 20);
  label_lengthH.setText("length H");
  label_lengthH.setOpaque(false);
  label_brightness = new GLabel(this, 620, 500, 60, 20);
  label_brightness.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_brightness.setText("brightness");
  label_brightness.setOpaque(false);
  label_effN_val = new GLabel(this, 20, 240, 40, 20);
  label_effN_val.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_effN_val.setText("1");
  label_effN_val.setOpaque(false);
  slider_action = new GSlider(this, 629, 10, 250, 40, 10.0);
  slider_action.setShowValue(true);
  slider_action.setRotation(PI/2, GControlMode.CORNER);
  slider_action.setLimits(0, 0, 5);
  slider_action.setStickToTicks(true);
  slider_action.setShowTicks(true);
  slider_action.setNumberFormat(G4P.INTEGER, 0);
  slider_action.setLocalColorScheme(GCScheme.ORANGE_SCHEME);
  slider_action.setOpaque(false);
  slider_action.addEventHandler(this, "slider_action_change");
  label_SerialSpeed = new GLabel(this, 490, 10, 80, 20);
  label_SerialSpeed.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  label_SerialSpeed.setText("0");
  label_SerialSpeed.setTextItalic();
  label_SerialSpeed.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  label_SerialSpeed.setOpaque(false);
  button_disconnect = new GButton(this, 490, 40, 80, 20);
  button_disconnect.setText("disconnect");
  button_disconnect.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
  button_disconnect.addEventHandler(this, "button_disconnect_click");
  effN_random = new GButton(this, 320, 240, 60, 20);
  effN_random.setText("random");
  effN_random.addEventHandler(this, "effN_random_click");
  effN_animate = new GButton(this, 390, 210, 80, 20);
  effN_animate.setText("animate to 1");
  effN_animate.addEventHandler(this, "effN_animate_click");
  effN_animate_continue = new GButton(this, 320, 210, 60, 20);
  effN_animate_continue.setText("animate");
  effN_animate_continue.addEventHandler(this, "effN_animate_continue_click");
  effN_demoRandom = new GButton(this, 510, 240, 70, 20);
  effN_demoRandom.setText("demo rand");
  effN_demoRandom.addEventHandler(this, "effN_demoRandom_click");
  effN_demoRandom_fast = new GButton(this, 390, 240, 110, 20);
  effN_demoRandom_fast.setText("demo random fast");
  effN_demoRandom_fast.addEventHandler(this, "effN_demoRandom_fast_click");
  button_effN_seq = new GButton(this, 150, 240, 40, 20);
  button_effN_seq.setText("seq");
  button_effN_seq.setLocalColorScheme(GCScheme.SCHEME_8);
  button_effN_seq.addEventHandler(this, "button_effN_seq_click");
  button_animateRandom = new GButton(this, 480, 210, 100, 20);
  button_animateRandom.setText("animate random");
  button_animateRandom.addEventHandler(this, "button_animateRandom_click1");
  button_codeGen = new GButton(this, 390, 70, 180, 20);
  button_codeGen.setText("generate code for switch(mode)");
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
