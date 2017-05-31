/**
 * args : <server IP address> <server port> <rudp port> <player name> <isAGhost>
 **/

#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include "TCP.h"
#include "TCPServer.h"
#include "RUDP.h"
#include "playerlist.h"
#include "chatwnd.h"
#include "Level.h"

using namespace std;

OpenGL opengl;
PlayerList playerlist;
int myID;
TCP* tcp = NULL;
RUDP* rudp = NULL;
UDPacket* outpacket;
ChatWnd chatwnd;
Level* testlevel;
int loopCount=0;
long ms;
pthread_mutex_t graphicsMutex;

/**
 * This function is what is called to start up openGL and the glutMainLoop
 **/
void* graphicsInit(void* playerID){
	//test skin object.  It's easiest to make these and then pass them into the addplayer function
	//cerr << "Inside graphicsInit\n";

	Space * tempspace = testlevel->pacmanStart[0];
	//cerr << "tempspace = " << tempspace << "\n";
	Player * tempplayer = playerlist.getPlayer(myID);
	tempplayer->changePosition(tempspace);

	//pull the space's indicies
	int x = tempspace->getX();
	int y = tempspace->getY();
	int z = tempspace->getZ();

	//assign his x and y coords
	tempplayer->SetX(x*6);
	tempplayer->SetY(-y*6);
	tempplayer->SetZ(z);

	//cerr << "Made it to the main loop\n";

	opengl.StartMainLoop();
	
	pthread_exit(0);
}

void addNewPlayer(const string* message){
	pthread_mutex_lock(&graphicsMutex);

	int i;
	int index = 0;
	char currChar = message->c_str()[index];
	char id[32];
	char name[256];
	bool isaghost;
	while(currChar != 0){
		i=index;
		while(currChar != ' '){
			id[index-i] = currChar;
			index++; currChar = message->c_str()[index];
		}
		id[index-i] = 0;
		i=++index; currChar = message->c_str()[index];
		while(currChar != ' '){
			name[index-i] = currChar;
			index++; currChar = message->c_str()[index];
		}
		name[index-i] = 0;
		++index; currChar = message->c_str()[index];
		isaghost = currChar=='0' ? false : true ;
		index += 2; currChar = message->c_str()[index];

		// Add this player to the playerlist
		playerlist.addplayer(string(name),0,NULL,isaghost,NULL,atoi(id));
	}

	pthread_mutex_unlock(&graphicsMutex);
}

int main(int argc,char* argv[]){
	int i,j,k;
	// The port on which the server is waiting
	int tport = 0;
	// The port to use for this clients RUDP
	int rport = 0;
	const string* message;
	UDPacket* inpacket = new UDPacket();
	outpacket = new UDPacket();
	pthread_t thread1;
	long startMS;
	pthread_mutex_init(&graphicsMutex,NULL);

	if(argc != 6 && argc != 7){
		cerr << "usage\n";
		exit(0);
	}

	try{
		tport = atoi(argv[2]);
		tcp = new TCP(string(argv[1]),tport);
		rport = atoi(argv[3]);
		rudp = new RUDP(rport);

		////Handshaking
		char temp[1024];
		string toSend = "";

		//cerr << "Send my name\n";
		// Send my name
		toSend = string(argv[4]);
		toSend += string(argv[5]);
		tcp->sendString(&toSend);

		//cerr << "Read my id\n";
		// read my id
		message = tcp->getString();
		//cerr << "got another message\n";
		myID = atoi(message->c_str());
		delete message;

		//cerr << "Send an acknowledge\n";
		// send an acknowledge
		sprintf(temp,"ack");
		toSend = string(temp);
		tcp->sendString(&toSend);

		//cerr << "Read and fill playerlist\n";
		// read and fill playerlist
		message = tcp->getString();
		//cerr << "read message : " << *message << "\n";
		addNewPlayer(message);
		delete message;

		//cerr << "Send an acknowledge\n";
		// send an acknowledge
		sprintf(temp,"ack");
		toSend = string(temp);
		tcp->sendString(&toSend);

		//cerr << "Read level data\n";
		// read level data
		int width,length,floors;
		int maxpacmen = 0;
		int numghosts = 0;
		message = tcp->getString();
		width = atoi(message->c_str());
		delete message;

		//cerr << "Send an acknowledge\n";
		// send an acknowledge
		sprintf(temp,"ack");
		toSend = string(temp);
		tcp->sendString(&toSend);

		message = tcp->getString();
		length = atoi(message->c_str());
		delete message;

		//cerr << "Send an acknowledge\n";
		// send an acknowledge
		sprintf(temp,"ack");
		toSend = string(temp);
		tcp->sendString(&toSend);

		message = tcp->getString();
		floors = atoi(message->c_str());
		delete message;

		//cerr << "Send an acknowledge\n";
		// send an acknowledge
		sprintf(temp,"ack");
		toSend = string(temp);
		tcp->sendString(&toSend);

		char textmap[width*length*floors];
		//cerr << "floors=" << floors
		//     << " length=" << length
		//		 << " width=" << width << "\n";
		for(i=0;i<floors;i++){
			for(j=0;j<length;j++){
				message = tcp->getString();
				//cerr << "receiving level .. " << *message << "\n";
				const char* tempmessage = message->c_str();
				for(k=0;k<width;k++){
					textmap[i*(length*width)+j*(width)+k] = tempmessage[k];
					if(tempmessage[k] == 'G' || tempmessage[k] == 'g')
						numghosts++;
					if(tempmessage[k] == 'P' || tempmessage[k] == 'p')
						maxpacmen++;
				}
				delete message;

				//cerr << "Send an acknowledge\n";
				// send an acknowledge
				sprintf(temp,"ack");
				toSend = string(temp);
				tcp->sendString(&toSend);

			}
		}

		testlevel = new Level(width,length,floors,maxpacmen,numghosts,textmap);

		/*
		cerr << "About to output my level\n";
		for(i=0;i<testlevel->getFloors();i++){
			for(j=0;j<testlevel->getLength();j++){
				for(k=0;k<testlevel->getWidth();k++){
					char c = textmap[k+j*testlevel->getWidth()+i*testlevel->getWidth()*testlevel->getLength()];
					if(c==' ') c = '-';
					cerr << c;
				}
				cerr << "|\n";
			}
		}

		cerr << "About to output my level\n";
		for(i=0;i<testlevel->getFloors();i++){
			for(j=0;j<testlevel->getLength();j++){
				for(k=0;k<testlevel->getWidth();k++){
					Space* s = testlevel->getSpace(k,j,i);
					if(s == NULL) cerr << "_";
					else {
						char c = s->getItemKey();
						if(c==' ') c = '-';
						cerr << c;
					}
				}
				cerr << "|\n";
			}
		}
		*/

		timeval tv;

		// Get RUDP port of server
		//cout << "About to get server udp port\n";
		message = tcp->getString();
		int serverPort = atoi(message->c_str());
		delete message;
		//cout << "Got server udp port " << serverPort << "\n";

		// Send RUDP port of client
		sprintf(temp,"%i",rport);
		toSend = string(temp);
		tcp->sendString(&toSend);

		// Send my hostname
		//cout << "About to get hostname\n";
		gethostname(temp,1024);
		if(argc == 7){
			toSend = string(argv[6]);
		} else {
			toSend = string(temp);
		}
		//cout << "About to send hostname :" << toSend << "\n";
		tcp->sendString(&toSend);

		// Make the UDPacket to store this info
		//cerr << "server address " << argv[1] << ":" << serverPort << "\n";
		outpacket->setAddress(string(argv[1]),serverPort);

		// Get the servers current milliseconds since the start
		//cout << "About to read server time\n";
		message = tcp->getString();
		//cout << "Just read server time :" << *message << ":\n";
		long serverMillis = atol(message->c_str());
		delete message;
		gettimeofday(&tv,NULL);
		startMS = tv.tv_sec*1000 + tv.tv_usec/1000 - serverMillis;

		////Done Handshaking

		// Create a new thread that calls the graphicsInit function
		
		//graphicsInit();
		pthread_create(&thread1, NULL,graphicsInit,NULL);

		while(true){
			//Get the current time
			gettimeofday(&tv,NULL);
			ms = tv.tv_sec * 1000 + tv.tv_usec/1000 - startMS;
			//cerr << "time : " << ms << "       \r";

			if(tcp->isReady()){
				message = tcp->getString();

				// Take care of message according to first char
				switch((*message)[0]){
					case 'c':
						chatwnd.addMessage(message->substr(1,message->length()-1));
						break;
					case 'a':
						addNewPlayer(&(message->substr(1,message->length()-1)));
						break;
					case 'r':
						playerlist.removeplayer(
							atoi(message->substr(1,message->length()-1).c_str())
						);
						break;
				}
				delete message;

			}
			while(rudp->isReady()){
				rudp->receivePacket(inpacket);
				const byte* packet_data = inpacket->getData();
				int length = inpacket->getLength();
				//cerr << "Recv : " << length << " " << (char)packet_data[0] << "\n";
				
				int pos,id,x,y,z;
				Player* tempplayer;
				long newtime;

				switch(packet_data[0]){
					case 'p':

	pos = 1;
	id = *(packet_data+pos); pos++;
	tempplayer = playerlist.getPlayer(id);
	newtime = *((long*)(packet_data+pos)); pos+=sizeof(long);
	pthread_mutex_lock(&graphicsMutex);
	if(tempplayer->getTimeStamp() < newtime){
		tempplayer->setTimeStamp(newtime);
		tempplayer->SetX(*((GLfloat*)(packet_data+pos))); pos+=sizeof(GLfloat);
		tempplayer->SetY(*((GLfloat*)(packet_data+pos))); pos+=sizeof(GLfloat);
		tempplayer->SetZ(*((GLfloat*)(packet_data+pos))); pos+=sizeof(GLfloat);
		tempplayer->setScore(*((int*)(packet_data+pos))); pos+=sizeof(int);
		tempplayer->setIntended(*((int*)(packet_data+pos))); pos+=sizeof(int);
		tempplayer->setDir(*((int*)(packet_data+pos))); pos+=sizeof(int);
		if(tempplayer->isAGhost()){
			if(*(packet_data+pos)==(byte)0x01){
				((Ghost*)tempplayer)->setDead();
			} else if(*(packet_data+pos)==(byte)0x02){
				((Ghost*)tempplayer)->setEdible();
			} else {
				((Ghost*)tempplayer)->resetDead();
				((Ghost*)tempplayer)->resetEdible();
			}
		} else {
			if(*(packet_data+pos) == (byte)0x00){
				((Pacman*)tempplayer)->resetDead();
			} else {
				((Pacman*)tempplayer)->setDead();
				((Pacman*)tempplayer)->setDeadCount(*(packet_data+pos));
			}
		}
	}
	pthread_mutex_unlock(&graphicsMutex);
						
						break;
					case 'g':
	pos = 1;
	x = *((int*)(packet_data+pos)); pos+=sizeof(int);
	y = *((int*)(packet_data+pos)); pos+=sizeof(int);
	z = *((int*)(packet_data+pos)); pos+=sizeof(int);
	pthread_mutex_lock(&graphicsMutex);
	Space* tempspace = testlevel->getSpace(x,y,z);
	tempspace->removeItem();
	pthread_mutex_unlock(&graphicsMutex);
						break;
				}
			}
	
			loopCount++;
			if(loopCount == 10){
				rudp->resendUnsent();
				loopCount = 0;
			}
		}
	} catch(NetworkException ne){
		cerr << ne << "\n";
		exit(1);
	}
}
