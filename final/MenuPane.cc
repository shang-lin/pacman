/*************  REVISION HISTORY  *********************



date: 2002/06/06 10:23:20;  
author: graham;    
Menusystem handles the args to console client.



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/05/12 11:43:40;  
author: graham;    

No changes were made these files, but CVS insists that i need to commit them again.



date: 2002/05/10 01:41:13;  
author: graham;    

Added more graphics code.



date: 2002/05/08 07:42:03;  
author: graham;    

MenuPane is working! There was a bug in the selectNext() method causing the tabkey not to work. I still need to make some changes to the selectNext() and selectPrevious() methods; if you're at the end of the linked list of widgets, it just moves to the first or last widget without checking that the widget is selectable.



date: 2002/05/08 02:59:18;  
author: graham;    

Still trying to get menupane working. it's not compiling right.



date: 2002/05/07 02:27:10;  
author: graham;    

It now checks that the next widget is selectable before making it the current widget. otherwise, it skips it.



date: 2002/05/07 02:17:51;  
author: graham;    

Finally filled in the menupane code.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/15 12:10:50;  
author: graham;    

This MenuPane code doesn't quite compile yet.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/19 07:36:31;  
author: graham;    

More menusystem code; some event-handling code in MenuPane and MenuSystem.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "MenuPane.h"
#include "drawableobject.h"


/*******************************************************************************/
/* This method causes the next selectable widget in the MenuPane               */
/* to become selected.                                                         */
/*******************************************************************************/
void MenuPane::selectNextWidget( void ) {
	if (curr != NULL)
		do {
			curr = curr->next;
		} while ( curr != NULL && ! (curr->w)->isSelectable() );
	if (curr == NULL){
		curr = head;
		while ( curr != NULL && ! (curr->w)->isSelectable() ) {
			curr = curr->next;
		} 
		if (curr == NULL)
			curr = head;
	}
}

/*******************************************************************************/
/* Causes the previous selectable widget to become the selected                */
/* widget.                                                                     */
/*******************************************************************************/
void MenuPane::selectPreviousWidget( void ) {
	if (curr != NULL)
		do {
			curr = curr->prev;
		} while ( curr != NULL && !(curr->w)->isSelectable() );
	if (curr == NULL){
		curr = tail;
		while ( curr != NULL && !(curr->w)->isSelectable() ) {
			curr = curr->prev;
		} 
		if (curr == NULL)
			curr = tail;
	}
}



/*******************************************************************************/
/* This method either accepts/handles events or passe them to                  */
/* the current menuwidget. MenuPanes accept tab events                         */
/*******************************************************************************/
void MenuPane::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT){
		switch (e->getType()){
		case tabkey:
			selectNextWidget();
			break;
		case shifttabkey:
			selectPreviousWidget();
			break;
		default:
			(curr->w)->receiveEvent( e );
			break;
		}
	}
	/* all other events are ignored.                                           */
}

/*******************************************************************************/
/* This method adds the given pointer to the list of widgets                   */
/* in the menupane.                                                            */
/*******************************************************************************/
void MenuPane::addWidget( MenuWidget * mw ) {
	if (head == NULL){
		head = new WidgetNode;
		head->w = mw;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
		curr = head;
	} else {
		WidgetNode * temp = tail;
		tail = new WidgetNode;
		tail->w = mw;
		temp->next = tail;
		tail->prev = temp;
		tail->next = NULL;
	}
}

/*******************************************************************************/
/* This method draws the MenuPane and all of its widgets.                      */
/*******************************************************************************/
void MenuPane::draw( void ) {
	// draw the background
	
	// iterate through the widget array and draw each widget.
	WidgetNode * temp = head;
	while (temp != NULL){
		if (temp == curr) (temp->w)->drawSelected();
		else {
			// for some reason, it was segfaulting when i 
			// had (temp->w)->draw, so i changed it to this.
			MenuWidget * mwp = temp->w;
			mwp->draw();
		}
		temp = temp->next;
	}
}

/*******************************************************************************/
/* This method returns a pointer to the MenuWidget with the provided           */
/* ID, or a null pointer if the MenuPane isn't aware of any such               */
/* widget.                                                                     */
/*******************************************************************************/
MenuWidget * MenuPane::getWidget( int ID ) {
	WidgetNode * wn = head;

	while (wn != 0x0L){
		if ((wn->w)->getWidgetID() == ID)
			return wn->w;
		wn = wn->next;
	}
	
	// if we've gotten to this point, there wasn't a widget with
	// that ID, so return a NULL pointer.
	return 0x0L;
}

/*******************************************************************************/
/* This method returns the ID of the current widget. This is for testing.      */
/*******************************************************************************/
int MenuPane::getID( void ){
	return (curr->w)->getWidgetID();
}

/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

MenuPane::MenuPane (int width, int height, int centerX, int centerY, int backgroundImageID) :
DrawableObject (-1, width, height, centerX, centerY){
	curr = NULL;
	head = NULL;
	tail = NULL;
	bgImageID = backgroundImageID;
}


/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

MenuPane::~MenuPane ( void ) {
}

