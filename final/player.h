/* Revision History

	4/21
	New methods
		I added a few methods for accessing the private data members
		of the Player class.  These were needed because I did some changing 
		to the PlayerList class that makes managing the pacmen and ghosts
		easier.  setPlayerID, getPlayerID were added to manipulate the
		new playerID member that can be used in playerlist to identify
		players without the index :/

	4/21
	New methods
		I added a few methods for accessing the private data members

	4/29
	Moved Skin
		Moved the PacSkin data memeber skin into the parent class of ghost and pacman
		I figured that it would be easier to leave it in pacman, but I forgot to 
		consider the consequences of changing the gender of a player from pacman
		to ghost
		added methods to set and get this PacSkin pointer value

  	5/14
	Get Score
		Added methods, among them, getScore for use with SideBar class, get name, etc.

	5/25
	Movement Variables
		James added several variables to let pacman move around, including fracdist,
		intendeddir and methods to access them
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include <iostream>
#include <string>
#include "drawableobject.h"
#include "pacskin.h"
#include "UDPacket.h"

#include  <stdio.h>
#include  <stdlib.h>

using namespace std;


//a place holder class to avoid multi inclusion, it was a big problem at first ^_^
class Space;


// Description:
//
// This is a general class for agents that operate in the game, 
// ie pacmen, user ghosts, and AI ghosts. The different types 
// of players have different characterstics; ie, pacmen can eat 
// pellets, ghosts can eat pacmen.
//The Player class is much more extensible than I thought it would be when
//first designing it.  It's movement is limited only by the Space objects
//therefore, if Space objects were oriented in level such that you could
//move in more than 4 directions, you could make a completely different game
//you can also very easily change the draw function to make the characters
//draw themselves differently.  I recommend subclassing for doing this.
//the great thing about making subclasses for Player is that they should
//primarily concern their drawing methods, and accessor methods for changing
//their various draw states.
//it would be pretty easy, I think, to create a Zelda type game using the Player
//class as it is here, and subclassing various monsters and Link himself.
//the only other thing that would need changing is the ServerLoop, but it
//needs work as it is

//as this class was being worked with, it because obvious that all interactions
//with player objects should be done through the PlayerList which contains them
//this makes everything easier and cleaner.  

//NOTE:  this class should have a lot more inlined functions.  The subclassed
//Player objects have a fair amount of inlining, but this one is seriously lacking
//especially for the dozen or so data returning methods.
class Player:public DrawableObject{
		// Data Members

	private:
		// An int that uniquely identifies the player. 
		int playerID;

		// The name of the player. 
		string playerName;

		// The number of lives that the player has remaining. 
		int numLives;

		// The x-position of the player in the level. 
		GLfloat x;

		// The y-position of the player in the level. 
		GLfloat y;

		// The z-position of the player in the level, the floor. 
		GLfloat z;

		// we can store the four numbers in the IP address as four chars. 
		unsigned char ipAddress[4];

		// The player's score. 
		int score;

		// The player's direction. 
		int direction;

		// The gameserver contols the real speed at which players travel. 
		// Individual players just need to know their speed for purposes 
		// of client-side position extrapolation. 
		//extrapolation was not done either due to time, but I think it could
		//be done easily enough
		float speed;

		// fractional distance moved towards center of current space
		//this was not used as the backbone for the game was not finished
		float fracdist;

		// The radius of the player. For example, the radius of the disc 
		// for the pacman. 
		int size;

		// A pointer to the current space on the gameboard. 
		Space * position;

		// The time (in milliseconds since server-start) at which this 
		// player joined the game. 
		int startTime;

		// The skin being used for this player. 
		PacSkin * skin;

		// The current time (since server-start) in milliseconds. 
		int currentTime;

		// The last direction entered by the user.  This variable determines 
		// how the player reacts when it reaches an intersection. 
		//not used, was placed in here for GameClient
		int lastdir;

		//intended direction
		//the direction that the player wants to move.  Check it for opposite at every timestep
		//check it for all directions at every intersection
		int wantdir;

		//a pointer to a UDPacket that holds that Player's
		//info
		UDPacket * udpacket;

		//timestamp used to synchronize data with server
		long timestamp;

	public:



		// Methods

	private:


	public:

		//override the draw method with opengl commands
		virtual void draw();

		//set the PlayerID, used by the playerlist to assign an ID
		//to the player
		void setPlayerID(int);

		//get the PlayerID, used by the playerlist to return player pointers
		int getPlayerID(void);

		//returns the player's score
		int getScore(void);

		//returns true is skin is NULL
		//there didn't need to be a function that returned the pointer to the skin
		bool isSkinNull(void);

		// adds change to the score. 
		void changeScore( int );
		
		//sets the score completely
		void setScore(int);

		// puts player in another space 
		void changePosition( Space* );

		string getName(void);

		void changeName(string);

		void changeDirection( int );

		// 100 is the normal speed 
		void changeSpeed( float );

		// 100 is the normal size 
		void changeSize( int );

		//I'm assuming that this is a method for guessing the player's next intended direction
		//I didn't put it here but I'd guess that it has something to do with GameClient
		virtual void decide(){ }

		void changeLives( int );

		// changes the game time variable 
		void changeTime( int );

		// lets the player move without help from the server, between 
		// queries for valid moves 
		// not actually used
		void guessmove( void );

		//return the size of the pacman, this scaler is a base 100 for a regular sized pacman
		int getSize(void);

		// Returns true if the player is a ghost, false otherwise. This 
		// should be overridden in the Ghost and Pacman classes. 
		virtual bool isAGhost( void );

		// Returns the number of milliseconds that this player has been 
		// in the game. 
		int getTime( void );

		void setFracDist(float fd);

		//set coords for drawing the players
		void SetXYZ(GLfloat newx, GLfloat newy, GLfloat newz);
		void SetX(GLfloat newx);
		void SetY(GLfloat newy);
		void SetZ(GLfloat newz);

		//get coords for drawing players
		GLfloat getX();
		GLfloat getY();
		GLfloat getZ();


		//accessors
		int getDirection(void);
		
		float getFracDist();
		float getSpeed();

		//set and return the player's current direction
		int getDir();
		void setDir(int newdir);



		// returns the direction the player will turn next
		int getIntended();
		
		//sets the direction that the player will go next
		void setIntended(int newdir);

		Space* getSpace();

		PacSkin * GetSkin(void);
		void SetSkin(PacSkin *);

		//methods to set and retrieve the UDPacket *
		UDPacket * getUDPacket(void){return udpacket;}
		void setUDPacket(UDPacket * udpin){
			if(udpacket != NULL) delete udpacket;
			udpacket = udpin;
		}



		//methods to get and set the last timestamp
		void setTimeStamp(long timein){timestamp = timein;}
		long getTimeStamp(void){return timestamp;}

		// Constructor(s)

		Player (void );


		// Destructor

		~Player ( void );

};

#endif

