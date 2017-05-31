#ifndef _CLIENT_MENU_SYSTEM_H_
#define _CLIENT_MENU_SYSTEM_H_

using namespace std;

#include "MenuSystem.h"
#include "ButtonWidget.h"
#include "LabelWidget.h"
#include "ScrollingMenuWidget.h"
#include "SliderWidget.h"
#include "RadioWidget.h"
#include "TextInputWidget.h"
#include "enums.h"
#include "Event.h"
#include <math.h>
#include <string>
#include "MenuPane.h"
#include "MenuWidget.h"

class ClientMenuSystem : public MenuSystem {
	private:

	public:
		// overrides a virtual function in MenuSystem that is
		// meant to contain any update code in a particular
		// type of menusystem, for example, if a menusystem
		// contained a slider and a label that displayed the 
		// on the slider, updateMenuDisplay should contain
		// code that reads the slider value and sets the 
		// label's text to a string representing that
		// value. in ClientMenuSystem there is nothing like
		// that to update.
		void updateMenuDisplay ( void );

		// returns the value of the IP text field
		string getIP ( void );

		// returns the value of the server port test field
		string getPort ( void );

		// returns the value of the client RUDP port test field
		string getRUDPPort ( void );

		// returns the value of the playername test field
		string getPlayerName ( void );
		
		// returns true iff the user chose the "ghost" option
		// in the pacman-or-ghost radio widget
		bool playerIsAGhost ( void );

		// the constructor;
		ClientMenuSystem ();
};


#endif
