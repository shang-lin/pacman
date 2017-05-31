/*************  REVISION HISTORY  *********************












date: 2002/06/05 21:32:35;  
author: graham;    
RadioWidget now draws properly. Guess it's time to start hardcoding the menus..



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/05 00:30:46;  
author: graham;    
Tweaked drawing methods.



date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/05/08 07:38:20;  
author: graham;    

Made slight modifications to the widget classes to make MenuPane work.



date: 2002/05/07 02:28:28;  
author: graham;    

Added an isSelectable() function to all menuwidgets. It returns true if the widget is something that can be modified (eg, a slider) and false if it cannot be modified (eg, a label). MenuPane needs this information when it moves from one widget to the next.



date: 2002/03/21 05:27:28;  
author: graham;    

Added comments to the code.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:26:34;  
author: graham;    

Fixed a bug where scrolling past the top of the list led to a bus error.



date: 2002/03/14 22:42:34;  
author: graham;    

RadioWidget's eventhandling has been completely tested.



date: 2002/03/14 21:57:04;  
author: graham;    

Modified the test event class to create the various kinds of arrowkey events (ie, up, down, right left) properly. Eliminated some bugs from RadioWidget, although it's not quite working yet.



date: 2002/02/23 07:43:14;  
author: graham;    

Modified the RadioWidget code. It now handles events. I also modified the constructor so that the number of elements can be specified instead of being a fixed value. The addEntry() methods now also check that the specified ID is not already assigned to an item in the widget.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/21 11:14:06;  
author: graham;    

Fixed a bug i saw in the code. I was returning the index in an array when i should have been returning data from the object to which that item in the array pointed.



date: 2002/02/21 11:05:56;  
author: graham;    

All the code for RadioWidget except draw- and event-related code. Some minimal code for ScrollingMenuWidget.



date: 2002/02/20 11:23:23;  
author: graham;    

More slight modifications to these Widget classes..



date: 2002/02/19 00:33:45;  
author: graham;    

Modifications to the RadioWidget class. Also, I missed the ButtonWidget.cc file earlier, so i'm adding it now.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "RadioWidget.h"
#include "MenuWidget.h"
#include "drawableobject.h"
#include "Event.h"




/*******************************************************************************/
/* Hilites the next item in the menu.                                          */
/*******************************************************************************/
void RadioWidget::hiliteNextItem( void ) {
	hilitedOption = (hilitedOption + 1) % (numItems);
//	if (hilitedOption >= numItems) hilitedOption = 0;
}

/*******************************************************************************/
/* Hilites the previous item in the menu.                                      */
/*******************************************************************************/
void RadioWidget::hilitePreviousItem( void ) {
	hilitedOption--;
	if (hilitedOption < 0) hilitedOption = numItems-1;
}

/*******************************************************************************/
/* This class accepts return/enter events (checks the currently-hilited        */
/* button), up/left-arrow events (hilites previous item), down/right-arrow     */
/* events (hilites next item).                                                 */
/*******************************************************************************/
void RadioWidget::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT){
		switch (e->getType()){
			case arrowkey:
				switch (e->getValue()){
					
					/* if they hit uparrow, select the previous item       */
					case ARROW_UP:
						hilitePreviousItem ();
						if ( hilitedOption >= 0 && hilitedOption <= getNumItems()){
							setValue(itemList[hilitedOption]->getID());
						}
						break;
					
					/* if they hit leftarrow, select the previous item     */
					case ARROW_LEFT:
						hilitePreviousItem ();
						if ( hilitedOption >= 0 && hilitedOption <= getNumItems()){
							setValue(itemList[hilitedOption]->getID());
						}
						break;
					
					/* if they hit downarrow, hilite the next item         */
					case ARROW_DOWN:
						hiliteNextItem ();
						if ( hilitedOption >= 0 && hilitedOption <= getNumItems()){
							setValue(itemList[hilitedOption]->getID());
						}
						break;
					
					/* if they hit rightarrow, hilite the next item        */
					case ARROW_RIGHT:
						hiliteNextItem ();
						if ( hilitedOption >= 0 && hilitedOption <= getNumItems()){
							setValue(itemList[hilitedOption]->getID());
						}
						break;
					
					/* other arrowkeys are ignored                         */
				}
				break;
			
			/*  If the current value of hilitedoption is good, select */
			/*  that option.                                          */
			case enterkey:
				if ( hilitedOption >= 0 && hilitedOption <= getNumItems()){
					setValue(itemList[hilitedOption]->getID());
				}
				break;
			
			
			
		}
	}
	/* all other events are ignored.                                           */
	
}

/*******************************************************************************/
/* Returns the widget identification number of this object.                    */
/*******************************************************************************/
int RadioWidget::getWidgetID( void ) {
	return widgetID;
}

/*******************************************************************************/
/* Returns the ID number of the currently checked entry.                       */
/*******************************************************************************/
int RadioWidget::getValue( void ) {
	return itemList[checkedOption]->getID();
}

/*******************************************************************************/
/* Returns the ID number of the currently hilited entry.                       */
/*******************************************************************************/
int RadioWidget::getHilitedValue( void ) {
	return itemList[hilitedOption]->getID();
}

/*******************************************************************************/
/* Checks the entry with the given ID, or does nothing if no                   */
/* such entry exists.                                                          */
/*******************************************************************************/
void RadioWidget::setValue( int ID ) {
	// iterate through the entries. if we find one with
	// the specified ID, check it.
	for (int i = 0; i < numItems; i++){
		if (itemList[i]->getID() == ID){
			checkedOption = i;
		}
	}
}

/*******************************************************************************/
/* Adds an entry with the given caption and ID if no entry with                */
/* that ID exists, and returns true. Returns false if an entry                 */
/* with that ID already exists.                                                */
/*******************************************************************************/
bool RadioWidget::addEntry( string caption, int ID ) {
	bool goodItem = (getNumItems() < getMaxItems() && isValid(ID));
	
	/* only add the entry if we have space and it's not a duplicate ID         */
	if (goodItem){
		
		itemList[numItems] = new RadioEntry(caption, ID);

		/* if it's the first item, automatically check & hilite it             */
		if (getNumItems() == 0){
			setValue(ID);
			hilitedOption = numItems;
		}
		
		
		/* increase the number of items                                       */
		numItems++;
	}
	
	return goodItem;
}

/*******************************************************************************/
/* Adds an entry with the given caption and ID if no entry with                */
/* that ID exists, and returns true. Returns false if an entry                 */
/* with that ID already exists. If bool is true, it checks this                */
/* new entry, otherwise, the entry is unchecked.                               */
/*******************************************************************************/
bool RadioWidget::addEntry( string caption, int ID, bool checked ) {
	if (numItems < 10 && isValid(ID)){

		itemList[numItems] = new RadioEntry(caption, ID);

		if (checked) setValue(ID);
		
		// if it's the first item, hilite it
		if (getNumItems() == 0){hilitedOption = numItems;}

		numItems++;

		return true;
	} else {
		return false;
	}
}

/*******************************************************************************/
/* Returns the maximum number of items in the RadioWidget.                     */
/*******************************************************************************/
int RadioWidget::getMaxItems( void ) {
	return maxItems;
}

/*******************************************************************************/
/* Returns the number of items in the RadioWidget.                     */
/*******************************************************************************/
int RadioWidget::getNumItems( void ) {
	return numItems;
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void RadioWidget::draw ( void ) {
	
	// get the size of the window
    int win_width, win_height;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);

	// save openGL's current settings
    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	
	// set the window extants
	#ifdef k_UNSELECTED_ITEMS_SWIM
    glOrtho(0 + 5*sin(r1), win_width + 5 * sin(r2), 0 + 5* cos(r3), win_height+ 5*sin(r2+r3), 10,-10);
	#else
    glOrtho(0 , win_width , 0 , win_height, 10,-10);
	#endif

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	#ifdef k_UNSELECTED_ITEMS_SWIM
	// if selected items are supposed to swim around, increment
	// the angles we're using to calculate the modified position
	r1 += .005*((float)(rand() % 10));
	r2 += .005*((float)(rand() % 10));
	r3 += .005*((float)(rand() % 10));
	#endif
	
	// move the center to the center of the radio widget
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	glColor3ub(50, 50, 152);
	// draw the radio widget's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// now, we want a border of 3 pixels across the box. 
	// so given the usable space in the box and the
	// number of radio entries, how do we want to
	// position the damn things?
	//
	// let's assume that entries need 24 vertical pixels
	// of space and 200 horizontal pixels of space. then,
	// try to put as many in a row as possible.
	int entriesPerRow = (DrawableObject::getWidth () - 6 )/200;
	
	// if we were dumb and made it too narrow and we get zero
	// for entriesPerRow, set its value to one.
	if (entriesPerRow < 1 ) entriesPerRow = 1;
	
	
	// and how many rows does this imply?
	int numRows = (int)(numItems / entriesPerRow);
	if (numItems % entriesPerRow != 0){
		numRows++;
	}
	
	// and what's the margin between rows? note that we also
	// want top and bottom margins
	int v_margin = ((DrawableObject::getHeight () - 6 ) -(24* numRows)) / (numRows + 1);
	
	// and calculate the horizontal margin..
	int h_margin = ((DrawableObject::getWidth () - 6 ) -(200 * entriesPerRow)) / (entriesPerRow + 1);
	
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < entriesPerRow; j++){
			
			// this is the current index in the array.
			int current_index = (numRows-1-i)*entriesPerRow + j;
			
			if (current_index < numItems){
			//	if (current_index != hilitedOption)
					if (current_index != checkedOption)
						glColor3ub(110, 110, 180);
					else
						glColor3ub(180, 110, 110);
			//	else
			//		if (current_index != checkedOption)
			//			glColor3ub(50, 50, 200);
			//		else
			//			glColor3ub(200, 50, 50);
					
				
				glPushMatrix();
				glTranslatef (-DrawableObject::getWidth()/2 + 3 + 200*j + (j+1)*h_margin + 100, -DrawableObject::getHeight()/2 +3  + (i+1)*v_margin + i*24 + 12, 0);
				glRectf (-95,-12,95,12);

				int label_width = Text::getStringWidth ( (itemList[current_index]->getLabel()).data() );
				
				
				glColor3ub(110, 180, 110);
				
				Text::print ((itemList[current_index]->getLabel()).data(), (DrawableObject::getCenterX()) - DrawableObject::getWidth()/2 + 3 + 200*j + (j+1)*h_margin + 100 - (label_width/2), (win_height-DrawableObject::getCenterY()) - DrawableObject::getHeight()/2 + 3 + (i+1)*v_margin + i*24 + 4);
				
				glPopMatrix();
			}
		}
	
	
	
	
	// restore openGL's previous settings
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

/*******************************************************************************/
/* Draws the widget in "selected" mode.                                        */
/*******************************************************************************/
void RadioWidget::drawSelected ( void ){
	
	// get the size of the window
    int win_width, win_height;
	win_width = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);

	// save openGL's current settings
    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	
	// set the window extants
	#ifdef k_SELECTED_ITEMS_SWIM
    glOrtho(0 + 5*sin(r1), win_width + 5 * sin(r2), 0 + 5* cos(r3), win_height+ 5*sin(r2+r3), 10,-10);
	#else
    glOrtho(0 , win_width , 0 , win_height, 10,-10);
	#endif

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	#ifdef k_SELECTED_ITEMS_SWIM
	// if selected items are supposed to swim around, increment
	// the angles we're using to calculate the modified position
	r1 += .005*((float)(rand() % 10));
	r2 += .005*((float)(rand() % 10));
	r3 += .005*((float)(rand() % 10));
	#endif
	
	// move the center to the center of the radio widget
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	glColor3ub(0, 0, 255);
	// draw the radio widget's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// now, we want a border of 3 pixels across the box. 
	// so given the usable space in the box and the
	// number of radio entries, how do we want to
	// position the damn things?
	//
	// let's assume that entries need 24 vertical pixels
	// of space and 200 horizontal pixels of space. then,
	// try to put as many in a row as possible.
	int entriesPerRow = (DrawableObject::getWidth () - 6 )/200;
	
	// if we were dumb and made it too narrow and we get zero
	// for entriesPerRow, set its value to one.
	if (entriesPerRow < 1 ) entriesPerRow = 1;
	
	
	// and how many rows does this imply?
	int numRows = (int)(numItems / entriesPerRow);
	if (numItems % entriesPerRow != 0){
		numRows++;
	}
	
	// and what's the margin between rows? note that we also
	// want top and bottom margins
	int v_margin = ((DrawableObject::getHeight () - 6 ) -(24* numRows)) / (numRows + 1);
	
	// and calculate the horizontal margin..
	int h_margin = ((DrawableObject::getWidth () - 6 ) -(200 * entriesPerRow)) / (entriesPerRow + 1);
	
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < entriesPerRow; j++){
			
			// this is the current index in the array.
			int current_index = (numRows-1-i)*entriesPerRow + j;
			
			if (current_index < numItems){
				if (current_index != hilitedOption)
					if (current_index != checkedOption)
						glColor3ub(110, 110, 180);
					else
						glColor3ub(180, 110, 110);
				else
					if (current_index != checkedOption)
						glColor3ub(50, 150, 255);
					else
						glColor3ub(170, 0, 50);
					
				
				glPushMatrix();
				glTranslatef (-DrawableObject::getWidth()/2 + 3 + 200*j + (j+1)*h_margin + 100, -DrawableObject::getHeight()/2 + 3 + (i+1)*v_margin + i*24 + 12, 0);
				glRectf (-95,-12,95,12);

				int label_width = Text::getStringWidth ( (itemList[current_index]->getLabel()).data() );
				
				glTranslatef (-label_width/2,8,0);
				
				if (current_index != hilitedOption)
					glColor3ub(110, 180, 110);
				else
					glColor3ub(0, 255, 0);
				
				Text::print ((itemList[current_index]->getLabel()).data(), (DrawableObject::getCenterX()) - DrawableObject::getWidth()/2 + 3 + 200*j + (j+1)*h_margin + 100 - (label_width/2), (win_height-DrawableObject::getCenterY()) - DrawableObject::getHeight()/2 + 3 + (i+1)*v_margin + i*24 + 4);
				
				glPopMatrix();
			}
		}
	
	
	
	
	// restore openGL's previous settings
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}


/*******************************************************************************/
/* Returns true iff an item with id_query is not already in the                */
/* list of items. Otherwise, returns false.                                    */
/*******************************************************************************/
bool RadioWidget::isValid( int id_query ) {
	bool b = true;
	
	/* iterate through the elements. if any one of them has the same ID, set b */
	/* to false;                                                               */
	for (int i = 0; i < getNumItems(); i++){
		if (itemList[i]->getID() == id_query){
			b = false;
		}
	}
	
	return b;
}



/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a RadioWidget with the given size and position, and                 */
/* initializes the array of radio button entries to the size                   */
/* of numElems.                                                                */
/*******************************************************************************/
RadioWidget::RadioWidget ( int width, int height, int centerX, int centerY, int wid):
MenuWidget (width, height, centerX, centerY, wid) {
	//itemList = new RadioEntry[10];
	for (int i = 0; i < 10; i++){
		itemList[i] = 0x0L;
	}
	maxItems = 10;
	numItems = 0;
	hilitedOption = -1;
	widgetID = wid;

	r1 = r2 = r3 = 0;
}



/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

RadioWidget::~RadioWidget ( void ) {
	
}

