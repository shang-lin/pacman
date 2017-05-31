/* Revision History

	4/21
	New methods
		Added a delete a player method.
		
		In order for this to work, I also had to add several supporting functions
		for searching for PlayerID's, support for playerIDs.  

		Modified the AddPlayer function so that it creates a pointer to a 
		new player and then passes that to the appropriate addplayer method
		now there isn't a wasted function for prebuild player objects

		changed some of the malloc's to new's for the players.

		added the bool array for a list of 100 free ID numbers
		this means that there can only be 100 pacmen in the game at a time,
		but I didn't think that would matter, it can be easily changed though
		In fact, it should be assigned to a defined variable
		
	4/29
	Major Overhaul
		Found out about STL recently and how easy it makes your life.  I hesitate
		to even write that in this code, because I know I should have learned it in
		CS40, and I did, but I really still thought that it would just overcomplicate
		what I was doing with mallocs and reallocs, what an idiot I was.  I had a volume of
		unreadable code that I completely minimized into a few dozen lines that do EXACTLY
		the same thing with the PlayerMap that three arrays did in a less efficient manner.

		I didn't bother to leave the removed code in, because it was just ridiculous array
		manipulations, but I left the data members that were used commented out
		in the header file so you can get an IDEA of what I was using before.

	Passing Int's Instead of Pointers
		Got rid of that too, it was criticized in our code comments, so I changed to using the
		map<int, Player *> process, I honestly can't believe that that worked, but
		it did, so here I am.

	6/03
	Added Accessors
		Added methods that change the state of the Player objects that PlayerList contains
		this turned out to be VERY efficient, all state changing methods should take place
		like this.
*/

#ifndef _PLAYERLIST_H_
#define _PLAYERLIST_H_

//this pragma warning is really a POS, I found it by sheer luck, I would hate to have been searching
//for how to fix a billion errors
#ifdef WIN32
#pragma warning(disable:4786)
#endif

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <iostream>
#include <string>
#include <map>

#include "drawableobject.h"
#include "pacman.h"
#include "ghost.h"
#include "pacskin.h"

#include  <stdio.h>
#include  <stdlib.h>

using namespace std;

// Description:
//
// This class started as a mere container for the list of players.
// As we began coding and integrating, however, it turned into more
// of an accessor class for the Player objects that it contained.
// for example, the set and reset GhostsEdible method allows
// any other class to turn the ghosts Edible for a short period of
// time without actually having to access the Player objects themselves.

// I wish we would have thought of that first and used only this 
// PlayerList object to interact with the Players.  It would
// probably even be better to subclass PlayerList into separate types
// of containers for the various subclassed Player objects.  That way
// we wouldn't have to append to PlayerList each time a new type of
// Player object had a new functionality.
class PlayerList:public DrawableObject{
		// Data Members

	private:
		//got rid of all those ridiculous arrays and substituted an STL map<>
		//for keeping track of players
		map<int, Player*> PlayerMap;

	public:

		// Methods

	private:
		// adds a player to the list from a ready made player object 
		// this is called from within the addplayer(params) method, so don't think you can just
		// get rid of it
		//if the ID param is set, the network wants to force an ID for a player... 
		int addplayer(Player * newplayer, int ID = 0);

	public:

		//move the coord system and draw the players in their places
		//put something in here to draw pacmen first, then move the coord system up and
		//draw the ghosts.
		//a possible solution would be to make the depth buffer read only when writing to the
		//system, such that the ghosts or pacman wouldn't draw if it was behind a level.
		//solved this problem by getting rid of the depth buffer.
		//pacmen are drawn first, then ghosts, that way ghosts are always on top
		void draw(void);

		// creates and adds a new Playser object to the array and returns 
		// the ID.  The IPaddress can be void if it's an AI player.
		//if the ID param is set, the network wants to force an ID for a player... 
		int addplayer(string name, int playerpicid, PacSkin * tex, bool Ghost = 0, 
				char* IPaddress = 0, int ID = 0);



		//need a function to remove a player from the game.
		//Just take them out of the array using their id and shift everything down
		int removeplayer(int playerid); 
		
		//getplayer returns a pointer to the player with a given ID, 
		//it can also return the Player's index in the map, but I haven't found a use for
		//it yet, maybe there isn't one.
		Player * getPlayer(int playerid, int * index = NULL);


		//return a copy of the current player map, in case any thing else needs to step 
		//through the players.....I will admit up front that this is a little sloppy
		//the class shouldn't return a pointer to one of it's private data members,
		//but I didn't have time to add functionality for accessing the players through 
		//the player list for the sidebar.  The server also needed to get a hold of the PlayerMap
		//itself.  If this class were to be worked on, the first step would be to get rid of this
		//method...
		map<int, Player*>* getPlayerMap(void);

		//returns number of players
		int getNumPlayers(void);



		//the following are the types of methods that should be ubiquitous in the PlayerList class
		//they takes so much work out of the calling function's hands and completely
		//obscures the implementation...


		//returns true if the players are on the same Z level
		bool onSameZLevel(int playerID1, int playerID2);

		//returns the X distance separating two players
		GLfloat getXSep(int playerID1, int playerID2);

		//returns the Y distance separating two players
		GLfloat getYSep(int playerID1, int playerID2);

		//set all of the ghosts to edible
		void setGhostsEdible();

		//set all of the ghosts to NOT edible
		void resetGhostsEdible();



		// Constructor(s)

		PlayerList( void );


		// Destructor

		~PlayerList ( void );

};

#endif

