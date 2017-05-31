#ifndef _GHOST_H_
#define _GHOST_H_

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "player.h"
#include "drawableobject.h"


// Description:
//
// This class represents Ghost players in the game.
//this class is another example of how to extend the Player class
//like Pacman, Ghost primarily contains methods that make the character
//draw differently on the screen, including animation size and colour.
class Ghost:public Player
{
		// Data Members

	private:
		int numsprite;

		//0x00 00 00 //rbg
		int color;


		//says if the ghost is edible or not, we had to stick this in as a temporary fix
		bool edible;

		//if the ghost is a pair of eyeballs right now, after he has been eaten
		bool dead;

		//time remaining until this ghost is alive again
		int deadcounter;

	public:


		// Methods

	private:

		//draws the eyeballs of the ghost, in the intended direction
		void drawEyeball(void);
		void drawIris();

	public:

		//override the draw method with opengl commands
		void draw();

		// Always returns true. This overrides the virtual function isAGhost() 
		// in the Player class. 
		bool isAGhost( void );

		//get the ghost's colour
		int getColor(void);

		void setColor(int newcolor);

		void setEdible(void);
		void resetEdible(void);
		bool isEdible(void){return edible;}


		//dead methods
		void setDead(void){dead = true;}
		void setDead(int count){dead = true; deadcounter = count;}
		void resetDead(void){dead = false; deadcounter = 0;}
		bool isDead(void){return dead;}
		
		//decrements the deadcounter, returns 1 when it's 0!
		bool decDeadCount();


		//set random color
		void setRandomColor(){setColor(rand()%0xFF +  ((rand()%0xFF) << 8) + ((rand()%0xFF) <<16));}
		// Constructor(s)
		Ghost(void);

		//0x00 00 00  rbg
		Ghost(string name, int playerpicid, int color, char* IPaddress);


		// Destructor
		~Ghost(void);

};

#endif

