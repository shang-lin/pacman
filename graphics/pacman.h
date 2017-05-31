/* Revision History

	4/29
	Moved Skin
		Moved the PacSkin data memeber skin into the parent class of ghost and pacman
		I figured that it would be easier to leave it in pacman, but I forgot to 
		consider the consequences of changing the gender of a player from pacman
		to ghost

*/

#ifndef _PACMAN_H_
#define _PACMAN_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "player.h"
#include "drawableobject.h"
#include "pacskin.h"

//TODO
//need functions and data members to handle direction changes
//and interpretations of the gameboard so that the ghosts can 
//move on their own


// Description:
//
// This object represents user-controlled pacmen. It accepts 
// certain keypress events. 

class Pacman:public Player
{
		// Data Members

	private:
		//the animation sprite that we're currently on
		int numsprite;
		//are we opening the mouth, or closing
		bool opening;
	
	public:


		// Methods

	private:


	public:
		//override the draw method with opengl commands
		void draw();

		// Draws the object subject to the specified scale arguments. 
		// A scale of 1 causes the object to be drawn normally; .5 causes 
		// the object to be scaled down by 1/2 in that direction; 2 causes 
		// it to be stretched to twice its size in that direction. 
		void drawResized(GLfloat width, GLfloat height);

		
		// Always returns false. This overrides the virtual function 
		// isAGhost() in the Player class. 
		bool isAGhost( void );


		// Constructor(s)
		Pacman(void);
		Pacman(string name, int playerpicid, PacSkin * tex, char* IPaddress);


		// Destructor

		~Pacman ( void );

};

#endif
