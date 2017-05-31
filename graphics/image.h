#ifndef _IMAGE_H_
#define _IMAGE_H_

using namespace std;

#include  <stdio.h>
#include  <stdlib.h>
#include  <string>
#include "bitmap.h"
#include "opengl.h"


// Description:
//
// This static object allows you to draw the OpenGL texture with 
// key ImageID onto the screen as a sprite. 
//this class looks significantly different from out OOA/OOD specs because
// a lot of it's functions were redundant, ie, the draw scaled and draw resized 
// functions are the same commands in OpenGL.  I have additionally added a 
// function that allows the display of partial textures, because textures must
// be 2^n in width and height in order to be displayed.  And the end display
//will not always be a square
class Image {
	private:

	public:
		// Calls the standard draw function with coordinates ( 0, 0 ).
		//move the coordinate system before calling this method with glTranslatef(x, y, z);
		static void draw (int ImageID, GLfloat width = 20, GLfloat height = 20);

		// Draws the image at ( 0, 0 ), with its width and 
		// height scaled to the given values. 
		static void drawResized (int ImageID, GLfloat widthscaler, GLfloat heightscaler,
								GLfloat width = 20, GLfloat height = 20);

		// Draws a portion of the image at ( 0, 0 ), with its width and 
		// height equal to the values given. 
		// the indent values are 0.0 - 1.0 and represent the amount you want to indent the texture
		// from the left side, right side, top and bottom
		static void drawPortion (int ImageID, GLfloat leftindent, GLfloat rightindent,
								GLfloat topindent, GLfloat bottomindent, 
								GLfloat width = 20, GLfloat height = 20);

		// adds an image to the OpenGL image hash and returns it's Texture ID. 
		static int addImage(string filename, bool blackclear=false);

		// Constructor(s)
		//a static class, no need for constructors
};


#endif
