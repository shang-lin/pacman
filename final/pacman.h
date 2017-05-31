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

//it will take this long for pacman to die when he gets hit by a ghost
#define deadcountermax 40

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "player.h"
#include "drawableobject.h"
#include "pacskin.h"


// Description:
//
// This object represents user-controlled pacmen. 
//this is an example of how you can extend the Player class into a 
//game entity.  The Pacman class primarily has his own animations and ways
//in which you access these animations, otherwise, all gameplay functionality
//is contained within the Player class

//there is a lot of left over code in the pacman.cpp file that has been
//commented out.  It was all drawing code and was used when we had a depth
//buffer and were using sprites as our animation.  I have left the blend
//and alpha functions in in case anyone needs a simple reference to them.

class Pacman:public Player
{
		// Data Members

	private:
		//the animation sprite that we're currently on
		int numsprite;
		//are we opening the mouth, or closing
		bool opening;

		//variables for pacman's horrific death throw animation...
		//what a classic 
		bool dead;
		int deadcounter;
	public:


		// Methods

	private:

		//alive draw draws pacman when he's not dying
		void aliveDraw(void);
		void dyingDraw(void);

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

		//methods for accessing the pacdeath variables
                void setDead(void){dead = true; deadcounter = deadcountermax;}
                void resetDead(void){dead = false;}
                bool isDead(void){return dead;}
		int getDeadCount(void){return deadcounter;}
		void setDeadCount(int countin){deadcounter = countin;} 

                //decrements the deadcounter, returns 1 when it's 0!
		//should reassign pacman to a random space
                bool decDeadCount();


		// Constructor(s)
		Pacman(void);
		Pacman(string name, int playerpicid, PacSkin * tex, char* IPaddress);

		// Destructor

		~Pacman ( void );

};

#endif
