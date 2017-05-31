#include <iostream>
#include "GameBoard.h"
#include "GameServer.h"
#include "Level.h"
#include "TCP.h"
#include "RUDP.h"
#include "network.h"

OpenGL opengl;
PlayerList playerlist;
int myID;
TCP* tcp = NULL;
RUDP* rudp = NULL;
ChatWnd chatwnd;
Level testlevel(50, 50, 1, 4, 4);

int main()
{
  sockaddr_in *servad;
  servad = 0;
  Level *level;
  cout << "generating level\n";
  level = new Level(20, 20, 1, 3, 3);
  cout << "level ready\n";
  Gameboard *theGame;
  cout << "starting game\n";
  theGame = new Gameboard(level, servad);
}
