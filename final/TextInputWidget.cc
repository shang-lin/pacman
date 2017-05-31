/*************  REVISION HISTORY  *********************



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/04 02:00:15;  
author: graham;    
Fixed a couple of lines in TextINputWidget and ScrollingMenuWidget that were generating warnings (the compiler wanted me to explicityly cast doubles to ints). Created a test program for the menusystem/graphics.



date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/05/12 11:39:46;  
author: graham;    

I was comparing variables of different types (signed vs. unsigned int) so i changed one of them so they'd match.



date: 2002/05/12 10:08:06;  
author: graham;    

Stripped down the TextInputWidget class. I was having some trouble getting strings to work right. I suspect it's a problem with files on my machine, since it worked fine when i tested it before. This way, the drawing is also more straightforward. Instead of being able to move around in the text with arrowkeys, you add to or delete from the end of the string. This way, i can easily use a character array to contain the string (since i don't have the problem of addinf characters in the middle of the string) and i don't have to draw a cursor.



date: 2002/05/12 09:26:51;  
author: graham;    

Modified the graphics code. This should be the finished version.



date: 2002/05/10 01:41:13;  
author: graham;    

Added more graphics code.



date: 2002/05/09 12:06:48;  
author: graham;    

Added rudimentary graphics code.



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



date: 2002/03/15 04:33:49;  
author: graham;    

Deleting characters from the end of the string and moving to the end/beginning via the down/up arrow keys now works correctly. When i did bounds-checking in the setPosition() function, i had accidentally used greater-than and less-than instead of greater-than-or-equal-to and less-than-or-equal-to.



date: 2002/03/15 04:31:27;  
author: graham;    

modified textinputwidget classes, and a textinputtest program. the text input widget isn't quite perfect yet; there are still some issues with it not retaining the correct cursor position when characters are deleted from the end of the string, as well as the up and down arrows not moving the cursor to the beginning and end of the input text.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/22 00:27:45;  
author: graham;    

Fixed some parenthesis-matching problems in the receiveEvent() method.



date: 2002/02/22 00:18:36;  
author: graham;    

Since string maintains its own length, I eliminated numChars and the setNumChars() method. getNumChars() now just calls the length() function on the text.



date: 2002/02/22 00:11:50;  
author: graham;    

Finished the code for textinputwidget, except the drawing code. I added a deleteChar function to allow users to delete text that they had entered. I also added numChars and maxChars variables to keep track of the maximum and current number of characters in the input box. There are also accessor and mutator functions for those two variables.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "TextInputWidget.h"
#include "MenuWidget.h"
#include "drawableobject.h"




/*******************************************************************************/
/* Copies the string in the Widget to the string pointed to by                 */
/* s.                                                                          */
/*******************************************************************************/
string TextInputWidget::getValue( void ) {
	string temp = text;
	return temp;
}


/*******************************************************************************/
/* Returns the widget identification number.                                   */
/*******************************************************************************/
int TextInputWidget::getWidgetID ( void ) {
	return widgetID;
}


/*******************************************************************************/
/* Copies the string to which s points into the string representing            */
/* the text contained in the text box.                                         */
/*******************************************************************************/
void TextInputWidget::setValue( string s ) {
	for (unsigned int i = 0; i < s.length() && i < (unsigned int)maxChars; i++)
		text[i] = s[i];
	for (unsigned int i = s.length(); i <= (unsigned int)maxChars; i++)
		text[i] = '\0';
		
	position = s.length();
}

/*******************************************************************************/
/* Inserts the character into the text input box at the current                */
/* position.                                                                   */
/*******************************************************************************/
void TextInputWidget::insertChar( char c ) {
	if (getNumChars() != getMaxChars()){
		text [position++] = c;
	}
}

/*
	this widget accepts alphanumeric keypress events and
	appends the character to the end of the string. it
	also accepts forward delete and backspace
	 */
void TextInputWidget::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT){
		switch (e->getType()){
			
			/* if they hit delete, call deleteChar(cursor position - 1) to   */
			/* delete the previous character                                 */
			case deletekey:
				deleteChar ();
				break;
			
			/* if they hit forwarddelete, call deleteChar(cursor position)   */
			/* to delete the next character                                  */
			case forwarddeletekey:
				deleteChar ();
				break;
			
			/* if they entered an alphanumeric value, add it to the text box */
			/* at the current position                                       */
			case alphanumeric:
				insertChar (e->getValue());
				break;
			
			
			
		}
	}
	/* all other events are ignored.                                           */
}

/*******************************************************************************/
/* Sets the maximum number of characters the user can type into                */
/* this widget.                                                                */
/*******************************************************************************/
void TextInputWidget::setMaxChars( int mc ) {
	maxChars = mc;
}

/*******************************************************************************/
/* Returns the maximum number of characters that the user is                   */
/* allowed to type into the text box.                                          */
/*******************************************************************************/
int TextInputWidget::getMaxChars( void ) {
	return maxChars;
}


/*******************************************************************************/
/* Returns the current number of characters.                                   */
/*******************************************************************************/
int TextInputWidget::getNumChars( void ) {
	return position;
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void TextInputWidget::draw ( void ) {
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
	
	// set the color for the rectangle
	glColor3ub(60, 60, 60);

	// move the center to the center of the input box
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	// draw the input box's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// set the color for the text and move slightly forward
	glColor3ub(255, 255, 255);
	glTranslatef(0, 0, .2);
	
	
	// draw the text left-aligned.
	#ifdef k_UNSELECTED_ITEMS_SWIM
	Text::print(text, (int)((DrawableObject::getCenterX()-DrawableObject::getWidth()/2) + 8+10*sin(r1)), (int)((win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2)+10*cos(r3)));
	#else
	Text::print(text, (DrawableObject::getCenterX()-DrawableObject::getWidth()/2) + 8, (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2));

	#endif
	
	// restore openGL's previous settings
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

/*******************************************************************************/
/* Draws the widget in "selected" mode.                                        */
/*******************************************************************************/
void TextInputWidget::drawSelected ( void ){
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
	
	// set the color for the rectangle
	glColor3ub(150, 150, 150);

	// move the center to the center of the input box
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	// draw the input box's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// set the color for the text and move slightly forward
	glColor3ub(255, 255, 255);
	glTranslatef(0, 0, .2);
	
	
	// draw the text left-aligned.
	#ifdef k_SELECTED_ITEMS_SWIM
	Text::print(text, (int)((DrawableObject::getCenterX()-DrawableObject::getWidth()/2) + 8+10*sin(r1)), (int)((win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2)+10*cos(r3)));
	#else
	Text::print(text, (DrawableObject::getCenterX()-DrawableObject::getWidth()/2) + 8, (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2));

	#endif
	
	// restore openGL's previous settings
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}


/*******************************************************************************/
/* Deletes the character at the specified location.                            */
/*******************************************************************************/
void TextInputWidget::deleteChar( void ) {
	if (position > 0){
		position--;
		text[position] = '\0';
	}
	
}



/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a text input box of a specified width at a specified                */
/* location, with a specified character limit.                                 */
/*******************************************************************************/
TextInputWidget::TextInputWidget ( int width, int centerX, int centerY, int maxChars, int wid ) :
MenuWidget (width, 30, centerX, centerY, wid) {
	text = new char[maxChars+1];
	for (int i = 0; i <= maxChars; i++)
		text[i] = '\0';
	setMaxChars(maxChars);
	widgetID = wid;
	position = 0;
	
	r1 = r2 = r3 = 0;
}

/*******************************************************************************/
/* Creates a text input box of a specified width at a specified                */
/* location, with a specified character limit, and with specified              */
/* default text.                                                               */
/*******************************************************************************/
TextInputWidget::TextInputWidget ( int width, int centerX, int centerY, int maxChars, string defaultText, int wid ) :
MenuWidget (width, 30, centerX, centerY, wid) {
	text = new char[maxChars+1];
	for (unsigned int i = 0; i < defaultText.length() && i < (unsigned int)maxChars; i++)
		text[i] = defaultText[i];
	for (unsigned int i = defaultText.length(); i <= (unsigned int)maxChars; i++)
		text[i] = '\0';
		
	setMaxChars(maxChars);
	widgetID = wid;
	position = defaultText.length();
	
	r1 = r2 = r3 = 0;
}



/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

TextInputWidget::~TextInputWidget ( void ) {
	delete (text);
}

