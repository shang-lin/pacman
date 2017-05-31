#include <iostream>
#include <string>
#include "image.h"
#include "opengl.h"
#include "playerlist.h"
#include "pacskin.h"

//simple test program.  It's important that the objects be initialized in this order
//because some of the initialzation steps that player list goes through
//won't work it opengl itself has not been initialized yet
OpenGL opengl;
PlayerList playerlist;
int myID;

int main(int argc,char* argv[])
{
	//test skin object.  It's easiest to make these and then pass them into the addplayer function
	PacSkin tex("pacskin.bmp");
	int pac = playerlist.addplayer("pac YOU", 0, &tex, 0, NULL, 1);
	int ghost = playerlist.addplayer("ghost", 0, NULL, 1, NULL, 30);
	int ghost2 = playerlist.addplayer("ghost 2", 0, NULL, 1, NULL, 4);
	playerlist.removeplayer(ghost2);

	int ghost3 = playerlist.addplayer("ghost 3", 0, NULL, 1, NULL, 8);
	int pac2 = playerlist.addplayer("pac2 your friend", 0, NULL);
	int ghost4 = playerlist.addplayer("ghost 4", 0, NULL, 1, NULL, 80);

	playerlist.getPlayer(pac)->changeScore(123456789);
	playerlist.getPlayer(ghost)->changeScore(12345678);
	playerlist.getPlayer(pac2)->changeScore(1234567);
	playerlist.getPlayer(ghost3)->changeScore(123);
	playerlist.getPlayer(ghost4)->changeScore(12345);

	playerlist.getPlayer(pac)->SetXYZ(12, 20, 0);
	playerlist.getPlayer(ghost)->SetXYZ(32, 30, 0);
	playerlist.getPlayer(pac2)->SetXYZ(17, 40, 0);
	playerlist.getPlayer(ghost3)->SetXYZ(0, 5, 0);
	playerlist.getPlayer(ghost4)->SetXYZ(.45, 30, 0);

	((Ghost*)playerlist.getPlayer(ghost))->setColor(0x1111FF);


	myID = pac;
	cout<<pac<<endl<<ghost<<endl<<ghost2<<endl<<ghost3<<endl<<pac2<<endl<<ghost4<<endl<<myID<<endl;

	opengl.StartMainLoop();

	return 0;
}
