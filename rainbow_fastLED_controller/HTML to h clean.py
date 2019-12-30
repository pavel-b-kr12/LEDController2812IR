import re
import sys, threading,time, os
from os.path import dirname, join, isdir, abspath, basename

exepath = os.path.dirname(sys.argv[0])+"\\"
file = open("HTML_settings.htm","r")  
filestr=file.read()   
#rrr = re.compile(r'(<!--(.|\\)*?-->|^\s*\/\/.* |\/\*\*.*?\*\/)', re.MULTILINE)       
#filestr = re.sub(rrr, "", filestr)

filestr = re.sub(r'\/\*\*.*?\*\/', "", filestr, flags=re.S) # /**  */
filestr = re.sub(r'<!---.*?--->', "", filestr, flags=re.S) # <!-- -->
filestr = re.sub(r'[\s;]+\/\/.*', "", filestr) #[\s;]+  so not eat http://
filestr = re.sub(r'^\/\/.*', "", filestr) # start of line//

#print(filestr)        
file_h = open("HTML_settings.h","w") 
file_h.write(filestr)
file_h.close()
#for line in file:    
    #if re.search('->',line):
    #   print ' '.join(re.findall('[0-9]+',line))
	
	
	
	
	
	
	
# https://regex101.com/
# asd asdasd
# <!-- --> 3r/*3r2*/3
# <script>
 # //g4g35g5
# svg.setAttributeNS("http://www.w3.org/2000
#// g4g35g5 
# </script>
