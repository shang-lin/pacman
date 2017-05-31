#ifndef _TEXT_H_
#define _TEXT_H_

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
//	#include <OpenGL/gl.h>
//	#include <OpenGL/glu.h>
#endif

#ifndef __APPLE__
	#include <GL/glut.h>
//	#include <GL/gl.h>
//	#include <GL/glu.h>
#endif

using namespace std;

// Description:
//
// This static object allows you to draw text to the screen at input coords 
//this function may be changed to output text using texture mapped fonts, but
//those are kind of hard to get looking right, and for now, the amount of text
//we're displaying is not going to affect the performance of the system
//it's a possible change on the table though.
//this is implemented as a static class, which is different from our original design
class Text {
	private:

	public:
		// Outs the text to the screen at the specified location. 
		static void print(const char* out, int x = 0, int y = 0, void *font = GLUT_BITMAP_HELVETICA_18);

		//little bit of polymorphism for ya
		static void print(int out, int x = 0, int y = 0, void *font = GLUT_BITMAP_HELVETICA_18);

		// the menusystem needs a getwidth method for centering strings
		static int getStringWidth( const char* out, void *font = GLUT_BITMAP_HELVETICA_18);
};

#endif
