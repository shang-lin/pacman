#include "ClientMenuSystem.h"
#include <unistd.h>
using namespace std;


/*
	overrides a virtual function in MenuSystem that is
	meant to contain any update code in a particular
	type of menusystem, for example, if a menusystem
	contained a slider and a label that displayed the 
	on the slider, updateMenuDisplay should contain
	code that reads the slider value and sets the 
	label's text to a string representing that
	value. in ClientMenuSystem there is nothing like
	that to update.
	*/
void ClientMenuSystem::updateMenuDisplay ( void ){
	// nothing to do for client menus..
}



/*
	returns the value of the IP text field
	*/
string ClientMenuSystem::getIP ( void ){
	// the IP text input widget is #128
	TextInputWidget * tiw = (TextInputWidget *)(mainMenu->getWidget (128));
	return (tiw->getValue());
}



/*
	 returns the value of the server port test field
	 */
string ClientMenuSystem::getPort ( void ){
	// the port text input widget is #129
	TextInputWidget * tiw = (TextInputWidget *)(mainMenu->getWidget (129));
	return (tiw->getValue());
}




/*
	 returns the value of the client RUDP port test field
	 */
string ClientMenuSystem::getRUDPPort ( void ){
	// the rudp port text input widget is #130
	TextInputWidget * tiw = (TextInputWidget *)(mainMenu->getWidget (130));
	return (tiw->getValue());
}




/*
	 returns the value of the playername test field
	 */
string ClientMenuSystem::getPlayerName ( void ){
	// the player name text input widget is #131
	TextInputWidget * tiw = (TextInputWidget *)(mainMenu->getWidget (131));
	return (tiw->getValue());
}




/*
	returns true iff the user chose the "ghost" option
	in the pacman-or-ghost radio widget
	*/
bool ClientMenuSystem::playerIsAGhost ( void ){
	// the player type radio button has ID # 132. "ghost" has ID 134,
	// and "pacman" has ID 133
	RadioWidget * rw = (RadioWidget *)(mainMenu->getWidget (132));
	return (rw->getValue() == 134);
}




/* Constructor */
ClientMenuSystem::ClientMenuSystem ( void ) : MenuSystem () {
	 // Widgets for clients' menus
	 
	int y_value = 170;
	int y_inc = 80;

	TextInputWidget * tiw_IP = new TextInputWidget (458, 375,y_value, 32,128);
	mainMenu->addWidget (tiw_IP);
	y_value += y_inc;

	TextInputWidget * tiw_port = new TextInputWidget (458, 375,y_value, 8,129);
	mainMenu->addWidget (tiw_port);
	y_value += y_inc;

	TextInputWidget * tiw_rudp_port = new TextInputWidget (458, 375,y_value, 8,130);
	mainMenu->addWidget (tiw_rudp_port);
	y_value += y_inc;

	TextInputWidget * tiw_player_name = new TextInputWidget (458, 375,y_value, 32,131);
	mainMenu->addWidget (tiw_player_name);
	y_value += y_inc + 20;

	RadioWidget * rw_player_type = new RadioWidget (408,50,375, y_value, 132);
	rw_player_type->addEntry ( "Pacman", 133 );
	rw_player_type->addEntry ( "Ghost", 134 );
	mainMenu->addWidget (rw_player_type);
	y_value += (700 - y_value)/2;

	ButtonWidget * bw_OK = new ButtonWidget (200, 50, 350, y_value, "Start", 135);
	mainMenu->addWidget (bw_OK);


	y_value = 170;
	y_inc = 80;

	LabelWidget * label_IP = new LabelWidget (50,20,80,y_value,"Server IP:", 1);
	mainMenu->addWidget (label_IP);
	y_value += y_inc;

	LabelWidget * label_port = new LabelWidget (50,20,80,y_value,"Server Port:", 2);
	mainMenu->addWidget (label_port);
	y_value += y_inc;

	LabelWidget * label_rudp_port = new LabelWidget (50,20,80,y_value,"RUDP Port:", 3);
	mainMenu->addWidget (label_rudp_port);
	y_value += y_inc;

	LabelWidget * label_player_name = new LabelWidget (50,20,80,y_value,"Player Name:", 4);
	mainMenu->addWidget (label_player_name);
	y_value += y_inc + 20;

	LabelWidget * label_is_a_ghost = new LabelWidget (50,20,80,y_value,"Player Type:", 5);
	mainMenu->addWidget (label_is_a_ghost);



	LabelWidget * label_header_1 = new LabelWidget (50,20,350, 60, "Welcome to", 30);
	LabelWidget * label_header_2 = new LabelWidget (50,20,350, 90, "Multiplayer Internet Pacman", 31);
	LabelWidget * label_header_3 = new LabelWidget (50,20,350, 120, "Client Edition", 32);
	mainMenu->addWidget (label_header_1);
	mainMenu->addWidget (label_header_2);
	mainMenu->addWidget (label_header_3);

}
