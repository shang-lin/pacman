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

#include  <stdio.h>
#include  <stdlib.h>

using namespace std;



class Space;


// Description:
//
// This is a general class for agents that operate in the game, 
// ie pacmen, user ghosts, and AI ghosts. The different types 
// of players have different characterstics; ie, pacmen can eat 
// pellets, ghosts can eat pacmen. 
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

		// The z-position of the player in the level. 
		GLfloat z;

		// we can store the four numbers in the IP address as four chars. 
		// 
		unsigned char ipAddress[4];

		// The player's score. 
		int score;

		// The player's direction. 
		int direction;

		// The gameserver contols the real speed at which players travel. 
		// Individual players just need to know their speed for purposes 
		// of client-side position extrapolation. 
		float speed;

		// fractional distance moved towards center of current space
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
		int lastdir;

		//intended direction
		//the direction that the player wants to move.  Check it for opposite at every timestep
		//check it for all directions at every intersection
		int wantdir;


	public:



		// Methods

	private:


	public:

		//override the draw method with opengl commands
		void draw();

		//set the PlayerID, used by the playerlist to assign an ID
		//to the player
		void setPlayerID(int);

		//get the PlayerID, used by the playerlist to return player pointers
		int getPlayerID(void);

		//returns the player's score
		int getScore(void);

		//returns true is skin is NULL
		bool isSkinNull(void);

		// adds change to the score. 
		void changeScore( int );
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

		// Constructor(s)

		Player (void );


		// Destructor

		~Player ( void );

};

#endif

