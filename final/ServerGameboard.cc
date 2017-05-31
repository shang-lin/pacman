// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "ServerGameboard.h"




// Returns the width of the level. 
int ServerGameboard::getWidth( void ) {
  return level->getWidth();
}

// Returns the length (range of y-values) of the level. 
int ServerGameboard::getLength( void ) {
  return level->getLength();
}

// Returns the number of levels (ie, stories) in the level. 
int ServerGameboard::getLevels( void ) {
  return level->getFloors();
}


Space* ServerGameboard::getSpace(int x, int y, int z)
{
  return level->getSpace(x, y, z);
}

void ServerGameboard::Move(Player* p, int x, int y, int z)
{
  Space* newspace = level->getSpace(x, y, z);
  Space* oldspace = p->getSpace();
  p->changePosition(newspace);  // Move the player into the new space
  newspace->addPlayer(p);
  oldspace->removePlayer(p->getPlayerID());
}

void ServerGameboard::Move(Player* p, Space* newspace)
{
  Space* oldspace = p->getSpace();
  p->changePosition(newspace);  // Move the player into the new space
  newspace->addPlayer(p);
  oldspace->removePlayer(p->getPlayerID());
}

void ServerGameboard::EatItem(Player* p, BaseItem* item)
{
  item->changeGameboard(this, p);  // immediate changes to gameboard
  server->invokeItemRules(item, p);  // changes in rules such as speed changes
  (p->getSpace())->removeItem();  // remove the item from the board
}

void ServerGameboard::EatPlayer(Player *p, Player *eaten)
{
  //int deltascore, deathscore;
  //if(p->isAGhost())
  //  {
  //    deltascore = ghostkillbonus;
  //    deathscore = pacdeathpenalty;
  //  }
  //else
  //  {
  //    deltascore = packillbonus;
  //    deathscore = ghostdeathpenalty;
  //  }
  //p->changeScore(deltascore);
  //eaten->changeScore(deathscore);
  (eaten->getSpace())->removePlayer(eaten->getPlayerID());
  (eaten->changePosition(0));
  server->CanIRespawn(eaten);  // does the eaten player have another life?

  // possibly add something to cause ghosts to become 'bloated' after eating a pacman

}

void ServerGameboard::addPlayer(Player *p, int ai)
{
  if(ai == 0)
    {
      userPlayers[numUsers]=p;  // This list determines who receives chat
      numUsers++;
      // sidebar->addPlayer(p);
    }
  if(ai == 1)
    {
      aiPlayers[numAI]=p;
      numAI++;
      // sidebar->addPlayer(p);
    }
  if(ai == 2)  // new player is an observer
    {
      observerList[numObs]=p;
      numObs++;
    }
}

// Constructor(s)

ServerGameboard::ServerGameboard(Level *newlevel, GameServer *newserver)
{
  level = newlevel;
  server = newserver;
  userPlayers = new Player*[16];
  aiPlayers = new Player*[16];
  observerList = new Player*[16];
  // chatWindow = new ChatWnd();
  // sidebar = new Sidebar();
  numUsers = numAI = numObs = 0;
}


// Destructor

ServerGameboard::~ServerGameboard ( void ) {
  delete userPlayers;
  delete aiPlayers;
  delete observerList;
  // delete chatWindow;
  // delete sidebar;
  userPlayers = 0;
  aiPlayers = 0;
  observerList = 0;
  // chatWindow = 0;
  // sidebar = 0;
}





