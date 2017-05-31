#ifndef _SIDEBAR_H_
#define _SIDEBAR_H_

//this pragma warning is really a POS, I found it by shear luck, I would hate to have been searching
//for how to fix a billion errors
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


// The includes for the superclasses are automatically listed.
// You need to specify any others
#include "drawableobject.h"
#include "playerlist.h"

// Description:
//
// This object represents the score display marquee. It is drawn 
// as an opaque overlay over the board. It will display scores

class SideBar : private DrawableObject
{
		// Data Members

	private:

		PlayerList * playerlist;
		vector<Player*> highscorers ;


	public:


		// Methods

	private:

		//draws onto the view using the orthogonal projection matrix
		//this should mean that the drawing overwrites anything that is on the viewing screen
		//this also means that orthodrawing must be done in order of what you want to appear:
		// side bar -> text/scores
		void ortho_draw(void); 

	public:

		void draw(void);


		// Constructor(s)

		SideBar(void);
		SideBar(PlayerList * playerlistin);


		// Destructor

		~SideBar ( void );

};

#endif
