/*************  REVISION HISTORY  *********************






date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/02 23:47:10;  
author: graham;    
Fixed capitalization on some #includes. My system doesn't care, but UGCS does.



date: 2002/05/12 11:42:12;  
author: graham;    

Rewrote the graphics code. This should be the final version of the graphics code for the slider widget.



date: 2002/05/10 10:12:18;  
author: graham;    

Modifications to tweak graphics code.



date: 2002/05/10 09:44:09;  
author: graham;    

Slight tweaks to the graphics code.



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



date: 2002/03/21 05:27:28;  
author: graham;    

Added comments to the code.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/15 05:33:09;  
author: graham;    

This is a fully functional sliderwidget class.



date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/22 01:29:25;  
author: graham;    

I made a slight modification to the switch statement in receiveEvent so that the prettyprinter script i wrote would work correctly on this file.



date: 2002/02/21 23:18:02;  
author: graham;    

Added the event-handling code to the SliderWidget class. The only remaining code to add is the graphics-related code.



date: 2002/02/18 22:05:17;  
author: graham;    

I've added most of the code for the SliderWidget. The only thing i haven't added is the Event-handling code and the Drawing code.



date: 2002/02/18 21:53:32;  
author: graham;    

Added mutator methods to this class.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "SliderWidget.h"
#include "MenuWidget.h"
#include "drawableobject.h"




/*******************************************************************************/
/* Returns the current value shown on the slider.                              */
/*******************************************************************************/
int SliderWidget::getSliderValue( void ) {
	return value;
	
}

/*******************************************************************************/
/* Increases the value by one step.                                            */
/*******************************************************************************/
void SliderWidget::increaseValue( void ) {
	setSliderValue (getSliderValue() + 1);
}

/*******************************************************************************/
/* Decreases the value by one step.                                            */
/*******************************************************************************/
void SliderWidget::decreaseValue( void ) {
	setSliderValue (getSliderValue() - 1);
}

/*******************************************************************************/
/* Sets the value displayed on the slider to the given value                   */
/* if it is between the max and min values. Otherwise, it does                 */
/* nothing.                                                                    */
/*******************************************************************************/
void SliderWidget::setSliderValue( int d ) {
	if (d >= getMinValue() && d <= getMaxValue()){
		value = d;
	}
}

/*******************************************************************************/
/* Sliders call increment when the user hits rightarrow or uparrow,            */
/* and decrement when the user hits leftarrow or downarrow. These              */
/* are the only events this class of Widgets handles.                          */
/*******************************************************************************/
void SliderWidget::receiveEvent( Event * e ) {
	if (e->getEventClass() == INPUT_EVENT){
		if (e->getType() == arrowkey){
			switch (e->getValue()){
			
			/* if they hit uparrow or rightarrow, we want to increase the    */
			/* slidervalue                                                   */
			case ARROW_UP:
				increaseValue();
				break;
			
			case ARROW_RIGHT:
				increaseValue();
				break;
			
			/* if they hit downarrow or leftarrow, we want to decrease the   */
			/* slidervalue                                                   */
			case ARROW_DOWN:
				decreaseValue();
				break;
			
			case ARROW_LEFT:
				decreaseValue();
				break;
		}
	}
	
	/* all other events are ignored.                                           */
}
}

/*******************************************************************************/
/* sets the minimum value of the slider.                                       */
/*******************************************************************************/
void SliderWidget::setMinValue( int mv ) {
minValue = mv;
}

/*******************************************************************************/
/* Sets the maximum value of the slider.                                       */
/*******************************************************************************/
void SliderWidget::setMaxValue( int mv ) {
maxValue = mv;
}

/*******************************************************************************/
/* Returns the maximum value of the slider.                                    */
/*******************************************************************************/
int SliderWidget::getMaxValue( void ) {
return maxValue;
}

/*******************************************************************************/
/* Returns the minimum value of the slider.                                    */
/*******************************************************************************/
int SliderWidget::getMinValue( void ) {
return minValue;
}

/*******************************************************************************/
/* returns the value of the widget ID.                                         */
/*******************************************************************************/
int SliderWidget::getWidgetID ( void ){
	return widgetID;
}

/*******************************************************************************/
/* Draws the widget normally (ie, not selected)                                */
/*******************************************************************************/
void SliderWidget::draw ( void ) {
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

	// draw the endpoints of the slider
	glColor3ub(150, 150, 150);
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , -(float)(DrawableObject::getWidth()/2)*.97, DrawableObject::getHeight()/2  );
	glRectf(DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , (float)(DrawableObject::getWidth()/2)*.97, DrawableObject::getHeight()/2  );

	// calculate the width of the dots
	float dotwidth = (.93*((float)DrawableObject::getWidth())) / (2.0 * (float)(getMaxValue() - getMinValue()) + 1.0);
	float offset;
	
	// draw the dots
	for (int i = getMinValue(); i <= getMaxValue(); i++){
		float i2 = i - getMinValue();
		offset = -.93*((float)DrawableObject::getWidth()/2.0) + dotwidth*(0.0+i2*2.0);
		if (i == getSliderValue()){
			glColor3ub(50, 150, 50);
			glRectf(offset, -DrawableObject::getHeight()/4 , offset + dotwidth, DrawableObject::getHeight()/4 );
		} else {
			glColor3ub(50, 50, 150);
			glRectf(offset, -DrawableObject::getHeight()/4 , offset + dotwidth, DrawableObject::getHeight()/4 );
		}
	}
	
    glPopMatrix();	// restore openGL's previous settings

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();

}

/*******************************************************************************/
/* Draws the widget in "selected" mode.                                        */
/*******************************************************************************/
void SliderWidget::drawSelected ( void ){
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

	// draw the endpoints of the slider
	glColor3ub(150, 150, 150);
	glRectf(-DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , -(float)(DrawableObject::getWidth()/2)*.97, DrawableObject::getHeight()/2  );
	glRectf(DrawableObject::getWidth()/2, -DrawableObject::getHeight()/2 , (float)(DrawableObject::getWidth()/2)*.97, DrawableObject::getHeight()/2  );

	// calculate the width of the dots
	float dotwidth = (.93*((float)DrawableObject::getWidth())) / (2.0 * (float)(getMaxValue() - getMinValue()) + 1.0);
	float offset;

	// loop from the minimum value to the maximum value and draw the dots
	for (int i = getMinValue(); i <= getMaxValue(); i++){
		float i2 = i - getMinValue();
		offset = -.93*((float)DrawableObject::getWidth()/2.0) + dotwidth*(0.0+i2*2.0);
		if (i == getSliderValue()){
			glColor3ub(0, 255, 0);
			glRectf(offset, -DrawableObject::getHeight()/4 , offset + dotwidth, DrawableObject::getHeight()/4 );
		} else {
			glColor3ub(0, 0, 255);
			glRectf(offset, -DrawableObject::getHeight()/4 , offset + dotwidth, DrawableObject::getHeight()/4 );
		}
	}
	
    glPopMatrix();	// restore openGL's previous settings

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}




/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

/*******************************************************************************/
/* Creates a slider of a specified width, in a specified location,             */
/* with specified max and min values, and with a specified initial             */
/* value.                                                                      */
/*******************************************************************************/
SliderWidget::SliderWidget ( int width, int center_x, int center_y, int minValue, int maxValue, int initialValue, int wid ) :
MenuWidget (width, 40, center_x, center_y, wid) {
	setMinValue(minValue);
	setMaxValue(maxValue);
	setSliderValue(initialValue);
	widgetID = wid;
	r1 = r2 = r3 = 0;
}



/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

SliderWidget::~SliderWidget ( void ) {

}

