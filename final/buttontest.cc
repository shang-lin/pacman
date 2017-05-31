/*************  REVISION HISTORY  *********************



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/14 21:57:04;  
author: graham;    

Modified the test event class to create the various kinds of arrowkey events (ie, up, down, right left) properly. Eliminated some bugs from RadioWidget, although it's not quite working yet.



date: 2002/03/14 20:39:01;  
author: graham;  

Code for testing ButtonWidget. The Event code isn't the actual event code; it's for testing purposes only.


***********  END REVISION HISTORY **********/

























#include "enums.h"
#include "Event.h"
#include "MenuWidget.h"
#include "ButtonWidget.h"
#include <iostream>
#include <string>

/*******************************************************************************/
/* This code simply tests the button widget class.                             */
/*******************************************************************************/

int main (void){
	char c;
	InputEvent * ie;
	
	/* create the button we're goingt to test                                  */
	ButtonWidget * bw = new ButtonWidget (20,20,50,50,"hamster",55);;
	
	/* read in characters until we get to a pound sign                         */
	do {
		/* display the current state of the button:                           */
		cout << "The label on the button is :    " << bw->getText() << endl;;
		cout << "The ID # of the button is :    " << bw->getWidgetID() << endl;;
		if (bw->isClicked()){
			cout << "The state of the button is :    clicked" << endl;;
		} else {
			cout << "The state of the button is :    not clicked" << endl;;
		}
		
		cin >> c;
		
		/* tell them what character they entered                              */
		cout << "Your input was :" << c << endl;
		
		
		cout << "Creating an input event..."<< endl;
		
		/* construct an input event from that character.                      */
		/* buttons only respond to enterkey events, which cause them to       */
		/* click/unclick themselves                                           */
		ie = new InputEvent(c);
		
		/* display information on that event                                  */
		cout << "The input event is of type  " <<  ie->getType() << endl;
		cout << "The input event is of class " <<  ie->getEventClass() << endl;
		cout << "The input event has value   " <<  ie->getValue() << endl<< endl;
		
		cout << "Sending the input event to the buttonwidget..."<< endl;
		
		/* send the event to the buttonwidget. it will handle the event, and  */
		/* change its                                                         */
		/* state as appropriate.                                              */
		bw->receiveEvent (ie);
		
		cout << endl ;
	} while (c != '#');
	
	/* now that we've tested whether or not it responds appropriately to       */
	/* inputevents,                                                            */
	/* let's test the label-changing function.                                 */
	cout << "testing label changing code..."<<endl;
	bw->setText("Not Hamster");
	
	/* and after we try to change the label, let's display the new state of    */
	/* the button, which should be identical to the previous one, except that  */
	/* the label of the button has changed.                                    */
	cout << "The label on the button is :    " << bw->getText() << endl;;
	if (bw->isClicked()){
		cout << "The state of the button is :    clicked" << endl;;
	} else {
		cout << "The state of the button is :    not clicked" << endl;;
	}
	
}