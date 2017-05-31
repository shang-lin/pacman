#ifndef _DRAWABLEOBJECT_H_
#define _DRAWABLEOBJECT_H_

#include "opengl.h"
#include "image.h"
#include "text.h"

// The includes for the superclasses are automatically listed.
// You need to specify any others


// Description:
//
// DrawableObject is a class from which all drawable objects 
// inherit. Every DrawableObject will have a draw() function 
// that behaves the same way.
//
// 
//
// Subclasses can either override the draw() function, or they 
// can generate an image of themselves and store it in the graphics 
// hash. Then, when draw() is called, the draw() in DrawableObject 
// merely looks up the Image by its hashID and draws it. If some 
// object has multiple images, it can keep track of the hashIDs 
// in a separate array and change the value of their DrawableObject:hashID 
// to reflect the current state. 

//changes:
//  We no longer have a hashID as was described in our first
// OOD/OOA presentation.  OpenGL has its own hashID system in place
// we are just using that.  There's no need for the extra wrapper.

//the drawable object handles it's own scaling as well, but it's geared toward
//texture scaling, therefore the Player subclasses handle their own graphical scaling
//because they are based on OpenGL primatives.

class DrawableObject {
		// Data Members

	private:
		// the x-value of the center of the object. 
		int centerX;

		// the y-value of the center of the object. 
		int centerY;

		// The width of the object in pixels. 
		int width;

		// The height of the object. 
		int height;

		// The key for the image for this item in the graphics hash. 
		// 
		int graphicsHashID;



	public:


		// Methods

	private:


	public:
		// Draws this object at the center of the coord system. This method should 
		// only be overridden by subclasses with special drawing requirements. 
		// Otherwise, the subclass should generate an image of itself, 
		//DrawableObject() will automatically draw it. 
		virtual void draw( void );


		// Returns the value of centerX. 
		int getCenterX( void );

		// Returns the value of centerY. 
		int getCenterY( void );

		// Returns the value of width. 
		int getWidth( void );

		// Returns the value of height. 
		int getHeight( void );

		// Draws the object subject to the specified scale arguments. 
		// A scale of 1 causes the object to be drawn normally; .5 causes 
		// the object to be scaled down by 1/2 in that direction; 2 causes 
		// it to be stretched to twice its size in that direction. 
		void drawResized(GLfloat width, GLfloat height);

		// Sets the width to the value of w. 
		void setWidth( unsigned int );

		// Sets the height to the value of h. 
		void setHeight( unsigned int );

		// Sets centerX to x. 
		void setCenterX( unsigned int );

		// Sets centerY to y. 
		void setCenterY( unsigned int );

		// Changes the value of the graphics hash ID. This is used for 
		// DrawableObject subclasses that don't override draw() but that 
		// have several states which require different images. 
		void setGraphicsHashID( int );

		// Returns the value of graphicsHashID, the key to this object's 
		// current image in the graphics hashtable. 
		int getGraphicsHashID( void );


		
		// Constructor(s)
		
		DrawableObject(void);

		// Initializes the DrawableObject to the specified size and location. 
		// 
		DrawableObject ( int id, int width, int height, int centerX, int centerY );



		// Destructor

		virtual ~DrawableObject ( void );

};

#endif

