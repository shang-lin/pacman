/*************  REVISION HISTORY  *********************



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/06/03 00:04:53;  
author: graham;    
Added math functions to menusystem files.



date: 2002/06/02 23:41:38;  
author: graham;    
Added "using namespace std" to everything



date: 2002/05/09 12:08:10;  
author: graham;    

Added #include <GL/glut.h> so that the class could call openGL routines.



date: 2002/05/08 07:42:03;  
author: graham;    

MenuPane is working! There was a bug in the selectNext() method causing the tabkey not to work. I still need to make some changes to the selectNext() and selectPrevious() methods; if you're at the end of the linked list of widgets, it just moves to the first or last widget without checking that the widget is selectable.



date: 2002/05/08 02:59:18;  
author: graham;    

Still trying to get menupane working. it's not compiling right.



date: 2002/05/07 02:18:22;  
author: graham;    

Instead of a fixed-size array of MenuWidget pointers, i'm using a linked list.



date: 2002/03/21 02:23:01;  
author: graham;    




date: 2002/03/16 21:28:19;  
author: graham;    

Added a widgetID variable and accessor methods to each MenuWidget so that MenuPane could keep track of them.



date: 2002/03/15 12:10:50;  
author: graham;    

This MenuPane code doesn't quite compile yet.



date: 2002/02/19 07:36:31;  
author: graham;    

More menusystem code; some event-handling code in MenuPane and MenuSystem.



date: 2002/02/18 21:25:46;  
author: graham;    

I left out a #include in the last commit..



date: 2002/02/18 21:22:22;  
author: graham;  

These are updated header files for the menusystem, as generated by the online documentation.


***********  END REVISION HISTORY **********/


using namespace std;


#ifndef _MENUPANE_H_
#define _MENUPANE_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
//#include "allmenu.h"
#include "drawableobject.h"
#include "enums.h"
#include "Event.h"
#include "MenuWidget.h"
#include "text.h"
#include <math.h>
//#include "ScrollingMenuWidget.h"
//#include "RadioWidget.h"
//#include "LabelWidget.h"
//#include "TextInputWidget.h"
//#include "SliderWidget.h"
//#include "ButtonWidget.h"
//#include "MenuPane.h"
#include <string>

// Description:
//
// A MenuPane is an object representing a single screen in the 
// menusystem. MenuWidgets can be inserted into these panes. 
// Every MenuPane must contain a button that terminates the pane 
// and returns the values of every MenuWidget in the pane.

 
// //
// 

 //
// The user can use tab or other keys to navigate among the widgets 
// in a pane. 

class MenuPane : private DrawableObject{
		// Data Members
		
		struct WidgetNode {
			MenuWidget * w;
			struct WidgetNode * next;
			struct WidgetNode * prev;
		};
		typedef struct WidgetNode WidgetNode;

	private:
		// a pointer to the head of a doubly linked list of widgetnodes
		WidgetNode * head;

		// a pointer to the tail of a doubly linked list of widgetnodes
		WidgetNode * tail;

		// a pointer to the current widget in the doubly linked list of widgetnodes
		WidgetNode * curr;
		
		// the id of the image for the background
		int bgImageID;


	public:


		// Methods

	private:
		// This method causes the next selectable widget in the MenuPane 
		// to become selected. 
		void selectNextWidget( void );

		// Causes the previous selectable widget to become the selected 
		// widget. 
		void selectPreviousWidget( void );



	public:
		// This method either accepts/handles events or passe them to 
		// the current menuwidget. MenuPanes accept tab events 
		void receiveEvent( Event * );

		// This method adds the given pointer to the list of widgets 
		// in the menupane. 
		void addWidget( MenuWidget * );

		// This method draws the MenuPane and all of its widgets. 
		void draw( void );
		
		// This method returns the ID of the current widget
		int getID( void );

		// This method returns a pointer to the MenuWidget with the provided 
		// ID, or a null pointer if the MenuPane isn't aware of any such 
		// widget. 
		MenuWidget * getWidget( int );



		// Constructor(s)

		MenuPane (int, int, int, int, int);

		// Destructor

		~MenuPane ( void );

};

#endif
