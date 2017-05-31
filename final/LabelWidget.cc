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



date: 2002/05/12 09:26:51;  
author: graham;    

Modified the graphics code. This should be the finished version.



date: 2002/05/10 10:12:18;  
author: graham;    

Modifications to tweak graphics code.



date: 2002/05/10 09:44:09;  
author: graham;    

Slight tweaks to the graphics code.



date: 2002/05/10 01:41:13;  
author: graham;    

Added more graphics code.



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



date: 2002/03/14 20:52:40;  
author: graham;    

Completely tested LabelWidget code, except for drawing. labeltest.cc is testing code.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/20 11:23:23;  
author: graham;    

More slight modifications to these Widget classes..



date: 2002/02/19 02:47:09;  
author: graham;    

Added a setText() method to LabelWidget. Also added more menu setup code to MenuSystem.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/










/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "LabelWidget.h"
#include "MenuWidget.h"
#include "drawableobject.h"
#include <string>


/*******************************************************************************/
/* returns the value of the widget ID.                                         */
/*******************************************************************************/
int LabelWidget::getWidgetID ( void ){
	return widgetID;
}



/*******************************************************************************/
/* Labels do not handle events, so any events are ignored.                     */
/*******************************************************************************/
void LabelWidget::receiveEvent( Event * e ) {
	
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void LabelWidget::draw ( void ) {
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
	
	// move the center to the center of the label
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	// set the color for the text and move slightly forward
	glColor3ub(255, 255, 255);
	glTranslatef(0, 0, .2);
	
	// calculate the length of the text string so we can
	// center it on the button
	int textwidth = Text::getStringWidth(text.data());
	
	// draw the text centered.
	#ifdef k_UNSELECTED_ITEMS_SWIM
	Text::print(text.data(), (int)((DrawableObject::getCenterX()-textwidth/2)+10*sin(r1)), (int)((win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2)+10*cos(r3)));
	#else
	Text::print(text.data(), (DrawableObject::getCenterX()-textwidth/2), (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2));

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
void LabelWidget::drawSelected ( void ){
	// nothing to do, but let's call draw() just in case
	// we end up here somehow so the label doesn't disappear
	draw(); 
}


/*******************************************************************************/
/* Sets the text of this label to the string s.                                */
/*******************************************************************************/
void LabelWidget::setText( string s ) {
	text = s;
}

// Sets the text of this label to a string representing the value of the
// integer argument. 
void LabelWidget::setText( int i ){
	int temp = i;
	string newchar;
	text = '\0';
	while (temp != 0){
//		char c = '0' + (temp % 10);
		newchar = (char)('0' + (temp % 10));
		text = newchar + text;
		temp /= 10;
	}
}



/*******************************************************************************/
/* Returns the text of this label.                                             */
/*******************************************************************************/
string LabelWidget::getText( void ) {
	return text;
}


/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a label with the specified position and dimensions                  */
/* and sets its label to text.                                                 */
/*******************************************************************************/
LabelWidget::LabelWidget ( int width, int height, int centerX, int centerY, string text, int wid ) 
: MenuWidget (width, height, centerX, centerY, wid)
{
	setText(text);
	widgetID = wid;
	r1 = r2 = r3 = 0;
}



