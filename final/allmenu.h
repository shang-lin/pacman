/*************  REVISION HISTORY  *********************



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/03 00:04:53;  
author: graham;    
Added math functions to menusystem files.



date: 2002/06/02 23:41:38;  
author: graham;    
Added "using namespace std" to everything



date: 2002/05/08 07:39:54;  
author: graham;    

Commented out duplicate definitions of ScrollingMenuEntry and RadioEntry that were wreaking havoc on my code. Luckily, the compiler gave impossibly cryptic error messages, so i only spent hours trying to find the problem. Stupid computers. I'm not sure i'm even using anything in this file anymore



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/14 20:38:00;  
author: graham;    

The ButtonWidget code here is completely tested, except that the graphics stuff isn't done yet. The Event classes are test event classes that construct inputevents out of alphanumeric keypresses for the purpose of testing the widgets.



date: 2002/02/21 11:05:56;  
author: graham;    

All the code for RadioWidget except draw- and event-related code. Some minimal code for ScrollingMenuWidget.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/


using namespace std;























#ifndef _ALL_MENU_H_
#define _ALL_MENU_H_

#include <string>
#include <math.h>

// a struct used to associate strings with their integer IDs for
// entries in RadioWidgets
/*struct {
	string s;
	int ID;
} RadioEntry;*/

// a struct used to associate strings with their integer IDs in 
// ScrollingMenuWidgets
/*struct {
	int imageID;
	string caption;
	int ID;
} ScrollingMenuEntry;*/


#endif
