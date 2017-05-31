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

	Limited Depth Buffer Avoidence
		Just like the heading suggests, I am working around the depth buffer now
		Since so many things can hinder the performance of the game on UGCS, I might as
		well move as many things OFF of the graphics processing as possible, one of these
		things of course, is the depth buffer, the only consequence is that the list has to
		be traversed twice, but I bet there is some cool stl device that I can use to
		get around that if it becomes a problem.  Perhaps another map with ghosts and
		pacmen as the key's?
	

*/

// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "playerlist.h"
#include "drawableobject.h"

//TODO
//put functions in to change the 'gender' of a player to a ghost
//to a pacman or vice versa.
//that would be easier and cleaner than just making new classes for 
//all the players during the games where you can change this.

extern int myID;

//return value used by PlayerList
typedef pair <int , Player *> PlayerPair;

//move the coord system and draw the players in their places
//put something in here to draw pacmen first, then move the coord system up and
//draw the ghosts.
//the pacmen and ghosts also should be drawn in order because they use alpha blending
//this could get tricky...I'll have to look at it in more detail when the level system
//is working, but it could get very tricky.
//a possible solution would be to make the depth buffer read only when writing to the
//system, such that the ghosts or pacman wouldn't draw if it was behind a level.
void PlayerList::draw()
{
	glPushMatrix();

	//this player's pacman should always be in the center of the screen.
	//I need to add something that sets up the system around this feature...


	//this is just temporary to demonstrate the players, should be taken out!!
//	glTranslatef(-20, 0, 0);

	map <int, Player*>::iterator i;

	//first get the player using the player ID
	Player * drawplayer = getPlayer(myID);
	//move the coord system over to their spot, so that they're in the center
	glTranslatef(0, 0, 0);
	//draw them
	drawplayer->draw();


	//step through the map and draw the pacmen first, they have to be under the ghosts
	for(i = PlayerMap.begin(); i != PlayerMap.end(); i++)
	{
		drawplayer = i->second;

		if(!drawplayer->isAGhost() && drawplayer->getPlayerID() != myID)
		{
			//this is just temporary to demonstrate the players, should be changed!!
			//right here we need to move the coord system to where they are...
			glTranslatef(7, 0, 0);

			drawplayer->draw();
		}

	}

	//step through the map and draw the ghosts
	for(i = PlayerMap.begin(); i != PlayerMap.end(); i++)
	{
		drawplayer = i->second;

		if(drawplayer->isAGhost() && drawplayer->getPlayerID() != myID)
		{
			//this is just temporary to demonstrate the players, should be changed!!
			//right here we need to move the coord system to where they are...
			glTranslatef(7, 0, 0);

			drawplayer->draw();
		}

	}


	glPopMatrix();
}

int PlayerList::getNumPlayers(void)
{
	return PlayerMap.size();
}

//need a function to remove a player from the game.
//Just take them out of the array using their id (index) and shift everything down
int PlayerList::removeplayer(int playerid)
{
	bool success = false;

	//see if the player ID exists in the map
	if(PlayerMap.erase(playerid) == 1)
	{
		//if so we successfully deleted them
		success = true;
	}

	//return whether or not we deleted someone
	return success;
}

// creates and adds a new Player object to the array and returns 
// the ID.  The IPaddress can be void if it's an AI player. 
int PlayerList::addplayer(string name, int playerpicid, PacSkin * tex, bool isGhost, char* IPaddress, int wantedID)
{

//	int newplayer;//make a new pacman
	Player* newplayer;

	//Player ID
	//zero if failure, 
	//this works as a flag too because a player id can never be 0
	int retID = 0; 

	if(!isGhost)
	{
		Pacman *pacman;
		pacman=new Pacman(name, playerpicid, tex, IPaddress);
		newplayer = pacman;
	}
	else
	{
		//add a random thing right here to pick the ghost's colour
		unsigned int color= 0xFF0000;

		Ghost *ghost;
		ghost=new Ghost(name, playerpicid, color, IPaddress);
		newplayer = ghost;
	}


	//this code was all duplicated in the addPlayer(ptr) function so I took it out and
	//passed the same pointer on to the addplayer function with a ready built player
	//I knew we'd find a purpose for that ^_^
	retID = addplayer(newplayer, wantedID);

	return retID;
}



// adds a player to the list from a ready made player object 
// we can just add them using their pointer because every object
// has it's own draw method and an AreYouAGhost method
int PlayerList::addplayer(Player * newplayer, int wantedID) 
{
	int retID = 0; //zero if failure, this works as a flag too

	//code from above, it could be placed in the add function that takes a myriad of
	//parameters, but it's always good to have an extra function like this incase
	//we do need to add pacmen like this
	map <int, Player*> :: const_iterator retpair;

	//if the server hasn't given us an ID, this is unlikely
	if(wantedID == 0)
	{
		//loop through possible ID numbers until we find one that isn't taken
		for(int i = 1; ;i++)
		{
			retpair = PlayerMap.find(i);
	
			if(retpair == PlayerMap.end())
			{
				//then the index was NOT found, that means the ID number is free
				retID = i;
				break;
			}
		}
	}
	else //we need to set the ID on our own
	{
		//search for it first		
		retpair = PlayerMap.find(wantedID);

		if(retpair == PlayerMap.end())
		{
			//then the index was NOT found, that means the ID number is free
			retID = wantedID;
		}
		else
		{
			 retID = 0;
		}
	}
			

	if(retID != 0)
	{
		//set the player's ID
		newplayer->setPlayerID(retID);

		//insert them into the map
		PlayerMap.insert( PlayerPair(retID, newplayer) );
	}

	//return the ID of this player
	return retID;
}


//getplayer returns a pointer to the player with a given ID, I haven't found a use for
//it yet, but I'm sure there will be one
Player * PlayerList::getPlayer(int playerid, int * index)
{
	Player * retptr = NULL; //if not found return NULL

	map <int, Player*>::const_iterator retpair;

	retpair = PlayerMap.find(playerid);

	if(retpair != PlayerMap.end())
	{
		//then the index WAS found, so

		//set the return pointer
		retptr = retpair->second;

		//if the index pointer is not NULL, fill it in too
		if(index != NULL)
		{
			*index = retpair->first;
		}
	}

	return retptr;
}

//return a copy of the current player map, in case any thing else needs to step through the players
map<int, Player*>* PlayerList::getPlayerMap(void)
{
	map<int, Player*>* returnmap = new map<int, Player*>;
	(*returnmap) = PlayerMap;

	return returnmap;
}


bool PlayerList::onSameZLevel(int playerID1, int playerID2)
{
	bool retval = false;
	if(getPlayer(playerID1)->getZ() == getPlayer(playerID2)->getZ())
	{
		//then they are on the same floor, return true
		retval = true;
	}
	return retval;
}

//returns the X distance separating two players
GLfloat PlayerList::getXSep(int playerID1, int playerID2)
{
	GLfloat retval = 0;
	retval = getPlayer(playerID1)->getX() - getPlayer(playerID2)->getX();
	if(retval <0)
	{
		retval*=-1;
	}
	return retval;
}

//returns the Y distance separating two players
GLfloat PlayerList::getYSep(int playerID1, int playerID2)
{
	GLfloat retval = 0;
	retval = getPlayer(playerID1)->getY() - getPlayer(playerID2)->getY();
	if(retval <0)
	{
		retval*=-1;
	}
	return retval;
}



// Constructor(s)
PlayerList::PlayerList()
{
	PlayerMap.empty();
}



// Destructor

PlayerList::~PlayerList ( void ) 
{
	PlayerMap.empty();
	
}


