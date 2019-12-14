/* TODO
gen HTML link
drop image, create array
test sending to MCU 
set NUM_LEDS_slider setup

fix app folder in root of disc, so find filed can't go in parent
link switch_slot.h to relise 

mode 168|328|full  to not show unavalable eff

fix load btn must not call effSet msg.   Avoid double event

ask again for fix g4p event for press because bo fix absense  of drag tolerance in Java-Swing (de-facto, he also confirm) and no other event available in current g4p version to workout this
*/
int useSerialPortN=0;

static int serialSpeed=1000000;//1000000 921600 500000 115200 57600//this may be redefined with command line arg. For ESP32 (cp2102) change to 921600 otherwise it buggy work and you spend many time to find why.

boolean b_Cube=true; //set NUM_LEDS_slider to Max; Use to calculate current.
boolean b_NUM_LEDS_adj=false;//true false //! fix adj mode especially if no adjustable set in MCU

//5 30 60 120 144 150 180 300 450
int NUM_LEDS_slider_startup=16*16;//150;//105;//60*3;//105; //145*3*4 60*8 15*8 8*8 16*16  //this is also max for draw gemetry arr DrawLEDs_pointsX 
int NUM_LEDS_slider_m=60;
int NUM_LEDS_slider_M=16*16;

int matrix_rowsE=8;//8 16  horizontal L-to-R //for plotPX //TODO2 vertiacal
boolean NUM_LEDS_x8=false;// true false // have to be true if gNUM_LEDS>255 , so we can send it with 1 byte


boolean bFlipArr_sim_to_zigZag_matrix=false; //for sim. If true - flips data before send to plot and MCU. MATRIX Plot also flip data by default plotPX.b_matrix_arr_is_zigZag

int bSetBrightnessAtConnect=33; //-1 for not set

boolean bDebugPrint=true;//false true
boolean bDebugXY=false; //ctrl - toggle

boolean bSendSimDataToMCU=true;

//performance
 boolean bRecieveLEDdata=true;

 boolean bDrawLEDs_PXHistory_enabled=true;
 boolean bDrawLEDs_enabled=true;
 boolean bDrawLEDs_customGeometry=true; //F3 toggle draw

 boolean bPlotPow_enabled=false; //! opt>400 LEDs
 boolean bPlotPowBig_enabled=false; //!!!TODO
 boolean bDraw_plot_RGB_pow=false;

 boolean bPlot_FPS_enabled=true; //# but show FPS num
 
 boolean bSim=false; //startup state
/*
 boolean bRecieveLEDdata=true;

 boolean bDrawLEDs_PXHistory_enabled=true;
 boolean bDrawLEDs_enabled=true;

 boolean bPlotPow_enabled=true;
 boolean bDraw_plot_RGB_pow=true;

 boolean bPlot_FPS_enabled=true; //# but show FPS num
 */
/*
boolean bRecieveLEDdata=true;

boolean bDrawLEDs_PXHistory_enabled=false;
boolean bDrawLEDs_enabled=true;

boolean bPlotPow_enabled=false;
boolean bDraw_plot_RGB_pow=false;

boolean bPlot_FPS_enabled=false; //# but show FPS num
*/


boolean bbtn_matrix_state=false;
void set_bbtn_matrix_state(int value)
{
  settingsVals.get("effN").setValue(value); 
  if(bbtn_matrix_state)
  {
   bbtn_matrix_state=false;
   label_matrix.setTextPlain();
  }
  else
  {
   bbtn_matrix_state=true;
   label_matrix.setTextBold();
  }
}

int gColorBgB=200;//200;
color gColorBg=color(gColorBgB);//200;
color gColorTxt=color(0);//200;



String DebugPrint_str_last="";
void  bDebugPrint_notSame_bRed(String str, boolean bRed)
{
	if(!bDebugPrint || str.equals(DebugPrint_str_last)) return;
	
	if(bRed) System.err.println(str);
	else				println(str);
	
	DebugPrint_str_last=str;
}

import java.util.Map;
import java.util.LinkedHashMap;

import java.util.Date;

//==================================================== Clipboard
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import javax.swing.*;
import java.io.*;
void copyToClipboard(String selection) //https://forum.processing.org/one/topic/what-is-the-simplest-way-to-copy-to-the-clipboard-from-processing.html
{
		bDebugPrint_notSame_bRed(selection, false);
	StringSelection data = new StringSelection(selection);
	Clipboard clipboard = 
	Toolkit.getDefaultToolkit().getSystemClipboard();
	clipboard.setContents(data, data);
}
String printVal(String str, String nm, int bSkipIfEqual)
{
	int value=settingsVals.get(nm).valueSlider.getValueI();
	if( value==bSkipIfEqual) return "";
	return "	"+str+"="+	Integer.toString(value)+";";
}
//====================================================

int bConnected=1; //0 off, 1 try connect, 2 connected
boolean bSkipEvent=false;

void setupValues() //set and display
{
	//settingsVals.get("effN").setValue(0);
	bSkipEvent=true;
	settingsVals.get("action").setValue(0);
	bSkipEvent=false;
}

import g4p_controls.*;
import processing.serial.*;
Serial myPort;


static int effN_PAUSE=0;

private LinkedHashMap<String, settingsVal> settingsVals = new LinkedHashMap<String, settingsVal>();
String actionNm[]={
"flashLEDs","invertLEDs","addGlitter","flashAndBackLEDs","scroll1cycle_continued","scroll1cycle_continuedRev","fadeOut_continued","moveOut_continued","offPixel_continued",
"","","","","",""
}; //upd arr size at put("action",
int actionsM=10;

boolean rCh=true,gCh=true,bCh=true;
void drawRGB(int chen)
{
		rCh=true;gCh=true;bCh=true;	
	if(chen==1 ||chen==4||chen==5)
		rCh=false; 
	if(chen==2 ||chen==5||chen==6)
		gCh=false;
	if(chen==3 ||chen==6||chen==4)
		bCh=false; 
}
long bSkipEvent_off_t=0;
class settingsVal
{
	public String nm;
	public int value;
	public void setValue(int v)
	{
		//if(value==v && value<239) return; // send again only № that toggle some settings at controller
		value=v;

		if(nm=="effN") //rollover
		{
			if(value>value_M) value=value_m;
			else
			if(value<value_m) value=value_M;
		}
		else //constrain
		{
			if(value>value_M) value=value_M;
			else
			if(value<value_m) value=value_m;
		}
//----------------------------------------------------------- upd GUI
		if(valueSlider!=null)
		{
			bSkipEvent=true;
			bSkipEvent_off_t=millis()+10;
			valueSlider.setValue(value);
		}
		if(nm=="effN") 
		{
			label_effN_val.setText(Integer.toString(value));

			if(mouseX<effParsedList_btns_posX+40)
			for (int i=0; i<effParsedList_btns_i-1; i++)
			{
				GButton btn=effParsedList_btns[i];
				if(btn.tagNo==value) scroll_effParsedList_btns_toTopFor(i);
			}
		}
		else
		if(nm=="RGB") drawRGB(value);
//-----------------------------------------------------------

		if(nm=="NUM_LEDS")
		{
			if(b_NUM_LEDS_adj)
			{
				if(NUM_LEDS_x8) 
					SendMsg(message_code, value/8); // msg is 1 byte
				else
					SendMsg(message_code, value);
			}
		}
		else
					SendMsg(message_code, value);
	}

	void add()
	{
		setValue(value+1);
	}

	void sub()
	{
		setValue(value-1);
	}

	public int value_m;
	public int value_M;
	public int message_code;
	GLabel valueLabel;
	GSlider valueSlider;
	public settingsVal(String n, int v, int vm, int vM, int code, GLabel label, GSlider slider)
	{
		nm=n;
		value=v;
		value_m=vm;
		value_M=vM;
		message_code=code;
		valueLabel=label;
		valueSlider=slider;

		if(valueSlider!=null)
		{
			valueSlider.setNumberFormat(G4P.INTEGER, 0);
			valueSlider.setLimits(1, vm, vM);
			valueSlider.setShowValue(true);
			
			if(nm=="NUM_LEDS") setValue(value);

			if(value_M<25)
			{
				valueSlider.setNbrTicks(value_M+1);
				valueSlider.setStickToTicks(true);
			}
			else
			if(value_M<50)
			{
				valueSlider.setNbrTicks(vM/5+1);
			}
			else
			valueSlider.setNbrTicks(value_M/20+1);
			if(labelColor>=0)
			{
				valueSlider.setLocalColor(2, color(labelColor));
			}

			//.addEventHandler(this, "slider_RGB_change1"); //!

			if(label==null && !nm.equals("action") && !nm.equals("gDelay") && !nm.contains("gColor"))
			{

        if(nm=="NUM_LEDS")
        {
          label = new GLabel(valueSlider.getPApplet(), valueSlider.getX()+220, valueSlider.getY()+22, 280, 20); //+125 -1
          label.setText(nm+" must be enabled in app and MCU");
        }
        else
        {
           label = new GLabel(valueSlider.getPApplet(), valueSlider.getX()+420, valueSlider.getY()+22, 80, 20); //+125 -1
           label.setText(nm);   
        }
        //label.resizeToFit(true, false);
  				label.setOpaque(false);
  				if(labelColor>=0)
  				{
  					label.setLocalColor(2, color(labelColor));
  				}
			}
		}

	}
}

settingsVal getsettingsVal_by_mode_N(int mode_N)
{
	return settingsVals.get((new ArrayList(settingsVals.keySet())).get(mode_N));
}

int mode;
static int mode_M=7; //sliders arr

GButton[] slots_s=new GButton[10];
GButton[] slots=new GButton[10];

boolean bModeSent=false;
int mode_last;
void modeChanged()
{
	if(mode>mode_M) mode=0;
	else
	if(mode<0) mode=mode_M;

	 settingsVal sett=getsettingsVal_by_mode_N(mode);

	btn3_M.setText("Mode:"+sett.nm);
	btn5_select.setText("Mode:"+sett.nm);

	if(sett.valueLabel!=null)	sett.valueLabel.setTextBold();
	if(mode_last!=mode) 
	{
		GLabel lab=getsettingsVal_by_mode_N(mode_last).valueLabel;
		if(lab!=null) lab.setTextPlain();
		
		mode_last=mode;
	}

	bModeSent=false;
}

void add(int mode_N)
{
	getsettingsVal_by_mode_N(mode_N).add();
}

void sub(int mode_N)
{
	getsettingsVal_by_mode_N(mode_N).sub();
}




public void slots_click(GButton source, GEvent event) {
	if ( event != GEvent.CLICKED) return;
	int slot_N=-1;
	int msgCode=-1;		

	if(source.tag.equals("s")) //serial commant to save
	{
		source.setText(Integer.toString(settingsVals.get("effN").value));

		msgCode=settingsVals.get("save").message_code;

		bModeSent=true;
		SendMsg(msgCode, source.tagNo);
	}
	else // commant to load
	{
		//msgCode=settingsVals.get("load").message_code; // not need because slots 0...9 loads
		settingsVals.get("effN").setValue( source.tagNo);
	}
}

void SendMsg(int msgCode, int val)
{
	//if(!bModeSent  //!!
	if(myPort==null)
	{
		button_disconnect.setText("not sent");
		return;
	}
		if(bDebugPrint){ println(msgCode,": ",val, "-sent---->>");}
	myPort.write(msgCode);
	myPort.write(msgCode);

	myPort.write(val);
}

void put(String n, int v, int vm, int vM, int code, GLabel label, GSlider slider)
{
	settingsVals.put(n, new settingsVal(n, v, vm, vM, code, label, slider));
}


Plot12 plotFPS;
Plot12 plot_pow;

Plot12 plotR; //from plotPX 
Plot12 plotG;
Plot12 plotB;
PlotPX plotPX;
boolean bplotPX=true;

int labelColor=-1;

int widthNormal=920;
public void setup(){
	size(920, 640); //, P3D); //widthNormal
	frameRate(144); //!! TODO test wht is rate is slower than USB
	surface.setResizable(true); 
	
    try
    {
	if (args != null && args.length != 0){ //$ processing-java --sketch=sketchname --run argu "arg o"
		serialSpeed=Integer.parseInt(args[0]);
    if(args.length >1)
        useSerialPortN=Integer.parseInt(args[1]);
	}
 }catch(Exception e){ button_disconnect.setText("err"); }


	//-------------------------------------------
	float rnd=random(200);
	if ( day()==1 && month()%5==0) {gColorBg= color(200,0,0); labelColor=0;} //changeSilerTextColor(color(0));
	else 
	if ( day()%4==0 && rnd<10) {gColorBg= color(0,0,0);labelColor=255;} //!! also labels
	else 
	if ( day()%3==0 && rnd<20) {gColorBg= color(44);labelColor=255;}
	else 
	if ( rnd>50) gColorBg= color(200);
	else 
	if ( rnd>40) gColorBg= color(165.0, 173.0, 173.0);
	else 
	if ( rnd>30) gColorBg= color(164.0, 196.0, 196.0);
	else 
	if ( rnd>20) gColorBg= color(237.0, 255.0, 241.0);
	else 
	if ( rnd>10) gColorBg= color(226.0, 255.0, 161.0);
	else 
	if ( rnd>5) gColorBg= color(255.0, 216.0, 216.0);
	else 
	if ( rnd>3) gColorBg= color(255.0, 255.0, 168.0);
	else 
	if ( rnd>2) gColorBg= color(255.0, 255.0, 63.0);
	else 
	if ( rnd>1) gColorBg= color(4.0, 171.0, 171.0);
	else 
	 { gColorBg= color(0, 0, 255); labelColor=255;} 
	//-------------------------------------------
	createGUI();
	customGUI();

  //first 5, so mode_N is right
	put("effN",		0,0,255,241,label_effN,slider_effN);
	put("speed",	1,0,255,242,label_speed,slider_speed); //! uniform names
	put("length",	9,1,255,243,label_length,slider_length);
	put("RGB",		0,0, 21,244,label_RGB,slider_RGB);
	put("gBrightness",	0,1,111,247,label_brightness,slider_brightness);


	put("gDelay",	0,0,100,234,null,slider_gDelay);
	put("effFade",	0,0,255,235,null,slider_effFade);
	put("gColorH",	255,0,255,236,null,slider_gColorH);
	put("gColorS",	127,0,255,237,null,slider_gColorS);
	put("gColorV",	255,0,255,238,null,slider_gColorV);
	put("indexOrBits",	0,0,255,239,null,slider_indexOrBits);
	put("NUM_LEDS",	NUM_LEDS_slider_startup,NUM_LEDS_slider_m,NUM_LEDS_slider_M,240,null,slider_NUM_LEDS);


	put("speedH",	4,0,255,245,label_speedH,slider_speedH);
	put("lengthH",	9,1,255,246,label_lengthH,slider_lengthH);


	put("action",	0,0,  actionsM,248,null,slider_action);

	put("save",		0,0,255,249,null,null);
	put("load",		0,0,255,250,null,null);

	put("clear",	0,0,255,251,null,null);
	put("pause",	0,0,255,252,null,null);
	put("reset",	0,0,255,253,null,null);
	put("msgprint",	0,0,255,254,null,null);
	put("msgprintPX", 0,0,255,255,null,null);



	label_SerialSpeed.setText(Integer.toString(serialSpeed));

	
	modeChanged(); //draw initial val

	setupValues();

	for (int i=0; i<10; i++) {
		slots_s[i]= new GButton(this, 20+45*i, 550, 30, 30);
		slots_s[i].setLocalColorScheme(GCScheme.PURPLE_SCHEME);
		slots_s[i].addEventHandler(this, "slots_click");
		slots_s[i].tag="s";
		slots_s[i].tagNo=i;

		slots[i]= new GButton(this, 20+45*i, 590, 30, 30);
		slots[i].setText(Integer.toString(i)); //TODO2 get from EEPROM
		slots[i].setLocalColorScheme(GCScheme.GREEN_SCHEME);
		slots[i].addEventHandler(this, "slots_click");
		slots[i].tagNo=i;
	}

	search_animh();

	fontFPS= createFont("Monospaced", 26);
	//fontFPS= createFont("SourceCodePro-Regular.ttf", 26);
	smooth(16); 
	plotFPS= new Plot12(400,2,145, 320, 100); //new Plot12(400,2,290, 620, 210); //  //plot= new Plot12(100,250,300, 300, 200);
	plotFPS.bDrawShiftLines=false;
	plotFPS.colorConnections=color(0,255,255);
	//plotFPS.bDrawBg=true;

	if(bRecieveLEDdata)
	{
		plot_pow= new Plot12(200,2,145, 320, 145);
		plot_pow.bDrawFromFarPoint=random(100)<20;
		plot_pow.bDrawFromFarPoint_toEndPioint=random(100)<2;
		plot_pow.colorFromFar_toEndPioint=color(gColorBgB,gColorBgB,255);
		//plot_pow.posXt=plot_pow.posX;
		//plot_pow.posYt=plot_pow.posY+32;

		if(bDraw_plot_RGB_pow)
		{
			plotR= new Plot12(400,2,145, 320, 100);
			plotR.bDrawShiftLines=false;
			plotR.colorConnections=color(255,0,0);
			plotR.set_value_mM_limits_byte();

			plotG= new Plot12(400,2,145, 320, 100);
			plotG.bDrawShiftLines=false;
			plotG.colorConnections=color(0,255,0);
			plotG.set_value_mM_limits_byte();

			plotB= new Plot12(400,2,145, 320, 100);
			plotB.bDrawShiftLines=false;
			plotB.colorConnections=color(0,0,255);
			plotB.set_value_mM_limits_byte();

			if(random(100)<10)
			{
				plotR.bAdjLimitsStrange=true;
				plotG.bAdjLimitsStrange=true;
				plotB.bAdjLimitsStrange=true;
			}
		}
	}
//btn3_L.fireAllEvents(true); //not work in G4P bug //!@ttt
}

void plotPX_create()
{
	plotPX=new PlotPX(60, height/2, width-widthNormal,height/2, widthNormal,height/2);
	plotPX.DrawLEDs_load();
}

void changeSilerTextColor(int cc)
{
	for (Map.Entry<String, settingsVal> entry : settingsVals.entrySet()) {
	    //String key = entry.getKey();
	    settingsVal value = entry.getValue();
	    if(value.valueSlider!=null)
	    value.valueSlider.setLocalColor(2, color(cc)); //palette index 4=bg 2=text
	}
}
//===========================================================================================================================
// //fireAllEvents
// public void handleButtonEvents(GButton button, GEvent event) {
//   System.out.println("Recieved " + event + " event from " + button.getText());
// }

void updateSlider(String nm, int value)
{
	GSlider slider = settingsVals.get(nm).valueSlider;
	if(slider.getValueI()!=value)
	slider.setValue(value);
}



int serState=0;
int rec_header[]={111,166,77};

static final int PRINT_leds		=133;
static final int PRINT_totall	=122;
static final int PRINT_settings	=99;

static final int msg_buffer_size=6000;

int[] msg_buffer=new int[msg_buffer_size];

int rec_fps;
int rec_msg_size;
int rec_msg_type;



void DisableSerial()
{
	if(myPort!=null)
	{
		myPort.clear();	myPort.stop(); myPort=null;
	}
	bConnected=0;
	button_disconnect.setText("Connect");
}
void EnableSerial()
{
	if(!bSendSimDataToMCU)
    bSim_set(false);
	bConnected=1;
	button_disconnect.setText("Disonnect");
}

boolean bErrStop=false;
void serialEvent(Serial cPort)
{
	if(bErrStop) return;
	try{
	/*		//debug print serial
	//String comPortString = cPort.readStringUntil('\n');
	if(myPort.available() > 8)
	{
		String comPortString = cPort.readString();
		if(comPortString != null)
		{
			comPortString=trim(comPortString);

			if(bDebugPrint) 
			{
			if(comPortString.length()>1)
			print(comPortString);
			return;
			}
		}
	}
	return;
	*/

//# if(comPortString.contains(","))  {  print("CRGB( "); print(comPortString); println(" ),"); return;}

	while (myPort.available() > 0)
	{
		int inByte = myPort.read(); //byte in Java is signed. It will not work with byte without refactoring

												//if(rec_msg_type!=PRINT_totall)	println("      " + inByte);

		if(serState<3) //bWait_mgs_header
		{
			if(inByte!=rec_header[serState])
			{
				serState=0;
				continue;
			}
		}
		else
		
		if(serState==3)
		{
				rec_fps=0;
				rec_msg_size=0;

			rec_msg_type=inByte;						//if(rec_msg_type!=PRINT_totall) println(rec_msg_type);
			if(rec_msg_type==PRINT_settings)
			{
				serState+=2;
			}
			else
			if(rec_msg_type!=PRINT_totall && rec_msg_type!=PRINT_leds )
			{
				serState=0;
				continue;
			}
		}

		else
		if(serState==4)
		{
			rec_fps=inByte;
		}
		else
		if(serState==5)
		{
			rec_fps+=inByte*256;				//if(rec_msg_type!=PRINT_totall) {print("fps: ");				println(rec_fps);	}	
		}

		else
		if(serState==6)
		{
			rec_msg_size=inByte;
			if(rec_msg_type==PRINT_settings ) serState++;  //size of PRINT_settings is 1, so +1
		}
		else
		if(serState==7)
		{
			rec_msg_size+=inByte*256;			
			//if(rec_msg_type!=PRINT_totall ) 
			if(rec_msg_size>=msg_buffer_size-8 ) 
			 {print("rec_msg_size: ");				println(rec_msg_size); rec_msg_size=msg_buffer_size-8; processSerialData();	}	

			if(rec_msg_type==PRINT_totall)
			{
				processSerialData(); continue;
			}
		}

		else
		if(serState-8 < rec_msg_size)
		{
												//if(rec_msg_type!=PRINT_settings) println("   "+inByte);
			msg_buffer[serState-8]=inByte;

			if(serState-8 == rec_msg_size-1)
			{
				processSerialData(); continue;
			}
		}

		serState++;
	}

return;

/*
 	if(comPortString.contains(","))  {  print("CRGB( "); print(comPortString); println(" ),"); return;}
  */
 }catch(Exception e){ println(e); println(rec_msg_size);  println(serState); bErrStop=true;  }
}


void processSerialData()
{
	serState=0;
	//rec_msg_type=0;
	switch(rec_msg_type)
	{
		case PRINT_leds:

			if(bRecieveLEDdata)
			{	 	//println("bRecieveLEDdata");
				if(plotPX==null)  plotPX_create();
				plotPX.push(msg_buffer, rec_msg_size);
				bplotPX=true;
				bDraw_plotPX_until_t=millis()+4000;
			}
			if(bDraw_plot_RGB_pow)
			{	 	//println("bDraw_plot_RGB_pow");
				plotR.push(plotPX.rE); plotR.tik();
				plotG.push(plotPX.gE); plotG.tik();
				plotB.push(plotPX.bE); plotB.tik();
			}
			if(bPlot_FPS_enabled)
			{ 		//println("bPlot_FPS_enabled");
				bDrawFPSnow=rec_fps;
				plotFPS.push(bDrawFPSnow); //plotFPS.push(((float)bDrawFPSnow)/10.);
				bDrawFPS_until_t=millis()+1000;
			}
			if(bPlotPow_enabled)
			{		//println("bPlotPow_enabled");
				bDrawPownow=plotPX.rE+plotPX.gE+plotPX.bE;
				plot_pow.push(bDrawPownow);
				bDrawPow_until_t=millis()+1000;
			}
		break;

		case PRINT_totall:
			if(bPlot_FPS_enabled)
			{	
				bDrawFPSnow=rec_fps;
				plotFPS.push(bDrawFPSnow); //plotFPS.push(((float)bDrawFPSnow)/10.);
				bDrawFPS_until_t=millis()+1000;
			}
			if(bPlotPow_enabled)
			{	
				bDrawPownow=rec_msg_size;
				plot_pow.push(bDrawPownow);
				bDrawPow_until_t=millis()+1000;
			}
		break;


		case PRINT_settings:
			bSkipEvent=true;
/*
struct SaveObj //# sizeof
{
	byte effN; // = eff SLOT at start
	byte effSpeed;
	byte effSpeedH; //! //EVERY_N_MILLISECONDS( 20 ) gHue+=effSpeed;
	byte effLength;
	byte effLengthH;
	byte effRGB;//1 => disable chennel R, 2 => disable G ,  7 => fast cycle diferent , //!comment other
	byte effFade;
	// byte gH;
	// byte gS;
	// byte gV;
	CRGB gColor;
	CRGB gColorBg;//! gHueBG == 0 ? White	== 255 ? black
	byte gFade; //apply before eff
	byte indexOrBits;
	byte gDelay;
	byte gBrightness; //#
	byte NUM_LEDS; //work ifdef use_ESP to save progmem
*/

			updateSlider("effN",(msg_buffer[0])); //! not upd if slider move over 0..9 slots or set some marker
			updateSlider("speed",(msg_buffer[1]));
			updateSlider("speedH",(msg_buffer[2]));
			updateSlider("length",(msg_buffer[3]));
			updateSlider("lengthH",(msg_buffer[4]));
			updateSlider("RGB",(msg_buffer[5]));
			updateSlider("effFade",(msg_buffer[6]));

			updateSlider("gColorH",(msg_buffer[7]));
			updateSlider("gColorS",(msg_buffer[8]));
			updateSlider("gColorV",(msg_buffer[9]));
			//gColorBg
			//
			//
			//gFade
			updateSlider("indexOrBits",(msg_buffer[14]));
			updateSlider("gDelay",(msg_buffer[15]));
			updateSlider("gBrightness",(msg_buffer[16]));
																// for (int i=0; i<22; i++) {
																// 	print(i+"= ");
																// 	println(msg_buffer[i]+", ");
																// }
			if(b_NUM_LEDS_adj)
			{	
				int NUM_LEDS_arr_size;
				if(msg_buffer[17]!=0 && msg_buffer[18]<=0) 
					NUM_LEDS_arr_size=msg_buffer[17];
				else
					NUM_LEDS_arr_size=msg_buffer[17]*256+msg_buffer[18];
	
				if(NUM_LEDS_arr_size%3==0)	updateSlider("NUM_LEDS",NUM_LEDS_arr_size/3);
																		//println(NUM_LEDS_arr_size/3);
			}

			bSkipEvent_off_t=millis()+120; //! test lower or different approach
		break;

	}

	for (int i=0; i<100; i++) 	msg_buffer[i]=-1;
}
//=========================================================================================================================== sim
void bSim_set(boolean b)
{
	bSim=b;
	if(bSim)
	{
		if(!bSendSimDataToMCU)
		{
			button_sim.setText("stop");
			DisableSerial();
		}
	}
	else button_sim.setText("sim");
}
//===========================================================================================================================
int bDrawFPSnow=-1;
int bDrawPownow=-1;
PFont fontFPS;
int bDrawFPS_until_t=0;
int bDrawPow_until_t=0;
int bDraw_plotPX_until_t=0;
color cc;
float mA_avg=-1;


public void draw()
{
	if(bSkipEvent && millis()>bSkipEvent_off_t) bSkipEvent=false;

	background(gColorBg);

	//---------------------------------------- RGB option state
	noStroke();
	fill(rCh?255:0, gCh?255:0, bCh?255:0); 
	final int RGB_indicator_x0=515;
	if(rCh)	ellipse(0+RGB_indicator_x0, 525, 8, 8);
	if(gCh)	ellipse(30+RGB_indicator_x0, 525, 8, 8);
	if(bCh)	ellipse(60+RGB_indicator_x0, 525, 8, 8);
	//----------------------------------------
	fill(255, 255, 88); stroke(128, 0, 128);
	polygon(3,  effParsedList_btns_posX-12, 8+effParsedList_btn_h*2 +10, 11);  //mark on current eff N (scroll list to this pos)

	stroke(255, gColorBgB, 255); //stroke(0);//stroke(gColorBgB-40);
	line(effParsedList_btns_posX+40,0,effParsedList_btns_posX+40, height); //GUI scroll area markers
	line(width-scroll_effParsedList_scrollWidth,0,width-scroll_effParsedList_scrollWidth, height);

	textFont(fontFPS);

	if(bPlot_FPS_enabled && bDrawFPSnow>-1 && millis()<bDrawFPS_until_t)
	{
		//textSize(32);
		text(bDrawFPSnow, 440, 155);
		if((millis()/50)%2==0)
		plotFPS.tik(); //## tikIfNewData
		plotFPS.draw();
	}

	
	if(width>1200 )
	{
		if(millis()<bDraw_plotPX_until_t)
		{
			if(plotPX!=null)
			{
				plotPX.matrix_rowsE=matrix_rowsE; //!!

				if(bDrawLEDs_PXHistory_enabled)
				{	
					plotPX.draww=width-widthNormal; //! on window resize
					plotPX.drawh=height/2;
					plotPX.posY=height/2;
					plotPX.draw();
				}
				if(bDraw_plot_RGB_pow)
				{
					plotR.draw();
					plotG.draw();
					plotB.draw();
				}

				if(bDrawLEDs_enabled)
				{
					noStroke();
					fill(0);
					rect(0,640-18,680+220,height);
					if(height>800)
					{
						int sim_NUM_LEDS=settingsVals.get("NUM_LEDS").value;
						plotPX.draw_LED_Line(sim_NUM_LEDS);
					}
				}
			}
		}
		else
		{
			fill(0, 255, 0);
			text(">start sending pixel data<",  width-widthNormal+50, height/2+100);
		}
	}

	if(bRecieveLEDdata && bPlotPow_enabled && bDrawPownow>-1 && millis()<bDrawPow_until_t)
	{
		//textSize(32); g.textSize
		textFont(fontFPS);
		fill(255, 0, 0);
		text("mA:", 320, 155); //! sw mW
		fill(255, 88, 88);
		//3...750
		float mul=1.*256/255;// /255; //32. //MCU range divider
		float LED_pow=20./255; //mA

		//float NUM_LEDS_used=(60+30+144+50)/144.; //144 in arduino 
		float NUM_LEDS_used=b_Cube?NUM_LEDS_slider_M: (60+30+144)/144.; //144 in arduino 

		float NUM_LEDS_limit = (float) settingsVals.get("NUM_LEDS").value;

		//---------- test set of 30+50+60+144 in parallel data pin
		if(NUM_LEDS_limit<=30) NUM_LEDS_used=NUM_LEDS_limit*4;
		else
		if(NUM_LEDS_limit<=50) NUM_LEDS_used=30+NUM_LEDS_limit*3;
		else
		//if(NUM_LEDS_limit<=60) NUM_LEDS_used=30+50+NUM_LEDS_limit*2;
		if(NUM_LEDS_limit<=60) NUM_LEDS_used=30+NUM_LEDS_limit*2;
		else
		//if(NUM_LEDS_limit>60) NUM_LEDS_used=30+50+60+NUM_LEDS_limit;
		if(NUM_LEDS_limit>60) NUM_LEDS_used=30+60+NUM_LEDS_limit;
		//----------

		float mA=bDrawPownow*mul*LED_pow* (settingsVals.get("gBrightness").value/255.) *NUM_LEDS_used/NUM_LEDS_limit +1*NUM_LEDS_used; //this is in case there are no Unused but connected
		
		if(mA_avg<0 || abs(mA_avg-mA)/mA >0.2 )	mA_avg=mA;
		else							mA_avg=mA_avg*0.9+mA*0.1;
	
		text((int)mA_avg, 365, 155); //! calibrate //!! set limist to average //!! gDark_mW   add after scale to current br
		//if((millis()/50)%2==0)
		plot_pow.tik(); //## tikIfNewData

		if(width>1200)
		{
			plot_pow.w=width-widthNormal;
			plot_pow.h=height/2;
		}

		if(width>1200 && !bWideSize)
		{
			bWideSize=true;
			plot_pow.posX=widthNormal;
			plot_pow.posY=0;
			plot_pow.w=width-widthNormal;
			plot_pow.h=height/2;
			plot_pow.bDrawBg=true;
			plot_pow.bDrawFromFarPoint=true;
			plot_pow.bDrawFromFarPoint_toEndPioint=true;
		}
		else
		if(width<1200 && bWideSize)
		{
			bWideSize=false;
			plot_pow.posX=0;
			plot_pow.posY=144;
			plot_pow.w=320;
			plot_pow.h=144;
			plot_pow.bDrawBg=false;
			plot_pow.colorRect=color(255);
			plot_pow.bDrawFromFarPoint=false;
			plot_pow.bDrawFromFarPoint_toEndPioint=false;
			plot_pow.colorShiftLines=color(0);
		}
		if(bWideSize)
		{
			if(random(1000)<2) plot_pow.bDrawFromFarPoint=!plot_pow.bDrawFromFarPoint;
			if(random(1000)<2) plot_pow.bDrawFromFarPoint_toEndPioint=!plot_pow.bDrawFromFarPoint_toEndPioint;
		}
		plot_pow.draw();
	}



	if(mouseX>(widthNormal-scroll_effParsedList_scrollWidth-200) && (mouseY<20 || mouseY>height-20))
	{
		 if(mouseY<20) 
		 {
		 	if(yStart_last>0) yStart_last-=4;
		 }
		 else
		 if(mouseY>height-20) 
		 {
		 	if(yStart_last<height-50) yStart_last+=8;;
		 }

		scroll_effParsedList_btns( (int)yStart_last);
	}


	if(bSim) sim();
	else
	{
//---------------------------------------- serial
		try
		{
			if(Serial.list().length<1)
			{
				text("plug USB or update driver",10,10);
				myPort=null;
				button_disconnect.setText("Connect");
				delay(50); return; 
			}
		}catch(Exception e){ button_disconnect.setText("err"); }

		if(myPort==null && bConnected==1)
		{
			try
			{
				if(Serial.list()[useSerialPortN]!=null) //!! tst
					myPort = new Serial(this, Serial.list()[useSerialPortN], serialSpeed); //, 'S' ,7, 1.0);  if need. Now working by default
				else if(Serial.list()[0]!=null) //!! tst
					myPort = new Serial(this, Serial.list()[0], serialSpeed);//, 'S' ,7, 1.0);  
			}catch(Exception e){ button_disconnect.setText("err"); text("USB Serial err",10,10); }

			if(myPort!=null) 
			{
				if(bSetBrightnessAtConnect>-1)	settingsVals.get("gBrightness").setValue(bSetBrightnessAtConnect);
				bConnected=2;
				button_disconnect.setText("Disonnect");
			}
		}
	}


	if(bDebugXY)
	{
		fill(255, 0, 0);	
		text(mouseX, mouseX, mouseY);		
		text(mouseY, mouseX, mouseY+30);
	}
}



// Use this method to add additional statements to customise the GUI controls
public void customGUI(){

}

void mouseMoved() //! only if not big dY, if big - anim or nothing do
{
	if(mouseX>(width-scroll_effParsedList_scrollWidth-200) && (mouseY<20 || mouseY>height-20))
	{
		//  if(mouseY<20) 
		//  {
		//  	if(yStart_last>0) yStart_last--;
		//  }
		//  else
		//  if(mouseY>height-20) 
		//  {
		//  	if(yStart_last<height-50) yStart_last++;
		//  }

		// scroll_effParsedList_btns( (int)yStart_last);
	}
	else
	if(mouseX>width-scroll_effParsedList_scrollWidth)
	{
		scroll_effParsedList_btns( mouseY);
	}

}

// void mouseDragged() 
// {
// 	//if(mouseX>width-scroll_effParsedList_scrollWidth)
// 	{
// 		scroll_effParsedList_btns( height-mouseY);
// 	}
// }


 boolean bWideSize=false;
// int wtmp;
 boolean bMadeScreenshot_thisTime=true;
void mouseClicked() {
																							bErrStop=false;

	if(plotPX!=null && (mouseY<200 ||  (mouseX<700&& mouseY>630))) plotPX.bDrawLEDs_line=!plotPX.bDrawLEDs_line;

	bWideSize=width>1200;

	if(bWideSize && mouseX>width/2 && mouseY>height/2) 
	{
		//if(millis()<bDraw_plotPX_until_t) //too big delay, so if we click to made screenshot we got 2
		if(millis()<bDraw_plotPX_until_t && bMadeScreenshot_thisTime) //!! show save btn on mouse over			//screen save,
		{
			plotPX.save(EffNms[settingsVals.get("effN").valueSlider.getValueI()]);
			
		} bMadeScreenshot_thisTime=!bMadeScreenshot_thisTime; //!!

		if(!bSim)  //!! toggle betwen pixel source or make 2 separate plots
		{
			SendMsg(settingsVals.get("msgprintPX").message_code, 0); 				//in MCU: bPrintPixels=!bPrintPixels
		}
	}

	if(mouseX>900 && mouseY<300)
	{
		if(bDrawLEDs_PXHistory_enabled)
		{
			bDrawLEDs_PXHistory_enabled=false;
			bDrawLEDs_enabled=true;
		}
		else
		{
			bDrawLEDs_PXHistory_enabled=true;
			bDrawLEDs_enabled=false;
		}
	}
	// if(mouseX<10 &&  mouseY<300)
	// {
	// 	bWideSize=!bWideSize;

	// 	if(bWideSize)
	// 	{
	// 		wtmp=width;
	// 	surface.setSize(width*2, height);
	// 	}
	// 	else
	// 		surface.setSize(wtmp, height);
	// }

	// print(red(cc));print(", ");
	// print(green(cc));print(", ");
	// println(blue(cc));
}


boolean bdebugK=false;
boolean bdebugS=false;
boolean bdebugC=false;

void keyReleased() {
 // print(key); print("\t");
 // println(keyCode);
	if(plotPX!=null && plotPX.DrawLEDs_currentPoint<NUM_LEDS_slider_startup)
	{
			if( (keyCode == SHIFT || keyCode == CONTROL) )
			{
				plotPX.bDrawLEDs_on=false;
			}
	}
}


void keyPressed() {
	//https://jogamp.org/deployment/jogamp-next/javadoc/jogl/javadoc/com/jogamp/newt/event/KeyEvent.html
	//https://docs.oracle.com/javase/6/docs/api/java/awt/event/KeyEvent.html
	//print(key); print("\t");
	//print(keyCode); println("pressed \t");
 
	if (key == CODED) {
		if (keyCode == CONTROL)		bDebugXY = !bDebugXY;
	}

  if(plotPX!=null && plotPX.bDrawLEDs_customGeometry_paint && plotPX.DrawLEDs_currentPoint<NUM_LEDS_slider_startup)
  {
	if(keyCode == DELETE)
	{
		plotPX.DrawLEDs_currentPoint=0;
	}
				
	if (key == CODED) {
			if(millis()>plotPX.DrawLEDs_next_t) //time lapsed && already drawn 
			{
				if (keyCode == SHIFT )
				{
						plotPX.bDrawLEDs_freq=55;

						plotPX.bDrawLEDs_on=true;
				}
				else if (keyCode == CONTROL) 
				{
						plotPX.bDrawLEDs_freq=111;

						plotPX.bDrawLEDs_on=true;
				}
		
			}
		}
	}
	//TODO
	//f5 save DrawLEDs
	//f12 save scr
	//f11 save led hist img
	//f4 copy current eff
	//f3 copy current eff HTML
	//ins add  current eff  to kit

}
