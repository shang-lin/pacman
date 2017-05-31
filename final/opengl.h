#ifndef _OPEN_GL_H_
#define _OPEN_GL_H_

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#ifndef __APPLE__
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "bitmap.h"


//this class was supposed to serve only as the first step of drawing propagation
//it has some initialization elements, but in the cpp file is a huge amount of 
//game mechanics that were needed 
//in order to make a mini map for the SideBar class, there needs to be a scaling factor
//in the beginning of RenderScene that will override the zoom level and the translation
//that sets your character in the middle and draw the entire hierarchy at one tenth the
//size.  SideBar itself should position the new minimap in the corner of the screen 
class OpenGL
{
	private:
		//hold all of the textures generated with bindtexture
		//it's possible this can be removed, because the implementation will retain the
		//texture values...
		//I'll have to experiemnt with that at a later time
		GLuint *texture_objects;

		//we might not need this either, but I'm not sure
		int numtextures;

	public:
		//use this function to set up OpenGL
		void InitializeOpenGL();

		//called in the test program to start the main rendering loop
		//it isn't delayed right now, but we're getting a playable FPS
		//right now so it isn't neccessary
		void StartMainLoop();

		
		//function of the OpenGL class that adds the texture into memory using the
		//glBindTexture function.
		//this method has an opposite removeBitmap method, but it is not implemented yet
		GLuint AddBitmap(BITMAPINFO *TexInfo, GLubyte *TexBits, bool blackclear = false);

		//there really needs to be a deleteBitmap function here, but I didn't get
		//time to make it, I also had some trouble loading the bitmaps
		//in the first place so I didn't want to mess this guy up again

		//simple constructor
		OpenGL(void);
};

#endif
