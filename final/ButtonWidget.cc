

// REVISION HISTORY

/******************************************************************************/
/* RCS file: /www/cvs/pacman/menusystem/ButtonWidget.cc,v                     */
/* Working file: ../ButtonWidget.cc                                           */
/* head: 1.7                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 7                                                         */
/* selected revisions: 7                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.7                                                               */
/*                                                                            */
/* DATE: 2002/03/16 21:28:19                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* Added a widgetID variable and accessor methods to each MenuWidget so       */
/* that MenuPane could keep track of them.                                    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.6                                                               */
/*                                                                            */
/* DATE: 2002/03/14 20:38:00                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* The ButtonWidget code here is completely tested, except that the           */
/* graphics stuff isn't done yet. The Event classes are test event classes    */
/* that construct inputevents out of alphanumeric keypresses for the          */
/* purpose of testing the widgets.                                            */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.5                                                               */
/*                                                                            */
/* DATE: 2002/02/22 01:41:43                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* The code is identical to the previous revision, but has been run through   */
/* a prettyprinter to clean it up.                                            */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.4                                                               */
/*                                                                            */
/* DATE: 2002/02/20 22:31:14                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* More methods added to the ButtonWidget class. Also, I'm no longer          */
/* overriding DrawableObject's draw() methods.                                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/02/20 11:23:23                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* More slight modifications to these Widget classes..                        */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/02/19 00:39:36                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* Slight modificataions to the code for the methods of ButtonWidget.         */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/02/19 00:33:45                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* Modifications to the RadioWidget class. Also, I missed the                 */
/* ButtonWidget.cc file earlier, so i'm adding it now.                        */
/*                                                                            */
/******************************************************************************/



// END REVISION HISTORY




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "ButtonWidget.h"
#include "MenuWidget.h"
#include "DrawableObject.h"
#include "enums.h"



/*******************************************************************************/
/* Events are handed to this function. Buttons accept only return/enter        */
/* events. Everything else is ignored.                                         */
/*******************************************************************************/
void ButtonWidget::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT && (EventTypeID)(e->getType()) == enterkey){
		toggleClick();
	}
}

/*******************************************************************************/
/* returns the value of the private variable clicked.                        */
/*******************************************************************************/
bool ButtonWidget::isClicked( void ) {
	return clicked;
}

/*******************************************************************************/
/* returns the text label on the button.                                       */
/*******************************************************************************/
string ButtonWidget::getText( void ) {
	return label;
}

void ButtonWidget::getText( unsigned char * c){
	for (unsigned int i = 0; i < 255 && i < label.length(); i++){
		c[i] = label[i];
	}
	if (label.length() < 256)
		c[255] = '\0';
	else
		c[label.length()] = '\0';
}


/*******************************************************************************/
/* Changes the label of the button to newLabel.                                */
/*******************************************************************************/
void ButtonWidget::setText( string newLabel ) {
	label = newLabel;
}

/*******************************************************************************/
/* Sets clicked to true.                                                     */
/*******************************************************************************/
void ButtonWidget::click( void ) {
	clicked = true;
}

/*******************************************************************************/
/* Sets the click-status of the button to the value of the boolean             */
/* argument.                                                                   */
/*******************************************************************************/
void ButtonWidget::setClick( bool theClick ) {
	clicked = theClick;
}

/*******************************************************************************/
/* Toggles the click-status of the button.                                     */
/*******************************************************************************/
void ButtonWidget::toggleClick( void ) {
	clicked = !clicked;
}

/*******************************************************************************/
/* Returns the widget identification number.                                   */
/*******************************************************************************/
int ButtonWidget::getWidgetID( void ) {
	return widgetID;
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void ButtonWidget::draw ( void ) {
	
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
	
	// set the color for the rectangle depending on 
	// whether or not the button is clicked.
	if (isClicked())
		glColor3ub(50, 50, 152);
	else
		glColor3ub(152, 152, 50);

	// move the center to the center of the button
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	// draw the button's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// set the color for the text and move slightly forward
	glColor3ub(255, 0, 0);
	glTranslatef(0, 0, .2);
	
	// calculate the length of the text string so we can
	// center it on the button
	int textwidth = Text::getStringWidth(label.data());
	
	// draw the text centered.
	#ifdef k_UNSELECTED_ITEMS_SWIM
	Text::print(label.data(), (DrawableObject::getCenterX()-textwidth/2)+10*sin(r1), (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2)+10*cos(r3));
	#else
	Text::print(label.data(), (DrawableObject::getCenterX()-textwidth/2), (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2));

	#endif
	
    glPopMatrix();	// restore openGL's previous settings

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

/*******************************************************************************/
/* Draws the widget in "selected" mode.                                        */
/*******************************************************************************/
void ButtonWidget::drawSelected ( void ){
	
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
	
	// set the color for the rectangle depending on 
	// whether or not the button is clicked.
	if (isClicked())
		glColor3ub(0, 0, 252);
	else
		glColor3ub(252, 252, 0);

	// move the center to the center of the button
	glTranslatef(DrawableObject::getCenterX(), win_height - DrawableObject::getCenterY(), 0);

	// draw the button's rectangle
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , DrawableObject::getWidth()/2, DrawableObject::getHeight()/2  );
	
	// set the color for the text and move slightly forward
	glColor3ub(255, 0, 0);
	glTranslatef(0, 0, .2);
	
	// calculate the length of the text string so we can
	// center it on the button
	int textwidth = Text::getStringWidth(label.data());
	
	// draw the text centered.
	#ifdef k_SELECTED_ITEMS_SWIM
	Text::print(label.data(), (DrawableObject::getCenterX()-textwidth/2)+10*sin(r1), (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2)+10*cos(r3));
	#else
	Text::print(label.data(), (DrawableObject::getCenterX()-textwidth/2), (win_height - DrawableObject::getCenterY()) - ((DrawableObject::getHeight()-18)/2));

	#endif
	
	// restore openGL's previous settings
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();

}



/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a button with the specified location and dimensions                 */
/* with the specified text as its label.                                       */
/*******************************************************************************/
ButtonWidget::ButtonWidget ( int width, int height, int centerX, int centerY, string text, int wid ): MenuWidget (width, height, centerX, centerY, wid) {
	setText(text);
	setClick(false);
	widgetID = wid;
	
	r1 = 0;
	r2 = 0;
	r3 = 0;
}



/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

ButtonWidget::~ButtonWidget ( void ) {
	
}

