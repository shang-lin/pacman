
using namespace std;

// REVISION HISTORY

/******************************************************************************/
/* RCS file: /www/cvs/pacman/menusystem/ButtonWidget.h,v                      */
/* Working file: ../ButtonWidget.h                                            */
/* head: 1.6                                                                  */
/* branch:                                                                    */
/* locks: strict                                                              */
/* access list:                                                               */
/* symbolic names:                                                            */
/* keyword substitution: kv                                                   */
/* total revisions: 6                                                         */
/* selected revisions: 6                                                      */
/* description:                                                               */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.6                                                               */
/*                                                                            */
/* DATE: 2002/03/16 21:28:19                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* Added a widgetID variable and accessor methods to each MenuWidget so       */
/* that MenuPane could keep track of them.                                    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.5                                                               */
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
/* REVISION 1.4                                                               */
/*                                                                            */
/* DATE: 2002/02/22 20:59:22                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* Added an image ID for the button when it is both selected AND clicked.     */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.3                                                               */
/*                                                                            */
/* DATE: 2002/02/20 22:31:14                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* More methods added to the ButtonWidget class. Also, I'm no longer          */
/* overriding DrawableObject's draw() methods.                                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.2                                                               */
/*                                                                            */
/* DATE: 2002/02/18 21:25:46                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* I left out a #include in the last commit..                                 */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* REVISION 1.1                                                               */
/*                                                                            */
/* DATE: 2002/02/18 21:22:22                                                  */
/* CHANGES MADE BY: Clara Graham                                              */
/*                                                                            */
/* These are updated header files for the menusystem, as generated by the     */
/* online documentation.                                                      */
/*                                                                            */
/******************************************************************************/



// END REVISION HISTORY







#ifndef _BUTTONWIDGET_H_
#define _BUTTONWIDGET_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "MenuWidget.h"
//#include "allmenu.h"
#include <string>
#include "DrawableObject.h"
#include <math.h>


// Description:
//
// This widget is simply a button, such as an OK or Cancel button. 
// 

class ButtonWidget : public MenuWidget{
		// Data Members

	private:
		// isClicked is initialized to false. When the button 
		// is 'clicked' by pressing enter/return when the button is selected 
		// in the pane, isClicked is set to true.
 
		bool clicked;

		// The label for the button. 
		string label;

		// The id for the image of this button when it is neither selected 
		// nor clicked. 
		int normal_image_ID;

		// The id for the image of this button when it is selected. 
		int selected_image_ID;

		// The id for the image of this button when it is clicked. 
		int clicked_image_ID;

		// The id of the image for when it is both selected and clicked. 
		// 
		int selected_clicked_image_id;
		
		// the widget identification number
		int widgetID;

		// these are angles used in the draw() functions for positioning
		float r1;
		float r2;
		float r3;


	public:


		// Methods

	private:


	public:
		// Draws the widget in "selected" mode and "regular" mode, repectively
		void drawSelected( void );
		void draw( void );
		
		
		// Events are handed to this function. Buttons accept only return/enter 
		// events. Everything else is ignored. 
		void receiveEvent( Event * );

		// returns the value of the private variable isClicked. 
		bool isClicked( void );

		// Changes the label of the button to newLabel. 
		void setText( string );

		// Sets isClicked to true. 
		void click( void );

		// returns the label on the button. 
		string getText( void );
		void getText( unsigned char * );

		// Sets the click-status of the button to the value of the boolean 
		// argument. 
		void setClick( bool );

		// Toggles the click-status of the button. 
		void toggleClick( void );
		
		// returns the widget identification number
		int getWidgetID ( void );
		
		// returns true because the user can select this kind of menuwidget
		bool isSelectable (void) { return true; }



		// Constructor(s)

		// Creates a button with the specified location and dimensions 
		// with the specified text as its label. The last argument is the
		// widget identification number
		ButtonWidget ( int, int, int, int, string, int );



		// Destructor

		~ButtonWidget ( void );

};

#endif
