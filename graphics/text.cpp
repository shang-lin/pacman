#include <iostream>
#include <string>
#include "text.h"


// Description:
//
// This static object allows you to draw text to the screen at input coords 
//this function may be changed to output text using texture mapped fonts, but
//those are kind of hard to get looking right, and for now, the amount of text
//we're displaying is not going to affect the performance of the system
//it's a possible change on the table though.
//this is implemented as a static class, which is different from our original design
void Text::print(const char* out, int x, int y, void * font)
{
	//window width and height
	//used to get the position of the cursor from x and y
    int win_width, win_height;

    win_width = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);

	//we want to disable the following stuff to get independent colour values
	//for the text.
    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

	//the projection matrix needs to be saved
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef((float)x, (float)y, 0.0);

	//set the raster to the approprite screen coords and draw the text.
    glRasterPos2f(0, 0);
    while (*out != '\0') {
        glutBitmapCharacter(font, *out++);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void Text::print(int out, int x, int y, void * font)
{
	char* intout;
	intout = new char[26];
	sprintf(intout, "%i", out);

	Text::print(intout, x, y, font);
	delete[] intout;
}


// the menusystem needs a getwidth method for centering strings
int Text::getStringWidth( const char* out, void *font = GLUT_BITMAP_HELVETICA_18){
	// calls glutBitmapWidth ( void * font, int character) to get the width
	// of the each character and returns the sum.

	int sum= 0;
	int i = 0;
	while (out[i] != '\0'){
		sum += glutBitmapWidth ( font, (int)(out[i]));
		i++;
	}

	return sum;
}
