#ifndef _GAMECLIENT_H_
#define _GAMECLIENT_H_

class GameClient;

// The includes for the superclasses are automatically listed.
// You need to specify any others

#include "GameBoard.h"
#include "MenuSystem.h"
#include "GameRules.h"
#include "UDPacket.h"

// Description:
//
// Holds the menu and gameboard. This is the Model & View. This 
// will be a global object. It passes events to other objects 
// depending on the current mode of the game (ie, menu mode, 
// or in-game mode). This object also hold the client-side networking 
// objects.  Once the game has started and GameBoard has been launched, 
// this class becomes essentially inactive.

class GameClient {
  // Data Members

 private:
  // The gameboard. 
  Gameboard *gameboard;

  // True if the game is in menu mode. False otherwise. 
  bool menuMode;

  // The menu system. It basically manages itself. Once it terminates, 
  // this object will generate the gameboard based on the menu 
  // choices. 
  MenuSystem * menuSystem;

  // Array of MP3s to be played during the game. 
  // MP3[] musicplaylist;

  // The MP3 that is played while the menusystem is active. 
  // MP3 menumusic;

  // The hashtable containing all the image objects. Keys are integers. 
  // DrawableObject's generic draw() function simply looks up an 
  // image in this table and draws it. 
  //GraphicsHashTable graphicshash;

  // The game mode. ModeID is an enumerated type. 
  int mode;

  // This is the set of rules for the game. The game client only 
  // uses the AI rules in singleplayer mode. Otherwise, the gameclient 
  // uses the mechanics rules to smooth out the animation between 
  // server updates. 
  GameRules *rules;



 public:


  // Methods

 private:


 public:
  // This registers a listener with the client, so that when the 
  // client
  // generates events it will give them to listener, as well as 
  // any others
  // that have been registered. 
  //void addListener( EventListener* );

  // Sets up the networking. If isGameCreator is true, it sets 
  // up this client and also a game server. Otherwise, it just 
  // sets up this client. 
  void setupNetworking( bool );

  // Handles/forwards events. 
  void receiveEvent( UDPacket );

  // ModeID is an enumerate type. This function sets the game mode 
  // variable in the client. This function only works while the 
  // client is in the menu system. The game mode should not change 
  // after that. 
  void setMode( int );

  // Returns a pointer to the game board. 
  Gameboard * getGameBoard( void );

  // Returns true if we're in menu mode, and false otherwise. 
  bool inMenuMode( void );



  // Constructor(s)



  // Destructor

  ~GameClient ( void );

};

#endif

