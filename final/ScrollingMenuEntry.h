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



date: 2002/05/08 07:37:09;  
author: graham;  

Moved the definition of ScrollingMenuEntry to a separate file during debugging. It turns out that this was unnecessary because the problem was elsewhere, but i think i'll keep it in a separate file for organizational purposes.


***********  END REVISION HISTORY **********/


using namespace std;


#ifndef _SCROLLINGMENUENTRY_H_
#define _SCROLLINGMENUENTRY_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <string>
#include <math.h>




class ScrollingMenuEntry {
	private:
		string caption;
		int imageID;
		int ID;
		bool showCaption;
		bool showImage;
	public:
		
		int getID( void ) { return ID; }
		int getImageID( void ) { return imageID; }
		string getCaption( void ) { return caption; }
		bool displayCaption ( void ) { return showCaption; }
		bool displayImage ( void ) { return showImage; }
		
		ScrollingMenuEntry (int iid, string s, bool showc, bool showi, int id){
			imageID = iid;
			caption = s;
			showCaption = showc;
			showImage = showi;
			ID = id;
		}
};

#endif
