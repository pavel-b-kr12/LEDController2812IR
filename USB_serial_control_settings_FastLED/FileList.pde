int effParsedList_btns_posX=692;
int effParsedList_btns_i=0;
int effParsedList_btn_h=21;
int scroll_effParsedList_scrollWidth=50; //moving mouse righ pixels cause scroll


void search_animh()
{

	String path = sketchFile("").getParent(); //sketchPath();
	ArrayList<File> allFiles = listFilesRecursive(path);

	for (File f : allFiles) {

		if(f.getName().equals("switch_slot.h")) 
		{

			// println("Name: " + f.getName());
			// println("Full path: " + f.getAbsolutePath());
			// println("Is directory: " + f.isDirectory());
			// println("Size: " + f.length());
			// String lastModified = new Date(f.lastModified()).toString();
			// println("Last Modified: " + lastModified);
			// println("-----------------------");

			// String[] lines = loadStrings("http://processing.org/about/index.html");
			// println("there are " + lines.length + " lines");
			// for (int i = 0 ; i < lines.length; i++) {
			// 	println(lines[i]);
			// }

		try
		{
			BufferedReader br = new BufferedReader(new FileReader(f.getAbsolutePath())); 

			String line; 
			effParsedList_btns_i=0;
			while ((line = br.readLine()) != null) 
			{
				String[] commented = match(line, "^[\\s\\t]*//s*?case"); //^[\s\t]*\\\\
				if(commented!=null) 
				{
					//System.err.println(line);
				}
				else
				{
					String[] m = match(line, "case\\s*?(\\d+)\\s*?\\:\\s*?anim_f=(.*?)\\s*?;"); //!opt cashe compiled regex
					if(m!=null)
					{
						for (int i = 0; i < m.length; i++) {
							println( m[i] );
						}
						println("-----------------");
							GButton btn= new GButton(this, effParsedList_btns_posX, 10+effParsedList_btn_h*effParsedList_btns_i, width-effParsedList_btns_posX-2, 18);
							btn.setTextAlign(GAlign.LEFT, GAlign.MIDDLE);
							btn.tagNo=Integer.parseInt(m[1]);
							btn.setText(m[1]+":"+m[2]);
							btn.setLocalColorScheme(GCScheme.PURPLE_SCHEME);
							btn.addEventHandler(this, "effParsedList_btns_click");
							effParsedList_btns[effParsedList_btns_i]=btn;
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
							btn.setLocalColor(4, color(BGcolor)); //palette index 4=bg 2=text
						}



						//.setLocalColorScheme(GCScheme.CYAN_SCHEME);
					}
				}
				//
				//case 11: anim_f=fillStriped;	
			}
		} catch(Exception e){}



		}
	}
}

GButton[] effParsedList_btns = new GButton[255];

void scroll_effParsedList_btns(int yStart)
{
	for (int i=0; i<effParsedList_btns_i-1; i++) {
		GButton btn=effParsedList_btns[i];
		btn.moveTo(btn.getX(),  map(yStart,0,height,0,-effParsedList_btns_i*effParsedList_btn_h) +10+effParsedList_btn_h*i);
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