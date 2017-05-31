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





date: 2002/06/04 23:16:27;  
author: graham;    
ScrollingMenuWidget's drawing routines now work better.



date: 2002/06/04 02:00:15;  
author: graham;    
Fixed a couple of lines in TextINputWidget and ScrollingMenuWidget that were generating warnings (the compiler wanted me to explicityly cast doubles to ints). Created a test program for the menusystem/graphics.



date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/05/13 10:03:13;  
author: graham;    

Added the scrollbar part of the scrolling widget. Now, it just need to be able to display images.



date: 2002/05/13 09:36:27;  
author: graham;    

ScrollingMenuWidget's graphics code is 80% done. i just need to add the code that draws the image corresponding to the selection, and the code that draws the scrollbar. Once that's done, i just need to copy the draw() code into the drawSelected() method and alter the colors.



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




date: 2002/03/16 21:27:06;  
author: graham;    

Fixed a slight bug where scrolling past the first element in the list caused a bus error.



date: 2002/03/15 11:48:40;  
author: graham;    

ScrollingMenuWidget is completely tested, as far as eventhandling goes. It doesn't draw yet.



date: 2002/03/15 11:23:26;  
author: graham;    

Untested ScrollingMenuWidget code.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/21 11:05:56;  
author: graham;    

All the code for RadioWidget except draw- and event-related code. Some minimal code for ScrollingMenuWidget.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "ScrollingMenuWidget.h"
#include "MenuWidget.h"
#include "drawableobject.h"




/*******************************************************************************/
/* Adds the given image/caption pair as an item in the menu,                   */
/* and assigns that pair and int ID.                                           */
/*******************************************************************************/
void ScrollingMenuWidget::addMenuItem( int imageID, string caption, int ID ) {
	// check to make sure there's space in the array
	if (getNumItems() < 100){
		// crreate a pointer to a new scrolling menu entry in the next location in the array
		sme[getNumItems()] = new ScrollingMenuEntry( imageID, caption, true, true, ID );
		
		// increase the number of items
		numItems++;
		
		// if we've added a first item, select it by default
		if (numItems == 1){
			currSelection = 0;
		}
	}
}

/*******************************************************************************/
/* Returns the ID of the currently selected item in the menu.                  */
/*                                                                             */
/*******************************************************************************/
int ScrollingMenuWidget::getSelection( void ) {
	return sme[currSelection]->getID();
}

/*******************************************************************************/
/* Returns the number of items currently listed in the menu.                   */
/*                                                                             */
/*******************************************************************************/
int ScrollingMenuWidget::getNumItems( void ) {
	return numItems;
}

/*******************************************************************************/
/* Returns widget identification number.                                       */
/*                                                                             */
/*******************************************************************************/
int ScrollingMenuWidget::getWidgetID( void ) {
	return widgetID;
}

/*******************************************************************************/
/* Selects the next item in the menu.                                          */
/*******************************************************************************/
void ScrollingMenuWidget::selectNext( void ) {
	currSelection = (currSelection + 1) % getNumItems();
}

/*******************************************************************************/
/* Selects the previous item in the menu.                                      */
/*******************************************************************************/
void ScrollingMenuWidget::selectPrevious( void ) {
	currSelection = (getNumItems() + currSelection - 1) % getNumItems();
}


// returns true if any entry in the list has a corresponding image
bool ScrollingMenuWidget::usesImages ( void ){
	for (int i = 0; i < getNumItems(); i++)
		if ( sme[i]->displayImage())
			return true;
	return false;
}


/*******************************************************************************/
/* This class accepts return/enter events (checks the currently-hilited        */
/* button), up/left-arrow events (hilites previous item), down/right-arrow     */
/* events (hilites next item).                                                 */
/*******************************************************************************/
void ScrollingMenuWidget::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT){
		switch (e->getType()){
			case arrowkey:
				switch (e->getValue()){
					
					/* if they hit uparrow, select the previous item       */
					case ARROW_UP:
						selectPrevious ();
						break;
					
					/* if they hit leftarrow, select the previous item     */
					case ARROW_LEFT:
						selectPrevious ();
						break;
					
					/* if they hit downarrow, hilite the next item         */
					case ARROW_DOWN:
						selectNext ();
						break;
					
					/* if they hit rightarrow, hilite the next item        */
					case ARROW_RIGHT:
						selectNext ();
						break;
					
					/* other arrowkeys are ignored                         */
				}
				break;
			
			/*  If the current value of hilitedoption is good, select */
			/*  that option.                                          */
			case enterkey:
				break;
			
			
			
		}
	}
	/* all other events are ignored.                                           */
	
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void ScrollingMenuWidget::draw ( void ) {
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
		// if unselected items are supposed to swim around, increment
		// the angles we're using to calculate the modified position
		r1 += .005*((float)(rand() % 10));
		r2 += .005*((float)(rand() % 10));
		r3 += .005*((float)(rand() % 10));
	#endif
	

	// move the center to the center of the widget
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);
	
	// (a,b) is the top left corner; (c,d) is the bottom right corner
	double a = - DrawableObject::getWidth()/2;
	double b =  DrawableObject::getHeight()/2;
	double c =  DrawableObject::getWidth()/2;
	double d = - DrawableObject::getHeight()/2;
	
	glColor3ub(150, 150, 150);
	glRectd(a,b,c,d);

	glColor3ub(100, 100, 100);
	#ifdef k_UNSELECTED_ITEMS_SWIM
		if ( usesImages() )
			glRectd(a+10,b-10,c-10-64-10,d+10);
		else
			glRectd(a+10,b-10,c-10,d+10);
	#else
		if ( usesImages() )
			glRectd((a+10)*cos(r1),(b-10)*sin(r1+r2),(c-10-64-10)*sin(r3 -r1),(d+10)*sin(r3));
		else
			glRectd((a+10)*cos(r1),(b-10)*sin(r1+r2),(c-10)*sin(r3 -r1),(d+10)*sin(r3));
	#endif
		
	// now, the amount of vertical space we have for display purposes
	// is the height - 2 * the margin, so divide that by the height of an entry
	// to get the number of entries we can display
	int visibleEntries = ( DrawableObject::getHeight() - 20 )/24;
	
	// this variable keeps track of the number of entries
	// that we've displayed, so that if there are fewer
	// entries than spaces for entries, we know to draw in
	// the blank spaces;
	int numEntriesDisplayed = 0;
	
	// the entry currently being displayed. We want the currently selected entry
	// to be in the middle UNLESS it is near the beginning or end of the list 
	int currEntry = currSelection - visibleEntries/2;
	if (currEntry < 0)
		currEntry = 0;
	else if (currEntry > getNumItems() - visibleEntries/2)
		currEntry = getNumItems() - visibleEntries/2;	
	
	// we were getting negative values that messed up the drawing, so 
	// if it's negative, add the number of total items to it.
	if (currEntry < 0) currEntry += getNumItems();

	
	// draw the little box that indicates how far along in
	// the list we are..
	//
	// the height of the viable region for this box is
	//		h = visibleEntries * 24 - 4
	//
	// we want to divide that box by the total number of entries
	// and draw a rectangle in the area corresponding to the
	// visible ones, so:
	//		top = (h / # of entries) * first visible entry
	//		bottom = (h / # of entries) * last visible entry

	int top = ((visibleEntries * 24 - 2) * (currEntry)) / getNumItems();
	int bot = ((visibleEntries * 24 - 2) * (currEntry+visibleEntries >= getNumItems() ? getNumItems() : currEntry + visibleEntries)) / getNumItems();

	// set the color to bluish gray
	glColor3ub(150, 150, 200);

	// draw the box on top of which the individual list entries are drawn
	if ( usesImages() )
		glRectd( c - 12 - 84 + 2, b - 12 - top, c - 12 - 84 +9, b - 12 - bot);
	else
		glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-10,b-34-numEntriesDisplayed*24);

	// keep displaying entries unless we display the last entry OR the
	// maximum number of entries
	while (numEntriesDisplayed < visibleEntries && currEntry < getNumItems()){
		if (currEntry >= 0 && currEntry < getNumItems()){
			if (currEntry == currSelection)
				glColor3ub(200, 100, 100);
			else
				glColor3ub(200, 200, 200);
				
			if ( usesImages() )
				glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-84,b-34-numEntriesDisplayed*24);
			else
				glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-10,b-34-numEntriesDisplayed*24);
			
			if (currEntry == currSelection)
				glColor3ub(200, 200, 0);
			else
				glColor3ub(0, 0, 200);
#ifdef k_UNSELECTED_ITEMS_SWIM
			Text::print((sme[currEntry]->getCaption()).data(), 
									(int)(a + 13 + DrawableObject::getCenterX() + 10*sin(r1)), 
									(int)(b - 32 - numEntriesDisplayed*24 + (win_height -DrawableObject::getCenterY() )+3*cos(r2)));
#else
			Text::print((sme[currEntry]->getCaption()).data(), 
									(int)(a + 13 + DrawableObject::getCenterX()), 
									(int)(b - 32 - numEntriesDisplayed*24 + (win_height -DrawableObject::getCenterY() )));
#endif
//			(sme[currEntry])
		}
		currEntry++;
		numEntriesDisplayed++;
	}
	
    glPopMatrix();	// restore openGL's previous settings

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

/*******************************************************************************/
/* Draws the widget in "selected" mode.                                        */
/*******************************************************************************/
void ScrollingMenuWidget::drawSelected ( void ){
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
		// if unselected items are supposed to swim around, increment
		// the angles we're using to calculate the modified position
		r1 += .005*((float)(rand() % 10));
		r2 += .005*((float)(rand() % 10));
		r3 += .005*((float)(rand() % 10));
	#endif
	

	// move the center to the center of the widget
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);
	
	// (a,b) is the top left corner; (c,d) is the bottom right corner
	double a = - DrawableObject::getWidth()/2;
	double b =  DrawableObject::getHeight()/2;
	double c =  DrawableObject::getWidth()/2;
	double d = - DrawableObject::getHeight()/2;
	
	glColor3ub(150, 150, 150);
	glRectd(a,b,c,d);

	glColor3ub(64, 64, 64);
//	#ifdef k_SELECTED_ITEMS_SWIM
		if ( usesImages() )
			glRectd(a+10,b-10,c-10-64-10,d+10);
		else
			glRectd(a+10,b-10,c-10,d+10);
//	#else
//		if ( usesImages() )
//			glRectd((a+10)*cos(r1),(b-10)*sin(r1+r2),(c-10-64-10)*sin(r3 -r1),(d+10)*sin(r3));
//		else
//			glRectd((a+10)*cos(r1),(b-10)*sin(r1+r2),(c-10)*sin(r3 -r1),(d+10)*sin(r3));
//	#endif
		
	// now, the amount of vertical space we have for display purposes
	// is the height - 2 * the margin, so divide that by the height of an entry
	// to get the number of entries we can display
	int visibleEntries = ( DrawableObject::getHeight() - 20 )/24;
	
	// this variable keeps track of the number of entries
	// that we've displayed, so that if there are fewer
	// entries than spaces for entries, we know to draw in
	// the blank spaces;
	int numEntriesDisplayed = 0;
	
	// the entry currently being displayed. We want the currently selected entry
	// to be in the middle UNLESS it is near the beginning or end of the list 
	int currEntry = currSelection - visibleEntries/2;
	if (currEntry < 0)
		currEntry = 0;
	else if (currEntry > getNumItems() - visibleEntries/2)
		currEntry = getNumItems() - visibleEntries/2;	
	
	// we were getting negative values that messed up the drawing, so 
	// if it's negative, add the number of total items to it.
	if (currEntry < 0) currEntry += getNumItems();

	
	// draw the little box that indicates how far along in
	// the list we are..
	//
	// the height of the viable region for this box is
	//		h = visibleEntries * 24 - 4
	//
	// we want to divide that box by the total number of entries
	// and draw a rectangle in the area corresponding to the
	// visible ones, so:
	//		top = (h / # of entries) * first visible entry
	//		bottom = (h / # of entries) * last visible entry

	int top = ((visibleEntries * 24 - 2) * (currEntry)) / getNumItems();
	int bot = ((visibleEntries * 24 - 2) * (currEntry+visibleEntries >= getNumItems() ? getNumItems() : currEntry + visibleEntries)) / getNumItems();

	// set the color to bluish gray
	glColor3ub(0, 0, 255);

	// draw the box on top of which the individual list entries are drawn
	if ( usesImages() )
		glRectd( c - 12 - 84 + 2, b - 12 - top, c - 12 - 84 +9, b - 12 - bot);
	else
		glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-10,b-34-numEntriesDisplayed*24);

	// keep displaying entries unless we display the last entry OR the
	// maximum number of entries
	while (numEntriesDisplayed < visibleEntries && currEntry < getNumItems()){
		if (currEntry >= 0 && currEntry < getNumItems()){
			if (currEntry == currSelection)
				glColor3ub(255, 0, 0);
			else
				glColor3ub(255, 255, 255);
				
			if ( usesImages() )
				glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-84,b-34-numEntriesDisplayed*24);
			else
				glRectd(a+12,b-12-numEntriesDisplayed*24,c-12-10,b-34-numEntriesDisplayed*24);
			
			if (currEntry == currSelection)
				glColor3ub(255, 255, 0);
			else
				glColor3ub(0, 0, 255);
#ifdef k_SELECTED_ITEMS_SWIM
			Text::print((sme[currEntry]->getCaption()).data(), 
									(int)(a + 13 + DrawableObject::getCenterX()) + 10*sin(r1), 
									(int)(b - 32 - numEntriesDisplayed*24 + (win_height -DrawableObject::getCenterY() ))+3*cos(r2));
#else
			Text::print((sme[currEntry]->getCaption()).data(), 
									(int)(a + 13 + DrawableObject::getCenterX()), 
									(int)(b - 32 - numEntriesDisplayed*24 + (win_height -DrawableObject::getCenterY() )));
#endif
			
		}
		currEntry++;
		numEntriesDisplayed++;
	}
	
    glPopMatrix();	// restore openGL's previous settings

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

// these are just for testing:
string ScrollingMenuWidget::getCaption (void ) { return sme[currSelection]->getCaption(); }
int ScrollingMenuWidget::getImageID (void ) { return sme[currSelection]->getImageID(); }



/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Constructs a ScrollingMenuWidget with a specified width, height,            */
/* and location. It also specifies the maximum number of items                 */
/* that the menu can contain.                                                  */
/*******************************************************************************/
ScrollingMenuWidget::ScrollingMenuWidget ( int width, int height, int centerX, int centerY, int wid ) :
MenuWidget (width, height, centerX, centerY, wid) {
	currSelection = -1;
	numItems = 0;
	widgetID = wid;
	r1 = r2 = r3 = 0;
}


/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

ScrollingMenuWidget::~ScrollingMenuWidget ( void ) {
	
}

