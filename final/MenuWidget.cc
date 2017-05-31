/*************  REVISION HISTORY  *********************



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/05/12 09:34:45;  
author: graham;    

Added two #defines to control what set of graphics options the menusystem compiles with. The options toggle "swim mode" for selected and unselected widgets. If swim mode is on, the item "swims" around the screen. otherwise, it stays in one place.



date: 2002/05/08 07:38:20;  
author: graham;    

Made slight modifications to the widget classes to make MenuPane work.



date: 2002/05/07 02:28:28;  
author: graham;    

Added an isSelectable() function to all menuwidgets. It returns true if the widget is something that can be modified (eg, a slider) and false if it cannot be modified (eg, a label). MenuPane needs this information when it moves from one widget to the next.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/14 20:38:00;  
author: graham;    

The ButtonWidget code here is completely tested, except that the graphics stuff isn't done yet. The Event classes are test event classes that construct inputevents out of alphanumeric keypresses for the purpose of testing the widgets.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/18 23:59:15;  
author: graham;    

Wrote some of the menusystem setup code.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "MenuWidget.h"
#include "drawableobject.h"






/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a MenuWidget with the specified dimensions and location.            */
/*                                                                             */
/*******************************************************************************/
MenuWidget::MenuWidget ( int width, int height, int centerX, int centerY, int widgetID ) 
: DrawableObject ( -1, width, height, centerX, centerY)
{
	// nothing to do
}

