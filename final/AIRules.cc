// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "AIRules.h"




// Returns a pointer to the preferred adjacent space. If the 
// ghost has not been eaten, it does this dependent on the value 
// of pacmanAttraction. If it has been eaten, then the preferred 
// adjacent space is that space which brings the ghost closer 
// to a respawn point. Distances to respawn points can be calculated 
// in O(n) time with a breadth-first search. Distances to pacmen 
// are even easier to calculate, since ghosts can only see in 
// a straight line, so we just need to keep searching north, 
// south, east, and west until we see a pacman. 
Space* AIRules::findBestAdjacentSquare( Space * currentPosition, Level * level ) {

}

// Modifies the value of pacmanAttraction. 
void AIRules::setPacmanAttraction( int pa ) {

}

// Returns the value of pacmanAttraction. 
int AIRules::getPacmanAttraction( void ) {

}

// Modifies the vision range of ghosts. 
void AIRules::setVisionRange( int vr ) {

}

// Returns the vision range of ghosts. 
int AIRules::getVisionRange( void ) {

}



// Constructor(s)

// Creates a generic AIRules object. 
AIRules::AIRules ( void ) {

}



// Destructor

AIRules::~AIRules ( void ) {
  
}


