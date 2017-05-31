#include "Level.h"
#include "Space.cc"
#include "FileException.cc"
#include<string>
#include<vector>
#include<fstream>
#include<iostream>


using namespace std;

// Randomly generates the map as a 3-D array of pointers to Space 
// objects. Precondition is that memory for the map has already been 
// allocated by the constructor.
void Level::generateRandom(){
  
// We want to first initialise the 3-d array of space pointers

// then, we arbitrarily pick some interior point in the array as our
// starting point.

// Now, we want to move around in the current floor and "carve out" as
// much space as possible, so we just want to move to all valid adjacent
// spaces from the current space recursively. this recursion will bottom 
// out when there are no other valid spaces.

// at this point, if there is an adjacent floor in the array that has
// yet to be set up, arbitrarily choose an accessible square in the
// current level, and make that a staircase connecting to the adjacent
// level. then, start the process over again from that point in the 
// new level to set up that level.

// once the board has been carved, out, specify pacman spawn points, 
// ghost spawn points, and other special spaces randomly throughout
// the graph 

}
