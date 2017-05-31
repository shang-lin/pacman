#ifndef _AIGHOST_H_
#define _AIGHOST_H_
#include "player.h"

class AIGhost : public Player{
 public:
  AIGhost(int i);  // needs to construct a decision rule for each ghost
  
  void decide();
};

#endif
