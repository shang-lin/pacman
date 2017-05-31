/* Level.h */


/* Revision History
 * 2/21/02: Generated from documentation and added to repository. 
 *          author: Shang-Lin Chen
 * 3/13/02: Added pre-compilation directives to specify maximum width and 
 *          height. author: Shang-Lin Chen
 * 3/14/02: Added string that contains legal chars in a level file.
 *          author: Shang-Lin Chen
 * 4/27/02: Fixed #include's. author: Shang-Lin Chen
 * 5/9/02: Fixed syntax errors. author: Shang-Lin Chen
 * 5/20/02: Changed "height" to "length." Added getWidth(), getLength(), and 
 *          getHeight() methods.
 * 5/21/02: Added method getSpace(int, int, int). author: Shang-Lin Chen
 * 6/02/02: Changed the maximum width and length of the level from 500x500
 *          to 200x200 because the other makes random level generation
 *          slow, and the level is ridiculously big (about 75,000 *hallway* 
 *          spaces alone!)
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_

// Includes
#include "genlevel.h"
#include<vector>
#include "Space.h"
#include "BaseItem.h"


//Max dimensions of the map
#define MAXWIDTH 200
#define MAXLENGTH 200
#define MAXFLOORS 5

#define DEBUG_MODE 0

// String containing legal characters in a level file
const string legal_chars(".*0iudPpg\n ");


/**
 * Class description:
 *
 * The Level class stores information about the state of the current level, 
 * which includes the maze, its dimensions, and its contents. The level can
 * be loaded from a level file, or it can be generated randomly from 
 * user-provided information about the
 * number of columns, number of rows, number of floors, number of Pacmen, and
 * number of ghosts.
 *
 * 
 **/

// This object maintains the current level data. It keeps track 
// both of the map, and of the the current state of the game. 
// The constructors can accept either the name of the level file, 
// or specifications for a random level. 

class Level : private DrawableObject{

  // Data Members

 private:

  // An array of pointers to spaces that represents the map where the players 
  // move. The dimensions of this array will be the width*height*floors.
  Space** map;

  // The number of columns of spaces in the map.
  int width;

  // The number of rows of spaces in the map.
  int length;

  // The number of floors in the map. 
  int floors;

  // The number of ghosts in the level. 
  int numghosts;

  // The maximum number of pacmen in the level. 
  int numpacmen;


 public:
 
  // Methods

  // A list of pointers to spaces where pacmen can spawn. 
  vector<Space*> pacmanStart;

  // A list of pointers to spaces where ghosts can spawn. 
  vector<Space*> ghostStart;


  // Methods 
  
 private:

  // Randomly generates the map as a 3-D array of pointers to Space 
  // objects. Assumes memory for the map has already been allocated by
  // the constructor.
  void generateRandom( void );
  

  // Helper function that loads the map array from a character array if it 
  // represents a valid level.
  // The helper function checkValid is called to check each character.
  // An exception is thrown if there is any error in the map.
  // Preconditions: The size of the char array must be width*length*floors.
  //
  // args: const char *textmap- char array containing the ASCII representation
  //                            of a level
  //
  void loadMap( const char *);
  

  // Helper for loadMap that checks that the character in a character array 
  // at a specific row, column, and floor can represent a valid Space in the 
  // actual map. The character array is an ASCII representation of the actual 
  // map in the Level. 
  // Returns true if the character is valid, false otherwise.
  //
  // args: const char *textmap- char array representing the level
  //       const int c- column of the character currently being checked
  //       const int r- row of the character currently being checked
  //       const int f- floor ""  
  bool checkValid( const char*, const int, const int, const int );
  
  // Builds the level from a user-defined level file. 
  // The characters in the level file are stored in a character array
  // which is then passed to the loadMap method. loadMap checks that
  // the characters can represent a valid map and loads the map from the char 
  // array  if all the tests are passed.
  //
  // args: const char *filename- the name of the level file.
  void parseFile( const char * );
  
  // Initializes the dimensions of the map when the input to 
  // the constructor is a level file. 
  //
  // args: const char *filename- the name of the level file
  void initializeFields( const char* );
  
  // Given the row, column, and floor coordinate, computes the appropriate 
  // index in the map array.
  int findIndex(int, int, int);

  // Sets all neighbors of the Space in the map located at row r, column c,
  // floor f. textmap is the character array that temporarily represents the 
  // map.
  // 
  // args: const char *textmap- char representation of the map.
  //                            size is assumed to be length*with*floors.
  //       const int c- column of the char to check
  //       const int r- row of the char to check
  //       const int f- floor of the char to check
  void setAllNeighbors(const char *textmap, const int r, const int c, const int f);



  // Returns true if every valid Space in the map is reachable from each Pacman
  // starting point, returns false if the test fails. A BFS object is
  // declared to model the Level as a graph. Then a breadth-first search is
  // performed on the graph to perform the test. Assumes the map has already
  // been declared.

  bool checkReachable();

 public:
 
	// returns a random pacman starting position
	Space * getPacmanStart ( void );

	// returns a random ghost starting position
	Space * getGhostStart ( void );
	
  // Calculates the shortest path from (x1,y1,z1) to (x2,y2,z2) 
  // in the level (using BFS). Not yet implemented. 
  int distance( int, int, int, int, int, int );
  
  // Saves this level's map to the specified file. 
  // Each Space* in the map is written to the output file as an ASCII 
  // character determined by the type of item it contains.
  //
  // args: string filename- name of the output file
  void saveLevel( string );
  
  // draws the level 
  void draw ( void );

  // Returns the width of the level.
  int getWidth();

  // Returns the maximum number of rows in the level.
  int getLength();

  // Returns the number of floors of the level.
  int getFloors();

  // Returns the pointer to a Space at a specified column, row, and floor in
  // the level.
  Space* getSpace(int, int, int);

  // Prints information about neighbors of each space.
  void printNeighbors();


  // Constructor(s) 

  // Generates the level from the contents of an input text file that contains
  // an ASCII representation of the actual map using only  
  // legal characters as defined in the header file. The level is only 
  // generated if the file passes all validation tests.
  //
  // args: string filename- name of the level file. 
  //                        must end with .txt extension.
  Level ( string );

  // Randomly generates a level with the user-provided parameters. The randomly
  // generated level must pass all validation tests.
  //
  // args: int xrange- number of columns in the randomly generated level
  //       int yrange- number of rows ""
  //       int numfloors- number of floors ""
  //       int maxpacmen- maximum number of Pacmen allowed and also number
  //                      of Pacman starting points
  //       int numGhosts- maximum number of ghosts allowed
  Level ( int, int, int, int, int );

  // Creates a level from the specified information and the array of chars.
  // 
  // args: int xrange- number of columns in the level
  //       int yrange- number of rows ""
  //       int numfloors- number of floors ""
  //       int maxpacmen- maximum number of pacmen
  //       int numghosts- number of ghosts
  //       char *textmap- chars representing the level
  Level ( int, int, int, int, int, char* );
  
  
  
  // Destructor
  
  // Deallocates memory.
  ~Level ( void );
  
};

#endif

