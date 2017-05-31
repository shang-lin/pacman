#ifndef _AIRULES_H_
#define _AIRULES_H_

class AIRules;
class Level;

// The includes for the superclasses are automatically listed.
// You need to specify any others

#include "Level.h"
#include "Space.h"

// Description:
//
// Defines the rules of the ghost AI, such as whether ghosts 
// want to move towards or away from pacmen.
 

class AIRules {
  // Data Members

 private:
  // Ghosts assign each adjacent square a ranking. The formula 
  // for that ranking is (distance from square to nearest pacman)*pacmanAttraction. 
  // The square with the highest ranking is picked. Therefore, 
  // to make the ghosts move towards pacman, make this value positive; 
  // to make them move away, make this value negative. If you want 
  // the ghosts to choose squares randomly (ghosts always choose 
  // randomly between identically-ranked squares), set this value 
  // to zero.
 
  int pacmanAttraction;

  // The number of squares that a ghost can see. Note that ghosts 
  // can only see in straight lines.
 
  int visionRange;



 public:


  // Methods

 private:


 public:
  // Returns a pointer to the preferred adjacent space. If the 
  // ghost has not been eaten, it does this dependent on the value 
  // of pacmanAttraction. If it has been eaten, then the preferred 
  // adjacent space is that space which brings the ghost closer 
  // to a respawn point. Distances to respawn points can be calculated 
  // in O(n) time with a breadth-first search. Distances to pacmen 
  // are even easier to calculate, since ghosts can only see in 
  // a straight line, so we just need to keep searching north, 
  // south, east, and west until we see a pacman. 
  Space * findBestAdjacentSquare( Space *, Level * );

  // Modifies the value of pacmanAttraction. 
  void setPacmanAttraction( int );

  // Returns the value of pacmanAttraction. 
  int getPacmanAttraction( void );

  // Modifies the vision range of ghosts. 
  void setVisionRange( int );

  // Returns the vision range of ghosts. 
  int getVisionRange( void );



  // Constructor(s)

  // Creates a generic AIRules object. 
  AIRules ( void );



  // Destructor

  ~AIRules ( void );

};

#endif

