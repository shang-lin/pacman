#ifndef _CHATWND_H_
#define _CHATWND_H_

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "drawableobject.h"


// Description:
//
// This object represents the chat display marquee. It is drawn 
// as a transparent overlay over the board. It will display three 
// lines of static chat text and system messages, as well as 
// one currently active line of type. 
//this class is left out in single player mode
class ChatWnd : private DrawableObject{
		// Data Members

	private:
		// The three lines of static text that are displayed. 
		string text[3];

		// The active line of text that the user is editing. 
		string activeString;

		// The maximum length of the string. 
		int maxlength; //we'll keep this at 1024 or something, so that messages can only be one line long.



	public:


		// Methods

	private:

		//draws onto the view using the orthogonal projection matrix
		//this should mean that the drawing overwrites anything that is on the viewing screen
		//this also means that orthodrawing must be done in order of what you want to appear:
		// chat window -> text
		void ortho_draw(void); 

	public:

		void draw(void);

		// adds a character onto the active test string.  The user typed a letter. 
		void addChar(char in);

		// Clears the last character that the user entered. 
		void deleteChar( void );

		// Adds the string to the marquee.  this should be used by the network 
		//listener to add an incoming chat message
		//this function will add the string to the bottom of 
		//the array and delete the 0 index string.
		void addMessage( string msgin);

		//this returns the active string, this should be called from 
		//the control object to get the user's chat message
		//that will be sent to the network layer.  This method will also
		//clear the user's active string!
		string getString(void);


		// Constructor(s)

		ChatWnd(void);


		// Destructor

		~ChatWnd ( void );

};

#endif
