// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "GameClient.h"




// This registers a listener with the client, so that when the 
// client
// generates events it will give them to listener, as well as 
// any others
// that have been registered. 
//void GameClient::addListener( EventListener* listener ) {
//
//}

// Sets up the networking. If isGameCreator is true, it sets 
// up this client and also a game server. Otherwise, it just 
// sets up this client. 
void GameClient::setupNetworking( bool isGameCreator ) {

}

// Handles/forwards events. 
void GameClient::receiveEvent( UDPacket pack ) {

}

// ModeID is an enumerate type. This function sets the game mode 
// variable in the client. This function only works while the 
// client is in the menu system. The game mode should not change 
// after that. 
void GameClient::setMode( int newmode ) {

}

// Returns a pointer to the game board. 
Gameboard* GameClient::getGameBoard( void ) {

}

// Returns true if we're in menu mode, and false otherwise. 
bool GameClient::inMenuMode( void ) {

}



// Constructor(s)



// Destructor

GameClient::~GameClient ( void ) {
  
}


