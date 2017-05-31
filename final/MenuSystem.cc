/*************  REVISION HISTORY  *********************






date: 2002/06/07 01:03:31;  
author: graham;    
added separate client and server menu system classes









date: 2002/06/06 10:23:20;  
author: graham;    
Menusystem handles the args to console client.



date: 2002/06/05 22:05:29;  
author: graham;    
Added getStringWidth to the final version of text.cpp.
MenuSystem now draws the menus for console client, but doesn't do anything with them. the delete key doesn't work properly in text input widgets.



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



date: 2002/06/04 04:04:09;  
author: graham;    
Menusystem works



date: 2002/06/04 03:40:37;  
author: graham;    
Menusystem draws but doesn't respond to keypresses..



date: 2002/06/04 03:04:29;  
author: graham;    
MenuSystem compiles. I don't know if it works yet, but it compiles.



date: 2002/06/04 02:21:09;  
author: graham;    
Trying to get the menusystem test program working.



date: 2002/05/09 12:08:10;  
author: graham;    

Added #include <GL/glut.h> so that the class could call openGL routines.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/02/22 01:41:43;  
author: graham;    

The code is identical to the previous revision, but has been run through a prettyprinter to clean it up.



date: 2002/02/20 11:18:40;  
author: graham;    

Made some changes to the constructor. In particular, i've commented out some of the incomplete setup code. Once the display stuff is working, i'll test out the various components, but i don't want to write out too much of the code in case some sort of unforseen problem arises.



date: 2002/02/19 07:36:31;  
author: graham;    

More menusystem code; some event-handling code in MenuPane and MenuSystem.



date: 2002/02/19 02:47:09;  
author: graham;    

Added a setText() method to LabelWidget. Also added more menu setup code to MenuSystem.



date: 2002/02/18 23:59:15;  
author: graham;    

Wrote some of the menusystem setup code.



date: 2002/02/18 21:21:23;  
author: graham;  

I'm removing some old header files and adding some skeletal .cc files. i'm going to go back and add the updated header files shortly.


***********  END REVISION HISTORY **********/




/*******************************************************************************/
/* The includes for the superclasses are automatically listed.                 */
/* You need to specify any others                                              */
/*******************************************************************************/
#include "MenuSystem.h"
#include "ButtonWidget.h"
#include "LabelWidget.h"
#include "ScrollingMenuWidget.h"
#include "SliderWidget.h"
#include "RadioWidget.h"
#include "TextInputWidget.h"
#include "enums.h"
#include "Event.h"


#define _CLIENT_MENU_MODE_

/*******************************************************************************/
/* Passes events to the current menupane.                                      */
/*******************************************************************************/
void MenuSystem::receiveEvent( InputEvent * e ) {
	int et = e->getType();
	switch ( et ) {
		
		case escapekey:
			/* go back one menu. I may set up a linkedlist type tree that    */
			/* will handle this automatically, but for now:                  */
	/*		if ( currentMenu == optionsMenu || currentMenu == highScoresMenu || currentMenu == singlePlayerMenu || currentMenu == multiPlayerMenu) {
				currentMenu = mainMenu;
			} else if (currentMenu == joinGame || currentMenu == createGame || currentMenu == viewWaitingRoom) {
				currentMenu = multiPlayerMenu;
			}
			*/
			break;
		
		default:
		/* otherwise, hand the event to the current menu                      */
		currentMenu->receiveEvent( e );
		break;
	}

updateMenuDisplay ();

}



/*******************************************************************************/
/* packages the keypress as an input event and sends it to the menus.    */
/* these prototypes are the same as the GLUT prototypes for special     */
/* regular keypresses.    */
/*******************************************************************************/
void MenuSystem::specialKey (int key, int x, int y){
	//packages the special keypress (ie, tab, return, esc, etc.) as an
	// input event and forwards it to receiveEvent
	InputEvent * ie;

	switch (key){
		case GLUT_KEY_DOWN:
			ie = new InputEvent(key, 's');
			break;

		case GLUT_KEY_UP:
			ie = new InputEvent(key, 'w');
			break;

		case GLUT_KEY_LEFT:
			ie = new InputEvent(key, 'a');
			break;

		case GLUT_KEY_RIGHT:
			ie = new InputEvent(key, 'd');
			break;
	}
	receiveEvent(ie);
}

void MenuSystem::regularKey (char key, int x, int y){
	//packages the special keypress (ie, tab, return, esc, etc.) as an
	// input event and forwards it to receiveEvent
	InputEvent * ie;

	switch (key){
		// check if enter/return has been pressed
		case '\r':
		case '\n':
			ie = new InputEvent(key, '4');
			break;

		// check if the tab key has been pressed
		case '\t':
			ie = new InputEvent(key, '2');
			break;

		// check if the forward delete or backspace key has been pressed
		case 127:
		case 8:
			ie = new InputEvent(key, '7');
			break;

		// check if the escape key has been pressed
		case 27:
			ie = new InputEvent(key, '6');
			break;

		default:
			ie = new InputEvent(key, '9');
			break;
	}
	receiveEvent(ie);
}

/* 
	 returns the state of the button widget with ID number
	 135.
	 */
bool MenuSystem::terminated ( void ) {
	// the start button has ID # 135

	if (mainMenu == NULL) return false;
	
	ButtonWidget * bw = (ButtonWidget *)(mainMenu->getWidget (135));
	if (bw == NULL) return false;
	return (bw->isClicked());
}




/*******************************************************************************/
/* draws the current menu pane */
/*******************************************************************************/
void MenuSystem::draw ( void ){
	currentMenu->draw();	
}

/*******************************************************************************/
/* Constructor(s)                                                              */
/*******************************************************************************/

MenuSystem::MenuSystem ( void ) {
	// set up the main menu                                               
	mainMenu = new MenuPane(250, 250, 500, 500, 0);

	currentMenu = mainMenu;
}



/*******************************************************************************/
/* Destructor                                                                  */
/*******************************************************************************/

MenuSystem::~MenuSystem ( void ) {
	delete mainMenu;
}

