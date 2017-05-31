/*************  REVISION HISTORY  *********************



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/04 02:21:09;  
author: graham;    
Trying to get the menusystem test program working.



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




date: 2002/03/14 22:42:34;  
author: graham;    

RadioWidget's eventhandling has been completely tested.



date: 2002/03/14 21:57:04;  
author: graham;    

Modified the test event class to create the various kinds of arrowkey events (ie, up, down, right left) properly. Eliminated some bugs from RadioWidget, although it's not quite working yet.



date: 2002/03/14 20:38:00;  
author: graham;    

The ButtonWidget code here is completely tested, except that the graphics stuff isn't done yet. The Event classes are test event classes that construct inputevents out of alphanumeric keypresses for the purpose of testing the widgets.



date: 2002/03/01 10:26:10;  
author: graham;  

This is a file containing definitions for Event and InputEvent classes that i'm using to test the menusystem components. These aren't the actual classes we'll be using. I just wanted to test the menusystem stuff without waiting for the event and graphics code to be written.


***********  END REVISION HISTORY **********/


using namespace std;








#ifndef _EVENT_H_
#define _EVENT_H_

#include "enums.h"
#include <math.h>


/*

	 This wasn't originally going to be the real event class. We were going
	 to have a whole event system for the game. However, first term, the
	 menus were the only part that were using the event class and the 
	 graphics weren't working yet (so i didn't have access to the GLUT
	 keypress functions), so i created a "fake" event class that 
	 translated some ascii characters into other types of events so that
	 i could test the menu widgets and menu panes quickly. for
	 example, W, A, D, and S represented the arrow keys. 

	 anyhow, once we got to second term, we decided to simply pass
	 the UDPPacket objects around instead. Because i already was using
	 events in the menus, and because UDP packets aren't being sent
	 when the game is in menu mode, i decided just to fix up
	 this event class. GLUT now sends regular and special keystrokes
	 to MenuSystem, which translates them into Input Events that the
	 various menu-related classes can handle.
	
	 
	 */











/* 
	 This class was originally going to be the superclass for all
	 Event types, but since we're not using Events, InputEvent is 
	 the only thing that subclasses it.
	 */

class Event {
	
	EventClassID ec;
	
	public:

	// constructor
	Event ( EventClassID );

	// returns the byte value of the event
	virtual char getValue ( void ){
		return '\0';
	}
		
	// returns the type of event. 
	virtual int getType ( void ){
		return -1;
	}

	// returns the class of event
	EventClassID getEventClass (void );
	
};

/*******************************************************************************/
/* again, not the real class, this is just used for testing. it accepts */
/* individual character, some of which are interpreted as other things, such */
/* as arrow keys. anything that's not redirected is interpreted as alphanumeric. */
/*******************************************************************************/
class InputEvent : public Event {
	
	private:
	// the event type. the listing of available types is in enums.h
	EventTypeID et;
	
	// a character value associated with the input event. 
	char value;
	
	// if it's an arrowkey, we need to keep track of the direction
	ArrowKeyDirection arrowvalue;
	
	public:
	
	// returns the event type (eg, arrow key, enter key, tab, etc.)
	int getType ( void );	
	
	// returns the associated value
	char getValue ( void );	
	
	// returns the event class (ie, INPUT_EVENT)
	EventClassID getEventClass (void );
	
	// the constructor. This event class takes a character and interprets
	// it as an event.
	InputEvent (char c, char type = '\0' );
};
#endif
