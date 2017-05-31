#ifndef _GAMERULES_H_
#define _GAMERULES_H_

class GameRules;

#include "GameMechanicsRules.h"
#include "AIRules.h"
#include "GameBoard.h"

// The includes for the superclasses are automatically listed.
// You need to specify any others


// Description:
//
// This object modifies settings in GameMechanicsRules such as ghost speed,
// pacman speed, etc. that the server would apply to the game. Items 
// that modify the rules of the game contain a pointer 
// to a GameRules object. When the item is eaten, the server 
// replaces its standard GameRules pointer with the item's 
// GameRules pointer for the specified period of time. 

class GameRules {
  // Data Members

 private:
  // The rules for game mechanics. 
  GameMechanicsRules *gameMechanics;

  // The rules for ghost AI. 
  AIRules *ai;

  // This variable gets decremented by the RunGame function in 
  // the GameServer class.  When it hits 0, the GameServer will 
  // revert back to the previously existing GameRules.  -1 will 
  // be used for permanent rules. 
  int time;



 public:


  // Methods

 private:


 public:
  // Applies the rules to the game. That is, it detects collisions 
  // (with items, ghosts, pacmen) and alters the game state accordingly, 
  // and computes the next position of pacmen and ghosts. 
  void applyRules( Gameboard *thegame );

  // Changes the game mechanics.  If persistant is true, then this 
  // is a permanent change, so forget about the old game mechanics. 
  // otherwise, save the old game mechanics and use the new game 
  // mechanics for the specified period of time. 
  void changeGameMechanics( GameMechanicsRules *gmr, bool persistent);

  // Changes the game mechanics. We'll ask gmr whether or not it 
  // is persistant. If so, then this is a permanent change, so 
  // forget about the old game mechanics. otherwise, save the old 
  // game mechanics and use the new game mechanics for the specified 
  // period of time. 
  void changeGameMechanics( GameMechanicsRules *gmr );

  // Decrements the time variable. 
  void decrementTime( void );

  // Returns true iff the value of time is 0. 
  bool expired( void );



  // Constructor(s)

  GameRules();

  // Destructor

  ~GameRules ( void );

};

#endif

