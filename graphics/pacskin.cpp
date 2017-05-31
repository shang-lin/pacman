/* Revision History

  4/14 - changed the move amount for adding the skin.  Now we move a full
	.1 away from Pacman, this had to be put in because the skin was being
	drawn on the same z level as the pacman when you were zoomed out far
	enough....
*/

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "pacskin.h"
#include "drawableobject.h"


//TODO
//add audio

// Description:
//
// The skin object for a client. This contains both graphical 
// and audio information. 

//draw the skin to the screen, pretty simple
void PacSkin::draw(void)
{
	Image::draw(getGraphicsHashID());
}

//draw the skin resized in case the pacman has grown or shrunk
//this should be the only draw method called for that reason
void PacSkin::drawResized(GLfloat width, GLfloat height)
{
	Image::drawResized(getGraphicsHashID(), width, height);
}

// Constructor(s)

// loads the pacman texture file and relevant bitmaps and MP3s. 
// 
PacSkin::PacSkin(string filename ) 
{
	this->setGraphicsHashID(Image::addImage(filename.data(), true));
}

PacSkin::PacSkin(void)
{
}

// Destructor

PacSkin::~PacSkin ( void ) {
	
}


