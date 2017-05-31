/*************  REVISION HISTORY  *********************



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/03/21 05:27:28;  
author: graham;    

Added comments to the code.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/15 04:31:27;  
author: graham;  

modified textinputwidget classes, and a textinputtest program. the text input widget isn't quite perfect yet; there are still some issues with it not retaining the correct cursor position when characters are deleted from the end of the string, as well as the up and down arrows not moving the cursor to the beginning and end of the input text.


***********  END REVISION HISTORY **********/




#include "enums.h"
#include "Event.h"
#include "MenuWidget.h"
#include "TextInputWidget.h"
#include <iostream>
#include <string>

// This code simply tests my stripped-down event class. i want to make sure it's working right before i use it to test the menuwidgets.

int main (void){
	char c;
	
	// create an input event pointer
	InputEvent * ie;
	
	// create two text widgets, one testing each constructor
	TextInputWidget * bw = new TextInputWidget (20,20,50,50, 100);
	TextInputWidget * bw2 = new TextInputWidget (20,20,50,50,"Default Text", 200);
	
	// read in characters until we get to a pound sign
	do {
	
		// output the state of the widgets
		cout << "Widget 1 has text " << bw->getValue() << endl;
		cout << "  cursor position " << bw->getPosition() << endl;
		cout << "    widget number " << bw->getWidgetID() << endl;
		cout << endl;
		
		cout << "Widget 2 has text " << bw2->getValue() << endl;
		cout << "  cursor position " << bw2->getPosition() << endl;
		cout << "    widget number " << bw2->getWidgetID() << endl;
		
		cin >> c;
		
		// tell them what character they inputted
		cout << "Your input was :" << c << endl;
		
		
		cout << "Creating an input event..."<< endl;
		
		// construct an input event from that character
		ie = new InputEvent(c);
		
		// display information on that event
		cout << "The input event is of type  " <<  ie->getType() << endl;
		cout << "The input event is of class " <<  ie->getEventClass() << endl;
		cout << "The input event has value   " <<  ie->getValue() << endl<< endl;
		
		cout << "Sending the input event to the radiowidget..."<< endl;
		
		// send the input event to the widgets
		bw->receiveEvent (ie);
		bw2->receiveEvent (ie);
		
		cout << endl ;
	} while (c != '#');
}