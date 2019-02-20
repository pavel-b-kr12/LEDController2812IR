boolean bSkipCommentedCases= true;//false;
int effParsedList_btns_posX=692;
int effParsedList_btns_i=0;
int effParsedList_btn_h=21;
int scroll_effParsedList_scrollWidth=50; //moving mouse righ pixels cause scroll

void search_animh()
{
	String path = sketchFile("").getParent(); //sketchPath();
	ArrayList<File> allFiles = listFilesRecursive(path);

	for (File f : allFiles)
	{
		if(f.getName().equals("switch_slot.h")) 
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
						// 	for (int i = 0; i < m.length; i++)	println( m[i] );
						// 	println("-----------------");
						// }
					int effN=Integer.parseInt(m[1]);
					if(effN>250) continue;

					GButton btn= new GButton(this, effParsedList_btns_posX, 10+effParsedList_btn_h*effParsedList_btns_i, width-effParsedList_btns_posX-2, 18);
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

					String[] effQualityMark = match(line, "//\\!");


					if(effQualityMark!=null)
					{
						btn.setLocalColorScheme(GCScheme.RED_SCHEME);
					}

					effQualityMark = match(line, "//\\:\\)");
					if(effQualityMark!=null)
					{
						btn.setLocalColorScheme(GCScheme.GOLD_SCHEME);
					}

					effQualityMark = match(line, "//\\:/");
					if(effQualityMark!=null)
					{
						btn.setLocalColor(4, color(gColorBg)); //palette index 4=bg 2=text
					}
				}

			}
		} catch(Exception e){}
		}
	}
}


String[] EffNms = new String[255];

GButton[] effParsedList_btns = new GButton[255];
float yStart_last=10;
float smothScroll=0.15;//0.03
void scroll_effParsedList_btns(int yStart)
{
	if(abs(yStart-yStart_last)>20)
	{
	 yStart_last= yStart_last*(1-smothScroll)+yStart*smothScroll;
	}
	else
	yStart_last=yStart;

	for (int i=0; i<effParsedList_btns_i-1; i++) {
		GButton btn=effParsedList_btns[i];
		btn.moveTo(btn.getX(),  map((int)yStart_last,0,height,0,-effParsedList_btns_i*effParsedList_btn_h) +10+effParsedList_btn_h*i);
	}
}
void scroll_effParsedList_btns_toTopFor(int btnsE) //btnsE is  btn N in effParsedList_btns array
{
	for (int i=0; i<effParsedList_btns_i-1; i++) {
		GButton btn=effParsedList_btns[i];
		btn.moveTo(btn.getX(),  8+effParsedList_btn_h*(i-btnsE+2));
	}
}




public void effParsedList_btns_click(GButton source, GEvent event) {
	//if ( event != GEvent.CLICKED) return;
	int N=source.tagNo; //Integer.parseInt(source.getText().split(":")[0]);
	println(N);
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