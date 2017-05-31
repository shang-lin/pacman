/* Space.cc- source file for Space */

 
/*
 * Revision History
 * 3/03/02- Generated Space.cc. author: Shang-Lin Chen
 * 3/13/02- Implemented constructors and methods
 * 3/22/02- Updated constructor to accept a character as an argument and to 
 *          test the character to determine the type of item.
 *          author: Shang-Lin Chen
 * 4/27/02- Fixed #include's. author: Shang-Lin Chen
 * 5/05/02- Fixed type of BaseItem. author: Shang-Lin Chen
 * 5/08/02- Fixed syntax and type errors. author: Shang-Lin Chen
 * 6/03/02- Implemented getX(), getY(), and getZ(). Modified constructors to
 *          accept coordinates. author: Shang-Lin Chen
 * 6/03/02- Added item key character to indicate the type of item contained.
 *          author: Shang-Lin Chen
 * 6/09/02- Added a character key to indicate the type of item originally 
 *          contained in this space. author: Shang-Lin Chen
 *
 */



// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "Space.h"
//#include "Exception.h"
#include<string>



/**
 * Class description:
 *
 * The Space class represents an individual space on the board. 
 * Each Space keeps track of the items and players it contains, 
 * as well as pointers to adjacent passable Spaces. 
 * 
 **/

// Returns pointer to the item that this space contains.
BaseItem* Space::getItem()
{
  return item;
}

//Draws the item contained in this Space.
void Space::draw(void)
{
  char item =  getItemKey();
  int x = getX()*6;
  int y = -getY()*6;

  switch(item)
  {
	case '.':
		glBegin(GL_POLYGON);
			glVertex2f(x-.5, y+.5);
			glVertex2f(x+.5, y+.5);
			glVertex2f(x+.5, y-.5);
			glVertex2f(x-.5, y-.5);
		glEnd();
		break;
	case '*':
		glColor3f(1, .5, .5);
		glBegin(GL_POLYGON);
			glVertex2f(x-1.3, y+1.3);
			glVertex2f(x+1.3, y+1.3);
			glVertex2f(x+1.3, y-1.3);
			glVertex2f(x-1.3, y-1.3);
		glEnd();
		glColor3f(1, 1, 1);
		break;
	default:
		break;
  }

  if(getNeighbor('u'))
  {
	//need to draw an Up space here....maybe a green triangle
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(x-1.3, y-1.3);
		glVertex2f(x, y+1.3);
		glVertex2f(x+1.3, y-1.3);
	glEnd();
	glColor3f(1, 1, 1);

  }
  else if(getNeighbor('d'))
  {
	//need to draw a Down space here....a red down triangle
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(x-1.3, y-1.3);
		glVertex2f(x, y+1.3);
		glVertex2f(x+1.3, y-1.3);
	glEnd();
	glColor3f(1, 1, 1);

  }
}

// Sets a neighbor of this Space. 
//
// args: char dir- the direction in which to set the neighbor.
//                 'n' means north, 's' means south, 'e' means east, 'w' 
//                 means west, 'u' means up, and 'd' means down.
//       Space *neighbor- a pointer to the space that will be the neighbor
void Space::setNeighbor(char dir, Space* neighbor){

  char ch = tolower(dir);

  if (neighbor!=NULL){
    // Determine which neighbor should be set.
    switch (ch){
    case 'u':  // 'u' means the up neighbor
      up = neighbor;
      break;
    case 'd': // 'd' means the down neighbor, and so on
      down = neighbor;
      break;
    case 'n':
      north = neighbor;
      break;
    case 's':
      south = neighbor;
      break;
    case 'w':
      west = neighbor;
      break;
    case 'e':
      east = neighbor;
      break;
   
    }
  }
}

// Returns a pointer to a neighboring Space.
//
// args: char dir- the direction of the neighbor you want to get
//                 'n' means north, 's' means south, 'e' means east, 'w' 
//                 means west, 'u' means up, and 'd' means down.
Space* Space::getNeighbor(char dir){
  char ch = tolower(dir);

  // Determine which neighbor to return
  switch (ch){
  case 'u':
    return up;
    break;
  case 'd':
    return down;
    break;
  case 'n':
    return north;
    break;
  case 's':
    return south;
    break;
  case 'e':
    return east;
    break;
  case 'w':
    return west;
    break;
  default:
    return NULL;
  }
} 

// Returns the x-coordinate of this Space.
int Space::getX(){
  return x;
}

// Returns the y-coordinate.
int Space::getY(){
  return y;
}

// Returns the z-coordinate.
int Space::getZ(){
  return z;
}

// Returns the number of players in the space.
int Space::getNumPlayers(){

  // no longer using vectors
  //return playersHere.size();  

  return numplayers;
}

// Returns the character that indicates the type of item currently in 
// this space.
// 'i' means special item, '.' means pellet, '*' means power pellet, and 
// anything else means no item.
char Space::getItemKey(){
  return itemKey;
}

// Returns the character that indicates the type of item originally in 
// this space.
// 'i' means special item, '.' means pellet, '*' means power pellet, and 
// anything else means no item.
char Space::getOrigItemKey(){
  return origItemKey;
}

// Returns true if this space does not contain an item, false if it does.
bool Space::isEmpty(){
  return empty;
}

// Returns an array of pointers to the players currently in this space.
Player** Space::getPlayers()
{
  return playerlist; 
}

// Adds a player to the list of players currently in this space. 
//
// args: Player *new_player- a pointer to the new player. 
void Space::addPlayer(Player *p)
{
  playerlist[numplayers] = p;
  numplayers++;
}

// Removes a player from the list of players currently in this space.
// 
// args: int pid- ID of the player to remove
void Space::removePlayer(int pid)
{
  int removed = 0;
  for(int i = 0; i < numplayers; i++)
    {
      if(removed)
	{
	  // shift the elements in the array forward
	  playerlist[(i-1)] = playerlist[i];
	}
      else
	{
	  // if the player to remove has been found...
	  if(pid == (playerlist[i]->getPlayerID()))
	    {
	      // set his spot to 0 to remove him 
	      playerlist[i] = 0;
	      numplayers--;
	      removed = 1;
	    }
	}
    }
}

// Removes the item contained in this space.
void Space::removeItem(){

  // no more items here...
  item = NULL; 
  itemKey = '0';

  // This space is now empty, so set the flag.
  empty = true;
}

// Constructors

// This constructor initializes a space containing a an item with the 
// specified type. The 
// coordinates of this Space can also be passed in as args, but they are 
// optional. 
//
// args: char i- character indicating the type of item this space contains
//               should be one of the legal Level chars, but not the newline
//       int c- column (x) coordinate in the level of this space (0 by default)
//       int r- row (y) coordinate ""
//       int f- floor (z) coordinate ""
Space::Space(char i, int c, int r, int f){

  // Set coordinates.
  x = c;
  y = r;
  z = f;

  // No players here right now, but we need to allocate memory.
  numplayers = 0;
  playerlist = new Player*[16];


  // Set item
  itemKey = i;
  origItemKey = i;
 
  // TO-DO: Add subclasses of BaseItem and more legal characters as they are
  // defined.

  // Initialize the correct type of item by looking at the character key.
  switch(itemKey){
  case '.':
  case '*':
  case 'i':
    // These characters all mean there's an item.

    item = new BaseItem();
    empty = false;
    break;

  default:
    // Any other character means it's an empty space.
    item = NULL;
    empty = true;
    break;
  }

  // Set neighbors to point to NULL, since neighbors have not been set yet.
  up = NULL;
  down = NULL;
  west = NULL;
  east = NULL;
  north = NULL;
  south = NULL;
}

// Initializes a space with no specified item.
// Coordinates are optional.
//
// args: int c- column (x) coordinate in the level of this space (0 by default)
//       int r- row (y) coordinate ""
//       int f- floor (z) coordinate "" 
Space::Space(int c, int r, int f){

  // No item
  itemKey = '0';
  origItemKey = '0';
  item = NULL;
  empty = true;

  // Set coordinates.
  x = c;
  y = r;
  z = f;

  // Originally 0 players
  numplayers = 0;
  playerlist = new Player*[16];

  // Set neighbors to point to NULL.
  up = NULL;
  down = NULL;
  west = NULL;
  east = NULL;
  north = NULL;
  south = NULL;
}

// Destructor

// Deallocates memory
Space::~Space ( void ) {
  if (item!=NULL){
    delete item; 
  }
}



