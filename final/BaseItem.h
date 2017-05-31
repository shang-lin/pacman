#ifndef _BASEITEM_H_
#define _BASEITEM_H_

class BaseItem;

#include "GameRules.h"

// The includes for the superclasses are automatically listed.
// You need to specify any others
//#include "drawableobject.h"


#include "drawableobject.h"
#include "ServerGameboard.h"


// Description:
//
// This class represents items on the gameboard, ranging from 
// pellets to special items. Specific items inherit from this 
// base class. Every item object has a function ChangeGameboard 
// that alters the state of the game when the item is eaten.
 
// //
// 
//
// If we simply give each object a pointer to a set of game rules, 
// we can avoid having to have a separate class for each type 
// of item. 

class BaseItem : private DrawableObject{
  // Data Members

 private:
  // A pointer to the GameRules object that this Item implements. 
  // When the item is eaten, the server uses that item's game rules 
  // for the period of time specified in the object. 
  GameRules* gmr;

  // True if pacmen can eat this item. False Otherwise. 
  bool isPacmanItem;

  // True if ghosts can eat this item. False otherwise. 
  bool isGhostItem;

  // ID number to identify item to the server 
  int ID;



 public:


  // Methods

 private:


 public:
  // Alters the gameboard in some way specified by the particular 
  // class of Item. 
  void changeGameboard(ServerGameboard * gb, Player *p );

  // Returns a pointer to the set of game rules that this item 
  // implements. 
  GameRules* getItemRules(Player *eater);

  // returns ID 
  int getID( void );

  // returns true if item is a pacman item, false if it is a ghost item
  virtual bool IsPacItem() { return true; }



  // Constructor(s)

  BaseItem();

  // Destructor

  ~BaseItem ( void );

};

#endif

