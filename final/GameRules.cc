// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "GameRules.h"




// Applies the rules to the game. That is, it detects collisions 
// (with items, ghosts, pacmen) and alters the game state accordingly, 
// and computes the next position of pacmen and ghosts. 
void GameRules::applyRules( Gameboard * game ) {

}

// Changes the game mechanics.  If persistant is true, then this 
// is a permanent change, so forget about the old game mechanics. 
// otherwise, save the old game mechanics and use the new game 
// mechanics for the specified period of time. 
void GameRules::changeGameMechanics( GameMechanicsRules * gmr, bool persistant ) {

}

// Changes the game mechanics. We'll ask gmr whether or not it 
// is persistant. If so, then this is a permanent change, so 
// forget about the old game mechanics. otherwise, save the old 
// game mechanics and use the new game mechanics for the specified 
// period of time. 
void GameRules::changeGameMechanics( GameMechanicsRules * gmr ) {

}

// Decrements the time variable. 
void GameRules::decrementTime( void ) {

}

// Returns true iff the value of time is 0. 
bool GameRules::expired( void ) {

}



// Constructor(s)

GameRules::GameRules(){

}

// Destructor

GameRules::~GameRules ( void ) {
  
}


