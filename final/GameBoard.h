#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

class Gameboard;
class Level;

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "drawableobject.h"
#include "Level.h"
#include "chatwnd.h"
#include "sidebar.h"
#include "GameServer.h"
#include "UDPacket.h"
#include "GameRules.h"
#include "GameClient.h"
#include "BaseItem.h"
#include "RUDP.h"

// Description:
//
// This is a member of GameClient. It serves as the Model & View 
// in the MVC model.
 //
// 
 //
// This object contains a PlayerList, the current Level, the 
// ChatWnd object, and the Sidebar object. 
// This class is also responsible for updating the positions
// of the players between packets from the server.

class Gameboard : private DrawableObject{
// Data Members

private:
// This is the range of x-values of spaces in the level. 
  int width;

// This is the current level. 
 Level *level;

// This is the list of user-controlled players. 
 Player** userPlayers;

// This is the list of AI-controlled players. 
 Player** aiPlayers;

 // list of both for updating location
 Player** playerList;

// The chatwindow overlay object. 
 ChatWnd *chatWindow;

// The sidebar object. This displays information such as the 
// list of players, the remaining time, and the mini-map. 
 SideBar *sidebar;

// The list of players who are merely observing the game. 
 Player** observerList;

 PlayerList *drawlist;

 GameRules *defaultRules;
 GameRules **currentRules;
 GameMechanicsRules *currentMechanics;

 // GameClient *client;

 RUDP *socket;

 sockaddr_in *serverad;

 int numPlayers, numAI, numObs, numtotalplayers;

 int starttime;  // the server time when this client was started

 int endgame;  // will be set to one when the game ends

 int whichplayer;  // tells the client which player it controls

 float oldtime;  // used to move players between updates

public:


// Methods

private:
// sends a request to the server asking for a move 
bool requestMove(int );

// requests to eat for the player from the server 
bool requestEatPlayer( int, int );

// asks the server for permission to eat this item 
bool requestEatItem( int, int );



public:
// Returns the width of the level. 
 int getWidth( void );
 
 // Returns the length (range of y-values) of the level. 
 int getLength( void );
 
 // Returns the number of levels (ie, stories) in the level. 
 int getLevels( void );
 
 // Handles/forwards events. 
 void receiveEvent(UDPacket* );

 void draw();
 
 Space* getSpace(int x, int y, int z);
 
 void Move(Player* p, int x, int y, int z);

 void Move(Player* p, Space* where); 

 void EatItem(Player* p, BaseItem* item);

 void EatPlayer(Player* p, Player* eaten);

 void addPlayer(Player* p, int ai);

 void RemovePlayer(Player *p);

 void runClient();

 float getTime();

 void movePlayers(float deltatime);

 bool CanIMove(Player *p, Space *where);

 void invokeItemRules(BaseItem *item, Player *p);

 int* IntToByte(int a, int b);

 // Constructor(s)
		 
 Gameboard(Level *newlevel, sockaddr_in *servad);


// Destructor

~Gameboard ( void );

};

#endif





