#ifndef _SERVER_MENU_SYSTEM_H_
#define _SERVER_MENU_SYSTEM_H_

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

class ServerMenuSystem : public MenuSystem {
	private:

	public:
		/*
			updateMenuDisplay is a virtual function in MenuSystem. it contains
			code that updates any changing menu display items, such as a label
			that displays the value represented by a slider.
			 */
		void updateMenuDisplay ( void );


		/*
			returns the value of the number-of-floors slider
			 */
		int getNumFloors ( void );

		/*
			returns the value of the level-width slider
			 */
		int getLevelWidth ( void );

		/*
			returns the value of the level-height slider
			 */
		int getLevelHeight ( void );

		/*
			returns the value of the max pacmen slider
			 */
		int getMaxPacmen ( void );

		/*
			returns the value of the max ghosts slider
			 */
		int getMaxGhosts ( void );

		/*
			sets up the hardcoded server menu system
			*/
		ServerMenuSystem ();
};


#endif
