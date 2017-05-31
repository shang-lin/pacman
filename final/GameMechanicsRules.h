#ifndef _GAMEMECHANICSRULES_H_
#define _GAMEMECHANICSRULES_H_

class GameMechanicsRules;

#include "GameBoard.h"

// The includes for the superclasses are automatically listed.
// You need to specify any others


// Description:
//
// Defines the rules of game mechanics, such as pacman and ghost 
// speed, collision detection, who can eat what, etc. 
// Changes are made to this class whenever a GameRules object is 
// either created or destroyed (when an item is eaten or a set of
// rules expire).

class GameMechanicsRules {
  // Data Members

 private:
  // This is -1 if th set of rules is to persist indefinitely. 
  // Otherwise, we set it to the number of milliseconds for which 
  // it should persist. Setting it to 0 has the effect of only 
  // applying the rules once; this would be useful for the 'switch 
  // positions' item. 
  int persistence;

  // The velocity of ghosts. 
  float ghostSpeed;

  // The velocity of pacmen. 
  float pacmanSpeed;

  // True if ghosts collide, false otherwise. 
  bool ghostCollisionOn;

  // True if pacmen collide, false otherwise. 
  bool pacmanCollisionOn;

  // True if pacmen collide with ghosts, false otherwise. This 
  // assumes that there are some game states where neither group 
  // can eat members of the other group. 
  bool pacmanGhostCollisionOn;

  // The time (in milliseconds) at which we started using this 
  // set of rules. 
  long startTime;

  // This is an enumerated type with values pacmanEatsGhost, ghostEatsPacman, 
  // noEating. 
  int eatmode;

  float *speedarray;  // contains the speed for each player in the game



 public:


  // Methods

 private:


 public:
  // True if persistance == -1, false otherwise. 
  bool isPersistant( void );

  float* getSpeedArray();

  // Sets the start time of the rule set. 
  int setStartTime( long );

  // Returns true iff the current time minus the start time is 
  // greater than the persistance. 
  bool isExpired( long );

  // Applies the game mechanics rules to the specified game. 
  void applyRules( Gameboard * );

  // Sets the ghost speed. 
  void setGhostSpeed( int );

  // Sets the pacman speed. 
  void setPacmanSpeed( int );

  // Returns the pacman speed. 
  int getPacmanSpeed( void );

  // Returns the ghost speed. 
  int getGhostSpeed( void );

  // Sets whether or not ghosts collide with one another. 
  void setGGCollision( bool );

  // Sets whether or not pacmen collide with one another. 
  void setPPCollision( bool );

  // Returns whether or not pacmen collide. 
  bool getPPCollision( void );

  // Returns the eat mode. 
  int getEatMode( void );

  // Sets the eat mode. 
  void setEatMode( int );

  int collision(bool first, bool second);

  // Constructor(s)

  GameMechanicsRules();

  // Destructor

  ~GameMechanicsRules ( void );

};

#endif

