/* Revision History

  5/13 - added this little class into the mix...
	It's mostly functional today, it doesn't look terribly good, but it works.

*/

#include "sidebar.h"
#include "text.h"


void SideBar::ortho_draw()
{
    int win_width, win_height;

    win_width = glutGet(GLUT_WINDOW_WIDTH);
    win_height = glutGet(GLUT_WINDOW_HEIGHT);

    glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

	glColor4f(0, 0, 0, 1);
	glRectf(win_width-200, 0, win_width, win_height);

//	glColor4f(.3, .7, .3, .85);
//	Text::print("this is the title bar", 15, win_height-30);

	//loop through the players here
	//it looks like 4 players will be fine, perhaps the four with the highest score
	//loop through the players

	//clear the highscorers list first to keep it as small as possible
	highscorers.clear();

	map <int, Player*>::iterator i;
	map <int, Player*> * tempplayermap = playerlist->getPlayerMap();
	for(i = tempplayermap->begin(); i != tempplayermap->end(); i++)
	{

		Player * tempplayer;
		tempplayer = i->second;
		bool justaddedhim = false;


		//if the current tempplayer's score is more than any in the list already
		for(vector<Player*>::iterator i = highscorers.begin(); i != highscorers.end(); i++)
		{
			int tempsscore= tempplayer->getScore();
			int thisguysscore = (*i)->getScore();

			if(tempplayer->getScore() > (*i)->getScore())
			{
				//the tempplayer is a higherscorer than the current iterator
				//insert the tempplayer pointer BEFORE i
				highscorers.insert(i, tempplayer);
				justaddedhim = true;
				break;
			}
		}

		//if the vector doesn't have four elements in it yet, and we didn't just add this guy
		//we have to add this guy anyway.
		if(highscorers.size()<4 && !justaddedhim)
		{
			highscorers.insert(highscorers.end(), tempplayer);
		}

	}
	delete tempplayermap;

	//now, the first four elements in the highscorers vector should be the top scorers in the game
	//it's probably not efficient to reduce the vector to only 4 elements because I'll be clearing it 
	//at the end of the loop anyway.

	//UNLESS:  it would be better to update the list every hundred iterations or so...at least every 10
	//in that case I will reduce the size of the vector
	//resize, what a great method, I almost missed it in lieu of a bunch of other junk for erasing
	if(highscorers.size()>4)
	{
		highscorers.resize(4);
	}

	//used for positioning the boxes
	int count = 0;

	//go through the four players now
	for(vector<Player*>::iterator j = highscorers.begin(); j != highscorers.end(); j++)
	{
		//pick a color for the box of the player
		//maybe use their name or ID to do it, so it stays constant
		//make sure it stays dark so that you can easily see the white writing
		GLfloat red = (GLfloat)((*j)->getPlayerID()%2)/2;
		GLfloat blue = (GLfloat)((*j)->getPlayerID()%3)/3;
		GLfloat green = (GLfloat)((*j)->getPlayerID()%4)/4;

		//set the rectangle color
		glColor3f(red, green, blue);

		//draw the opaque rectangle for behind the player's stats
		glRectf(win_width-195, win_height-105*(count+1), win_width-5, win_height-5-105*count);

		//draw their picture....this won't be supported initially, or will it?
		//no it won't

		//set the text color
		glColor3f(1, 1, 1);

		//put their name on top
		Text::print((char *)(*j)->getName().data(), win_width-180, win_height-20-105*(count), GLUT_BITMAP_HELVETICA_12);

		//then the ghost they're playing?  or name of the pacman skin they're using?
		if((*j)->isAGhost())
		{
			//output the name of the ghost here
		}
		else
		{
			//output the name of the skin file here, not supported in the skin file yet...
		}

		
		//then their score
		Text::print((*j)->getScore(), win_width-180, win_height-50-105*(count), GLUT_BITMAP_HELVETICA_12);

		count++;
	}


	//next we need this player's score and info....where are we going to get that?
	//there has to be a place that holds this player's id
	//we'll use that and put their score
	//the time they've been in the game

	//then a draw of the entire level except miniaturized
	//this will probably be left to last just because of the damn render speed of the UGCS
	//computers.  It would be easy to do though, maybe draw should accept a bool to
	//pass down to children's draw methods, and they could do less steps in the rendering
	//process depending on the variable.


    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}


//draw the chat window on the screen using the ortho draw function
void SideBar::draw(void)
{
	//make the ortho projected stuff see through....this is cool...well pretty cool
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ortho_draw();

	glDisable(GL_BLEND);

}


// Constructor(s)
SideBar::SideBar(void)
{
}

SideBar::SideBar(PlayerList * playerlistin)
{
	playerlist = playerlistin;
}

// Destructor
SideBar::~SideBar ( void )
{
}

