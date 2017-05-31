// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <iostream>
#include <string>
#include "drawableobject.h"
#include "image.h"

//TODO:
//   a few methods for different types of drawing may need to be added to this
// there are a few methods missing from the OOA/OOD spec because they were
// redundant.  Things like draw scaled and draw resized are the same to
// OpenGL, so the function draw scaled remains.

//  if we find that some of the other functions were needed after all, they can be
// added.



// The draw functions based on this class will ultimately call the Image::draw() function
// which outputs a texture mapped square or rectangle onto the screen.


//ACCESSORS

// Returns the value of centerX.  Used when a parent moves this item into position
int DrawableObject::getCenterX(void) 
{
	return centerX;
}

// Returns the value of centerY. Used when a parent moves this item into position
int DrawableObject::getCenterY(void)
{
	return centerY;
}

// Returns the value of width. Used when a parent draws this item
int DrawableObject::getWidth(void) 
{
	return width;
}

// Returns the value of height.  Used when a parent draws this item
int DrawableObject::getHeight(void)
{
	return height;
}

//MUTATORS

// Sets the width to the value of w.  Used when a parent draws this item
void DrawableObject::setWidth( unsigned int w ) 
{
	width = w;
}

// Sets the height to the value of h.  Used when a parent draws this item
void DrawableObject::setHeight( unsigned int h ) 
{
	height = h;
}

// Sets centerX to x.  Used when a parent draws this item
void DrawableObject::setCenterX( unsigned int x ) 
{
	centerX = x;
}

// Sets centerY to y.  Used when a parent draws this item
void DrawableObject::setCenterY( unsigned int y ) 
{
	centerY = y;
}

//set the id to the OpenGL texture key
void DrawableObject::setGraphicsHashID( int id) 
{
	graphicsHashID = id;
}


// Returns the value of graphicsHashID, the key to this object's 
// current image in the graphics hashtable. 
int DrawableObject::getGraphicsHashID( void ) 
{
	return graphicsHashID;
}


// Draws this object at its x & y coordinates. This method should 
// only be overridden by subclasses with special drawing requirements. 
// Otherwise, the subclass should generate an image of itself, 
// place that image in the GraphicsHash, and set its graphicsHashID 
// to the key of that image. Then, DrawableObject() will automatically 
// draw it. 
void DrawableObject::draw(void) 
{
	Image::draw(getGraphicsHashID());

}


// Draws the object subject to the specified scale arguments. 
// A scale of 1 causes the object to be drawn normally; .5 causes 
// the object to be scaled down by 1/2 in that direction; 2 causes 
// it to be stretched to twice its size in that direction. It 
// also draws the object at the specified location rather than 
// the default location. 
void DrawableObject::drawResized(GLfloat scaleX, GLfloat scaleY) 
{
	Image::drawResized(getGraphicsHashID(), scaleX, scaleY);
}


// Constructor(s)

// Initializes the DrawableObject to the specified size and location. 
// 
DrawableObject::DrawableObject(int id, int width, int height, int centerX, int centerY ) 
{
	setGraphicsHashID(id);
	setWidth(width);
	setHeight(height);
	setCenterX(centerX);
	setCenterY(centerY);
}

//default
DrawableObject::DrawableObject(void) 
{
}


// Destructor
//no need to free any memory yet
DrawableObject::~DrawableObject ( void ) 
{
	
}

