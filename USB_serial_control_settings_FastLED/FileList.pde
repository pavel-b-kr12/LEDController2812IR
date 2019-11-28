//#

boolean bSkipCommentedCases= true;//false;
int effParsedList_btns_posX=692;
int btnShiftX_if_same_nm_w=12;
int effParsedList_btns_i=0;
int effParsedList_btn_h=21;
int scroll_effParsedList_scrollWidth=50; //moving mouse righ pixels cause scroll

void parse_switch_slot(File f)
{
  try
    {
      BufferedReader br = new BufferedReader(new FileReader(f.getAbsolutePath())); 

      String line; 
      effParsedList_btns_i=0;
      while ((line = br.readLine()) != null) 
      {
        String[] commented = match(line, "^\\s*//[\\s/]*case"); //^[\s\t]*\\\\
        if(commented!=null) 
        {
          //if(bDebugPrint) System.err.println(line);
          if(bSkipCommentedCases) continue;

        }

        String[] m = match(line, "case\\s*?(\\d+)\\s*?\\:\\s*?anim_f=(.*?)\\s*?;"); //!opt cashe compiled regex
        if(m!=null)
        {
            // if(bDebugPrint)
            // {
            //   for (int i = 0; i < m.length; i++)  println( m[i] );
            //   println("-----------------");
            // }
          int effN=Integer.parseInt(m[1]);
          if(effN>250) continue;

          int btnShiftX_if_same_nm=0;
          if( m[2].equals(EffNms[effN-1]) ) btnShiftX_if_same_nm =btnShiftX_if_same_nm_w;
          

          GButton btn=new GButton(this, effParsedList_btns_posX +btnShiftX_if_same_nm, 10+effParsedList_btn_h*effParsedList_btns_i, width-effParsedList_btns_posX-2 -btnShiftX_if_same_nm, 18);
          btn.setTextAlign(GAlign.LEFT, GAlign.MIDDLE);
          
          
          btn.tagNo=effN;
          btn.setText(m[1]+":"+m[2]);
          if(commented==null)
          {
            btn.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
            btn.addEventHandler(this, "effParsedList_btns_click");
          }
          else
          {
            btn.setLocalColor(4, color(gColorBg));
            btn.setLocalColor(2, color(gColorBg-40));
          }
          effParsedList_btns[effParsedList_btns_i]=btn;
          EffNms[effN]=m[2];

          effParsedList_btns_i++;

          String[] effQualityMark;
          int effQuality_i=1;

          effQualityMark = match(line, "//\\:/");
          if(effQualityMark!=null)
          {
            effQuality_i++;
            btn.setLocalColor(4, color(gColorBg)); //palette index 4=bg 2=text
          }

          effQualityMark = match(line, "//\\!");
          if(effQualityMark!=null)
          {
            effQuality_i+=2;
            btn.setLocalColorScheme(GCScheme.RED_SCHEME);
          }

          effQualityMark = match(line, "//\\:\\)");
          if(effQualityMark!=null)
          {
            effQuality_i--;
            btn.setLocalColorScheme(GCScheme.GOLD_SCHEME);
          }

          

          EffNmsQuality[effN]=effQuality_i; //0...4
        }

      }
    } catch(Exception e){ println(e); }
}


void search_animh()
{

  File fileInReliese=new File("switch_slot.h"); //put file in Release's root
  if( fileInReliese.exists())
  {
    parse_switch_slot(fileInReliese);
  }
  else
  {
    try
    {
        String path = sketchFile("").getParent(); //sketchPath();
				ArrayList<File> allFiles = listFilesRecursive(path);


			  for (File f : allFiles)
			  {
			    if(f.getName().equals("switch_slot.h")) //!! DOTO we can add support of multiple lists
			    {	
			    	 if(f.getParent().contains("USB_serial_control_settings_FastLED")) continue; //skip release build folders when run full code version
			       parse_switch_slot(f);

			    }
			  }
  
    }
    
 catch(Exception e){}
  }

}


String[] EffNms = new String[255];
Integer[] EffNmsQuality = new Integer[255];

GButton[] effParsedList_btns = new GButton[255];
float yStart_last=10;
float smothScroll=0.07;//0.15 0.03

void setBtnPosY_and_visibility(GButton btn, float posY)
{
  if(posY<600)
    {
     btn.moveTo(btn.getX(), posY );
     btn.setVisible(true);
    }
    else
    {
      btn.setVisible(false);
    }
}
void scroll_effParsedList_btns(int yStart) //yStart=mouseY
{
	float y_diff_abs=abs(yStart-yStart_last);
	if(y_diff_abs>20) //smooth
	{
		yStart_last= yStart_last*(1-smothScroll)+yStart*smothScroll;
	}
	else if(y_diff_abs<4)
	{
		return;
	}
	else
	{
		yStart_last=yStart;
	}
	

	for (int i=0; i<effParsedList_btns_i-1; i++) {
		GButton btn=effParsedList_btns[i];
    float posY=map((int)yStart_last,0,height,0,-effParsedList_btns_i*effParsedList_btn_h) +10+effParsedList_btn_h*i;
    setBtnPosY_and_visibility(btn, posY);
	}
}
void scroll_effParsedList_btns_toTopFor(int btnsE) //btnsE is  btn N in effParsedList_btns array
{
	for (int i=0; i<effParsedList_btns_i-1; i++) {
		GButton btn=effParsedList_btns[i];
    setBtnPosY_and_visibility(btn, 8+effParsedList_btn_h*(i-btnsE+2));
	}
}




public void effParsedList_btns_click(GButton source, GEvent event) {
	//if ( event != GEvent.CLICKED) return;
	int N=source.tagNo; //Integer.parseInt(source.getText().split(":")[0]);
					if(bDebugPrint)println(N);
	settingsVals.get("effN").setValue(N);
}


//================================================================================== file

// This function returns all the files in a directory as an array of Strings  
String[] listFileNames(String dir) {
	File file = new File(dir);
	if (file.isDirectory()) {
		String names[] = file.list();
		return names;
	} else {
    // If it's not a directory
		return null;
	}
}

// This function returns all the files in a directory as an array of File objects
// This is useful if you want more info about the file
File[] listFiles(String dir) {
	File file = new File(dir);
	if (file.isDirectory()) {
		File[] files = file.listFiles();
		return files;
	} else {
    // If it's not a directory
		return null;
	}
}

// Function to get a list of all files in a directory and all subdirectories
ArrayList<File> listFilesRecursive(String dir) {
	ArrayList<File> fileList = new ArrayList<File>(); 
	recurseDir(fileList, dir);
	return fileList;
}

// Recursive function to traverse subdirectories
void recurseDir(ArrayList<File> a, String dir) {
	File file = new File(dir);
	if (file.isDirectory()) {
    // If you want to include directories in the list
		a.add(file);  
		File[] subfiles = file.listFiles();
		for (int i = 0; i < subfiles.length; i++) {
      // Call this function on all files in this directory
			recurseDir(a, subfiles[i].getAbsolutePath());
		}
	} else {
		a.add(file);
	}
}
