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



date: 2002/03/14 20:39:01;  
author: graham;  

Code for testing ButtonWidget. The Event code isn't the actual event code; it's for testing purposes only.


***********  END REVISION HISTORY **********/










#include "Event.h"

// constructor for the Event class. EventClassIDs are described in
// enums.h
	Event::Event ( EventClassID n ){
		ec = n;
	}

// returns the class of event. EventClassIDs are described in enums.h
	EventClassID Event::getEventClass (void){ return ec; }

/*
	The InputEvent Class accepts individual character, some of 
	which are interpreted as other things, such as arrow keys. 
	anything that's not redirected is interpreted as alphanumeric.
	*/
	int InputEvent::getType ( void ){
		return (int)et;
	}
	
	char InputEvent::getValue ( void ){
		char retval = value;
		if (et == arrowkey){
			retval = (char)arrowvalue;
		}
		return retval;
	}
	
	EventClassID InputEvent::getEventClass (void){
		return INPUT_EVENT;
	}

/* 
	the constructor accepts a character value and a character type
	descriptor. the type descriptor has a default value corresponding
	to alphanumeric input. If the type descriptor is '\0', then
	the constructor assumes that the character c is also the type
	descriptor.
	 */
	InputEvent::InputEvent (char c, char type) : Event ( INPUT_EVENT ){
		char typeindicator;
		if (type == '\0')
			typeindicator = c;
		else
			typeindicator = type;
		switch (typeindicator){
			case '1':
				et = noevent;
				break;
			case '2':
				et = tabkey;
				break;
			case '3':
				et = shifttabkey;
				break;
			case '4':
				et = enterkey;
				break;
			case 'w':
				et = arrowkey;
				arrowvalue = ARROW_UP;
				break;
			case 'a':
				et = arrowkey;
				arrowvalue = ARROW_LEFT;
				break;
			case 'd':
				et = arrowkey;
				arrowvalue = ARROW_RIGHT;
				break;
			case 's':
				et = arrowkey;
				arrowvalue = ARROW_DOWN;
				break;
			case '6':
				et = escapekey;
				break;
			case '7':
				et = deletekey;
				break;
			case '8':
				et = forwarddeletekey;
				break;
			default:
				et = alphanumeric;
				break;
		}
		value = c;
	}
