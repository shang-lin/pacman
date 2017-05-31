#ifndef _SERVERGAMEBOARD_H_
#define _SERVERGAMEBOARD_H_

/* This class contains the server's representation of the level and everything in it.  GameServer gets information from this class, makes the necessary decisions, and updates this class accordingly. */

class ServerGameboard;
class Level;
// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "drawableobject.h"
#include "GameServer.h"
#include "../graphics/sidebar.h"
#include "../graphics/chatwnd.h"
 

class ServerGameboard : private DrawableObject{
// Data Members

private:
// This is the range of x-values of spaces in the level. 
int width;

// This is the current level. 
Level* level;

// This is the list of user-controlled players. 
Player** userPlayers;

// This is the list of AI-controlled players. 
Player** aiPlayers;

// The list of players who are merely observing the game. 
Player** observerList;

 int numUsers, numAI, numObs;

// The GameServer containing the gameboard, null if this is a client gameboard
 GameServer *server;

 int ghostkillbonus, pacdeathpenalty, packillbonus, ghostdeathpenalty;

public:


// Methods


public:
// Returns the width of the level. 
 int getWidth( void );
 
 // Returns the length (range of y-values) of the level. 
 int getLength( void );
 
 // Returns the number of levels (ie, stories) in the level. 
 int getLevels( void );
 
 Space* getSpace(int x, int y, int z);
 
 Level* getLevel();

 void Move(Player* p, int x, int y, int z);

 void Move(Player* p, Space* where); 

 void EatItem(Player* p, BaseItem* item);

 void EatPlayer(Player* p, Player* eaten);

 void addPlayer(Player* p, int ai);

 // Constructor(s)
		 
 ServerGameboard(Level *newlevel, GameServer *newserver);


// Destructor

~ServerGameboard ( void );

};

#endif








