// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "BaseItem.h"




// Alters the gameboard in some way specified by the particular 
// class of Item. 
void BaseItem::changeGameboard( ServerGameboard * gameboard, Player *p ) {

}

// Returns a pointer to the set of game rules that this item 
// implements. 
GameRules* BaseItem::getItemRules(Player *p ) {

}

// returns ID 
int BaseItem::getID( void ) {
	return -1;
}



// Constructor(s)

BaseItem::BaseItem()
{
}

// Destructor

BaseItem::~BaseItem ( void ) {
  
}

