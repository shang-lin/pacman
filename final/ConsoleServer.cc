/**
 * Arguments : <tcp port> <rudp port>
 **/

#include <iostream>
#include <map>
#include <sys/time.h>
#include "TCP.h"
#include "TCPServer.h"
#include "RUDP.h"
#include "playerlist.h"
#include "chatwnd.h"
#include "Level.h"
#include "FileException.h"

using namespace std;

#define MAX_PLAYERS 6

OpenGL opengl;
PlayerList playerlist;
int myID;
TCP* tcp;
RUDP* rudp = NULL;
ChatWnd chatwnd;
Level* testlevel;
UDPacket* outpacket;
pthread_mutex_t graphicsMutex;

//Variables from the ServerLoop function
bool cedible = false;
int cediblecount = 0;
long startMS,ms;
int loopCount = 0;

void ConsoleServerLoop();

int main(int argc,char* argv[]){
	int i,j,k;
	int tport = 0;
	int rport = 0;
	TCPServer* serv = NULL;
	TCP* connections[MAX_PLAYERS+1];
	bool notStarted = true;
	int numPlayers = 0;
	const string* message;

	if(argc != 3 && argc!=4){
		cerr << "Usage : <tcp port> <rudp port> [levelfile]\n";
		exit(0);
	}
	
	try{
	  try{
	    if (argc==4){
	      testlevel = new Level(string(argv[3]));
	    }
	    else{
	      //testlevel = new Level(string("testlevel.txt"));
		testlevel = new Level(60,60,2,10,6);
	    }
	  }
	  catch (FileException f){
	        cerr<<"Error in level: "<<endl;
	        f.print(cerr);
	        exit(1);
	  }
		tport = atoi(argv[1]);
		serv = new TCPServer(tport);
		cerr << "The tcp server is waiting on port " << tport << "\n";
		rport = atoi(argv[2]);
		rudp = new RUDP(rport);
		for(i=0;i<MAX_PLAYERS+1;i++){
			connections[i] = NULL;
		}

		timeval tv;
		gettimeofday(&tv,NULL);
		startMS = tv.tv_sec * 1000 + tv.tv_usec/1000;
		while(notStarted || numPlayers != 0){
			gettimeofday(&tv,NULL);
			ms = tv.tv_sec * 1000 + tv.tv_usec/1000 - startMS;
			//cerr << "time : " << ms << "       \r";
			if(serv->isReady()){
				tcp = serv->acceptTCP();
				if(numPlayers == MAX_PLAYERS){
					cout << "Connection attempted, but we're all full\n";
					delete tcp;
				} else {
					char temp[1024];
					string toSend = "";

					////Handshaking

					cerr << "Get name of new player\n";
					// Get the name of this new player and whether he wants to be ghost
					message = tcp->getString();

					cerr << "Add new player to the player list\n";
					// Add new player to the player list
					i = playerlist.addplayer(
						message->substr(0,message->length()-1),
						0,NULL,
						atoi(message->substr(message->length()-1,1).c_str())
					);
					Player* tempplayer = playerlist.getPlayer(i);
					if(tempplayer->isAGhost()){
						((Ghost*)tempplayer)->changePosition(testlevel->getGhostStart());
					} else {
						((Pacman*)tempplayer)->changePosition(testlevel->getPacmanStart());
					}
					connections[i] = tcp;
					/*
					cout << "Added player " << i 
					     << " with name :" << message->substr(0,message->length()-1)
							 << ": and isAGhost of " 
							 << atoi(message->substr(message->length()-1,1).c_str())
							 << "\n";
					*/

					cerr << "Give new player his id number\n";
					//Give new player his id number
					sprintf(temp,"%i",i);
					toSend = string(temp);
					tcp->sendString(&toSend);

					cerr << "Receive acknowledge\n";
					// Receive acknowledge
					delete message;
					message = tcp->getString();

					cerr << "Give new player a list of all current players\n";
					//Give new player list of all current players
					toSend = "";
					map<int, Player*>* listmap = playerlist.getPlayerMap();
					for(map<int, Player*>::iterator it=listmap->begin();
					    it != listmap->end();
							it++){
						Player* p = it->second;
						sprintf(
							temp,
							"%i %s %i ",
							it->first,
							p->getName().c_str(),
							p->isAGhost() ? 1 : 0
						);
						toSend += string(temp);
					}
					tcp->sendString(&toSend);

					cerr << "Receive acknowledge\n";
					// Receive acknowledge
					delete message;
					message = tcp->getString();

					cerr << "Send new player info to all current players\n";
					//Give all current players data about new player
					map<int, Player*>::iterator it = listmap->find(i);
					Player* p = it->second;
					toSend = "a";
					sprintf(
						temp,
						"%i %s %i ",
						it->first,
						p->getName().c_str(),
						p->isAGhost() ? 1 : 0
					);
					toSend += string(temp);
					for(map<int, Player*>::iterator it=listmap->begin();
							it != listmap->end();
							it++){
						if(it->first != i){
							connections[it->first]->sendString(&toSend);
						}
					}

					cerr << "Send level data\n";
					//Send level data
					//Send a string for width
					int width = testlevel->getWidth();
					int length = testlevel->getLength();
					int floors = testlevel->getFloors();
					sprintf(temp,"%i",width);
					toSend = string(temp);
					tcp->sendString(&toSend);

					cerr << "Receive acknowledge\n";
					// Receive acknowledge
					delete message;
					message = tcp->getString();

					//Send a string for length
					sprintf(temp,"%i",length);
					toSend = string(temp);
					tcp->sendString(&toSend);

					cerr << "Receive acknowledge\n";
					// Receive acknowledge
					delete message;
					message = tcp->getString();

					//Send a string for floors
					sprintf(temp,"%i",floors);
					toSend = string(temp);
					tcp->sendString(&toSend);

					cerr << "Receive acknowledge\n";
					// Receive acknowledge
					delete message;
					message = tcp->getString();

					//Send length*floors strings for each row
					for(i=0;i<floors;i++){
						for(j=0;j<length;j++){
							for(k=0;k<width;k++){
								Space* spc = testlevel->getSpace(k,j,i);
								if (spc){
								  temp[k] = spc->getItemKey();
								} else {
								  temp[k] = ' ';
								}
							}
							temp[width]=0;
							toSend = string(temp);
							cerr << "sending level ... " << toSend << "\n";
							tcp->sendString(&toSend);

							cerr << "Receive acknowledge\n";
							// Receive acknowledge
							delete message;
							message = tcp->getString();

						}
					}
					
					//Send RUDP port of Server
					sprintf(temp,"%i",rport);
					toSend = string(temp);
					//cout << "About to send my RUDP port number\n";
					tcp->sendString(&toSend);

					//Get RUDP port of Client
					delete message;
					//cout << "About to read the port of the client\n";
					message = tcp->getString();
					int clientPort = atoi(message->c_str());

					//Get hostname of client
					delete message;
					//cout << "About to get the hostname of the client\n";
					message = tcp->getString();
					//cout << "Got the hostname of the client :" << *message << "\n";
					
					//Make the UDPacket to store this info in
					UDPacket* packet = new UDPacket();
					cerr << "clientPort is " << clientPort << " and address is " << *message << "\n";
					packet->setAddress(*message,clientPort);

					p->setUDPacket(packet);

					//Send the current time
					gettimeofday(&tv,NULL);
					long currTimeMS = tv.tv_sec * 1000 + tv.tv_usec/1000 - startMS;
					sprintf(temp,"%d",currTimeMS);
					toSend = string(temp);
					//cout << "About to send the server time :" << toSend << ":\n";
					tcp->sendString(&toSend);
					//cout << "Sent the server time\n";

					////Done Handshaking

					numPlayers++;
					notStarted = false;
					cout << "New connection : Player " << i << "\n";
					delete message;
				}
			}
			for(i=1;i<MAX_PLAYERS+1;i++){
				if(connections[i] != NULL && connections[i]->isReady()){
					try{
						message = connections[i]->getString();
						cout << "Message from player " << i << " : " << *message << "\n";
						for(j=1;j<MAX_PLAYERS+1;j++){
							if(connections[j] != NULL){
								connections[j]->sendString(message);
							}
						}
						delete message;
					} catch(SocketIOException sioe){
						cout << "Player " << i << " left the game\n";
						char temp[32];
						sprintf(temp,"r%i",i);
						message = new string(temp);
						for(j=1;j<MAX_PLAYERS+1;j++){
							if(connections[j] != NULL){
								connections[j]->sendString(message);
							}
						}
						delete message;
						playerlist.removeplayer(i);
						delete connections[i];
						numPlayers--;
						connections[i] = NULL;
					}
				}
			}
			//FIXIT : check for incoming RUDP packets
			while(rudp->isReady()){
				UDPacket* inpacket = new UDPacket();
				rudp->receivePacket(inpacket);
				const byte* data = inpacket->getData();
				int length = inpacket->getLength();
				//cerr << "Recv : " << length << " " << (char)data[0] << "\n";
				switch(data[0]){
					case 'k': // 'k' (long)timestamp (byte)id (glenum)GLUT_KEY_*
						switch(*((GLenum*)(data+sizeof(long)+2))){
							case GLUT_KEY_DOWN:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(4);
								break;
							case GLUT_KEY_RIGHT:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(3);
								break;
							case GLUT_KEY_UP:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(2);
								break;
							case GLUT_KEY_LEFT:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(1);
								break;
							case GLUT_KEY_PAGE_UP:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(5);
								break;
							case GLUT_KEY_PAGE_DOWN:
								playerlist.getPlayer(data[sizeof(long)+1])->setIntended(6);
								break;

							default:
								break;
						}
						break;
				}
				delete inpacket;
			}
			ConsoleServerLoop();
		}

		delete rudp;
		delete serv;
	} catch(NetworkException e){
		cerr << e << "\n";
		delete rudp;
		delete serv;
		exit(0);
	}
}

//THINGS THAT NEED TO BE SENT TO THE CLIENT:
//Changes in edibleness (reliable)
//Change in score (reliable)
//Change in death (reliable)
//Change Space to have no item (reliable)
//Moving players position (unreliable)

//this function is used for a collision with a ghost!
void ConsoleCollision(Player * tempplayer, Player * otherguy)
{

	//if the tempplayer is a pacman and the otherguy is a ghost
	if(!tempplayer->isAGhost() && otherguy->isAGhost())
	{	

		//make a temp ghost*
		Ghost * tempghost = (Ghost*)otherguy;

		//make a temp pacman*
		Pacman * temppacman = (Pacman*)tempplayer;

		//if the ghost is not dead
		if(!tempghost->isDead())
		{
			//eat the ghost if it is edible, or else kill the pacman
			if(tempghost->isEdible() && !tempghost->isDead())
			{
				//kill the ghost
				cout<<"eat the ghost first"<<endl;
				
				//award points too
				temppacman->changeScore(1000);
				tempghost->setDead(150);
			}
			//if pacman isn't already dead, eat him here
			else if(!temppacman->isDead())
			{
				//kill the pacman
				cout<<"kill the pacman second"<<endl;
				
				//award points too
				tempghost->changeScore(500);
				temppacman->setDead();
			}
		}
		
	}

	//if the tempplayer is a ghost and the otherguy is a pacman
	else if(tempplayer->isAGhost() && !otherguy->isAGhost())
	{
		//make a temp ghost*
		Ghost * tempghost = (Ghost*)tempplayer;
		
		//make a temp pacman*
		Pacman * temppacman = (Pacman*)otherguy;
		

		//if the ghost is not dead
		if(!tempghost->isDead())
		{
			//eat the pacman if the ghost is not edible, or else kill the ghost
			if(tempghost->isEdible() && !tempghost->isDead())
			{
				//kill the ghost
				cout<<"eat the ghost third, he's edible"<<endl;

				//award points too
				otherguy->changeScore(1000);
				tempghost->setDead(150);
			}
			//if pacman isn't already dead, eat him here
			else if(!temppacman->isDead())
			{
				//kill the pacman
				cout<<"kill the pacman forth"<<endl;
				
				//award points too
				tempghost->changeScore(100);
				temppacman->setDead();
			}
		}
	}

/*

	//if the tempplayer is a pacman and the otherguy is a ghost
	if(!tempplayer->isAGhost() && otherguy->isAGhost())
	{	

		//make a temp ghost*
		Ghost * tempghost = (Ghost*)otherguy;

		//if the ghost is not dead
		if(!tempghost->isDead())
		{
			//eat the ghost if it is edible, or else kill the pacman
			if(tempghost->isEdible() && !tempghost->isDead())
			{
				//kill the ghost
				cout<<"eat the ghost first"<<endl;
				
				//award points too
				tempplayer->changeScore(1000);
				tempghost->setDead(150);
			}
			else
			{
				//kill the pacman
				cout<<"kill the pacman second"<<endl;
			}
		}
		
	}

	//if the tempplayer is a ghost and the otherguy is a pacman
	else if(tempplayer->isAGhost() && !otherguy->isAGhost())
	{
		//make a temp ghost*
		Ghost * tempghost = (Ghost*)tempplayer;

		//if the ghost is not dead
		if(!tempghost->isDead())
		{
			//eat the pacman if the ghost is not edible, or else kill the ghost
			if(tempghost->isEdible() && !tempghost->isDead())
			{
				//kill the ghost
				cout<<"eat the ghost third, he's edible"<<endl;

				//award points too
				otherguy->changeScore(1000);
				tempghost->setDead(150);
			}
			else
			{
				//kill the pacman
				cout<<"kill the pacman forth"<<endl;
			}
		}
	}
	*/
}

void ConsoleServerLoop()
{
	struct timespec to_wait;
	to_wait.tv_sec = 0;
	to_wait.tv_nsec = 12000000; //12 million nanoseconds = 12 milliseconds
	nanosleep(&to_wait,NULL);

        map <int, Player*>::iterator i,j;   
        map <int, Player*> * tempplayermap = playerlist.getPlayerMap();

	//cout<<"begin server loop"<<endl;
	if(cedible)
	{
		cediblecount++;
		if(cediblecount == 75)
		{
			playerlist.resetGhostsEdible();	
			cediblecount = 0;
			cedible = false;
			for(j = tempplayermap->begin();j != tempplayermap->end();j++){
				//FIXIT : send each player j the non edible packet
				//n 
			}
		}
	}

	//loop through all of the players each time
        for(i = tempplayermap->begin(); i != tempplayermap->end(); i++)
        {
                Player * tempplayer;
                tempplayer = i->second;



		/*
		//temp stuff for emulating other players
		if(tempplayer->getPlayerID() != myID)
		{
			if(tempplayer->getDirection() == 0)
			{
				tempplayer->setIntended(randomdir);
				randomdir++;
				if(randomdir == 5)
					randomdir = 1;
			} 
		}
		*/




		//first off, if you're a ghost, check your death counter to see if you need
		//to be brought back
		if(tempplayer->isAGhost())
		{
			Ghost * tempghost = (Ghost*)tempplayer;
			//if they're dead
			if(tempghost->isDead())
			{
				//try decrementing their death counter
				if(tempghost->decDeadCount())
				{
					tempghost->resetDead();
					//cout<<"reset dead in server loop"<<endl;
				}
			}
			//if they're not dead and not edible
			else if(!tempghost->isEdible())
			{
				//give them some points
				tempghost->changeScore(1);
			}
		}

		//if you're a pacman, check to see if you're dead
		if(!tempplayer->isAGhost())
		{
			Pacman * temppacman = (Pacman*)tempplayer;

			//if they're dead, check their deadcounter
			if(temppacman->isDead())
			{
				//try decrementing their death counter
				if(temppacman->decDeadCount())
				{
					cout<<"dead count returned true"<<endl;
				}
				else
				{
					//else, make the pacman hold still
					temppacman->setDir(0);
					temppacman->setIntended(0);			
				}
			}
			
		}


		int idir = tempplayer->getIntended();
		int dir = tempplayer->getDirection();

		//if(tempplayer->getPlayerID() == 2)
			//cout<<"1 dir and idir "<<dir<<", "<<idir<<endl;

		Space * tempspace = tempplayer->getSpace();

		//check to see if they are at an intersection first.
		//that is, if their x and y coords are divisible by 6
		if( ((int)tempplayer->getX())%6 == 0 && ((int)tempplayer->getY())%6 == 0)
		{


			//they are at an intersection

			//the player is already in the middle of the space
			//so they get the item, look to see what the item 
			//is
			bool isghost = tempplayer->isAGhost();
			char item = tempspace->getItemKey();


			//now, since they are in an intersection
			//check for any stuff in the space, and eat it
			//this does not include other players
			if(item == '.' && !isghost)
			{
				//cout<<"found a pill"<<endl;
				//item is a pill, pacman should eat it

				//eat the item by changing his score
				tempplayer->changeScore(100);
				//changeScore increments his score

				//remove the item
				tempspace->removeItem();
				
				byte packet_data[1024];
				int pos = 0;
				*(packet_data+pos) = 'g'; pos++;
				*((int*)(packet_data+pos)) = tempspace->getX(); pos+=sizeof(int);
				*((int*)(packet_data+pos)) = tempspace->getY(); pos+=sizeof(int);
				*((int*)(packet_data+pos)) = tempspace->getZ(); pos+=sizeof(int);
				
				for(j = tempplayermap->begin();j != tempplayermap->end();j++){
					//FIXIT : Send packet for this item is gone
					//g index_of_space
					UDPacket* packet = j->second->getUDPacket();
					packet->setData(packet_data,pos);
					rudp->sendReliable(packet);
				}
			}
			else if(item == '*' && !isghost)
			{
				//cout<<"found a power pill"<<endl;
				//item is a power pill, pacman eats it
				//eat the item by changing all of the
				//ghosts to Edible with SetEdible
				//this should actually be a function in
				//playerlist...I'll do that
				playerlist.setGhostsEdible();
				
				//there needs to be a timer that resets
				//the ghosts' edible bool
				cedible = true;
				cediblecount = 0;

				//remove the item
				tempspace->removeItem();
				byte packet_data[1024];
				int pos = 0;
				*(packet_data+pos) = 'g'; pos++;
				*((int*)(packet_data+pos)) = tempspace->getX(); pos+=sizeof(int);
				*((int*)(packet_data+pos)) = tempspace->getY(); pos+=sizeof(int);
				*((int*)(packet_data+pos)) = tempspace->getZ(); pos+=sizeof(int);
				
				for(j = tempplayermap->begin();j != tempplayermap->end();j++){
					//FIXIT : Send packet for this item is gone
					//g index_of_space
					UDPacket* packet = j->second->getUDPacket();
					packet->setData(packet_data,pos);
					rudp->sendReliable(packet);
				}
			}

			//if they want to go the same way, throw a flag
			bool sameway = false;
			if(idir == dir)
				sameway = true;

			//if their current direction hits a wall
			bool hitsWall = true;
			char dirC = 'w';
			switch(dir){
				case 2:
					dirC = 'n';
					break;
				case 3:
					dirC = 'e';
					break;
				case 4:
					dirC = 's';
					break;
				case 5:
					dirC = 'u';
					break;
				case 6:
					dirC = 'd';
					break;
			}
			if(tempspace->getNeighbor(dirC)){
				hitsWall = false;
			}

			//and see if there is a neighbor in that direction
			//change dir
			switch(idir)
			{
			case 1:
				if(tempspace->getNeighbor('w'))
				{
					tempplayer->setDir(idir);
				}
				else
				{
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}

				}
		
				break;
			case 2:
				if(tempspace->getNeighbor('n'))
				{
					tempplayer->setDir(idir);
					//cout<<"yup, there's an north neighbor"<<endl;
				}
				else
				{
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}
				}
				break;
			case 3:
				if(tempspace->getNeighbor('e'))
				{
					tempplayer->setDir(idir);
					//cout<<"yup, there's a right neighbor"<<endl;
				}
				else
				{
					//cout<<"nope no right neighbor"<<endl;
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}

				}
				break;
			case 4:
				if(tempspace->getNeighbor('s'))
				{
					tempplayer->setDir(idir);
					//cout<<"yup, there's a south neighbor"<<endl;
				}
				else
				{
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}
				}
				break;
			case 5:
				if(tempspace->getNeighbor('u'))
				{
					tempplayer->setDir(idir);
					//cout<<"yup, there's an up neighbor"<<endl;
				}
				else
				{
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}
				}
				break;
			case 6:
				if(tempspace->getNeighbor('d'))
				{
					tempplayer->setDir(idir);
					//cout<<"yup, there's a down neighbor"<<endl;
				}
				else
				{
					if(sameway || hitsWall)
					{
						//make them stop because they are running into a wall
						tempplayer->setDir(0);
						tempplayer->setIntended(0);
					}
				}
				break;
			default:
				break;
			}
	

			//finally reset dir and idir so we know where we're going
			idir = tempplayer->getIntended();
			dir = tempplayer->getDirection();

			//if(tempplayer->getPlayerID() == 2)
			//cout<<"dir and idir before collisions "<<dir<<", "<<idir<<endl;


		}
		//else if they are not at an intersection
		else
		{

			//if they aren't at an intersection, they're probably reversing directions
			//or starting again after a collision, so just check to see which coord
			//is not divisible by 6
			if((idir == 1) || (idir == 3))
			{
				//if they're between two horizontal spaces, let them change
				if( ((int)tempplayer->getX())%6 != 0 ) 
				{
					tempplayer->setDir(idir);
					dir = idir;
				}
			}
			else if( (idir == 2 || idir == 4))
			{
				//if they're between two vertical spaces, let them change
				if( ((int)tempplayer->getY())%6 != 0 ) 
				{
					tempplayer->setDir(idir);
					dir = idir;
				}
				
			}

		}

		//check for collisions here...this is where pacmen eat ghosts and vice versa
	        map <int, Player*>::iterator j;

		//loop through all the other players
		for(j = tempplayermap->begin(); j != tempplayermap->end(); j++)
		{
			
			Player * otherguy = j->second;
			int thisID = tempplayer->getPlayerID();
			int hisID = otherguy->getPlayerID();

			//don't compare against yourself, or with guys on different levels
			if(otherguy != tempplayer && playerlist.onSameZLevel(thisID, hisID))
			{

				GLfloat xsep = playerlist.getXSep(thisID, hisID);
				GLfloat ysep = playerlist.getYSep(thisID, hisID);
	
				//if(tempplayer->getPlayerID() == 2)
				//cout<<"thisID, hisID, xsep, ysep: "<<thisID<<", "<<hisID<<", "<<xsep<<", "<<ysep<<endl;

				//if(tempplayer->getPlayerID() == 2)
				//cout<<"3 dir and idir "<<dir<<", "<<idir<<endl;

				switch(dir)
				{
				case 1: //you're moving left
					if(xsep <= 3 && xsep > 0 &&  ysep == 0)
					{
						//collision, do something
						//cout<<"this ID: "<<thisID<<endl;

						//cout<<"collision dir 1 idir:"<<idir<<endl;
						//if they are both pacmen, stop this one...this could be booled out
						if(!tempplayer->isAGhost() && !otherguy->isAGhost())
						{
							//stop myself here
							tempplayer->setDir(0);
							dir = 0;

							//but let him go the other way
							if(idir == 3)
							{
								//cout<<"direction set for 3"<<endl;
								tempplayer->setIntended(3);
								tempplayer->setDir(3);
								dir = 3;
							}
						}
						ConsoleCollision(tempplayer, otherguy);
						
					}
					break;
				case 2:
					if(ysep >= -3 && ysep < 0 &&  xsep == 0)
					{
						//collision, do something
						//cout<<"collision"<<endl;
						
						//if they are both pacmen, stop them...this could be booled out
						if(!tempplayer->isAGhost() && !otherguy->isAGhost())
						{
							//stop myself here
							tempplayer->setDir(0);
							dir = 0;

							//but let them go the other way
							if(idir == 4)
							{
								tempplayer->setIntended(4);
								tempplayer->setDir(4);
								dir = 4;
							}
						}
						ConsoleCollision(tempplayer, otherguy);
					}
					break;
				case 3:	
					if(xsep >= -3 && xsep < 0 &&  ysep == 0)
					{
						//collision, do something
						//cout<<"collision"<<endl;
						
						//if they are both pacmen, stop them...this could be booled out
						if(!tempplayer->isAGhost() && !otherguy->isAGhost())
						{
							//stop myself here
							tempplayer->setDir(0);
							dir = 0;

							//but let them go the other way
							if(idir == 1)
							{
								tempplayer->setIntended(1);
								tempplayer->setDir(1);
								dir = 1;
							}
						}
						ConsoleCollision(tempplayer, otherguy);
					}
					break;
				case 4:
					if(ysep <= 5 && ysep > 0 &&  xsep == 0)
					{
						//collision, do something
						//cout<<"collision"<<endl;
						
						//if they are both pacmen, stop them...this could be booled out
						if(!tempplayer->isAGhost() && !otherguy->isAGhost())
						{
							//stop myself here
							tempplayer->setDir(0);
							dir = 0;

							//but let them go the other way
							if(idir == 2)
							{
								tempplayer->setIntended(2);
								tempplayer->setDir(2);
								dir = 2;
							}
						}
						ConsoleCollision(tempplayer, otherguy);
					}

					break;
				default:
					break;
				}
			}
		}		
		





		//move the player here
		GLfloat move = 2;

		//if they're an edible and not dead ghost, use a different movement unit
		//make a temp ghost*
		if(tempplayer->isAGhost())
		{
			Ghost * tempghost = (Ghost*)tempplayer;

			//if the ghost is not dead
			if(tempghost->isEdible() && !tempghost->isDead())
			{
				move = 1.5;
			}
		}
		

		//cout<<"about to move player "<<tempplayer->getPlayerID()<<" in direction: "<<dir<<endl;
		switch(dir)
		{
		case 1:
			tempplayer->SetX(tempplayer->getX()-move);
			break;
		case 2:
			tempplayer->SetY(tempplayer->getY()+move);
			break;
		case 3:
			tempplayer->SetX(tempplayer->getX()+move);
			break;
		case 4:
			tempplayer->SetY(tempplayer->getY()-move);
			break;
		case 5:
			tempplayer->SetZ(tempplayer->getZ()+1);
			tempplayer->setIntended(1);
			tempplayer->setDir(0);

			//reset space UP!!
			tempplayer->changePosition(tempspace->getNeighbor('u'));
			break;
		case 6:
			tempplayer->SetZ(tempplayer->getZ()-1);
			tempplayer->setIntended(1);
			tempplayer->setDir(0);

			//reset space DOWN!!
			tempplayer->changePosition(tempspace->getNeighbor('d'));
			break;
		default:
			break;
		}

		//if the player's X and Y coords are greater than 6 units away from the space that they should be
		//occupying, put them in the new space and leave their coords alone
		GLfloat spacex = tempspace->getX()*6;
		GLfloat spacey = tempspace->getY()*-6;
		GLfloat x = tempplayer->getX();
		GLfloat y = tempplayer->getY();

		GLfloat xdiff = spacex - x;
		GLfloat ydiff = spacey - y;

		if(xdiff >= 6 || xdiff <=-6 || ydiff >= 6 || ydiff <=-6)
		{
			//set player's Space * to a neighboring pointer
			//cout<<"x and y diffs: "<<xdiff<<", "<<ydiff<<endl;
			if(xdiff >= 6)
			{
				tempplayer->changePosition(tempspace->getNeighbor('w'));
				//cout<<"reset space west"<<endl;
			}
			else if(xdiff <= -6)
			{
				tempplayer->changePosition(tempspace->getNeighbor('e'));
				//cout<<"reset space east"<<endl;
			}
			else if(ydiff >= 6)
			{
				tempplayer->changePosition(tempspace->getNeighbor('s'));
				//cout<<"reset space south"<<endl;
			}
			else if(ydiff <= -6)
			{
				tempplayer->changePosition(tempspace->getNeighbor('n'));
				//cout<<"reset space north"<<endl;
			}
			

			//after the Space * has been set, set the coords of pacman equal to his new space
			Space * newspace = tempplayer->getSpace();
			tempplayer->SetX( newspace->getX()*6);
			tempplayer->SetY( newspace->getY()*-6);
			
		}
		//FIXIT : Send a player update packet
		//'p' timestamp pID x_float y_float z_int intend_dir dir alive_dead_edible
		//alive = 0
		//dead = 1
		//edible = 2
		byte packet_data[1024];
		int pos = 0;
		*(packet_data+pos) = 'p'; pos++;
		*(packet_data+pos) = (byte)(tempplayer->getPlayerID()); pos++;
		*((long*)(packet_data+pos)) = ms; pos+=sizeof(long);
		*((GLfloat*)(packet_data+pos)) = tempplayer->getX(); pos+=sizeof(GLfloat);
		*((GLfloat*)(packet_data+pos)) = tempplayer->getY(); pos+=sizeof(GLfloat);
		*((GLfloat*)(packet_data+pos)) = tempplayer->getZ(); pos+=sizeof(GLfloat);
		*((int*)(packet_data+pos)) = tempplayer->getScore(); pos+=sizeof(int);
		*((int*)(packet_data+pos)) = tempplayer->getIntended(); pos+=sizeof(int);
		*((int*)(packet_data+pos)) = tempplayer->getDirection(); pos+=sizeof(int);
		if(tempplayer->isAGhost()){
			if(((Ghost*)tempplayer)->isDead()){
				*(packet_data+pos) = (byte)0x01; pos++;
			} else if(((Ghost*)tempplayer)->isEdible()){
				*(packet_data+pos) = (byte)0x02; pos++;
			} else {
				*(packet_data+pos) = (byte)0x00; pos++;
			}
		} else {
			if(!((Pacman*)tempplayer)->isDead()){
				*(packet_data+pos) = (byte)0x00; pos++;
			} else {
				*(packet_data+pos) = (byte)(((Pacman*)tempplayer)->getDeadCount()); pos++;
			}
		}
		for(j = tempplayermap->begin();j != tempplayermap->end();j++){
			//FIXIT : Get the UDPacket and set the data and length
			UDPacket* packet = j->second->getUDPacket();
			packet->setData(packet_data,pos);
			//cerr << "send : " << packet->getLength() << " " << (char)(packet->getData()[0]) << "\n";
			rudp->sendUnreliable(packet);
		}
	}
	
	delete tempplayermap;

	loopCount++;
	if(loopCount == 10){
		rudp->resendUnsent();
		loopCount = 0;
	}
}
