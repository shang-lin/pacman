/* Revision History

	4/21
	New methods
		I added a few methods for accessing the private data members
		of the Player class.  These were needed because I did some changing 
		to the PlayerList class that makes managing the pacmen and ghosts
		easier.  setPlayerID, getPlayerID

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


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "player.h"
#include "drawableobject.h"
#include "image.h"
#include "text.h"

//includes from other portions of the project should be done in 
//the cpp files because they are probably using 
//your classes too!!
#include "Space.h"


//TODO
//lots of these functions need to be completely implemented
//I'm waiting on a few things here.  Namely a player class
//that completely works under linux, and several of the event classes
//the direction and changing functions are probably going to end up 
//being redundant somewhat because a lot of the data won't need
//changing once the player is set up and in the game

// Description:
//
// This is a general class for agents that operate in the game, 
// ie pacmen, user ghosts, and AI ghosts. The different types 
// of players have different characterstics; ie, pacmen can eat 
// pellets, ghosts can eat pacmen. 

//the characteristics of the classes will be defined by the rules objects
//the implementation of which is still a bit of a logistical question

void Player::draw(void)
{
	glTranslatef(x, y, 0);
}

void Player::SetXYZ(GLfloat newx, GLfloat newy, GLfloat newz)
{
	x = newx;
	y = newy;
	z = newz;
}
void Player::SetX(GLfloat newx)
{
	x = newx;
}
void Player::SetY(GLfloat newy)
{
	y = newy;
}
void Player::SetZ(GLfloat newz)
{
	z = newz;
}

GLfloat Player::getX()
{
	return x;
}

GLfloat Player::getY()
{
	return y;
}

GLfloat Player::getZ()
{
	return z;
}

// adds change to the score. 
void Player::changeScore(int change) 
{
	score+=change;

}

bool Player::isSkinNull(void)
{
	if(skin == NULL)
		return true;
	else
		return false;
}

// sets the score. 
void Player::setScore(int setscore) 
{
	score=setscore;

}

int Player::getScore(void)
{
	return score;
}

int Player::getDirection(void)
{
	return direction;
}

string Player::getName(void)
{
	return playerName;
}


//set the PlayerID, used by the playerlist to assign an ID to the player
void Player::setPlayerID(int IDin)
{
	playerID = IDin;
}

//get the PlayerID, used by the playerlist to return player pointers
int Player::getPlayerID(void)
{
	return playerID;
}

void Player::changeName( string newname) {
	playerName=newname;
}

void Player::changeDirection( int newdir ) {
	direction=newdir;
}

// 100 is the normal speed 
void Player::changeSpeed( float newspeed ) {
  speed = newspeed;
}

// 100 is the normal size 
void Player::changeSize( int newsize ) {
	size = newsize;
}


void Player::changeLives( int newlives ) {

}

// changes the game time variable 
void Player::changeTime( int newtime ) {

}

// lets the player move without help from the server, between 
// queries for valid moves 
void Player::guessmove(  ) {

}


// Returns true if the player is a ghost, false otherwise. This 
// should be overridden in the Ghost and Pacman classes. 
bool Player::isAGhost( void ) 
{
	return false;
}

//return the size of the pacman, this scaler is a base 100 for a regular sized pacman
int Player::getSize(void)
{
	return size;
}

//return the skin so that the Pacman class can access it
PacSkin * Player::GetSkin(void)
{
	return skin;
}

void Player::SetSkin(PacSkin * skinin)
{
	skin = skinin;
}


// Returns the number of milliseconds that this player has been 
// in the game. 
int Player::getTime( void ) {
	return startTime - currentTime;
}

void Player::setFracDist(float fd)
{
  fracdist = fd;
}

float Player::getFracDist()
{
  return fracdist;
}

float Player::getSpeed()
{
  return speed;
}



int Player::getDir()
{
  return direction;
}

void Player::setDir(int newdir)
{
  direction = newdir;
}


int Player::getIntended()
{
  return wantdir;
}

void Player::setIntended(int newdir)
{
  wantdir = newdir;
}
  

Space* Player::getSpace()
{
  return position;
}

void Player::changePosition( Space* newpos)
{
	position = newpos;
}



// Constructor(s)
Player::Player()
{

}


// Destructor

Player::~Player ( void ) 
{
	
}

