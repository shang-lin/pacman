/* Space.h 
   header file for Space class
*/

/*
 * Revision History
 * 3/03/02- Generated Space.h. author: Shang-Lin Chen
 * 3/13/02- Added getNeighbor and setNeighbor, changed the constructor to take
 *          an argument. author: Shang-Lin Chen
 * 4/27/02- Fixed #include's. author: Shang-Lin Chen
 * 5/05/02- Fixed data types of item. author: Shang-Lin Chen
 * 5/09/02- Added BaseItem.h to include files. author: Shang-Lin Chen
 * 6/03/02- Added x, y, z coordinates and methods to return them. Modified 
 *          constructors to accept coordinates.
 *          author: Shang-Lin Chen
 * 6/03/02- Added character key to indicate the type of item.
 *          author: Shang-Lin Chen
 * 6/04/02- Added flag for empty Spaces. author: Shang-Lin Chen
 */

#ifndef _SPACE_H_
#define _SPACE_H_
 

#include "player.h"
#include<vector>
#include "BaseItem.h"

/**
 * Description:
 *
 * The Space class represents an individual space on the board. 
 * Each Space keeps track of the items and players it contains, 
 * as well as pointers to adjacent passable Spaces. 
 * 
 **/

class Space : private DrawableObject{
  // Data Members

 private:
  // A pointer to the space above this space. 
  Space *up;

  // A pointer to the space below this space. 
  Space *down;
  
  // A pointer to the space north of this space. 
  Space *north;
  
  // A pointer to the space south of this space. 
  Space *south;
  
  // A pointer to the space east of this space. 
  Space *east;
  
  // A pointer to the space west of this space. 
  Space *west;
  
  // Column, row, and floor (x, y,z) coordinates of a Space. The coordinates
  // indicate its location in the map in Level.
  int x, y, z;
 
  // A pointer to the item contained in this space. If no item 
  // is contained, then this pointer is null. 
  
  BaseItem *item;
 
  // An array of players contained in this space. 
  //vector<Player*>playersHere;
  Player** playerlist;
  
  // Number of players in this space
  int numplayers;
 
  // A character that keeps track of what item is contained in this space.
  // The characters used are the same as the ones allowed in Level files.
  // For now, '.' represents a pellet, '*' represents a power pellet, and 'i'
  // represents a generic special item. 
  // '0', 'p', 'P', 'g', 'G', 'u','U', 'd', 'D', and ' 'all represent no item. 
  // ('0' is the default indicator for no item, but the others are needed by 
  // Level.)
  char itemKey;  



  // A character that records the item contained in this space when
  // it was created. Intially, origItemKey is the same as itemKey, but itemKey
  // may change. origItemKey is used by Level::saveLevel to save a level with
  // all its spaces in their original form.  
  char origItemKey;

  // Flag that is true if the Space does not contain an item, false if it does
  // contain an item.
  bool empty;

 public:
  // Methods
  

  //Draws the item in this Space.
  void draw(void);

  // Sets a neighbor of this Space. 
  //
  // args: char dir- the direction in which to set the neighbor.
  //                 'n' means north, 's' means south, 'e' means east, 'w' 
  //                 means west, 'u' means up, and 'd' means down.
  //       Space *neighbor- a pointer to the space that will be the neighbor
  void setNeighbor(char dir, Space *neighbor);
  
  // Returns the pointer to a neighboring space.
  //
  // args: char dir- the direction of the neighbor you want to get
  //                 'n' means north, 's' means south, 'e' means east, 'w' 
  //                 means west, 'u' means up, and 'd' means down.
  Space* getNeighbor(char);

  // Returns a pointer to the item that this space contains.
  BaseItem * getItem( void );

  // Returns the x-coordinate (column) of this Space.
  int getX();

  // Returns the y-coordinate (row) of this Space.
  int getY();

  // Returns the z-coordinate (floor) of this Space.
  int getZ();

  int getNumPlayers();  // returns the number of players in the space
  Player** getPlayers(); // returns a list of players in the space


  // Adds a player to the list of players currently in this space. 
  //
  // args: Player *new_player- a pointer to the new player. 
  void addPlayer(Player *new_player); 

  // Removes a player from the list of players currently in this space.
  // 
  // args: int pid- ID of the player to remove
  void removePlayer(int pid);
  
  // Removes the item contained in this space.
  void removeItem();

  // Returns the character that indicates the type of item currently in 
  // this space.
  // 'i' means special item, '.' means pellet, '*' means power pellet, and 
  // anything else means no item.
  char getItemKey();

  // Returns the character that indicates the type of item originally in 
  // this space.
  // 'i' means special item, '.' means pellet, '*' means power pellet, and 
  // anything else means no item.
  char getOrigItemKey();

  // Returns true if the Space does not contain an item, false if it does.
  bool isEmpty();



  // Constructor(s)

  // This constructor initializes a space containing an item with the 
  // specified item type.
  // The coordinates of the space can also be passed in as args, but they are 
  // optional. 
  //
  // args: char i- character indicating the type of item this space contains
  //               should be one of the legal Level chars, but not the newline
  //       int c- column (x) coordinate in the level of this space 
  //              (0 by default)
  //       int r- row (y) coordinate ""
  //       int f- floor (z) coordinate ""
  Space(char item, int c=0, int r=0, int f=0);
  


  // Initializes a space with no specified item.
  // Coordinates are optional.
  //
  // args: int c- column (x) coordinate in the level of this space 
  //              (0 by default)
  //       int r- row (y) coordinate ""
  //       int f- floor (z) coordinate "" 
  Space(int c=0, int r=0, int f=0);


  // Destructor
  
  ~Space ( void );
  
};

#endif






