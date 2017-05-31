#ifndef _PACSKIN_H_
#define _PACSKIN_H_

//TODO
//add audio


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <iostream>
#include <string>
#include "drawableobject.h"


// Description:
//
// The skin object for a client. This contains both graphical 
// and audio information. 

class PacSkin : private DrawableObject{
		// Data Members

	private:
		// colour of Pacman 
		float rgb[3];

		// size of pacman 100 is normal 
		int size;

		// sound game plays when pacman eats a pill 
//		MP3 munching;

		// sound game player when pacman is super pacman 
//		MP3 superpac;



	public:


		// Methods

	private:


	public:

		//override the draw method with opengl commands
		void draw(void);

		// Draws the object subject to the specified scale arguments. 
		// A scale of 1 causes the object to be drawn normally; .5 causes 
		// the object to be scaled down by 1/2 in that direction; 2 causes 
		// it to be stretched to twice its size in that direction. 
		void drawResized(GLfloat width, GLfloat height);


		// Constructor(s)

		// loads the pacman texture file and relevant bitmaps and MP3s. 
		// 
		PacSkin ( string );
		PacSkin ( void);



		// Destructor

		~PacSkin ( void );

};

#endif

