
#ifndef _RAND_LEVEL_GENERATOR_H_
#define _RAND_LEVEL_GENERATOR_H_
 
using namespace std;

//#include "level.h"
#include <string>
#include <iostream>


// constants for space type
#define k_WALL ' '
#define k_HALLWAY '0'
#define k_HALLWAY_WITH_PELLET '.'
#define k_EDGEHALL '.'
#define k_DROPDOWN 'd'
#define k_JUMPUP 'u'
#define k_MAIN_PACMAN_RESPAWN 'P'
#define k_ITEM 'i'
#define k_POWER_PILL '*'
#define k_PACMAN_RESPAWN 'p'
#define k_GHOST_RESPAWN 'g'


#define k_NUMITS 100
#define k_LINELENGTH 10

#define k_FLOOR_HEIGHT	2
#define k_SPACE_WIDTH 1
#define k_SPACE_HEIGHT 1

#define k_UP 0
#define k_DOWN 1
#define k_RIGHT 2
#define k_LEFT 3


class RandomLevelGenerator {
	// variables
private:
	// the width, height, and number of floors of the level.
	int width;
	int height;
	int floors;

	// the maximum number of pacmen and ghosts
	int maxpacmen;
	int maxghosts;
	
	// a pointer to a 3d character array that represents the level.
	char * the_level;
	
	// methods
private:


public:
	// this is the big ugly method that generates the level.
	void generate_level ( void );

	// this returns the character in the level array with
	// the specified indices
	char getValue(int, int, int);

	// the level array is dynamically allocated, so it has to
	// be a 1d array that represents a 3d array. this method
	// takes a set of width, length, and depth indices and
	// converts them to a single number that corresponds to
	// that point's index in the level array
	int getIndex(int, int, int);
	

	// these are just accessors. they all accept a position in 
	// the level and return whether or not that position is 
	// the type of space in the method name.
	bool isHallway(int, int, int);
	bool isWall(int, int, int);
	bool isEdgehall(int, int, int);
	bool isJumpUp(int, int, int);
	bool isDropDown(int, int, int);
	bool isPassable(int, int, int);
	
	// accessors for the width, height, and number of floors
	// variables
	int getWidth(void);
	int getHeight(void);
	int getFloors(void);
	
	
	// allows "cout << randomlevel" to make coding a little 
	// easier.
	friend ostream & operator<<(ostream & os, const RandomLevelGenerator & rlg);

	
	// constructors
	// the ints are the width of a level, the height of a level, and the
	// number of floors. the last two ints are the max number of pacmen
	// that will be on the screen at any given time followed by the max
	// number of ghosts that will be on the screen at any given time.
	RandomLevelGenerator (int, int, int, int, int);
	
	// destructor
	~RandomLevelGenerator( void );
	
};

#endif
