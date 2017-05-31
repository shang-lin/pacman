#ifndef _GHOST_H_
#define _GHOST_H_

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "player.h"
#include "drawableobject.h"

//TODO
//make AIGhost and UserGhost
//need functions and data members to handle direction changes
//and interpretations of the gameboard so that the ghosts can 
//move on their own

// Description:
//
// This class represents Ghost players in the game. It has two 
// subclasses AIGhost and UserGhost.
class Ghost:public Player
{
		// Data Members

	private:
		int numsprite;

		//0x00 00 00 //rbg
		int color;


		//says if the ghost is edible or not, we had to stick this in as a temporary fix
		bool edible;

	public:


		// Methods

	private:


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

		// Constructor(s)
		Ghost(void);

		//0x00 00 00  rbg
		Ghost(string name, int playerpicid, int color, char* IPaddress);


		// Destructor
		~Ghost(void);

};

#endif

