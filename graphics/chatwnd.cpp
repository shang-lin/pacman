/* Revision History

  4/14 - added this little class into the mix...
	It's mostly functional today, it doesn't look terribly good, but it works.

*/


#include <iostream>
#include <string>
#include "chatwnd.h"


void ChatWnd::ortho_draw()
{
    int win_width, win_height;

    win_width = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);

    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
//    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

//	glColor4f(1, 0, 0, .5);
//	glRectf(5, win_height-32, win_width, win_height-30);
	glColor4f(.2, .2, .4, .5);
	glRectf(10.0, win_height-100, win_width-200, win_height-5);

	glColor4f(.3, .7, .3, .85);
//	Text::print("this is the title bar", 15, win_height-30);
	Text::print((char *)text[2].data(), 15, win_height-30);
	Text::print((char *)text[1].data(), 15, win_height-50);
	Text::print((char *)text[0].data(), 15, win_height-70);

	//draw a line separating the chat messages from the pending message
	glRectf(10.0, win_height-77, win_width-200, win_height-75);

	Text::print((char *)activeString.data(), 15, win_height-97);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}


//draw the chat window on the screen using the ortho draw function
void ChatWnd::draw(void)
{
	//make the ortho projected stuff see through....this is cool pretty cool
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ortho_draw();

	glDisable(GL_BLEND);

}


// adds a character onto the active test string.  The user typed a letter. 
void ChatWnd::addChar(char charin)
{
	activeString+=charin;
}


// Clears the last character that the user entered. 
void ChatWnd::deleteChar( void )
{
	//haha, this is a good one
	//make sure there is more than one character in the string
	if(activeString.length() > 0)
	{
		activeString.erase(activeString.length()-1);
	}

}


// Adds the string to the marquee.  this should be used by the network 
//listener to add an incoming chat message
//this function will add the string to the bottom of 
//the array and delete the 0 index string.
void ChatWnd::addMessage(string msgin)
{
	text[2] = text[1];
	text[1] = text[0];
	text[0] = msgin;
}


//this returns the active string, this should be called from 
//the control object to get the user's chat message
//that will be sent to the network layer.  This method will also
//clear the user's active string!
string ChatWnd::getString(void)
{
	string ret = activeString;
	activeString.erase();
	return ret;
}

// Constructor(s)
ChatWnd::ChatWnd(void)
{
}

// Destructor
ChatWnd::~ChatWnd ( void )
{
}

