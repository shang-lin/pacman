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



date: 2002/03/21 05:27:28;  
author: graham;    

Added comments to the code.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/14 21:57:04;  
author: graham;    

Modified the test event class to create the various kinds of arrowkey events (ie, up, down, right left) properly. Eliminated some bugs from RadioWidget, although it's not quite working yet.



date: 2002/03/14 20:38:00;  
author: graham;    

The ButtonWidget code here is completely tested, except that the graphics stuff isn't done yet. The Event classes are test event classes that construct inputevents out of alphanumeric keypresses for the purpose of testing the widgets.



date: 2002/02/22 00:10:13;  
author: graham;    

Added deletekey, forwarddeletekey, and alphanumeric as keyboard input types.



date: 2002/02/21 23:18:47;  
author: graham;    

Added an enumerated type for event classes, so that generic events can return whether they are an input event or a game event.



date: 2002/02/19 09:06:49;  
author: graham;  

This is a header file containing all the enumerated types that I'm using. So far, there is an enumerated type EventTypeID for the event type, and an enumerate type for the arrowkey direction (ie: up, down, left, right).


***********  END REVISION HISTORY **********/


using namespace std;








#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <math.h>

// These are the different types of input events
enum EventTypeID {noevent, tabkey, shifttabkey, enterkey, arrowkey, escapekey, deletekey, forwarddeletekey, alphanumeric};

// these are the directions an arrow key event can have.
enum ArrowKeyDirection {ARROW_UP, ARROW_DOWN, ARROW_RIGHT, ARROW_LEFT};

// these are the different classes of events.
enum EventClassID {NO_EVENT_CLASS, INPUT_EVENT, GAME_EVENT};

#endif
