// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "GameMechanicsRules.h"




// True if persistance == -1, false otherwise. 
bool GameMechanicsRules::isPersistant( void ) {

}

// Sets the start time of the rule set. 
int GameMechanicsRules::setStartTime( long milliseconds ) {

}

// Returns true iff the current time minus the start time is 
// greater than the persistance. 
bool GameMechanicsRules::isExpired( long currentmilliseconds ) {

}

// Applies the game mechanics rules to the specified game. 
void GameMechanicsRules::applyRules( Gameboard * game ) {

}

// Sets the ghost speed. 
void GameMechanicsRules::setGhostSpeed( int speed ) {

}

// Sets the pacman speed. 
void GameMechanicsRules::setPacmanSpeed( int speed ) {

}

// Returns the pacman speed. 
int GameMechanicsRules::getPacmanSpeed( void ) {

}

// Returns the ghost speed. 
int GameMechanicsRules::getGhostSpeed( void ) {

}

// Sets whether or not ghosts collide with one another. 
void GameMechanicsRules::setGGCollision( bool coll ) {

}

// Sets whether or not pacmen collide with one another. 
void GameMechanicsRules::setPPCollision( bool coll ) {

}

// Returns whether or not pacmen collide. 
bool GameMechanicsRules::getPPCollision( void ) {

}

// Returns the eat mode. 
int GameMechanicsRules::getEatMode( void ) {

}

// Sets the eat mode. 
void GameMechanicsRules::setEatMode( int em ) {

}

float* GameMechanicsRules::getSpeedArray()
{
  return speedarray;
}

int GameMechanicsRules::collision(bool first, bool second){

}

// Constructor(s)

GameMechanicsRules::GameMechanicsRules(){

}

// Destructor

GameMechanicsRules::~GameMechanicsRules ( void ) {
  
}


