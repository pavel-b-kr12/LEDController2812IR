
void colorSchema_choose()
{
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
}