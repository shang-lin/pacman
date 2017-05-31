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

//TODO
//see if we need the texture_objects pointer

//add a remove bitmap function

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

		//this needs to be changed to use the glTimeDelayFunc() declaration.
		//I think it takes 2 parameters.  a void * for the function to call
		//and an int for the amount of time to wait before calling it
		//it'll work cross platform
		void StartMainLoop();

		
		//function of the OpenGL class that adds the texture into memory using the
		//glBindTexture function.
		//this method has an opposite removeBitmap method, but it is not implemented yet
		GLuint AddBitmap(BITMAPINFO *TexInfo, GLubyte *TexBits, bool blackclear = false);

		//simple constructor
		OpenGL(void);
};

#endif
