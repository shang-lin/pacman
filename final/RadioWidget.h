/*************  REVISION HISTORY  *********************



date: 2002/06/05 01:12:17;  
author: graham;    
Copied menusystem files into final directory



date: 2002/06/04 21:37:57;  
author: nowell;  
Added directory for our final build





date: 2002/06/05 00:30:46;  
author: graham;    
Tweaked drawing methods.



date: 2002/06/03 00:55:13;  
author: graham;    
Changed the menusystem classes to use the real drawableobject.h instead of the one i created for testing. also changed <string.h> to <string> in image.h.



date: 2002/06/03 00:04:53;  
author: graham;    
Added math functions to menusystem files.



date: 2002/06/02 23:41:38;  
author: graham;    
Added "using namespace std" to everything



date: 2002/05/08 07:38:20;  
author: graham;    

Made slight modifications to the widget classes to make MenuPane work.



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



date: 2002/02/21 11:05:56;  
author: graham;    

All the code for RadioWidget except draw- and event-related code. Some minimal code for ScrollingMenuWidget.



date: 2002/02/18 21:25:46;  
author: graham;    

I left out a #include in the last commit..



date: 2002/02/18 21:22:22;  
author: graham;  

These are updated header files for the menusystem, as generated by the online documentation.


***********  END REVISION HISTORY **********/


using namespace std;


#ifndef _RADIOWIDGET_H_
#define _RADIOWIDGET_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "MenuWidget.h"
#include "drawableobject.h"
#include "Event.h"
#include <string>
#include <math.h>




// Description:
//
// This widget is used for radio buttons. You add strings of 
// text to this object, and when this object is drawn, it draws 
// a radio button for each option. This object accepts up/down/right/left 
// arrow events, and return/enterkey events. up/left moves to 
// the previous item; down/right moves to the next item; return/enter 
// selects the currently hilighted radio button. 

class RadioWidget : public MenuWidget{

		// Description:
		//
		// This class encapsulates the entries in the radio button. each 
		// entry has an integer ID and a caption
		
		class RadioEntry {
			private:
				string caption;
				int ID;
			
			public:
				
				string getLabel (void ) { return caption; }
				int getID (void ) { return ID; }
				
				RadioEntry (string s, int k){
					caption = s;
					ID = k;
				}
		};

		// Data Members

	private:
		
		// The list of options in the radio button. The size of the array 
		// is determined in the constructor. 
		RadioEntry * itemList [10];

		// The currently checked option in the widget. This int is the 
		// item's index in the array, NOT its ID. 
		int checkedOption;

		// The currently hilited option in the widget. This int is the 
		// item's index in the array, NOT its ID. 
		int hilitedOption;

		// The number of items defined in the itemList. 
		int numItems;

		// The maximum number of elements in this Radio Widget. 
		int maxItems;

		// This is an integer that identifies the widget
		int widgetID;
		
		// angles used for drawing
		double r1, r2, r3;
		

	public:


		// Methods

	private:


	public:
		// Returns the widget identification number
		int getWidgetID ( void );
		
		// Hilites the next item in the menu. 
		void hiliteNextItem( void );

		// Hilites the previous item in the menu. 
		void hilitePreviousItem( void );

		// This class accepts return/enter events (checks the currently-hilited 
		// button), up/left-arrow events (hilites previous item), down/right-arrow 
		// events (hilites next item). 
		void receiveEvent( Event * );

		// Returns the ID number of the currently checked entry. 
		int getValue( void );

		// Returns the ID number of the currently hilited entry. 
		int getHilitedValue( void );

		// Checks the entry with the given ID, or does nothing if no 
		// such entry exists. 
		void setValue( int );

		// Adds an entry with the given caption and ID if no entry with 
		// that ID exists, and returns true. Returns false if an entry 
		// with that ID already exists. 
		bool addEntry( string, int );

		// Adds an entry with the given caption and ID if no entry with 
		// that ID exists, and returns true. Returns false if an entry 
		// with that ID already exists. If bool is true, it checks this 
		// new entry, otherwise, the entry is unchecked. 
		bool addEntry( string, int, bool );

		// Returns the maximum number of items in the RadioWidget. 
		int getMaxItems( void );

		// Returns the number of items in the RadioWidget. 
		int getNumItems( void );

		// Returns true iff an item with id_query is not already in the 
		// list of items. Otherwise, returns false. 
		bool isValid( int );
		
		// returns true because the user can select this kind of menuwidget
		bool isSelectable (void) { return true; }

		// Draws the widget in "selected" mode and "regular" mode, repectively
		void drawSelected( void );
		void draw( void );


		// Constructor(s)

		// Creates a RadioWidget with the given size and position, and 
		// initializes the array of radio button entries to 10. The final
		// argument is an ID number identifying the widget
		RadioWidget ( int, int, int, int, int );



		// Destructor

		~RadioWidget ( void );

};

#endif
