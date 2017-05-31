#ifndef _POWERPELLET_H_
#define _POWERPELLET_H_


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "BaseItem.h"
#include "drawableobject.h"


// Description:
//
// This subclass of BaseItem represents a power pellet on the 
// game board. When a pacman eats a power pellet, it can eat 
// ghosts for a certain time period. 

class PowerPellet : private BaseItem{
                // Data Members

        private:


        public:


                // Methods

        private:


        public:


                // Constructor(s)
                PowerPellet(); 


                // Destructor

                ~PowerPellet ( void );

};

#endif

