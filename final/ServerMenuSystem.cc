#include "ServerMenuSystem.h"
using namespace std;

/*
	updateMenuDisplay is a virtual function in MenuSystem. it contains
	code that updates any changing menu display items, such as a label
	that displays the value represented by a slider.
	 */
void ServerMenuSystem::updateMenuDisplay ( void ){
	// set the label widget corresponding the value of the number-of-floors
	// slider to display the value
	LabelWidget * floors_out = (LabelWidget *)(mainMenu->getWidget (7));
	SliderWidget * floors_slider = (SliderWidget *)(mainMenu->getWidget (228));
	floors_out->setText ( floors_slider->getSliderValue());
	
	// set the label widget corresponding the value of the floor width
	// slider to display the value
	LabelWidget * fw_out = (LabelWidget *)(mainMenu->getWidget (9));
	SliderWidget * fw_slider = (SliderWidget *)(mainMenu->getWidget (229));
	fw_out->setText ( fw_slider->getSliderValue());
	
	// set the label widget corresponding the value of the floor length
	// slider to display the value
	LabelWidget * f_len_out = (LabelWidget *)(mainMenu->getWidget (11));
	SliderWidget * f_len_slider = (SliderWidget *)(mainMenu->getWidget (230));
	f_len_out->setText ( f_len_slider->getSliderValue());
	
	// set the label widget corresponding the value of the max. pacmen
	// slider to display the value
	LabelWidget * f_mp_out = (LabelWidget *)(mainMenu->getWidget (13));
	SliderWidget * f_mp_slider = (SliderWidget *)(mainMenu->getWidget (231));
	f_mp_out->setText ( f_mp_slider->getSliderValue());
	
	// set the label widget corresponding the value of the max. ghosts
	// slider to display the value
	LabelWidget * f_mg_out = (LabelWidget *)(mainMenu->getWidget (15));
	SliderWidget * f_mg_slider = (SliderWidget *)(mainMenu->getWidget (232));
	f_mg_out->setText ( f_mg_slider->getSliderValue());
}

/*
	returns the value of the number-of-floors slider
	 */
int ServerMenuSystem::getNumFloors ( void ){
	SliderWidget * floors_slider = (SliderWidget *)(mainMenu->getWidget (228));
	return ( floors_slider->getSliderValue());
}

/*
	returns the value of the level-width slider
	 */
int ServerMenuSystem::getLevelWidth ( void ){
	SliderWidget * fw_slider = (SliderWidget *)(mainMenu->getWidget (229));
	return ( fw_slider->getSliderValue());
}


/*
	returns the value of the level-height slider
	 */
int ServerMenuSystem::getLevelHeight ( void ){
	SliderWidget * f_len_slider = (SliderWidget *)(mainMenu->getWidget (230));
	return ( f_len_slider->getSliderValue());
}

/*
	returns the value of the max pacmen slider
	 */
int ServerMenuSystem::getMaxPacmen ( void ){
	SliderWidget * f_mp_slider = (SliderWidget *)(mainMenu->getWidget (231));
	return ( f_mp_slider->getSliderValue());
}

/*
	returns the value of the max ghosts slider
	 */
int ServerMenuSystem::getMaxGhosts ( void ){
	SliderWidget * f_mg_slider = (SliderWidget *)(mainMenu->getWidget (232));
	return ( f_mg_slider->getSliderValue());
}

/*
	 sets up the hardcoded server menu system
	 */
ServerMenuSystem::ServerMenuSystem ( void ) : MenuSystem () {
// widgets for server's menus
	
	int y_value = 210;
	int y_inc = 70;

	// there are five sliders in the menu, each of which has two associated
	// labels which contain its description, and its value.

	
	// create the widgets for the number of floors slider
	LabelWidget * label_num_floors = new LabelWidget (50,20,100,y_value,"Number of Floors:", 6);
	LabelWidget * label_num_floors_out = new LabelWidget (50,20,620,y_value,"1", 7);
	SliderWidget * slider_num_floors = new SliderWidget (400,385,y_value,1,5,1,228);
	// add the widgets to the menupane
	mainMenu->addWidget (slider_num_floors);
	mainMenu->addWidget (label_num_floors);
	mainMenu->addWidget (label_num_floors_out);
	
	// increment the y_value so that the next set of widgets is drawn
	// further down the screen
	y_value += y_inc;

	// create the widgets for the floor-width slider
	LabelWidget * label_floor_width = new LabelWidget (50,20,100,y_value,"Floor Width:", 8);
	LabelWidget * label_floor_width_out = new LabelWidget (50,20,620,y_value,"25", 9);
	SliderWidget * slider_floor_width = new SliderWidget (400,385,y_value,10,200,25,229);
	// add the widgets to the menu pane
	mainMenu->addWidget (slider_floor_width);
	mainMenu->addWidget (label_floor_width);
	mainMenu->addWidget (label_floor_width_out);

	// increment the y_value at which widgets are drawn
	y_value += y_inc;

	// create the widgets for the floor-length slider
	LabelWidget * label_floor_length = new LabelWidget (50,20,100,y_value,"Floor Length:", 10);
	LabelWidget * label_floor_length_out = new LabelWidget (50,20,620,y_value,"25", 11);
	SliderWidget * slider_floor_length = new SliderWidget (400,385,y_value,10,200,25,230);
	// add the widgets to the menu pane
	mainMenu->addWidget (slider_floor_length);
	mainMenu->addWidget (label_floor_length);
	mainMenu->addWidget (label_floor_length_out);
	y_value += y_inc;

	// create the widgets fort the number-of-pacmen slider
	LabelWidget * label_max_pacmen = new LabelWidget (50,20,100,y_value,"Max. Pacmen:", 12);
	LabelWidget * label_max_pacmen_out = new LabelWidget (50,20,620,y_value,"4", 13);
	SliderWidget * slider_max_pacmen = new SliderWidget (400,385,y_value,1,30,4,231);
	// add the widgets to the menupane
	mainMenu->addWidget (slider_max_pacmen);
	mainMenu->addWidget (label_max_pacmen);
	mainMenu->addWidget (label_max_pacmen_out);
	y_value += y_inc;

	// create the widgets for the max. # of ghosts.
	LabelWidget * label_max_ghosts = new LabelWidget (50,20,100,y_value,"Max. Ghosts:", 14);
	LabelWidget * label_max_ghosts_out = new LabelWidget (50,20,620,y_value,"4", 15);
	SliderWidget * slider_max_ghosts = new SliderWidget (400,385,y_value,1,30,4,232);
	// add the widgets to the menupane
	mainMenu->addWidget (slider_max_ghosts);
	mainMenu->addWidget (label_max_ghosts);
	mainMenu->addWidget (label_max_ghosts_out);
	y_value = y_value + (700-y_value)/2;


	// finally, create the button that terminates the menusystem. it must
	// have ID # 135
	ButtonWidget * bw_OK = new ButtonWidget (200, 50, 365, y_value, "Start", 135);
	mainMenu->addWidget (bw_OK);

	// oh, and don't forget to add the labels at the top that tell
	// the player that they're running multiplayer internet pacman
	// server edition.
	LabelWidget * label_header_1 = new LabelWidget (50,20,365, 60, "Welcome to", 30);
	LabelWidget * label_header_2 = new LabelWidget (50,20,365, 90, "Multiplayer Internet Pacman", 31);
	LabelWidget * label_header_3 = new LabelWidget (50,20,365, 120, "Server Edition", 32);
	mainMenu->addWidget (label_header_1);
	mainMenu->addWidget (label_header_2);
	mainMenu->addWidget (label_header_3);
	
}
