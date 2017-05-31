// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "GameBoard.h"
#include "../graphics/drawableobject.h"
// #include <time.h>
#include <sys/time.h>

// sends a request to the server asking for a move 
bool Gameboard::requestMove(int direction ) {
  UDPacket *request;
  request = new UDPacket();
  byte reqinfo[3];
  reqinfo[0] = (char)1;
  reqinfo[1] = (char)whichplayer;
  reqinfo[2] = (char)direction;
  request->setData(reqinfo, 3);
  request->setAddress(serverad);
  socket->sendReliable(request);
}
  // used to be part of request move 

  //int* dataarray;
  //int* secondarray;
  //int* temparray;
  //dataarray = new int[8];
  //secondarray = new int[8];
  //temparray = new int[8];
  //for(int i = 0; i < 8; i++)
  //  {
  //    dataarray[i] = 0;
  //    secondarray[i] = 0;
  //    temparray[i] = 0;
  //  }
  //dataarray[1] = 1;
  //temparray = IntToByte(PlayerID, 4);
  //for (int i = 0; i < 4; i++)
  //  {
  //    dataarray[(i+3)] = temparray[i];
  //  }
  //secondarray = IntToByte(direction, 3);
 
  // convert these arrays to bytes, create and send packet


int* IntToByte(int a, int b){

}

// the next two functions will not be used

// requests to eat for the player from the server 
bool Gameboard::requestEatPlayer( int eater, int eaten ) {

}

// asks the server for permission to eat this item 
bool Gameboard::requestEatItem( int PlayerID, int ItemID ) {

}



// Returns the width of the level. 
int Gameboard::getWidth( void ) {
  return level->getWidth();
}

// Returns the length (range of y-values) of the level. 
int Gameboard::getLength( void ) {
  return level->getLength();
}

// Returns the number of levels (ie, stories) in the level. 
int Gameboard::getLevels( void ) {
  return level->getFloors();
}

// Handles/forwards events. 
void Gameboard::receiveEvent( UDPacket *pack ) {
  int length = pack->getLength();
  int type = pack->getData(0);
  int xloc, yloc, zloc, pid, i, done, firsthalf, secondhalf, neg, score, nump, dir, nextdir, fd;
  pid = xloc = yloc = zloc = done = i = firsthalf = secondhalf = neg = score = nump = dir = nextdir = fd = 0;
  float fdist = 0.0;
  Space *where;
  Player *who;
  if(type == 0)
    {
      nump = (int)(pack->getData(1));
      if(length == ((8 * nump) + 2));
      for(int k = 0; k < nump; k++)
	{
	  pid = (int)(pack->getData((8 * k) + 2));
	  xloc = (int)(pack->getData((8 * k) + 3));
	  yloc = (int)(pack->getData((8 * k) + 4));
	  zloc = (int)(pack->getData((8 * k) + 5));
	  dir = (int)(pack->getData((8 * k) + 6));
	  nextdir = (int)(pack->getData((8 * k) + 7));
	  firsthalf = (int)(pack->getData((8 * k) + 8));
	  secondhalf = (int)(pack->getData((8 * k) + 9));
	  fd = ((firsthalf * 100) + secondhalf);
	  fdist = (float)fd;
	  fdist /= 10000;
	  while(!done)
	    {
	      if(pid == (playerList[i]->getPlayerID()))
		{
		  who = playerList[i];
		  done = 1;
		}
	      i++;
	    }
	  where = level->getSpace(xloc, yloc, zloc);
	  who->changePosition(where);
	  who->changeDirection(dir);
	  who->setIntended(nextdir);
	  who->setFracDist(fdist);
	}
      oldtime = time(0);
    }

      // update player information
  if(type == 2)
    {
      if(length == 5)
	{
	  xloc = (int)(pack->getData(1));
	  yloc = (int)(pack->getData(2));
	  zloc = (int)(pack->getData(3));
	  where = level->getSpace(xloc, yloc, zloc);
	  pid = (int)(pack->getData(4));
	  while(!done)
	    {
	      if(pid == playerList[i]->getPlayerID())
		{
		  EatItem(playerList[i], (where->getItem()));
		  done = 1;
		}
	      i++;
	    }
	}
    }
  if(type == 3)
    {
      if(length == 2)
	{
	  pid = (int)(pack->getData(1));
	  while(!done)
	    {
	      if(pid == playerList[i]->getPlayerID())
		{
		  RemovePlayer(playerList[i]);
		  done = 1;
		}
	      i++;
	    }	 
	}
    }
  if(type == 4)
    {
      if(length == 5)
	{
	  pid = (int)(pack->getData(1));
	  neg = (int)(pack->getData(2));
	  firsthalf = (int)(pack->getData(3));
	  secondhalf = (int)(pack->getData(4));
	  score = (firsthalf * 100) + secondhalf;
	  if(neg)
	    score *= -1;
	  while(!done)
	    {
	      if(pid == playerList[i]->getPlayerID())
		{
		  playerList[i]->changeScore(score);
		  done = 1;
		}
	      i++;
	    }	  
	}
    }

  // start and end stuff
	      
}

void Gameboard::draw()
{
  //level->draw();
  //drawlist->draw();
  //sidebar->draw();
  //chatWindow->draw();
}

void Gameboard::RemovePlayer(Player *p)
{
  Space *where;
  where = p->getSpace();
  p->changePosition(0);
  where->removePlayer(p->getPlayerID());
}

Space* Gameboard::getSpace(int x, int y, int z)
{
  return level->getSpace(x, y, z);
}

void Gameboard::Move(Player* p, int x, int y, int z)
{
  Space* newspace = level->getSpace(x, y, z);
  Space* oldspace = p->getSpace();
  p->changePosition(newspace);  // Move the player into the new space
  newspace->addPlayer(p);
  oldspace->removePlayer(p->getPlayerID());
}

void Gameboard::Move(Player* p, Space* newspace)
{
  Space* oldspace = p->getSpace();
  p->changePosition(newspace);  // Move the player into the new space
  newspace->addPlayer(p);
  oldspace->removePlayer(p->getPlayerID());
}

void Gameboard::EatItem(Player* p, BaseItem* item)
{
  // client doesn't change gameboard directly, just remove the item and update speed rules
  // item->changeGameboard(this, p);  // immediate changes to gameboard
  invokeItemRules(item, p);  // changes in rules such as speed changes
  (p->getSpace())->removeItem();  // remove the item from the board
}

void Gameboard::invokeItemRules(BaseItem *item, Player *p){

}

// remove this method from client?

//void Gameboard::EatPlayer(Player *p, Player *eaten)
//{
//  int deltascore, deathscore;
//  if(p->isAGhost())
//    {
//      deltascore = ghostkillbonus;
//      deathscore = pacdeathpenalty;
//    }
//  else
//    {
//      deltascore = packillbonus;
//      deathscore = ghostdeathpenalty;
//    }
//  p->changeScore(deltascore);
//  eaten->changeScore(deathscore);
//  (eaten->getPostition())->removePlayer(eaten);
//  (eaten->changePosition(null));
//  server->CanIRespawn(eaten);  // does the eaten player have another life?

  // possibly add something to cause ghosts to become 'bloated' after eating a pacman

//}

void Gameboard::addPlayer(Player *p, int ai)
{
  if(ai == 0)
    {
      userPlayers[numPlayers] = p;  // This list determines who receives chat
      numPlayers++;
      playerList[numtotalplayers]=p;
      numtotalplayers++;
      drawlist->addplayer(p, (p->getPlayerID()));
    }
  if(ai == 1)
    {
      aiPlayers[numAI] = p;
      numAI++;
      playerList[numtotalplayers]=p;
      numtotalplayers++;
      drawlist->addplayer(p, (p->getPlayerID()));
    }
  if(ai == 2)  // new player is an observer
    {
      observerList[numObs] = p;
      numObs++;
    }
}

void Gameboard::runClient()
{
  // need different method to update from server
  // get system time and create deltatime
  float curtime, deltatime;
  float gametime = starttime;
  timeval tm;
  gettimeofday(&tm, NULL);
  oldtime = ((tm.tv_sec - starttime) * 1000) + (tm.tv_usec / 1000);
  endgame = 0;
  int steps = 0;
  while(!endgame)
    {
      gettimeofday(&tm, NULL);
      cout << (tm.tv_sec - starttime) << " and " << tm.tv_usec << '\n';
      curtime = ((tm.tv_sec - starttime) * 1000) + (tm.tv_usec / 1000);
      cout << "time: " << curtime << '\n';
      deltatime = curtime - oldtime;
      cout << deltatime << '\n';
      if(deltatime)
	movePlayers(deltatime);
      if(steps >= 10)
        {
	  draw();
      //    updateClients();
      //    AIdecisions();
          steps = 0;
	}
      else
	{
	if(deltatime)
	  steps++;
	}
      oldtime = curtime;
    }
}

float Gameboard::getTime(){

}

void Gameboard::movePlayers(float deltatime)
{
  Space* current;
  int curdir, newdir, moved, olddir;
  float fracdist;
  float distance;
  float* speedarray;
  speedarray = currentMechanics->getSpeedArray();
  for(int i = 0; i < numtotalplayers; i++)
    {
      moved = 0;
      cout << i << " is too high\n";
      fracdist = playerList[i]->getFracDist();
      cout << "time to segfault?\n";
      distance = deltatime * (speedarray[i]);
      cout << "guess not\n";
      fracdist += distance;
      if(fracdist >= 1)
        {
          curdir = playerList[i]->getDirection();
          newdir = playerList[i]->getIntended();
          current = playerList[i]->getSpace();
          if(current->getNeighbor(newdir))
            {
              if(CanIMove(playerList[i], current->getNeighbor(newdir)))
                {
                  moved = 1;
                }
            }
          if(!(moved))
            {
              if(current->getNeighbor(curdir))
                {
                  if(CanIMove(playerList[i], current->getNeighbor(curdir)))
                    {
                      moved = 1;
                    }
                }
            }
          if(!(moved))
            {
              if(curdir == 1)
                olddir = 3;
              else if(curdir == 2)
                olddir = 4;
              else if(curdir == 3)
                olddir = 1;
              else if(curdir == 4)
                olddir = 2;
              else if(curdir == 5)
                olddir = 6;
              else
                olddir = 5;
              for(int j = 0; ((j < 7) && (!(moved))); j++)
                {
                  if((j != newdir) && (j != curdir) && (j != olddir))
                    {
                      if(current->getNeighbor(j))
                        {
                          if(CanIMove(playerList[i], current->getNeighbor(j)))
                            {
                              moved = 1;
                            }
                        }
                    }
                }
            }
          if(!(moved))
            {
              if(current->getNeighbor(olddir))
                {
                  if(CanIMove(playerList[i], current->getNeighbor(olddir)))
                    {
                      moved = 1;
                    }
                }
            }
          assert(moved);
          fracdist -= 1.0;
        }
      playerList[i]->setFracDist(fracdist);
    }
}

// check if player can move into space
bool Gameboard::CanIMove(Player *p, Space *where){

}


// Constructor(s)

Gameboard::Gameboard(Level *newlevel, sockaddr_in *servad)
{
  cout << "called Gameboard constructor\n";
  int portnum = 42;  // what should portnum be?
  level = newlevel;
  // client = theclient;
  userPlayers = new Player*[16];
  aiPlayers = new Player*[16];
  observerList = new Player*[16];
  playerList = new Player*[32];
  chatWindow = new ChatWnd();
  sidebar = new SideBar();
  socket = new RUDP(portnum);
  drawlist = new PlayerList();
  numPlayers = numAI = numObs = 0;
  defaultRules = new GameRules();
  currentRules = new GameRules*[8];
  currentMechanics = new GameMechanicsRules();

  serverad = servad;

  numPlayers = numAI = numObs = numtotalplayers = endgame = whichplayer = 0;
  
  timeval tm;
  gettimeofday(&tm, NULL);
  starttime = tm.tv_sec;

  oldtime = 0.0;

  runClient();
}


// Destructor

Gameboard::~Gameboard ( void ) {
  delete userPlayers;
  delete aiPlayers;
  delete observerList;
  delete chatWindow;
  delete sidebar;
  delete socket;
  userPlayers = 0;
  aiPlayers = 0;
  observerList = 0;
  chatWindow = 0;
  sidebar = 0;
  socket = 0;
}





